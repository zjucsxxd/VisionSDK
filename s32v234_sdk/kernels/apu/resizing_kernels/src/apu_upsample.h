#ifndef _APU_UPSAMPLE_H
#define _APU_UPSAMPLE_H

#include "stringify_macros.h"

#define UPSAMPLE_K			apu_upsample
#define UPSAMPLE_KN			XSTR(UPSAMPLE_K)

#define UPSAMPLE_KN_IN	"INPUT_0"
#define UPSAMPLE_KN_OUT	"OUTPUT_0"

#ifdef APEX2_EMULATE

//extern KERNEL_INFO _kernel_info_upsample;
extKernelInfoDecl(UPSAMPLE_K);
void UPSAMPLE_K(kernel_io_desc lIn0, kernel_io_desc lOut0);

extKernelInfoDecl(UPSAMPLE_16u_K);
void UPSAMPLE_16u_K(kernel_io_desc lIn0, kernel_io_desc lOut0);

extKernelInfoDecl(UPSAMPLE_GAUSS_K);
void UPSAMPLE_GAUSS_K(kernel_io_desc lIn0, kernel_io_desc lOut0);

#endif


#endif
