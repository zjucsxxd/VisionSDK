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
/**
* \file APU_vec.cpp
* \brief APU vector implementation
* \author Igor Aleksandrowicz
* \version
* \date 21-November-2013
****************************************************************************/

#include "apu_vec.hpp"
#include "apu_cond.hpp"

using namespace APEX2;

/****************************************************************************
* functions
****************************************************************************/

////////////////
//APU-C specialized 16-bit shifts definitions
////////////////
void APEX2::vsllx (vec16u &resLow, vec16s &resHigh, const vec16s& va, const vec16s& vb, const vec16s& vs) 
{
  ADD_VECTOR_CYCLES_FUNCTION(vec16s, special_shift)
  vec32s v = (vec32s(vb) << 16) | va;
  v = vsll(v, vec32s(vs));
  resHigh = (v >> 16) & 0xffff;
  resLow = vec16u(v & 0xffff);
}

void APEX2::vsrax(vec16u &resLow, vec16s &resHigh, const vec16s& va, const vec16s& vb, const vec16s& vs)
{
  ADD_VECTOR_CYCLES_FUNCTION(vec16s, special_shift)
  vec32s v = (vec32s(vb) << 16) | va;
  v = vsra(v, vec32s(vs));
  resHigh = (v >> 16) & 0xffff;
  resLow = vec16u(v & 0xffff);
}

void APEX2::vsrlx(vec16u &resLow, vec16s &resHigh, const vec16s& va, const vec16s& vb, const vec16s& vs)
{
  ADD_VECTOR_CYCLES_FUNCTION(vec16s, special_shift)
  vec32s v = (vec32s(vb) << 16) | va;
  v = vsrl(v, vec32s(vs));
  resHigh = (v >> 16) & 0xffff;
  resLow = vec16u(v & 0xffff);
}

void APEX2::vsllx(vec16u &resLow, vec16u &resHigh, const vec16u& va, const vec16u& vb, const vec16u& vs)
{
  ADD_VECTOR_CYCLES_FUNCTION(vec16s, special_shift)
  vec32u v = (vec32u(vb) << 16) | va;
  v = vsll(v, vec32u(vs));
  resHigh = (v >> 16) & 0xffff;
  resLow = vec16u(v & 0xffff);
}

void APEX2::vsrax(vec16u &resLow, vec16u &resHigh, const vec16u& va, const vec16u& vb, const vec16u& vs)
{
  ADD_VECTOR_CYCLES_FUNCTION(vec16s, special_shift)
  vec32u v = (vec32u(vb) << 16) | va;
  v = vsra(v, vec32u(vs));
  resHigh = (v >> 16) & 0xffff;
  resLow = vec16u(v & 0xffff);
}

void APEX2::vsrlx(vec16u &resLow, vec16u &resHigh, const vec16u& va, const vec16u& vb, const vec16u& vs)
{
  ADD_VECTOR_CYCLES_FUNCTION(vec16s, special_shift)
  vec32u v = (vec32u(vb) << 16) | va;
  v = vsrl(v, vec32u(vs));
  resHigh = (v >> 16) & 0xffff;
  resLow = vec16u(v & 0xffff);
}

//common specialized 16-bit multiplication function
//the specialized multiplications work on high or low bytes of input values only
static vec16s specializedMult(bool aSigned, bool aHigh, bool bSigned, bool bHigh, const vec16u& a, const vec16u& b)
{
  ADD_VECTOR_CYCLES_FUNCTION(vec16s, special_multiplication)
  vec16u a8 = aHigh ? ((a >> 8) & 0xff) : (a & 0xff);
  vec16u b8 = bHigh ? ((b >> 8) & 0xff) : (b & 0xff);
  vec16u extSignA = aHigh ? ((vec16s)a) >> 15 : ((((vec16s)a) & 0x80) << 7) >> 15;
  vec16u extSignB = bHigh ? ((vec16s)b) >> 15 : ((((vec16s)b) & 0x80) << 7) >> 15;
  vec16s ret;
  if (aSigned && !bSigned)
  {
    ret = vec16s(a8 | extSignA) * vec16u(b8);
  }
  else if (aSigned && bSigned)
  {
	  ret = vec16s(a8 | extSignA) * vec16s(b8 | extSignB);
  }
  else if (!aSigned && !bSigned)
  {
    ret = vec16u(a8) * vec16u(b8);
  }
  else if (!aSigned && bSigned)
  {
	  ret = vec16u(a8) * vec16s(b8 | extSignB);
  }
  return ret;
}

