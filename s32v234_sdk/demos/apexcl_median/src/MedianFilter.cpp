// Copyright (c) 2009-2011 Intel Corporation
// All rights reserved.
// 
// WARRANTY DISCLAIMER
// 
// THESE MATERIALS ARE PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL INTEL OR ITS
// CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
// EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
// PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
// PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
// OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY OR TORT (INCLUDING
// NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THESE
// MATERIALS, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
// 
// Intel Corporation is the author of the Materials, and requests that all
// problem reports or change requests be submitted to it directly

//#include "stdafx.h"
//#include "CL/cl.h"
#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <iostream>

#include "CLUtil.hpp"
#include "SDKUtil.hpp"

#ifdef WIN32
using namespace appsdk;
#else
#include "APU_OCL_LOAD.hpp"
#endif
//#include "utils.h"


#define LOCAL_SIZE_X 8
#define LOCAL_SIZE_Y 8

cl_mem		g_inputBuffer_regular = NULL, g_inputBuffer_async = NULL, g_inputBuffer_async2d = NULL;
cl_mem		g_outputBuffer_regular = NULL, g_outputBuffer_async = NULL, g_outputBuffer_async2d = NULL;
cl_context	g_context = NULL;
cl_command_queue g_cmd_queue = NULL;
cl_program	g_program = NULL;
cl_kernel	g_kernel_regular = NULL, g_kernel_async = NULL, g_kernel_async2d = NULL;
cl_int      g_min_align = 0;

bool g_bRunOnPG = false;


void Cleanup_OpenCL()
{
    if( g_inputBuffer_regular ) {clReleaseMemObject( g_inputBuffer_regular ); g_inputBuffer_regular = NULL;}
    if( g_inputBuffer_async ) {clReleaseMemObject( g_inputBuffer_async ); g_inputBuffer_async = NULL;}
    if( g_inputBuffer_async2d ) {clReleaseMemObject( g_inputBuffer_async2d ); g_inputBuffer_async2d = NULL;}
    if( g_outputBuffer_regular ) {clReleaseMemObject( g_outputBuffer_regular ); g_outputBuffer_regular = NULL;}
    if( g_outputBuffer_async ) {clReleaseMemObject( g_outputBuffer_async ); g_outputBuffer_async = NULL;}
    if( g_outputBuffer_async2d ) {clReleaseMemObject( g_outputBuffer_async2d ); g_outputBuffer_async2d = NULL;}	
    if( g_kernel_regular ) {clReleaseKernel( g_kernel_regular ); g_kernel_regular = NULL;}
    if( g_kernel_async ) {clReleaseKernel( g_kernel_async ); g_kernel_async = NULL;}    
    if( g_kernel_async2d ) {clReleaseKernel( g_kernel_async2d ); g_kernel_async2d = NULL;}    	
	if( g_program ) {clReleaseProgram( g_program ); g_program = NULL;}
    if( g_cmd_queue ) {clReleaseCommandQueue( g_cmd_queue ); g_cmd_queue = NULL;}
    if( g_context ) {clReleaseContext( g_context ); g_context = NULL;}
}

char* ReadSources(const char *fileName) {
	FILE *f = fopen(fileName, "rt");
	if (f != NULL) {
		int fileLen = fseek(f, 0, SEEK_END);
		fileLen = ftell(f);
		fseek(f, 0, SEEK_SET);
		char *content = new char[fileLen];
		fread(content, sizeof(char), fileLen, f);
		fclose(f);
		return content;
	}
	return NULL;
}

