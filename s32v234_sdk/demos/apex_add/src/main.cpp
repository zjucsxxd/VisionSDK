/*****************************************************************************
*
* Freescale Confidential Proprietary
*
* Copyright (c) 2014 Freescale Semiconductor;
* All Rights Reserved
*
*****************************************************************************
*
* THIS SOFTWARE IS PROVIDED BY FREESCALE "AS IS" AND ANY EXPRESSED OR
* IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
* OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
* IN NO EVENT SHALL FREESCALE OR ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
* INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
* (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
* SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
* HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
* STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
* IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
* THE POSSIBILITY OF SUCH DAMAGE.
*
****************************************************************************/

/****************************************************************************
* Includes
****************************************************************************/

#ifdef APEX2_EMULATE 
  #include <tchar.h>
  #include "apu_lib.hpp"
  #include "apu_extras.hpp"
  #include "acf_lib.hpp"
  using namespace APEX2;
#else
  #include <icp_data.h>
  using namespace icp;
  #include <stdio.h>
  #include <iostream>
  #include <fstream>
  #include <iomanip>
  #include "apex.h"
  #include <oal.h>
#endif

#include <string.h>
#include "time_measure.h"

using namespace std;
#include "stringify_macros.h"
#include "apu_add_process.h"

#ifdef APEX2_EMULATE
  const int TILE_SIZE_X = 8;
  const int TILE_SIZE_Y = 8;
#endif

/****************************************************************************
* Function declarations
****************************************************************************/
int pixel_a1_ref(DataDescriptor& lInput0, DataDescriptor& lInput1, DataDescriptor& lOutput0);


