/******************************************************************************
 *  (C) Copyright CogniVue Corporation. 2013 All right reserved.
 * 
 *  Confidential Information
 *
 *  All parts of the CogniVue Program Source are protected by copyright law
 *  and all rights are reserved.
 *  This documentation may not, in whole or in part, be copied, photocopied,
 *  reproduced, translated, or reduced to any electronic medium or machine
 *  readable form without prior consent, in writing, from CogniVue.
 *
 *  Created by: Ramin Azarmehr
 ******************************************************************************/

#ifndef _APU_RESIZE_UTILS_H_
#define _APU_RESIZE_UTILS_H_

#include "apu_resize_definitions.h"

/*! Only for debug on simulator. */
#ifdef __APU_DEBUG__ 
#include "apu_acf_debug_utils.h"
#endif // __APU_DEBUG__ 


#ifdef APEX2_EMULATE
#include "acf_kernel.hpp" // if using the ACF emulation library
using namespace APEX2;
#endif


#include "stringify_macros.h"

#define RESZ_VERT_K		resize_vertical
#define RESZ_VERT_KN	XSTR(RESZ_VERT_K)

#define RESZ_VERT_KN_IN		"ReszVert_In"
#define RESZ_VERT_KN_OUT	"ReszVert_Out"
#define RESZ_VERT_KN_DESCR	"ReszVert_Descr"

#ifdef APEX2_EMULATE
extKernelInfoDecl(RESZ_VERT_K);
void RESZ_VERT_K(kernel_io_desc lIn0, kernel_io_desc lOut0);
#else
#include "apu2_kernel_port.h"
///// ACF wrapper for apu_resize_integer
void resize_vertical(kernel_io_desc input_image, kernel_io_desc output_image,
	kernel_io_desc rsz_desc);

#endif //APEX2_EMULATE

#endif /* _APU_RESIZE_UTILS_H_ */