int Setup_OpenCL( const char * program_source, const int32_t *program_bin)
{
    cl_device_id devices[16];
    size_t cb;
    cl_int err;
    int num_cores;
    cl_device_id device_ID;
    char device_name[128] = {0};

#ifdef WIN32

	CLCommandArgs   sampleArgs;   /**< CLCommand argument class */
	sampleArgs.deviceType.clear();
	sampleArgs.deviceType.append("cpu");

	cl_int status = 0;
	cl_device_type dType;

	if (sampleArgs.deviceType.compare("cpu") == 0)
	{
		dType = CL_DEVICE_TYPE_CPU;
	}
	else //deviceType = "gpu"
	{
		dType = CL_DEVICE_TYPE_GPU;
		if (sampleArgs.isThereGPU() == false)
		{
			std::cout << "GPU not found. Falling back to CPU device" << std::endl;
			dType = CL_DEVICE_TYPE_CPU;
		}
	}
	cl_platform_id platform = NULL;
	int retValue = getPlatform(platform, sampleArgs.platformId,
		sampleArgs.isPlatformEnabled());
	CHECK_ERROR(retValue, SDK_SUCCESS, "getPlatform() failed");

	// Display available devices.
	retValue = displayDevices(platform, dType);
	CHECK_ERROR(retValue, SDK_SUCCESS, "displayDevices() failed");
	cl_context_properties cps[3] = {
		CL_CONTEXT_PLATFORM,
		(cl_context_properties)platform,
		0
	};
#else
	cl_context_properties *cps = NULL;
#endif
    /*
    if(g_bRunOnPG)
    {
        std::cout<<"Trying to run on a Processor Graphics \n" << std::endl;
    }
    else
    {
        std::cout<<"Trying to run on a CPU \n" << std::endl;
    }
    */
    // create the OpenCL context on any available OCL device 

    g_context = clCreateContextFromType(cps,
                                    CL_DEVICE_TYPE_ALL,
                                    NULL, NULL, NULL);
    if (g_context == (cl_context)0) 
      return -1; 
 
  
    // get the list of devices associated with context
    err = clGetContextInfo(g_context, CL_CONTEXT_DEVICES, 0, NULL, &cb);
    clGetContextInfo(g_context, CL_CONTEXT_DEVICES, cb, devices, NULL);

    g_cmd_queue = clCreateCommandQueue(g_context, devices[0], 0, NULL);
    if (g_cmd_queue == (cl_command_queue)0)
    {
        Cleanup_OpenCL();
        return -1;
    }
    
    char *sources = 0;

    // runtime compilation
#ifdef WIN32
	SDKFile kernelFile;
	if (!kernelFile.open(program_source))//bool
	{
		std::cout << "Failed to load kernel file: " << std::string(program_source) << std::endl;
		return SDK_FAILURE;
	}
	const char *knSources = kernelFile.source().c_str();
	size_t sourceSize[] = { strlen(knSources) };
	/*sources = ReadSources(program_source);	//read program .cl source file
	if (sources == NULL) {
		status = -1;
		CHECK_ERROR(status, 0, "Failed to open program source file " + std::string(program_source));
		return -1;
	}*/
	
	g_program = clCreateProgramWithSource(g_context, 1, (const char**)&knSources, sourceSize, &status);
	CHECK_OPENCL_ERROR(status, "clCreateProgramWithSource failed.");

    if (g_program == (cl_program)0)
    {
		std::cout << "ERROR: Failed to create Program with source..." << program_source << std::endl;
        Cleanup_OpenCL();
        free(sources);
        return -1;
    }
	/*alternatively us the SDK::buildOpenCL
	cl_program            program;    / **< CL program  * /
	buildProgramData buildData;
	buildData.devices = devices;
	buildData.kernelName = program_source;
	buildData.deviceId = sampleArgs.deviceId;
	buildData.flagsStr = std::string("");
	retValue = buildOpenCLProgram(program, g_context, buildData);
	CHECK_ERROR(retValue, 0, "buildOpenCLProgram() failed");*/

	err = clBuildProgram(g_program, 1, &devices[0], "", NULL, NULL);
	/*
    if (err != CL_SUCCESS)
    {
        std::cout<<"ERROR: Failed to build program...\n"<< std::endl;
        //BuildFailLog(g_program, devices[0]);
        Cleanup_OpenCL();
        free(sources);
        return -1;
    }
*/
	if (err != CL_SUCCESS)
	{
		if (err == CL_BUILD_PROGRAM_FAILURE)
		{
			cl_int logStatus;
			char *buildLog = NULL;
			size_t buildLogSize = 0;
			logStatus = clGetProgramBuildInfo(
				g_program,
				devices[0],
				CL_PROGRAM_BUILD_LOG,
				buildLogSize,
				buildLog,
				&buildLogSize);
			CHECK_OPENCL_ERROR(logStatus, "clGetProgramBuildInfo failed.");
			buildLog = (char*)malloc(buildLogSize);
			CHECK_ALLOCATION(buildLog, "Failed to allocate host memory. (buildLog)");
			memset(buildLog, 0, buildLogSize);
			logStatus = clGetProgramBuildInfo(
				g_program,
				devices[0],
				CL_PROGRAM_BUILD_LOG,
				buildLogSize,
				buildLog,
				NULL);
			if (checkVal(logStatus, CL_SUCCESS, "clGetProgramBuildInfo failed."))
			{
				free(buildLog);
				return SDK_FAILURE;
			}
			std::cout << " \n\t\t\tBUILD LOG\n";
			std::cout << " ************************************************\n";
			std::cout << buildLog << std::endl;
			std::cout << " ************************************************\n";
			free(buildLog);
		}
		CHECK_OPENCL_ERROR(status, "clBuildProgram failed.");
	}
#else
    // offline compilation
    // create the program
    size_t binsz = sizeof(int32_t*);
    void * pos  = (void *)&program_bin;
    g_program = clCreateProgramWithBinary(g_context, 1, &devices[0],
	    &binsz, (const unsigned char**)&pos, NULL, NULL);
    if (g_program == (cl_program)0) 
    { 
        Cleanup_OpenCL();
        return -1;
    } 
 
    // build the program 
    err = clBuildProgram(g_program, 0, NULL, NULL, NULL, NULL); 
    if (err != CL_SUCCESS) 
    { 
        Cleanup_OpenCL();
        return -1;
    } 

#endif
    g_kernel_regular = clCreateKernel(g_program, "MedianFilterBitonic", NULL);
    if (g_kernel_regular == (cl_kernel)0)
    {
        std::cout<<"ERROR: Failed to create kernel...\n" << std::endl;
		  
        Cleanup_OpenCL();
        if(sources) free(sources);
        return -1;
    }

	/*
    g_kernel_async = clCreateKernel(g_program, "MedianFilterBitonicAsync", NULL);
    if (g_kernel_async == (cl_kernel)0)
    {
        std::cout<<"ERROR: Failed to create kernel...\n" << std::endl;
		  
        Cleanup_OpenCL();
        if(sources) free(sources);
        return -1;
    }    if(sources) free(sources);

    g_kernel_async2d = clCreateKernel(g_program, "MedianFilterBitonicAsync2D", NULL);
    if (g_kernel_async2d == (cl_kernel)0)
    {
        std::cout<<"ERROR: Failed to create kernel...\n" << std::endl;
		  
        Cleanup_OpenCL();
        if(sources) free(sources);
        return -1;
    }    if(sources) free(sources);
	*/
    // retrieve device information

    // use first device ID
    device_ID = devices[0];

    err = clGetDeviceInfo(device_ID, CL_DEVICE_NAME, 128, device_name, NULL);
    if (err!=CL_SUCCESS)
    {
        std::cout<<"ERROR: Failed to get device information (device name)...\n" << std::endl;		  
        Cleanup_OpenCL();
        return -1;
    }
	 //std::cout<<"Using device %s...\n" << std::endl;		  

    err = clGetDeviceInfo(device_ID, CL_DEVICE_MAX_COMPUTE_UNITS, sizeof(cl_uint), &num_cores, NULL);
    if (err!=CL_SUCCESS)
    {
		  std::cout<<"ERROR: Failed to get device information (max compute units)...\n" << std::endl;		  
        Cleanup_OpenCL();
        return -1;
    }
	 //std::cout<<"Using %d compute units...\n" << std::endl;		  


    err = clGetDeviceInfo(device_ID, CL_DEVICE_MEM_BASE_ADDR_ALIGN, sizeof(cl_uint), &g_min_align, NULL);
    if (err!=CL_SUCCESS)
    {
        std::cout<<"ERROR: Failed to get device information (max memory base address align size)...\n"<< std::endl;
        Cleanup_OpenCL();
        return -1;
    }
    g_min_align /= 8; //in bytes
	 //std::cout<<"Expected min alignment for buffers is %d bytes...\n" << std::endl;


    return 0; // success...
}