/****************************************************************************
* Main function
****************************************************************************/
#ifdef APEX2_EMULATE
int _tmain(int argc, _TCHAR* argv[])
#else
int main(int, char**)
#endif
{
  // This is needed only for the Target Compiler
  // HW and resources init
#ifndef APEX2_EMULATE 
#ifndef __STANDALONE__
  OAL_MemoryAllocInit();
#endif
 	ACF_Init();
#endif

  int lSrcWidth = 256;
  int lSrcHeight = 256;

  #ifndef USE_OPENCV
    unsigned int dimElemX = 1, dimElemY = 1, imgDepth = 2; // define a volume with two image layers

    DataDescriptor lInput0(lSrcWidth, lSrcHeight, DATATYPE_08U);
    DataDescriptor lInput1(lSrcWidth, lSrcHeight, DATATYPE_08U);
  #endif

  DataDescriptor lOutput0_REF(lSrcWidth, lSrcHeight, DATATYPE_16U, lInput0.GetElementDimX(), lInput0.GetElementDimY(), lInput0.GetDimensions());

  #ifdef DEF_TIME_MEASURE 
    // to be called, if the run time has to be measured
    int64_t ticks0 = FSL_Ticks();
  #endif

  int lRetVal = 0;
  
  // Configure two processes which shall run in parallel, each on one of the two APEX devices.
  CTemplate_Demo_Proc addProcess0(0);
  CTemplate_Demo_Proc addProcess1(1);
  lRetVal |= addProcess0.InitData(&lInput0, &lInput1);
  lRetVal |= addProcess1.InitData(&lInput0, &lInput1);

  DataDescriptor* lOutput0_ACF1 = &addProcess0.lOutput;
  DataDescriptor* lOutput0_ACF2 = &addProcess1.lOutput;

  printf("Data on: \n");
  printf("   Input 1           (%dx%d bytes) at %p\n", lSrcWidth, lSrcHeight, lInput0.GetDataPtrPhys());
  printf("   Input 2           (%dx%d bytes) at %p\n", lSrcWidth, lSrcHeight, lInput1.GetDataPtrPhys());
  printf("   Output APEX 1     (%dx%d words) at %p\n", lSrcWidth, lSrcHeight, lOutput0_ACF1->GetDataPtrPhys());
  printf("   Output APEX 2     (%dx%d words) at %p\n", lSrcWidth, lSrcHeight, lOutput0_ACF2->GetDataPtrPhys());

  if (lRetVal)
   return lRetVal;
    
  printf("Initialize APEX process n. 1.\n");
  lRetVal |= addProcess0.Connect();

  printf("Initialize APEX process n. 2.\n");
  lRetVal |= addProcess1.Connect();

  if (lRetVal) 
    return lRetVal;
 
  if (lInput0.IsOK() != 0 && lInput1.IsOK() != 0 && lOutput0_ACF1->IsOK() && lOutput0_ACF2->IsOK())
  {
    for (unsigned int i = 0; i < 5; ++i)
    {
      printf("Iteration %d\n", i);
      printf("=======================================\n");

      printf("Input random seed.\n");
      lInput0.FillRandom(1);
      lInput1.FillRandom(15);

      printf("Compute reference value via SW.\n");
      lRetVal |= pixel_a1_ref(lInput0, lInput1, lOutput0_REF);

      printf("Start both APEXes.\n");
      lRetVal |= addProcess0.Start();
      lRetVal |= addProcess1.Start();

      printf("Wait for both done.\n");
      lRetVal |= addProcess0.Wait();
      lRetVal |= addProcess1.Wait();

      if (lRetVal)
        return lRetVal;
      
	  printf("Comparison: ");
      if (0 == lRetVal)
	  {
	    if (lOutput0_REF == *lOutput0_ACF1 && lOutput0_REF == *lOutput0_ACF2)
	      lRetVal = 0;
		else
		  lRetVal += 1;
	  }

      if (0 == lRetVal) 
	    printf("All three outputs match.\n\n");
	  else 
	  {
		printf("Data do not match.\n\n");
        return lRetVal;
	  }
	}
  } 
  else
  {
	lRetVal = 1;
  }

  #ifdef DEF_TIME_MEASURE
    int64_t ticks1 = FSL_Ticks();
    int64_t cpu_ticks = ticks1 - ticks0;
    int64_t apex_ticks = total_apex_ticks;
    int64_t data_load_ticks = total_load_ticks;
    int64_t arm_ticks = cpu_ticks - apex_ticks - data_load_ticks;
    double armTimeInSecs = FSL_TicksToSeconds(arm_ticks);
    double dataLoadTimeInSecs = FSL_TicksToSeconds(data_load_ticks);
    double apexTimeInSecs = FSL_TicksToSeconds(apex_ticks);
    double cpuTimeInSecs = FSL_TicksToSeconds(cpu_ticks);

    printf("\n___________________________________________________\n"
           "Processes took %f sec on APEX, %f sec on ARM, %f sec for data loading and %f sec in total"
		   "\n___________________________________________________\n", apexTimeInSecs, armTimeInSecs, dataLoadTimeInSecs, cpuTimeInSecs);
  #else 
    printf("\n____________________________________________________\n"
	       "Processes finished"
	       "\n____________________________________________________\n");
  #endif

  lInput0.SetFreeOnExit(true);
  lInput1.SetFreeOnExit(true);
  lOutput0_REF.SetFreeOnExit(true);
	
  return lRetVal;
}

int pixel_a1_ref(DataDescriptor& lInput0, DataDescriptor& lInput1, DataDescriptor& lOutput0)
{
  unsigned char* lpInput0 = (unsigned char*)lInput0.GetDataPtr();
  unsigned char* lpInput1 = (unsigned char*)lInput1.GetDataPtr();
  unsigned short* lpOutput0 = (unsigned short*)lOutput0.GetDataPtr();

  int lStrideInput0 = lInput0.GetSpan();
  int lStrideInput1 = lInput1.GetSpan();
  int lStrideOutput0 = lOutput0.GetSpan() / 2;
  
  int lWidth = lInput0.GetWidth();
  int lHeight = lInput0.GetHeight();
  int lDimensions = lInput0.GetDimensions();

  for (int d = 0; d < lDimensions; ++d)
  {
	for (int i = 0; i<lHeight; i++)
	{
	  for (int j = 0; j<lWidth; j++)
	  {
		lpOutput0[(lStrideOutput0*lHeight*d) + i*lStrideOutput0 + j] = (unsigned short)lpInput0[(lStrideInput0*lHeight*d) + i*lStrideInput0 + j] + (unsigned short)lpInput1[(lStrideInput1*lHeight*d) + i*lStrideInput1 + j];
	  }
	}
  }
  return 0;
}
