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
/*!*********************************************************************************
*  \file apexcv_arithmetic_ref-impl.cpp
*  \brief Contains template definitions for reference code
***********************************************************************************/

#include "apexcv_arithmetic_ref.hpp"

#include <stdint.h>


template void abs_ref<int8_t, uint8_t>(     const int8_t* src, int sstr, uint8_t* dst, int dstr, int blockWidth, int blockHeight );
template void abs_ref<int16_t, uint16_t>(   const int16_t* src, int sstr, uint16_t* dst, int dstr, int blockWidth, int blockHeight );
template void abs_ref<int32_t, uint32_t>(   const int32_t* src, int sstr, uint32_t* dst, int dstr, int blockWidth, int blockHeight );

template void absdiff_ref<unsigned char>(   const unsigned char* src0, int sstr0, const unsigned char* src1, int sstr1,
											unsigned char* dst,  int dstr, int blockWidth, int blockHeight );
template void absdiff_ref<unsigned short>(  const unsigned short* src0, int sstr0, const unsigned short* src1, int sstr1,
											unsigned short* dst,  int dstr, int blockWidth, int blockHeight );
template void absdiff_ref<unsigned int>(    const unsigned int* src0, int sstr0, const unsigned int* src1, int sstr1,
											unsigned int* dst,  int dstr, int blockWidth, int blockHeight );
template void absdiff_ref<char>(            const char* src0, int sstr0, const char* src1, int sstr1,
											char* dst,  int dstr, int blockWidth, int blockHeight );
template void absdiff_ref<short>(           const short* src0, int sstr0, const short* src1, int sstr1,
											short* dst,  int dstr, int blockWidth, int blockHeight );
template void absdiff_ref<int>(             const int* src0, int sstr0, const int* src1, int sstr1,
											int* dst,  int dstr, int blockWidth, int blockHeight );
											 
template void accumulate_ref<unsigned char>(const unsigned char* src0, int sstr0, const unsigned char* src1, int sstr1,
											unsigned char* dst,  int dstr, int blockWidth, int blockHeight );
template void accumulate_ref<unsigned short>(const unsigned short* src0, int sstr0, const unsigned short* src1, int sstr1,
											unsigned short* dst,  int dstr, int blockWidth, int blockHeight );
template void accumulate_ref<unsigned int>(	const unsigned int* src0, int sstr0, const unsigned int* src1, int sstr1,
											unsigned int* dst,  int dstr, int blockWidth, int blockHeight );
template void accumulate_ref<char>(         const char* src0, int sstr0, const char* src1, int sstr1,
											char* dst,  int dstr, int blockWidth, int blockHeight );
template void accumulate_ref<short>(        const short* src0, int sstr0, const short* src1, int sstr1,
											short* dst,  int dstr, int blockWidth, int blockHeight );
template void accumulate_ref<int>(          const int* src0, int sstr0, const int* src1, int sstr1,
											int* dst,  int dstr, int blockWidth, int blockHeight );
template void accumulate_ref<unsigned char, short>( const unsigned char* src0, int sstr0, const unsigned char* src1, int sstr1,
                                              short* dst,  int dstr, int blockWidth, int blockHeight );											

template void accumulate_squared_ref<unsigned char>(const unsigned char* src0, int sstr0, const unsigned char* src1, int sstr1,
                                             unsigned char* dst,  int dstr, int blockWidth, int blockHeight, unsigned char scale );
template void accumulate_squared_ref<unsigned short>(const unsigned short* src0, int sstr0, const unsigned short* src1, int sstr1,
                                             unsigned short* dst,  int dstr, int blockWidth, int blockHeight, unsigned char scale );
template void accumulate_squared_ref<unsigned int>(const unsigned int* src0, int sstr0, const unsigned int* src1, int sstr1,
                                             unsigned int* dst,  int dstr, int blockWidth, int blockHeight, unsigned char scale );
template void accumulate_squared_ref<char>(const char* src0, int sstr0, const char* src1, int sstr1,
                                             char* dst,  int dstr, int blockWidth, int blockHeight, unsigned char scale );
template void accumulate_squared_ref<short>(const short* src0, int sstr0, const short* src1, int sstr1,
                                             short* dst,  int dstr, int blockWidth, int blockHeight, unsigned char scale );
template void accumulate_squared_ref<int>(const int* src0, int sstr0, const int* src1, int sstr1,
                                             int* dst,  int dstr, int blockWidth, int blockHeight, unsigned char scale );
