/******************************************************************************
 *  (C) Copyright CogniVue Corporation. 2014 All right reserved.
 *  
 *  Confidential Information
 *
 *  All parts of the CogniVue Program Source are protected by copyright law
 *  and all rights are reserved.
 *  This documentation may not, in whole or in part, be copied, photocopied,
 *  reproduced, translated, or reduced to any electronic medium or machine
 *  readable form without prior consent, in writing, from CogniVue.
 ******************************************************************************/
 
#include <apexcv_base_color_conversion.h>
#include <stdint.h>

#ifndef APEX2_EMULATE
#include <icp_data.h>
using namespace icp;
#else
#include "apu_lib.hpp"
#include "apu_extras.hpp"
#include "acf_lib.hpp"
using namespace APEX2;
#endif

#include <apexcv_rgb565_to_rgb888.h>
#include <apexcv_rgb888_to_rgb565.h>
#include <apexcv_rgb888_to_y.h>
#include <apexcv_rgb888_to_yuv.h>
#include <apexcv_ht_8uc3_to_y.h>

namespace apexcv{

ColorConverter::ColorConverter()
{
}

ColorConverter::~ColorConverter()
{
}

int ColorConverter::convert( DataDescriptor&        src /*!< Source memory buffer. */,
                             DataDescriptor&        dst /*!< Destination memory buffer. */,
                             ConversionType              ct /*!< Color conversion type. */,
                             int       		      R2YFactor /*!< Conversion factor for red to gray. Used with RGB888_TO_Y */,
                             int        	      G2YFactor /*!< Conversion factor for green to gray. Used with RGB888_TO_Y */,
                             int        		  B2YFactor /*!< Conversion factor for blue to gray. Used with RGB888_TO_Y*/ )
{
	int result = 0;
   
   if(ct == ColorConverter::RGB565_TO_RGB888) {
      if(src.GetElementDataType() == DATATYPE_16U && 
         dst.GetElementDataType() == DATATYPE_32U) {
      
         apexcv_rgb565_to_rgb888 c; 
         
         result |= c.Initialize(src, dst);
         result |= c.Process();
      } else {
         return 1;
      }
   } else if(ct == ColorConverter::RGB888_TO_RGB565) {
      if(src.GetElementDataType() == DATATYPE_32U && 
         dst.GetElementDataType() == DATATYPE_16U) {
      
         apexcv_rgb888_to_rgb565 c; 
         
         result |= c.Initialize(src, dst);
         result |= c.Process();         
      } else {
         return 1;
      }
   } else if(ct == ColorConverter::RGB888_TO_YUV) {
      if(src.GetElementDataType() == DATATYPE_08U && 
         dst.GetElementDataType() == DATATYPE_08U) {
      
         apexcv_rgb888_to_yuv c; 
         
         result |= c.Initialize(src, dst);
         result |= c.Process();         
      } else {
         return 1;
      }
   }  else if(ct == ColorConverter::RGB888_TO_Y) {
      if(src.GetElementDataType() == DATATYPE_08U && 
         dst.GetElementDataType() == DATATYPE_08U) {
			
			DataDescriptor R2YImg(1, 1, DATATYPE_32S);
			DataDescriptor G2YImg(1, 1, DATATYPE_32S);
			DataDescriptor B2YImg(1, 1, DATATYPE_32S);
			*(int32_t *)(R2YImg.GetDataPtr()) = R2YFactor;
			*(int32_t *)(G2YImg.GetDataPtr()) = G2YFactor;
			*(int32_t *)(B2YImg.GetDataPtr()) = B2YFactor;
			
			if(!R2YImg.IsOK() || !G2YImg.IsOK() || !B2YImg.IsOK()) {
				R2YImg.SetFreeOnExit(true);
				G2YImg.SetFreeOnExit(true);
				B2YImg.SetFreeOnExit(true);
				return 1;
			}
	
         apexcv_rgb888_to_y c; 
         
         result |= c.Initialize(src, dst, R2YImg, G2YImg, B2YImg);
         result |= c.Process();

         R2YImg.SetFreeOnExit(true);
		 G2YImg.SetFreeOnExit(true);
		 B2YImg.SetFreeOnExit(true);
      } else {
         return 1;
      }
	} else {
      //TODO: add standardized apex cv error codes
      return 1;
	}

	return result;
}   


namespace OPT {
   ColorConverter::ColorConverter()
   {
   }

   ColorConverter::~ColorConverter()
   {
   }

   int ColorConverter::convert(       DataDescriptor&        src /*!< Source memory buffer. */,
                                      DataDescriptor&        dst /*!< Destination memory buffer. */,
                                      ConversionType              ct /*!< Color conversion type. */,
                                      int                  R2YFactor /*!< Conversion factor for red channel. */,
                                      int                  G2YFactor /*!< Conversion factor for green channel. */,
                                      int                  B2YFactor /*!< Conversion factor for blue channel. */,
                                      int                ShiftFactor /*!< Shift factor. Used in HT_8UC3_TO_Y. */
   )
   {
      int result = 0;

      if (ct == ColorConverter::HT_8UC3_TO_Y) {
         if (src.GetElementDataType() == DATATYPE_08U &&
             dst.GetElementDataType() == DATATYPE_16S) {

            DataDescriptor R2YImg(1, 1, DATATYPE_08U);
			DataDescriptor G2YImg(1, 1, DATATYPE_08U);
			DataDescriptor B2YImg(1, 1, DATATYPE_08U);
			DataDescriptor ShiftImg(1, 1, DATATYPE_16U);

			*(uint8_t *)(R2YImg.GetDataPtr()) = R2YFactor;
			*(uint8_t *)(G2YImg.GetDataPtr()) = G2YFactor;
			*(uint8_t *)(B2YImg.GetDataPtr()) = B2YFactor;
			*(uint16_t *)(ShiftImg.GetDataPtr()) = ShiftFactor;
			
			if(!R2YImg.IsOK() || !G2YImg.IsOK() || !B2YImg.IsOK() || !ShiftImg.IsOK()) {
				R2YImg.SetFreeOnExit(true);
				G2YImg.SetFreeOnExit(true);
				B2YImg.SetFreeOnExit(true);
				ShiftImg.SetFreeOnExit(true);
				return 1;
			}
			
           apexcv_ht_8uc3_to_y c; 

            result |= c.Initialize(src, dst, R2YImg, G2YImg, B2YImg, ShiftImg);
            result |= c.Process();

            R2YImg.SetFreeOnExit(true);
			G2YImg.SetFreeOnExit(true);
			B2YImg.SetFreeOnExit(true);
			ShiftImg.SetFreeOnExit(true);
         } else {
            return 1;
         }
      } else {
         //TODO: add standardized apex cv error codes
         return 1;
      }

      return result;
   }
} 

} // namespace apecv 
                 
