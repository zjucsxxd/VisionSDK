/*****************************************************************************
*
* Freescale Confidential Proprietary
*
* Copyright (c) 2013 Freescale Semiconductor;
* All Rights Reserved
*
*****************************************************************************
*
* THIS SOFTWARE IS PROVIDED BY FREESCALE "AS IS" AND ANY EXPRESSED OR
* IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
* OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
* IN NO EVENT SHALL FREESCALE OR ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
* INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
* (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
* SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
* HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
* STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
* IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
* THE POSSIBILITY OF SUCH DAMAGE.
*
****************************************************************************/

//vector cycle database
//operators with both binary and unary versions have to include "_binary" in their name


#define APEX2_CU 1
// other defines could be activated
//#define APEX4_CU 1
//#define APEX5_CU 1

#ifdef APEX2_CU
#define CLOCK_FREQ 500000000.0f
#else 
#ifdef APEX4_CU
#define CLOCK_FREQ 600000000.0f
#else // APEX5_CU is defined
#define CLOCK_FREQ 800000000.0f
#endif
#endif

///////////////////////////////////////////////////
//  vec08u
///////////////////////////////////////////////////

CYCLES_ENTRY("vec08u_binary_=", 1)

CYCLES_ENTRY("vec08u_binary_+",   1)
CYCLES_ENTRY("vec08u_binary_-",   1)
CYCLES_ENTRY("vec08u_binary_*",   1)
CYCLES_ENTRY("vec08u_binary_/",   1)
CYCLES_ENTRY("vec08u_binary_%",   1)

CYCLES_ENTRY("vec08u_binary_^",   1)
CYCLES_ENTRY("vec08u_binary_|",   1)
CYCLES_ENTRY("vec08u_binary_&",   1)

CYCLES_ENTRY("vec08u_binary_==",  1)
CYCLES_ENTRY("vec08u_binary_!=",  1)
CYCLES_ENTRY("vec08u_binary_>",   1)
CYCLES_ENTRY("vec08u_binary_<",   1)
CYCLES_ENTRY("vec08u_binary_>=",  1)
CYCLES_ENTRY("vec08u_binary_<=",  1)

CYCLES_ENTRY("vec08u_binary_>>",  1)
CYCLES_ENTRY("vec08u_binary_<<",  1)

CYCLES_ENTRY("vec08u_binary_+=",  1)
CYCLES_ENTRY("vec08u_binary_-=",  1)
CYCLES_ENTRY("vec08u_binary_*=",  1)
CYCLES_ENTRY("vec08u_binary_/=",  1)
CYCLES_ENTRY("vec08u_binary_%=",  1)
CYCLES_ENTRY("vec08u_binary_&=",  1)
CYCLES_ENTRY("vec08u_binary_|=",  1)
CYCLES_ENTRY("vec08u_binary_^=",  1)

CYCLES_ENTRY("vec08u_binary_<<=", 1)
CYCLES_ENTRY("vec08u_binary_>>=", 1)

CYCLES_ENTRY("vec08u_-",  1)
CYCLES_ENTRY("vec08u_+",  1)
CYCLES_ENTRY("vec08u_~",  1)

CYCLES_ENTRY("vec08u_++", 1)
CYCLES_ENTRY("vec08u_--", 1)

CYCLES_ENTRY("vec08u_--", 1)

CYCLES_ENTRY("vec08u_broadcast", 1)

CYCLES_ENTRY("vec08u_vget", 1)
CYCLES_ENTRY("vec08u_vput", 1)
CYCLES_ENTRY("vec08u_vmr",  1)
CYCLES_ENTRY("vec08u_vml",  1)
CYCLES_ENTRY("vec08u_vmsl", 1)
CYCLES_ENTRY("vec08u_vmsr", 1)
CYCLES_ENTRY("vec08u_vmrl", 1)
CYCLES_ENTRY("vec08u_vmrr", 1)

CYCLES_ENTRY("vec08u_vload",  1)
CYCLES_ENTRY("vec08u_vstore", 1)

CYCLES_ENTRY("vec08u_vadd",  1)
CYCLES_ENTRY("vec08u_vaddx", 1)
CYCLES_ENTRY("vec08u_vsub",  1)
CYCLES_ENTRY("vec08u_vsubx", 1)
CYCLES_ENTRY("vec08u_vmul",  1)

CYCLES_ENTRY("vec08u_vand",  1)
CYCLES_ENTRY("vec08u_vor",   1)
CYCLES_ENTRY("vec08u_vxor",  1)
CYCLES_ENTRY("vec08u_vnot",  1)

CYCLES_ENTRY("vec08u_vcomplement", 1)

