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

#ifndef _tct_opencl_apu_h
#define _tct_opencl_apu_h

#include "tct_opencl.h"
#include "tct_opencl_apu_builtin.h"

#include <stdint.h>
#include <math.h>

// 6.12.2.1 Floating-point macros and pragmas
#define FLT_MAX 0x1.fffffep127f
#define FLT_MIN 0x1.0p-126f
// 6.12.3 Integer Functions
#define INT_MAX   INT32_MAX


#define VECTOR_TRUE   (~0)
#define VECTOR_FALSE  (0)

// 6.3 g, h (page 219, 220)
#define vLogicAnd(a, b)                 (a && b)? VECTOR_TRUE : VECTOR_FALSE
#define vLogicOr(a, b)                  (a || b)? VECTOR_TRUE : VECTOR_FALSE
#define vLogicNot(a)                    (!a)? VECTOR_TRUE : VECTOR_FALSE

// 6.3 d, e (page 218)
#define vEqual(a, b)                    (a == b)? VECTOR_TRUE : VECTOR_FALSE
#define vGreat(a, b)                    (a > b)? VECTOR_TRUE : VECTOR_FALSE
#define vLess(a, b)                     (a < b)? VECTOR_TRUE : VECTOR_FALSE
#define vGequ(a, b)                     (a >= b)? VECTOR_TRUE : VECTOR_FALSE
#define vLequ(a, b)                     (a <= b)? VECTOR_TRUE : VECTOR_FALSE
#define vNequ(a, b)                     (a != b)? VECTOR_TRUE : VECTOR_FALSE

// 6.3 h (page 220)
#define vShiftRight(a, b, c)            (a>>(b&((8*sizeof(c))-1))) 
#define vShiftLeft(a, b, c)             (a<<(b&((8*sizeof(c))-1))) 


typedef vec32s    vint;
typedef vec32u    vuint;

vuint get_local_id_trf(uint dim);    // s
vuint get_group_id_trf(uint dim);    // w



// Note: C allows constant 0 to be converted to a pointer with higher priority
// than user-defined int->vec32s conversion; this function forces 0 + <vector>
// to use the int->vec32s conversion
inline vec32s operator+(int a, vec32s b) {
    return vec32s(a) + b;
}

inline vec32s operator-(int a, vec32s b) { 
    return vec32s(a) - b; 
}



//
inline uint32_t comp2Int32u(uint32_t a, uint32_t b){
	if(a < b)	return 0xFFFFFFFF;
	else        return 0x00000000;
}

inline int32_t comp2Int32s(int32_t a, int32_t b){
	if (a < b)  return 0xFFFFFFFF;
	else        return 0x00000000;
}


// OPENCL STRUCTURE DEFINITION
// component constructor
// uint4(uint s0, uint s1, uint s2, uint s3): s0(s0), s1(s1), s2(s2), s3(s3) { }
// broadcast constructor
// uint4(uint v): s0(v), s1(v), s2(v), s3(v) { }
#define DEF_VEC2_S(TYPE_NAME, GEN_TYPE)                                                      \
struct TYPE_NAME property(keep_in_registers) {                                               \
   GEN_TYPE s0;  GEN_TYPE s1;                                                                \
   TYPE_NAME(GEN_TYPE _s0, GEN_TYPE _s1): s0(_s0), s1(_s1) { }                               \
   TYPE_NAME(GEN_TYPE v): s0(v), s1(v) { }                                                   \
   TYPE_NAME(TYPE_NAME  s) : s0(s.s0), s1(s.s1) { }                                          \
};
//   

#define DEF_VEC3_S(TYPE_NAME, GEN_TYPE)                                                      \
struct TYPE_NAME property(keep_in_registers) {                                               \
   GEN_TYPE s0, s1, s2;                                                                      \
   TYPE_NAME(GEN_TYPE  v): s0(v), s1(v), s2(v) { }                                           \
   TYPE_NAME(GEN_TYPE  _s0, GEN_TYPE _s1, GEN_TYPE _s2): s0(_s0), s1(_s1), s2(_s2) { }       \
   TYPE_NAME(TYPE_NAME _v): s0(_v.s0), s1(_v.s1), s2(_v.s2) { }                              \
};

#define DEF_VEC4_S(TYPE_NAME, GEN_TYPE)                                                                        \
struct TYPE_NAME property(keep_in_registers) {                                                                 \
   GEN_TYPE s0; GEN_TYPE s1; GEN_TYPE s2; GEN_TYPE s3;                                                         \
   TYPE_NAME(GEN_TYPE  v) : s0(v), s1(v), s2(v), s3(v) { }                                                     \
   TYPE_NAME(TYPE_NAME s) : s0(s.s0), s1(s.s1), s2(s.s2), s3(s.s3) { }                                         \
   TYPE_NAME(GEN_TYPE _s0, GEN_TYPE _s1, GEN_TYPE _s2, GEN_TYPE _s3): s0(_s0), s1(_s1), s2(_s2), s3(_s3) { }   \
};

#define DEF_VEC8_S(TYPE_NAME, GEN_TYPE)                                                            \
struct TYPE_NAME property(keep_in_registers) {                                                     \
   GEN_TYPE s0;  GEN_TYPE s1;  GEN_TYPE s2;  GEN_TYPE s3;                                          \
   GEN_TYPE s4;  GEN_TYPE s5;  GEN_TYPE s6;  GEN_TYPE s7;                                          \
   TYPE_NAME(GEN_TYPE v): s0(v), s1(v), s2(v), s3(v), s4(v), s5(v), s6(v), s7(v) { }               \
   TYPE_NAME(GEN_TYPE _s0, GEN_TYPE _s1, GEN_TYPE _s2, GEN_TYPE _s3,                               \
             GEN_TYPE _s4, GEN_TYPE _s5, GEN_TYPE _s6, GEN_TYPE _s7):                              \
      s0(_s0), s1(_s1), s2(_s2), s3(_s3), s4(_s4), s5(_s5), s6(_s6), s7(_s7)     { }               \
   TYPE_NAME(TYPE_NAME _v):                                                                        \
      s0(_v.s0), s1(_v.s1), s2(_v.s2), s3(_v.s3), s4(_v.s4), s5(_v.s5), s6(_v.s6), s7(_v.s7) { }   \
}; 

#define DEF_VEC16_S(TYPE_NAME, GEN_TYPE)                                                                    \
struct TYPE_NAME  property(keep_in_registers) {                                                                                         \
   GEN_TYPE s0;  GEN_TYPE s1;  GEN_TYPE s2;  GEN_TYPE s3;                                                   \
   GEN_TYPE s4;  GEN_TYPE s5;  GEN_TYPE s6;  GEN_TYPE s7;                                                   \
   GEN_TYPE s8;  GEN_TYPE s9;  GEN_TYPE sa;  GEN_TYPE sb;                                                   \
   GEN_TYPE sc;  GEN_TYPE sd;  GEN_TYPE se;  GEN_TYPE sf;                                                   \
   TYPE_NAME(GEN_TYPE v): s0(v), s1(v), s2(v), s3(v), s4(v), s5(v), s6(v), s7(v),                           \
                          s8(v), s9(v), sa(v), sb(v), sc(v), sd(v), se(v), sf(v) { }                        \
   TYPE_NAME(GEN_TYPE _s0, GEN_TYPE _s1, GEN_TYPE _s2, GEN_TYPE _s3,                                        \
             GEN_TYPE _s4, GEN_TYPE _s5, GEN_TYPE _s6, GEN_TYPE _s7,                                        \
             GEN_TYPE _s8, GEN_TYPE _s9, GEN_TYPE _sa, GEN_TYPE _sb,                                        \
             GEN_TYPE _sc, GEN_TYPE _sd, GEN_TYPE _se, GEN_TYPE _sf):                                       \
             s0(_s0), s1(_s1), s2(_s2), s3(_s3), s4(_s4), s5(_s5), s6(_s6), s7(_s7),                        \
             s8(_s8), s9(_s9), sa(_sa), sb(_sb), sc(_sc), sd(_sd), se(_se), sf(_sf) { }                     \
   TYPE_NAME(TYPE_NAME _v):                                                                                 \
             s0(_v.s0), s1(_v.s1), s2(_v.s2), s3(_v.s3), s4(_v.s4), s5(_v.s5), s6(_v.s6), s7(_v.s7),        \
             s8(_v.s8), s9(_v.s9), sa(_v.sa), sb(_v.sb), sc(_v.sc), sd(_v.sd), se(_v.se), sf(_v.sf) { }     \
};

// DEF_VEC2             (short2,   short, vec_short2, vec16s)
#define DEF_VEC2(TYPE_NAME, GEN_TYPE, TYPE_NAME_V, GEN_TYPE_V)                            \
DEF_VEC2_S(TYPE_NAME, GEN_TYPE)                                                           \
struct TYPE_NAME_V property(keep_in_registers) {                                          \
   GEN_TYPE_V s0;                                                                         \
   GEN_TYPE_V s1;                                                                         \
   TYPE_NAME_V(TYPE_NAME  s) property(broadcast) : s0(s.s0), s1(s.s1) { }                 \
};

#define DEF_VEC3(TYPE_NAME, GEN_TYPE, TYPE1_NAME, APU_TYPE)                                        \
DEF_VEC3_S(TYPE_NAME, GEN_TYPE)                                                                    \
struct TYPE1_NAME property(keep_in_registers) {                                                    \
    APU_TYPE s0; APU_TYPE s1; APU_TYPE s2;                                                         \
    TYPE1_NAME(TYPE_NAME s) property(broadcast): s0(s.s0), s1(s.s1), s2(s.s2) { }                  \
    TYPE1_NAME(APU_TYPE  v)                    : s0(v),    s1(v),    s2(v)    { }                  \
    TYPE1_NAME(APU_TYPE  _s0, APU_TYPE _s1, APU_TYPE _s2):                                         \
    s0(_s0), s1(_s1), s2(_s2) { }                                                                  \
};

#define DEF_VEC4(TYPE_NAME, GEN_TYPE, TYPE1_NAME, APU_TYPE)                                        \
DEF_VEC4_S(TYPE_NAME, GEN_TYPE)                                                                    \
struct TYPE1_NAME property(keep_in_registers) {                                                    \
    APU_TYPE s0; APU_TYPE s1; APU_TYPE s2; APU_TYPE s3;                                            \
    TYPE1_NAME(TYPE_NAME s) property(broadcast): s0(s.s0), s1(s.s1), s2(s.s2), s3(s.s3) { }        \
};

#define DEF_VEC8(TYPE_NAME, GEN_TYPE, TYPE1_NAME, APU_TYPE)                                        \
DEF_VEC8_S(TYPE_NAME, GEN_TYPE)                                                                    \
struct TYPE1_NAME property(keep_in_registers) {                                                    \
    APU_TYPE s0, s1, s2, s3, s4, s5, s6, s7;                                                       \
    TYPE1_NAME(TYPE_NAME s) property(broadcast):                                                   \
    s0(s.s0), s1(s.s1), s2(s.s2), s3(s.s3), s4(s.s4), s5(s.s5), s6(s.s6), s7(s.s7) { }             \
    TYPE1_NAME(APU_TYPE  v) :                                                                      \
    s0(v), s1(v), s2(v), s3(v), s4(v), s5(v), s6(v), s7(v) { }                                     \
    TYPE1_NAME(APU_TYPE _s0, APU_TYPE _s1, APU_TYPE _s2, APU_TYPE _s3,                             \
               APU_TYPE _s4, APU_TYPE _s5, APU_TYPE _s6, APU_TYPE _s7) :                           \
    s0(_s0), s1(_s1), s2(_s2), s3(_s3), s4(_s4), s5(_s5), s6(_s6), s7(_s7) { }                     \
};

#define DEF_VEC16(TYPE_NAME, GEN_TYPE, TYPE1_NAME, APU_TYPE)                                       \
DEF_VEC16_S(TYPE_NAME, GEN_TYPE)                                                                   \
struct TYPE1_NAME  property(keep_in_registers) {                                                    \
   APU_TYPE s0;  APU_TYPE s1;  APU_TYPE s2;  APU_TYPE s3;                                          \
   APU_TYPE s4;  APU_TYPE s5;  APU_TYPE s6;  APU_TYPE s7;                                          \
   APU_TYPE s8;  APU_TYPE s9;  APU_TYPE sa;  APU_TYPE sb;                                          \
   APU_TYPE sc;  APU_TYPE sd;  APU_TYPE se;  APU_TYPE sf;                                          \
   TYPE1_NAME(TYPE_NAME s) property(broadcast):                                                    \
            s0(s.s0), s1(s.s1), s2(s.s2), s3(s.s3), s4(s.s4), s5(s.s5), s6(s.s6), s7(s.s7),        \
            s8(s.s8), s9(s.s9), sa(s.sa), sb(s.sb), sc(s.sc), sd(s.sd), se(s.se), sf(s.sf) {}      \
    TYPE1_NAME(APU_TYPE  v) :                                                                      \
             s0(v), s1(v), s2(v), s3(v), s4(v), s5(v), s6(v), s7(v),                               \
             s8(v), s9(v), sa(v), sb(v), sc(v), sd(v), se(v), sf(v) {}                             \
    TYPE1_NAME(APU_TYPE _s0, APU_TYPE _s1, APU_TYPE _s2, APU_TYPE _s3,                             \
               APU_TYPE _s4, APU_TYPE _s5, APU_TYPE _s6, APU_TYPE _s7,                             \
               APU_TYPE _s8, APU_TYPE _s9, APU_TYPE _sa, APU_TYPE _sb,                             \
               APU_TYPE _sc, APU_TYPE _sd, APU_TYPE _se, APU_TYPE _sf) :                           \
    s0(_s0), s1(_s1), s2(_s2), s3(_s3), s4(_s4), s5(_s5), s6(_s6), s7(_s7),                        \
    s8(_s8), s9(_s9), sa(_sa), sb(_sb), sc(_sc), sd(_sd), se(_se), sf(_sf) {}                      \
};  


// ARITHMETIC BINARY OPERATORS
#define DEF_VEC2_ARITHMETIC(TYPE_NAME, GEN_TYPE)                                    \
inline TYPE_NAME operator+(TYPE_NAME a, TYPE_NAME b) {                              \
   return TYPE_NAME(a.s0 + b.s0, a.s1 + b.s1);                                      \
}                                                                                   \
inline TYPE_NAME operator-(TYPE_NAME a, TYPE_NAME b) {                              \
   return TYPE_NAME(a.s0 - b.s0, a.s1 - b.s1);                                      \
}                                                                                   \
inline TYPE_NAME operator*(TYPE_NAME a, TYPE_NAME b) {                              \
   return TYPE_NAME(a.s0 * b.s0, a.s1 * b.s1);                                      \
}                                                                                   \
inline TYPE_NAME operator/(TYPE_NAME a, TYPE_NAME b) {                              \
   return TYPE_NAME(a.s0 / b.s0, a.s1 / b.s1);                                      \
}                                                                                   
     
// UNARY
#define DEF_VEC2_UNARY(TYPE_NAME, GEN_TYPE)                                         \
inline TYPE_NAME operator++(TYPE_NAME& a, int b) {                                  \
   return TYPE_NAME(a.s0++, a.s1++);                                                \
}                                                                                   \
inline TYPE_NAME operator++(TYPE_NAME& a) {                                         \
   return TYPE_NAME(++a.s0, ++a.s1);                                                \
}                                                                                   \
inline TYPE_NAME operator--(TYPE_NAME& a, int b) {                                  \
   return TYPE_NAME(a.s0--, a.s1--);                                                \
}                                                                                   \
inline TYPE_NAME operator--(TYPE_NAME& a) {                                         \
   return TYPE_NAME(--a.s0, --a.s1);                                                \
} 

// SELECT
// TERNARY: EXPR1?EXPR2:EXPR3
// SELECT(EXPR3, EXPR2, EXPR1)
// Parameter order below:
// OPENCL VECTOR DATATYPE, MSB_CONST = 0x80 (char/uchar), 0x8000(short/ushort)
#define DEF_VEC2_SELECT(TYPE_NAME, MSB_CONST)                                          \
inline TYPE_NAME select(TYPE_NAME c, TYPE_NAME b, TYPE_NAME a) {                       \
    return TYPE_NAME(a.s0 & MSB_CONST ? b.s0 : c.s0, a.s1 & MSB_CONST ? b.s1 : c.s1);  \
}

#define DEF_VEC3_SELECT(TYPE_NAME, MSB_CONST)                                          \
inline TYPE_NAME select(TYPE_NAME c, TYPE_NAME b, TYPE_NAME a) {                       \
    return TYPE_NAME(a.s0 & MSB_CONST ? b.s0 : c.s0, a.s1 & MSB_CONST ? b.s1 : c.s1, a.s2 & MSB_CONST ? b.s2 : c.s2);  \
}

#define DEF_VEC4_SELECT(TYPE_NAME, MSB_CONST)                                          \
inline TYPE_NAME select(TYPE_NAME c, TYPE_NAME b, TYPE_NAME a) {                       \
    return TYPE_NAME(a.s0 & MSB_CONST ? b.s0 : c.s0, a.s1 & MSB_CONST ? b.s1 : c.s1,   \
                     a.s2 & MSB_CONST ? b.s2 : c.s2, a.s3 & MSB_CONST ? b.s3 : c.s3);  \
}

#define DEF_VEC8_SELECT(TYPE_NAME, MSB_CONST)                                          \
inline TYPE_NAME select(TYPE_NAME c, TYPE_NAME b, TYPE_NAME a) {                       \
    return TYPE_NAME(a.s0 & MSB_CONST ? b.s0 : c.s0, a.s1 & MSB_CONST ? b.s1 : c.s1,   \
                     a.s2 & MSB_CONST ? b.s2 : c.s2, a.s3 & MSB_CONST ? b.s3 : c.s3,   \
                     a.s4 & MSB_CONST ? b.s4 : c.s4, a.s5 & MSB_CONST ? b.s5 : c.s5,   \
                     a.s6 & MSB_CONST ? b.s6 : c.s6, a.s7 & MSB_CONST ? b.s7 : c.s7);  \
}

#define DEF_VEC16_SELECT(TYPE_NAME, MSB_CONST)                                         \
inline TYPE_NAME select(TYPE_NAME c, TYPE_NAME b, TYPE_NAME a) {                       \
    return TYPE_NAME(a.s0 & MSB_CONST ? b.s0 : c.s0, a.s1 & MSB_CONST ? b.s1 : c.s1,   \
                     a.s2 & MSB_CONST ? b.s2 : c.s2, a.s3 & MSB_CONST ? b.s3 : c.s3,   \
                     a.s4 & MSB_CONST ? b.s4 : c.s4, a.s5 & MSB_CONST ? b.s5 : c.s5,   \
                     a.s6 & MSB_CONST ? b.s6 : c.s6, a.s7 & MSB_CONST ? b.s7 : c.s7,   \
                     a.s8 & MSB_CONST ? b.s8 : c.s8, a.s9 & MSB_CONST ? b.s9 : c.s9,   \
                     a.sa & MSB_CONST ? b.sa : c.sa, a.sb & MSB_CONST ? b.sb : c.sb,   \
                     a.sc & MSB_CONST ? b.sc : c.sc, a.sd & MSB_CONST ? b.sd : c.sd,   \
                     a.se & MSB_CONST ? b.se : c.se, a.sf & MSB_CONST ? b.sf : c.sf);  \
}

// MODULO                                                                         
#define DEF_VEC2_MODULO(TYPE_NAME, GEN_TYPE)                                        \
inline TYPE_NAME operator%(TYPE_NAME a, TYPE_NAME b) {                              \
   return TYPE_NAME(a.s0 % b.s0, a.s1 % b.s1);                                      \
}