template void accumulate_squared_ref<unsigned char, short>( const unsigned char* src0, int sstr0, const unsigned char* src1, int sstr1,
                                             short* dst,  int dstr, int blockWidth, int blockHeight, unsigned char scale );												 
											
template void accumulate_weighted_ref<unsigned char>(const unsigned char* src0, int sstr0, const unsigned char* src1, int sstr1,
                                             unsigned char* dst,  int dstr, int blockWidth, int blockHeight, unsigned char alpha );
template void accumulate_weighted_ref<unsigned short>(const unsigned short* src0, int sstr0, const unsigned short* src1, int sstr1,
                                             unsigned short* dst,  int dstr, int blockWidth, int blockHeight, unsigned char alpha );
template void accumulate_weighted_ref<unsigned int>(const unsigned int* src0, int sstr0, const unsigned int* src1, int sstr1,
                                             unsigned int* dst,  int dstr, int blockWidth, int blockHeight, unsigned char alpha );
template void accumulate_weighted_ref<char>( const char* src0, int sstr0, const char* src1, int sstr1,
                                             char* dst,  int dstr, int blockWidth, int blockHeight, unsigned char alpha );
template void accumulate_weighted_ref<short>(const short* src0, int sstr0, const short* src1, int sstr1,
                                             short* dst,  int dstr, int blockWidth, int blockHeight, unsigned char alpha );
template void accumulate_weighted_ref<int>(	 const int* src0, int sstr0, const int* src1, int sstr1,
                                             int* dst,  int dstr, int blockWidth, int blockHeight, unsigned char alpha );
                                                                                        
template void add_ref<unsigned char>(        const unsigned char* src0, int sstr0, const unsigned char* src1, int sstr1,
                                             unsigned char* dst,  int dstr, int blockWidth, int blockHeight );
template void add_ref<unsigned short>(       const unsigned short* src0, int sstr0, const unsigned short* src1, int sstr1,
                                             unsigned short* dst,  int dstr, int blockWidth, int blockHeight );
template void add_ref<unsigned int>(         const unsigned int* src0, int sstr0, const unsigned int* src1, int sstr1,
                                             unsigned int* dst,  int dstr, int blockWidth, int blockHeight );
template void add_ref<char>(                 const char* src0, int sstr0, const char* src1, int sstr1,
                                             char* dst,  int dstr, int blockWidth, int blockHeight );
template void add_ref<short>(                const short* src0, int sstr0, const short* src1, int sstr1,
                                             short* dst,  int dstr, int blockWidth, int blockHeight );
template void add_ref<int>(                  const int* src0, int sstr0, const int* src1, int sstr1,
                                             int* dst,  int dstr, int blockWidth, int blockHeight );

template void and_ref<unsigned char>(        const unsigned char* src0, int sstr0, const unsigned char* src1, int sstr1,
                                             unsigned char* dst,  int dstr, int blockWidth, int blockHeight );
template void and_ref<unsigned short>(       const unsigned short* src0, int sstr0, const unsigned short* src1, int sstr1,
                                             unsigned short* dst,  int dstr, int blockWidth, int blockHeight );
template void and_ref<unsigned int>(         const unsigned int* src0, int sstr0, const unsigned int* src1, int sstr1,
                                             unsigned int* dst,  int dstr, int blockWidth, int blockHeight );
template void and_ref<char>(                 const char* src0, int sstr0, const char* src1, int sstr1,
                                             char* dst,  int dstr, int blockWidth, int blockHeight );
template void and_ref<short>(                const short* src0, int sstr0, const short* src1, int sstr1,
                                             short* dst,  int dstr, int blockWidth, int blockHeight );
template void and_ref<int>(                  const int* src0, int sstr0, const int* src1, int sstr1,
                                             int* dst,  int dstr, int blockWidth, int blockHeight );
                                         
template void clz_ref<uint8_t, uint8_t>(     uint8_t* src, int sstr, uint8_t* dst, int dstr, int blockWidth, int blockHeight );                                        
template void clz_ref<int8_t, uint8_t>(      int8_t* src, int sstr, uint8_t* dst, int dstr, int blockWidth, int blockHeight );
template void clz_ref<uint16_t, uint8_t>(    uint16_t* src, int sstr, uint8_t* dst, int dstr, int blockWidth, int blockHeight );
template void clz_ref<int16_t, uint8_t>(     int16_t* src, int sstr, uint8_t* dst, int dstr, int blockWidth, int blockHeight );

template void magnitude_ref<short, unsigned short>( const short* src0, int sstr0, const short* src1, int sstr1,
                                             unsigned short* dst,  int dstr, int blockWidth, int blockHeight );                                          
                                             
