
#ifndef _APU_ROTATE_180_H_
#define _APU_ROTATE_180_H_

#include <stdint.h>

#include "stringify_macros.h"

#define ROTATE_K			apu_rotate_180
#define ROTATE_KN			XSTR(ROTATE_K)

#define ROTATE_KN_IN "INPUT"
#define ROTATE_KN_OUT "OUTPUT"

#ifdef APEX2_EMULATE 
#include "apu_lib.hpp" // if using the APU emulation library
using namespace APEX2;

//extern KERNEL_INFO _kernel_info_rotate_180;
extKernelInfoDecl(ROTATE_K);
void ROTATE_K(kernel_io_desc lIn, kernel_io_desc lOut);


#endif




#endif // _APU_rotate_180_IMPL_H_