void generateInput(cl_uint* inputArray, size_t arrayWidth, size_t arrayHeight)
{

    srand(12345);

    // random initialization of input
    for (cl_uint i = 0; i <  arrayWidth * (arrayHeight+4); ++i)
    {
        inputArray[i] = (rand() | (rand()<<15) ) & 0xFFFFFF;
    }
}

//inline functions for reference kernel
typedef unsigned char (uchar4)[4];

#ifndef max
#define max(a,b)            (((a) > (b)) ? (a) : (b))
#endif

#ifndef min
#define min(a,b)            (((a) < (b)) ? (a) : (b))
#endif

inline unsigned c4max(const unsigned& l, const unsigned& r)
{
    unsigned ur;
    unsigned char* res = (unsigned char*)&ur;
    unsigned char* left = (unsigned char*)&l;
    unsigned char* right = (unsigned char*)&r;

    res[0] = max(left[0],right[0]);
    res[1] = max(left[1],right[1]);
    res[2] = max(left[2],right[2]);
    res[3] = max(left[3],right[3]);

    return ur;
}

inline unsigned c4min(const unsigned& l, const unsigned& r)
{
    unsigned ur;
    unsigned char* res = (unsigned char*)&ur;
    unsigned char* left = (unsigned char*)&l;
    unsigned char* right = (unsigned char*)&r;

    res[0] = min(left[0],right[0]);
    res[1] = min(left[1],right[1]);
    res[2] = min(left[2],right[2]);
    res[3] = min(left[3],right[3]);

    return ur;
}


