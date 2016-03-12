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
 
#include <apexcv_base_interpolation.h>
#include <stdint.h>


#include <apexcv_interp_linear_grayscale.h>
#include <apexcv_interp_bilinear_grayscale.h>
#include <apexcv_interp_bicubic_grayscale.h>
#include "all_interpol_graph_registrations.h"


namespace apexcv{

Interpolation::Interpolation()
{
}

Interpolation::~Interpolation()
{
}

int Interpolation::linearGrayscale( DataDescriptor&        src /*!< Source memory buffer. */,
                                    DataDescriptor&        dst /*!< Destination memory buffer. */,
                                    DataDescriptor&     deltaX /*!< Delta X values for interpolation. */ )
{
   int result = 0;
   
   if(src.GetElementDataType() == DATATYPE_08U && 
      dst.GetElementDataType() == DATATYPE_08U &&
      deltaX.GetElementDataType() == DATATYPE_08U) {
      
      apexcv_interp_linear_grayscale f; 
      
      result |= f.Initialize(src, dst, deltaX);
      result |= f.Process();
      
   } else {
      //TODO: add standardized apex cv error codes
      return 1;
   }
  
   return result;
}

int Interpolation::bilinearGrayscale( DataDescriptor&        src /*!< Source memory buffer. */,
                                      DataDescriptor&        dst /*!< Destination memory buffer. */,
                                      DataDescriptor&      delta /*!< Delta XY values for interpolation. */ )
{
   int result = 0;
   
   if(src.GetElementDataType() == DATATYPE_08U && 
      dst.GetElementDataType() == DATATYPE_08U &&
      delta.GetElementDataType() == DATATYPE_08U) {
      
      apexcv_interp_bilinear_grayscale f; 
      
      result |= f.Initialize(src, dst, delta);
      result |= f.Process();
      
   } else {
      //TODO: add standardized apex cv error codes
      return 1;
   }
  
   return result;
}

int Interpolation::bicubicGrayscale(       DataDescriptor&           src /*!< Source memory buffer. */,
                                           DataDescriptor&           dst /*!< Destination memory buffer. */,
                                           DataDescriptor&      x_offset /*!< Delta X value for interpolation. */,
                                           DataDescriptor&      y_offset /*!< Delta X value for interpolation. */)
{
   int result = 0;

   if(src.GetElementDataType()      == DATATYPE_08U && 
      dst.GetElementDataType()      == DATATYPE_08U &&
      x_offset.GetElementDataType() == DATATYPE_08U &&
      y_offset.GetElementDataType() == DATATYPE_08U) {

      apexcv_interp_bicubic_grayscale f;

      result |= f.Initialize(src, dst, x_offset, y_offset);
      result |= f.Process();
   }

   else{
    return 1;
   }

   return result;
}


}  /* namespace apex */