CYCLES_ENTRY("vec08u_vsl",  1)
CYCLES_ENTRY("vec08u_vsr",  1)
CYCLES_ENTRY("vec08u_vsll", 1)
CYCLES_ENTRY("vec08u_vsra", 1)
CYCLES_ENTRY("vec08u_vsrl", 1)

CYCLES_ENTRY("vec08u_vseq", 1)
CYCLES_ENTRY("vec08u_vsne", 1)
CYCLES_ENTRY("vec08u_vsge", 1)
CYCLES_ENTRY("vec08u_vsgt", 1)
CYCLES_ENTRY("vec08u_vsge", 1)
CYCLES_ENTRY("vec08u_vsle", 1)
CYCLES_ENTRY("vec08u_vslt", 1)

CYCLES_ENTRY("vec08u_vselect", 1)
CYCLES_ENTRY("vec08u_vswap",   1)
CYCLES_ENTRY("vec08u_vabs",    1)

CYCLES_ENTRY("vec08u_special_shift", 1)
CYCLES_ENTRY("vec08u_special_multiplication", 1)

///////////////////////////////////////////////////
//  vec08s
///////////////////////////////////////////////////

CYCLES_ENTRY("vec08s_binary_=", 1)

CYCLES_ENTRY("vec08s_binary_+", 1)
CYCLES_ENTRY("vec08s_binary_-", 1)
CYCLES_ENTRY("vec08s_binary_*", 1)
CYCLES_ENTRY("vec08s_binary_/", 1)
CYCLES_ENTRY("vec08s_binary_%", 1)

CYCLES_ENTRY("vec08s_binary_^", 1)
CYCLES_ENTRY("vec08s_binary_|", 1)
CYCLES_ENTRY("vec08s_binary_&", 1)

CYCLES_ENTRY("vec08s_binary_==", 1)
CYCLES_ENTRY("vec08s_binary_!=", 1)
CYCLES_ENTRY("vec08s_binary_>", 1)
CYCLES_ENTRY("vec08s_binary_<", 1)
CYCLES_ENTRY("vec08s_binary_>=", 1)
CYCLES_ENTRY("vec08s_binary_<=", 1)

CYCLES_ENTRY("vec08s_binary_>>", 1)
CYCLES_ENTRY("vec08s_binary_<<", 1)

CYCLES_ENTRY("vec08s_binary_+=", 1)
CYCLES_ENTRY("vec08s_binary_-=", 1)
CYCLES_ENTRY("vec08s_binary_*=", 1)
CYCLES_ENTRY("vec08s_binary_/=", 1)
CYCLES_ENTRY("vec08s_binary_%=", 1)
CYCLES_ENTRY("vec08s_binary_&=", 1)
CYCLES_ENTRY("vec08s_binary_|=", 1)
CYCLES_ENTRY("vec08s_binary_^=", 1)

CYCLES_ENTRY("vec08s_binary_<<=", 1)
CYCLES_ENTRY("vec08s_binary_>>=", 1)

CYCLES_ENTRY("vec08s_-", 1)
CYCLES_ENTRY("vec08s_+", 1)
CYCLES_ENTRY("vec08s_~", 1)

CYCLES_ENTRY("vec08s_++", 1)
CYCLES_ENTRY("vec08s_--", 1)

CYCLES_ENTRY("vec08s_--", 1)

CYCLES_ENTRY("vec08s_broadcast", 1)

CYCLES_ENTRY("vec08s_vget", 1)
CYCLES_ENTRY("vec08s_vput", 1)
CYCLES_ENTRY("vec08s_vmr", 1)
CYCLES_ENTRY("vec08s_vml", 1)
CYCLES_ENTRY("vec08s_vmsl", 1)
CYCLES_ENTRY("vec08s_vmsr", 1)
CYCLES_ENTRY("vec08s_vmrl", 1)
CYCLES_ENTRY("vec08s_vmrr", 1)

CYCLES_ENTRY("vec08s_vload", 1)
CYCLES_ENTRY("vec08s_vstore", 1)

CYCLES_ENTRY("vec08s_vadd", 1)
CYCLES_ENTRY("vec08s_vaddx", 1)
CYCLES_ENTRY("vec08s_vsub", 1)
CYCLES_ENTRY("vec08s_vsubx", 1)
CYCLES_ENTRY("vec08s_vmul", 1)

CYCLES_ENTRY("vec08s_vand", 1)
CYCLES_ENTRY("vec08s_vor", 1)
CYCLES_ENTRY("vec08s_vxor", 1)
CYCLES_ENTRY("vec08s_vnot", 1)