// BITWISE BINARY OPERATORS
#define DEF_VEC2_BITWISE(TYPE_NAME, GEN_TYPE)                                       \
inline TYPE_NAME operator|(TYPE_NAME a, TYPE_NAME b) {                              \
	return TYPE_NAME(a.s0 | b.s0, a.s1 | b.s1);                                      \
}                                                                                   \
inline TYPE_NAME operator&(TYPE_NAME a, TYPE_NAME b) {                              \
	return TYPE_NAME(a.s0 & b.s0, a.s1 & b.s1);                                      \
}                                                                                   \
inline TYPE_NAME operator^(TYPE_NAME a, TYPE_NAME b) {                              \
	return TYPE_NAME(a.s0 ^ b.s0, a.s1 ^ b.s1);                                      \
}                                                                                   \
inline TYPE_NAME operator~(TYPE_NAME a) {                                           \
	return TYPE_NAME(~(a.s0), ~(a.s1));                                              \
}
#if 1
    
// SHIFT
#define DEF_VEC2_SHIFT(TYPE_NAME, GEN_TYPE)                                         \
inline TYPE_NAME operator>>(TYPE_NAME a, TYPE_NAME b) {                             \
   return TYPE_NAME(vShiftRight(a.s0, b.s0, GEN_TYPE) , vShiftRight(a.s1, b.s1, GEN_TYPE));                                        \
}                                                                                   \
inline TYPE_NAME operator<<(TYPE_NAME a, TYPE_NAME b) {                             \
   return TYPE_NAME(vShiftLeft(a.s0, b.s0, GEN_TYPE) , vShiftLeft(a.s1, b.s1, GEN_TYPE));                                        \
}
#else
// SHIFT
#define DEF_VEC2_SHIFT(TYPE_NAME, GEN_TYPE)                                         \
inline TYPE_NAME operator>>(TYPE_NAME a, TYPE_NAME b) {                             \
   return TYPE_NAME(a.s0>>b.s0, a.s1>>b.s1);                                        \
}                                                                                   \
inline TYPE_NAME operator<<(TYPE_NAME a, TYPE_NAME b) {                             \
   return TYPE_NAME(a.s0<<b.s0, a.s1<<b.s1);                                        \
}
#endif
// 6.3 ARITHMETIC BINARY OPERATORS
// The arithmetic operators add (+), subtract (-), multiply (*) and divide (/) operate on built-in
// integer and floating-point scalar, and vector data types. The remainder (%) operates on builtin
// integer scalar and integer vector data types. All arithmetic operators return result of the
// same built-in type (integer or floating-point) as the type of the operands, after operand type
// conversion.
#define DEF_VEC3_ARITHMETIC(TYPE_NAME, GEN_TYPE)                                    \
inline TYPE_NAME operator+(TYPE_NAME a, TYPE_NAME b) {                              \
   return TYPE_NAME(a.s0 + b.s0, a.s1 + b.s1, a.s2 + b.s2);                         \
}                                                                                   \
inline TYPE_NAME operator-(TYPE_NAME a, TYPE_NAME b) {                              \
   return TYPE_NAME(a.s0 - b.s0, a.s1 - b.s1, a.s2 - b.s2);                         \
}                                                                                   \
inline TYPE_NAME operator*(TYPE_NAME a, TYPE_NAME b) {                              \
   return TYPE_NAME(a.s0 * b.s0, a.s1 * b.s1, a.s2 * b.s2);                         \
}                                                                                   \
inline TYPE_NAME operator/(TYPE_NAME a, TYPE_NAME b) {                              \
   return TYPE_NAME(a.s0 / b.s0, a.s1 / b.s1, a.s2 / b.s2);                         \
}                                                                                   
#define DEF_VEC3_MODULO(TYPE_NAME, GEN_TYPE)                                        \
inline TYPE_NAME operator%(TYPE_NAME a, TYPE_NAME b) {                              \
   return TYPE_NAME(a.s0 % b.s0, a.s1 % b.s1, a.s2 % b.s2);                         \
}

// UNARY
#define DEF_VEC3_UNARY(TYPE_NAME, GEN_TYPE)                                         \
inline TYPE_NAME operator++(TYPE_NAME& a, int b) {                                  \
   return TYPE_NAME(a.s0++, a.s1++, a.s2++);                                        \
}                                                                                   \
inline TYPE_NAME operator++(TYPE_NAME& a) {                                         \
   return TYPE_NAME(++a.s0, ++a.s1, ++a.s2);                                        \
}                                                                                   \
inline TYPE_NAME operator--(TYPE_NAME& a, int b) {                                  \
   return TYPE_NAME(a.s0--, a.s1--, a.s2--);                                        \
}                                                                                   \
inline TYPE_NAME operator--(TYPE_NAME& a) {                                         \
   return TYPE_NAME(--a.s0, --a.s1, --a.s2);                                        \
}

// BITWISE BINARY OPERATORS
#define DEF_VEC3_BITWISE(TYPE_NAME, GEN_TYPE)                                       \
inline TYPE_NAME operator|(TYPE_NAME a, TYPE_NAME b) {                              \
	return TYPE_NAME(a.s0 | b.s0, a.s1 | b.s1, a.s2 | b.s2);                         \
}                                                                                   \
inline TYPE_NAME operator&(TYPE_NAME a, TYPE_NAME b) {                              \
	return TYPE_NAME(a.s0 & b.s0, a.s1 & b.s1, a.s2 & b.s2);                         \
}                                                                                   \
inline TYPE_NAME operator^(TYPE_NAME a, TYPE_NAME b) {                              \
	return TYPE_NAME(a.s0 ^ b.s0, a.s1 ^ b.s1, a.s2 ^ b.s2);                         \
}                                                                                   \
inline TYPE_NAME operator~(TYPE_NAME a) {                                           \
	return TYPE_NAME(~(a.s0), ~(a.s1), ~(a.s2));                                     \
} 

#if 1
#define DEF_VEC3_SHIFT(TYPE_NAME, GEN_TYPE)                                         \
inline TYPE_NAME operator>>(TYPE_NAME a, TYPE_NAME b) {                             \
	return TYPE_NAME(vShiftRight(a.s0, b.s0, GEN_TYPE) , vShiftRight(a.s1, b.s1, GEN_TYPE), vShiftRight(a.s2, b.s2, GEN_TYPE)); \
}                                                                                   \
inline TYPE_NAME operator<<(TYPE_NAME a, TYPE_NAME b) {                             \
	return TYPE_NAME(vShiftLeft(a.s0, b.s0, GEN_TYPE) , vShiftLeft(a.s1, b.s1, GEN_TYPE), vShiftLeft(a.s2, b.s2, GEN_TYPE)); \
} 
#else
#define DEF_VEC3_SHIFT(TYPE_NAME, GEN_TYPE)                                         \
inline TYPE_NAME operator>>(TYPE_NAME a, TYPE_NAME b) {                             \
	return TYPE_NAME(a.s0 >> b.s0, a.s1 >> b.s1, a.s2 >> b.s2);                      \
}                                                                                   \
inline TYPE_NAME operator<<(TYPE_NAME a, TYPE_NAME b) {                             \
	return TYPE_NAME(a.s0 << b.s0, a.s1 << b.s1, a.s2 << b.s2);                      \
} 
#endif

// ARITHMETIC BINARY OPERATORS
#define DEF_VEC4_ARITHMETIC(TYPE_NAME, GEN_TYPE)                                    \
inline TYPE_NAME operator+(TYPE_NAME a, TYPE_NAME b) {                              \
   return TYPE_NAME(a.s0 + b.s0, a.s1 + b.s1, a.s2 + b.s2, a.s3 + b.s3);                    \
}                                                                                   \
inline TYPE_NAME operator-(TYPE_NAME a, TYPE_NAME b) {                              \
   return TYPE_NAME(a.s0 - b.s0, a.s1 - b.s1, a.s2 - b.s2, a.s3 - b.s3);                    \
}                                                                                   \
inline TYPE_NAME operator*(TYPE_NAME a, TYPE_NAME b) {                              \
   return TYPE_NAME(a.s0 * b.s0, a.s1 * b.s1, a.s2 * b.s2, a.s3 * b.s3);                    \
}                                                                                   \
inline TYPE_NAME operator/(TYPE_NAME a, TYPE_NAME b) {                              \
   return TYPE_NAME(a.s0 / b.s0, a.s1 / b.s1, a.s2 / b.s2, a.s3 / b.s3);                    \
}                                                                                   
#define DEF_VEC4_MODULO(TYPE_NAME, GEN_TYPE)                                        \
inline TYPE_NAME operator%(TYPE_NAME a, TYPE_NAME b) {                              \
   return TYPE_NAME(a.s0 % b.s0, a.s1 % b.s1, a.s2 % b.s2, a.s3 % b.s3);                    \
}

// ARITHMETIC BINARY OPERATORS
#define DEF_VEC4_SCL_ARITHMETIC(VEC_TYPE, SCL_TYPE)                                 \
inline VEC_TYPE operator+(VEC_TYPE a, SCL_TYPE b) {                                 \
   return VEC_TYPE(a.s0 + b, a.s1 + b, a.s2 + b, a.s3 + b);                         \
}                                                                                   \
inline VEC_TYPE operator-(VEC_TYPE a, SCL_TYPE b) {                                 \
   return VEC_TYPE(a.s0 - b, a.s1 - b, a.s2 - b, a.s3 - b);                         \
}                                                                                   \
inline VEC_TYPE operator*(VEC_TYPE a, SCL_TYPE b) {                                 \
   return VEC_TYPE(a.s0 * b, a.s1 * b, a.s2 * b, a.s3 * b);                         \
}                                                                                   \
inline VEC_TYPE operator/(VEC_TYPE a, SCL_TYPE b) {                                 \
   return VEC_TYPE(a.s0 / b, a.s1 / b, a.s2 / b, a.s3 / b);                         \
} 

// UNARY
#define DEF_VEC4_UNARY(TYPE_NAME, GEN_TYPE)                                         \
inline TYPE_NAME operator++(TYPE_NAME& a, int b) {                                  \
   return TYPE_NAME(a.s0++, a.s1++, a.s2++, a.s3++);                                \
}                                                                                   \
inline TYPE_NAME operator++(TYPE_NAME& a) {                                         \
   return TYPE_NAME(++a.s0, ++a.s1, ++a.s2, ++a.s3);                                \
}                                                                                   \
inline TYPE_NAME operator--(TYPE_NAME& a, int b) {                                  \
   return TYPE_NAME(a.s0--, a.s1--, a.s2--, a.s3--);                                \
}                                                                                   \
inline TYPE_NAME operator--(TYPE_NAME& a) {                                         \
   return TYPE_NAME(--a.s0, --a.s1, --a.s2, --a.s3);                                \
} 

// BITWISE BINARY OPERATORS
#define DEF_VEC4_BITWISE(TYPE_NAME, GEN_TYPE)                                       \
inline TYPE_NAME operator|(TYPE_NAME a, TYPE_NAME b) {                              \
	return TYPE_NAME(a.s0 | b.s0, a.s1 | b.s1, a.s2 | b.s2, a.s3 | b.s3);            \
}                                                                                   \
inline TYPE_NAME operator&(TYPE_NAME a, TYPE_NAME b) {                              \
	return TYPE_NAME(a.s0 & b.s0, a.s1 & b.s1, a.s2 & b.s2, a.s3 & b.s3);            \
}                                                                                   \
inline TYPE_NAME operator^(TYPE_NAME a, TYPE_NAME b) {                              \
	return TYPE_NAME(a.s0 ^ b.s0, a.s1 ^ b.s1, a.s2 ^ b.s2, a.s3 ^ b.s3);            \
}                                                                                   \
inline TYPE_NAME operator~(TYPE_NAME a) {                                           \
	return TYPE_NAME(~(a.s0), ~(a.s1), ~(a.s2), ~(a.s3));                            \
}

#if 1
#define DEF_VEC4_SHIFT(TYPE_NAME, GEN_TYPE)                                         \
inline TYPE_NAME operator>>(TYPE_NAME a, TYPE_NAME b) {                             \
	return TYPE_NAME(vShiftRight(a.s0, b.s0, GEN_TYPE) , vShiftRight(a.s1, b.s1, GEN_TYPE), vShiftRight(a.s2, b.s2, GEN_TYPE), vShiftRight(a.s3, b.s3, GEN_TYPE)); \
}                                                                                   \
inline TYPE_NAME operator<<(TYPE_NAME a, TYPE_NAME b) {                             \
	return TYPE_NAME(vShiftLeft(a.s0, b.s0, GEN_TYPE) , vShiftLeft(a.s1, b.s1, GEN_TYPE), vShiftLeft(a.s2, b.s2, GEN_TYPE), vShiftLeft(a.s3, b.s3, GEN_TYPE)); \
} 
#else
#define DEF_VEC4_SHIFT(TYPE_NAME, GEN_TYPE)                                         \
inline TYPE_NAME operator>>(TYPE_NAME a, TYPE_NAME b) {                             \
	return TYPE_NAME(a.s0 >> b.s0, a.s1 >> b.s1, a.s2 >> b.s2, a.s3 >> b.s3);        \
}                                                                                   \
inline TYPE_NAME operator<<(TYPE_NAME a, TYPE_NAME b) {                             \
	return TYPE_NAME(a.s0 << b.s0, a.s1 << b.s1, a.s2 << b.s2, a.s3 << b.s3);        \
} 
#endif

// COMPARISION OPERATORS
#define DEF_VEC4_S_COMPARISON(TYPE_NAME, GEN_TYPE)                                  \
inline TYPE_NAME operator<(TYPE_NAME a, TYPE_NAME b) {                              \
	return TYPE_NAME(                                                                \
	   comp2Int32s(a.s0, b.s0),                                                      \
	   comp2Int32s(a.s1, b.s1),                                                      \
	   comp2Int32s(a.s2, b.s2),                                                      \
	   comp2Int32s(a.s3, b.s3));                                                     \
}


// ARITHMETIC BINARY OPERATORS
#define DEF_VEC8_ARITHMETIC(TYPE_NAME, GEN_TYPE)                                    \
inline TYPE_NAME operator+(TYPE_NAME a, TYPE_NAME b) {                              \
   return TYPE_NAME(a.s0 + b.s0, a.s1 + b.s1, a.s2 + b.s2, a.s3 + b.s3,             \
                    a.s4 + b.s4, a.s5 + b.s5, a.s6 + b.s6, a.s7 + b.s7);            \
}                                                                                   \
inline TYPE_NAME operator-(TYPE_NAME a, TYPE_NAME b) {                              \
   return TYPE_NAME(a.s0 - b.s0, a.s1 - b.s1, a.s2 - b.s2, a.s3 - b.s3,             \
                    a.s4 - b.s4, a.s5 - b.s5, a.s6 - b.s6, a.s7 - b.s7);            \
}                                                                                   \
inline TYPE_NAME operator*(TYPE_NAME a, TYPE_NAME b) {                              \
   return TYPE_NAME(a.s0 * b.s0, a.s1 * b.s1, a.s2 * b.s2, a.s3 * b.s3,             \
                    a.s4 * b.s4, a.s5 * b.s5, a.s6 * b.s6, a.s7 * b.s7);            \
}                                                                                   \
inline TYPE_NAME operator/(TYPE_NAME a, TYPE_NAME b) {                              \
   return TYPE_NAME(a.s0 / b.s0, a.s1 / b.s1, a.s2 / b.s2, a.s3 / b.s3,             \
                    a.s4 / b.s4, a.s5 / b.s5, a.s6 / b.s6, a.s7 / b.s7);            \
}                                                                                   
#define DEF_VEC8_MODULO(TYPE_NAME, GEN_TYPE)                                        \
inline TYPE_NAME operator%(TYPE_NAME a, TYPE_NAME b) {                              \
   return TYPE_NAME(a.s0 % b.s0, a.s1 % b.s1, a.s2 % b.s2, a.s3 % b.s3,             \
                    a.s4 % b.s4, a.s5 % b.s5, a.s6 % b.s6, a.s7 % b.s7);            \
}

#if 1
#define DEF_VEC8_SHIFT(TYPE_NAME, GEN_TYPE)                                         \
inline TYPE_NAME operator>>(TYPE_NAME a, TYPE_NAME b) {                             \
   return TYPE_NAME(vShiftRight(a.s0, b.s0, GEN_TYPE) , vShiftRight(a.s1, b.s1, GEN_TYPE), vShiftRight(a.s2, b.s2, GEN_TYPE), vShiftRight(a.s3, b.s3, GEN_TYPE),         \
                    vShiftRight(a.s4, b.s4, GEN_TYPE) , vShiftRight(a.s5, b.s5, GEN_TYPE), vShiftRight(a.s6, b.s6, GEN_TYPE), vShiftRight(a.s7, b.s7, GEN_TYPE));        \
}                                                                                   \
inline TYPE_NAME operator<<(TYPE_NAME a, TYPE_NAME b) {                             \
   return TYPE_NAME(vShiftLeft(a.s0, b.s0, GEN_TYPE) , vShiftLeft(a.s1, b.s1, GEN_TYPE), vShiftLeft(a.s2, b.s2, GEN_TYPE), vShiftLeft(a.s3, b.s3, GEN_TYPE),         \
                    vShiftLeft(a.s4, b.s4, GEN_TYPE) , vShiftLeft(a.s5, b.s5, GEN_TYPE), vShiftLeft(a.s6, b.s6, GEN_TYPE), vShiftLeft(a.s7, b.s7, GEN_TYPE));        \
}

#else
#define DEF_VEC8_SHIFT(TYPE_NAME, GEN_TYPE)                                         \
inline TYPE_NAME operator>>(TYPE_NAME a, TYPE_NAME b) {                             \
   return TYPE_NAME(a.s0 >> b.s0, a.s1 >> b.s1, a.s2 >> b.s2, a.s3 >> b.s3,         \
                    a.s4 >> b.s4, a.s5 >> b.s5, a.s6 >> b.s6, a.s7 >> b.s7);        \
}                                                                                   \
inline TYPE_NAME operator<<(TYPE_NAME a, TYPE_NAME b) {                             \
   return TYPE_NAME(a.s0 << b.s0, a.s1 << b.s1, a.s2 << b.s2, a.s3 << b.s3,         \
                    a.s4 << b.s4, a.s5 << b.s5, a.s6 << b.s6, a.s7 << b.s7);        \
}
#endif

// UNARY
#define DEF_VEC8_UNARY(TYPE_NAME, GEN_TYPE)                                         \
inline TYPE_NAME operator++(TYPE_NAME& a, int b) {                                  \
   return TYPE_NAME(a.s0++, a.s1++, a.s2++, a.s3++,                                 \
                    a.s4++, a.s5++, a.s6++, a.s7++);                                \
}                                                                                   \
inline TYPE_NAME operator++(TYPE_NAME& a) {                                         \
   return TYPE_NAME(++a.s0, ++a.s1, ++a.s2, ++a.s3,                                 \
                    ++a.s4, ++a.s5, ++a.s6, ++a.s7);                                \
}                                                                                   \
inline TYPE_NAME operator--(TYPE_NAME& a, int b) {                                  \
   return TYPE_NAME(a.s0--, a.s1--, a.s2--, a.s3--,                                 \
                    a.s4--, a.s5--, a.s6--, a.s7--);                                \
}                                                                                   \
inline TYPE_NAME operator--(TYPE_NAME& a) {                                         \
   return TYPE_NAME(--a.s0, --a.s1, --a.s2, --a.s3,                                 \
                    --a.s4, --a.s5, --a.s6, --a.s7);                                \
}