//APU-C specialized 16-bit multiplication definitions using the common function
vec16s APEX2::vmul_ulul (const vec16s& a, const vec16s& b)
{
  return specializedMult(false, false, false, false, vec16u(a), vec16u(b));
}

vec16s APEX2::vmul_uluh (const vec16s& a, const vec16s& b)
{
  return specializedMult(false, false, false, true, vec16u(a), vec16u(b));
}

vec16s APEX2::vmul_ulsh (const vec16s& a, const vec16s& b)
{
  return specializedMult(false, false, true, true, vec16u(a), vec16u(b));
}

vec16s APEX2::vmul_slul(const vec16s& a, const vec16s& b){
  return specializedMult(true, false, false, false, vec16u(a), vec16u(b));
}


vec16s APEX2::vmul_slul(const vec16u& a, const vec16u& b){
	return specializedMult(true, false, false, false, vec16u(a), vec16u(b));
}


vec16s APEX2::vmul_ulsl(const vec16s& a, const vec16s& b){
	return specializedMult(false, false, true, false, vec16u(a), vec16u(b));
}


vec16s APEX2::vmul_ulsl(const vec16u& a, const vec16u& b){
	return specializedMult(false, false, true, false, vec16u(a), vec16u(b));
}
vec16s APEX2::vmul_uhul (const vec16s& a, const vec16s& b)
{
  return specializedMult(false, true, false, false, vec16u(a), vec16u(b));
}

vec16s APEX2::vmul_uhsl(const vec16s& a, const vec16s& b) {
	return specializedMult(false, true, true, false, vec16u(a), vec16u(b));
}


vec16u APEX2::vmul_uhsl(const vec16u& a, const vec16u& b) {
	return specializedMult(false, true, true, false, vec16u(a), vec16u(b));
}

vec16s APEX2::vmul_uhuh (const vec16s& a, const vec16s& b)
{
  return specializedMult(false, true, false, true, vec16u(a), vec16u(b));
}

vec16s APEX2::vmul_uhsh (const vec16s& a, const vec16s& b)
{
  return specializedMult(false, true, true, true, vec16u(a), vec16u(b));
}

vec16s APEX2::vmul_shul (const vec16s& a, const vec16s& b)
{
  return specializedMult(true, true, false, false, vec16u(a), vec16u(b));
}

vec16s APEX2::vmul_shuh (const vec16s& a, const vec16s& b)
{
  return specializedMult(true, true, false, true, vec16u(a), vec16u(b));
}

vec16s APEX2::vmul_shsh (const vec16s& a, const vec16s& b)
{
  return specializedMult(true, true, true, true, vec16u(a), vec16u(b));
}

vec16u APEX2::vmul_ulul (const vec16u& a, const vec16u& b)
{
  return vec16u(specializedMult(false, false, false, false, vec16u(a), vec16u(b)));
}

vec16u APEX2::vmul_uluh (const vec16u& a, const vec16u& b)
{
  return vec16u(specializedMult(false, false, false, true, vec16u(a), vec16u(b)));
}

vec16s APEX2::vmul_ulsh (const vec16u& a, const vec16u& b)
{
  return specializedMult(false, false, true, true, vec16u(a), vec16u(b));
}

vec16u APEX2::vmul_uhul (const vec16u& a, const vec16u& b)
{
  return vec16u(specializedMult(false, true, false, false, vec16u(a), vec16u(b)));
}

vec16u APEX2::vmul_uhuh (const vec16u& a, const vec16u& b)
{
  return vec16u(specializedMult(false, true, false, true, vec16u(a), vec16u(b)));
}

vec16s APEX2::vmul_uhsh (const vec16u& a, const vec16u& b)
{
  return specializedMult(false, true, true, true, vec16u(a), vec16u(b));
}

vec16s APEX2::vmul_shul (const vec16u& a, const vec16u& b)
{
  return specializedMult(true, true, false, false, vec16u(a), vec16u(b));
}

