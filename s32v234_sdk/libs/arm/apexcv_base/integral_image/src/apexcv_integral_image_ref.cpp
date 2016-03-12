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
*  \file apexcv_integral_image_ref.cpp
*  \brief Reference code for integral image kernel
***********************************************************************************/

#include <stdint.h>

#include <apexcv_integral_image_ref.h>

void integral_image_ref(uint32_t* dst, const uint8_t* src, int ss, int sw, int sh)
{ 
	uint32_t *d = dst;
	uint8_t *s = (uint8_t *)src;
	for(int y = 0; y < sh; ++y) 
	{
		d[0] = s[0];
		for(int x = 1; x < sw; ++x) 
		{
			d[x] = d[x-1] + s[x];
		}
		
		d += ss;
		s += ss;
	}

  d = dst;
	s = (uint8_t *)src;
	d += ss;
	s += ss;
	
	for (int y=1; y<sh; ++y)
	{
		for (int x=0; x<sw; ++x)
		{
			d[x] = d[x - ss] + d[x];
		}

		d += ss;
		s += ss;
	}
	
}
