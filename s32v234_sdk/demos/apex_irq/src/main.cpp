#include <icp_data.h>
#include <APU_ADD.hpp>
#include <apex.h>
#include <oal.h>
#include <iostream>

#include <stdio.h>
#include <stdlib.h>

using namespace std;

bool done1 = false;
bool done2 = false;
void handler1 ()
{
  done1 = true;
}
void handler2 ()
{
  done2 = true;
}

int pixel_a1_ref(icp::DataDescriptor& lInput0, icp::DataDescriptor& lInput1, icp::DataDescriptor& lOutput0);

/*======================================================================================*/
/* Main function									*/
/*======================================================================================*/
int main(int, char**)
{
  // HW and resources init
  ACF_Init();
  
  int lSrcWidth = 256;
  int lSrcHeight = 256;
  int lRetVal = 0;
  
  printf("Allocating data.\n");
  // Create images
  icp::DataDescriptor lInput0(lSrcWidth, lSrcHeight, icp::DATATYPE_08U);
  icp::DataDescriptor lInput1(lSrcWidth, lSrcHeight, icp::DATATYPE_08U);
  icp::DataDescriptor lOutput0_ACF1(lSrcWidth, lSrcHeight, icp::DATATYPE_16U);
  icp::DataDescriptor lOutput0_ACF2(lSrcWidth, lSrcHeight, icp::DATATYPE_16U);
  icp::DataDescriptor lOutput0_REF(lSrcWidth, lSrcHeight, icp::DATATYPE_16U);

  printf("Data on: \n");
  printf("   Input 1       (16x16 bytes) at %p\n", lInput0.GetDataPtrPhys());
  printf("   Input 2       (16x16 bytes) at %p\n", lInput1.GetDataPtrPhys());
  printf("   Output APEX 1 (16x16 words) at %p\n", lOutput0_ACF1.GetDataPtrPhys());
  printf("   Output APEX 2 (16x16 words) at %p\n", lOutput0_ACF2.GetDataPtrPhys());
  printf("   Output SW     (16x16 words) at %p\n", lOutput0_REF.GetDataPtrPhys());
  
  
		
  if (lInput0.IsOK() != 0 && lInput1.IsOK() != 0 && lOutput0_ACF1.IsOK() != 0 && lOutput0_ACF2.IsOK() != 0 && lOutput0_REF.IsOK() != 0)
  {
	  printf("Initialize APEX processes.\n");
	  APU_ADD process_apex1(APEX_APEX0); // True for Use IRQs
	  lRetVal |= process_apex1.Initialize();
	  lRetVal |= process_apex1.ConnectIO("Template_Demo_InputA", lInput0);
	  lRetVal |= process_apex1.ConnectIO("Template_Demo_InputB", lInput1);
	  lRetVal |= process_apex1.ConnectIO("Template_Demo_Output", lOutput0_ACF1);
	
	  APU_ADD process_apex2(APEX_APEX1); // True for Use IRQs
	  lRetVal |= process_apex2.Initialize(); 
	  lRetVal |= process_apex2.ConnectIO("Template_Demo_InputA", lInput0);
	  lRetVal |= process_apex2.ConnectIO("Template_Demo_InputB", lInput1);
	  lRetVal |= process_apex2.ConnectIO("Template_Demo_Output", lOutput0_ACF2);
		
	  for (int i = 0; i < 5; ++i)
	  {
		printf("Iteration %d\n", i);
		printf("=======================================\n");
		printf("Input random seed.\n");
		lInput0.FillRandom();
		lInput1.FillRandom();
	
		printf("Compute reference value via SW.\n");
		lRetVal |= pixel_a1_ref(lInput0, lInput1, lOutput0_REF);
  
		printf("Start APEX and init interrupts.\n");
		lRetVal |= process_apex1.InitDoneInterrupt(handler1);
		lRetVal |= process_apex1.Start();
		lRetVal |= process_apex2.InitDoneInterrupt(handler2);
		lRetVal |= process_apex2.Start();
		
		printf("Wait for done.\n");
	
		while (!done1 && !done2) {;}
	
		printf("Comparison: ");
		if (0 == lRetVal)
		{
			if (lOutput0_ACF1 == lOutput0_REF && lOutput0_ACF2 == lOutput0_REF)
				lRetVal = 0;
			else
				lRetVal += 1;
		}
	
		if (0 == lRetVal)
			printf("Outputs match.\n\n");
		else
			printf("Data do not match.\n\n");
		
		done1 = false;
		done2 = false;
	  }
  }
  else
  {
    lRetVal = 1;
  }

  return 0;
}

int pixel_a1_ref(icp::DataDescriptor& lInput0, icp::DataDescriptor& lInput1, icp::DataDescriptor& lOutput0)
{
   unsigned char* lpInput0 = (unsigned char*)lInput0.GetDataPtr();
   unsigned char* lpInput1 = (unsigned char*)lInput1.GetDataPtr();
   unsigned short* lpOutput0 = (unsigned short*)lOutput0.GetDataPtr();

   int lStrideInput0 = lInput0.GetSpan();
   int lStrideInput1 = lInput1.GetSpan();
   int lStrideOutput0 = lOutput0.GetSpan()/2;

   int lWidth = lInput0.GetWidth();
   int lHeight = lInput0.GetHeight();

   for (int i=0; i<lHeight; i++)
   {
      for (int j=0; j<lWidth; j++)
      {
         lpOutput0[i*lStrideOutput0 + j] = (unsigned short)lpInput0[i*lStrideInput0+j] + (unsigned short)lpInput1[i*lStrideInput1+j];
      }
   }

   return 0;
}