vec16s APEX2::vmul_shuh (const vec16u& a, const vec16u& b)
 {
  return specializedMult(true, true, false, true, vec16u(a), vec16u(b));
}

vec16s APEX2::vmul_shsh (const vec16u& a, const vec16u& b)
{
  return specializedMult(true, true, true, true, vec16u(a), vec16u(b));
}

vec16u APEX2::extract_low(const vec32s a){
	vec32s mask = 0x0000FFFF;
	return vec16u(a & mask);
}

vec16u APEX2::extract_low(const vec32u a){
	vec32s mask = 0x0000FFFF;
	return vec16u(a & mask);
}

vec16s APEX2::extract_high(const vec32s a){
	return vec16s(a >>  16);
}

vec16u APEX2::extract_high(const vec32u a){
	return vec16u(a >> 16);
}



vec08u APEX2::extract_low(const vec16s a){
	vec16s mask = 0x00FF;
	return vec08u(a & mask);
}

vec08u APEX2::extract_low(const vec16u a){
	vec16s mask = 0x00FF;
	return vec08u(a & mask);
}

vec08s APEX2::extract_high(const vec16s a){
	return vec08s(a >> 8);
}

vec08u APEX2::extract_high(const vec16u a){
	return vec08u(a >> 16);
}




//Vector Accumulate Middle (signed extended or zero extended depending on input type)
/**
void vacm(vec16s va_high, vec16u va_low, vec16s vb))
va: source and destination high 16-bit;
vb: source input 16-bit

Computes [va] += (vec32s)sext(vb) << 8

*/
void APEX2::vacm(APU_vec<int32s>& va, const APU_vec<int16s>& vb)
{
	ADD_VECTOR_CYCLES_FUNCTION(T, vadd)
	ADD_VECTOR_CYCLES_FUNCTION(T, << )
	ADD_VECTOR_CYCLES_FUNCTION(T, << )
	ADD_VECTOR_CYCLES_FUNCTION(T, << )
	ADD_VECTOR_CYCLES_FUNCTION(T, << )
	ADD_VECTOR_CYCLES_FUNCTION(T, &)

	vec16s vsgn = (vb & vec16s(0x8000)) >> 15;
	vec32s vbWithSign = (( ((vec32s)vsgn) << 31) >> 31 ) & vec32s(vb);
	vbWithSign <<= 8;
	va = va + vbWithSign;
}

/**
void vacm(vec32u va, vec16u vb))
va: source input 32-bit;
vb: source input 16-bit

Computes [va] += (vec32s)sext(vb) << 8

*/
void APEX2::vacm(APU_vec<int32u>& va, const APU_vec<int16u>& vb)
{
	ADD_VECTOR_CYCLES_FUNCTION(T, vadd)
	ADD_VECTOR_CYCLES_FUNCTION(T, << )
	ADD_VECTOR_CYCLES_FUNCTION(T, &)

	vec32u vbWithSign = vec32u(vb);
	vbWithSign <<= 8;
	va = va + vbWithSign;
}


/**
void vacm(vec16s va_high, vec16u va_low, vec16s vb))
va_high: source and destination high 16-bit;
va_low: source and destination low 16-bit;
vb: source input 16-bit

Computes [va_high va_low] += (vec32s)sext(vb);

*/
void vacm(APU_vec<int16s>& va_hi, APU_vec<int16u>& va_lo, const APU_vec<int16s>& vb)
{
	ADD_VECTOR_CYCLES_FUNCTION(T, vsub)
	ADD_VECTOR_CYCLES_FUNCTION(T, = )
	vec32s tmp(va_hi, va_lo);
	vacm(APU_vec<int32s>(tmp), APU_vec<int16s>(vb));
	va_hi = tmp.high();
	va_lo = (vec16u)(tmp.low());
}


void vacm(APU_vec<int16u>& va_hi, APU_vec<int16u>& va_lo, const APU_vec<int16u>& vb)
{
	ADD_VECTOR_CYCLES_FUNCTION(T, vsub)
	ADD_VECTOR_CYCLES_FUNCTION(T, = )
	vec32u tmp(va_hi,va_lo);
	vacm(APU_vec<int32u>(tmp), APU_vec<int16u>(vb));
	va_hi = tmp.high();
	va_lo = (vec16u)(tmp.low());
}