CYCLES_ENTRY("vec08s_vcomplement", 1)

CYCLES_ENTRY("vec08s_vsl", 1)
CYCLES_ENTRY("vec08s_vsr", 1)
CYCLES_ENTRY("vec08s_vsll", 1)
CYCLES_ENTRY("vec08s_vsra", 1)
CYCLES_ENTRY("vec08s_vsrl", 1)

CYCLES_ENTRY("vec08s_vseq", 1)
CYCLES_ENTRY("vec08s_vsne", 1)
CYCLES_ENTRY("vec08s_vsge", 1)
CYCLES_ENTRY("vec08s_vsgt", 1)
CYCLES_ENTRY("vec08s_vsge", 1)
CYCLES_ENTRY("vec08s_vsle", 1)
CYCLES_ENTRY("vec08s_vslt", 1)

CYCLES_ENTRY("vec08s_vselect", 1)
CYCLES_ENTRY("vec08s_vswap", 1)
CYCLES_ENTRY("vec08s_vabs", 1)

CYCLES_ENTRY("vec08s_special_shift", 1)
CYCLES_ENTRY("vec08s_special_multiplication", 1)

///////////////////////////////////////////////////
//  vec16u
///////////////////////////////////////////////////


#ifdef APEX2_CU
CYCLES_ENTRY("vec16u_binary_*", 8)
CYCLES_ENTRY("vec16u_binary_/", 50)
CYCLES_ENTRY("vec16u_binary_%", 50)

CYCLES_ENTRY("vec16u_binary_*=", 8)
CYCLES_ENTRY("vec16u_binary_/=", 50)
CYCLES_ENTRY("vec16u_binary_%=", 50)

CYCLES_ENTRY("vec16u_vmul", 8)
CYCLES_ENTRY("vec16u_special_multiplication", 8)


#else
CYCLES_ENTRY("vec16u_binary_*", 1)
CYCLES_ENTRY("vec16u_binary_/", 25)
CYCLES_ENTRY("vec16u_binary_%", 25)

CYCLES_ENTRY("vec16u_binary_*=", 1)
CYCLES_ENTRY("vec16u_binary_/=", 25)
CYCLES_ENTRY("vec16u_binary_%=", 25)

CYCLES_ENTRY("vec16u_vmul", 1)
CYCLES_ENTRY("vec16u_special_multiplication", 8)

#endif

CYCLES_ENTRY("vec16u_binary_=", 1)

CYCLES_ENTRY("vec16u_binary_+", 1)
CYCLES_ENTRY("vec16u_binary_-", 1)

CYCLES_ENTRY("vec16u_binary_^", 1)
CYCLES_ENTRY("vec16u_binary_|", 1)
CYCLES_ENTRY("vec16u_binary_&", 1)

CYCLES_ENTRY("vec16u_binary_==", 1)
CYCLES_ENTRY("vec16u_binary_!=", 1)
CYCLES_ENTRY("vec16u_binary_>", 1)
CYCLES_ENTRY("vec16u_binary_<", 1)
CYCLES_ENTRY("vec16u_binary_>=", 1)
CYCLES_ENTRY("vec16u_binary_<=", 1)

CYCLES_ENTRY("vec16u_binary_>>", 1)
CYCLES_ENTRY("vec16u_binary_<<", 1)

CYCLES_ENTRY("vec16u_binary_+=", 1)
CYCLES_ENTRY("vec16u_binary_-=", 1)


CYCLES_ENTRY("vec16u_binary_&=", 1)
CYCLES_ENTRY("vec16u_binary_|=", 1)
CYCLES_ENTRY("vec16u_binary_^=", 1)

CYCLES_ENTRY("vec16u_binary_<<=", 1)
CYCLES_ENTRY("vec16u_binary_>>=", 1)

CYCLES_ENTRY("vec16u_-", 1)
CYCLES_ENTRY("vec16u_+", 1)
CYCLES_ENTRY("vec16u_~", 1)

CYCLES_ENTRY("vec16u_++", 1)
CYCLES_ENTRY("vec16u_--", 1)

CYCLES_ENTRY("vec16u_--", 1)

CYCLES_ENTRY("vec16u_broadcast", 1)

CYCLES_ENTRY("vec16u_vget", 1)
CYCLES_ENTRY("vec16u_vput", 1)
CYCLES_ENTRY("vec16u_vmr", 1)
CYCLES_ENTRY("vec16u_vml", 1)
CYCLES_ENTRY("vec16u_vmsl", 1)
CYCLES_ENTRY("vec16u_vmsr", 1)
CYCLES_ENTRY("vec16u_vmrl", 1)
CYCLES_ENTRY("vec16u_vmrr", 1)