// BITWISE BINARY OPERATORS
#define DEF_VEC8_BITWISE(TYPE_NAME, GEN_TYPE)                                       \
inline TYPE_NAME operator|(TYPE_NAME a, TYPE_NAME b) {                              \
   return TYPE_NAME(a.s0 | b.s0, a.s1 | b.s1, a.s2 | b.s2, a.s3 | b.s3,             \
                    a.s4 | b.s4, a.s5 | b.s5, a.s6 | b.s6, a.s7 | b.s7);            \
}                                                                                   \
inline TYPE_NAME operator&(TYPE_NAME a, TYPE_NAME b) {                              \
   return TYPE_NAME(a.s0 & b.s0, a.s1 & b.s1, a.s2 & b.s2, a.s3 & b.s3,             \
                    a.s4 & b.s4, a.s5 & b.s5, a.s6 & b.s6, a.s7 & b.s7);            \
}                                                                                   \
inline TYPE_NAME operator^(TYPE_NAME a, TYPE_NAME b) {                              \
   return TYPE_NAME(a.s0 ^ b.s0, a.s1 ^ b.s1, a.s2 ^ b.s2, a.s3 ^ b.s3,             \
                    a.s4 ^ b.s4, a.s5 ^ b.s5, a.s6 ^ b.s6, a.s7 ^ b.s7);            \
}                                                                                   \
inline TYPE_NAME operator~(TYPE_NAME a) {                                           \
   return TYPE_NAME(~a.s0, ~a.s1, ~a.s2, ~a.s3,                                     \
                    ~a.s4, ~a.s5, ~a.s6, ~a.s7);                                    \
}



// ARITHMETIC BINARY OPERATORS
#define DEF_VEC16_ARITHMETIC(TYPE_NAME, GEN_TYPE)                                   \
inline TYPE_NAME operator+(TYPE_NAME a, TYPE_NAME b) {                              \
   return TYPE_NAME(a.s0 + b.s0, a.s1 + b.s1, a.s2 + b.s2, a.s3 + b.s3,             \
                    a.s4 + b.s4, a.s5 + b.s5, a.s6 + b.s6, a.s7 + b.s7,             \
                    a.s8 + b.s8, a.s9 + b.s9, a.sa + b.sa, a.sb + b.sb,             \
                    a.sc + b.sc, a.sd + b.sd, a.se + b.se, a.sf + b.sf);            \
}                                                                                   \
inline TYPE_NAME operator-(TYPE_NAME a, TYPE_NAME b) {                              \
   return TYPE_NAME(a.s0 - b.s0, a.s1 - b.s1, a.s2 - b.s2, a.s3 - b.s3,             \
                    a.s4 - b.s4, a.s5 - b.s5, a.s6 - b.s6, a.s7 - b.s7,             \
                    a.s8 - b.s8, a.s9 - b.s9, a.sa - b.sa, a.sb - b.sb,             \
                    a.sc - b.sc, a.sd - b.sd, a.se - b.se, a.sf - b.sf);            \
}                                                                                   \
inline TYPE_NAME operator*(TYPE_NAME a, TYPE_NAME b) {                              \
   return TYPE_NAME(a.s0 * b.s0, a.s1 * b.s1, a.s2 * b.s2, a.s3 * b.s3,             \
                    a.s4 * b.s4, a.s5 * b.s5, a.s6 * b.s6, a.s7 * b.s7,             \
                    a.s8 * b.s8, a.s9 * b.s9, a.sa * b.sa, a.sb * b.sb,             \
                    a.sc * b.sc, a.sd * b.sd, a.se * b.se, a.sf * b.sf);            \
}                                                                                   \
inline TYPE_NAME operator/(TYPE_NAME a, TYPE_NAME b) {                              \
   return TYPE_NAME(a.s0 / b.s0, a.s1 / b.s1, a.s2 / b.s2, a.s3 / b.s3,             \
                    a.s4 / b.s4, a.s5 / b.s5, a.s6 / b.s6, a.s7 / b.s7,             \
                    a.s8 / b.s8, a.s9 / b.s9, a.sa / b.sa, a.sb / b.sb,             \
                    a.sc / b.sc, a.sd / b.sd, a.se / b.se, a.sf / b.sf);            \
}
#define DEF_VEC16_MODULO(TYPE_NAME, GEN_TYPE)                                       \
inline TYPE_NAME operator%(TYPE_NAME a, TYPE_NAME b) {                              \
   return TYPE_NAME(a.s0 % b.s0, a.s1 % b.s1, a.s2 % b.s2, a.s3 % b.s3,             \
                    a.s4 % b.s4, a.s5 % b.s5, a.s6 % b.s6, a.s7 % b.s7,             \
                    a.s8 % b.s8, a.s9 % b.s9, a.sa % b.sa, a.sb % b.sb,             \
                    a.sc % b.sc, a.sd % b.sd, a.se % b.se, a.sf % b.sf);            \
}

#if 1
#define DEF_VEC16_SHIFT(TYPE_NAME, GEN_TYPE)                                        \
inline TYPE_NAME operator>>(TYPE_NAME a, TYPE_NAME b) {                             \
   return TYPE_NAME(vShiftRight(a.s0, b.s0, GEN_TYPE) , vShiftRight(a.s1, b.s1, GEN_TYPE), vShiftRight(a.s2, b.s2, GEN_TYPE), vShiftRight(a.s3, b.s3, GEN_TYPE),         \
                    vShiftRight(a.s4, b.s4, GEN_TYPE) , vShiftRight(a.s5, b.s5, GEN_TYPE), vShiftRight(a.s6, b.s6, GEN_TYPE), vShiftRight(a.s7, b.s7, GEN_TYPE),         \
                    vShiftRight(a.s8, b.s8, GEN_TYPE) , vShiftRight(a.s9, b.s9, GEN_TYPE), vShiftRight(a.sa, b.sa, GEN_TYPE), vShiftRight(a.sb, b.sb, GEN_TYPE),         \
                    vShiftRight(a.sc, b.sc, GEN_TYPE) , vShiftRight(a.sd, b.sd, GEN_TYPE), vShiftRight(a.se, b.se, GEN_TYPE), vShiftRight(a.sf, b.sf, GEN_TYPE));        \
}                                                                                   \
inline TYPE_NAME operator<<(TYPE_NAME a, TYPE_NAME b) {                             \
   return TYPE_NAME(vShiftLeft(a.s0, b.s0, GEN_TYPE) , vShiftLeft(a.s1, b.s1, GEN_TYPE), vShiftLeft(a.s2, b.s2, GEN_TYPE), vShiftLeft(a.s3, b.s3, GEN_TYPE),         \
                    vShiftLeft(a.s4, b.s4, GEN_TYPE) , vShiftLeft(a.s5, b.s5, GEN_TYPE), vShiftLeft(a.s6, b.s6, GEN_TYPE), vShiftLeft(a.s7, b.s7, GEN_TYPE),         \
                    vShiftLeft(a.s8, b.s8, GEN_TYPE) , vShiftLeft(a.s9, b.s9, GEN_TYPE), vShiftLeft(a.sa, b.sa, GEN_TYPE), vShiftLeft(a.sb, b.sb, GEN_TYPE),         \
                    vShiftLeft(a.sc, b.sc, GEN_TYPE) , vShiftLeft(a.sd, b.sd, GEN_TYPE), vShiftLeft(a.se, b.se, GEN_TYPE), vShiftLeft(a.sf, b.sf, GEN_TYPE));        \
}
#else
#define DEF_VEC16_SHIFT(TYPE_NAME, GEN_TYPE)                                        \
inline TYPE_NAME operator>>(TYPE_NAME a, TYPE_NAME b) {                             \
   return TYPE_NAME(a.s0 >> b.s0, a.s1 >> b.s1, a.s2 >> b.s2, a.s3 >> b.s3,         \
                    a.s4 >> b.s4, a.s5 >> b.s5, a.s6 >> b.s6, a.s7 >> b.s7,         \
                    a.s8 >> b.s8, a.s9 >> b.s9, a.sa >> b.sa, a.sb >> b.sb,         \
                    a.sc >> b.sc, a.sd >> b.sd, a.se >> b.se, a.sf >> b.sf);        \
}                                                                                   \
inline TYPE_NAME operator<<(TYPE_NAME a, TYPE_NAME b) {                             \
   return TYPE_NAME(a.s0 << b.s0, a.s1 << b.s1, a.s2 << b.s2, a.s3 << b.s3,         \
                    a.s4 << b.s4, a.s5 << b.s5, a.s6 << b.s6, a.s7 << b.s7,         \
                    a.s8 << b.s8, a.s9 << b.s9, a.sa << b.sa, a.sb << b.sb,         \
                    a.sc << b.sc, a.sd << b.sd, a.se << b.se, a.sf << b.sf);        \
}
#endif

// UNARY
#define DEF_VEC16_UNARY(TYPE_NAME, GEN_TYPE)                                        \
inline TYPE_NAME operator++(TYPE_NAME& a, int b) {                                  \
   return TYPE_NAME(a.s0++, a.s1++, a.s2++, a.s3++,                                 \
                    a.s4++, a.s5++, a.s6++, a.s7++,                                 \
                    a.s8++, a.s9++, a.sa++, a.sb++,                                 \
                    a.sc++, a.sd++, a.se++, a.sf++);                                \
}                                                                                   \
inline TYPE_NAME operator++(TYPE_NAME& a) {                                         \
   return TYPE_NAME(++a.s0, ++a.s1, ++a.s2, ++a.s3,                                 \
                    ++a.s4, ++a.s5, ++a.s6, ++a.s7,                                 \
                    ++a.s8, ++a.s9, ++a.sa, ++a.sb,                                 \
                    ++a.sc, ++a.sd, ++a.se, ++a.sf);                                \
}                                                                                   \
inline TYPE_NAME operator--(TYPE_NAME& a, int b) {                                  \
   return TYPE_NAME(a.s0--, a.s1--, a.s2--, a.s3--,                                 \
                    a.s4--, a.s5--, a.s6--, a.s7--,                                 \
                    a.s8--, a.s9--, a.sa--, a.sb--,                                 \
                    a.sc--, a.sd--, a.se--, a.sf--);                                \
}                                                                                   \
inline TYPE_NAME operator--(TYPE_NAME& a) {                                         \
   return TYPE_NAME(--a.s0, --a.s1, --a.s2, --a.s3,                                 \
                    --a.s4, --a.s5, --a.s6, --a.s7,                                 \
                    --a.s8, --a.s9, --a.sa, --a.sb,                                 \
                    --a.sc, --a.sd, --a.se, --a.sf);                                \
}


// BITWISE BINARY OPERATORS
#define DEF_VEC16_BITWISE(TYPE_NAME, GEN_TYPE)                                      \
inline TYPE_NAME operator|(TYPE_NAME a, TYPE_NAME b) {                              \
   return TYPE_NAME(a.s0 | b.s0, a.s1 | b.s1, a.s2 | b.s2, a.s3 | b.s3,             \
                    a.s4 | b.s4, a.s5 | b.s5, a.s6 | b.s6, a.s7 | b.s7,             \
                    a.s8 | b.s8, a.s9 | b.s9, a.sa | b.sa, a.sb | b.sb,             \
                    a.sc | b.sc, a.sd | b.sd, a.se | b.se, a.sf | b.sf);            \
}                                                                                   \
inline TYPE_NAME operator&(TYPE_NAME a, TYPE_NAME b) {                              \
   return TYPE_NAME(a.s0 & b.s0, a.s1 & b.s1, a.s2 & b.s2, a.s3 & b.s3,             \
                    a.s4 & b.s4, a.s5 & b.s5, a.s6 & b.s6, a.s7 & b.s7,             \
                    a.s8 & b.s8, a.s9 & b.s9, a.sa & b.sa, a.sb & b.sb,             \
                    a.sc & b.sc, a.sd & b.sd, a.se & b.se, a.sf & b.sf);            \
}                                                                                   \
inline TYPE_NAME operator^(TYPE_NAME a, TYPE_NAME b) {                              \
   return TYPE_NAME(a.s0 ^ b.s0, a.s1 ^ b.s1, a.s2 ^ b.s2, a.s3 ^ b.s3,             \
                    a.s4 ^ b.s4, a.s5 ^ b.s5, a.s6 ^ b.s6, a.s7 ^ b.s7,             \
                    a.s8 ^ b.s8, a.s9 ^ b.s9, a.sa ^ b.sa, a.sb ^ b.sb,             \
                    a.sc ^ b.sc, a.sd ^ b.sd, a.se ^ b.se, a.sf ^ b.sf);            \
}                                                                                   \
inline TYPE_NAME operator~(TYPE_NAME a) {                                           \
   return TYPE_NAME(~a.s0, ~a.s1, ~a.s2, ~a.s3,                                     \
                    ~a.s4, ~a.s5, ~a.s6, ~a.s7,                                     \
                    ~a.s8, ~a.s9, ~a.sa, ~a.sb,                                     \
                    ~a.sc, ~a.sd, ~a.se, ~a.sf);                                    \
}

// BITWISE NOT OPERATORS: ALWAYS RETURN SIGNED
#define DEF_VEC2_LOGICAL(TYPE_NAME, RTYPE_NAME, GEN_TYPE)                  \
inline RTYPE_NAME operator!(TYPE_NAME a) {                                 \
   return RTYPE_NAME(vLogicNot(a.s0), vLogicNot(a.s1));                                        \
}                                                                          \
inline RTYPE_NAME operator&&(TYPE_NAME a, TYPE_NAME b) {                   \
   return RTYPE_NAME(vLogicAnd(a.s0, b.s0), vLogicAnd(a.s1, b.s1));                          \
}                                                                          \
inline RTYPE_NAME operator||(TYPE_NAME a, TYPE_NAME b) {                   \
   return RTYPE_NAME(vLogicOr(a.s0, b.s0), vLogicOr(a.s1, b.s1));                          \
}

#define DEF_VEC3_LOGICAL(TYPE_NAME, RTYPE_NAME, GEN_TYPE)                  \
inline RTYPE_NAME operator!(TYPE_NAME a) {                                 \
   return RTYPE_NAME(vLogicNot(a.s0), vLogicNot(a.s1), vLogicNot(a.s2));                                 \
}                                                                          \
inline RTYPE_NAME operator&&(TYPE_NAME a, TYPE_NAME b) {                   \
   return RTYPE_NAME(vLogicAnd(a.s0, b.s0), vLogicAnd(a.s1, b.s1), vLogicAnd(a.s2, b.s2));            \
}                                                                          \
inline RTYPE_NAME operator||(TYPE_NAME a, TYPE_NAME b) {                   \
   return RTYPE_NAME(vLogicOr(a.s0, b.s0), vLogicOr(a.s1, b.s1), vLogicOr(a.s2, b.s2));            \
}

#define DEF_VEC4_LOGICAL(TYPE_NAME, RTYPE_NAME, GEN_TYPE)                           \
inline RTYPE_NAME operator!(TYPE_NAME a) {                                          \
   return RTYPE_NAME(vLogicNot(a.s0), vLogicNot(a.s1), vLogicNot(a.s2), vLogicNot(a.s3));                                   \
}                                                                                   \
inline RTYPE_NAME operator&&(TYPE_NAME a, TYPE_NAME b) {                            \
   return RTYPE_NAME(vLogicAnd(a.s0, b.s0), vLogicAnd(a.s1, b.s1), vLogicAnd(a.s2, b.s2), vLogicAnd(a.s3, b.s3));       \
}                                                                                   \
inline RTYPE_NAME operator||(TYPE_NAME a, TYPE_NAME b) {                            \
   return RTYPE_NAME(vLogicOr(a.s0, b.s0), vLogicOr(a.s1, b.s1), vLogicOr(a.s2, b.s2), vLogicOr(a.s3, b.s3));       \
}

#define DEF_VEC8_LOGICAL(TYPE_NAME, RTYPE_NAME, GEN_TYPE)                  \
inline RTYPE_NAME operator!(TYPE_NAME a) {                                 \
   return RTYPE_NAME(vLogicNot(a.s0), vLogicNot(a.s1), vLogicNot(a.s2), vLogicNot(a.s3),                           \
                     vLogicNot(a.s4), vLogicNot(a.s5), vLogicNot(a.s6), vLogicNot(a.s7));                          \
}                                                                          \
inline RTYPE_NAME operator&&(TYPE_NAME a, TYPE_NAME b) {                   \
   return RTYPE_NAME(vLogicAnd(a.s0, b.s0), vLogicAnd(a.s1, b.s1),                           \
                     vLogicAnd(a.s2, b.s2), vLogicAnd(a.s3, b.s3),                           \
                     vLogicAnd(a.s4, b.s4), vLogicAnd(a.s5, b.s5),                           \
                     vLogicAnd(a.s6, b.s6), vLogicAnd(a.s7, b.s7));                          \
}                                                                          \
inline RTYPE_NAME operator||(TYPE_NAME a, TYPE_NAME b) {                   \
   return RTYPE_NAME(vLogicOr(a.s0, b.s0), vLogicOr(a.s1, b.s1),                           \
                     vLogicOr(a.s2, b.s2), vLogicOr(a.s3, b.s3),                           \
                     vLogicOr(a.s4, b.s4), vLogicOr(a.s5, b.s5),                           \
                     vLogicOr(a.s6, b.s6), vLogicOr(a.s7, b.s7));                          \
}

#define DEF_VEC16_LOGICAL(TYPE_NAME, RTYPE_NAME, GEN_TYPE)                 \
inline RTYPE_NAME operator!(TYPE_NAME a) {                                 \
   return RTYPE_NAME(vLogicNot(a.s0), vLogicNot(a.s1), vLogicNot(a.s2), vLogicNot(a.s3),                           \
                     vLogicNot(a.s4), vLogicNot(a.s5), vLogicNot(a.s6), vLogicNot(a.s7),                           \
                     vLogicNot(a.s8), vLogicNot(a.s9), vLogicNot(a.sa), vLogicNot(a.sb),                           \
                     vLogicNot(a.sc), vLogicNot(a.sd), vLogicNot(a.se), vLogicNot(a.sf));                          \
}                                                                          \
inline RTYPE_NAME operator&&(TYPE_NAME a, TYPE_NAME b) {                   \
   return RTYPE_NAME(vLogicAnd(a.s0, b.s0), vLogicAnd(a.s1, b.s1),                           \
                     vLogicAnd(a.s2, b.s2), vLogicAnd(a.s3, b.s3),                           \
                     vLogicAnd(a.s4, b.s4), vLogicAnd(a.s5, b.s5),                           \
                     vLogicAnd(a.s6, b.s6), vLogicAnd(a.s7, b.s7),                           \
                     vLogicAnd(a.s8, b.s8), vLogicAnd(a.s9, b.s9),                           \
                     vLogicAnd(a.sa, b.sa), vLogicAnd(a.sb, b.sb),                           \
                     vLogicAnd(a.sc, b.sc), vLogicAnd(a.sd, b.sd),                           \
                     vLogicAnd(a.se, b.se), vLogicAnd(a.sf, b.sf));                          \
}                                                                          \
inline RTYPE_NAME operator||(TYPE_NAME a, TYPE_NAME b) {                   \
   return RTYPE_NAME(vLogicOr(a.s0, b.s0), vLogicOr(a.s1, b.s1),                           \
                     vLogicOr(a.s2, b.s2), vLogicOr(a.s3, b.s3),                           \
                     vLogicOr(a.s4, b.s4), vLogicOr(a.s5, b.s5),                           \
                     vLogicOr(a.s6, b.s6), vLogicOr(a.s7, b.s7),                           \
                     vLogicOr(a.s8, b.s8), vLogicOr(a.s9, b.s9),                           \
                     vLogicOr(a.sa, b.sa), vLogicOr(a.sb, b.sb),                           \
                     vLogicOr(a.sc, b.sc), vLogicOr(a.sd, b.sd),                           \
                     vLogicOr(a.se, b.se), vLogicOr(a.sf, b.sf));                          \
}

