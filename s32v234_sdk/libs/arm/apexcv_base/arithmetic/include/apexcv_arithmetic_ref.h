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
*  \file apexcv_arithmetic_ref.hpp
*  \brief Reference code for arithmetic kernels
***********************************************************************************/

#ifndef _APEXCV_ARITHMETIC_REF_HPP_
#define _APEXCV_ARITHMETIC_REF_HPP_

template <typename S, typename D>
void abs_ref( const S* src, int sstr, 
			        D* dst,  int dstr, 
			  int blockWidth, int blockHeight );
   
template <typename D>
void absdiff_ref( const D* src0, int sstr0, 
                  const D* src1, int sstr1,
                  D* dst,  int dstr, 
                  int blockWidth, int blockHeight );
                     
template <typename S, typename D>
void accumulate_ref (const S* src0, int sstr0,
					 const S* src1, int sstr1,
					 D* dst, int dstr,
					 int blockWidth, int blockHeight );
					 
template <typename S, typename D>
void accumulate_squared_ref( const S* src0, int sstr0, 
                             const S* src1, int sstr1,
                             D* dst,  int dstr, 
                             int blockWidth, int blockHeight,
                             unsigned char scale );
					 
template <typename D>
void accumulate_weighted_ref( const D* src0, int sstr0, 
                              const D* src1, int sstr1,
                              D* dst,  int dstr, 
                              int blockWidth, int blockHeight,
                              unsigned char alpha );

template <typename D>                                
void add_ref( const D* src0, int sstr0, 
              const D* src1, int sstr1,
              D* dst,  int dstr, 
              int blockWidth, int blockHeight );                   

template <typename D>                                     
void and_ref( const D* src0, int sstr0, 
              const D* src1, int sstr1,
              D* dst,  int dstr, 
              int blockWidth, int blockHeight );   
              
template <typename S, typename D>
void clz_ref( S* src, int sstr, 
              D* dst, int dstr, 
			     int blockWidth, int blockHeight );
              
template <typename S, typename D>                                     
void magnitude_ref( const S* src0, int sstr0, 
                    const S* src1, int sstr1,
                          D* dst,  int dstr, 
                   int blockWidth, int blockHeight );     
              
template <typename D>            
void not_ref( const D* src0, int sstr0, 
              D* dst,  int dstr, 
              int blockWidth, int blockHeight );                      
       
template <typename D>       
void or_ref( const D* src0, int sstr0, 
             const D* src1, int sstr1,
             D* dst,  int dstr, 
             int blockWidth, int blockHeight );             

template <typename S, typename D>       
void sub_ref( const S* src0, int sstr0, 
              const S* src1, int sstr1,
              D* dst,  int dstr, 
              int blockWidth, int blockHeight );      

template <typename D>       
void threshold_ref( const D* src0, int sstr0, 
                    unsigned int threshold,
                    unsigned char* dst,  int dstr, 
                    int blockWidth, int blockHeight );   

template <typename D>       
void xor_ref( const D* src0, int sstr0, 
              const D* src1, int sstr1,
              D* dst,  int dstr, 
              int blockWidth, int blockHeight );
              
#endif /* _APEXCV_ARITHMETIC_REF_HPP_ */