void ExecuteMedianFilterReference(cl_uint* inputArray, cl_uint* outputArray, cl_int arrayWidth, cl_uint arrayHeight)
{
    memset(outputArray, 0,   arrayWidth * (arrayHeight+4));

    // do the Median 
    for(cl_uint y = 0; y < arrayHeight; y++)		// rows loop
    {
        int iOffset = (y+2) * arrayWidth;
        int iPrev = iOffset - arrayWidth;
        int iNext = iOffset + arrayWidth;

        for(int x = 0; x < arrayWidth; x++)		// columns loop
        {

			unsigned uiRGBA[9];	
            //get pixels within aperture
            uiRGBA[0] = inputArray[iPrev + x - 1];
            uiRGBA[1] = inputArray[iPrev + x];
            uiRGBA[2] = inputArray[iPrev + x + 1];

            uiRGBA[3] = inputArray[iOffset + x - 1];
            uiRGBA[4] = inputArray[iOffset + x];
            uiRGBA[5] = inputArray[iOffset + x + 1];

            uiRGBA[6] = inputArray[iNext + x - 1];
            uiRGBA[7] = inputArray[iNext + x];
            uiRGBA[8] = inputArray[iNext + x + 1];

            unsigned uiMin = c4min(uiRGBA[0], uiRGBA[1]);
            unsigned uiMax = c4max(uiRGBA[0], uiRGBA[1]);
            uiRGBA[0] = uiMin;
            uiRGBA[1] = uiMax;

            uiMin = c4min(uiRGBA[3], uiRGBA[2]);
            uiMax = c4max(uiRGBA[3], uiRGBA[2]);
            uiRGBA[3] = uiMin;
            uiRGBA[2] = uiMax;

            uiMin = c4min(uiRGBA[2], uiRGBA[0]);
            uiMax = c4max(uiRGBA[2], uiRGBA[0]);
            uiRGBA[2] = uiMin;
            uiRGBA[0] = uiMax;

            uiMin = c4min(uiRGBA[3], uiRGBA[1]);
            uiMax = c4max(uiRGBA[3], uiRGBA[1]);
            uiRGBA[3] = uiMin;
            uiRGBA[1] = uiMax;

            uiMin = c4min(uiRGBA[1], uiRGBA[0]);
            uiMax = c4max(uiRGBA[1], uiRGBA[0]);
            uiRGBA[1] = uiMin;
            uiRGBA[0] = uiMax;

            uiMin = c4min(uiRGBA[3], uiRGBA[2]);
            uiMax = c4max(uiRGBA[3], uiRGBA[2]);
            uiRGBA[3] = uiMin;
            uiRGBA[2] = uiMax;

            uiMin = c4min(uiRGBA[5], uiRGBA[4]);
            uiMax = c4max(uiRGBA[5], uiRGBA[4]);
            uiRGBA[5] = uiMin;
            uiRGBA[4] = uiMax;

            uiMin = c4min(uiRGBA[7], uiRGBA[8]);
            uiMax = c4max(uiRGBA[7], uiRGBA[8]);
            uiRGBA[7] = uiMin;
            uiRGBA[8] = uiMax;

            uiMin = c4min(uiRGBA[6], uiRGBA[8]);
            uiMax = c4max(uiRGBA[6], uiRGBA[8]);
            uiRGBA[6] = uiMin;
            uiRGBA[8] = uiMax;

            uiMin = c4min(uiRGBA[6], uiRGBA[7]);
            uiMax = c4max(uiRGBA[6], uiRGBA[7]);
            uiRGBA[6] = uiMin;
            uiRGBA[7] = uiMax;

            uiMin = c4min(uiRGBA[4], uiRGBA[8]);
            uiMax = c4max(uiRGBA[4], uiRGBA[8]);
            uiRGBA[4] = uiMin;
            uiRGBA[8] = uiMax;

            uiMin = c4min(uiRGBA[4], uiRGBA[6]);
            uiMax = c4max(uiRGBA[4], uiRGBA[6]);
            uiRGBA[4] = uiMin;
            uiRGBA[6] = uiMax;

            uiMin = c4min(uiRGBA[5], uiRGBA[7]);
            uiMax = c4max(uiRGBA[5], uiRGBA[7]);
            uiRGBA[5] = uiMin;
            uiRGBA[7] = uiMax;

            uiMin = c4min(uiRGBA[4], uiRGBA[5]);
            uiMax = c4max(uiRGBA[4], uiRGBA[5]);
            uiRGBA[4] = uiMin;
            uiRGBA[5] = uiMax;

            uiMin = c4min(uiRGBA[6], uiRGBA[7]);
            uiMax = c4max(uiRGBA[6], uiRGBA[7]);
            uiRGBA[6] = uiMin;
            uiRGBA[7] = uiMax;

            uiMin = c4min(uiRGBA[0], uiRGBA[8]);
            uiMax = c4max(uiRGBA[0], uiRGBA[8]);
            uiRGBA[0] = uiMin;
            uiRGBA[8] = uiMax;

            uiRGBA[4] = c4max(uiRGBA[0], uiRGBA[4]);
            uiRGBA[5] = c4max(uiRGBA[1], uiRGBA[5]);

            uiRGBA[6] = c4max(uiRGBA[2], uiRGBA[6]);
            uiRGBA[7] = c4max(uiRGBA[3], uiRGBA[7]);

            uiRGBA[4] = c4min(uiRGBA[4], uiRGBA[6]);
            uiRGBA[5] = c4min(uiRGBA[5], uiRGBA[7]);

            // convert and copy to output
            outputArray[(y+2) * arrayWidth + x] = c4min(uiRGBA[4], uiRGBA[5]);
        }
    } 
}