#if 0
// RELATIONAL OPERATORS: ALWAYS RETURN SIGNED
// vec2
#define DEF_VEC2_RELATIONAL(TYPE_NAME, RTYPE_NAME, GEN_TYPE)               \
inline RTYPE_NAME operator!=(TYPE_NAME a, TYPE_NAME b) {                   \
   return RTYPE_NAME(((vNequ(a.s0, b.s0))? ~0 :0), ((vNequ(a.s1, b.s1))? ~0 : 0));                          \
}                                                                          \
inline RTYPE_NAME operator==(TYPE_NAME a, TYPE_NAME b) {                   \
   return RTYPE_NAME(vEqual(a.s0, b.s0), vEqual(a.s1, b.s1));              \
}                                                                          \
inline RTYPE_NAME operator>(TYPE_NAME a, TYPE_NAME b) {                    \
   return RTYPE_NAME(vGreat(a.s0, b.s0), vGreat(a.s1, b.s1));              \
}                                                                          \
inline RTYPE_NAME operator>=(TYPE_NAME a, TYPE_NAME b) {                   \
   return RTYPE_NAME(vGequ(a.s0, b.s0), vGequ(a.s1, b.s1));                \
}                                                                          \
inline RTYPE_NAME operator<(TYPE_NAME a, TYPE_NAME b) {                    \
   GEN_TYPE a0, a1, b0, b1, c0, c1;                                        \
   a0 = a.s0;                                                              \
   a1 = a.s1;                                                              \
   b0 = b.s0;                                                              \
   b1 = b.s1;                                                              \
   c0 = a0<b0;                                                             \
   c1 = a1<b1;                                                             \
   return RTYPE_NAME(c0, c1);                                              \
}                                                                          \
inline RTYPE_NAME operator<=(TYPE_NAME a, TYPE_NAME b) {                   \
   return RTYPE_NAME(vLequ(a.s0, b.s0), vLequ(a.s1, b.s1));                \
}


#else
// RELATIONAL OPERATORS: ALWAYS RETURN SIGNED
// vec2
#define DEF_VEC2_RELATIONAL(TYPE_NAME, RTYPE_NAME, GEN_TYPE)               \
inline RTYPE_NAME operator!=(TYPE_NAME a, TYPE_NAME b) {                   \
   return RTYPE_NAME(vNequ(a.s0, b.s0), vNequ(a.s1, b.s1));                          \
}                                                                          \
inline RTYPE_NAME operator==(TYPE_NAME a, TYPE_NAME b) {                   \
   return RTYPE_NAME(vEqual(a.s0, b.s0), vEqual(a.s1, b.s1));                          \
}                                                                          \
inline RTYPE_NAME operator>(TYPE_NAME a, TYPE_NAME b) {                    \
   return RTYPE_NAME(vGreat(a.s0, b.s0), vGreat(a.s1, b.s1));                            \
}                                                                          \
inline RTYPE_NAME operator>=(TYPE_NAME a, TYPE_NAME b) {                   \
   return RTYPE_NAME(vGequ(a.s0, b.s0), vGequ(a.s1, b.s1));                          \
}                                                                          \
inline RTYPE_NAME operator<(TYPE_NAME a, TYPE_NAME b) {                    \
   return RTYPE_NAME(vLess(a.s0, b.s0), vLess(a.s1, b.s1));                            \
}                                                                          \
inline RTYPE_NAME operator<=(TYPE_NAME a, TYPE_NAME b) {                   \
   return RTYPE_NAME(vLequ(a.s0, b.s0), vLequ(a.s1, b.s1));                          \
}
#endif


// vec3
#define DEF_VEC3_RELATIONAL(TYPE_NAME, RTYPE_NAME, GEN_TYPE)               \
inline RTYPE_NAME operator!=(TYPE_NAME a, TYPE_NAME b) {                   \
   return RTYPE_NAME(vNequ(a.s0, b.s0), vNequ(a.s1, b.s1), vNequ(a.s2, b.s2));            \
}                                                                          \
inline RTYPE_NAME operator==(TYPE_NAME a, TYPE_NAME b) {                   \
   return RTYPE_NAME(vEqual(a.s0, b.s0), vEqual(a.s1, b.s1), vEqual(a.s2, b.s2));            \
}                                                                          \
inline RTYPE_NAME operator>(TYPE_NAME a, TYPE_NAME b) {                   \
   return RTYPE_NAME(vGreat(a.s0, b.s0), vGreat(a.s1, b.s1), vGreat(a.s2, b.s2));            \
}                                                                          \
inline RTYPE_NAME operator>=(TYPE_NAME a, TYPE_NAME b) {                   \
   return RTYPE_NAME(vGequ(a.s0, b.s0), vGequ(a.s1, b.s1), vGequ(a.s2, b.s2));            \
}                                                                          \
inline RTYPE_NAME operator<(TYPE_NAME a, TYPE_NAME b) {                    \
   return RTYPE_NAME(vLess(a.s0, b.s0), vLess(a.s1, b.s1), vLess(a.s2, b.s2));               \
}                                                                          \
inline RTYPE_NAME operator<=(TYPE_NAME a, TYPE_NAME b) {                   \
   return RTYPE_NAME(vLequ(a.s0, b.s0), vLequ(a.s1, b.s1), vLequ(a.s2, b.s2));            \
}

// vec4
#define DEF_VEC4_RELATIONAL(TYPE_NAME, RTYPE_NAME, GEN_TYPE)                        \
inline RTYPE_NAME operator!=(TYPE_NAME a, TYPE_NAME b) {                            \
   return RTYPE_NAME(vNequ(a.s0, b.s0), vNequ(a.s1, b.s1), vNequ(a.s2, b.s2), vNequ(a.s3, b.s3));       \
}                                                                                   \
inline RTYPE_NAME operator==(TYPE_NAME a, TYPE_NAME b) {                            \
   return RTYPE_NAME(vEqual(a.s0, b.s0), vEqual(a.s1, b.s1), vEqual(a.s2, b.s2), vEqual(a.s3, b.s3));       \
}                                                                                   \
inline RTYPE_NAME operator>(TYPE_NAME a, TYPE_NAME b) {                             \
   return RTYPE_NAME(vGreat(a.s0, b.s0), vGreat(a.s1, b.s1), vGreat(a.s2, b.s2), vGreat(a.s3, b.s3));           \
}                                                                                   \
inline RTYPE_NAME operator>=(TYPE_NAME a, TYPE_NAME b) {                            \
   return RTYPE_NAME(vGequ(a.s0, b.s0), vGequ(a.s1, b.s1), vGequ(a.s2, b.s2), vGequ(a.s3, b.s3));        \
}                                                                                   \
inline RTYPE_NAME operator<(TYPE_NAME a, TYPE_NAME b) {                             \
   return RTYPE_NAME(vLess(a.s0, b.s0), vLess(a.s1, b.s1), vLess(a.s2, b.s2), vLess(a.s3, b.s3));           \
}                                                                                   \
inline RTYPE_NAME operator<=(TYPE_NAME a, TYPE_NAME b) {                            \
   return RTYPE_NAME(vLequ(a.s0, b.s0), vLequ(a.s1, b.s1), vLequ(a.s2, b.s2), vLequ(a.s3, b.s3));       \
}

// vec8
#define DEF_VEC8_RELATIONAL(TYPE_NAME, RTYPE_NAME, GEN_TYPE)               \
inline RTYPE_NAME operator!=(TYPE_NAME a, TYPE_NAME b) {                   \
   return RTYPE_NAME(vNequ(a.s0, b.s0), vNequ(a.s1, b.s1),                           \
                     vNequ(a.s2, b.s2), vNequ(a.s3, b.s3),                           \
                     vNequ(a.s4, b.s4), vNequ(a.s5, b.s5),                           \
                     vNequ(a.s6, b.s6), vNequ(a.s7, b.s7));                          \
}                                                                          \
inline RTYPE_NAME operator==(TYPE_NAME a, TYPE_NAME b) {                   \
   return RTYPE_NAME(vEqual(a.s0, b.s0), vEqual(a.s1, b.s1),                           \
                     vEqual(a.s2, b.s2), vEqual(a.s3, b.s3),                           \
                     vEqual(a.s4, b.s4), vEqual(a.s5, b.s5),                           \
                     vEqual(a.s6, b.s6), vEqual(a.s7, b.s7));                          \
}                                                                          \
inline RTYPE_NAME operator>(TYPE_NAME a, TYPE_NAME b) {                    \
   return RTYPE_NAME(vGreat(a.s0, b.s0), vGreat(a.s1, b.s1),                             \
                     vGreat(a.s2, b.s2), vGreat(a.s3, b.s3),                             \
                     vGreat(a.s4, b.s4), vGreat(a.s5, b.s5),                             \
                     vGreat(a.s6, b.s6), vGreat(a.s7, b.s7));                            \
}                                                                          \
inline RTYPE_NAME operator>=(TYPE_NAME a, TYPE_NAME b) {                   \
   return RTYPE_NAME(vGequ(a.s0, b.s0), vGequ(a.s1, b.s1),                           \
                     vGequ(a.s2, b.s2), vGequ(a.s3, b.s3),                           \
                     vGequ(a.s4, b.s4), vGequ(a.s5, b.s5),                           \
                     vGequ(a.s6, b.s6), vGequ(a.s7, b.s7));                          \
}                                                                          \
inline RTYPE_NAME operator<(TYPE_NAME a, TYPE_NAME b) {                    \
   return RTYPE_NAME(vLess(a.s0, b.s0), vLess(a.s1, b.s1),                             \
                     vLess(a.s2, b.s2), vLess(a.s3, b.s3),                             \
                     vLess(a.s4, b.s4), vLess(a.s5, b.s5),                             \
                     vLess(a.s6, b.s6), vLess(a.s7, b.s7));                            \
}                                                                          \
inline RTYPE_NAME operator<=(TYPE_NAME a, TYPE_NAME b) {                   \
   return RTYPE_NAME(vLequ(a.s0, b.s0), vLequ(a.s1, b.s1),                           \
                     vLequ(a.s2, b.s2), vLequ(a.s3, b.s3),                           \
                     vLequ(a.s4, b.s4), vLequ(a.s5, b.s5),                           \
                     vLequ(a.s6, b.s6), vLequ(a.s7, b.s7));                          \
}
// vec16
#define DEF_VEC16_RELATIONAL(TYPE_NAME, RTYPE_NAME, GEN_TYPE)               \
inline RTYPE_NAME operator!=(TYPE_NAME a, TYPE_NAME b) {                   \
   return RTYPE_NAME(vNequ(a.s0, b.s0), vNequ(a.s1, b.s1),                           \
                     vNequ(a.s2, b.s2), vNequ(a.s3, b.s3),                           \
                     vNequ(a.s4, b.s4), vNequ(a.s5, b.s5),                           \
                     vNequ(a.s6, b.s6), vNequ(a.s7, b.s7),                           \
                     vNequ(a.s8, b.s8), vNequ(a.s9, b.s9),                           \
                     vNequ(a.sa, b.sa), vNequ(a.sb, b.sb),                           \
                     vNequ(a.sc, b.sc), vNequ(a.sd, b.sd),                           \
                     vNequ(a.se, b.se), vNequ(a.sf, b.sf));                          \
}                                                                          \
inline RTYPE_NAME operator==(TYPE_NAME a, TYPE_NAME b) {                   \
   return RTYPE_NAME(vEqual(a.s0, b.s0), vEqual(a.s1, b.s1),                           \
                     vEqual(a.s2, b.s2), vEqual(a.s3, b.s3),                           \
                     vEqual(a.s4, b.s4), vEqual(a.s5, b.s5),                           \
                     vEqual(a.s6, b.s6), vEqual(a.s7, b.s7),                           \
                     vEqual(a.s8, b.s8), vEqual(a.s9, b.s9),                           \
                     vEqual(a.sa, b.sa), vEqual(a.sb, b.sb),                           \
                     vEqual(a.sc, b.sc), vEqual(a.sd, b.sd),                           \
                     vEqual(a.se, b.se), vEqual(a.sf, b.sf));                          \
}                                                                          \
inline RTYPE_NAME operator>(TYPE_NAME a, TYPE_NAME b) {                    \
   return RTYPE_NAME(vGreat(a.s0, b.s0), vGreat(a.s1, b.s1),                             \
                     vGreat(a.s2, b.s2), vGreat(a.s3, b.s3),                             \
                     vGreat(a.s4, b.s4), vGreat(a.s5, b.s5),                             \
                     vGreat(a.s6, b.s6), vGreat(a.s7, b.s7),                             \
                     vGreat(a.s8, b.s8), vGreat(a.s9, b.s9),                             \
                     vGreat(a.sa, b.sa), vGreat(a.sb, b.sb),                             \
                     vGreat(a.sc, b.sc), vGreat(a.sd, b.sd),                             \
                     vGreat(a.se, b.se), vGreat(a.sf, b.sf));                            \
}                                                                          \
inline RTYPE_NAME operator>=(TYPE_NAME a, TYPE_NAME b) {                   \
   return RTYPE_NAME(vGequ(a.s0, b.s0), vGequ(a.s1, b.s1),                           \
                     vGequ(a.s2, b.s2), vGequ(a.s3, b.s3),                           \
                     vGequ(a.s4, b.s4), vGequ(a.s5, b.s5),                           \
                     vGequ(a.s6, b.s6), vGequ(a.s7, b.s7),                           \
                     vGequ(a.s8, b.s8), vGequ(a.s9, b.s9),                           \
                     vGequ(a.sa, b.sa), vGequ(a.sb, b.sb),                           \
                     vGequ(a.sc, b.sc), vGequ(a.sd, b.sd),                           \
                     vGequ(a.se, b.se), vGequ(a.sf, b.sf));                          \
}                                                                          \
inline RTYPE_NAME operator<(TYPE_NAME a, TYPE_NAME b) {                    \
   return RTYPE_NAME(vLess(a.s0, b.s0), vLess(a.s1, b.s1),                             \
                     vLess(a.s2, b.s2), vLess(a.s3, b.s3),                             \
                     vLess(a.s4, b.s4), vLess(a.s5, b.s5),                             \
                     vLess(a.s6, b.s6), vLess(a.s7, b.s7),                             \
                     vLess(a.s8, b.s8), vLess(a.s9, b.s9),                             \
                     vLess(a.sa, b.sa), vLess(a.sb, b.sb),                             \
                     vLess(a.sc, b.sc), vLess(a.sd, b.sd),                             \
                     vLess(a.se, b.se), vLess(a.sf, b.sf));                            \
}                                                                          \
inline RTYPE_NAME operator<=(TYPE_NAME a, TYPE_NAME b) {                   \
   return RTYPE_NAME(vLequ(a.s0, b.s0), vLequ(a.s1, b.s1),                           \
                     vLequ(a.s2, b.s2), vLequ(a.s3, b.s3),                           \
                     vLequ(a.s4, b.s4), vLequ(a.s5, b.s5),                           \
                     vLequ(a.s6, b.s6), vLequ(a.s7, b.s7),                           \
                     vLequ(a.s8, b.s8), vLequ(a.s9, b.s9),                           \
                     vLequ(a.sa, b.sa), vLequ(a.sb, b.sb),                           \
                     vLequ(a.sc, b.sc), vLequ(a.sd, b.sd),                           \
                     vLequ(a.se, b.se), vLequ(a.sf, b.sf));                          \
}

// OPERATOR ASSIGNMENT
#define DEF_VECX_OPA_ARITHMETIC(TYPE_NAME, GEN_TYPE)                         \
inline void operator+=(TYPE_NAME& a, TYPE_NAME b) { a = a + b; }             \
inline void operator-=(TYPE_NAME& a, TYPE_NAME b) { a = a - b; }             \
inline void operator*=(TYPE_NAME& a, TYPE_NAME b) { a = a * b; }             \
inline void operator/=(TYPE_NAME& a, TYPE_NAME b) { a = a / b; }            

#define DEF_VECX_OPA(TYPE_NAME, GEN_TYPE)                                     \
inline void operator|=(TYPE_NAME& a, TYPE_NAME b) { a = a | b; }             \
inline void operator&=(TYPE_NAME& a, TYPE_NAME b) { a = a & b; }             \
inline void operator^=(TYPE_NAME& a, TYPE_NAME b) { a = a ^ b; }             \
inline void operator%=(TYPE_NAME& a, TYPE_NAME b) { a = a % b; }              \
DEF_VECX_OPA_ARITHMETIC(TYPE_NAME, GEN_TYPE)

 



// inline void operator%=(TYPE_NAME& a, TYPE_NAME b) { return a = a % b; }       
// inline TYPE_NAME operator%(TYPE_NAME a, TYPE_NAME b) { return TYPE_NAME(a.s0 % b.s0, a.s1 % b.s1);  }

// MATH
// sin, cos, tan, fabs, sqrt

#define DEF_VEC4_S_MATH(MATH_FUNC, MATH_FUNC_APU, VEC_TYPE)                         \
inline VEC_TYPE MATH_FUNC(VEC_TYPE a) {                                             \
        return VEC_TYPE(                                                            \
            MATH_FUNC_APU(a.s0),                                                    \
            MATH_FUNC_APU(a.s1),                                                    \
            MATH_FUNC_APU(a.s2),                                                    \
            MATH_FUNC_APU(a.s3) ) ;                                                 \
}


//********
// char
//********
DEF_VEC2             (char2,  char, vec_char2,  vec08s)
DEF_VEC3             (char3,  char, vec_char3,  vec08s)
DEF_VEC4             (char4,  char, vec_char4,  vec08s)
DEF_VEC8             (char8,  char, vec_char8,  vec08s)
DEF_VEC16            (char16, char, vec_char16, vec08s)

DEF_VEC2_ARITHMETIC  (char2,  char)
DEF_VEC3_ARITHMETIC  (char3,  char)
DEF_VEC4_ARITHMETIC  (char4,  char)
DEF_VEC8_ARITHMETIC  (char8,  char)
DEF_VEC16_ARITHMETIC (char16, char)

DEF_VEC2_UNARY(char2, char)
DEF_VEC3_UNARY(char3, char)
DEF_VEC4_UNARY(char4, char)
DEF_VEC8_UNARY(char8, char)
DEF_VEC16_UNARY(char16, char)

// TERNARY: EXPR1?EXPR2:EXPR3
// SELECT(EXPR3, EXPR2, EXPR1)
DEF_VEC2_SELECT(char2, 0x80)
DEF_VEC3_SELECT(char3, 0x80)
DEF_VEC4_SELECT(char4, 0x80)
DEF_VEC8_SELECT(char8, 0x80)
DEF_VEC16_SELECT(char16, 0x80)

DEF_VEC2_BITWISE     (char2,  char)
DEF_VEC3_BITWISE     (char3,  char)
DEF_VEC4_BITWISE     (char4,  char)
DEF_VEC8_BITWISE     (char8,  char)
DEF_VEC16_BITWISE    (char16, char)

DEF_VEC2_MODULO      (char2,  char)
DEF_VEC3_MODULO      (char3,  char)
DEF_VEC4_MODULO      (char4,  char)
DEF_VEC8_MODULO      (char8,  char)
DEF_VEC16_MODULO     (char16, char)

DEF_VEC2_SHIFT       (char2,  char)
DEF_VEC3_SHIFT       (char3,  char)
DEF_VEC4_SHIFT       (char4,  char)
DEF_VEC8_SHIFT       (char8,  char)
DEF_VEC16_SHIFT      (char16, char)

DEF_VEC2_LOGICAL      (char2,  char2,  char)
DEF_VEC3_LOGICAL      (char3,  char3,  char)
DEF_VEC4_LOGICAL      (char4,  char4,  char)
DEF_VEC8_LOGICAL      (char8,  char8,  char)
DEF_VEC16_LOGICAL     (char16, char16, char)

DEF_VEC2_RELATIONAL      (char2,  char2,  char)
DEF_VEC3_RELATIONAL      (char3,  char3,  char)
DEF_VEC4_RELATIONAL      (char4,  char4,  char)
DEF_VEC8_RELATIONAL      (char8,  char8,  char)
DEF_VEC16_RELATIONAL     (char16, char16, char)


DEF_VECX_OPA         (char2,  char)
DEF_VECX_OPA         (char3,  char)
DEF_VECX_OPA         (char4,  char)
DEF_VECX_OPA         (char8,  char)
DEF_VECX_OPA         (char16, char)


//********
// uchar
//********
DEF_VEC2             (uchar2,  uchar, vec_uchar2, vec08u)
DEF_VEC3             (uchar3,  uchar, vec_uchar3,  vec08u)
DEF_VEC4             (uchar4,  uchar, vec_uchar4,  vec08u)
DEF_VEC8             (uchar8,  uchar, vec_uchar8,  vec08u)
DEF_VEC16            (uchar16, uchar, vec_uchar16, vec08u)

