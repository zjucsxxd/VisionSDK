/**********************************************************************
Copyright ©2013 Advanced Micro Devices, Inc. All rights reserved.

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

•   Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
•   Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or
 other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY
 DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
********************************************************************/

#include <CL/cl.h>
#include <stdio.h>
#include <stdlib.h>
//#include <iostream>
#include <fstream>
#include <cstring>
#include <iostream>

#include "SDKUtil.hpp"
#include "CLUtil.hpp"

#ifdef WIN32
using namespace appsdk;
#else
#include "APU_OCL_LOAD.hpp"
#endif

using namespace std;
const int  width= 256;
const int  sizespace=4;
const int  localsize=16;

/* read the kernel into a string */
int convertToString(const char *filename, std::string& s)
{
    size_t size;
    char*  str;

    std::fstream f(filename, (std::fstream::in | std::fstream::binary));

    if(f.is_open())
    {
        size_t fileSize;
        f.seekg(0, std::fstream::end);
        size = fileSize = (size_t)f.tellg();
        f.seekg(0, std::fstream::beg);

        str = new char[size+1];
        if(!str)
        {
            f.close();
            return 0;
        }

        f.read(str, fileSize);
        f.close();
        str[size] = '\0';

        s = str;
        delete[] str;
        return 0;
    }
    //std::cout<<"Error: faileded to open file \n"<<filename;
    return -1;
}