/**
APU_vec<int32u> vacl(vec32s va, vec16s vb))
va: source and destination high 16-bit;
vb: source input 16-bit

Computes res = va + (vec32s)sext(vb);

*/
void APEX2::vacl(APU_vec<int32u>& va, const APU_vec<int16u>& vb)
{
	ADD_VECTOR_CYCLES_FUNCTION(T, vadd)
	ADD_VECTOR_CYCLES_FUNCTION(T, << )
	ADD_VECTOR_CYCLES_FUNCTION(T, &)

	vec32u vbWithSign = vec32u(vb);
	va = va + vbWithSign;
	
}


/**
APU_vec<int32s>  vacl(vec32s va, vec16s vb))
va: source and destination high 16-bit;
vb: source input 16-bit

Computes res = [va_high va_low] + (vec32s)sext(vb);

*/
void APEX2::vacl(APU_vec<int32s>& va, const APU_vec<int16s>& vb)
{
	ADD_VECTOR_CYCLES_FUNCTION(T, vadd)
	ADD_VECTOR_CYCLES_FUNCTION(T, << )
	ADD_VECTOR_CYCLES_FUNCTION(T, &)
	vec16s vsgn = ((vb & vec16s(0x8000)) >> 15);
	vec32s vbWithSign = (( ((vec32s)vsgn) << 31) >> 31) & vec32s(vb);
	va = va + vbWithSign;
}


/**
void vacl(vec16s va_high, vec16u va_low, vec16s vb))
va_high: source and destination high 16-bit;
va_low: source and destination low 16-bit;
vb: source input 16-bit

Computes [va_high va_low] += (vec32s)sext(vb);

*/
void APEX2::vacl(APU_vec<int16s>& va_hi, APU_vec<int16u>& va_lo, const APU_vec<int16s>& vb)
{
	ADD_VECTOR_CYCLES_FUNCTION(T, vsub)
		ADD_VECTOR_CYCLES_FUNCTION(T, = )
		vec32s tmp(va_hi, va_lo);
	vacl(APU_vec<int32s>(tmp), APU_vec<int16s>(vb));
	va_hi = tmp.high();
	va_lo = (vec16u)(tmp.low());
}


void APEX2::vacl(APU_vec<int16u>& va_hi, APU_vec<int16u>& va_lo, const APU_vec<int16u>& vb)
{
	ADD_VECTOR_CYCLES_FUNCTION(T, vsub)
		ADD_VECTOR_CYCLES_FUNCTION(T, = )
		vec32u tmp(va_hi, va_lo);
	vacl(APU_vec<int32u>(tmp), APU_vec<int16u>(vb));
	va_hi = tmp.high();
	va_lo = (vec16u)(tmp.low());
}

void APEX2::vsx(vec16s  a, vec16s &  b, vec16u &  c)
{
	b = a >> 15;
	c = a;
}


/**
 *Vector 32-bit accumulator.
 *
 *Vector Sign Extension (to 32-bit)

 *vector sign extension (to 32-bit) void vsx (vw16 a, vw16& b, vw16& c);
 *@parameter a [in]
 *@parameter b [out] msb
 *@parameter c [out] lsb [ b c ] = [ (a>>15) a ];

 *vector sign extension and shift right bit 8 (to 32-bit) void vssx(vw16 a, vw16& b, vw16& c) [ b c ] = [ (a>>8) (a<<8) ];

 *vector zero extension void vzx(vw16 a, vw16& b, vw16& c) [ b c ] = [ 0 a ];

 *vector zero extension and shift right bit 8 (to 32-bit) void vszx(vw16 a, vw16& b, vw16& c) [ b c ] = [ ((u)a>>8) (a<<8) ];
 *@parameter a [in]
 *@parameter b [out] msb
 *@parameter c [out] lsb
 *@return [ b c ] = [ (a>>15) a ]
*/
void APEX2::vsx(vec16u  a, vec16u &  b, vec16u &  c)
{
	b = a >> 15;
	c = a;
}

