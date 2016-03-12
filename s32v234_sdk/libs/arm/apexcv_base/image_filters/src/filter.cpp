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
 
#include <apexcv_base_image_filters.h>
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

#include <oal.h>
#include <apexcv_filter.h>
#include <stdio.h>
#include "graph_templates.h"

namespace apexcv{

ImageFilter::ImageFilter()
{
}

ImageFilter::~ImageFilter()
{
}

int ImageFilter::bilateralFilter( DataDescriptor&        src /*!< Source memory buffer. */,
                                  DataDescriptor&        dst /*!< Destination memory buffer. */,
                                  int                 sigmaColor /*!< Sigma value for color space. */,
                                  int                 sigmaSpace /*!< Sigma value for distance space. */ )
{
   int result = 0;
   
   DataDescriptor sigmaCImg(1, 1, DATATYPE_32S);
   DataDescriptor sigmaSImg(1, 1, DATATYPE_32S);
   //DataDescriptor r_lut(src.GetWidth()*8,src.GetHeight(), DATATYPE_08U); 
   //DataDescriptor d_lut(9, 1, DATATYPE_08U);
   
   if(!sigmaCImg.IsOK() || !sigmaSImg.IsOK()// ||
	   //!r_lut.IsOK() || !d_lut.IsOK()
	   ) {
      sigmaCImg.SetFreeOnExit(true);
	  sigmaSImg.SetFreeOnExit(true);
	  //r_lut.SetFreeOnExit(true);
	  //d_lut.SetFreeOnExit(true);
      return 1;
   }

   
   *(int32_t *)(sigmaCImg.GetDataPtr()) = sigmaColor;
   *(int32_t *)(sigmaSImg.GetDataPtr()) = sigmaSpace;
   
   if(src.GetElementDataType() == DATATYPE_08U && 
      dst.GetElementDataType() == DATATYPE_08U) {
      
      apexcv_filter<BILATERAL_5X5> f; 
      
      result |= f.Initialize(src, dst, sigmaCImg, sigmaSImg);//, r_lut, d_lut);
      result |= f.Process();
      
   } else {
      //TODO: add standardized apex cv error codes
      sigmaCImg.SetFreeOnExit(true);
	  sigmaSImg.SetFreeOnExit(true);
	  //r_lut.SetFreeOnExit(true);
	  //d_lut.SetFreeOnExit(true);

      return 1;
   }
  
   sigmaCImg.SetFreeOnExit(true);
   sigmaSImg.SetFreeOnExit(true);
   //r_lut.SetFreeOnExit(true);
   //d_lut.SetFreeOnExit(true);

   return result;
}

int ImageFilter::boxFilter( DataDescriptor&  src /*!< Source memory buffer. */,
                            DataDescriptor&  dst /*!< Destination memory buffer. */ ,
                            int           windowSize /*!< Defines a filter window with dimensions _windowSize_ x _windowSize_. Default is 3. See supported window sizes. */)
{
   int result = 0;
   
   if (windowSize == 3) {
      if (src.GetElementDataType() == DATATYPE_08U &&
          dst.GetElementDataType() == DATATYPE_08U) {
      
         apexcv_filter<BOX_3X3_08U> f;   
      
         result |= f.Initialize(src, dst);
         result |= f.Process();
      } else if ( src.GetElementDataType() == DATATYPE_16S &&
                  dst.GetElementDataType() == DATATYPE_16S) {

         apexcv_filter<BOX_3X3_16S> f;   
      
         result |= f.Initialize(src, dst);
         result |= f.Process();
      } else {
         //TODO: add standardized apex cv error codes
         result = 1;
      }
   } else if (windowSize == 5) {
      if ( src.GetElementDataType() == DATATYPE_16S &&
           dst.GetElementDataType() == DATATYPE_16S) {

         apexcv_filter<BOX_5X5_16S> f;

         result |= f.Initialize(src, dst);
         result |= f.Process();
      } else {
         //TODO: add standardized apex cv error codes
         result = 1;
      }
   } else {
      //TODO: add standardized apex cv error codes
      result = 1;
   }
   
   return result;
}

int ImageFilter::dilateFilter( DataDescriptor&  src /*!< Source memory buffer. */,
                               DataDescriptor&  dst /*!< Destination memory buffer. */ )
{
   int result = 0;
   
   if (src.GetElementDataType() == DATATYPE_08U &&
       dst.GetElementDataType() == DATATYPE_08U) {
      
      apexcv_filter<DILATE_3X3_08U> f; 
      
      result |= f.Initialize(src, dst);
      result |= f.Process();
   
   } else if ( src.GetElementDataType() == DATATYPE_16S &&
               dst.GetElementDataType() == DATATYPE_16S) {
   
	  apexcv_filter<DILATE_3X3_16S> f; 
      
      result |= f.Initialize(src, dst);
      result |= f.Process();
   } else {
      //TODO: add standardized apex cv error codes
      return 1;
   }
      
   return result;
}

int ImageFilter::erodeFilter( DataDescriptor&  src /*!< Source memory buffer. */,
                              DataDescriptor&  dst /*!< Destination memory buffer. */ )
{
   int result = 0;
   
   if(src.GetElementDataType() == DATATYPE_08U &&
      dst.GetElementDataType() == DATATYPE_08U) {
      
      apexcv_filter<ERODE_3X3_08U> f;
      
      result |= f.Initialize(src, dst);
      result |= f.Process();
      
   } else {
      //TODO: add standardized apex cv error codes
      return 1;
   }
  
   return result;
}     

int ImageFilter::medianFilter( DataDescriptor&  src /*!< Source memory buffer. */,
                               DataDescriptor&  dst /*!< Destination memory buffer. */,
                               int           windowSize /*!< Defines a filter window with height: windowSize, width: windowSize. Default is 3. See supported window sizes. */ )                                                
{
   int result = 0;
   
   if(src.GetElementDataType() == DATATYPE_08U &&
      dst.GetElementDataType() == DATATYPE_08U) {
      
         apexcv_filter<MEDIAN_3X3_08U> f3;
         apexcv_filter<MEDIAN_5X5_08U> f5;
         switch(windowSize) 
         {
            case 3:
               result |= f3.Initialize(src, dst);
               result |= f3.Process();
               break;
               
            case 5:
               result |= f5.Initialize(src, dst);
               result |= f5.Process();
               break;
               
            default:
               return 1;         
         }  
   } else {
      //TODO: add standardized apex cv error codes
      return 1;
   }
  
   return result;
}   

int ImageFilter::gaussianFilter( DataDescriptor&  src /*!< Source memory buffer. */,
                                 DataDescriptor&  dst /*!< Destination memory buffer. */ ,
                                 int           windowSize /*!< Defines a filter window with dimensions _windowSize_ x _windowSize_. Default is 3. See supported window sizes. */)
{
   int result = 0;
   
   if (windowSize==3) {
      if(src.GetElementDataType() == DATATYPE_08U &&
         dst.GetElementDataType() == DATATYPE_08U) {

         apexcv_filter<GAUSSIAN_3X3_08U> f;

         result |= f.Initialize(src, dst);
         result |= f.Process();
      } else {
         //TODO: add standardized apex cv error codes
         result = 1;
      }
   } else if (windowSize==5) {
      if(src.GetElementDataType() == DATATYPE_08U &&
         dst.GetElementDataType() == DATATYPE_08U) {

         apexcv_filter<GAUSSIAN_5X5_08U> f;

         result |= f.Initialize(src, dst);
         result |= f.Process();
      } else {
         //TODO: add standardized apex cv error codes
         result = 1;
      }
   } else {
      //TODO: add standardized apex cv error codes
      result = 1;
   }
   
   return result;
}  

int ImageFilter::sobelFilter( DataDescriptor&        src /*!< Source memory buffer. See DataDescriptor \cite ACF_CHM */,
                              DataDescriptor&        dst /*!< Destination memory buffer. See DataDescriptor \cite ACF_CHM */,
                              int                 windowSize /*!< Defines a filter window with height: windowSize, width: windowSize. Default is 3. See supported window sizes. */,                                            
                              SobelType                   st /*!< Specify which sobel filter type to use. Default is SOBEL_BOTH. See SobelType. */ )
{
   int result = 0;
   
      if(src.GetElementDataType() == DATATYPE_08U &&
         dst.GetElementDataType() == DATATYPE_08U) {
      
         if(st == ImageFilter::SOBEL_X) {
            apexcv_filter<SOBEL_X_3X3_08U> f3;
            apexcv_filter<SOBEL_X_5X5_08U> f5;
            
            switch(windowSize) 
            {
               case 3:
                  result |= f3.Initialize(src, dst);
                  result |= f3.Process();
                  break;
                  
               case 5:
                  result |= f5.Initialize(src, dst);
                  result |= f5.Process();
                  break;
                  
               default:
                  return 1;         
            }  
         } else if(st == ImageFilter::SOBEL_Y) {
            apexcv_filter<SOBEL_Y_3X3_08U> f3;
            apexcv_filter<SOBEL_Y_5X5_08U> f5;
            
            switch(windowSize) 
            {
               case 3:
                  result |= f3.Initialize(src, dst);
                  result |= f3.Process();
                  break;
                  
               case 5:
                  result |= f5.Initialize(src, dst);
                  result |= f5.Process();
                  break;
                  
               default:
                  return 1;         
            } 
         }else if(st == ImageFilter::SOBEL_BOTH) {
            apexcv_filter<SOBEL_3X3_08U> f3;
            apexcv_filter<SOBEL_5X5_08U> f5;
            
            switch(windowSize) 
            {
               case 3:
                  result |= f3.Initialize(src, dst);
                  result |= f3.Process();
                  break;
                  
               case 5:
                  result |= f5.Initialize(src, dst);
                  result |= f5.Process();
                  break;
                  
               default:
                  return 1;         
            }  
         } else {
            return 1;
         }
      } else if ( src.GetElementDataType() == DATATYPE_08U &&
                  dst.GetElementDataType() == DATATYPE_08S) {
         if (st == ImageFilter::SOBEL_X) {
            apexcv_filter<SOBEL_X_3X3_08S> f3;
            apexcv_filter<SOBEL_X_5X5_08S> f5;
            
            switch(windowSize) 
            {
               case 3:
                  result |= f3.Initialize(src, dst);
                  result |= f3.Process();
                  break;
                  
               case 5:
                  result |= f5.Initialize(src, dst);
                  result |= f5.Process();
                  break;
                  
               default:
                  return 1;         
            }  
         } else if (st == ImageFilter::SOBEL_Y) {
            apexcv_filter<SOBEL_Y_3X3_08S> f3;
            apexcv_filter<SOBEL_Y_5X5_08S> f5;
            
            switch(windowSize) 
            {
               case 3:
                  result |= f3.Initialize(src, dst);
                  result |= f3.Process();
                  break;
                  
               case 5:
                  result |= f5.Initialize(src, dst);
                  result |= f5.Process();
                  break;
                  
               default:
                  return 1;         
            } 
         } else {
            return 1;
         }
      } else {
      //TODO: add standardized apex cv error codes
      return 1;
      }
  
   return result;
}  

int ImageFilter::sobelFilter(        DataDescriptor&        src /*!< Source memory buffer. See ICP_ContigDataDesc \cite ACF_CHM */,
                                     DataDescriptor&       dstX /*!< Destination X memory buffer. See ICP_ContigDataDesc \cite ACF_CHM */,
                                     DataDescriptor&       dstY /*!< Destination Y memory buffer. See ICP_ContigDataDesc \cite ACF_CHM */
)
{
   int result = 0;

   if(src.GetElementDataType() == DATATYPE_08U &&
      dstX.GetElementDataType() == DATATYPE_08U &&
      dstY.GetElementDataType() == DATATYPE_08U) {
      
      SOBEL_XY_3X3_08U fProcess;
      result |= fProcess.Initialize();
      result |= fProcess.ConnectIO(GR_IN_0, src);
      result |= fProcess.ConnectIO(GR_OUT_0, dstX);
      result |= fProcess.ConnectIO(GR_OUT_1, dstY);
      if (!result) {
         result |= fProcess.Start();
         result |= fProcess.Wait();
      }
   } else {
      //TODO: add standardized apex cv error codes
      result = 1;
   }

   return result;
}

int ImageFilter::convolveFilter( DataDescriptor&        src /*!< Source memory buffer. See DataDescriptor \cite ACF_CHM */,
                                 DataDescriptor&        dst /*!< Destination memory buffer. See DataDescriptor \cite ACF_CHM */,
                                 signed char* filterCoeff /*!< Array containing the filter coefficients to be applied. */,                                            
                                 int                 windowSize /*!< Defines a filter window with height: windowSize, width: windowSize. Default is 3. See supported window sizes. */,
                                 int                filterScale /*!< Optional: used to scale the resulting filtered pixel by 2^filterScale. */ )
{
   int result = 0;
   
   DataDescriptor filterCoeffImg;
   filterCoeffImg.InitManual(windowSize* windowSize, 1, (void *)filterCoeff, OAL_MemoryReturnAddress((void *)filterCoeff, ACCESS_PHY) ,DATATYPE_08S);
   DataDescriptor filterScaleImg(1, 1, DATATYPE_32S);
   
   if(!filterCoeffImg.IsOK() || !filterScaleImg.IsOK()) {
      //filterCoeffImg.SetFreeOnExit(true);
	  filterScaleImg.SetFreeOnExit(true);
      return 1;
   }
   
   *(int32_t *)(filterScaleImg.GetDataPtr()) = filterScale;
   
   if(src.GetElementDataType() == DATATYPE_08U &&
      dst.GetElementDataType() == DATATYPE_08U) {

      if(filterScale > 0) {
         apexcv_filter<CONVOLVE_SCALE_3X3_08U> f3;
         apexcv_filter<CONVOLVE_SCALE_5X5_08U> f5;
         switch(windowSize) 
         {
            case 3:
               result |= f3.Initialize_Scale(src, dst, filterCoeffImg, filterScaleImg);
               result |= f3.Process();
               break;
               
            case 5:
               result |= f5.Initialize_Scale(src, dst, filterCoeffImg, filterScaleImg);
               result |= f5.Process();
               break;
               
            default:
               return 1;         
         }
      } else {
         apexcv_filter<CONVOLVE_3X3_08U> f3;
         apexcv_filter<CONVOLVE_5X5_08U> f5;
         switch(windowSize) 
         {
            case 3:
               result |= f3.Initialize(src, dst, filterCoeffImg);
               result |= f3.Process();
               break;
               
            case 5:
               result |= f5.Initialize(src, dst, filterCoeffImg);
               result |= f5.Process();
               break;
               
            default:
               return 1;         
         }
      }
   } else if(src.GetElementDataType() == DATATYPE_08U &&
               dst.GetElementDataType() == DATATYPE_16S) {
                  
      if(filterScale > 0) {
         apexcv_filter<CONVOLVE_SCALE_3X3_16S> f3;
         apexcv_filter<CONVOLVE_SCALE_5X5_16S> f5;
         switch(windowSize) 
         {
            case 3:
               result |= f3.Initialize_Scale(src, dst, filterCoeffImg, filterScaleImg);
               result |= f3.Process();
               break;
               
            case 5:
               result |= f5.Initialize_Scale(src, dst, filterCoeffImg, filterScaleImg);
               result |= f5.Process();
               break;
               
            default:
               return 1;         
         }
      } else {
         apexcv_filter<CONVOLVE_3X3_16S> f3;
         apexcv_filter<CONVOLVE_5X5_16S> f5;
         switch(windowSize) 
         {
            case 3:
               result |= f3.Initialize(src, dst, filterCoeffImg);
               result |= f3.Process();
               break;
               
            case 5:
               result |= f5.Initialize(src, dst, filterCoeffImg);
               result |= f5.Process();
               break;
               
            default:
               return 1;         
         }
      }
   } else {
    //TODO: add standardized apex cv error codes
    //  filterCoeffImg.SetFreeOnExit(true);
	//  filterScaleImg.SetFreeOnExit(true);
    return 1;
   }
  
   //filterCoeffImg.SetFreeOnExit(true);
   filterScaleImg.SetFreeOnExit(true);
   return result;
}                                                
                              
int ImageFilter::prewittFilter( DataDescriptor&  src /*!< Source memory buffer. */,
                                DataDescriptor&  dst /*!< Destination memory buffer. */,
                                PrewittType           pt /*!< Specify which prewitt filter to use. Default is PREWITT_X. See PrewittType. */ )
{
   int result = 0;
   
   if(src.GetElementDataType() == DATATYPE_08U &&
      dst.GetElementDataType() == DATATYPE_16S) {
      
      if(pt == ImageFilter::PREWITT_X) {
         apexcv_filter<PREWITT_X_3X3> f;

         result |= f.Initialize(src, dst);
         result |= f.Process();
            
      } else if(pt == ImageFilter::PREWITT_Y) {
         apexcv_filter<PREWITT_Y_3X3> f;

         result |= f.Initialize(src, dst);
         result |= f.Process();  
      } else {
         return 1;
      }
   } else {
      //TODO: add standardized apex cv error codes
      return 1;
   }
      
   return result;
}
   
int OPT::ImageFilter::boxFilter(      DataDescriptor&  src /*!< Source memory buffer. */,
                                      DataDescriptor&  dst /*!< Destination memory buffer. See ICP_ContigDataDesc \cite ACF_CHM */,
                                      int           windowSize /*!< Defines a filter window with dimensions _windowSize_ x _windowSize_. Default is 3. See supported window sizes. */

)
{
   int result = 0;

   if (src.GetElementDataType() == DATATYPE_08U &&
       dst.GetElementDataType() == DATATYPE_08U) {
      switch(windowSize)
      {
         case 3:
         {
            apexcv_filter<HT_BOX_3X3_08U> f;

            result |= f.Initialize(src, dst);
            result |= f.Process();
         }
         break;
         default:
         {
            result = 1;
         }
         break;
      }
   } else {
      //TODO: add standardized apex cv error codes
      result = 1;
   }

   return result;
}

OPT::ImageFilter::ImageFilter()
{
}

OPT::ImageFilter::~ImageFilter()
{
}

int OPT::ImageFilter::convolveFilter(  DataDescriptor&    src /*!< Source memory buffer. See ICP_ContigDataDesc \cite ACF_CHM */,
                                       DataDescriptor&        dst /*!< Destination memory buffer. See ICP_ContigDataDesc \cite ACF_CHM */,
                                       const signed char* filterCoeff /*!< Array containing the filter coefficients to be applied. */,
                                       int                 windowSize /*!< Defines a filter window with height: windowSize, width: windowSize. Default is 3. See supported window sizes. */,
                                       int                filterScale /*!< Optional: used to scale the resulting filtered pixel by 2^filterScale. */ )
{
   int result = 0;

   DataDescriptor filterCoeffImg;
   DataDescriptor filterScaleImg(1, 1, DATATYPE_08S);
   filterCoeffImg.InitManual(windowSize * windowSize, 1, (void *)filterCoeff, OAL_MemoryReturnAddress((void *)filterCoeff, ACCESS_PHY), DATATYPE_08S);
   
   if(!filterCoeffImg.IsOK() || !filterScaleImg.IsOK()) {
      //filterCoeffImg.SetFreeOnExit(true);
	  filterScaleImg.SetFreeOnExit(true);
      return 1;
   }
   
   *(uint8_t *)(filterScaleImg.GetDataPtr()) = filterScale;
   
   if(src.GetElementDataType() == DATATYPE_08U &&
      dst.GetElementDataType() == DATATYPE_08U) {
      
      switch(windowSize)
      {
         case 3:
         {
            apexcv_filter<HT_GENERIC_3X3_08U> f3;
            result |= f3.Initialize_Scale(src, dst, filterCoeffImg, filterScaleImg);
            result |= f3.Process();
         }
         break;

         case 5:
         {
            apexcv_filter<HT_GENERIC_5X5_08U> f5;
            result |= f5.Initialize_Scale(src, dst, filterCoeffImg, filterScaleImg);
            result |= f5.Process();
         }
         break;

         default:
         {
            result = 1;
         }
         break;
      }
   } else {
      //TODO: add standardized apex cv error codes
      result = 1;
   }

   //filterCoeffImg.SetFreeOnExit(true);
   filterScaleImg.SetFreeOnExit(true);
   return result;
}

int OPT::ImageFilter::derivativeFilter(         DataDescriptor& src /*!< Source memory buffer. See ICP_ContigDataDesc \cite ACF_CHM */,
                                                DataDescriptor& dst /*!< Destination memory buffer. See ICP_ContigDataDesc \cite ACF_CHM */,
                                                     DerivativeType dt /*!< Specify which derivative filter type to use. See \ref DerivativeType. */,
                                                        signed char k0 /*!< The first filter coefficient. */,
                                                        signed char k1 /*!< The first filter coefficient. */,
                                                        signed char k2 /*!< The first filter coefficient. */
)
{
   int result = 0;

   DataDescriptor k0Img(1, 1, DATATYPE_08S);
   DataDescriptor k1Img(1, 1, DATATYPE_08S);
   DataDescriptor k2Img(1, 1, DATATYPE_08S);
   
   if(!k0Img.IsOK() || !k1Img.IsOK() || !k2Img.IsOK()) {
      k0Img.SetFreeOnExit(true);
	  k1Img.SetFreeOnExit(true);
	  k2Img.SetFreeOnExit(true);
      return 1;
   }
   
   *(int8_t *)(k0Img.GetDataPtr()) = k0;
   *(int8_t *)(k1Img.GetDataPtr()) = k1;
   *(int8_t *)(k2Img.GetDataPtr()) = k2;
   
   if (src.GetElementDataType() == DATATYPE_08U &&
       dst.GetElementDataType() == DATATYPE_16S) {
      
      switch(dt)
      {
      case DERIVATIVE_X:
      {
         HT_CENTRALDX_3X3_16S fx;
         result |= fx.Initialize();
         result |= fx.ConnectIO(GR_IN_0, src);
         result |= fx.ConnectIO(GR_OUT_0, dst);
         result |= fx.ConnectIO("K_0", k0Img);
         result |= fx.ConnectIO("K_1", k1Img);
         result |= fx.ConnectIO("K_2", k2Img);
         if (!result) {
            result |= fx.Start();
            result |= fx.Wait();
         }
      }
      break;
      case DERIVATIVE_Y:
      {
         HT_CENTRALDY_3X3_16S fy;
         result |= fy.Initialize();
         result |= fy.ConnectIO(GR_IN_0, src);
         result |= fy.ConnectIO(GR_OUT_0, dst);
         result |= fy.ConnectIO("K_0", k0Img);
         result |= fy.ConnectIO("K_1", k1Img);
         result |= fy.ConnectIO("K_2", k2Img);
         if (!result) {
            result |= fy.Start();
            result |= fy.Wait();
         }
      }
      break;
      default:
         result = 1;
         break;
      }
   } else {
      //TODO: add standardized apex cv error codes
      result = 1;
   }

   k0Img.SetFreeOnExit(true);
   k1Img.SetFreeOnExit(true);
   k2Img.SetFreeOnExit(true);
   return result;
}

int OPT::ImageFilter::saturateFilter(      DataDescriptor&  src /*!< Source memory buffer. */,
                                           DataDescriptor&  dst /*!< Destination memory buffer. */
)
{
   int result = 0;

   if (src.GetElementDataType() == DATATYPE_16S &&
       dst.GetElementDataType() == DATATYPE_08S) {

      apexcv_filter<HT_SATURATE_08S> f;

      result |= f.Initialize(src, dst);
      result |= f.Process();
   } else {
      //TODO: add standardized apex cv error codes
      result = 1;
   }

   return result;
}

int OPT::ImageFilter::separableFilter(      DataDescriptor&        src /*!< Source memory buffer. See ICP_ContigDataDesc \cite ACF_CHM */,
                                            DataDescriptor&        dst /*!< Destination memory buffer. See ICP_ContigDataDesc \cite ACF_CHM */,
                                            signed char*   filterRow /*!< Array containing the row filter coefficients to be applied. */,
                                            signed char*   filterCol /*!< Array containing the column filter coefficients to be applied. */,
                                            int                 windowSize /*!< Defines a filter window with height: windowSize, width: windowSize. Default is 3. See supported window sizes. */
)
{
   int result = 0;

   DataDescriptor filterRowImg;
   filterRowImg.InitManual(windowSize, windowSize, (void *)filterRow, OAL_MemoryReturnAddress((void *)filterRow, ACCESS_PHY) ,DATATYPE_08S);
   DataDescriptor filterColImg;
   filterColImg.InitManual(windowSize, windowSize, (void *)filterCol, OAL_MemoryReturnAddress((void *)filterCol, ACCESS_PHY) ,DATATYPE_08S);
   
   if(!filterRowImg.IsOK() || !filterColImg.IsOK()) {
      //filterRowImg.SetFreeOnExit(true);
	  //filterColImg.SetFreeOnExit(true);
      return 1;
   }
   
   if (src.GetElementDataType() == DATATYPE_08U &&
       dst.GetElementDataType() == DATATYPE_16S) {

      switch(windowSize)
      {
         case 3:
         {
            HT_SEPARABLE_3X3_16S f3;
            result |= f3.Initialize();
            result |= f3.ConnectIO(GR_IN_0, src);
            result |= f3.ConnectIO(GR_OUT_0, dst);
            result |= f3.ConnectIO(GR_F_ROW, filterRowImg);
            result |= f3.ConnectIO(GR_F_COL, filterColImg);
            if (!result) {
               result |= f3.Start();
               result |= f3.Wait();
            }
         }
         break;

         case 5:
         {
            HT_SEPARABLE_5X5_16S f5;
            result |= f5.Initialize();
            result |= f5.ConnectIO(GR_IN_0, src);
            result |= f5.ConnectIO(GR_OUT_0, dst);
            result |= f5.ConnectIO(GR_F_ROW, filterRowImg);
            result |= f5.ConnectIO(GR_F_COL, filterColImg);
            if (!result) {
               result |= f5.Start();
               result |= f5.Wait();
            }
         }
         break;

         default:
         {
            result = 1;
         }
         break;
      }
   } else {
      //TODO: add standardized apex cv error codes
      result = 1;
   }

  // filterRowImg.SetFreeOnExit(true);
  // filterColImg.SetFreeOnExit(true);
   return result;
}

int OPT::ImageFilter::sobelFilter(     DataDescriptor&        src /*!< Source memory buffer. See ICP_ContigDataDesc \cite ACF_CHM */,
                                       DataDescriptor&        dst /*!< Destination memory buffer. See ICP_ContigDataDesc \cite ACF_CHM */,
                                       int                 windowSize /*!< Defines a filter window with dimensions _windowSize_ x _windowSize_. Default is 3. See supported window sizes. */,                                              
                                       SobelType                  st  /*!< Specify which sobel filter type to use. Default is SOBEL_SUM. See \ref SobelType. */
)
{
   int result = 0;

   if(src.GetElementDataType() == DATATYPE_08U &&
      dst.GetElementDataType() == DATATYPE_08S) {
      
	  DataDescriptor bufferImg(src.GetWidth(), src.GetHeight(), DATATYPE_16S);
	  if(!bufferImg.IsOK()) {
		bufferImg.SetFreeOnExit(true);
      return 1;
   }
    
      if (st == ImageFilter::SOBEL_X) {
         switch(windowSize)
         {
            case 3:
            {
               HT_SOBEL_X_3X3_08S f3;
               result |= f3.Initialize();
               result |= f3.ConnectIO(GR_IN_0, src);
               result |= f3.ConnectIO(GR_OUT_0, dst);
               result |= f3.ConnectIO("BUFFER_0", bufferImg);
               if (!result) {
                  result |= f3.Start();
                  result |= f3.Wait();
               }
            }
            break;
            default:
            {
               result = 1;
            }
            break;
         }
      } else if (st == ImageFilter::SOBEL_Y) {
         switch(windowSize)
         {
            case 3:
            {
               HT_SOBEL_Y_3X3_08S f3;
               result |= f3.Initialize();
               result |= f3.ConnectIO(GR_IN_0, src);
               result |= f3.ConnectIO(GR_OUT_0, dst);
               result |= f3.ConnectIO("BUFFER_0", bufferImg);
               if (!result) {
                  result |= f3.Start();
                  result |= f3.Wait();
               }
            }
            break;
            default:
            {
               result = 1;
            }
            break;
         }
      } else {
         result = 1;
      }
      bufferImg.SetFreeOnExit(true);
   } else if ( src.GetElementDataType() == DATATYPE_08U &&
               dst.GetElementDataType() == DATATYPE_16S) {
      if(st == ImageFilter::SOBEL_BOTH) {
         switch(windowSize)
         {
            case 3:
            {
               apexcv_filter<HT_SOBEL_3X3_16S> f;
               result |= f.Initialize(src, dst);
               result |= f.Process();
            }
            break;
            default:
            {
               result = 1;
            }
            break;
         }
      } else {
         result = 1;
      }
   } else {
      //TODO: add standardized apex cv error codes
      result = 1;
   }

   return result;
}
   
}  /* namespace apex */
