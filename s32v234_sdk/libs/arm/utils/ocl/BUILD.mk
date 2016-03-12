##############################################################################
#
# Freescale Confidential Proprietary
#
# Copyright (c) 2014 Freescale Semiconductor;
# All Rights Reserved
#
##############################################################################
#
# THIS SOFTWARE IS PROVIDED BY FREESCALE "AS IS" AND ANY EXPRESSED OR
# IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
# OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
# IN NO EVENT SHALL FREESCALE OR ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
# INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
# (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
# SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
# HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
# STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
# IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
# THE POSSIBILITY OF SUCH DAMAGE.
#
##############################################################################
#
#  CONTENT
#    ACF2 Host lib
#
#  AUTHOR
#    Stefan Schwarz
#
#  DATE
#    2013-07-17
#
#  LANGUAGE
#    make
#
##############################################################################

SDK_ROOT := ../../../../../../s32v234_sdk

ARM_LIB = libocl.a

##############################################################################
# libacf2host.a
##############################################################################

VPATH += ../src
VPATH += ../src/devices

ARM_LIB_SRCS +=                                                              \
    bufalloc.c                                                               \
    cpuinfo.c                                                                \
    devices.c                                                                \
    clBuildProgram.c                                                         \
    clCreateBuffer.c                                                         \
    clCreateCommandQueue.c                                                   \
    clCreateContext.c                                                        \
    clCreateContextFromType.c                                                \
    clCreateFromGLTexture2D.c                                                \
    clCreateFromGLTexture3D.c                                                \
    clCreateImage.c                                                          \
    clCreateImage2D.c                                                        \
    clCreateImage3D.c                                                        \
    clCreateKernel.c                                                         \
    clCreateKernelsInProgram.c                                               \
    clCreateProgramWithBinary.c                                              \
    clCreateProgramWithSource.c                                              \
    clCreateSampler.c                                                        \
    clCreateSubBuffer.c                                                      \
    clCreateUserEvent.c                                                      \
    clEnqueueBarrier.c                                                       \
    clEnqueueCopyBuffer.c                                                    \
    clEnqueueCopyBufferRect.c                                                \
    clEnqueueCopyBufferToImage.c                                             \
    clEnqueueCopyImage.c                                                     \
    clEnqueueCopyImageToBuffer.c                                             \
    clEnqueueFillImage.c                                                     \
    clEnqueueMapBuffer.c                                                     \
    clEnqueueMapBuffer.h                                                     \
    clEnqueueMapImage.c                                                      \
    clEnqueueMarker.c                                                        \
    clEnqueueMarkerWithWaitList.c                                            \
    clEnqueueNativeKernel.c                                                  \
    clEnqueueNDRangeKernel.c                                                 \
    clEnqueueReadBuffer.c                                                    \
    clEnqueueReadBufferRect.c                                                \
    clEnqueueReadImage.c                                                     \
    clEnqueueTask.c                                                          \
    clEnqueueUnmapMemObject.c                                                \
    clEnqueueWaitForEvents.c                                                 \
    clEnqueueWriteBuffer.c                                                   \
    clEnqueueWriteBufferRect.c                                               \
    clEnqueueWriteImage.c                                                    \
    clFinish.c                                                               \
    clFlush.c                                                                \
    clGetCommandQueueInfo.c                                                  \
    clGetContextInfo.c                                                       \
    clGetDeviceIDs.c                                                         \
    clGetDeviceInfo.c                                                        \
    clGetEventInfo.c                                                         \
    clGetEventProfilingInfo.c                                                \
    clGetExtensionFunctionAddress.c                                          \
    clGetImageInfo.c                                                         \
    clGetKernelInfo.c                                                        \
    clGetKernelArgInfo.c                                                     \
    clGetKernelWorkGroupInfo.c                                               \
    clGetMemObjectInfo.c                                                     \
    clGetPlatformIDs.c                                                       \
    clGetPlatformInfo.c                                                      \
    clGetProgramBuildInfo.c                                                  \
    clGetProgramInfo.c                                                       \
    clGetSamplerInfo.c                                                       \
    clGetSupportedImageFormats.c                                             \
    clIcdGetPlatformIDsKHR.c                                                 \
    clReleaseCommandQueue.c                                                  \
    clReleaseContext.c                                                       \
    clReleaseDevice.c                                                        \
    clReleaseEvent.c                                                         \
    clReleaseKernel.c                                                        \
    clReleaseMemObject.c                                                     \
    clReleaseProgram.c                                                       \
    clReleaseSampler.c                                                       \
    clRetainCommandQueue.c                                                   \
    clRetainContext.c                                                        \
    clRetainDevice.c                                                         \
    clRetainEvent.c                                                          \
    clRetainKernel.c                                                         \
    clRetainMemObject.c                                                      \
    clRetainProgram.c                                                        \
    clRetainSampler.c                                                        \
    clSetEventCallback.c                                                     \
    clSetKernelArg.c                                                         \
    clSetMemObjectDestructorCallback.c                                       \
    clSetUserEventStatus.c                                                   \
    clUnloadCompiler.c                                                       \
    clWaitForEvents.c                                                        \
    pocl_image_util.c                                                        \
    pocl_mem_management.c                                                    \
    pocl_runtime_config.c                                                    \
    pocl_util.c                                                              \
    poclu_bswap.c
    
ARM_CCOPTS +=                                                                \
    -include stdlib.h                                                        \
    -w
	
ifneq (,$(findstring -integrity-d,$(ODIR)))
	ARM_CCOPTS += -gcc
endif

ARM_INCS +=                                                                  \
    -I$(SDK_ROOT)/libs/arm/utils/ocl/include                                 \
    -I$(SDK_ROOT)/libs/arm/utils/ocl/include/CL                              \
    -I$(SDK_ROOT)/libs/arm/utils/ocl/include/devices                         \
    -I$(SDK_ROOT)/libs/arm/utils/oal/user/include/

##############################################################################