bool ExecuteMedianFilterKernel(cl_uint* inputArray, cl_uint* outputArray, cl_int arrayWidth, cl_uint arrayHeight)
{
    cl_int err = CL_SUCCESS;

    // allocate the buffer with some padding (to avoid boundaries checking)
    g_inputBuffer_regular = clCreateBuffer(g_context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, sizeof(cl_uint) * arrayWidth * (arrayHeight+4), inputArray, NULL);

    if (g_inputBuffer_regular == (cl_mem)0)
    {
        std::cout<<"ERROR: Failed to create Input Buffer...\n"<< std::endl;
		  
        return false;
    }

    // allocate the buffer with some padding (to avoid boundaries checking)
    g_outputBuffer_regular = clCreateBuffer(g_context, CL_MEM_WRITE_ONLY | CL_MEM_COPY_HOST_PTR, sizeof(cl_uint) * arrayWidth * (arrayHeight+4), outputArray, NULL);

    if (g_outputBuffer_regular == (cl_mem)0)
    {
        std::cout<<"ERROR: Failed to create Output Buffer...\n"<< std::endl;
        return false;
    }


    err  =  clSetKernelArg(g_kernel_regular, 0, sizeof(cl_mem), (void *) &g_inputBuffer_regular);
    err  |= clSetKernelArg(g_kernel_regular, 1, sizeof(cl_mem), (void *) &g_outputBuffer_regular);
    if (err != CL_SUCCESS)
    {
        std::cout<<"ERROR: Failed to set input g_kernel_regular arguments...\n"<< std::endl;
        return false;
    }



	 size_t global_work_size[2] = { (size_t)arrayWidth, (size_t)arrayHeight};
    size_t local_work_size[2]= { LOCAL_SIZE_X, LOCAL_SIZE_Y};					
	 size_t offset[2]= { 0, 2};					

    // execute kernel
    if (CL_SUCCESS != (err = clEnqueueNDRangeKernel(g_cmd_queue, g_kernel_regular, 2, offset, global_work_size, local_work_size, 0, NULL, NULL)))
    {
        std::cout<<"ERROR: Failed to run kernel...\n"<< std::endl;
        return false;
    }
    err = clFinish(g_cmd_queue);

     // read output image 
    err = clEnqueueReadBuffer(g_cmd_queue, g_outputBuffer_regular, CL_TRUE, 
             0, sizeof(cl_uint) * arrayWidth * (arrayHeight+4), outputArray,
             0, NULL, NULL);
    err = clFinish(g_cmd_queue);

    clReleaseMemObject(g_inputBuffer_regular); g_inputBuffer_regular = NULL;
    clReleaseMemObject(g_outputBuffer_regular); g_outputBuffer_regular = NULL;

    return true;
}

