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
*  \file apu_filter.c
*  \brief APU filter kernels.
***********************************************************************************/

#include "apu_filter_bilateral_impl.cpp"
#include "apu_filter_box_impl.cpp"
#include "apu_filter_box_ht_impl.cpp"
#include "apu_filter_centralderivatives_ht_impl.cpp"
#include "apu_filter_gaussian_impl.cpp"
#include "apu_filter_generic_impl.cpp"
#include "apu_filter_generic_ht_impl.cpp"
#include "apu_filter_median_impl.cpp"
#include "apu_filter_morph_impl.cpp"
#include "apu_filter_prewitt_impl.cpp"
#include "apu_filter_separable_ht_impl.cpp"
#include "apu_filter_sobel_impl.cpp"
#include "apu_filter_sobel_ht_impl.cpp"