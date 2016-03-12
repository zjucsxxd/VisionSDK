/*****************************************************************************
*
* Freescale Confidential Proprietary
*
* Copyright (c) 2014 Freescale Semiconductor;
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

#ifndef _tct_opencl_apu_builtin_h
#define _tct_opencl_apu_builtin_h

#include <stdint.h>
#include "tct_opencl_apu.h"


/// ---------------------------
/// ---------------------------
// 6.12.3 Integer Functions
// abs
#define DCL_ABS(UGEN_TYPE, GEN_TYPE) UGEN_TYPE abs(GEN_TYPE a) property(functional);
DCL_ABS(uchar,  char)
DCL_ABS(uchar,  uchar)
DCL_ABS(ushort, short)
DCL_ABS(ushort, ushort)
DCL_ABS(vec08u, vec08s)
DCL_ABS(vec08u, vec08u)
DCL_ABS(vec16u, vec16s)
DCL_ABS(vec16u, vec16u)
DCL_ABS(vec32u, vec32s)
DCL_ABS(vec32u, vec32u)

// abs_diff
inline   ushort   abs_diff(short  a, short  b) property(functional) {return abs_diff((int)a, (int)b );};
inline   ushort   abs_diff(ushort a, ushort b) property(functional) {return abs_diffu(a,b);};
inline   uint     abs_diff(uint   a, uint   b) property(functional) {return abs_diffu(a,b);};
         vec16u   abs_diff(vec16s a, vec16s b) property(functional);
         vec16u   abs_diff(vec16u a, vec16u b) property(functional);
         vec32u   abs_diff(vec32s a, vec32s b) property(functional);
         vec32u   abs_diff(vec32u a, vec32u b) property(functional);

// add_sat
// scalar with 16-bit only;
inline char    add_sat(char  a, char  b) property(functional) {return (add_sat ((( short)a)<<8,(( short)b)<<8)>>8);};
inline uchar   add_sat(uchar a, uchar b) property(functional) {return (add_satu(((ushort)a)<<8,((ushort)b)<<8)>>8);};
inline short   add_sat(short  a, short  b) property(functional) {return (add_sat ((( int)a)<<16,(( int)b)<<16)>>16);};
inline ushort  add_sat(ushort a, ushort b) property(functional) {return (add_satu(((uint)a)<<16,((uint)b)<<16)>>16);};
inline uint    add_sat(uint   a, uint   b) property(functional) {return add_satu(a,b);};
#define DCL_ADD_SAT(RET_TYPE, GEN_TYPE) RET_TYPE add_sat(GEN_TYPE x, GEN_TYPE y);
//DCL_ADD_SAT(char,  char)
//DCL_ADD_SAT(uchar,  uchar)
//DCL_ADD_SAT(short,  short)
//DCL_ADD_SAT(ushort,  ushort)
//DCL_ADD_SAT(int,  int)
//DCL_ADD_SAT(uint,  uint)
DCL_ADD_SAT(vec08s, vec08s)
DCL_ADD_SAT(vec08u, vec08u)
DCL_ADD_SAT(vec16s, vec16s)
DCL_ADD_SAT(vec16u, vec16u)
DCL_ADD_SAT(vec32s, vec32s)
DCL_ADD_SAT(vec32u, vec32u)

// sub_sat
inline char   sub_sat(char  a, char  b) property(functional) {return (sub_sat (((short)a)<<8,((short)b)<<8)>>8);}
inline uchar  sub_sat(uchar a, uchar b) property(functional) {return (sub_satu(((ushort)a)<<8,((ushort)b)<<8)>>8);}
inline short   sub_sat(short  a, short  b) property(functional) {return (sub_sat (((int)a)<<16,((int)b)<<16)>>16);}
inline ushort  sub_sat(ushort a, ushort b) property(functional) {return (sub_satu(((uint)a)<<16,((uint)b)<<16)>>16);}
inline uint    sub_sat(uint   a, uint   b) property(functional) {return sub_satu(a,b);}
#define DCL_SUB_SAT(RET_TYPE, GEN_TYPE) RET_TYPE sub_sat(GEN_TYPE x, GEN_TYPE y);
//DCL_SUB_SAT(char,  char)
//DCL_SUB_SAT(uchar,  uchar)
//DCL_SUB_SAT(short,  short)
//DCL_SUB_SAT(ushort,  ushort)
DCL_SUB_SAT(int,  int)
//DCL_SUB_SAT(uint,  uint)
DCL_SUB_SAT(vec08s, vec08s)
DCL_SUB_SAT(vec08u, vec08u)
DCL_SUB_SAT(vec16s, vec16s)
DCL_SUB_SAT(vec16u, vec16u)
DCL_SUB_SAT(vec32s, vec32s)
DCL_SUB_SAT(vec32u, vec32u)

// mul_hi
inline char    mul_hi(char  a,  char   b) property(functional) {return (( int)a*( int)b)>> 8;}
inline uchar   mul_hi(uchar a,  uchar  b) property(functional) {return ((uint)a*(uint)b)>> 8;}
inline short   mul_hi(short a,  short  b) property(functional) {return (( int)a*( int)b)>>16;}
inline ushort  mul_hi(ushort a, ushort b) property(functional) {return ((uint)a*(uint)b)>>16;}

#define DCL_MUL_HI(RET_TYPE, GEN_TYPE) RET_TYPE mul_hi(GEN_TYPE a, GEN_TYPE b);
DCL_MUL_HI(int,    int)
DCL_MUL_HI(uint,   uint)
DCL_MUL_HI(vec08s, vec08s)
DCL_MUL_HI(vec08u, vec08u)
DCL_MUL_HI(vec16s, vec16s)
DCL_MUL_HI(vec16u, vec16u)
DCL_MUL_HI(vec32s, vec32s)
DCL_MUL_HI(vec32u, vec32u)

// mad_hi
inline char   mad_hi(char a,  char  b, char  c) property(functional) {return (mul_hi(a, b) + c);}
inline uchar  mad_hi(uchar a, uchar b, uchar c) property(functional) {return (mul_hi(a, b) + c);}
inline short  mad_hi(short a,  short  b, short  c) property(functional) {return (mul_hi(a, b) + c);}
inline ushort mad_hi(ushort a, ushort b, ushort c) property(functional) {return (mul_hi(a, b) + c);}

#define DCL_MAD_HI(RET_TYPE, GEN_TYPE) RET_TYPE mad_hi(GEN_TYPE a, GEN_TYPE b, GEN_TYPE c);
//DCL_MAD_HI(char, char)
//DCL_MAD_HI(uchar, uchar)
//DCL_MAD_HI(short, short)
//DCL_MAD_HI(ushort, ushort)
DCL_MAD_HI(int, int)
DCL_MAD_HI(uint, uint)
DCL_MAD_HI(vec08s, vec08s)
DCL_MAD_HI(vec08u, vec08u)
DCL_MAD_HI(vec16s, vec16s)
DCL_MAD_HI(vec16u, vec16u)
DCL_MAD_HI(vec32s, vec32s)
DCL_MAD_HI(vec32u, vec32u)

// mad_sat
//inline short mad_sat(short a, short b, short c) property(functional) {return add_sat((int)a*(int)b, (int)c);};
//inline ushort mad_sat(ushort a, ushort b, ushort c) property(functional) {return add_sat((uint)a*(uint)b, (uint)c);};
#define DCL_MAD_SAT(RET_TYPE, GEN_TYPE) RET_TYPE mad_sat(GEN_TYPE a, GEN_TYPE b, GEN_TYPE c);
DCL_MAD_SAT(char,  char)
DCL_MAD_SAT(uchar, uchar)
DCL_MAD_SAT(short,  short)
DCL_MAD_SAT(ushort, ushort)
DCL_MAD_SAT(int,    int)
DCL_MAD_SAT(uint,   uint)
DCL_MAD_SAT(vec08s, vec08s)
DCL_MAD_SAT(vec08u, vec08u)
DCL_MAD_SAT(vec16s, vec16s)
DCL_MAD_SAT(vec16u, vec16u)
DCL_MAD_SAT(vec32s, vec32s)
DCL_MAD_SAT(vec32u, vec32u)

// upsample

// clz: special case
#define DCL_CLZ(GEN_TYPE, RET_TYPE)   RET_TYPE clz(GEN_TYPE a) property(functional);

DCL_CLZ(char,  char)
DCL_CLZ(uchar, uchar)
DCL_CLZ(short, short)
DCL_CLZ(ushort, ushort)

DCL_CLZ(vec08s, vec08s)
DCL_CLZ(vec08u, vec08u)
DCL_CLZ(vec16s, vec16s)
DCL_CLZ(vec16u, vec16u)
DCL_CLZ(vec32s, vec32s)
DCL_CLZ(vec32u, vec32u)

// rotate
#define DCL_ROTATE(GEN_TYPE, RET_TYPE)   RET_TYPE rotate(GEN_TYPE a, GEN_TYPE b) property(functional);
// 08s
DCL_ROTATE(vec08s, vec08s)
DCL_ROTATE(char, char)
// 08u
DCL_ROTATE(vec08u, vec08u)
DCL_ROTATE(uchar, uchar)
// 16s
DCL_ROTATE(vec16s, vec16s)
DCL_ROTATE(short, short)
// 16u
DCL_ROTATE(vec16u, vec16u)
DCL_ROTATE(ushort, ushort)
// 32s
DCL_ROTATE(vec32s, vec32s)
DCL_ROTATE(int, int)
// 32u
DCL_ROTATE(vec32u, vec32u)
DCL_ROTATE(uint, uint)

// clamp
#define DCL_CLAMP(RET_TYPE, GEN_TYPE) RET_TYPE clamp(GEN_TYPE x, GEN_TYPE minval, GEN_TYPE maxval);
DCL_CLAMP(char,     char)
DCL_CLAMP(uchar,    uchar)
DCL_CLAMP(short,    short)
DCL_CLAMP(ushort,   ushort)
DCL_CLAMP(int,      int)
DCL_CLAMP(uint,     uint)
DCL_CLAMP(vec08s, vec08s)
DCL_CLAMP(vec08u, vec08u)
DCL_CLAMP(vec16s, vec16s)
DCL_CLAMP(vec16u, vec16u)
DCL_CLAMP(vec32s, vec32s)
DCL_CLAMP(vec32u, vec32u)

// popcount
inline char    popcount(char   a) property(functional) {return pcnt(a & 0xFF);}
inline uchar   popcount(uchar  a) property(functional) {return pcnt(a);}
inline short   popcount(short  a) property(functional) {return pcnt(a & 0xFFFF);}
inline ushort  popcount(ushort a) property(functional) {return pcnt(a);}
inline int     popcount(int    a) property(functional) {return pcnt(a);}
inline uint    popcount(uint   a) property(functional) {return pcnt(a);}
//inline vec08s  popcount(vec08s a) property(functional) {return (vec08s)vpcnt(a & 0xFF);}
inline vec08s  popcount(vec08s a) property(functional) {
    vec16s s = (vec16s)a & 0x00FF;
    return (vec08s)vpcnt(s);
}
inline vec08u  popcount(vec08u a) property(functional) {return (vec08u)vpcnt(a);}
inline vec16s  popcount(vec16s a) property(functional) {return vpcnt(a);}
inline vec16u  popcount(vec16u a) property(functional) {return vpcnt(a);}
inline vec32s  popcount(vec32s a) property(functional) {return (vec32s)(vpcnt(a.high()) + vpcnt(a.low()));}
inline vec32u  popcount(vec32u a) property(functional) {return (vec32u)(vpcnt(a.high()) + vpcnt(a.low()));}

// [FLOAT]
// gentype  fmin (gentype x, gentype y)
// gentypef fmin (gentypef x, float y)
// gentyped fmin (gentyped x, double y)
#define DEF_FMIN(GENTYPE_0, GENTYPE_1)                \
inline GENTYPE_1 fmin(GENTYPE_0 x, GENTYPE_1 y) {     \
         GENTYPE_1 rval = (y<x)?y:x; return rval;     \
}

// gentype fmax (gentype x, gentype y)
// gentypef fmax (gentypef x, float y)
// gentyped fmax (gentyped x, double y)
#define DEF_FMAX(GENTYPE_0, GENTYPE_1)                   \
inline GENTYPE_0 fmax(GENTYPE_0 x, GENTYPE_1 y) {        \
         GENTYPE_0 rval = (x<y)?y:x; return rval;        \
}

DEF_FMIN(float, float)
DEF_FMAX(float, float)

// float clamp that uses fmin
#define DEF_FCLAMP(GENTYPE)                                           \
inline GENTYPE clamp (GENTYPE x, GENTYPE minval, GENTYPE maxval)  {  \
         return fmin(fmax(x, minval), maxval);                       \
}
DEF_FCLAMP(float)

// hadd and rhadd
// promotion int hadduu(int,int) = w32 hadduu(w32,w32,uint1&);
// promotion int haddss(int,int) = w32 haddss(w32,w32,uint1&);
// promotion int rhadduu(int,int) = w32 rhadduu(w32,w32,uint1&);
// promotion int rhaddss(int,int) = w32 rhaddss(w32,w32,uint1&);
// promotion vec16s vhadduu(vec16s,vec16s) = vw16 vhadduu(vw16,vw16,vuint1&);
// promotion vec16s vhaddss(vec16s,vec16s) = vw16 vhaddss(vw16,vw16,vuint1&);
// promotion vec16s vrhadduu(vec16s,vec16s) = vw16 vrhadduu(vw16,vw16,vuint1&);
// promotion vec16s vrhaddss(vec16s,vec16s) = vw16 vrhaddss(vw16,vw16,vuint1&);

inline int8_t     hadd(int8_t   a, int8_t b)    property(functional) { return (int8_t)    (haddss(a, b)); }
inline uint8_t    hadd(uint8_t  a, uint8_t b)   property(functional) { return (uint8_t)   (haddss(a, b)); }
inline int16_t    hadd(int16_t  a, int16_t b)   property(functional) { return (int16_t)   (haddss(a, b)); }
inline uint16_t   hadd(uint16_t a, uint16_t b)  property(functional) { return (uint16_t)  (haddss(a, b)); }
inline int32_t    hadd(int32_t  a, int32_t b)   property(functional) { return (int32_t)   (haddss(a, b)); }
inline uint32_t   hadd(uint32_t a, uint32_t b)  property(functional) { return (uint32_t)  (hadduu(a, b)); }

inline int8_t     rhadd(int8_t   a, int8_t b)   property(functional) { return (int8_t)    (rhaddss(a, b)); }
inline uint8_t    rhadd(uint8_t  a, uint8_t b)  property(functional) { return (uint8_t)   (rhaddss(a, b)); }
inline int16_t    rhadd(int16_t  a, int16_t b)  property(functional) { return (int16_t)   (rhaddss(a, b)); }
inline uint16_t   rhadd(uint16_t a, uint16_t b) property(functional) { return (uint16_t)  (rhaddss(a, b)); }
inline int32_t    rhadd(int32_t  a, int32_t b)  property(functional) { return (int32_t)   (rhaddss(a, b)); }
inline uint32_t   rhadd(uint32_t a, uint32_t b) property(functional) { return (uint32_t)  (rhadduu(a, b)); }

inline vec08s     hadd(vec08s a, vec08s b)   property(functional) { return (vec08s)    (vhaddss(a, b)); }
inline vec08u     hadd(vec08u a, vec08u b)   property(functional) { return (vec08u)    (vhaddss(a, b)); }
inline vec16s     hadd(vec16s a, vec16s b)   property(functional) { return (vec16s)    (vhaddss(a, b)); }
inline vec16u     hadd(vec16u a, vec16u b)   property(functional) { return (vec16u)    (vhadduu(a, b)); }
// 
// inline vec32s     hadd(vec32s a, vec32s b)   property(functional) { vbool c; vec32s r = vadd(a, b, c); vec16s h = vsro(r.high(), c, c); vec16u l = vsro(r.low(), c); return vec32s(h,l); }
inline vec32s     hadd(vec32s a, vec32s b)   property(functional) { vbool c; vec32u r = vadd(a, b, c); vec16s t = vaddx(a.high()>>15, b.high()>>15, c); vec32s h = vec32s(t, r.high())>>1; vec32u l = r>>1; return vec32s((vec16s)h.low(), l.low()); }
inline vec32u     hadd(vec32u a, vec32u b)   property(functional) { vbool c; vec32u r = vadd(a, b, c); vec16u h = vsro(r.high(), c, c); vec16u l = vsro(r.low(), c); return vec32u(h,l); }

inline vec08s     rhadd(vec08s a, vec08s b)  property(functional) { return (vec08s)    (vrhaddss(a, b)); }
inline vec08u     rhadd(vec08u a, vec08u b)  property(functional)  { return (vec08u)    (vrhaddss(a, b)); }
inline vec16s     rhadd(vec16s a, vec16s b)  property(functional)  { return (vec16s)    (vrhaddss(a, b)); }
inline vec16u     rhadd(vec16u a, vec16u b)  property(functional)  { return (vec16u)    (vrhadduu(a, b)); }
// inline vec32s     rhadd(vec32s a, vec32s b) property(functional)   { vbool c=1;   vec32s r = vaddx(a, b, c, c);    vec16s h = vsro(r.high(), c, c); vec16u l = vsro(r.low(), c); return vec32s(h,l); }
inline vec32s     rhadd(vec32s a, vec32s b)  property(functional)  { vbool c=1; vec32u r = vaddx(a, b, c, c); vec16s t = vaddx(a.high()>>15, b.high()>>15, c); vec32s h = vec32s(t, r.high())>>1; vec32u l = r>>1; return vec32s((vec16s)h.low(), l.low()); }
inline vec32u     rhadd(vec32u a, vec32u b)  property(functional)  { vbool c=1; vec32u r = vaddx(a, b, c, c); vec16u h = vsro(r.high(), c, c); vec16u l = vsro(r.low(), c); return vec32u(h,l); }
   
// abs_diff
#define DEF_ABS_DIFF_V(RET_TYPE, GEN_TYPE) RET_TYPE abs_diff(GEN_TYPE x, GEN_TYPE y) property(functional);


#define DEF_MIN_V(RET_TYPE, GEN_TYPE)                                      \
         inline RET_TYPE min(GEN_TYPE a, GEN_TYPE b) property(functional)  \
         {return (RET_TYPE)vselect(a, b, ((a) < (b))); }
         
#define DEF_MIN_S(RET_TYPE, GEN_TYPE)                                         \
         inline RET_TYPE min(GEN_TYPE a, GEN_TYPE b) property(functional)     \
         {RET_TYPE c= (((a) < (b)) ? (a) : (b));  return c;}


#define DEF_MAX_V(RET_TYPE, GEN_TYPE)                                      \
         inline RET_TYPE max(GEN_TYPE a, GEN_TYPE b) property(functional)  \
         {return (RET_TYPE)vselect(a, b, ((a) > (b))); }
         
#define DEF_MAX_S(RET_TYPE, GEN_TYPE)                                      \
         inline RET_TYPE max(GEN_TYPE a, GEN_TYPE b) property(functional)  \
         {RET_TYPE c= (((a) > (b)) ? (a) : (b));  return c;}

#define DEF_MIN_MAX_V(RET_TYPE, GEN_TYPE)                      \
         DEF_MIN_V(RET_TYPE, GEN_TYPE)                         \
         DEF_MAX_V(RET_TYPE, GEN_TYPE)

#define DEF_MIN_MAX_S(RET_TYPE, GEN_TYPE)                      \
         DEF_MIN_S(RET_TYPE, GEN_TYPE)                         \
         DEF_MAX_S(RET_TYPE, GEN_TYPE)


DEF_MIN_MAX_V(vec32u, vec32u)
DEF_MIN_MAX_V(vec32s, vec32s)
DEF_MIN_MAX_V(vec16u, vec16u)
DEF_MIN_MAX_V(vec16s, vec16s)
DEF_MIN_MAX_V(vec08u, vec08u)
DEF_MIN_MAX_V(vec08s, vec08s)

DEF_MIN_MAX_S(int32_t,  int32_t)
DEF_MIN_MAX_S(uint32_t, uint32_t)
DEF_MIN_MAX_S(int16_t,  int16_t)
DEF_MIN_MAX_S(uint16_t, uint16_t)
DEF_MIN_MAX_S(int8_t,  int8_t)
DEF_MIN_MAX_S(uint8_t, uint8_t)




// gentype max (gentype x, gentype y)
// gentypef max (gentypef x, float y)
// gentyped max (gentyped x, double y)
#define DEF_MAX(GENTYPE_0, GENTYPE_1)                 \
inline GENTYPE_0 max(GENTYPE_0 x, GENTYPE_1 y)  {     \
         GENTYPE_0 rval = (x<y)?y:x; return rval;     \
}
DEF_MAX(float, float)

// upsample
inline short   upsample(char   hi, uchar  lo)    property(functional) { return ((short) hi <<  8) | lo; }
inline ushort  upsample(uchar  hi, uchar  lo)    property(functional) { return ((ushort)hi <<  8) | lo; }
inline int     upsample(short  hi, ushort lo)    property(functional) { return ((int)   hi << 16) | lo; }
inline uint    upsample(ushort hi, ushort lo)    property(functional) { return ((uint)  hi << 16) | lo; }
inline vec16s  upsample(vec08s hi, vec08u lo)    property(functional) { return ((vec16s)hi <<  8) | (vec16s)lo; }
inline vec16u  upsample(vec08u hi, vec08u lo)    property(functional) { return ((vec16u)hi <<  8) | (vec16u)lo; }
inline vec32s  upsample(vec16s hi, vec16u lo)    property(functional) { return vec32s(hi, lo); }
inline vec32u  upsample(vec16u hi, vec16u lo)    property(functional) { return vec32u(hi, lo); }

// table 6.11
inline  int    mul24(int  x, int  y)               property(functional) {  return x*y; };
inline  uint   mul24(uint x, uint y)               property(functional) {  return x*y; };
inline  int    mad24(int  x, int  y, int  z)       property(functional) {  return x*y + z; };
inline  uint   mad24(uint x, uint y, uint z)       property(functional) {  return x*y + z; };
inline  vec32s mul24(vec32s x, vec32s y)           property(functional) {  return x*y; };
inline  vec32s mad24(vec32s x, vec32s y, vec32s z) property(functional) {  return x*y + z; };
inline  vec32u mul24(vec32u x, vec32u y)           property(functional) {  return x*y; };
inline  vec32u mad24(vec32u x, vec32u y, vec32u z) property(functional) {  return x*y + z; };


#endif