DEF_VEC2_ARITHMETIC  (uchar2,  uchar)
DEF_VEC3_ARITHMETIC  (uchar3,  uchar)
DEF_VEC4_ARITHMETIC  (uchar4,  uchar)
DEF_VEC8_ARITHMETIC  (uchar8,  uchar)
DEF_VEC16_ARITHMETIC (uchar16, uchar)

// TERNARY: EXPR1?EXPR2:EXPR3
// SELECT(EXPR3, EXPR2, EXPR1)
DEF_VEC2_SELECT(uchar2, 0x80)
DEF_VEC3_SELECT(uchar3, 0x80)
DEF_VEC4_SELECT(uchar4, 0x80)
DEF_VEC8_SELECT(uchar8, 0x80)
DEF_VEC16_SELECT(uchar16, 0x80)

DEF_VEC2_UNARY (uchar2, uchar)
DEF_VEC3_UNARY (uchar3, uchar)
DEF_VEC4_UNARY (uchar4, uchar)
DEF_VEC8_UNARY (uchar8, uchar)
DEF_VEC16_UNARY(uchar16, uchar)

DEF_VEC2_BITWISE     (uchar2,  uchar)
DEF_VEC3_BITWISE     (uchar3,  uchar)
DEF_VEC4_BITWISE    (uchar4,  uchar)
DEF_VEC8_BITWISE     (uchar8,  uchar)
DEF_VEC16_BITWISE    (uchar16, uchar)

DEF_VEC2_MODULO      (uchar2,  uchar)
DEF_VEC3_MODULO      (uchar3,  uchar)
DEF_VEC4_MODULO      (uchar4,  uchar)
DEF_VEC8_MODULO      (uchar8,  uchar)
DEF_VEC16_MODULO     (uchar16, uchar)

DEF_VEC2_LOGICAL      (uchar2,  char2,  uchar)
DEF_VEC3_LOGICAL      (uchar3,  char3,  uchar)
DEF_VEC4_LOGICAL      (uchar4,  char4,  uchar)
DEF_VEC8_LOGICAL      (uchar8,  char8,  uchar)
DEF_VEC16_LOGICAL     (uchar16, char16, uchar)

DEF_VEC2_RELATIONAL      (uchar2,  char2,  uchar)
DEF_VEC3_RELATIONAL      (uchar3,  char3,  uchar)
DEF_VEC4_RELATIONAL      (uchar4,  char4,  uchar)
DEF_VEC8_RELATIONAL      (uchar8,  char8,  uchar)
DEF_VEC16_RELATIONAL     (uchar16, char16, uchar)

DEF_VEC2_SHIFT       (uchar2,  uchar)
DEF_VEC3_SHIFT       (uchar3,  uchar)
DEF_VEC4_SHIFT       (uchar4,  uchar)
DEF_VEC8_SHIFT       (uchar8,  uchar)
DEF_VEC16_SHIFT      (uchar16, uchar)


DEF_VECX_OPA         (uchar2,  uchar)
DEF_VECX_OPA         (uchar3,  uchar)
DEF_VECX_OPA         (uchar4,  uchar)
DEF_VECX_OPA         (uchar8,  uchar)
DEF_VECX_OPA         (uchar16, uchar)

//********
// short
//********
DEF_VEC2             (short2,  short, vec_short2, vec16s)
DEF_VEC3             (short3,  short, vec_short3,  vec16s)
DEF_VEC4             (short4,  short, vec_short4,  vec16s)
DEF_VEC8             (short8,  short, vec_short8,  vec16s)
DEF_VEC16            (short16, short, vec_short16, vec16s)

DEF_VEC2_ARITHMETIC  (short2,  short)
DEF_VEC3_ARITHMETIC  (short3,  short)
DEF_VEC4_ARITHMETIC  (short4,  short)
DEF_VEC8_ARITHMETIC  (short8,  short)
DEF_VEC16_ARITHMETIC (short16, short)

DEF_VEC2_SELECT(short2,  0x8000)
DEF_VEC3_SELECT(short3, 0x8000)
DEF_VEC4_SELECT(short4, 0x8000)
DEF_VEC8_SELECT(short8, 0x8000)
DEF_VEC16_SELECT(short16, 0x8000)

DEF_VEC2_UNARY (short2,  short)
DEF_VEC3_UNARY (short3,  short)
DEF_VEC4_UNARY (short4,  short)
DEF_VEC8_UNARY (short8,  short)
DEF_VEC16_UNARY(short16, short)

DEF_VEC2_BITWISE     (short2,  short)
DEF_VEC3_BITWISE     (short3,  short)
DEF_VEC4_BITWISE     (short4,  short)
DEF_VEC8_BITWISE     (short8,  short)
DEF_VEC16_BITWISE    (short16, short)

DEF_VEC2_MODULO      (short2,  short)
DEF_VEC3_MODULO      (short3,  short)
DEF_VEC4_MODULO      (short4,  short)
DEF_VEC8_MODULO      (short8,  short)
DEF_VEC16_MODULO     (short16, short)

DEF_VEC2_LOGICAL      (short2,  short2,  ushort)
DEF_VEC3_LOGICAL      (short3,  short3,  ushort)
DEF_VEC4_LOGICAL      (short4,  short4,  ushort)
DEF_VEC8_LOGICAL      (short8,  short8,  ushort)
DEF_VEC16_LOGICAL     (short16, short16, ushort)

DEF_VEC2_RELATIONAL      (short2,  short2,  short)
DEF_VEC3_RELATIONAL      (short3,  short3,  short)
DEF_VEC4_RELATIONAL      (short4,  short4,  short)
DEF_VEC8_RELATIONAL      (short8,  short8,  short)
DEF_VEC16_RELATIONAL     (short16, short16, short)

DEF_VEC2_SHIFT       (short2,   short)
DEF_VEC3_SHIFT       (short3,   short)
DEF_VEC4_SHIFT       (short4,   short)
DEF_VEC8_SHIFT       (short8,   short)
DEF_VEC16_SHIFT      (short16,  short)



DEF_VECX_OPA         (short2,  short)
DEF_VECX_OPA         (short3,  short)
DEF_VECX_OPA         (short4,  short)
DEF_VECX_OPA         (short8,  short)
DEF_VECX_OPA         (short16, short)

//********
// ushort
//********
DEF_VEC2             (ushort2,  ushort, vec_ushort2,  vec16u)
DEF_VEC3             (ushort3,  ushort, vec_ushort3,  vec16u)
DEF_VEC4             (ushort4, ushort, vec_ushort4, vec16u)
DEF_VEC8             (ushort8,  ushort, vec_ushort8,  vec16u)
DEF_VEC16            (ushort16, ushort, vec_ushort16, vec16u)

DEF_VEC2_ARITHMETIC  (ushort2,  ushort)
DEF_VEC3_ARITHMETIC  (ushort3,  ushort)
DEF_VEC4_ARITHMETIC  (ushort4,  ushort)
DEF_VEC8_ARITHMETIC  (ushort8,  ushort)
DEF_VEC16_ARITHMETIC (ushort16, ushort)

DEF_VEC2_SELECT(ushort2,  0x8000)
DEF_VEC3_SELECT(ushort3, 0x8000)
DEF_VEC4_SELECT(ushort4, 0x8000)
DEF_VEC8_SELECT(ushort8, 0x8000)
DEF_VEC16_SELECT(ushort16, 0x8000)

DEF_VEC2_UNARY (ushort2,  ushort)
DEF_VEC3_UNARY (ushort3,  ushort)
DEF_VEC4_UNARY (ushort4,  ushort)
DEF_VEC8_UNARY (ushort8,  ushort)
DEF_VEC16_UNARY(ushort16, ushort)

DEF_VEC2_BITWISE     (ushort2,  ushort)
DEF_VEC3_BITWISE     (ushort3,  ushort)
DEF_VEC4_BITWISE     (ushort4,  ushort)
DEF_VEC8_BITWISE     (ushort8,  ushort)
DEF_VEC16_BITWISE    (ushort16, ushort)

DEF_VEC2_MODULO      (ushort2,  ushort)
DEF_VEC3_MODULO      (ushort3,  ushort)
DEF_VEC4_MODULO      (ushort4,  ushort)
DEF_VEC8_MODULO      (ushort8,  ushort)
DEF_VEC16_MODULO     (ushort16, ushort)

DEF_VEC2_LOGICAL      (ushort2,  short2,  ushort)
DEF_VEC3_LOGICAL      (ushort3,  short3,  ushort)
DEF_VEC4_LOGICAL      (ushort4,  short4,  ushort)
DEF_VEC8_LOGICAL      (ushort8,  short8,  ushort)
DEF_VEC16_LOGICAL     (ushort16, short16, ushort)


DEF_VEC2_RELATIONAL      (ushort2,  short2,  ushort)
DEF_VEC3_RELATIONAL      (ushort3,  short3,  ushort)
DEF_VEC4_RELATIONAL      (ushort4,  short4,  ushort)
DEF_VEC8_RELATIONAL      (ushort8,  short8,  ushort)
DEF_VEC16_RELATIONAL     (ushort16, short16, ushort)

DEF_VEC2_SHIFT       (ushort2,   ushort)
DEF_VEC3_SHIFT       (ushort3,   ushort)
DEF_VEC4_SHIFT       (ushort4,   ushort)
DEF_VEC8_SHIFT       (ushort8,   ushort)
DEF_VEC16_SHIFT      (ushort16,  ushort)


DEF_VECX_OPA         (ushort2,  ushort)
DEF_VECX_OPA         (ushort3,  ushort)
DEF_VECX_OPA         (ushort4,  ushort)
DEF_VECX_OPA         (ushort8,  ushort)
DEF_VECX_OPA         (ushort16, ushort)

//********
// int
//********

DEF_VEC2             (int2,   int, vec_int2,  vec32s)
DEF_VEC3             (int3,   int, vec_int3,  vec32s)
DEF_VEC4             (int4,   int, vec_int4,  vec32s)
DEF_VEC8             (int8,   int, vec_int8,  vec32s)
DEF_VEC16            (int16,  int, vec_int16, vec32s)

DEF_VEC2_ARITHMETIC  (int2,   int)
DEF_VEC3_ARITHMETIC  (int3,   int)
DEF_VEC4_ARITHMETIC  (int4,   int)
DEF_VEC8_ARITHMETIC  (int8,   int)
DEF_VEC16_ARITHMETIC (int16,  int)

DEF_VEC2_SELECT(int2, 0x80000000)
DEF_VEC3_SELECT(int3, 0x80000000)
DEF_VEC4_SELECT(int4, 0x80000000)
DEF_VEC8_SELECT(int8, 0x80000000)
DEF_VEC16_SELECT(int16, 0x80000000)

DEF_VEC2_UNARY (int2, int)
DEF_VEC3_UNARY (int3, int)
DEF_VEC4_UNARY (int4, int)
DEF_VEC8_UNARY (int8, int)
DEF_VEC16_UNARY(int16, int)

DEF_VEC2_BITWISE     (int2,   int)
DEF_VEC3_BITWISE     (int3,   int)
DEF_VEC4_BITWISE     (int4,   int)
DEF_VEC8_BITWISE     (int8,   int)
DEF_VEC16_BITWISE    (int16,  int)

DEF_VEC2_MODULO      (int2,  int)
DEF_VEC3_MODULO      (int3,  int)
DEF_VEC4_MODULO      (int4,  int)
DEF_VEC8_MODULO      (int8,  int)
DEF_VEC16_MODULO     (int16, int)

DEF_VEC2_SHIFT       (int2,   int)
DEF_VEC3_SHIFT       (int3,   int)
DEF_VEC4_SHIFT       (int4,   int)
DEF_VEC8_SHIFT       (int8,   int)
DEF_VEC16_SHIFT      (int16,  int)


DEF_VEC2_LOGICAL      (int2,  int2,  int)
DEF_VEC3_LOGICAL      (int3,  int3,  int)
DEF_VEC4_LOGICAL      (int4,  int4,  int)
DEF_VEC8_LOGICAL      (int8,  int8,  int)
DEF_VEC16_LOGICAL     (int16, int16, int)

DEF_VEC2_RELATIONAL      (int2,  int2,  int)
DEF_VEC3_RELATIONAL      (int3,  int3,  int)
DEF_VEC4_RELATIONAL      (int4,  int4,  int)
DEF_VEC8_RELATIONAL      (int8,  int8,  int)
DEF_VEC16_RELATIONAL     (int16, int16, int)


DEF_VECX_OPA         (int2,  int)
DEF_VECX_OPA         (int3,  int)
DEF_VECX_OPA         (int4,  int)
DEF_VECX_OPA         (int8,  int)
DEF_VECX_OPA         (int16, int)

//********
// uint
//********

DEF_VEC2             (uint2,  uint, vec_uint2,  vec32u)
DEF_VEC3             (uint3,  uint, vec_uint3,  vec32u)
DEF_VEC4             (uint4,  uint, vec_uint4,  vec32u)
DEF_VEC8             (uint8,  uint, vec_uint8,  vec32u)
DEF_VEC16            (uint16, uint, vec_uint16, vec32u)

DEF_VEC2_ARITHMETIC  (uint2,  uint)
DEF_VEC3_ARITHMETIC  (uint3,  uint)
DEF_VEC4_ARITHMETIC  (uint4,  uint)
DEF_VEC8_ARITHMETIC  (uint8,  uint)
DEF_VEC16_ARITHMETIC (uint16, uint)

DEF_VEC2_SELECT(uint2, 0x80000000)
DEF_VEC3_SELECT(uint3, 0x80000000)
DEF_VEC4_SELECT(uint4, 0x80000000)
DEF_VEC8_SELECT(uint8, 0x80000000)
DEF_VEC16_SELECT(uint16, 0x80000000)

DEF_VEC2_UNARY (uint2,  uint)
DEF_VEC3_UNARY (uint3,  uint)
DEF_VEC4_UNARY (uint4,  uint)
DEF_VEC8_UNARY (uint8,  uint)
DEF_VEC16_UNARY(uint16, uint)

DEF_VEC2_BITWISE     (uint2,  uint)
DEF_VEC3_BITWISE     (uint3,  uint)
DEF_VEC4_BITWISE     (uint4,  uint)
DEF_VEC8_BITWISE     (uint8,  uint)
DEF_VEC16_BITWISE    (uint16, uint)

DEF_VEC2_MODULO      (uint2,  uint)
DEF_VEC3_MODULO      (uint3,  uint)
DEF_VEC4_MODULO      (uint4,  uint)
DEF_VEC8_MODULO      (uint8,  uint)
DEF_VEC16_MODULO     (uint16, uint)

DEF_VEC2_LOGICAL      (uint2,  int2,  uint)
DEF_VEC3_LOGICAL      (uint3,  int3,  uint)
DEF_VEC4_LOGICAL      (uint4,  int4,  uint)
DEF_VEC8_LOGICAL      (uint8,  int8,  uint)
DEF_VEC16_LOGICAL     (uint16, int16, uint)

DEF_VEC2_RELATIONAL      (uint2,  int2,  uint)
DEF_VEC3_RELATIONAL      (uint3,  int3,  uint)
DEF_VEC4_RELATIONAL      (uint4,  int4,  uint)
DEF_VEC8_RELATIONAL      (uint8,  int8,  uint)
DEF_VEC16_RELATIONAL     (uint16, int16, uint)

DEF_VEC2_SHIFT       (uint2,  uint)
DEF_VEC3_SHIFT       (uint3,  uint)
DEF_VEC4_SHIFT       (uint4,  uint)
DEF_VEC8_SHIFT       (uint8,  uint)
DEF_VEC16_SHIFT      (uint16, uint)

DEF_VECX_OPA         (uint2,  uint)
DEF_VECX_OPA         (uint3,  uint)
DEF_VECX_OPA         (uint4,  uint)
DEF_VECX_OPA         (uint8,  uint)
DEF_VECX_OPA         (uint16, uint)



//
DEF_VEC2_S            (float2,  float)
DEF_VEC3_S            (float3,  float)
DEF_VEC4_S            (float4,  float)
DEF_VEC8_S            (float8,  float)
DEF_VEC16_S           (float16, float)

DEF_VEC3_S           (double3, double)
                                                                                         
DEF_VEC2_ARITHMETIC  (float2, float)                                                             
DEF_VEC3_ARITHMETIC  (float3, float) 
DEF_VEC3_ARITHMETIC  (double3, double) 


// OPENCL VECTOR DATATYPE, GENERIC TYPE
DEF_VEC4_ARITHMETIC  (float4, float)
//
inline float4 operator-(float4 b) {
    return (float4)(0,0,0,0) - b; 
}


//DEF_VEC8_S           (float8, float)
DEF_VEC8_ARITHMETIC  (float8, float)  


/*
inline vec_int4 operator-(vec_int4 b) { 
    return vec_int4(0,0,0,0) - b; 
}
*/


// arithmetic 
// math 
DEF_VEC4_S_MATH(sin,    sinf,    float4)
DEF_VEC4_S_MATH(cos,    cosf,    float4)
DEF_VEC4_S_MATH(sqrt,   sqrtf,   float4) 
DEF_VEC4_S_MATH(fabs,   fabsf,   float4) 


// += operators
/*
DEF_VEC2_BITWISE     (float2,  float)
DEF_VEC3_BITWISE     (float3,  float)
DEF_VEC4_BITWISE     (float4,  float)
DEF_VEC8_BITWISE     (float8,  float)
DEF_VEC16_BITWISE    (float16, float)
*/
DEF_VECX_OPA_ARITHMETIC         (float4,  float)

//DEF_VEC4_S_MATH(tan, tan, float4) 
// special case
inline float4 tan (float4 a)  { return float4(tan(double(a.s0)), tan(double(a.s1)), tan(double(a.s3)), tan(double(a.s2))); }


/*
inline vec_int4 operator<(vec_int4 a, vec_int4 b) {
	return vec_int4(comp2Vec32s(a.s0, b.s0), comp2Vec32s(a.s1, b.s1), comp2Vec32s(a.s2, b.s2), comp2Vec32s(a.s3, b.s3));
}
*/


// General (memcopy) load/store functions
void load_global (      void*, const GLOBAL(void)* obj, global_ptrdiff_t off, size_t, size_t);
void store_global(const void*,       GLOBAL(void)* obj, global_ptrdiff_t off, size_t, size_t);

void load_global (      void chess_storage(VMb)*, const GLOBAL(void)* obj, global_ptrdiff_vt off, size_t, size_t);
void store_global(const void chess_storage(VMb)*,       GLOBAL(void)* obj, global_ptrdiff_vt off, size_t, size_t);

void load_global (      void chess_storage(VMb)*, const GLOBAL(void)@ obj, global_ptrdiff_vt off, size_t, size_t);
void store_global(const void chess_storage(VMb)*,       GLOBAL(void)@ obj, global_ptrdiff_vt off, size_t, size_t);


// explicit data type support: load/store_global
// "char" (memcopy) load/store functions
#define DCL_LOAD_STORE_DATATYPE(GEN_TYPE, APU_TYPE, OFFSET_GEN_TYPE, OFFSET_APU_TYPE)              \
   void load_global (chess_output GEN_TYPE& val, const GLOBAL(void)* obj, OFFSET_GEN_TYPE off);    \
   void load_global (chess_output APU_TYPE& val, const GLOBAL(void)* obj, OFFSET_APU_TYPE off);    \
   void load_global (chess_output APU_TYPE& val, const GLOBAL(void)@ obj, OFFSET_APU_TYPE off);    \
   void store_global(const GEN_TYPE& val, GLOBAL(void)* obj, OFFSET_GEN_TYPE off);                 \
   void store_global(const APU_TYPE& val, GLOBAL(void)* obj, OFFSET_APU_TYPE off);                 \
   void store_global(const APU_TYPE& val, GLOBAL(void)@ obj, OFFSET_APU_TYPE off);