int MemoryModel_main()
{

    int m_test[width];
    int *outBuf=new int[width];
    int *verificationBuf=new int[width];
    const int mask[sizespace] = {1, -1, 2, -2}; //used to compute result on cpu
    std::cout << "\t.............MemoryModel Test............." << std::endl;
	 
    // initialization array 
    //std::cout << "Input Array: " << std::endl;
    for(int i=0; i<width; i++)
    {
        m_test[i]=i+1;
        //if(i%16==0)
        //{
        //    std::cout<< std::endl;
        //}
        //std::cout<< m_test[i] << " ";
    }
    //std::cout<< std::endl << std::endl;
    //std::cout<<"GPU computing......." << std::endl;

    /* Get Platforms and choose an available one */
    cl_int status;
    cl_platform_id platform=NULL;
    cl_uint numPlatforms = 0;
    status=clGetPlatformIDs(0,NULL,&numPlatforms);
    if(status!=CL_SUCCESS)
    {
        //std::cout<<"Get paltform failed\n";
        return -1;
    }
    if(numPlatforms>0)
    {
        cl_platform_id* platforms = (cl_platform_id* )malloc(numPlatforms* sizeof(
                                        cl_platform_id));
        status=clGetPlatformIDs(numPlatforms,platforms,NULL);
        platform=platforms[0];
        free(platforms);
    }

	/* Query the context and get the available devices */
    cl_uint numDevice=0;
    status=clGetDeviceIDs(platform,CL_DEVICE_TYPE_ALL,0,NULL,&numDevice);
    cl_device_id *device=(cl_device_id*)malloc(numDevice*sizeof(cl_device_id));
    if (device == 0)
    {
        //std::cout << "No device available\n";
        return -1;
    }

	cl_uint *devId = (cl_uint*)malloc(numDevice*sizeof(cl_uint));
    clGetDeviceIDs(platform,CL_DEVICE_TYPE_ALL,numDevice,device,devId);
	cl_context_properties cps[3] =
	{
		CL_CONTEXT_PLATFORM,
		(cl_context_properties)platform,
		0
	};

#ifdef WIN32
	cl_device_type dType = CL_DEVICE_TYPE_CPU;

	// Display available devices.
	int err = displayDevices(platform, dType);
	CHECK_ERROR(err, SDK_SUCCESS, "displayDevices() failed");
#endif
    /* Create Context using the platform selected above */
    //cl_context context=clCreateContext(NULL,numDevice,device,NULL,NULL,NULL);
    cl_context context= clCreateContextFromType(
                                                cps, //NULL,
                                                CL_DEVICE_TYPE_ALL,
                                                NULL, NULL, NULL);
   
    /* create command queue */
    cl_command_queue queue0=clCreateCommandQueue(context,device[0],
                            CL_QUEUE_PROFILING_ENABLE,NULL);

    /* create cl_buffer objects */
    cl_mem clsrc=clCreateBuffer(context,CL_MEM_READ_ONLY|CL_MEM_COPY_HOST_PTR,
                                width * sizeof(int),m_test,NULL);
    cl_mem clout=clCreateBuffer(context,CL_MEM_WRITE_ONLY|CL_MEM_ALLOC_HOST_PTR,
                                width * sizeof(int),NULL,NULL);

    /* Create program object */
    //cl_program program=clCreateProgramWithSource(context,1,&source,sourceSize,NULL);
    size_t binsz = sizeof(int32_t*);
	cl_program program;
#ifndef WIN32
    int32_t *program_bin = (int32_t *)APU_OCL_LOAD_SEGMENTS;
    void* pos  = (void *)&program_bin;    
    program= clCreateProgramWithBinary(context, 1, &device[0],
	    &binsz, (const unsigned char**)&pos, NULL, NULL);
#else
	CLCommandArgs sampleArgs;
	CHECK_ERROR(sampleArgs.initialize(), SDK_SUCCESS,
		"OpenCL resource initilization failed");

	buildProgramData buildData;
	buildData.kernelName = std::string("../../../../kernels/cl/unsorted_kernels/src/MemoryModel.cl");
	buildData.devices = &device[0];
	buildData.deviceId = 0;// devId;
	buildData.flagsStr = std::string("");
	if (sampleArgs.isLoadBinaryEnabled())
	{
		buildData.binaryName = std::string(sampleArgs.loadBinary.c_str());
	}

	if (sampleArgs.isComplierFlagsSpecified())
	{
		buildData.flagsFileName = std::string(sampleArgs.flags.c_str());
	}

	int retValue = buildOpenCLProgram(program, context, buildData);
	CHECK_ERROR(retValue, 0, "buildOpenCLProgram() failed");

#endif

    /* Build program object */
    //status=clBuildProgram(program,1,device,NULL,NULL,NULL);
    status=clBuildProgram(program,0,NULL,NULL,NULL,NULL);
    if(status!=CL_SUCCESS)
    {
        //std::cout<<"Building program failed\n";
        return -1;
    }

    /* Create kernel object */
    cl_kernel kernel=clCreateKernel(program,"MemoryModel", NULL);

    /* Set Kernel arguments */
    clSetKernelArg(kernel,0,sizeof(cl_mem),(void *)&clout);
    clSetKernelArg(kernel,1,sizeof(cl_mem),(void *)&clsrc);

    size_t globalws[1]= {width};
    size_t localws[1]= {localsize};

    /* Enqueue kernel into command queue and run it */
    clEnqueueNDRangeKernel(queue0,kernel,1,0,globalws,localws,0,NULL,NULL);

    clFinish(queue0);

    /* Read the output back to host memory */
    status = clEnqueueReadBuffer(
                 queue0, clout,
                 CL_TRUE,        /* Blocking Read Back */
                 0, width*sizeof(int),(void*)outBuf, 0, NULL, NULL);

    /*compute the results on CPU,in order to verify*/
    for(int i=0; i<width; i++)
    {
        int interation=i/localsize;
        int t=interation*localsize;
        int result = 0;
        for (int j = 0; j < 4; j++)
        {
            result += m_test[(i+j)%localsize+t];
        }
        result *= mask[interation%sizespace];
        verificationBuf[i]= result;
    }

    // compare the results and see if they match
    if(memcmp(outBuf, verificationBuf,width*sizeof(int)) == 0)
    {
        std::cout<<"Passed!\n" << std::endl;
    }
    else
    {
        std::cout<<"Failed\n" << std::endl;
    }

    /*clean up*/
    if(outBuf)
    {
        free(outBuf);
    }
    if(verificationBuf)
    {
        free(verificationBuf);
    }
    /* Release OpenCL resource object */
    status =clReleaseKernel(kernel);
    status =clReleaseMemObject(clsrc);
    status =clReleaseMemObject(clout);
    status =clReleaseProgram(program);
    status =clReleaseCommandQueue(queue0);
    status =clReleaseContext(context);
    free(device);

	 
    return 0;
}