/**
 *Vector Zero Extension and Shift Right Bit 8 (to 32-bit)
 *
 *@parameter a [in]
 *@parameter b [out] msb
 *@parameter c [out] lsb
 *@parameter return [ b c ] = [ ((u)a>>8) (a<<8) ]
*/
void APEX2::vszx(vec16s  a, vec16s &  b, vec16u &  c)
{
	//b = ((u)a>>8); // ??? what is (u)
	b = ((vec16u)a >> 8); // ??? what is (u)
	c = (a<<8);
}


/**
 * Vector Zero Extension and Shift Right Bit 8 (to 32-bit)
 *
 *@parameter a [in]
 *@parameter b [out] msb
 *@parameter c [out] lsb
 *@parameter return [ b c ] = [ ((u)a>>8) (a<<8) ]
*/
void APEX2::vszx(vec16u  a, vec16u &  b, vec16u &  c)
{
	//b = ((u)a>>8); // ??? what is (u)
	b = ((vec16u)a >> 8); // ??? what is (u)
	c = (a<<8);
}

/**
 *Vector Zero Extension.
 *
 *@parameter a [in]
 *@parameter b [out] msb
 *@parameter c [out] lsb
 *@return [ b c ] = [ 0 a ]
*/
void APEX2::vzx(vec16s  a, vec16s &  b, vec16u &  c)
{
	b = 0;
	c = a;
}

/**
 *Vector Zero Extension.
 *
 *@parameter a [in]
 *@parameter b [out] msb
 *@parameter c [out] lsb
 *@return [ b c ] = [ 0 a ]
*/
void APEX2::vzx(vec16u  a, vec16u &  b, vec16u &  c)
{
	b = 0;
	c = a;
}


/**
 * Vector Sign Extension and Shift Right bit 8 (to 32-bit)
 *
 *@parameter a [in]
 *@parameter b [out] msb
 *@parameter c [out] lsb
 *@return [ b c ] = [ (a>>8) (a<<8) ]
*/
void APEX2::vssx(vec16u  a, vec16u &  b, vec16u &  c)
{
	b = a >> 8;
	c = a << 8;
}

/**
 * Vector Sign Extension and Shift Right bit 8 (to 32-bit)
 *
 *@parameter a [in]
 *@parameter b [out] msb
 *@parameter c [out] lsb
 *@return [ b c ] = [ (a>>8) (a<<8) ]
*/
void APEX2::vssx(vec16s  a, vec16s &  b, vec16u &  c)
{
	b = a >> 8;
	c = a << 8;
}


/**
 *If the source is greater than the upper bound or smaller than the lower bound, it is set ("clamped") to the upper/lower bound (16-bit)
 *
 *@parameter va Source vector
 *@parameter vb Lower bound
 *@parameter vc Upper bound
 *@return if (va >= upper bound) upper bound, else if (va <= upper bound) lower bound, else va
*/
vec16s APEX2::vsat(vec16s  va, vec16s  vb, vec16s  vc)
{
	vec16s retV = va;
	vif(va > vc) {
		retV = vc;
	} vendif
	vif(va < vb) {
		retV = vb;
	} vendif
	
	return retV;
}


/**
 *If the source is greater than the upper bound or smaller than the lower bound, it is set ("clamped") to the upper/lower bound (16-bit)
 *
 *@parameter va Source vector
 *@parameter vb Lower bound
 *@parameter vc Upper bound
 *@return if (va >= upper bound) upper bound, else if (va <= upper bound) lower bound, else va
*/
vec16u APEX2::vsat(vec16u  va, vec16u  vb, vec16u  vc)
{
	vec16u retV = va;
	vif (va >= vc)
		retV = vc;
	velse
		vif (va <= vb)
			retV = vb;
		vendif
	vendif

	return retV;
}

/*
void APEX2::_vmac(vec32s& o, vec08u a, short b)
{
   vec16u rl = extract_low(o);
   vec16s rh = extract_high(o);
   vec16u chess_storage(V7)   a0b0 = vmul_ulul(a, b); vacl(rh, rl, a0b0);
   vec16s chess_storage(V7)   a0b1 = vmul_ulsh(a, b); vacm(rh, rl, a0b1);
   o = vec32s(rh, rl);
}
*/
///////////Known