DCL_LOAD_STORE_DATATYPE(char,   vec08s,      int, vec32s)
DCL_LOAD_STORE_DATATYPE(uchar,  vec08u,      int, vec32s)
DCL_LOAD_STORE_DATATYPE(char3,  vec_char3,   int, vec32s)
DCL_LOAD_STORE_DATATYPE(uchar3, vec_uchar3,  int, vec32s)
//
void load_constant (      void*, const CONSTANT(void)* obj, global_ptrdiff_t off, size_t, size_t);
void store_constant(const void*,       CONSTANT(void)* obj, global_ptrdiff_t off, size_t, size_t);

void load_constant (      void chess_storage(VMb)*, const CONSTANT(void)* obj, global_ptrdiff_vt off, size_t, size_t);
void store_constant(const void chess_storage(VMb)*,       CONSTANT(void)* obj, global_ptrdiff_vt off, size_t, size_t);


//

// 6.2.3 Explicit Conversions
#if 0
inline int4    convert_int4 (UINT4  a) { return int4  (a.s0, a.s1, a.s2, a.s3); }
inline UINT4   convert_uint4(uchar4 a) { return UINT4 (a.s0, a.s1, a.s2, a.s3); }
inline uchar4  convert_uchar4(int4  a) { return uchar4(a.s0, a.s1, a.s2, a.s3); }
inline uchar4  convert_uchar4(UINT4 a) { return uchar4(a.s0, a.s1, a.s2, a.s3); }

inline float   convert_float(int x)    { return (float)(x); }
#else
#define DEF_CONVERT(FUNC, RET, TYPE) \
   inline RET FUNC(TYPE a) property(functional) { return (RET)a; }
   