CYCLES_ENTRY("vec16u_vload", 1)
CYCLES_ENTRY("vec16u_vstore", 1)

CYCLES_ENTRY("vec16u_vadd", 1)
CYCLES_ENTRY("vec16u_vaddx",1)
CYCLES_ENTRY("vec16u_vsub", 1)
CYCLES_ENTRY("vec16u_vsubx", 1)


CYCLES_ENTRY("vec16u_vand", 1)
CYCLES_ENTRY("vec16u_vor", 1)
CYCLES_ENTRY("vec16u_vxor", 1)
CYCLES_ENTRY("vec16u_vnot", 1)

CYCLES_ENTRY("vec16u_vcomplement", 1)

CYCLES_ENTRY("vec16u_vsl", 1)
CYCLES_ENTRY("vec16u_vsr", 1)
CYCLES_ENTRY("vec16u_vsll", 1)
CYCLES_ENTRY("vec16u_vsra", 1)
CYCLES_ENTRY("vec16u_vsrl", 1)

CYCLES_ENTRY("vec16u_vseq", 1)
CYCLES_ENTRY("vec16u_vsne", 1)
CYCLES_ENTRY("vec16u_vsge", 1)
CYCLES_ENTRY("vec16u_vsgt", 1)
CYCLES_ENTRY("vec16u_vsge", 1)
CYCLES_ENTRY("vec16u_vsle", 1)
CYCLES_ENTRY("vec16u_vslt", 1)

CYCLES_ENTRY("vec16u_vselect", 1)
CYCLES_ENTRY("vec16u_vswap", 1)
CYCLES_ENTRY("vec16u_vabs", 1)

CYCLES_ENTRY("vec16u_special_shift", 1)





///////////////////////////////////////////////////
//  vec16s
///////////////////////////////////////////////////


#ifdef APEX2_CU
CYCLES_ENTRY("vec16s_binary_*", 8)
CYCLES_ENTRY("vec16s_binary_/", 50)
CYCLES_ENTRY("vec16s_binary_%", 50)

CYCLES_ENTRY("vec16s_binary_*=", 8)
CYCLES_ENTRY("vec16s_binary_/=", 50)
CYCLES_ENTRY("vec16s_binary_%=", 50)

CYCLES_ENTRY("vec16s_vmul", 8)
CYCLES_ENTRY("vec16s_special_multiplication", 8)


#else
CYCLES_ENTRY("vec16s_binary_*", 1)
CYCLES_ENTRY("vec16s_binary_/", 25)
CYCLES_ENTRY("vec16s_binary_%", 25)

CYCLES_ENTRY("vec16s_binary_*=", 1)
CYCLES_ENTRY("vec16s_binary_/=", 25)
CYCLES_ENTRY("vec16s_binary_%=", 25)

CYCLES_ENTRY("vec16s_vmul", 1)
CYCLES_ENTRY("vec16s_special_multiplication", 8)
#endif


CYCLES_ENTRY("vec16s_binary_=", 1)

CYCLES_ENTRY("vec16s_binary_+", 1)
CYCLES_ENTRY("vec16s_binary_-", 1)

CYCLES_ENTRY("vec16s_binary_^", 1)
CYCLES_ENTRY("vec16s_binary_|", 1)
CYCLES_ENTRY("vec16s_binary_&", 1)

CYCLES_ENTRY("vec16s_binary_==", 1)
CYCLES_ENTRY("vec16s_binary_!=", 1)
CYCLES_ENTRY("vec16s_binary_>", 1)
CYCLES_ENTRY("vec16s_binary_<", 1)
CYCLES_ENTRY("vec16s_binary_>=", 1)
CYCLES_ENTRY("vec16s_binary_<=", 1)

CYCLES_ENTRY("vec16s_binary_>>", 1)
CYCLES_ENTRY("vec16s_binary_<<", 1)

CYCLES_ENTRY("vec16s_binary_+=", 1)
CYCLES_ENTRY("vec16s_binary_-=", 1)

CYCLES_ENTRY("vec16s_binary_&=", 1)
CYCLES_ENTRY("vec16s_binary_|=", 1)
CYCLES_ENTRY("vec16s_binary_^=", 1)

CYCLES_ENTRY("vec16s_binary_<<=", 1)
CYCLES_ENTRY("vec16s_binary_>>=", 1)

CYCLES_ENTRY("vec16s_-", 1)
CYCLES_ENTRY("vec16s_+", 1)
CYCLES_ENTRY("vec16s_~", 1)

CYCLES_ENTRY("vec16s_++", 1)
CYCLES_ENTRY("vec16s_--", 1)