bool ExecuteMedianFilterAsyncKernel(cl_uint* inputArray, cl_uint* outputArray, cl_int arrayWidth, cl_uint arrayHeight)
{
    cl_int err = CL_SUCCESS;

    // allocate the buffer with some padding (to avoid boundaries checking)
    g_inputBuffer_async = clCreateBuffer(g_context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, sizeof(cl_uint) * arrayWidth * (arrayHeight+4), inputArray, NULL);

    if (g_inputBuffer_async == (cl_mem)0)
    {
        std::cout<<"ERROR: Failed to create Input Buffer...\n"<< std::endl;
		  
        return false;
    }

    // allocate the buffer with some padding (to avoid boundaries checking)
    g_outputBuffer_async = clCreateBuffer(g_context, CL_MEM_WRITE_ONLY | CL_MEM_COPY_HOST_PTR, sizeof(cl_uint) * arrayWidth * (arrayHeight+4), outputArray, NULL);

    if (g_outputBuffer_async == (cl_mem)0)
    {
        std::cout<<"ERROR: Failed to create Output Buffer...\n"<< std::endl;
        return false;
    }

	
    err  =  clSetKernelArg(g_kernel_async, 0, sizeof(cl_mem), (void *) &g_inputBuffer_async);
    err  |= clSetKernelArg(g_kernel_async, 1, sizeof(cl_mem), (void *) &g_outputBuffer_async);
    if (err != CL_SUCCESS)
    {
        std::cout<<"ERROR: Failed to set input g_kernel_async arguments...\n"<< std::endl;
        return false;
    }



	size_t global_work_size[2] = { (size_t)arrayWidth, (size_t)arrayHeight};
	size_t local_work_size[2]= { LOCAL_SIZE_X, LOCAL_SIZE_Y};					
	size_t offset[2]= { 0, 2};					

    // execute kernel
    if (CL_SUCCESS != (err = clEnqueueNDRangeKernel(g_cmd_queue, g_kernel_async, 2, offset, global_work_size, local_work_size, 0, NULL, NULL)))
    {
        std::cout<<"ERROR: Failed to run kernel...\n"<< std::endl;
        return false;
    }
	
    err = clFinish(g_cmd_queue);


     // read output image 
    err = clEnqueueReadBuffer(g_cmd_queue, g_outputBuffer_async, CL_TRUE, 
             0, sizeof(cl_uint) * arrayWidth * (arrayHeight+4), outputArray,
             0, NULL, NULL);
    err = clFinish(g_cmd_queue);

    clReleaseMemObject(g_inputBuffer_async); g_inputBuffer_async = NULL;
    clReleaseMemObject(g_outputBuffer_async); g_outputBuffer_async = NULL;

    return true;
}


bool ExecuteMedianFilterAsync2DKernel(cl_uint* inputArray, cl_uint* outputArray, cl_int arrayWidth, cl_uint arrayHeight)
{
    cl_int err = CL_SUCCESS;

    // allocate the buffer with some padding (to avoid boundaries checking)
    g_inputBuffer_async2d = clCreateBuffer(g_context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, sizeof(cl_uint) * arrayWidth * (arrayHeight+4), inputArray, NULL);

    if (g_inputBuffer_async2d == (cl_mem)0)
    {
        std::cout<<"ERROR: Failed to create Input Buffer...\n"<< std::endl;
		  
        return false;
    }

    // allocate the buffer with some padding (to avoid boundaries checking)
    g_outputBuffer_async2d = clCreateBuffer(g_context, CL_MEM_WRITE_ONLY | CL_MEM_COPY_HOST_PTR, sizeof(cl_uint) * arrayWidth * (arrayHeight+4), outputArray, NULL);

    if (g_outputBuffer_async2d == (cl_mem)0)
    {
        std::cout<<"ERROR: Failed to create Output Buffer...\n"<< std::endl;
        return false;
    }


    err  =  clSetKernelArg(g_kernel_async2d, 0, sizeof(cl_mem), (void *) &g_inputBuffer_async2d);
    err  |= clSetKernelArg(g_kernel_async2d, 1, sizeof(cl_mem), (void *) &g_outputBuffer_async2d);
    if (err != CL_SUCCESS)
    {
        std::cout<<"ERROR: Failed to set input g_kernel_async arguments...\n"<< std::endl;
        return false;
    }



	size_t global_work_size[2] = { (size_t)arrayWidth, (size_t)arrayHeight};
	size_t local_work_size[2]= { LOCAL_SIZE_X, LOCAL_SIZE_Y};					
	size_t offset[2]= { 0, 2};					

    // execute kernel
    if (CL_SUCCESS != (err = clEnqueueNDRangeKernel(g_cmd_queue, g_kernel_async2d, 2, offset, global_work_size, local_work_size, 0, NULL, NULL)))
    {
        std::cout<<"ERROR: Failed to run kernel...\n"<< std::endl;
        return false;
    }

    err = clFinish(g_cmd_queue);

     // read output image 
    err = clEnqueueReadBuffer(g_cmd_queue, g_outputBuffer_async2d, CL_TRUE, 
             0, sizeof(cl_uint) * arrayWidth * (arrayHeight+4), outputArray,
             0, NULL, NULL);
    err = clFinish(g_cmd_queue);

    clReleaseMemObject(g_inputBuffer_async2d); g_inputBuffer_async2d = NULL;
    clReleaseMemObject(g_outputBuffer_async2d); g_outputBuffer_async2d = NULL;

    return true;
}