#define DEF_CONVERT_RND(FUNC, RET, TYPE)  \
   DEF_CONVERT(FUNC##_rte, RET, TYPE)     \
   DEF_CONVERT(FUNC##_rtp, RET, TYPE)     \
   DEF_CONVERT(FUNC##_rtn, RET, TYPE)     \
   DEF_CONVERT(FUNC##_rtz, RET, TYPE)
   
#define DEF_CONVERT_SAT_RND(FUNC, RET, TYPE) \
   DEF_CONVERT(FUNC##_sat_rte, RET, TYPE)    \
   DEF_CONVERT(FUNC##_sat_rtp, RET, TYPE)    \
   DEF_CONVERT(FUNC##_sat_rtn, RET, TYPE)    \
   DEF_CONVERT(FUNC##_sat_rtz, RET, TYPE)

#define DEF_CONVERT_RND_ALL(FUNC, RET, TYPE) \
   DEF_CONVERT(FUNC, RET, TYPE)              \
   DEF_CONVERT_RND(FUNC, RET, TYPE)
   
#define DEF_CONVERT_SAT_RND_ALL(FUNC, RET, TYPE)   \
   DEF_CONVERT(FUNC, RET, TYPE)                    \
   DEF_CONVERT_RND(FUNC, RET, TYPE)                \
   DEF_CONVERT(FUNC##_sat, RET, TYPE)              \
   DEF_CONVERT_SAT_RND(FUNC, RET, TYPE)

#define DCL_CONVERT(FUNC, RET, TYPE) \
   RET FUNC(TYPE a);
   
#define DCL_CONVERT_RND(FUNC, RET, TYPE)  \
   DCL_CONVERT(FUNC##_rte, RET, TYPE)     \
   DCL_CONVERT(FUNC##_rtp, RET, TYPE)     \
   DCL_CONVERT(FUNC##_rtn, RET, TYPE)     \
   DCL_CONVERT(FUNC##_rtz, RET, TYPE)
      
#define DCL_CONVERT_SAT_RND(FUNC, RET, TYPE) \
   DCL_CONVERT(FUNC##_sat_rte, RET, TYPE)    \
   DCL_CONVERT(FUNC##_sat_rtp, RET, TYPE)    \
   DCL_CONVERT(FUNC##_sat_rtn, RET, TYPE)    \
   DCL_CONVERT(FUNC##_sat_rtz, RET, TYPE)
   
#define DCL_CONVERT_SAT_RND_ALL(FUNC, RET, TYPE)   \
   DCL_CONVERT(FUNC##_sat, RET, TYPE)              \
   DCL_CONVERT_SAT_RND(FUNC, RET, TYPE)
   
#define DCL_CONVERT_SAT_RND_ALL2(FUNC, RET, TYPE)  \
   DCL_CONVERT_RND(FUNC, RET, TYPE)                \
   DCL_CONVERT(FUNC##_sat, RET, TYPE)              \
   DCL_CONVERT_SAT_RND(FUNC, RET, TYPE)
   
#define DCL_CONVERT_RND_ALL(FUNC, RET, TYPE) \
   DCL_CONVERT(FUNC, RET, TYPE)              \
   DCL_CONVERT_RND(FUNC, RET, TYPE)

// Convert to uchar
DEF_CONVERT_SAT_RND_ALL(convert_uchar, uchar, uchar)
DEF_CONVERT_SAT_RND_ALL(convert_uchar, vec08u, vec08u)

DEF_CONVERT_RND_ALL(convert_uchar, uchar, char)
DEF_CONVERT_RND_ALL(convert_uchar, vec08u, vec08s)
DCL_CONVERT_SAT_RND_ALL(convert_uchar, uchar, char)
DCL_CONVERT_SAT_RND_ALL(convert_uchar, vec08u, vec08s)

DEF_CONVERT_RND_ALL(convert_uchar, uchar, ushort)
DEF_CONVERT_RND_ALL(convert_uchar, vec08u, vec16u)
DCL_CONVERT_SAT_RND_ALL(convert_uchar, uchar, ushort)
DCL_CONVERT_SAT_RND_ALL(convert_uchar, vec08u, vec16u)

DEF_CONVERT_RND_ALL(convert_uchar, uchar, short)
DEF_CONVERT_RND_ALL(convert_uchar, vec08u, vec16s)
DCL_CONVERT_SAT_RND_ALL(convert_uchar, uchar, short)
DCL_CONVERT_SAT_RND_ALL(convert_uchar, vec08u, vec16s)

DEF_CONVERT_RND_ALL(convert_uchar, uchar, uint)
DEF_CONVERT_RND_ALL(convert_uchar, vec08u, vec32u)
DCL_CONVERT_SAT_RND_ALL(convert_uchar, uchar, uint)
DCL_CONVERT_SAT_RND_ALL(convert_uchar, vec08u, vec32u)

DEF_CONVERT_RND_ALL(convert_uchar, uchar, int)
DEF_CONVERT_RND_ALL(convert_uchar, vec08u, vec32s)
DCL_CONVERT_SAT_RND_ALL(convert_uchar, uchar, int)
DCL_CONVERT_SAT_RND_ALL(convert_uchar, vec08u, vec32s)

DEF_CONVERT(convert_uchar, uchar, float)
DCL_CONVERT_SAT_RND_ALL2(convert_uchar, uchar, float)

// Convert to char
DEF_CONVERT_RND_ALL(convert_char, char, uchar)
DEF_CONVERT_RND_ALL(convert_char, vec08s, vec08u)
DCL_CONVERT_SAT_RND_ALL(convert_char, char, uchar)
DCL_CONVERT_SAT_RND_ALL(convert_char, vec08s, vec08u)

DEF_CONVERT_SAT_RND_ALL(convert_char, char, char)
DEF_CONVERT_SAT_RND_ALL(convert_char, vec08s, vec08s)

DEF_CONVERT_RND_ALL(convert_char, char, ushort)
DEF_CONVERT_RND_ALL(convert_char, vec08s, vec16u)
DCL_CONVERT_SAT_RND_ALL(convert_char, char, ushort)
DCL_CONVERT_SAT_RND_ALL(convert_char, vec08s, vec16u)

DEF_CONVERT_RND_ALL(convert_char, char, short)
DEF_CONVERT_RND_ALL(convert_char, vec08s, vec16s)
DCL_CONVERT_SAT_RND_ALL(convert_char, char, short)
DCL_CONVERT_SAT_RND_ALL(convert_char, vec08s, vec16s)

DEF_CONVERT_RND_ALL(convert_char, char, uint)
DEF_CONVERT_RND_ALL(convert_char, vec08s, vec32u)
DCL_CONVERT_SAT_RND_ALL(convert_char, char, uint)
DCL_CONVERT_SAT_RND_ALL(convert_char, vec08s, vec32u)

DEF_CONVERT_RND_ALL(convert_char, char, int)
DEF_CONVERT_RND_ALL(convert_char, vec08s, vec32s)
DCL_CONVERT_SAT_RND_ALL(convert_char, char, int)
DCL_CONVERT_SAT_RND_ALL(convert_char, vec08s, vec32s)

DEF_CONVERT(convert_char, char, float)
DCL_CONVERT_SAT_RND_ALL2(convert_char, char, float)

// Convert to ushort
DEF_CONVERT_SAT_RND_ALL(convert_ushort, ushort, uchar)
DEF_CONVERT_SAT_RND_ALL(convert_ushort, vec16u, vec08u)

DEF_CONVERT_RND_ALL(convert_ushort, ushort, char)
DEF_CONVERT_RND_ALL(convert_ushort, vec16u, vec08s)
DCL_CONVERT_SAT_RND_ALL(convert_ushort, ushort, char)
DCL_CONVERT_SAT_RND_ALL(convert_ushort, vec16u, vec08s)

DEF_CONVERT_SAT_RND_ALL(convert_ushort, ushort, ushort)
DEF_CONVERT_SAT_RND_ALL(convert_ushort, vec16u, vec16u)

DEF_CONVERT_RND_ALL(convert_ushort, ushort, short)
DEF_CONVERT_RND_ALL(convert_ushort, vec16u, vec16s)
DCL_CONVERT_SAT_RND_ALL(convert_ushort, ushort, short)
DCL_CONVERT_SAT_RND_ALL(convert_ushort, vec16u, vec16s)

DEF_CONVERT_RND_ALL(convert_ushort, ushort, uint)
DEF_CONVERT_RND_ALL(convert_ushort, vec16u, vec32u)
DCL_CONVERT_SAT_RND_ALL(convert_ushort, ushort, uint)
DCL_CONVERT_SAT_RND_ALL(convert_ushort, vec16u, vec32u)

DEF_CONVERT_RND_ALL(convert_ushort, ushort, int)
DEF_CONVERT_RND_ALL(convert_ushort, vec16u, vec32s)
DCL_CONVERT_SAT_RND_ALL(convert_ushort, ushort, int)
DCL_CONVERT_SAT_RND_ALL(convert_ushort, vec16u, vec32s)

DEF_CONVERT(convert_ushort, ushort, float)
DCL_CONVERT_SAT_RND_ALL2(convert_ushort, ushort, float)

// Convert to short
DEF_CONVERT_SAT_RND_ALL(convert_short, short, uchar)
DEF_CONVERT_SAT_RND_ALL(convert_short, vec16s, vec08u)

DEF_CONVERT_SAT_RND_ALL(convert_short, short, char)
DEF_CONVERT_SAT_RND_ALL(convert_short, vec16s, vec08s)

DEF_CONVERT_RND_ALL(convert_short, short, ushort)
DEF_CONVERT_RND_ALL(convert_short, vec16s, vec16u)
DCL_CONVERT_SAT_RND_ALL(convert_short, short, ushort)
DCL_CONVERT_SAT_RND_ALL(convert_short, vec16s, vec16u)

DEF_CONVERT_SAT_RND_ALL(convert_short, short, short)
DEF_CONVERT_SAT_RND_ALL(convert_short, vec16s, vec16s)

DEF_CONVERT_RND_ALL(convert_short, short, uint)
DEF_CONVERT_RND_ALL(convert_short, vec16s, vec32u)
DCL_CONVERT_SAT_RND_ALL(convert_short, short, uint)
DCL_CONVERT_SAT_RND_ALL(convert_short, vec16s, vec32u)

DEF_CONVERT_RND_ALL(convert_short, short, int)
DEF_CONVERT_RND_ALL(convert_short, vec16s, vec32s)
DCL_CONVERT_SAT_RND_ALL(convert_short, short, int)
DCL_CONVERT_SAT_RND_ALL(convert_short, vec16s, vec32s)

DEF_CONVERT(convert_short, short, float)
DCL_CONVERT_SAT_RND_ALL2(convert_short, short, float)

// Convert to uint
DEF_CONVERT_SAT_RND_ALL(convert_uint, uint, uchar)
DEF_CONVERT_SAT_RND_ALL(convert_uint, vec32u, vec08u)

DEF_CONVERT_RND_ALL(convert_uint, uint, char)
DEF_CONVERT_RND_ALL(convert_uint, vec32u, vec08s)
DCL_CONVERT_SAT_RND_ALL(convert_uint, uint, char)
DCL_CONVERT_SAT_RND_ALL(convert_uint, vec32u, vec08s)

DEF_CONVERT_SAT_RND_ALL(convert_uint, uint, ushort)
DEF_CONVERT_SAT_RND_ALL(convert_uint, vec32u, vec16u)

DEF_CONVERT_RND_ALL(convert_uint, uint, short)
DEF_CONVERT_RND_ALL(convert_uint, vec32u, vec16s)
DCL_CONVERT_SAT_RND_ALL(convert_uint, uint, short)
DCL_CONVERT_SAT_RND_ALL(convert_uint, vec32u, vec16s)

DEF_CONVERT_SAT_RND_ALL(convert_uint, uint, uint)
DEF_CONVERT_SAT_RND_ALL(convert_uint, vec32u, vec32u)

DEF_CONVERT_RND_ALL(convert_uint, uint, int)
DEF_CONVERT_RND_ALL(convert_uint, vec32u, vec32s)
DCL_CONVERT_SAT_RND_ALL(convert_uint, uint, int)
DCL_CONVERT_SAT_RND_ALL(convert_uint, vec32u, vec32s)

// float to uint requires float32_to_int64 from the 64-bit softfloat library.
// However, for the embedded opencl profile 64-bit is not supported.
DEF_CONVERT(convert_uint, uint, float)
DCL_CONVERT_SAT_RND_ALL2(convert_uint, uint, float)

// Convert to int
DEF_CONVERT_SAT_RND_ALL(convert_int, int, uchar)
DEF_CONVERT_SAT_RND_ALL(convert_int, vec32s, vec08u)

DEF_CONVERT_SAT_RND_ALL(convert_int, int, char)
DEF_CONVERT_SAT_RND_ALL(convert_int, vec32s, vec08s)

DEF_CONVERT_SAT_RND_ALL(convert_int, int, ushort)
DEF_CONVERT_SAT_RND_ALL(convert_int, vec32s, vec16u)

DEF_CONVERT_SAT_RND_ALL(convert_int, int, short)
DEF_CONVERT_SAT_RND_ALL(convert_int, vec32s, vec16s)

DEF_CONVERT_RND_ALL(convert_int, int, uint)
DEF_CONVERT_RND_ALL(convert_int, vec32s, vec32u)
DCL_CONVERT_SAT_RND_ALL(convert_int, int, uint)
DCL_CONVERT_SAT_RND_ALL(convert_int, vec32s, vec32u)

DEF_CONVERT_SAT_RND_ALL(convert_int, int, int)
DEF_CONVERT_SAT_RND_ALL(convert_int, vec32s, vec32s)

DEF_CONVERT(convert_int, int, float)
DCL_CONVERT_SAT_RND_ALL2(convert_int, int, float)

// Convert to float
DCL_CONVERT_RND_ALL(convert_float, float, uchar)

DCL_CONVERT_RND_ALL(convert_float, float, char)

DCL_CONVERT_RND_ALL(convert_float, float, ushort)

DCL_CONVERT_RND_ALL(convert_float, float, short)

// uint to float requires int32_to_float64 from the 64-bit softfloat library.
// However, for the embedded opencl profile 64-bit is not supported.
DCL_CONVERT_RND_ALL(convert_float, float, uint)

DCL_CONVERT_RND_ALL(convert_float, float, int)

//DCL_CONVERT_RND_ALL(convert_float, float, float)
DEF_CONVERT_RND_ALL(convert_float, float, float)
#endif

// temporary solution (not supported)
#define atomic_inc(_PTR)         (*(_PTR)) = (*(_PTR) + 1)
#define atomic_dec(_PTR)         (*(_PTR)) = (*(_PTR) - 1)
#define atomic_add(_PTR, _CNT)   ((*(_PTR)) = (*(_PTR) + (_CNT)))


// 6.12.5 Geometric Functions53
// only exist for floating point
inline float dot(float  a, float  b)      { return a*b;}
inline float dot(float2 a, float2 b)      { return a.s0*b.s0 + a.s1*b.s1;}
inline float dot(float4 a, float4 b)      { return a.s0*b.s0 + a.s1*b.s1 + a.s2*b.s2 + a.s3*b.s3;}

// 6.12.2 math functions
// Returns the correctly rounded floating-point
// representation of the sum of c with the infinitely
// precise product of a and b.
inline float  fma   (float  a, float b, float c) { return c += dot(a,b); }
inline double pown  (double x, int y)            { return pow(x,y); }

// TBD
inline float  hypot (float  x, float y)          { return (x+y);}

// Round to integral value (using round to nearest
// even rounding mode) in floating-point format.
// Refer to section 7.1 for description of rounding modes.
// TBD
inline ushort  rint  (float x)                    {ushort z; return z;}

inline int4 operator-(int4 a) {
    return int4(-a.s0, -a.s1, -a.s2, -a.s3);
}

/// ----------------------------
/// Same operation: vector input
/// ----------------------------
// Define 1 functions with vec2 types, takes in 1 argument
#define DEF_FUNC1_2_ARG1(FUNC, TRET, TYPE1)                                      \
   inline TRET FUNC(TYPE1 a) { return TRET(FUNC(a.s0), FUNC(a.s1)); }   
#define DEF_FUNC1N_2_ARG1(FUNCN, FUNC, TRET, TYPE1)                                      \
   inline TRET FUNCN(TYPE1 a) { return TRET(FUNC(a.s0), FUNC(a.s1)); }     

// Define 1 functions with vec2 types, takes in 2 arguments
#define DEF_FUNC1_2_ARG2(FUNC, TRET, TYPE1)                                              \
   inline TRET FUNC(TYPE1 a, TYPE1 b) { return TRET(FUNC(a.s0, b.s0), FUNC(a.s1, b.s1)); }
#define DEF_FUNC1_2_ARG2_A(FUNC, TRET, TYPE1, TYPE2)                                     \
   inline TRET FUNC(TYPE1 a, TYPE2 b) { return TRET(FUNC(a.s0, b.s0), FUNC(a.s1, b.s1)); }

// Define 1 functions with vec2 types, takes in 3 arguments  
#define DEF_FUNC1_2_ARG3(FUNC, TRET, TYPE1)                                              \
   inline TRET FUNC(TYPE1 a, TYPE1 b, TYPE1 c) { return TRET(FUNC(a.s0, b.s0, c.s0), FUNC(a.s1, b.s1, c.s1)); }
   
// Define 1 functions with vec3 types, takes in 1 arguments
#define DEF_FUNC1_3_ARG1(FUNC, TRET, TYPE1)             \
   inline TRET FUNC(TYPE1 a) { \
      return TRET(FUNC(a.s0), FUNC(a.s1), FUNC(a.s2)); }
#define DEF_FUNC1N_3_ARG1(FUNCN, FUNC, TRET, TYPE1)             \
   inline TRET FUNCN(TYPE1 a) { \
      return TRET(FUNC(a.s0), FUNC(a.s1), FUNC(a.s2)); }      
      
// Define 1 functions with vec3 types, takes in 2 arguments
#define DEF_FUNC1_3_ARG2(FUNC, TRET, TYPE1)                            \
   inline TRET FUNC(TYPE1 a, TYPE1 b) { \
      return TRET(FUNC(a.s0, b.s0), FUNC(a.s1, b.s1), FUNC(a.s2, b.s2)); }   
#define DEF_FUNC1_3_ARG2_A(FUNC, TRET, TYPE1, TYPE2)                            \
   inline TRET FUNC(TYPE1 a, TYPE2 b) { \
      return TRET(FUNC(a.s0, b.s0), FUNC(a.s1, b.s1), FUNC(a.s2, b.s2)); }   
      
// Define 1 functions with vec3 types, takes in 3 arguments
#define DEF_FUNC1_3_ARG3(FUNC, TRET, TYPE1)                            \
   inline TRET FUNC(TYPE1 a, TYPE1 b, TYPE1 c) {  \
      return TRET(FUNC(a.s0, b.s0, c.s0), FUNC(a.s1, b.s1, c.s1), FUNC(a.s2, b.s2, c.s2)); }

// Define 1 functions with vec4 types, takes in 1 argument
#define DEF_FUNC1_4_ARG1(FUNC, TRET, TYPE1)                            \
   inline TRET FUNC(TYPE1 a) { \
      return TRET(FUNC(a.s0), FUNC(a.s1), FUNC(a.s2), FUNC(a.s3)); } 
#define DEF_FUNC1N_4_ARG1(FUNCN, FUNC, TRET, TYPE1)                            \
   inline TRET FUNCN(TYPE1 a) { \
      return TRET(FUNC(a.s0), FUNC(a.s1), FUNC(a.s2), FUNC(a.s3)); }       
      
// Define 1 functions with vec4 types, takes in 2 argument 
#define DEF_FUNC1_4_ARG2(FUNC, TRET, TYPE1)                                           \
   inline TRET FUNC(TYPE1 a, TYPE1 b) { \
      return TRET(FUNC(a.s0, b.s0), FUNC(a.s1, b.s1), FUNC(a.s2, b.s2), FUNC(a.s3, b.s3)); } 
#define DEF_FUNC1_4_ARG2_A(FUNC, TRET, TYPE1, TYPE2)                                        \
   inline TRET FUNC(TYPE1 a, TYPE2 b) { \
      return TRET(FUNC(a.s0, b.s0), FUNC(a.s1, b.s1), FUNC(a.s2, b.s2), FUNC(a.s3, b.s3)); } 

// Define 1 functions with vec4 types, takes in 3 arguments
#define DEF_FUNC1_4_ARG3(FUNC, TRET, TYPE1)                                           \
   inline TRET FUNC(TYPE1 a, TYPE1 b, TYPE1 c) { \
      return TRET(FUNC(a.s0, b.s0, c.s0), FUNC(a.s1, b.s1, c.s1), FUNC(a.s2, b.s2, c.s2), FUNC(a.s3, b.s3, c.s3)); }
   
// Define 1 function with vec8 types, takes in 1 argument
#define DEF_FUNC1_8_ARG1(FUNC, TRET, TYPE1)                               \
   inline TRET FUNC(TYPE1 a) {                                            \
      return TRET(   FUNC(a.s0), FUNC(a.s1), FUNC(a.s2), FUNC(a.s3),       \
                     FUNC(a.s4), FUNC(a.s5), FUNC(a.s6), FUNC(a.s7)); } 
#define DEF_FUNC1N_8_ARG1(FUNCN, FUNC, TRET, TYPE1)                               \
   inline TRET FUNCN(TYPE1 a) {                                            \
      return TRET(   FUNC(a.s0), FUNC(a.s1), FUNC(a.s2), FUNC(a.s3),       \
                     FUNC(a.s4), FUNC(a.s5), FUNC(a.s6), FUNC(a.s7)); }                      
      
// Define 1 function with vec8 types, takes in 2 arguments
#define DEF_FUNC1_8_ARG2(FUNC, TRET, TYPE1)                                                    \
   inline TRET FUNC(TYPE1 a, TYPE1 b) { \
      return TRET(   FUNC(a.s0, b.s0), FUNC(a.s1, b.s1), FUNC(a.s2, b.s2), FUNC(a.s3, b.s3),\
                     FUNC(a.s4, b.s4), FUNC(a.s5, b.s5), FUNC(a.s6, b.s6), FUNC(a.s7, b.s7)); } 
#define DEF_FUNC1_8_ARG2_A(FUNC, TRET, TYPE1, TYPE2)                                                    \
   inline TRET FUNC(TYPE1 a, TYPE2 b) { \
      return TRET(   FUNC(a.s0, b.s0), FUNC(a.s1, b.s1), FUNC(a.s2, b.s2), FUNC(a.s3, b.s3),\
                     FUNC(a.s4, b.s4), FUNC(a.s5, b.s5), FUNC(a.s6, b.s6), FUNC(a.s7, b.s7)); } 

// Define 1 function with vec8 types, takes in 3 arguments
#define DEF_FUNC1_8_ARG3(FUNC, TRET, TYPE1)                                                    \
   inline TRET FUNC(TYPE1 a, TYPE1 b, TYPE1 c) {                                               \
      return TRET(   FUNC(a.s0, b.s0, c.s0), FUNC(a.s1, b.s1, c.s1), FUNC(a.s2, b.s2, c.s2), FUNC(a.s3, b.s3, c.s3),    \
                     FUNC(a.s4, b.s4, c.s4), FUNC(a.s5, b.s5, c.s5), FUNC(a.s6, b.s6, c.s6), FUNC(a.s7, b.s7, c.s7)); }

// Define 1 functions with vec16 types, takes in 1 argument
#if 1
#define DEF_FUNC1_16_ARG1(FUNC, TRET, TYPE1) inline TRET FUNC( TYPE1 a) {     \
   return TRET(   FUNC(a.s0), FUNC(a.s1), FUNC(a.s2), FUNC(a.s3),             \
                  FUNC(a.s4), FUNC(a.s5), FUNC(a.s6), FUNC(a.s7),             \
                  FUNC(a.s8), FUNC(a.s9), FUNC(a.sa), FUNC(a.sb),             \
                  FUNC(a.sc), FUNC(a.sd), FUNC(a.se), FUNC(a.sf)); }
#else
#define DCL_FUNC1_16_ARG1(FUNC, TRET, TYPE1)                                     \
   TRET FUNC(const TYPE1 a);

#endif

#define DEF_FUNC1N_16_ARG1(FUNCN, FUNC, TRET, TYPE1)                                     \
   inline TRET FUNCN(TYPE1 a) {                                            \
      return TRET(   FUNC(a.s0), FUNC(a.s1), FUNC(a.s2), FUNC(a.s3),       \
                     FUNC(a.s4), FUNC(a.s5), FUNC(a.s6), FUNC(a.s7),       \
                     FUNC(a.s8), FUNC(a.s9), FUNC(a.sa), FUNC(a.sb),       \
                     FUNC(a.sc), FUNC(a.sd), FUNC(a.se), FUNC(a.sf)); }                     
      
// Define 1 functions with vec16 types, takes in 2 argument 
#define DEF_FUNC1_16_ARG2(FUNC, TRET, TYPE1)                                                   \
   inline TRET FUNC(TYPE1 a, TYPE1 b) {                                                        \
      return TRET(   FUNC(a.s0, b.s0), FUNC(a.s1, b.s1), FUNC(a.s2, b.s2), FUNC(a.s3, b.s3),    \
                     FUNC(a.s4, b.s4), FUNC(a.s5, b.s5), FUNC(a.s6, b.s6), FUNC(a.s7, b.s7),    \
                     FUNC(a.s8, b.s8), FUNC(a.s9, b.s9), FUNC(a.sa, b.sa), FUNC(a.sb, b.sb),    \
                     FUNC(a.sc, b.sc), FUNC(a.sd, b.sd), FUNC(a.se, b.se), FUNC(a.sf, b.sf)); }
#define DEF_FUNC1_16_ARG2_A(FUNC, TRET, TYPE1, TYPE2)                                                   \
   inline TRET FUNC(TYPE1 a, TYPE2 b) {                                                        \
      return TRET(   FUNC(a.s0, b.s0), FUNC(a.s1, b.s1), FUNC(a.s2, b.s2), FUNC(a.s3, b.s3),    \
                     FUNC(a.s4, b.s4), FUNC(a.s5, b.s5), FUNC(a.s6, b.s6), FUNC(a.s7, b.s7),    \
                     FUNC(a.s8, b.s8), FUNC(a.s9, b.s9), FUNC(a.sa, b.sa), FUNC(a.sb, b.sb),    \
                     FUNC(a.sc, b.sc), FUNC(a.sd, b.sd), FUNC(a.se, b.se), FUNC(a.sf, b.sf)); }
                     
// Define 1 function with vec16 types, takes in 3 arguments 
#define DEF_FUNC1_16_ARG3(FUNC, TRET, TYPE1)                                                   \
   inline TRET FUNC(TYPE1 a, TYPE1 b, TYPE1 c) {                                                        \
      return TRET(   FUNC(a.s0, b.s0, c.s0), FUNC(a.s1, b.s1, c.s1), FUNC(a.s2, b.s2, c.s2), FUNC(a.s3, b.s3, c.s3),    \
                     FUNC(a.s4, b.s4, c.s4), FUNC(a.s5, b.s5, c.s5), FUNC(a.s6, b.s6, c.s6), FUNC(a.s7, b.s7, c.s7),    \
                     FUNC(a.s8, b.s8, c.s8), FUNC(a.s9, b.s9, c.s9), FUNC(a.sa, b.sa, c.sa), FUNC(a.sb, b.sb, c.sb),    \
                     FUNC(a.sc, b.sc, c.sc), FUNC(a.sd, b.sd, c.sd), FUNC(a.se, b.se, c.se), FUNC(a.sf, b.sf, c.sf)); }
   
////////////////////////////////////////////////////////////////////////   
// Define 2 functions with vec2 types, takes in 1 argument
#define DEF_FUNC2_2_ARG1(FUNC, TYPE1, TYPE2)                            \
   inline TYPE1 FUNC(TYPE1 a) { return TYPE1(FUNC(a.s0), FUNC(a.s1)); } \
   inline TYPE2 FUNC(TYPE2 a) { return TYPE2(FUNC(a.s0), FUNC(a.s1)); }  

// Define 2 functions with vec2 types, takes in 2 arguments
#define DEF_FUNC2_2_ARG2(FUNC, TYPE1, TYPE2)                                              \
   inline TYPE1 FUNC(TYPE1 a, TYPE1 b) { return TYPE1(FUNC(a.s0, b.s0), FUNC(a.s1, b.s1)); } \
   inline TYPE2 FUNC(TYPE2 a, TYPE2 b) { return TYPE2(FUNC(a.s0, b.s0), FUNC(a.s1, b.s1)); } 

// Define 2 functions with vec2 types, takes in 3 arguments  
#define DEF_FUNC2_2_ARG3(FUNC, TYPE1, TYPE2)                                              \
   inline TYPE1 FUNC(TYPE1 a, TYPE1 b, TYPE1 c) { return TYPE1(FUNC(a.s0, b.s0, c.s0), FUNC(a.s1, b.s1, c.s1)); } \
   inline TYPE2 FUNC(TYPE2 a, TYPE2 b, TYPE2 c) { return TYPE2(FUNC(a.s0, b.s0, c.s0), FUNC(a.s1, b.s1, c.s1)); } 
   

// Define 2 functions with vec3 types, takes in 1 arguments
#define DEF_FUNC2_3_ARG1(FUNC, TYPE1, TYPE2)             \
   inline TYPE1 FUNC(TYPE1 a) { \
      return TYPE1(FUNC(a.s0), FUNC(a.s1), FUNC(a.s2)); } \
   inline TYPE2 FUNC(TYPE2 a) { \
      return TYPE2(FUNC(a.s0), FUNC(a.s1), FUNC(a.s2)); }   
      
// Define 2 functions with vec3 types, takes in 2 arguments
#define DEF_FUNC2_3_ARG2(FUNC, TYPE1, TYPE2)                            \
   inline TYPE1 FUNC(TYPE1 a, TYPE1 b) { \
      return TYPE1(FUNC(a.s0, b.s0), FUNC(a.s1, b.s1), FUNC(a.s2, b.s2)); } \
   inline TYPE2 FUNC(TYPE2 a, TYPE2 b) { \
      return TYPE2(FUNC(a.s0, b.s0), FUNC(a.s1, b.s1), FUNC(a.s2, b.s2)); }   
      
// Define 2 functions with vec3 types, takes in 3 arguments
#define DEF_FUNC2_3_ARG3(FUNC, TYPE1, TYPE2)                            \
      DEF_FUNC1_3_ARG3(FUNC, TYPE1)                                     \
      DEF_FUNC1_3_ARG3(FUNC, TYPE2)
      
// Define 2 functions with vec4 types, takes in 1 argument
#define DEF_FUNC2_4_ARG1(FUNC, TYPE1, TYPE2)                            \
   inline TYPE1 FUNC(TYPE1 a) { \
      return TYPE1(FUNC(a.s0), FUNC(a.s1), FUNC(a.s2), FUNC(a.s3)); } \
   inline TYPE2 FUNC(TYPE2 a) { \
      return TYPE2(FUNC(a.s0), FUNC(a.s1), FUNC(a.s2), FUNC(a.s3)); }
      
// Define 2 functions with vec4 types, takes in 2 argument 
#define DEF_FUNC2_4_ARG2(FUNC, TYPE1, TYPE2)                                           \
   inline TYPE1 FUNC(TYPE1 a, TYPE1 b) { \
      return TYPE1(FUNC(a.s0, b.s0), FUNC(a.s1, b.s1), FUNC(a.s2, b.s2), FUNC(a.s3, b.s3)); } \
   inline TYPE2 FUNC(TYPE2 a, TYPE2 b) { \
      return TYPE2(FUNC(a.s0, b.s0), FUNC(a.s1, b.s1), FUNC(a.s2, b.s2), FUNC(a.s3, b.s3)); } 

// Define 2 functions with vec4 types, takes in 3 arguments
#define DEF_FUNC2_4_ARG3(FUNC, TYPE1, TYPE2)                            \
      DEF_FUNC1_4_ARG3(FUNC, TYPE1)                                     \
      DEF_FUNC1_4_ARG3(FUNC, TYPE2)
 
// Define 2 functions with vec8 types, takes in 1 argument
#define DEF_FUNC2_8_ARG1(FUNC, TYPE1, TYPE2)                               \
   inline TYPE1 FUNC(TYPE1 a) {                                            \
      return TYPE1(  FUNC(a.s0), FUNC(a.s1), FUNC(a.s2), FUNC(a.s3),       \
                     FUNC(a.s4), FUNC(a.s5), FUNC(a.s6), FUNC(a.s7)); }    \
   inline TYPE2 FUNC(TYPE2 a) {                                            \
      return TYPE2(  FUNC(a.s0), FUNC(a.s1), FUNC(a.s2), FUNC(a.s3),       \
                     FUNC(a.s4), FUNC(a.s5), FUNC(a.s6), FUNC(a.s7)); }
      
// Define 2 functions with vec8 types, takes in 2 arguments
#define DEF_FUNC2_8_ARG2(FUNC, TYPE1, TYPE2)                                                    \
   inline TYPE1 FUNC(TYPE1 a, TYPE1 b) { \
      return TYPE1(  FUNC(a.s0, b.s0), FUNC(a.s1, b.s1), FUNC(a.s2, b.s2), FUNC(a.s3, b.s3),\
                     FUNC(a.s4, b.s4), FUNC(a.s5, b.s5), FUNC(a.s6, b.s6), FUNC(a.s7, b.s7)); } \
   inline TYPE2 FUNC(TYPE2 a, TYPE2 b) { \
      return TYPE2(  FUNC(a.s0, b.s0), FUNC(a.s1, b.s1), FUNC(a.s2, b.s2), FUNC(a.s3, b.s3),\
                     FUNC(a.s4, b.s4), FUNC(a.s5, b.s5), FUNC(a.s6, b.s6), FUNC(a.s7, b.s7)); }

// Define 1 function with vec8 types, takes in 3 arguments
#define DEF_FUNC2_8_ARG3(FUNC, TYPE1, TYPE2)                            \
      DEF_FUNC1_8_ARG3(FUNC, TYPE1)                                     \
      DEF_FUNC1_8_ARG3(FUNC, TYPE2)

// Define 2 functions with vec16 types, takes in 1 argument
#define DEF_FUNC2_16_ARG1(FUNC, TYPE1, TYPE2)                              \
   inline TYPE1 FUNC(TYPE1 a) {                                            \
      return TYPE1(  FUNC(a.s0), FUNC(a.s1), FUNC(a.s2), FUNC(a.s3),       \
                     FUNC(a.s4), FUNC(a.s5), FUNC(a.s6), FUNC(a.s3),       \
                     FUNC(a.s8), FUNC(a.s9), FUNC(a.sa), FUNC(a.sb),       \
                     FUNC(a.sc), FUNC(a.sd), FUNC(a.se), FUNC(a.sf)); }    \
   inline TYPE2 FUNC(TYPE2 a) {                                            \
      return TYPE2(  FUNC(a.s0), FUNC(a.s1), FUNC(a.s2), FUNC(a.s3),       \
                     FUNC(a.s4), FUNC(a.s5), FUNC(a.s6), FUNC(a.s3),       \
                     FUNC(a.s8), FUNC(a.s9), FUNC(a.sa), FUNC(a.sb),       \
                     FUNC(a.sc), FUNC(a.sd), FUNC(a.se), FUNC(a.sf)); }  
      
// Define 2 functions with vec16 types, takes in 2 argument 
#define DEF_FUNC2_16_ARG2(FUNC, TYPE1, TYPE2)                                                   \
   inline TYPE1 FUNC(TYPE1 a, TYPE1 b) {                                                        \
      return TYPE1(  FUNC(a.s0, b.s0), FUNC(a.s1, b.s1), FUNC(a.s2, b.s2), FUNC(a.s3, b.s3),    \
                     FUNC(a.s4, b.s4), FUNC(a.s5, b.s5), FUNC(a.s6, b.s6), FUNC(a.s7, b.s7),    \
                     FUNC(a.s8, b.s8), FUNC(a.s9, b.s9), FUNC(a.sa, b.sa), FUNC(a.sb, b.sb),    \
                     FUNC(a.sc, b.sc), FUNC(a.sd, b.sd), FUNC(a.se, b.se), FUNC(a.sf, b.sf)); } \
   inline TYPE2 FUNC(TYPE2 a, TYPE2 b) {                                                        \
      return TYPE2(  FUNC(a.s0, b.s0), FUNC(a.s1, b.s1), FUNC(a.s2, b.s2), FUNC(a.s3, b.s3),    \
                     FUNC(a.s4, b.s4), FUNC(a.s5, b.s5), FUNC(a.s6, b.s6), FUNC(a.s7, b.s7),    \
                     FUNC(a.s8, b.s8), FUNC(a.s9, b.s9), FUNC(a.sa, b.sa), FUNC(a.sb, b.sb),    \
                     FUNC(a.sc, b.sc), FUNC(a.sd, b.sd), FUNC(a.se, b.se), FUNC(a.sf, b.sf)); }

// Define 1 function with vec16 types, takes in 3 arguments 
#define DEF_FUNC2_16_ARG3(FUNC, TYPE1, TYPE2)                            \
      DEF_FUNC1_16_ARG3(FUNC, TYPE1)                                     \
      DEF_FUNC1_16_ARG3(FUNC, TYPE2)
        
#define DEF_FUNC_N_ARG1(FUNC, _RET, _TYPE)        \
   DEF_FUNC1_2_ARG1 (FUNC,  _RET##2,  _TYPE##2)   \
   DEF_FUNC1_3_ARG1 (FUNC,  _RET##3,  _TYPE##3)   \
   DEF_FUNC1_4_ARG1 (FUNC,  _RET##4,  _TYPE##4)   \
   DEF_FUNC1_8_ARG1 (FUNC,  _RET##8,  _TYPE##8)   \
   DEF_FUNC1_16_ARG1(FUNC,  _RET##16, _TYPE##16)
   //DCL_FUNC1_16_ARG1(FUNC,  _RET##16, _TYPE##16)
   
#define DEF_FUNCN_N_ARG1(FUNC, MOD, RND, _RET, _TYPE)        \
   DEF_FUNC1N_2_ARG1 (FUNC##2##MOD##RND, FUNC##MOD##RND, _RET##2,  _TYPE##2)   \
   DEF_FUNC1N_3_ARG1 (FUNC##3##MOD##RND, FUNC##MOD##RND,  _RET##3,  _TYPE##3)   \
   DEF_FUNC1N_4_ARG1 (FUNC##4##MOD##RND, FUNC##MOD##RND,  _RET##4,  _TYPE##4)   \
   DEF_FUNC1N_8_ARG1 (FUNC##8##MOD##RND, FUNC##MOD##RND,  _RET##8,  _TYPE##8)   \
   DEF_FUNC1N_16_ARG1(FUNC##16##MOD##RND, FUNC##MOD##RND,  _RET##16, _TYPE##16)

#define DEF_FUNCN_N_ARG1_NO_16(FUNC, MOD, RND, _RET, _TYPE)        \
   DEF_FUNC1N_2_ARG1 (FUNC##2##MOD##RND, FUNC##MOD##RND, _RET##2,  _TYPE##2)   \
   DEF_FUNC1N_3_ARG1 (FUNC##3##MOD##RND, FUNC##MOD##RND,  _RET##3,  _TYPE##3)   \
   DEF_FUNC1N_4_ARG1 (FUNC##4##MOD##RND, FUNC##MOD##RND,  _RET##4,  _TYPE##4)   \
   DEF_FUNC1N_8_ARG1 (FUNC##8##MOD##RND, FUNC##MOD##RND,  _RET##8,  _TYPE##8)

#define DEF_FUNC_N_ARG2(FUNC, _RET, _TYPE)    \
   DEF_FUNC1_2_ARG2 (FUNC,  _RET##2,  _TYPE##2)   \
   DEF_FUNC1_3_ARG2 (FUNC,  _RET##3,  _TYPE##3)   \
   DEF_FUNC1_4_ARG2 (FUNC,  _RET##4,  _TYPE##4)   \
   DEF_FUNC1_8_ARG2 (FUNC,  _RET##8,  _TYPE##8)   \
   DEF_FUNC1_16_ARG2(FUNC,  _RET##16, _TYPE##16)

#define DEF_FUNC_N_ARG2_A(FUNC, _RET, _TYPEA, _TYPEB)    \
   DEF_FUNC1_2_ARG2_A (FUNC,  _RET##2,  _TYPEA##2,  _TYPEB##2)   \
   DEF_FUNC1_3_ARG2_A (FUNC,  _RET##3,  _TYPEA##3,  _TYPEB##3)   \
   DEF_FUNC1_4_ARG2_A (FUNC,  _RET##4,  _TYPEA##4,  _TYPEB##4)   \
   DEF_FUNC1_8_ARG2_A (FUNC,  _RET##8,  _TYPEA##8,  _TYPEB##8)   \
   DEF_FUNC1_16_ARG2_A(FUNC,  _RET##16, _TYPEA##16, _TYPEB##16)

#define DEF_FUNC_N_ARG3(FUNC, _RET, _TYPE)    \
   DEF_FUNC1_2_ARG3 (FUNC,  _RET##2,  _TYPE##2)   \
   DEF_FUNC1_3_ARG3 (FUNC,  _RET##3,  _TYPE##3)   \
   DEF_FUNC1_4_ARG3 (FUNC,  _RET##4,  _TYPE##4)   \
   DEF_FUNC1_8_ARG3 (FUNC,  _RET##8,  _TYPE##8)   \
   DEF_FUNC1_16_ARG3(FUNC,  _RET##16, _TYPE##16)

#define DEF_FUNC_ARG1(FUNC)                                         \
   DEF_FUNC_N_ARG1(FUNC, uchar,        uchar)                       \
   DEF_FUNC_N_ARG1(FUNC, char,         char)                        \
   DEF_FUNC_N_ARG1(FUNC, short,        short)                       \
   DEF_FUNC_N_ARG1(FUNC, ushort,       ushort)                      \
   DEF_FUNC_N_ARG1(FUNC, int,          int)                         \
   DEF_FUNC_N_ARG1(FUNC, uint,         uint)                        /*\
   DEF_FUNC_N_ARG1(FUNC, vec_short,    vec_short)                   \
   DEF_FUNC_N_ARG1(FUNC, vec_ushort,   vec_ushort)                  \
   DEF_FUNC_N_ARG1(FUNC, vec_int,      vec_int)                     \
   DEF_FUNC_N_ARG1(FUNC, vec_uint,     vec_uint)
   */

#define DEF_FUNC_ARG1_U(FUNC)                                       \
   DEF_FUNC_N_ARG1(FUNC, uchar,        char)                        \
   DEF_FUNC_N_ARG1(FUNC, uchar,        uchar)                       \
   DEF_FUNC_N_ARG1(FUNC, ushort,       short)                       \
   DEF_FUNC_N_ARG1(FUNC, ushort,       ushort)                      \
   DEF_FUNC_N_ARG1(FUNC, uint,         int)                         \
   DEF_FUNC_N_ARG1(FUNC, uint,         uint)                        /*\
   DEF_FUNC_N_ARG1(FUNC, vec_ushort,   vec_short)                   \
   DEF_FUNC_N_ARG1(FUNC, vec_ushort,   vec_ushort)                  \
   DEF_FUNC_N_ARG1(FUNC, vec_uint,     vec_int)                     \
   DEF_FUNC_N_ARG1(FUNC, vec_uint,     vec_uint)
   */

#define DEF_FUNC_ARG2(FUNC)                                         \
   DEF_FUNC_N_ARG2(FUNC, char,         char)                        \
   DEF_FUNC_N_ARG2(FUNC, uchar,        uchar)                       \
   DEF_FUNC_N_ARG2(FUNC, short,        short)                       \
   DEF_FUNC_N_ARG2(FUNC, ushort,       ushort)                      \
   DEF_FUNC_N_ARG2(FUNC, int,          int)                         \
   DEF_FUNC_N_ARG2(FUNC, uint,         uint)                        /*\
   DEF_FUNC_N_ARG2(FUNC, vec_short,    vec_short)                   \
   DEF_FUNC_N_ARG2(FUNC, vec_ushort,   vec_ushort)                  \
   DEF_FUNC_N_ARG2(FUNC, vec_int,      vec_int)                     \
   DEF_FUNC_N_ARG2(FUNC, vec_uint,     vec_uint)
   */

#define DEF_FUNC_ARG2_U(FUNC)                                       \
   DEF_FUNC_N_ARG2(FUNC, uchar,        char)                        \
   DEF_FUNC_N_ARG2(FUNC, uchar,        uchar)                       \
   DEF_FUNC_N_ARG2(FUNC, ushort,       short)                       \
   DEF_FUNC_N_ARG2(FUNC, ushort,       ushort)                      \
   DEF_FUNC_N_ARG2(FUNC, uint,         int)                         \
   DEF_FUNC_N_ARG2(FUNC, uint,         uint)                        /*\
   DEF_FUNC_N_ARG2(FUNC, vec_ushort,   vec_short)                   \
   DEF_FUNC_N_ARG2(FUNC, vec_ushort,   vec_ushort)                  \
   DEF_FUNC_N_ARG2(FUNC, vec_uint,     vec_int)                     \
   DEF_FUNC_N_ARG2(FUNC, vec_uint,     vec_uint)
   */
   
#define DEF_FUNC_ARG3(FUNC)                                         \
   DEF_FUNC_N_ARG3(FUNC, char,         char)                        \
   DEF_FUNC_N_ARG3(FUNC, uchar,        uchar)                       \
   DEF_FUNC_N_ARG3(FUNC, short,        short)                       \
   DEF_FUNC_N_ARG3(FUNC, ushort,       ushort)                      \
   DEF_FUNC_N_ARG3(FUNC, int,          int)                         \
   DEF_FUNC_N_ARG3(FUNC, uint,         uint)                        /*\
   DEF_FUNC_N_ARG3(FUNC, vec_short,    vec_short)                   \
   DEF_FUNC_N_ARG3(FUNC, vec_ushort,   vec_ushort)                  \
   DEF_FUNC_N_ARG3(FUNC, vec_int,      vec_int)                     \
   DEF_FUNC_N_ARG3(FUNC, vec_uint,     vec_uint)
   */

#define DEF_FUNCN_N_ARG1_MOD_RND(FUNC, RET, TYPE)              \
   DEF_FUNCN_N_ARG1(FUNC, , , RET, TYPE)                       \
   DEF_FUNCN_N_ARG1(FUNC, , _rte, RET, TYPE)                   \
   DEF_FUNCN_N_ARG1(FUNC, , _rtp, RET, TYPE)                   \
   DEF_FUNCN_N_ARG1(FUNC, , _rtn, RET, TYPE)                   \
   DEF_FUNCN_N_ARG1(FUNC, , _rtz, RET, TYPE)                   \
   DEF_FUNCN_N_ARG1(FUNC, _sat, , RET, TYPE)                   \
   DEF_FUNCN_N_ARG1(FUNC, _sat, _rte, RET, TYPE)               \
   DEF_FUNCN_N_ARG1(FUNC, _sat, _rtp, RET, TYPE)               \
   DEF_FUNCN_N_ARG1(FUNC, _sat, _rtn, RET, TYPE)               \
   DEF_FUNCN_N_ARG1(FUNC, _sat, _rtz, RET, TYPE)              /* \
   DEF_FUNCN_N_ARG1(FUNC, _sat, _rte, vec_##RET, vec_##TYPE)   \
   DEF_FUNCN_N_ARG1(FUNC, _sat, _rtp, vec_##RET, vec_##TYPE)   \
   DEF_FUNCN_N_ARG1(FUNC, _sat, , vec_##RET, vec_##TYPE)       \
   DEF_FUNCN_N_ARG1(FUNC, , _rtz, vec_##RET, vec_##TYPE)       \
   DEF_FUNCN_N_ARG1(FUNC, , _rtn, vec_##RET, vec_##TYPE)       \
   DEF_FUNCN_N_ARG1(FUNC, , _rtp, vec_##RET, vec_##TYPE)       \
   DEF_FUNCN_N_ARG1(FUNC, , _rte, vec_##RET, vec_##TYPE)       \
   DEF_FUNCN_N_ARG1(FUNC, , , vec_##RET, vec_##TYPE)           \
   DEF_FUNCN_N_ARG1(FUNC, _sat, _rtz, vec_##RET, vec_##TYPE)
   */

#define DEF_FUNCN_N_ARG1_MOD_RND_NO_VEC(FUNC, RET, TYPE)       \
   DEF_FUNCN_N_ARG1_NO_16(FUNC, , , RET, TYPE)                       \
   DEF_FUNCN_N_ARG1_NO_16(FUNC, , _rte, RET, TYPE)                   \
   DEF_FUNCN_N_ARG1_NO_16(FUNC, , _rtp, RET, TYPE)                   \
   DEF_FUNCN_N_ARG1_NO_16(FUNC, , _rtn, RET, TYPE)                   \
   DEF_FUNCN_N_ARG1_NO_16(FUNC, , _rtz, RET, TYPE)                   \
   DEF_FUNCN_N_ARG1_NO_16(FUNC, _sat, , RET, TYPE)                   \
   DEF_FUNCN_N_ARG1_NO_16(FUNC, _sat, _rte, RET, TYPE)               \
   DEF_FUNCN_N_ARG1_NO_16(FUNC, _sat, _rtp, RET, TYPE)               \
   DEF_FUNCN_N_ARG1_NO_16(FUNC, _sat, _rtn, RET, TYPE)               \
   DEF_FUNCN_N_ARG1_NO_16(FUNC, _sat, _rtz, RET, TYPE)

#define DEF_FUNCN_N_ARG1_RND_NO_VEC(FUNC, RET, TYPE)  \
   DEF_FUNCN_N_ARG1_NO_16(FUNC, , , RET, TYPE)              \
   DEF_FUNCN_N_ARG1_NO_16(FUNC, , _rte, RET, TYPE)          \
   DEF_FUNCN_N_ARG1_NO_16(FUNC, , _rtp, RET, TYPE)          \
   DEF_FUNCN_N_ARG1_NO_16(FUNC, , _rtn, RET, TYPE)          \
   DEF_FUNCN_N_ARG1_NO_16(FUNC, , _rtz, RET, TYPE)

#define DEF_FUNCN_ARG1_RND_NO_VEC(FUNC, RET)             \
   DEF_FUNCN_N_ARG1_RND_NO_VEC(FUNC, RET, uchar)         \
   DEF_FUNCN_N_ARG1_RND_NO_VEC(FUNC, RET, char)          \
   DEF_FUNCN_N_ARG1_RND_NO_VEC(FUNC, RET, ushort)        \
   DEF_FUNCN_N_ARG1_RND_NO_VEC(FUNC, RET, short)         \
   DEF_FUNCN_N_ARG1_RND_NO_VEC(FUNC, RET, uint)          \
   DEF_FUNCN_N_ARG1_RND_NO_VEC(FUNC, RET, int)           \
   DEF_FUNCN_N_ARG1_RND_NO_VEC(FUNC, RET, float)

#define DEF_FUNCN_ARG1_MOD_RND(FUNC, RET)             \
   DEF_FUNCN_N_ARG1_MOD_RND(FUNC, RET, uchar)         \
   DEF_FUNCN_N_ARG1_MOD_RND(FUNC, RET, char)          \
   DEF_FUNCN_N_ARG1_MOD_RND(FUNC, RET, ushort)        \
   DEF_FUNCN_N_ARG1_MOD_RND(FUNC, RET, short)         \
   DEF_FUNCN_N_ARG1_MOD_RND(FUNC, RET, uint)          \
   DEF_FUNCN_N_ARG1_MOD_RND(FUNC, RET, int)           \
   DEF_FUNCN_N_ARG1_MOD_RND_NO_VEC(FUNC, RET, float)


DEF_FUNC_ARG1(clz)
DEF_FUNC_ARG1(popcount)
DEF_FUNC_ARG2(hadd)
DEF_FUNC_ARG2(rhadd)
DEF_FUNC_ARG2(mul_hi)
DEF_FUNC_ARG2(rotate)
DEF_FUNC_ARG3(clamp)
DEF_FUNC_ARG3(mad_sat)
DEF_FUNC_ARG3(mad_hi)
DEF_FUNC_ARG2(max)
DEF_FUNC_ARG2(min)
DEF_FUNC_ARG1_U(abs)
DEF_FUNC_ARG2_U(abs_diff)
DEF_FUNC_ARG2(add_sat)
DEF_FUNC_ARG2(sub_sat)


// upsample 
DEF_FUNC_N_ARG2_A(upsample, short,        char,   uchar)
DEF_FUNC_N_ARG2_A(upsample, ushort,       uchar,  uchar)
DEF_FUNC_N_ARG2_A(upsample, int,          short,  ushort)
DEF_FUNC_N_ARG2_A(upsample, uint,         ushort, ushort)
/*
DEF_FUNC_N_ARG2_A(upsample, vec_short,    vec_char,   vec_uchar)
DEF_FUNC_N_ARG2_A(upsample, vec_ushort,   vec_uchar,  vec_uchar)
DEF_FUNC_N_ARG2_A(upsample, vec_uint,     vec_short,  vec_ushort)
DEF_FUNC_N_ARG2_A(upsample, vec_uint,     vec_ushort, vec_ushort)
*/

// table 6.11
DEF_FUNC_N_ARG2(mul24, int,          int)
DEF_FUNC_N_ARG2(mul24, uint,         uint)
/*
DEF_FUNC_N_ARG2(mul24, vec_int,      vec_int)
DEF_FUNC_N_ARG2(mul24, vec_uint,     vec_uint)
*/

DEF_FUNC_N_ARG3(mad24, int,          int)
DEF_FUNC_N_ARG3(mad24, uint,         uint)
//DEF_FUNC_N_ARG3(mad24, vec_int,      vec_int)
//DEF_FUNC_N_ARG3(mad24, vec_uint,     vec_uint)

// 6.2.3 Explicit conversions
DEF_FUNCN_ARG1_MOD_RND(convert_uchar, uchar)
DEF_FUNCN_ARG1_MOD_RND(convert_char, char)
DEF_FUNCN_ARG1_MOD_RND(convert_ushort, ushort)
DEF_FUNCN_ARG1_MOD_RND(convert_short, short)
DEF_FUNCN_ARG1_MOD_RND(convert_uint, uint)
DEF_FUNCN_ARG1_MOD_RND(convert_int, int)
DEF_FUNCN_ARG1_RND_NO_VEC(convert_float, float)

// vloadX<T> interface
#if 0
#define DCL_OVEC_LDST_N(_DTYPE, _PTYPE, _N, _SIZE, _ALGN)                                          \
_DTYPE##_N        vload##_N(size_t offset, const GLOBAL(_PTYPE) *p);                               \
vec_##_DTYPE##_N  vload##_N(vec_size_t offset, const GLOBAL(_PTYPE) *p);                           \
void              vload##_N(_DTYPE##_N* dst, size_t offset, const GLOBAL(_PTYPE) *p);              \
void              vload##_N(vec_##_DTYPE##_N* dst, vec_size_t offset, const GLOBAL(_PTYPE) *p);    \
void              vstore##_N(_DTYPE##_N data, size_t offset, GLOBAL(_PTYPE) *p);                   \
void              vstore##_N(vec_##_DTYPE##_N data, vec_size_t offset, GLOBAL(_PTYPE) *p);
#else

#define DCL_OVEC_LDST_N_VAL(_DTYPE, _PTYPE, _N, _SIZE, _ALGN)                                      \
_DTYPE##_N        vload##_N(size_t offset, const GLOBAL(_PTYPE) *p);                               \
vec_##_DTYPE##_N  vload##_N(vec_size_t offset, const GLOBAL(_PTYPE) *p);                           \
void              vstore##_N(_DTYPE##_N data, size_t offset, GLOBAL(_PTYPE) *p);                   \
void              vstore##_N(vec_##_DTYPE##_N  data, vec_size_t offset, GLOBAL(_PTYPE) *p);

#define DCL_OVEC_LDST_N_REF(_DTYPE, _PTYPE, _N, _SIZE, _ALGN)                                      \
_DTYPE##_N        vload##_N(size_t offset, const GLOBAL(_PTYPE) *p);                               \
vec_##_DTYPE##_N  vload##_N(vec_size_t offset, const GLOBAL(_PTYPE) *p);                           \
void              vstore##_N(const _DTYPE##_N& data, size_t offset, GLOBAL(_PTYPE) *p);            \
void              vstore##_N(const vec_##_DTYPE##_N&  data, vec_size_t offset, GLOBAL(_PTYPE) *p);

#endif



#define DCL_OVEC_LDST(_DTYPE, _PTYPE)                                         \
DCL_OVEC_LDST_N_VAL(_DTYPE, _PTYPE,  2, sizeof(_DTYPE##2 ), sizeof(_PTYPE))   \
DCL_OVEC_LDST_N_VAL(_DTYPE, _PTYPE,  3, sizeof(_DTYPE##3 ), sizeof(_PTYPE))   \
DCL_OVEC_LDST_N_VAL(_DTYPE, _PTYPE,  4, sizeof(_DTYPE##4 ), sizeof(_PTYPE))   \
DCL_OVEC_LDST_N_VAL(_DTYPE, _PTYPE,  8, sizeof(_DTYPE##8 ), sizeof(_PTYPE))   \
DCL_OVEC_LDST_N_VAL(_DTYPE, _PTYPE, 16, sizeof(_DTYPE##16), sizeof(_PTYPE))
//DCL_OVEC_LDST_N_REF(_DTYPE, _PTYPE, 16, sizeof(_DTYPE##16), sizeof(_PTYPE))

// DCL_OVEC_LDST_N(_DTYPE, _PTYPE, 16, sizeof(_DTYPE##16), sizeof(_PTYPE))

DCL_OVEC_LDST(char,     char)
DCL_OVEC_LDST(uchar,    uchar)
DCL_OVEC_LDST(short,    short)
DCL_OVEC_LDST(ushort,   ushort)
DCL_OVEC_LDST(int,      int)
DCL_OVEC_LDST(uint,     uint)

#endif