CYCLES_ENTRY("vec16s_--", 1)

CYCLES_ENTRY("vec16s_broadcast", 1)

CYCLES_ENTRY("vec16s_vget", 1)
CYCLES_ENTRY("vec16s_vput", 1)
CYCLES_ENTRY("vec16s_vmr", 1)
CYCLES_ENTRY("vec16s_vml", 1)
CYCLES_ENTRY("vec16s_vmsl", 1)
CYCLES_ENTRY("vec16s_vmsr", 1)
CYCLES_ENTRY("vec16s_vmrl", 1)
CYCLES_ENTRY("vec16s_vmrr", 1)

CYCLES_ENTRY("vec16s_vload", 1)
CYCLES_ENTRY("vec16s_vstore", 1)

CYCLES_ENTRY("vec16s_vadd", 1)
CYCLES_ENTRY("vec16s_vaddx", 1)
CYCLES_ENTRY("vec16s_vsub", 1)
CYCLES_ENTRY("vec16s_vsubx", 1)


CYCLES_ENTRY("vec16s_vand", 1)
CYCLES_ENTRY("vec16s_vor", 1)
CYCLES_ENTRY("vec16s_vxor", 1)
CYCLES_ENTRY("vec16s_vnot", 1)

CYCLES_ENTRY("vec16s_vcomplement", 1)

CYCLES_ENTRY("vec16s_vsl", 1)
CYCLES_ENTRY("vec16s_vsr", 1)
CYCLES_ENTRY("vec16s_vsll", 1)
CYCLES_ENTRY("vec16s_vsra", 1)
CYCLES_ENTRY("vec16s_vsrl", 1)

CYCLES_ENTRY("vec16s_vseq", 1)
CYCLES_ENTRY("vec16s_vsne", 1)
CYCLES_ENTRY("vec16s_vsge", 1)
CYCLES_ENTRY("vec16s_vsgt", 1)
CYCLES_ENTRY("vec16s_vsge", 1)
CYCLES_ENTRY("vec16s_vsle", 1)
CYCLES_ENTRY("vec16s_vslt", 1)

CYCLES_ENTRY("vec16s_vselect", 1)
CYCLES_ENTRY("vec16s_vswap", 1)
CYCLES_ENTRY("vec16s_vabs", 1)

CYCLES_ENTRY("vec16s_special_shift", 1)


///////////////////////////////////////////////////
//  vec32u
///////////////////////////////////////////////////

#ifdef APEX2_CU
CYCLES_ENTRY("vec32u_binary_*", 32)
CYCLES_ENTRY("vec32u_binary_/", 145)
CYCLES_ENTRY("vec32u_binary_%", 145)

CYCLES_ENTRY("vec32u_binary_*=", 32)
CYCLES_ENTRY("vec32u_binary_/=", 145)
CYCLES_ENTRY("vec32u_binary_%=", 145)

CYCLES_ENTRY("vec32u_vmul", 32)
CYCLES_ENTRY("vec32u_special_multiplication", 32)


#else
CYCLES_ENTRY("vec32u_binary_*", 2)
CYCLES_ENTRY("vec32u_binary_/", 50)
CYCLES_ENTRY("vec32u_binary_%", 50)

CYCLES_ENTRY("vec32u_binary_*=", 2)
CYCLES_ENTRY("vec32u_binary_/=", 50)
CYCLES_ENTRY("vec32u_binary_%=", 50)

CYCLES_ENTRY("vec32u_vmul", 2)
CYCLES_ENTRY("vec32u_special_multiplication", 2)
#endif

CYCLES_ENTRY("vec32u_binary_=", 1)

CYCLES_ENTRY("vec32u_binary_+",2)
CYCLES_ENTRY("vec32u_binary_-",2)

CYCLES_ENTRY("vec32u_binary_^", 1)
CYCLES_ENTRY("vec32u_binary_|", 1)
CYCLES_ENTRY("vec32u_binary_&", 1)

CYCLES_ENTRY("vec32u_binary_==", 1)
CYCLES_ENTRY("vec32u_binary_!=", 1)
CYCLES_ENTRY("vec32u_binary_>", 1)
CYCLES_ENTRY("vec32u_binary_<", 1)
CYCLES_ENTRY("vec32u_binary_>=", 1)
CYCLES_ENTRY("vec32u_binary_<=", 1)

CYCLES_ENTRY("vec32u_binary_>>",2)
CYCLES_ENTRY("vec32u_binary_<<",2)

CYCLES_ENTRY("vec32u_binary_+=",2)
CYCLES_ENTRY("vec32u_binary_-=",2)

