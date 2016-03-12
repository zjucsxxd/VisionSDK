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

#include <apexcv_base_arithmetic.h>
#include <stdint.h>

//arithmetic kernel headers
#include <apexcv_arithmetic.hpp>
#include "graph_templates.h"
#include "all_arithmetic_graph_registrations.h"

#include <map>
#include <utility>

namespace apexcv{


Arithmetic::Arithmetic()
{
}

Arithmetic::~Arithmetic()
{
}


typedef std::pair<std::pair<DATATYPE, DATATYPE>, ArithmBaseClass*> _mapPairType;
typedef std::map<std::pair<DATATYPE, DATATYPE>, ArithmBaseClass*> _graphMapType;

int Arithmetic::add(DataDescriptor&  src0 /*!< Source 0 memory buffer. */
	, DataDescriptor&  src1 /*!< Source 1 memory buffer. */
	, DataDescriptor&   dst /*!< Destination memory buffer. */
	)
{
	// For each function intialize a map with all variants of input/output data types and their associated instance of the process creator class "apexcv_arithmetic"
	_graphMapType addGraphMap;
	addGraphMap.insert(_mapPairType(std::pair<DATATYPE, DATATYPE>(DATATYPE_08U, DATATYPE_08U), new apexcv_arithmetic<ADD_08U>));
	addGraphMap.insert(_mapPairType(std::pair<DATATYPE, DATATYPE>(DATATYPE_16S, DATATYPE_16S), new apexcv_arithmetic<ADD_16S>));

	// Get at run time the type of the input and output data
	int result = 0;
	DATATYPE in1 = (DATATYPE)src0.GetElementDataType(),
		in2 = (DATATYPE)src1.GetElementDataType(),
		out = (DATATYPE)dst.GetElementDataType();

	// find the corresponding process instance for these data types
	_graphMapType::iterator it = addGraphMap.find(std::pair<DATATYPE, DATATYPE>(in1, out));

	if (it == addGraphMap.end()) {
		return 1; // error, type combination not yet implemented. An exception should be thrown
	}
	
	// Execute the found process
	result |= it->second->Initialize(src0, src1, dst);
	result |= it->second->Process();

	/*
	if (src0.GetElementDataType() == DATATYPE_08U &&
		src1.GetElementDataType() == DATATYPE_08U &&
		dst.GetElementDataType() == DATATYPE_08U) {

		apexcv_arithmetic<ADD_08U> a;

		result |= a.Initialize(src0, src1, dst);
		result |= a.Process();

	}
	else if (src0.GetElementDataType() == DATATYPE_16S &&
		src1.GetElementDataType() == DATATYPE_16S &&
		dst.GetElementDataType() == DATATYPE_16S) {

		apexcv_arithmetic<ADD_16S> a;

		result |= a.Initialize(src0, src1, dst);
		result |= a.Process();

	}
	else {
		//TODO: add standardized apex cv error codes
		return 1;
	}
*/
	return result;
}


int Arithmetic::abs( DataDescriptor&  src0 /*!< Source 0 memory buffer. */,
		             DataDescriptor&  dst  /*!< Destination memory buffer. */ )
{
    int result = 0;
   
    if(src0.GetElementDataType() == DATATYPE_08S && 
       dst.GetElementDataType()  == DATATYPE_08U) {
      
       apexcv_arithmetic<ABS_08U> a; 
      
       result |= a.Initialize(src0, dst);
       result |= a.Process();
      
    } else {
       //TODO: add standardized apex cv error codes
       return 1;
	}
   
	return result;
}

int Arithmetic::absdiff( DataDescriptor&  src0 /*!< Source 0 memory buffer. */,
                         DataDescriptor&  src1 /*!< Source 1 memory buffer. */,
		                 DataDescriptor&   dst /*!< Destination memory buffer. */ )
{
	int result = 0;
   
    if(src0.GetElementDataType() == DATATYPE_08U && 
       src1.GetElementDataType() == DATATYPE_08U && 
       dst.GetElementDataType()  == DATATYPE_08U) {
      
       apexcv_arithmetic<ABSDIFF_08U> a; 
      
       result |= a.Initialize(src0, src1, dst);
       result |= a.Process();
      
    } else {
       //TODO: add standardized apex cv error codes
       return 1;
	}
   
	return result;
}

int Arithmetic::accumulate( DataDescriptor&  src0 /*!< Source 0 memory buffer. */,
                            DataDescriptor&  src1 /*!< Source 1 memory buffer. */,
		                    DataDescriptor&   dst /*!< Destination memory buffer. */ )
{
    int result = 0;   

    if(src0.GetElementDataType() == DATATYPE_08U &&
       src1.GetElementDataType() == DATATYPE_08U &&
       dst.GetElementDataType()  == DATATYPE_16S) {
      
       apexcv_arithmetic<ACCUMULATE_16S> a;   
      
       result |= a.Initialize(src0, src1, dst);
       result |= a.Process();
      
    } else {
       //TODO: add standardized apex cv error codes
       result = 1;
    }
     
	return result;
}

int Arithmetic::accumulateSquared( DataDescriptor& src0 /*!< Source 0 memory buffer. */,
								   DataDescriptor& src1 /*!< Source 1 memory buffer. */,
								   DataDescriptor& dst /*!< Destination memory buffer. */,
								   unsigned char scale /*!< Scale amount. (0 <= scale <= 15) */)
{
	int result = 0;
	DataDescriptor scaleImg(1, 1, DATATYPE_08U);	
	*(unsigned char *)scaleImg.GetDataPtr() = scale;

    if(src0.GetElementDataType() == DATATYPE_08U &&
       src1.GetElementDataType() == DATATYPE_08U &&
       dst.GetElementDataType()  == DATATYPE_16S) {
      
       apexcv_arithmetic<ACCUMULATE_SQUARED_16S> a;   
      
       result |= a.Initialize(src0, src1, scaleImg, dst);
       result |= a.Process();
      
    } else {
      //TODO: add standardized apex cv error codes
      result = 1;
	}
   
    scaleImg.SetFreeOnExit(true);
   
	return result;
}

int Arithmetic::accumulateWeighted( DataDescriptor&  src0 /*!< Source 0 memory buffer. */,
                                    DataDescriptor&  src1 /*!< Source 1 memory buffer. */,
		                            DataDescriptor&   dst /*!< Destination memory buffer. */,
                                    unsigned char       alpha /*!< Weight amount. (0_8 bit fixed point) */ )
{
	int result = 0;
    DataDescriptor alphaImg(1, 1, DATATYPE_08U);
	*(unsigned char *)alphaImg.GetDataPtr() = alpha;
   
    if(src0.GetElementDataType() == DATATYPE_08U &&
       src1.GetElementDataType() == DATATYPE_08U &&
       dst.GetElementDataType()  == DATATYPE_08U) {
      
       apexcv_arithmetic<ACCUMULATE_WEIGHTED_08U> a;   
      
       result |= a.Initialize(src0, src1, alphaImg, dst);
       result |= a.Process();
      
    } else {
       //TODO: add standardized apex cv error codes
       result = 1;
 	}
   
    alphaImg.SetFreeOnExit(true);
   
	return result;
}

int Arithmetic::bitwiseAND( DataDescriptor&  src0 /*!< Source 0 memory buffer. */,
                            DataDescriptor&  src1 /*!< Source 1 memory buffer. */,
                            DataDescriptor&   dst /*!< Destination memory buffer. */ )
{
	int result = 0;
   
    if(src0.GetElementDataType() == DATATYPE_08U &&
       src1.GetElementDataType() == DATATYPE_08U &&
       dst.GetElementDataType() ==  DATATYPE_08U) {
      
       apexcv_arithmetic<AND_08U> a;
      
       result |= a.Initialize(src0, src1, dst);
       result |= a.Process();
      
    } else if(src0.GetElementDataType() == DATATYPE_16U &&
              src1.GetElementDataType() == DATATYPE_16U &&
              dst.GetElementDataType()  == DATATYPE_16U) {
             
       apexcv_arithmetic<AND_16U> a;
      
       result |= a.Initialize(src0, src1, dst);
       result |= a.Process();
      
    } else if(src0.GetElementDataType() == DATATYPE_32U &&
              src1.GetElementDataType() == DATATYPE_32U &&
              dst.GetElementDataType()  == DATATYPE_32U) {
             
       apexcv_arithmetic<AND_32U> a;
      
       result |= a.Initialize(src0, src1, dst);
       result |= a.Process();
      
    } else {
       //TODO: add standardized apex cv error codes
       return 1;
	}
   
	return result;
}

int Arithmetic::clz( DataDescriptor&  src  /*!< Source 0 memory buffer. */,
                     DataDescriptor&  dst  /*!< Destination memory buffer. */ )
{
	int result = 0;
   
    if(src.GetElementDataType() == DATATYPE_08U && 
       dst.GetElementDataType() == DATATYPE_08U) {
      
       apexcv_arithmetic<CLZ_08U> a; 
      
       result |= a.Initialize(src, dst);
       result |= a.Process();
      
    } else if(src.GetElementDataType() == DATATYPE_08S && 
              dst.GetElementDataType() == DATATYPE_08U) {
      
       apexcv_arithmetic<CLZ_08S> a; 
       
       result |= a.Initialize(src, dst);
       result |= a.Process();
      
    } else if(src.GetElementDataType() == DATATYPE_16U && 
              dst.GetElementDataType() == DATATYPE_08U) {
      
       apexcv_arithmetic<CLZ_16U> a; 
      
       result |= a.Initialize(src, dst);
       result |= a.Process();
      
    } else if(src.GetElementDataType() == DATATYPE_16S && 
              dst.GetElementDataType() == DATATYPE_08U) {
      
       apexcv_arithmetic<CLZ_16S> a; 
      
       result |= a.Initialize(src, dst);
       result |= a.Process();
      
    } else {
       //TODO: add standardized apex cv error codes
       return 1;
	}
   
	return result;
}

int Arithmetic::bitwiseNOT( DataDescriptor&  src /*!< Source 0 memory buffer. */,
                            DataDescriptor&  dst /*!< Destination memory buffer. */ )
{
	int result = 0;
   
    if(src.GetElementDataType() == DATATYPE_08U &&
       dst.GetElementDataType() == DATATYPE_08U) {
      
       apexcv_arithmetic<NOT_08U> a;
      
       result |= a.Initialize(src, dst);
       result |= a.Process();
       
    } else {
       //TODO: add standardized apex cv error codes
       return 1;
	}
   
	return result;
}

int Arithmetic::bitwiseOR( DataDescriptor&  src0 /*!< Source 0 memory buffer. */,
                           DataDescriptor&  src1 /*!< Source 1 memory buffer. */,
                           DataDescriptor&   dst /*!< Destination memory buffer. */ )
{
	int result = 0;
   
    if(src0.GetElementDataType() == DATATYPE_08U &&
       src1.GetElementDataType() == DATATYPE_08U &&
       dst.GetElementDataType() ==  DATATYPE_08U) {
      
       apexcv_arithmetic<OR_08U> a;
      
       result |= a.Initialize(src0, src1, dst);
       result |= a.Process();
      
    } else if(src0.GetElementDataType() == DATATYPE_16U &&
              src1.GetElementDataType() == DATATYPE_16U &&
              dst.GetElementDataType()  == DATATYPE_16U) {
             
       apexcv_arithmetic<OR_16U> a;
      
       result |= a.Initialize(src0, src1, dst);
       result |= a.Process();
      
    } else if(src0.GetElementDataType() == DATATYPE_32U &&
              src1.GetElementDataType() == DATATYPE_32U &&
              dst.GetElementDataType()  == DATATYPE_32U) {
             
       apexcv_arithmetic<OR_32U> a;
      
       result |= a.Initialize(src0, src1, dst);
       result |= a.Process();
      
    } else {
       //TODO: add standardized apex cv error codes
       return 1;
	}
   
	return result;
}

int Arithmetic::bitwiseXOR( DataDescriptor&  src0 /*!< Source 0 memory buffer. */,
                            DataDescriptor&  src1 /*!< Source 1 memory buffer. */,
                            DataDescriptor&   dst /*!< Destination memory buffer. */ )
{
	int result = 0;
   
    if(src0.GetElementDataType() == DATATYPE_08U &&
       src1.GetElementDataType() == DATATYPE_08U &&
       dst.GetElementDataType() ==  DATATYPE_08U) {
      
       apexcv_arithmetic<XOR_08U> a;
      
       result |= a.Initialize(src0, src1, dst);
       result |= a.Process();
      
    } else if(src0.GetElementDataType() == DATATYPE_16U &&
              src1.GetElementDataType() == DATATYPE_16U &&
              dst.GetElementDataType()  == DATATYPE_16U) {
             
       apexcv_arithmetic<XOR_16U> a;
      
       result |= a.Initialize(src0, src1, dst);
       result |= a.Process();
      
    } else if(src0.GetElementDataType() == DATATYPE_32U &&
              src1.GetElementDataType() == DATATYPE_32U &&
              dst.GetElementDataType()  == DATATYPE_32U) {
             
       apexcv_arithmetic<XOR_32U> a;
      
       result |= a.Initialize(src0, src1, dst);
       result |= a.Process();
      
    } else {
       //TODO: add standardized apex cv error codes
       return 1;
	}
   
	return result;
}

int Arithmetic::magnitude( DataDescriptor&  src0 /*!< Source 0 memory buffer. */,
                           DataDescriptor&  src1 /*!< Source 1 memory buffer. */,
                           DataDescriptor&   dst /*!< Destination memory buffer. */ )
{
	int result = 0;
   
    if(src0.GetElementDataType() == DATATYPE_16S &&
       src1.GetElementDataType() == DATATYPE_16S &&
       dst.GetElementDataType() ==  DATATYPE_16U) {
      
       apexcv_arithmetic<MAGNITUDE_16S> a;
      
       result |= a.Initialize(src0, src1, dst);
       result |= a.Process();
      
    } else {
       //TODO: add standardized apex cv error codes
       return 1;
	}
   
	return result;
}

int Arithmetic::subtract( DataDescriptor&  src0 /*!< Source 0 memory buffer. */,
                          DataDescriptor&  src1 /*!< Source 1 memory buffer. */,
                          DataDescriptor&   dst /*!< Destination memory buffer. */ )
{
	int result = 0;
   
    if(src0.GetElementDataType() == DATATYPE_08U &&
       src1.GetElementDataType() == DATATYPE_08U &&
       dst.GetElementDataType() ==  DATATYPE_16S) {
      
       apexcv_arithmetic<SUB_08U> a;
         
       result |= a.Initialize(src0, src1, dst);
       result |= a.Process();
      
    } else if(src0.GetElementDataType() == DATATYPE_16S &&
              src1.GetElementDataType() == DATATYPE_16S &&
              dst.GetElementDataType()  == DATATYPE_16S) {
             
       apexcv_arithmetic<SUB_16S> a;
            
       result |= a.Initialize(src0, src1, dst);
       result |= a.Process();
      
    } else {
       //TODO: add standardized apex cv error codes
       return 1;
	}
   
	return result;
}

int Arithmetic::threshold( DataDescriptor&        src /*!< Source 0 memory buffer. */,
                           DataDescriptor&        dst /*!< Destination memory buffer. */,
                           unsigned int         threshold /*!< Threshold value. */ )
{
    int result = 0;
      
    if(src.GetElementDataType() == DATATYPE_08U &&
       dst.GetElementDataType() == DATATYPE_08U) {
      
     if(threshold > 0xFF) {
        threshold = 0xFF;
     }
       DataDescriptor thresholdImg(1, 1, DATATYPE_08U);
	   *(uint8_t *)thresholdImg.GetDataPtr() = (uint8_t)threshold;
       apexcv_arithmetic<THRESHOLD_08U> a;
      	
       result |= a.Initialize(src, thresholdImg, dst);
       result |= a.Process();
	  
	   thresholdImg.SetFreeOnExit(true);
			
    } else if(src.GetElementDataType() == DATATYPE_16U &&
              dst.GetElementDataType() == DATATYPE_08U) {
      
       if(threshold > 0xFFFF) {
          threshold = 0xFFFF;
       }
      
       apexcv_arithmetic<THRESHOLD_16U> a;
	   DataDescriptor thresholdImg(1, 1, DATATYPE_16U);
	   *(uint16_t *)thresholdImg.GetDataPtr() = (uint16_t)threshold;
      			
       result |= a.Initialize(src, thresholdImg, dst);
       result |= a.Process();
	  
	   thresholdImg.SetFreeOnExit(true);
  
    } else if(src.GetElementDataType() == DATATYPE_32U &&
             dst.GetElementDataType() == DATATYPE_08U) {
      
       apexcv_arithmetic<THRESHOLD_32U> a;
	   DataDescriptor thresholdImg(1, 1, DATATYPE_32U);
	   *(uint32_t *)thresholdImg.GetDataPtr() = (uint32_t)threshold;
      			
       result |= a.Initialize(src, thresholdImg, dst);
       result |= a.Process();
	  
	   thresholdImg.SetFreeOnExit(true);
          
    } else {
       //TODO: add standardized apex cv error codes
       return 1;
	}
     
	return result;
}
                                       
}  /* namespace apex */