template void not_ref<unsigned char>(        const unsigned char* src0, int sstr0,
                                             unsigned char* dst,  int dstr, int blockWidth, int blockHeight );
template void not_ref<unsigned short>(       const unsigned short* src0, int sstr0,
                                             unsigned short* dst,  int dstr, int blockWidth, int blockHeight );
template void not_ref<unsigned int>(         const unsigned int* src0, int sstr0,
                                             unsigned int* dst,  int dstr, int blockWidth, int blockHeight );
template void not_ref<char>(                 const char* src0, int sstr0,
                                             char* dst,  int dstr, int blockWidth, int blockHeight );
template void not_ref<short>(                const short* src0, int sstr0,
                                             short* dst,  int dstr, int blockWidth, int blockHeight );
template void not_ref<int>(                  const int* src0, int sstr0,
                                             int* dst,  int dstr, int blockWidth, int blockHeight );

template void or_ref<unsigned char>(         const unsigned char* src0, int sstr0, const unsigned char* src1, int sstr1,
                                             unsigned char* dst,  int dstr, int blockWidth, int blockHeight );
template void or_ref<unsigned short>(        const unsigned short* src0, int sstr0, const unsigned short* src1, int sstr1,
                                             unsigned short* dst,  int dstr, int blockWidth, int blockHeight );
template void or_ref<unsigned int>(          const unsigned int* src0, int sstr0, const unsigned int* src1, int sstr1,
                                             unsigned int* dst,  int dstr, int blockWidth, int blockHeight );
template void or_ref<char>(                  const char* src0, int sstr0, const char* src1, int sstr1,
                                             char* dst,  int dstr, int blockWidth, int blockHeight );
template void or_ref<short>(                 const short* src0, int sstr0, const short* src1, int sstr1,
                                             short* dst,  int dstr, int blockWidth, int blockHeight );
template void or_ref<int>(                   const int* src0, int sstr0, const int* src1, int sstr1,
                                             int* dst,  int dstr, int blockWidth, int blockHeight );

template void sub_ref<unsigned char, short>( const unsigned char* src0, int sstr0, const unsigned char* src1, int sstr1,
                                             short* dst,  int dstr, int blockWidth, int blockHeight );
template void sub_ref<short, short>(         const short* src0, int sstr0, const short* src1, int sstr1,
                                             short* dst,  int dstr, int blockWidth, int blockHeight );

template void threshold_ref<unsigned char>(  const unsigned char* src0, int sstr0, unsigned int threshold,
                                             unsigned char* dst,  int dstr, int blockWidth, int blockHeight );
template void threshold_ref<unsigned short>( const unsigned short* src0, int sstr0, unsigned int threshold,
                                             unsigned char* dst,  int dstr, int blockWidth, int blockHeight );
template void threshold_ref<unsigned int>(   const unsigned int* src0, int sstr0, unsigned int threshold,
                                             unsigned char* dst,  int dstr, int blockWidth, int blockHeight );
template void threshold_ref<char>(           const char* src0, int sstr0, unsigned int threshold,
                                             unsigned char* dst,  int dstr, int blockWidth, int blockHeight );
template void threshold_ref<short>(          const short* src0, int sstr0, unsigned int threshold,
                                             unsigned char* dst,  int dstr, int blockWidth, int blockHeight );
template void threshold_ref<int>(            const int* src0, int sstr0, unsigned int threshold,
                                             unsigned char* dst,  int dstr, int blockWidth, int blockHeight );

template void xor_ref<unsigned char>(        const unsigned char* src0, int sstr0, const unsigned char* src1, int sstr1,
                                             unsigned char* dst,  int dstr, int blockWidth, int blockHeight );
template void xor_ref<unsigned short>(       const unsigned short* src0, int sstr0, const unsigned short* src1, int sstr1,
                                             unsigned short* dst,  int dstr, int blockWidth, int blockHeight );
template void xor_ref<unsigned int>(         const unsigned int* src0, int sstr0, const unsigned int* src1, int sstr1,
                                             unsigned int* dst,  int dstr, int blockWidth, int blockHeight );
template void xor_ref<char>(                 const char* src0, int sstr0, const char* src1, int sstr1,
                                             char* dst,  int dstr, int blockWidth, int blockHeight );
template void xor_ref<short>(                const short* src0, int sstr0, const short* src1, int sstr1,
                                             short* dst,  int dstr, int blockWidth, int blockHeight );
template void xor_ref<int>(                  const int* src0, int sstr0, const int* src1, int sstr1,
                                             int* dst,  int dstr, int blockWidth, int blockHeight );