CYCLES_ENTRY("vec32u_binary_&=", 1)
CYCLES_ENTRY("vec32u_binary_|=", 1)
CYCLES_ENTRY("vec32u_binary_^=", 1)

CYCLES_ENTRY("vec32u_binary_<<=",2)
CYCLES_ENTRY("vec32u_binary_>>=",2)

CYCLES_ENTRY("vec32u_-", 1)
CYCLES_ENTRY("vec32u_+", 1)
CYCLES_ENTRY("vec32u_~", 1)

CYCLES_ENTRY("vec32u_++", 1)
CYCLES_ENTRY("vec32u_--", 1)

CYCLES_ENTRY("vec32u_--", 1)

CYCLES_ENTRY("vec32u_broadcast", 1)

CYCLES_ENTRY("vec32u_vget", 1)
CYCLES_ENTRY("vec32u_vput", 1)
CYCLES_ENTRY("vec32u_vmr", 1)
CYCLES_ENTRY("vec32u_vml", 1)
CYCLES_ENTRY("vec32u_vmsl", 1)
CYCLES_ENTRY("vec32u_vmsr", 1)
CYCLES_ENTRY("vec32u_vmrl", 1)
CYCLES_ENTRY("vec32u_vmrr", 1)

CYCLES_ENTRY("vec32u_vload", 1)
CYCLES_ENTRY("vec32u_vstore", 1)

CYCLES_ENTRY("vec32u_vadd", 2)
CYCLES_ENTRY("vec32u_vaddx", 2)
CYCLES_ENTRY("vec32u_vsub", 2)
CYCLES_ENTRY("vec32u_vsubx", 2)

CYCLES_ENTRY("vec32u_vand", 1)
CYCLES_ENTRY("vec32u_vor", 1)
CYCLES_ENTRY("vec32u_vxor", 1)
CYCLES_ENTRY("vec32u_vnot", 1)

CYCLES_ENTRY("vec32u_vcomplement", 1)

CYCLES_ENTRY("vec32u_vsl", 1)
CYCLES_ENTRY("vec32u_vsr", 1)
CYCLES_ENTRY("vec32u_vsll", 1)
CYCLES_ENTRY("vec32u_vsra", 1)
CYCLES_ENTRY("vec32u_vsrl", 1)

CYCLES_ENTRY("vec32u_vseq", 1)
CYCLES_ENTRY("vec32u_vsne", 1)
CYCLES_ENTRY("vec32u_vsge", 1)
CYCLES_ENTRY("vec32u_vsgt", 1)
CYCLES_ENTRY("vec32u_vsge", 1)
CYCLES_ENTRY("vec32u_vsle", 1)
CYCLES_ENTRY("vec32u_vslt", 1)

CYCLES_ENTRY("vec32u_vselect", 1)
CYCLES_ENTRY("vec32u_vswap", 1)
CYCLES_ENTRY("vec32u_vabs", 1)

CYCLES_ENTRY("vec32u_special_shift", 2)


///////////////////////////////////////////////////
//  vec32s
///////////////////////////////////////////////////

#ifdef APEX2_CU
CYCLES_ENTRY("vec32s_binary_*", 32)
CYCLES_ENTRY("vec32s_binary_/", 145)
CYCLES_ENTRY("vec32s_binary_%", 145)

CYCLES_ENTRY("vec32s_binary_*=", 32)
CYCLES_ENTRY("vec32s_binary_/=", 145)
CYCLES_ENTRY("vec32s_binary_%=", 145)

CYCLES_ENTRY("vec32s_vmul", 32)
CYCLES_ENTRY("vec32s_special_multiplication", 32)


#else
CYCLES_ENTRY("vec32s_binary_*", 2)
CYCLES_ENTRY("vec32s_binary_/", 50)
CYCLES_ENTRY("vec32s_binary_%", 50)

CYCLES_ENTRY("vec32s_binary_*=", 2)
CYCLES_ENTRY("vec32s_binary_/=", 50)
CYCLES_ENTRY("vec32s_binary_%=", 50)

CYCLES_ENTRY("vec32s_vmul", 2)
CYCLES_ENTRY("vec32s_special_multiplication", 2)
#endif



CYCLES_ENTRY("vec32s_binary_=", 1)

CYCLES_ENTRY("vec32s_binary_+", 2)
CYCLES_ENTRY("vec32s_binary_-", 2)

CYCLES_ENTRY("vec32s_binary_^", 1)
CYCLES_ENTRY("vec32s_binary_|", 1)
CYCLES_ENTRY("vec32s_binary_&", 1)