void Usage()
{
    std::cout<<"Usage: MedianFilter.exe [--h] [-h <height>] [-w <width>] [-g]\n"<< std::endl;
    std::cout<<"  where, --h prints this message\n"<< std::endl;
    std::cout<<"    <height> and <width> are input dimensions\n"<< std::endl;
    std::cout<<"    -g run on Processor Graphics\n"<< std::endl;
    exit(-1);
}

// main execution routine - performs median filtering with 3x3 kernel size
int MedianFilter_main()
{
    cl_int arrayWidth  = 512;
    cl_int arrayHeight = 256;

    std::cout << "\t.............MedianFilter Test............." << std::endl; 

    //validate user input parameters
    {
        if( arrayWidth < 4 || arrayHeight < 4 || arrayWidth > 8192 || arrayHeight > 8192 )
        {
            std::cout<<"Input size in each dimension should be in the range [4, 8192]!\n"<< std::endl;
            return -1;
        }

        cl_uint _logb = 0;

        for (int temp = arrayWidth; temp>1; temp >>= 1)
            _logb++;

        if( arrayWidth & ((1 << _logb)-1)  )
        {
            std::cout<<"Input size should be (2^N)!\n"<< std::endl;
            return -1;
        }

        _logb = 0;

        for (int temp = arrayHeight; temp>1; temp >>= 1)
            _logb++;

        if( arrayHeight & ((1 << _logb)-1)  )
        {
            std::cout<<"Input size should be (2^N)!\n"<< std::endl;
            return -1;
        }

    }

#ifndef WIN32
    //initialize Open CL objects (context, queue, etc.)
    if( 0 != Setup_OpenCL("MedianFilter.cl", (const int32_t*)APU_OCL_LOAD_SEGMENTS))
        return -1;
#else
	if (0 != Setup_OpenCL("../../../../kernels/cl/unsorted_kernels/src/MedianFilter.cl", NULL))
		return -1;
#endif

    //std::cout<<"Input size is" << arrayWidth << "x" << arrayHeight << std::endl;	 

    // allocate buffers with some padding (to avoid boundaries checking)
    cl_uint* inputArray = (cl_uint*)malloc(sizeof(cl_uint) * arrayWidth * (arrayHeight+4));
    cl_uint* outputArray_regular = (cl_uint*)malloc(sizeof(cl_uint) * arrayWidth * (arrayHeight+4));
    cl_uint* outputArray_async = (cl_uint*)malloc(sizeof(cl_uint) * arrayWidth * (arrayHeight+4));
    cl_uint* outputArray_async2d = (cl_uint*)malloc(sizeof(cl_uint) * arrayWidth * (arrayHeight+4));
    cl_uint* refArray = (cl_uint*)malloc(sizeof(cl_uint) * arrayWidth * (arrayHeight+4));

    //random input
    generateInput(inputArray, arrayWidth, arrayHeight);

    //median filtering
    std::cout<<"Executing OpenCL kernel...without async_work_goup_copy\n" << std::endl;
    ExecuteMedianFilterKernel(inputArray, outputArray_regular, arrayWidth, arrayHeight);
	
    //std::cout<<"Executing OpenCL kernel...with async_work_group_copy\n" << std::endl;
   // ExecuteMedianFilterAsyncKernel(inputArray, outputArray_async, arrayWidth, arrayHeight);
	
    //std::cout<<"Executing OpenCL kernel...with 2D async_work_group_copy\n" << std::endl;
   // ExecuteMedianFilterAsync2DKernel(inputArray, outputArray_async2d, arrayWidth, arrayHeight);

    std::cout<<"Executing reference...\n" << std::endl;
    ExecuteMedianFilterReference(inputArray, refArray, arrayWidth, arrayHeight);

    std::cout<<"Performing verification...without async_work_group_copy\n" << std::endl;
    bool result = true;
    for(cl_uint y = 0; y < (cl_uint)arrayHeight; y++)		// rows loop
    {
        for(cl_uint x = 0; x < (cl_uint)arrayWidth; x++)		// columns loop
        {
            unsigned int REF = (refArray+2*arrayWidth)[y * arrayWidth + x] & 0xFFFFFF;
            unsigned int RES = (outputArray_regular+2*arrayWidth)[y * arrayWidth + x] & 0xFFFFFF;

            if((abs((int)(REF & 0xFF)- (int)(RES & 0xFF))>1)||(abs((int)(REF & 0xFF00)- (int)(RES & 0xFF00))>1)||(abs((int)(REF & 0xFF0000)- (int)(RES & 0xFF0000))>1))
            {

                std::cout<<"y = "<<std::dec<<y<< 
                           " x ="<<std::dec<<x<< 
                           " REF = "<<std::hex<<(REF & 0xFF)<<" "<<
                           std::hex<<((REF & 0xFF00) >> 8)<<" "<<
                           std::hex<<((REF & 0xFF0000) >> 16)<<" "<<
                           "RES = "<<" "<<std::hex<<(RES & 0xFF)<<" "<<
                           std::hex<<((RES & 0xFF00) >> 8)<<" "<<
                           std::hex<<((RES & 0xFF0000) >> 16)
                           <<std::endl;

					 
                result = false;
            }
        }           
    }
    if(!result)
    {
        std::cout<<"Failed\n" << std::endl;
    }
    else
    {
        std::cout<<"Passed!\n" << std::endl;
    }

	/*
    std::cout<<"Performing verification...with async_work_group_copy\n" << std::endl;
    result = true;
    for(cl_uint y = 0; y < (cl_uint)arrayHeight; y++)		// rows loop
    {
        for(cl_uint x = 0; x < (cl_uint)arrayWidth; x++)		// columns loop
        {
            unsigned int REF = (refArray+2*arrayWidth)[y * arrayWidth + x] & 0xFFFFFF;
            unsigned int RES = (outputArray_async+2*arrayWidth)[y * arrayWidth + x] & 0xFFFFFF;

            if((abs((int)(REF & 0xFF)- (int)(RES & 0xFF))>1)||(abs((int)(REF & 0xFF00)- (int)(RES & 0xFF00))>1)||(abs((int)(REF & 0xFF0000)- (int)(RES & 0xFF0000))>1))
            {

                std::cout<<"y = "<<std::dec<<y<< 
                           " x ="<<std::dec<<x<< 
                           " REF = "<<std::hex<<(REF & 0xFF)<<" "<<
                           std::hex<<((REF & 0xFF00) >> 8)<<" "<<
                           std::hex<<((REF & 0xFF0000) >> 16)<<" "<<
                           "RES = "<<" "<<std::hex<<(RES & 0xFF)<<" "<<
                           std::hex<<((RES & 0xFF00) >> 8)<<" "<<
                           std::hex<<((RES & 0xFF0000) >> 16)
                           <<std::endl;

					 
                result = false;
            }
        }           
    }
    if(!result)
    {
        std::cout<<"Failed\n" << std::endl;
    }
    else
    {
        std::cout<<"Passed!\n" << std::endl;
    }

    std::cout<<"Performing verification...with 2D async_work_group_copy\n" << std::endl;
    result = true;
    for(cl_uint y = 0; y < (cl_uint)arrayHeight; y++)		// rows loop
    {
        for(cl_uint x = 0; x < (cl_uint)arrayWidth; x++)		// columns loop
        {
            unsigned int REF = (refArray+2*arrayWidth)[y * arrayWidth + x] & 0xFFFFFF;
            unsigned int RES = (outputArray_async2d+2*arrayWidth)[y * arrayWidth + x] & 0xFFFFFF;

            if((abs((int)(REF & 0xFF)- (int)(RES & 0xFF))>1)||(abs((int)(REF & 0xFF00)- (int)(RES & 0xFF00))>1)||(abs((int)(REF & 0xFF0000)- (int)(RES & 0xFF0000))>1))
            {

                std::cout<<"y = "<<std::dec<<y<< 
                           " x ="<<std::dec<<x<< 
                           " REF = "<<std::hex<<(REF & 0xFF)<<" "<<
                           std::hex<<((REF & 0xFF00) >> 8)<<" "<<
                           std::hex<<((REF & 0xFF0000) >> 16)<<" "<<
                           "RES = "<<" "<<std::hex<<(RES & 0xFF)<<" "<<
                           std::hex<<((RES & 0xFF00) >> 8)<<" "<<
                           std::hex<<((RES & 0xFF0000) >> 16)
                           <<std::endl;

					 
                result = false;
            }
        }           
    }
    if(!result)
    {
        std::cout<<"Failed\n" << std::endl;
    }
    else
    {
        std::cout<<"Passed!\n" << std::endl;
    }
	*/


    free( refArray );
    free( inputArray );
    free( outputArray_regular );
    free( outputArray_async );
    free( outputArray_async2d );
    
    Cleanup_OpenCL();
    	 
    if(!result)
    {
        return -1;
    }
    else
    {
        return 0;
    }
}