CYCLES_ENTRY("vec32s_binary_==", 1)
CYCLES_ENTRY("vec32s_binary_!=", 1)
CYCLES_ENTRY("vec32s_binary_>", 1)
CYCLES_ENTRY("vec32s_binary_<", 1)
CYCLES_ENTRY("vec32s_binary_>=", 1)
CYCLES_ENTRY("vec32s_binary_<=", 1)

CYCLES_ENTRY("vec32s_binary_>>", 1)
CYCLES_ENTRY("vec32s_binary_<<", 1)

CYCLES_ENTRY("vec32s_binary_+=", 2)
CYCLES_ENTRY("vec32s_binary_-=", 2)

CYCLES_ENTRY("vec32s_binary_&=", 1)
CYCLES_ENTRY("vec32s_binary_|=", 1)
CYCLES_ENTRY("vec32s_binary_^=", 1)

CYCLES_ENTRY("vec32s_binary_<<=", 2)
CYCLES_ENTRY("vec32s_binary_>>=", 2)

CYCLES_ENTRY("vec32s_-", 1)
CYCLES_ENTRY("vec32s_+", 1)
CYCLES_ENTRY("vec32s_~", 1)

CYCLES_ENTRY("vec32s_++", 1)
CYCLES_ENTRY("vec32s_--", 1)

CYCLES_ENTRY("vec32s_--", 1)

CYCLES_ENTRY("vec32s_broadcast", 1)

CYCLES_ENTRY("vec32s_vget", 1)
CYCLES_ENTRY("vec32s_vput", 1)
CYCLES_ENTRY("vec32s_vmr", 1)
CYCLES_ENTRY("vec32s_vml", 1)
CYCLES_ENTRY("vec32s_vmsl", 1)
CYCLES_ENTRY("vec32s_vmsr", 1)
CYCLES_ENTRY("vec32s_vmrl", 1)
CYCLES_ENTRY("vec32s_vmrr", 1)

CYCLES_ENTRY("vec32s_vload", 1)
CYCLES_ENTRY("vec32s_vstore", 1)

CYCLES_ENTRY("vec32s_vadd", 2)
CYCLES_ENTRY("vec32s_vaddx", 2)
CYCLES_ENTRY("vec32s_vsub", 2)
CYCLES_ENTRY("vec32s_vsubx", 2)


CYCLES_ENTRY("vec32s_vand", 1)
CYCLES_ENTRY("vec32s_vor", 1)
CYCLES_ENTRY("vec32s_vxor", 1)
CYCLES_ENTRY("vec32s_vnot", 1)

CYCLES_ENTRY("vec32s_vcomplement", 1)

CYCLES_ENTRY("vec32s_vsl", 1)
CYCLES_ENTRY("vec32s_vsr", 1)
CYCLES_ENTRY("vec32s_vsll", 1)
CYCLES_ENTRY("vec32s_vsra", 1)
CYCLES_ENTRY("vec32s_vsrl", 1)

CYCLES_ENTRY("vec32s_vseq", 1)
CYCLES_ENTRY("vec32s_vsne", 1)
CYCLES_ENTRY("vec32s_vsge", 1)
CYCLES_ENTRY("vec32s_vsgt", 1)
CYCLES_ENTRY("vec32s_vsge", 1)
CYCLES_ENTRY("vec32s_vsle", 1)
CYCLES_ENTRY("vec32s_vslt", 1)

CYCLES_ENTRY("vec32s_vselect", 1)
CYCLES_ENTRY("vec32s_vswap", 1)
CYCLES_ENTRY("vec32s_vabs", 1)

CYCLES_ENTRY("vec32s_special_shift", 2)

///////////////////////////////////////////////////
//  vec08u
///////////////////////////////////////////////////
/* This is duplicated from above
CYCLES_ENTRY("vec08u_binary_+", 1)
CYCLES_ENTRY("vec08u_binary_-", 1)
CYCLES_ENTRY("vec08u_binary_*", 1)
CYCLES_ENTRY("vec08u_binary_/", 1)
CYCLES_ENTRY("vec08u_binary_%", 1)

CYCLES_ENTRY("vec08u_binary_^", 1)
CYCLES_ENTRY("vec08u_binary_|", 1)
CYCLES_ENTRY("vec08u_binary_&", 1)

CYCLES_ENTRY("vec08u_binary_==", 1)
CYCLES_ENTRY("vec08u_binary_!=", 1)
CYCLES_ENTRY("vec08u_binary_>", 1)
CYCLES_ENTRY("vec08u_binary_<", 1)
CYCLES_ENTRY("vec08u_binary_>=", 1)
CYCLES_ENTRY("vec08u_binary_<=", 1)

CYCLES_ENTRY("vec08u_binary_>>", 1)
CYCLES_ENTRY("vec08u_binary_<<", 1)

CYCLES_ENTRY("vec08u_binary_+=", 1)
CYCLES_ENTRY("vec08u_binary_-=", 1)
CYCLES_ENTRY("vec08u_binary_*=", 1)
CYCLES_ENTRY("vec08u_binary_/=", 1)
CYCLES_ENTRY("vec08u_binary_%=", 1)
CYCLES_ENTRY("vec08u_binary_&=", 1)
CYCLES_ENTRY("vec08u_binary_|=", 1)
CYCLES_ENTRY("vec08u_binary_^=", 1)

CYCLES_ENTRY("vec08u_binary_<<=", 1)
CYCLES_ENTRY("vec08u_binary_>>=", 1)

CYCLES_ENTRY("vec08u_-", 1)
CYCLES_ENTRY("vec08u_+", 1)
CYCLES_ENTRY("vec08u_~", 1)

CYCLES_ENTRY("vec08u_++", 1)
CYCLES_ENTRY("vec08u_--", 1)

CYCLES_ENTRY("vec08u_--", 1)

CYCLES_ENTRY("vec08u_broadcast", 1)

CYCLES_ENTRY("vec08u_vget", 1)
CYCLES_ENTRY("vec08u_vput", 1)
CYCLES_ENTRY("vec08u_vmr", 1)
CYCLES_ENTRY("vec08u_vml", 1)
CYCLES_ENTRY("vec08u_vmsl", 1)
CYCLES_ENTRY("vec08u_vmsr", 1)
CYCLES_ENTRY("vec08u_vmrl", 1)
CYCLES_ENTRY("vec08u_vmrr", 1)

CYCLES_ENTRY("vec08u_vload", 1)
CYCLES_ENTRY("vec08u_vstore", 1)

CYCLES_ENTRY("vec08u_vadd", 1)
CYCLES_ENTRY("vec08u_vaddx", 1)
CYCLES_ENTRY("vec08u_vsub", 1)
CYCLES_ENTRY("vec08u_vsubx", 1)
CYCLES_ENTRY("vec08u_vmul", 1)

CYCLES_ENTRY("vec08u_vand", 1)
CYCLES_ENTRY("vec08u_vor", 1)
CYCLES_ENTRY("vec08u_vxor", 1)
CYCLES_ENTRY("vec08u_vnot", 1)

CYCLES_ENTRY("vec08u_vcomplement", 1)

CYCLES_ENTRY("vec08u_vsl", 1)
CYCLES_ENTRY("vec08u_vsr", 1)
CYCLES_ENTRY("vec08u_vsll", 1)
CYCLES_ENTRY("vec08u_vsra", 1)
CYCLES_ENTRY("vec08u_vsrl", 1)

CYCLES_ENTRY("vec08u_vseq", 1)
CYCLES_ENTRY("vec08u_vsne", 1)
CYCLES_ENTRY("vec08u_vsge", 1)
CYCLES_ENTRY("vec08u_vsgt", 1)
CYCLES_ENTRY("vec08u_vsge", 1)
CYCLES_ENTRY("vec08u_vsle", 1)
CYCLES_ENTRY("vec08u_vslt", 1)

CYCLES_ENTRY("vec08u_vselect", 1)
CYCLES_ENTRY("vec08u_vswap", 1)
CYCLES_ENTRY("vec08u_vabs", 1)

CYCLES_ENTRY("vec08u_special_shift", 1)
CYCLES_ENTRY("vec08u_special_multiplication", 1)

*/

///////////////////////////////////////////////////
//  vbool
///////////////////////////////////////////////////

CYCLES_ENTRY("vbool_binary_=",  1)
CYCLES_ENTRY("vbool_binary_==", 1)
CYCLES_ENTRY("vbool_binary_!=", 1)
CYCLES_ENTRY("vbool_binary_&&", 1)
CYCLES_ENTRY("vbool_binary_||", 1)

CYCLES_ENTRY("vbool_!", 1)

CYCLES_ENTRY("vbool_vget", 1)
CYCLES_ENTRY("vbool_vput", 1)

CYCLES_ENTRY("vbool_vmsl", 1)
CYCLES_ENTRY("vbool_vmsr", 1)
CYCLES_ENTRY("vbool_vmrl", 1)
CYCLES_ENTRY("vbool_vmrr", 1)

CYCLES_ENTRY("vbool_vall", 1)
CYCLES_ENTRY("vbool_vany", 1)

///////////////////////////////////////////////////
//  other
///////////////////////////////////////////////////

CYCLES_ENTRY("vif", 1)
CYCLES_ENTRY("velse", 1)
