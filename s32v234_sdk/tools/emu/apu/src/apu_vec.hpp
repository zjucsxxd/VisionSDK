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
* \file APU_vec.h
* \brief APU vector types
* \author Igor Aleksandrowicz
* \version
* \date 21-November-2013
****************************************************************************/

#ifndef _APU_VEC_H_
#define _APU_VEC_H_

#include "apu_config.hpp"
#include "apu_vbool.hpp"
#include "apu_cycles.hpp"
#include <cassert>

namespace APEX2
{

/****************************************************************************
* globals
****************************************************************************/

//global vector condition state
extern bool gEnabledCUs[VSIZE];
extern int _tileWidthInChunks;

/****************************************************************************
* generic vector type, vec__s and vec__u are typedefs of parametrized APU_vec
****************************************************************************/
template <class T, class highType, class lowType>
class High_LowTypes{
public:
	typedef T			OrigType;
	typedef highType	HWType;
	typedef lowType		LWType;
};

typedef High_LowTypes<int32s, int16s, int16u> int32sHLType;
typedef High_LowTypes<int32u, int16u, int16u> int32uHLType;

typedef High_LowTypes<int16s, int08s, int08u> int16sHLType;
typedef High_LowTypes<int16u, int08u, int08u> int16uHLType;

typedef High_LowTypes<int08s, int08s, int08u> int08sHLType;
typedef High_LowTypes<int08u, int08u, int08u> int08uHLType;

#define conc(a,b) \
a##b

#define expand(a) conc(a,HLType)


template<class T>
class tPairs {
public:
typedef T _hlType;
};

#define pairTempl(T) \
template<>\
class tPairs<T>{\
public:\
typedef expand(T) _hlType;\
};\


pairTempl(int32s);
pairTempl(int32u);
pairTempl(int16s);
pairTempl(int16u);
pairTempl(int08s);
pairTempl(int08u);



template <class T>
class APU_vec {
public:
  ///vector elements are public for easier interaction with the rest of the library and easier debugging
  ///however this member does NOT exist in APU-C and shouldn't be used for the final code
  T mElements[VSIZE];
  typedef typename tPairs<T>::_hlType::HWType _hT;
  typedef typename tPairs<T>::_hlType::LWType _lT;
  

  APU_vec();

  ///broadcast
  APU_vec(const T& arValue);

  ///conversions
  template <class OT>
  APU_vec(const APU_vec<OT>& arOther);
  APU_vec(const vbool& arOther);
  
  /* Do not implement this. It causes a heap corruption
  virtual ~APU_vec()
  {}
*/  

 
  /// Constructur with low and high word
  APU_vec(_hT highWord, _lT lowWord) {
	  int nrBits = ((sizeof(T) * 8) >> 1);
	  T tmp = (T(highWord) << nrBits) | T(lowWord);
	  ADD_VECTOR_CYCLES_FUNCTION(T, = )
	  for (int i = 0; i < _tileWidthInChunks; ++i)
	  {
		  if (gEnabledCUs[i])
		  {
			  mElements[i] = tmp;// [t];
		  }
	  }
	  //mElements = T(highWord << nrBits) + T(lowWord);
  };

  /// Constructur with low and high word
  APU_vec(APU_vec<_hT> highWord, APU_vec<_lT> lowWord) {
	  int nrBits = ((sizeof(T) * 8)>>1);

	  APU_vec<T> tmp = (APU_vec<T>(highWord) << nrBits) | APU_vec<T>(lowWord);
	  ADD_VECTOR_CYCLES_FUNCTION(T, = )
	  for (int i = 0; i < _tileWidthInChunks; ++i)
	  {
		  if (gEnabledCUs[i])
		  {
			  mElements[i] = tmp.mElements[i];// [t];
		  }
	  }
	  //mElements = T(highWord << nrBits) + T(lowWord);
  };
  
  APU_vec<T>& operator=(const APU_vec<T>& arRhs);


  APU_vec<_lT> low() {
	  return (APU_vec<_lT>) extract_low(*this);
  }

  APU_vec<_hT> high() {

	  return (APU_vec<_hT>)extract_high(*this);
  }

/****************************************************************************
* binary operators
****************************************************************************/

///macros for operator declarations and definitions, will be used on real operators later
#define BIN_OP_DEC(OPERATOR) APU_vec<T> operator OPERATOR (const APU_vec<T>& arOther) const;
#define BIN_OP_DEF(OPERATOR) template <class T>\
    APU_vec<T> APU_vec<T>::operator OPERATOR (const APU_vec<T>& arOther) const\
    {\
      ADD_VECTOR_CYCLES_BINARY_OPERATOR(T, OPERATOR)\
      APU_vec<T> r;\
      for (int i = 0; i < _tileWidthInChunks; ++i)\
      {\
        if (gEnabledCUs[i])\
        {\
          r.mElements[i] = mElements[i] OPERATOR arOther.mElements[i];\
        }\
      }\
      return r;\
    }

/****************************************************************************
* unary operators
****************************************************************************/

///macros for operator declarations and definitions, will be used on real operators later
#define UN_OP_DEC(OPERATOR) APU_vec<T> operator OPERATOR () const;
#define UN_OP_DEF(OPERATOR) template <class T>\
    APU_vec<T> APU_vec<T>::operator OPERATOR () const\
    {\
      ADD_VECTOR_CYCLES_UNARY_OPERATOR(T, OPERATOR)\
      APU_vec<T> r;\
      for (int i = 0; i < _tileWidthInChunks; ++i)\
      {\
        if (gEnabledCUs[i])\
        {\
          r.mElements[i] = OPERATOR mElements[i];\
        }\
      }\
      return r;\
    }

/****************************************************************************
* shift operators
****************************************************************************/

///macros for operator declarations and definitions, will be used on real operators later
#define SHIFT_OP_DEC(OPERATOR) APU_vec<T> operator OPERATOR (const APU_vec<T>& arBits) const;
#define SHIFT_OP_DEF(OPERATOR) template <class T>\
    APU_vec<T> APU_vec<T>::operator OPERATOR (const APU_vec<T>& arBits) const\
    {\
      ADD_VECTOR_CYCLES_BINARY_OPERATOR(T, OPERATOR)\
      APU_vec<T> r;\
      for (int i = 0; i < _tileWidthInChunks; ++i)\
      {\
        if (gEnabledCUs[i])\
        {\
          r.mElements[i] = mElements[i] OPERATOR arBits.mElements[i];\
        }\
      }\
      return r;\
    }

/****************************************************************************
* relation operators
****************************************************************************/

///macros for operator declarations and definitions, will be used on real operators later
#define REL_OP_DEC(OPERATOR) vbool operator OPERATOR (const APU_vec<T>& arOther) const;
#define REL_OP_DEF(OPERATOR) template <class T>\
    vbool APU_vec<T>::operator OPERATOR (const APU_vec<T>& arOther) const\
    {\
      ADD_VECTOR_CYCLES_BINARY_OPERATOR(T, OPERATOR)\
      vbool r;\
      for (int i = 0; i < _tileWidthInChunks; ++i)\
      {\
        if (gEnabledCUs[i])\
        {\
          r.mElements[i] = mElements[i] OPERATOR arOther.mElements[i];\
        }\
      }\
      return r;\
    }

/****************************************************************************
* compound assign operators
****************************************************************************/

///macros for operator declarations and definitions, will be used on real operators later
#define CASS_OP_DEC(OPERATOR) APU_vec<T>& operator OPERATOR (const APU_vec<T>& arOther);
#define CASS_OP_DEF(OPERATOR) template <class T>\
    APU_vec<T>& APU_vec<T>::operator OPERATOR (const APU_vec<T>& arOther)\
    {\
      ADD_VECTOR_CYCLES_BINARY_OPERATOR(T, OPERATOR)\
      for (int i = 0; i < _tileWidthInChunks; ++i)\
      {\
        if (gEnabledCUs[i])\
        {\
          mElements[i] OPERATOR arOther.mElements[i];\
        }\
      }\
      return *this;\
    }

/****************************************************************************
* compound shift assign operators
****************************************************************************/

///macros for operator declarations and definitions, will be used on real operators later
#define CASSSH_OP_DEC(OPERATOR) APU_vec<T>& operator OPERATOR (const APU_vec<T>& arBits);
#define CASSSH_OP_DEF(OPERATOR) template <class T>\
    APU_vec<T>& APU_vec<T>::operator OPERATOR (const APU_vec<T>& arBits)\
    {\
      ADD_VECTOR_CYCLES_BINARY_OPERATOR(T, OPERATOR)\
      for (int i = 0; i < _tileWidthInChunks; ++i)\
      {\
        if (gEnabledCUs[i])\
        {\
          mElements[i] OPERATOR arBits.mElements[i];\
        }\
      }\
      return *this;\
    }

/****************************************************************************
* prefix operators
****************************************************************************/

///macros for operator declarations and definitions, will be used on real operators later
#define PREF_OP_DEC(OPERATOR) APU_vec<T>& operator OPERATOR ();
#define PREF_OP_DEF(OPERATOR) template <class T>\
    APU_vec<T>& APU_vec<T>::operator OPERATOR ()\
    {\
      ADD_VECTOR_CYCLES_UNARY_OPERATOR(T, OPERATOR)\
      for (int i = 0; i < _tileWidthInChunks; ++i)\
      {\
        if (gEnabledCUs[i])\
        {\
          OPERATOR mElements[i];\
        }\
      }\
      return *this;\
    }

/****************************************************************************
* postfix operators
****************************************************************************/

///macros for operator declarations and definitions, will be used on real operators later
#define POST_OP_DEC(OPERATOR) APU_vec<T> operator OPERATOR (int NA);
#define POST_OP_DEF(OPERATOR) template <class T>\
    APU_vec<T> APU_vec<T>::operator OPERATOR (int NA)\
    {\
      ADD_VECTOR_CYCLES_UNARY_OPERATOR(T, OPERATOR)\
      APU_vec<T> r = *this;\
      for (int i = 0; i < _tileWidthInChunks; ++i)\
      {\
        if (gEnabledCUs[i])\
        {\
          mElements[i] OPERATOR;\
        }\
      }\
      return r;\
    }

///operator declarations using the declaration macros
 
  BIN_OP_DEC(+)
  BIN_OP_DEC(-)
  BIN_OP_DEC(*)
  BIN_OP_DEC(/)
  BIN_OP_DEC(%)
  UN_OP_DEC(-)
  UN_OP_DEC(+)

  BIN_OP_DEC(^)
  BIN_OP_DEC(|)
  BIN_OP_DEC(&)
  UN_OP_DEC(~)
  SHIFT_OP_DEC(>>)
  SHIFT_OP_DEC(<<)

  REL_OP_DEC(==)
  REL_OP_DEC(!=)
  REL_OP_DEC(>)
  REL_OP_DEC(<)
  REL_OP_DEC(>=)
  REL_OP_DEC(<=)

  CASS_OP_DEC(+=)
  CASS_OP_DEC(-=)
  CASS_OP_DEC(*=)
  CASS_OP_DEC(/=)
  CASS_OP_DEC(%=)
  CASS_OP_DEC(&=)
  CASS_OP_DEC(|=)
  CASS_OP_DEC(^=)

  CASSSH_OP_DEC(<<=)
  CASSSH_OP_DEC(>>=)

  PREF_OP_DEC(++)
  POST_OP_DEC(++)
  PREF_OP_DEC(--)
  POST_OP_DEC(--)

private:

  ///helper get and put functions
  T get(int aIndex) const
  {
    assert(aIndex >= 0 && aIndex < _tileWidthInChunks);
    return mElements[aIndex];
  }

  void put(int aIndex, const T arValue)
  {
    assert(aIndex >= 0 && aIndex < _tileWidthInChunks);
    mElements[aIndex] = arValue;
  }

  ///helper vector move shift and rotate function declarations, these functions don't modify *this
  APU_vec<T> moveShiftLeft(const APU_vec<T>& arFillVector) const;
  APU_vec<T> moveShiftRight(const APU_vec<T>& arFillVector) const;
  APU_vec<T> moveRotateLeft(const APU_vec<T>& arFillVector) const;
  APU_vec<T> moveRotateRight(const APU_vec<T>& arFillVector) const;

  ///APU-C vget, vput operators declarations
  template <class U> friend U vget(const APU_vec<U>& arVector, int aIndex);
  template <class U> friend APU_vec<U> vput(const APU_vec<U>& arVector, const U arValue, int aIndex);

  ///APU-C vector move shift and rotate functions declarations
  template <class U> friend
  APU_vec<U> vmsl(const APU_vec<U>& arVectorShift, const APU_vec<U>& arVectorFill);
  template <class U> friend
  APU_vec<U> vmr(const APU_vec<U>& arVectorShift, const APU_vec<U>& arVectorFill);
  template <class U> friend
  APU_vec<U> vmsr(const APU_vec<U>& arVectorShift, const APU_vec<U>& arVectorFill);
  template <class U> friend
  APU_vec<U> vml(const APU_vec<U>& arVectorShift, const APU_vec<U>& arVectorFill);
  template <class U> friend
  APU_vec<U> vmrl(const APU_vec<U>& arVectorRotate, const APU_vec<U>& arVectorFill);
  template <class U> friend
  APU_vec<U> vmrr(const APU_vec<U>& arVectorRotate, const APU_vec<U>& arVectorFill);
  template <class U> friend
  APU_vec<U> vmsl(const APU_vec<U>& arVectorShift);
  template <class U> friend
  APU_vec<U> vmsr(const APU_vec<U>& arVectorShift);
  template <class U> friend
  APU_vec<U> vmrl(const APU_vec<U>& arVectorRotate);
  template <class U> friend
  APU_vec<U> vmrr(const APU_vec<U>& arVectorRotate);
};

template <class T>
APU_vec<T>::APU_vec()
{
  for (int i = 0; i < VSIZE; ++i)
  {
    mElements[i] = 0;
  }
}

//broadcast
template <class T>
APU_vec<T>::APU_vec(const T& arValue)
{
  ADD_VECTOR_CYCLES_FUNCTION(T, broadcast)
  for (int i = 0; i < _tileWidthInChunks; ++i)
  {
    if (gEnabledCUs[i])
    {
      mElements[i] = arValue;
    }
  }
}

template <class T>
template <class OT>
APU_vec<T>::APU_vec(const APU_vec<OT>& arOther)
{
  ADD_VECTOR_CYCLES_BINARY_OPERATOR(T, =)
  for (int i = 0; i < _tileWidthInChunks; ++i)
  {
    if (gEnabledCUs[i])
    {
      mElements[i] = T(arOther.mElements[i]);
    }
  }
}

template <class T>
APU_vec<T>::APU_vec(const vbool& arOther)
{
  ADD_VECTOR_CYCLES_BINARY_OPERATOR(T, =)
  for (int i = 0; i < _tileWidthInChunks; ++i)
  {
    if (gEnabledCUs[i])
    {
      mElements[i] = arOther.mElements[i] ? 1 : 0;
    }
  }
}




template <class T>
APU_vec<T>& APU_vec<T>::operator=(const APU_vec<T>& arRhs)
{
  ADD_VECTOR_CYCLES_BINARY_OPERATOR(T, =)
  for (int i = 0; i < _tileWidthInChunks; ++i)
  {
    if (gEnabledCUs[i])
    {
      mElements[i] = T(arRhs.mElements[i]);
    }
  }
  return *this;
}

//operator definitions using previously defined macros

BIN_OP_DEF(+)
BIN_OP_DEF(-)
BIN_OP_DEF(*)
BIN_OP_DEF(/)
BIN_OP_DEF(%)
UN_OP_DEF(-)
UN_OP_DEF(+)

BIN_OP_DEF(^)
BIN_OP_DEF(|)
BIN_OP_DEF(&)
UN_OP_DEF(~)
SHIFT_OP_DEF(>>)
SHIFT_OP_DEF(<<)

REL_OP_DEF(==)
REL_OP_DEF(!=)
REL_OP_DEF(>)
REL_OP_DEF(<)
REL_OP_DEF(>=)
REL_OP_DEF(<=)

CASS_OP_DEF(+=)
CASS_OP_DEF(-=)
CASS_OP_DEF(*=)
CASS_OP_DEF(/=)
CASS_OP_DEF(%=)
CASS_OP_DEF(&=)
CASS_OP_DEF(|=)
CASS_OP_DEF(^=)

CASSSH_OP_DEF(<<=)
CASSSH_OP_DEF(>>=)

PREF_OP_DEF(++)
POST_OP_DEF(++)
PREF_OP_DEF(--)
POST_OP_DEF(--)

//macros for scalar/vector operations

//for scalar * vector ops, type ambiguity solved by using int
//don't update the cycle count here!
#define BIN_INT_OP_DEC(OPERATOR) template <class T>\
    APU_vec<T> operator OPERATOR(int value, const APU_vec<T>& arVec)\
    {\
      return APU_vec<T>(value) OPERATOR arVec;\
    }\
    \
    template <class T>\
    APU_vec<T> operator OPERATOR(unsigned int value, const APU_vec<T>& arVec)\
    {\
      return APU_vec<T>(value) OPERATOR arVec;\
    }\

//for number < vector ops, type ambiguity solved by using int
//don't update the cycle count here!
#define REL_INT_OP_DEC(OPERATOR) template <class T>\
    vbool operator OPERATOR(int value, const APU_vec<T>& arVec)\
    {\
      return APU_vec<T>(value) OPERATOR arVec;\
    }\
    \
    template <class T>\
    vbool operator OPERATOR(unsigned int value, const APU_vec<T>& arVec)\
    {\
      return APU_vec<T>(value) OPERATOR arVec;\
    }\

BIN_INT_OP_DEC(+)
BIN_INT_OP_DEC(-)
BIN_INT_OP_DEC(*)
BIN_INT_OP_DEC(/)
BIN_INT_OP_DEC(%)

BIN_INT_OP_DEC(^)
BIN_INT_OP_DEC(|)
BIN_INT_OP_DEC(&)

REL_INT_OP_DEC(==)
REL_INT_OP_DEC(!=)
REL_INT_OP_DEC(>)
REL_INT_OP_DEC(<)
REL_INT_OP_DEC(>=)
REL_INT_OP_DEC(<=)

//undefine the macros

#undef BIN_OP_DEC
#undef BIN_OP_DEF
#undef SHIFT_OP_DEC
#undef SHIFT_OP_DEF
#undef UN_OP_DEC
#undef UN_OP_DEF
#undef REL_OP_DEC
#undef REL_OP_DEF
#undef CASS_OP_DEC
#undef CASS_OP_DEF
#undef CASSSH_OP_DEC
#undef CASSSH_OP_DEF
#undef PREF_OP_DEC
#undef PREF_OP_DEF
#undef POST_OP_DEC
#undef POST_OP_DEF
#undef BIN_INT_OP_DEC
#undef REL_INT_OP_DEC

///don't update the cycles in the following functions (but in vmsl, vmsr... instead)

//APU-C vector move shifts and rotates implementation
template <class T>
APU_vec<T> APU_vec<T>::moveShiftLeft(const APU_vec<T>& arFillVector) const
{
  APU_vec<T> r = *this;
  for (int i = 0; i < _tileWidthInChunks - 1; ++i)
  {
	if (gEnabledCUs[i] && gEnabledCUs[i+1] )
    {
      r.mElements[i] = mElements[i+1];
    }
  }
  if (gEnabledCUs[_tileWidthInChunks-1])
  {
    r.mElements[_tileWidthInChunks - 1] = arFillVector.mElements[_tileWidthInChunks - 1];
  }
  return r;
}

template <class T>
APU_vec<T> APU_vec<T>::moveShiftRight(const APU_vec<T>& arFillVector) const
{
  APU_vec<T> r = *this;
  for (int i = 1; i < _tileWidthInChunks; ++i)
  {
	if (gEnabledCUs[i] && gEnabledCUs[i - 1])
    {
      r.mElements[i] = mElements[i-1];
    }
  }
  if (gEnabledCUs[0])
  {
    r.mElements[0] = arFillVector.mElements[0];
  }
  return r;
}

template <class T>
APU_vec<T> APU_vec<T>::moveRotateLeft(const APU_vec<T>& arFillVector) const
{
  APU_vec<T> r = *this;
  for (int i = 0; i < _tileWidthInChunks - 1; ++i)
  {
	if (gEnabledCUs[i] && gEnabledCUs[i + 1])
    {
      r.mElements[i] = mElements[i+1];
    }
  }
  if (gEnabledCUs[_tileWidthInChunks - 1] && gEnabledCUs[0])
  {
	  r.mElements[_tileWidthInChunks - 1] = arFillVector.mElements[0];
  }
  return r;
}

template <class T>
APU_vec<T> APU_vec<T>::moveRotateRight(const APU_vec<T>& arFillVector) const
{
  APU_vec<T> r = *this;
  for (int i = 1; i < _tileWidthInChunks; ++i)
  {
	if (gEnabledCUs[i] && gEnabledCUs[i - 1] )
    {
      r.mElements[i] = mElements[i-1];
    }
  }
  if (gEnabledCUs[0] && gEnabledCUs[_tileWidthInChunks - 1])
  {
    r.mElements[0] = arFillVector.mElements[_tileWidthInChunks-1];
  }
  return r;
}


typedef APU_vec<int08u> vec08u;
typedef APU_vec<int08s> vec08s;
typedef APU_vec<int16u> vec16u;
typedef APU_vec<int16s> vec16s;



////////////////
/// Specialized vector class which provides additionally the low-high word constructor 
/// should be used only for 32bit signed/unsigned instantiation
////////////////
/*
template <class T>
class APU_vec_spec : public APU_vec<T> {
public:



	APU_vec_spec()
		: APU_vec<T>()
	{};

	//broadcast
	APU_vec_spec(const T& arValue)
		: APU_vec<T>(arValue)
	{}


	//conversions
	template <class OT>
	APU_vec_spec(const APU_vec<OT>& arOther)
		: APU_vec<T>(arOther)
	{}

	APU_vec_spec(const vbool& arOther)
		: APU_vec<T>(arOther)
	{};
	/// Constructur with low and high word
	APU_vec_spec(vec16s highWord, vec16u lowWord)
		: APU_vec<T>()
	{
			T tmp = (T(highWord) << 16) + T(lowWord);
			ADD_VECTOR_CYCLES_FUNCTION(T, = )
			for (int i = 0; i < _tileWidthInChunks; ++i)
			{
				if (gEnabledCUs[i])
				{
					mElements[i] = tmp[t];
				}
			}
			mElements = (T(highWord) << 16) + T(lowWord);
		}

	/// Constructur with low and high word
	APU_vec_spec(vec16u highWord, vec16u lowWord)
		: APU_vec<T>()
	{
			T tmp = (T(highWord) << 16) + T(lowWord);
			ADD_VECTOR_CYCLES_FUNCTION(T, = )
			for (int i = 0; i < _tileWidthInChunks; ++i)
			{
				if (gEnabledCUs[i])
				{
					mElements[i] = tmp[t];
				}
			}
			mElements =( T(highWord) << 16) + T(lowWord);
		}

	virtual ~APU_vec_spec()
	{}
};

*/

/****************************************************************************
* APU-C vector types continued
****************************************************************************/
typedef APU_vec/*_spec*/<int32u> vec32u;
typedef APU_vec/*_spec*/<int32s> vec32s;
/****************************************************************************
* non-member functions
****************************************************************************/
////////////////
//APU-C element instructions
////////////////
template <class T>
T vget(const APU_vec<T>& arVector, int aIndex)
{
  ADD_VECTOR_CYCLES_FUNCTION(T, vget)
  return arVector.get(aIndex);
}

//
template <class T>
APU_vec<T> vput(const APU_vec<T>& arVector, const T arValue, int aIndex)
{
  ADD_VECTOR_CYCLES_FUNCTION(T, vput)
  APU_vec<T> r = arVector;
  if (gEnabledCUs[aIndex])
  {
    r.put(aIndex, arValue);
  }
  return r;
}

//vector version of vput. It copies the values for which index(i) = i and leaves the other elements intact
//do not confuse with vstore!
template <class T>
APU_vec<T> vput(const APU_vec<T>& arVector, const APU_vec<T>& arValue, const APU_vec<T>& aIndex)
{
  ADD_VECTOR_CYCLES_FUNCTION(T, vput)
  APU_vec<T> r = arVector;
  for (int i = 0; i < _tileWidthInChunks; ++i)
  {
    if (gEnabledCUs[i])
    {
      T index = aIndex.mElements[i];
      if (int(index) == i)
      {
        r.mElements[i] = arValue.mElements[i];
      }
      else
      {
        r.mElements[i] = arVector.mElements[i];
      }
    }
  }
  return r;
}

////////////////
//vector move shifts and rotates implementation
////////////////
template <class T>
APU_vec<T> vmsl(const APU_vec<T>& arVectorShift, const APU_vec<T>& arVectorFill)
{
  ADD_VECTOR_CYCLES_FUNCTION(T, vmsl)
  return arVectorShift.moveShiftLeft(arVectorFill);
}

template <class T>
APU_vec<T> vmr(const APU_vec<T>& arVectorShift, const APU_vec<T>& arVectorFill)
{
  ADD_VECTOR_CYCLES_FUNCTION(T, vmr)
  return arVectorShift.moveShiftLeft(arVectorFill);
}

template <class T>
APU_vec<T> vmsr(const APU_vec<T>& arVectorShift, const APU_vec<T>& arVectorFill)
{
  ADD_VECTOR_CYCLES_FUNCTION(T, vmsr)
  return arVectorShift.moveShiftRight(arVectorFill);
}

template <class T>
APU_vec<T> vml(const APU_vec<T>& arVectorShift, const APU_vec<T>& arVectorFill)
{
  ADD_VECTOR_CYCLES_FUNCTION(T, vml)
  return arVectorShift.moveShiftRight(arVectorFill);
}

template <class T>
APU_vec<T> vmrl(const APU_vec<T>& arVectorRotate, const APU_vec<T>& arVectorFill)
{
  ADD_VECTOR_CYCLES_FUNCTION(T, vmrl)
  return arVectorRotate.moveRotateLeft(arVectorFill);
}

template <class T>
APU_vec<T> vmrr(const APU_vec<T>& arVectorRotate, const APU_vec<T>& arVectorFill)
{
  ADD_VECTOR_CYCLES_FUNCTION(T, vmrr)
  return arVectorRotate.moveRotateRight(arVectorFill);
}

template <class T>
APU_vec<T> vmsl(const APU_vec<T>& arVectorShift)
{
  ADD_VECTOR_CYCLES_FUNCTION(T, vmsl)
  return arVectorShift.moveShiftLeft(0);
}

template <class T>
APU_vec<T> vmsr(const APU_vec<T>& arVectorShift)
{
  ADD_VECTOR_CYCLES_FUNCTION(T, vmsr)
  return arVectorShift.moveShiftRight(0);
}

template <class T>
APU_vec<T> vmrl(const APU_vec<T>& arVectorRotate)
{
  ADD_VECTOR_CYCLES_FUNCTION(T, vmrl)
  return arVectorRotate.moveRotateLeft(arVectorRotate);
}

template <class T>
APU_vec<T> vmrr(const APU_vec<T>& arVectorRotate)
{
  ADD_VECTOR_CYCLES_FUNCTION(T, vmrr)
  return arVectorRotate.moveRotateRight(arVectorRotate);
}

////////////////
//indirect memory access functions implementation
////////////////
template <class T>
APU_vec<T> vload(const APU_vec<T>* apBase, const vec16s& arIndex)
{
  ADD_VECTOR_CYCLES_FUNCTION(T, vload)
  APU_vec<T> ret;
  for (int i = 0; i < _tileWidthInChunks; ++i)
  {
    if (gEnabledCUs[i])
    {
      int index = arIndex.mElements[i];
      ret.mElements[i] = apBase[index].mElements[i];
    }
  }
  return ret;
}

template <class T>
void vstore(APU_vec<T>* apBase, const vec16s& arIndex, const APU_vec<T>& arValue)
{
  ADD_VECTOR_CYCLES_FUNCTION(T, vstore)
  for (int i = 0; i < _tileWidthInChunks; ++i)
  {
    if (gEnabledCUs[i])
    {
      int index = arIndex.mElements[i];
      apBase[index].mElements[i] = T(arValue.mElements[i]);
    }
  }
}

////////////////
//specialized arithmetic APU-C functions implementation
////////////////
template <class T>
APU_vec<T> vadd (const APU_vec<T>& va, const APU_vec<T>& vb)
{
  ADD_VECTOR_CYCLES_FUNCTION(T, vadd)
  return va + vb;
}

//slow, but handles different signed and unsigned types
template <class T>
APU_vec<T> vaddx (const APU_vec<T>& va, const APU_vec<T>& vb, const vbool& vc, vbool& vf)
{
  ADD_VECTOR_CYCLES_FUNCTION(T, vaddx)
  int bits = sizeof(T) * 8;
  APU_vec<T> res = 0;

  vbool carry = vc;
  for (int i = 0; i < bits; ++i)
  {
    vbool aBit = (va & (1 << i)) != 0;
    vbool bBit = (vb & (1 << i)) != 0;
    vec32u bitCount = vec32u(aBit) + vec32u(bBit) + vec32u(carry);
    vbool resBit = (bitCount & 1) != 0;
    carry = bitCount > 1;

    res |= (APU_vec<T>(resBit) << i);
  }

  vf = carry;
  return res;
}

template <class T>
APU_vec<T> vaddx (const APU_vec<T>& va, const APU_vec<T>& vb, const vbool& vc)
{
  ADD_VECTOR_CYCLES_FUNCTION(T, vaddx)
  vbool temp;
  return vaddx(va, vb, vc, temp);
}

template <class T>
APU_vec<T> vadd (const APU_vec<T>& va, const APU_vec<T>& vb, vbool& vf)
{
  ADD_VECTOR_CYCLES_FUNCTION(T, vadd)
  return vaddx(va, vb, false, vf);
}

template <class T>
APU_vec<T> vsub (const APU_vec<T>& va, const APU_vec<T>& vb)
{
  ADD_VECTOR_CYCLES_FUNCTION(T, vsub)
  return va - vb;
}



template <class T>
APU_vec<T> vabs_diffu(const APU_vec<T>&  va, const APU_vec<T>&  vb)  {
	ADD_VECTOR_CYCLES_FUNCTION(T, -)
	ADD_VECTOR_CYCLES_FUNCTION(T, vabs)

	return (APU_vec<T>) vabs((vec32s)va - (vec32s)vb);
}

template <class T>
APU_vec<T> vabs_diff(const APU_vec<T>&  va, const APU_vec<T>&  vb)  {
	ADD_VECTOR_CYCLES_FUNCTION(T, -)
	ADD_VECTOR_CYCLES_FUNCTION(T, vabs)

		return (APU_vec<T>) vabs((vec32s)va - (vec32s)vb);
}
template <class T>
APU_vec<T> vadd_sat(const APU_vec<T>&  va, const APU_vec<T>&  vb)  {
	ADD_VECTOR_CYCLES_FUNCTION(T, +)
	ADD_VECTOR_CYCLES_FUNCTION(T, < )

	int32s maxVal = (1<<(sizeof(T) * 8 -1)) - 1;

	vec32s tmp = vec32s(va) + vec32s(vb);
	for (int i = 0; i < _tileWidthInChunks; ++i)
	{
		if (gEnabledCUs[i])
		{
			if (tmp.mElements[i] > maxVal) {
				tmp.mElements[i] = maxVal;
			}

			if (tmp.mElements[i] < -(maxVal+1)) {
				tmp.mElements[i] = -(maxVal+1);
			}
		}
	}

	return tmp;
}


template <class T>
APU_vec<T> vsub_sat(const APU_vec<T>&  va, const APU_vec<T>&  vb)  {
	ADD_VECTOR_CYCLES_FUNCTION(T, +)
	ADD_VECTOR_CYCLES_FUNCTION(T, <)

	int32s maxVal = (1 << (sizeof(T) * 8 - 1)) - 1;

	vec32s tmp = vec32s(va) - vec32s(vb);
	for (int i = 0; i < _tileWidthInChunks; ++i)
	{
		if (gEnabledCUs[i])
		{
			if (tmp.mElements[i] > maxVal) {
				tmp.mElements[i] = maxVal;
			}

			if (tmp.mElements[i] < -(maxVal+1)) {
				tmp.mElements[i] = -(maxVal+1);
			}
		}
	}

	return tmp;
}


///Vector Add / Subtract(based on condition)
/// r = (c) ? (a+b) : (a-b); 
template <class T>
APU_vec<T> vasb(const APU_vec<T>& va, const APU_vec<T>& vb, vbool& cond)
{
	ADD_VECTOR_CYCLES_FUNCTION(T, vadd)
	ADD_VECTOR_CYCLES_FUNCTION(T, vselect)

	APU_vec<T> r;

	r = va + vselect(vb, -vb, cond);
	return r;
}

///Vector add with absolute value of b
/// @return r += va + abs(vb); 
template <class T>
APU_vec<T> vasbs(const APU_vec<T>& va, const APU_vec<T>& vb, vbool& cond)
{
	ADD_VECTOR_CYCLES_FUNCTION(T, vadd)
		ADD_VECTOR_CYCLES_FUNCTION(T, vselect)

		APU_vec<T> r;

	r = va + vabs(vb);
	return r;
}

//slow bit-wise implementation which handles various signed and unsigned types
template <class T>
APU_vec<T> vsubx (const APU_vec<T>& va, const APU_vec<T>& vb, const vbool& vc, vbool& vf)
{
  ADD_VECTOR_CYCLES_FUNCTION(T, vsubx)
  int bits = sizeof(T) * 8;
  APU_vec<T> res = 0;

  vbool borrow = vc;
  for (int i = 0; i < bits; ++i)
  {
    vbool aBit = (va & (1 << i)) != 0;
    vbool bBit = (vb & (1 << i)) != 0;

    vec08u bitCount = vec08u(aBit) + vec08u(bBit) + vec08u(borrow);
    vbool resBit = bitCount == 1 || bitCount == 3;
    borrow = (!aBit && bitCount != 0) || (bitCount == 3);

    res |= (APU_vec<T>(resBit) << i);
  }

  vf = borrow;
  return res;
}

template <class T>
APU_vec<T> vsubx (const APU_vec<T>& va, const APU_vec<T>& vb, const vbool& vc)
{
  ADD_VECTOR_CYCLES_FUNCTION(T, vsubx)
  vbool temp;
  return vsubx(va, vb, vc, temp);
}

template <class T>
APU_vec<T> vsub (const APU_vec<T>& va, const APU_vec<T>& vb, vbool& vf)
{
  ADD_VECTOR_CYCLES_FUNCTION(T, vsub)
  return vsubx(va, vb, false, vf);
}

template <class T>
APU_vec<T> vmul (const APU_vec<T>& va, const APU_vec<T>& vb)
{
  ADD_VECTOR_CYCLES_FUNCTION(T, vmul)
  return va * vb;
}

////////////////
//specialized logical APU-C functions implementation
////////////////
template <class T>
APU_vec<T> vand (const APU_vec<T>& va, const APU_vec<T>& vb)
{
  ADD_VECTOR_CYCLES_FUNCTION(T, vand)
  return va & vb;
}

template <class T>
APU_vec<T> vor (const APU_vec<T>& va, const APU_vec<T>& vb)
{
  ADD_VECTOR_CYCLES_FUNCTION(T, vor)
  return va | vb;
}

template <class T>
APU_vec<T> vxor (const APU_vec<T>& va, const APU_vec<T>& vb)
{
  ADD_VECTOR_CYCLES_FUNCTION(T, vxor)
  return va ^ vb;
}

template <class T>
APU_vec<T> vnot (const APU_vec<T>& va)
{
  ADD_VECTOR_CYCLES_FUNCTION(T, vnot)
  return ~va;
}

template <class T>
APU_vec<T> vcomplement (const APU_vec<T>& va)
{
  ADD_VECTOR_CYCLES_FUNCTION(T, vcomplement)
  return ~va;
}

////////////////
//specialized bit shift APU-C functions implementation
////////////////
//naming convention: vsAB where:
//A (l/r) left/right shift
//B (l/a or missing) determines whether the shift is a logical shift (l) or an arithmetic shift (a or missing)
template <class T>
APU_vec<T> vsl (const APU_vec<T>& va, const APU_vec<T>& vb)
{
  ADD_VECTOR_CYCLES_FUNCTION(T, vsl)
  return va << vb;
}

template <class T>
APU_vec<T> vsr (const APU_vec<T>& va, const APU_vec<T>& vb)
{
  ADD_VECTOR_CYCLES_FUNCTION(T, vsr)
  return va >> vb;
}


// TODO vsla missing
/*
//signed l-logical shift, a-arithmetic shift
template <class T>
APU_vec<T> vsla (const APU_vec<T>& va, const APU_vec<T>& vb)
{
	ADD_VECTOR_CYCLES_FUNCTION(T, vsla)
	return va << vb;
}
*/


//l-logical shift, a-arithmetic shift
template <class T>
APU_vec<T> vsll (const APU_vec<T>& va, const APU_vec<T>& vb)
{
  ADD_VECTOR_CYCLES_FUNCTION(T, vsll)
  return va << vb;
}

template <class T>
APU_vec<T> vsra (const APU_vec<T>& va, const APU_vec<T>& vb)
{
  ADD_VECTOR_CYCLES_FUNCTION(T, vsra)
  return va >> vb;
}


template <class T>
APU_vec<T> vsrl (const APU_vec<T>& va, const APU_vec<T>& vb)
{
  ADD_VECTOR_CYCLES_FUNCTION(T, vsrl)
  //logical right shift
  T signPattern = 1 << (sizeof(T) * 8 - 1);
  T shiftedSignPattern = 1 << (sizeof(T) * 8 - 2);
  APU_vec<T> temp = va & (~signPattern);
  temp >>= vb;
  for (int i = 0; i < _tileWidthInChunks; ++i)
  {
    if ((va.mElements[i] & signPattern) && gEnabledCUs[i])
    {
      temp.mElements[i] |= shiftedSignPattern;
    }
  }
  return temp;
}

////////////////
//specialized comparison APU-C functions implementation
////////////////
template <class T>
vbool vseq (const APU_vec<T>& va, const APU_vec<T>& vb)
{
  ADD_VECTOR_CYCLES_FUNCTION(T, vseq)
  return va == vb;
}

template <class T>
vbool vsne (const APU_vec<T>& va, const APU_vec<T>& vb)
{
  ADD_VECTOR_CYCLES_FUNCTION(T, vsne)
  return va != vb;
}

template <class T>
vbool vsge (const APU_vec<T>& va, const APU_vec<T>& vb)
{
  ADD_VECTOR_CYCLES_FUNCTION(T, vsge)
  return va >= vb;
}

template <class T>
vbool vsgt (const APU_vec<T>& va, const APU_vec<T>& vb)
{
  ADD_VECTOR_CYCLES_FUNCTION(T, vsgt)
  return va > vb;
}

template <class T>
vbool vsle (const APU_vec<T>& va, const APU_vec<T>& vb)
{
  ADD_VECTOR_CYCLES_FUNCTION(T, vsle)
  return va <= vb;
}

template <class T>
vbool vslt (const APU_vec<T>& va, const APU_vec<T>& vb)
{
  ADD_VECTOR_CYCLES_FUNCTION(T, vslt)
  return va < vb;
}

////////////////
//APU-C vector select and swap implementations
////////////////
//fills the output vector elements individually from va or vb depending on the boolean value of the corresponding vc element
template <class T>
APU_vec<T> vselect (const APU_vec<T>& va, const APU_vec<T>& vb, const vbool& vc)
{
  ADD_VECTOR_CYCLES_FUNCTION(T, vselect)
  APU_vec<T> ret;
  for (int i = 0; i < _tileWidthInChunks; ++i)
  {
    if (gEnabledCUs[i])
    {
      ret.mElements[i] = vc.mElements[i] ? va.mElements[i] : vb.mElements[i];
    }
  }
  return ret;
}

//swaps the elements of va and vb on positions where vc elements are true
template <class T>
void vswap (APU_vec<T>& va, APU_vec<T>& vb, const vbool& vc)
{
  ADD_VECTOR_CYCLES_FUNCTION(T, vswap)
  for (int i = 0; i < _tileWidthInChunks; ++i)
  {
    if (gEnabledCUs[i] && vc.mElements[i])
    {
      T temp = va.mElements[i];
      va.mElements[i] = vb.mElements[i];
      vb.mElements[i] = temp;
    }
  }
}

////////////////
//APU-C specialized 16-bit shifts declarations
////////////////
//extended shifts, i.e. vd::vc = (vb::va >>[<<] vs) where high::low creates a 32-bit vector from 2 16-bit vectors
//naming convention: vsABx where:
//A (l/r) left/right shift
//B (l/a) determines whether the shift is a logical shift or an arithmetic shift
void vsllx (vec16u &resLow, vec16s &resHigh, const vec16s& va, const vec16s& vb, const vec16s& vs);
void vsrax (vec16u &resLow, vec16s &resHigh, const vec16s& va, const vec16s& vb, const vec16s& vs);
void vsrlx (vec16u &resLow, vec16s &resHigh, const vec16s& va, const vec16s& vb, const vec16s& vs);
void vsllx (vec16u &resLow, vec16u &resHigh, const vec16u& va, const vec16u& vb, const vec16u& vs);
void vsrax (vec16u &resLow, vec16u &resHigh, const vec16u& va, const vec16u& vb, const vec16u& vs);
void vsrlx (vec16u &resLow, vec16u &resHigh, const vec16u& va, const vec16u& vb, const vec16u& vs);

////////////////
//specialized APU-C 16-bit multiplications declarations
//they operate on high/low parts of the inputs only
//name format: vmul_ABCD where:
//A (s/u) determines whether the first 8-bit multiplier should be treated as signed/unsigned
//B (l/h) determines whether the first 8-bit multiplier should be copied from low/high part of the first input
//C (s/u) determines whether the second 8-bit multiplier should be treated as signed/unsigned
//D (l/h) determines whether the second 8-bit multiplier should be copied from low/high part of the first input
////////////////
vec16s vmul_ulul (const vec16s& a, const vec16s& b);
vec16s vmul_uluh (const vec16s& a, const vec16s& b);
vec16s vmul_ulsh (const vec16s& a, const vec16s& b);
vec16s vmul_slul (const vec16s& a, const vec16s& b);
vec16s vmul_ulsl (const vec16s& a, const vec16s& b);
vec16s vmul_uhul (const vec16s& a, const vec16s& b);
vec16s vmul_uhuh (const vec16s& a, const vec16s& b);
vec16s vmul_uhsh (const vec16s& a, const vec16s& b);
vec16s vmul_uhsl (const vec16s& a, const vec16s& b);
vec16s vmul_shul (const vec16s& a, const vec16s& b);
vec16s vmul_shuh (const vec16s& a, const vec16s& b);
vec16s vmul_shsh (const vec16s& a, const vec16s& b);
vec16u vmul_ulul (const vec16u& a, const vec16u& b);
vec16u vmul_uluh (const vec16u& a, const vec16u& b);
vec16s vmul_ulsh (const vec16u& a, const vec16u& b);
vec16s vmul_ulsl (const vec16u& a, const vec16u& b);
vec16s vmul_slul (const vec16u& a, const vec16u& b);
vec16u vmul_uhul (const vec16u& a, const vec16u& b);
vec16u vmul_uhsl (const vec16u& a, const vec16u& b);
vec16u vmul_uhuh (const vec16u& a, const vec16u& b);
vec16s vmul_uhsh (const vec16u& a, const vec16u& b);
vec16s vmul_shul (const vec16u& a, const vec16u& b);
vec16s vmul_shuh (const vec16u& a, const vec16u& b);
vec16s vmul_shsh (const vec16u& a, const vec16u& b);



/// Extract high and low word vectors from a 32 bit vector
vec16u extract_low(const vec32s a);
vec16u extract_low(const vec32u a);
vec16s extract_high(const vec32s a);
vec16u extract_high(const vec32u a);

vec08u extract_low(const vec16s a);
vec08u extract_low(const vec16u a);
vec08s extract_high(const vec16s a);
vec08u extract_high(const vec16u a);


///////////// Function declarations
//Vector Accumulate Middle (signed extended or zero extended depending on input type)
/**
void vacm(vec16s va_high, vec16u va_low, vec16s vb))
va_high: source and destination high 16-bit;
va_low: source and destination low 16-bit;
vb: source input 16-bit

Computes [va_high va_low] += (vec32s)sext(vb) << 8

*/
void vacm(APU_vec<int32s>& va, const APU_vec<int16s>& vb);
void vacm(APU_vec<int32u>& va, const APU_vec<int16u>& vb);
void vacm(APU_vec<int16s>& va_hi, APU_vec<int16u>& va_lo, const APU_vec<int16s>& vb);
void vacm(APU_vec<int16u>& va_hi, APU_vec<int16u>& va_lo, const APU_vec<int16u>& vb);

void vacl(APU_vec<int32s>& va, const APU_vec<int16s>& vb);
void vacl(APU_vec<int32u>& va, const APU_vec<int16u>& vb);
void vacl(APU_vec<int16s>& va_hi, APU_vec<int16u>& va_lo, const APU_vec<int16s>& vb);
void vacl(APU_vec<int16u>& va_hi, APU_vec<int16u>& va_lo, const APU_vec<int16u>& vb);


/**
*It returns the number of leading zeros of crtEl. If va is negative, then returns zero.
*@parameter va Source vector
*@return clz(va)
*/
template <class T>
int08u clz(const T crtEl) {
	T tmp = crtEl;
	int bits = sizeof(T) * 8;
	int08u numZeros = 0;
	uint32_t msb = 1 << (bits - 1);
	for (int i = 0; i < bits; ++i) {
		if (tmp & msb) {
			break;
		}
		++numZeros;
		tmp <<= 1;
	}
	return numZeros;
}

/**
*It returns the number of leading zeros of crtEl. If va is negative, then returns zero.
*@parameter va Source vector
*@return clz(va)
*/
template <class T>
int08u clb(const T crtEl) {
	T tmp = crtEl;
	int bits = sizeof(T) * 8;
	int08u numSignedBits = 0;
	uint32_t msb = 1 << (bits - 1);
	for (int i = 1; i < bits; ++i) {
		if (tmp ^ msb) {
			break;
		}
		++numSignedBits;
		tmp <<= 1;
	}
	return numSignedBits;
}
/// Count leading zero
template <class T>
vec08u vclz(const APU_vec<T>& v) {	
	int bits = sizeof(T) * 8;	
	vec08u numZeros = 0;
	for (int j = 0; j < _tileWidthInChunks; ++j)
	{
		if (gEnabledCUs[j])
		{
			T crtEl = v.mElements[j];
			numZeros.mElements[j] = clz(crtEl);
		}
	}
	return numZeros;	
}

/// Count leading sign bits
template <class T>
vec08u vclb(const APU_vec<T>& v) {
	int bits = sizeof(T) * 8;
	vec08u numZeros = 0;
	for (int j = 0; j < _tileWidthInChunks; ++j)
	{
		if (gEnabledCUs[j])
		{
			T crtEl = v.mElements[j];
			numZeros.mElements[j] = clb(crtEl);
		}
	}
	return numZeros;
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
void vsx(vec16s  a, vec16s&  b, vec16u&  c);


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
void vsx(vec16u  a, vec16u&  b, vec16u&  c);


/**
 *Vector Sign Extension(to 32 - bit)
 *@parameter a[in]
 * @parameter b[out] msb
 *@parameter c[out] lsb
 *@return[b c] = [(a >> 15) a]
*/
void vszx(vec16u  a, vec16u &  b, vec16u &  c);


/**
 *Vector Zero Extension and Shift Right Bit 8 (to 32-bit)
 *
 *@parameter a [in]
 *@parameter b [out] msb
 *@parameter c [out] lsb
 *@parameter return [ b c ] = [ ((u)a>>8) (a<<8) ]
*/
void vszx(vec16s  a, vec16s &  b, vec16u &  c);

/**
 *Vector Zero Extension.
 *
 *@parameter a [in]
 *@parameter b [out] msb
 *@parameter c [out] lsb
 *@return [ b c ] = [ 0 a ]
*/
void vzx(vec16s  a, vec16s &  b, vec16u &  c);

/**
 *Vector Zero Extension.
 *
 *@parameter a [in]
 *@parameter b [out] msb
 *@parameter c [out] lsb
 *@return [ b c ] = [ 0 a ]
*/
void vzx(vec16u  a, vec16u &  b, vec16u &  c);


/**
* Vector Sign Extension and Shift Right bit 8 (to 32-bit)
*
*@parameter a [in]
*@parameter b [out] msb
*@parameter c [out] lsb
*@return [ b c ] = [ (a>>8) (a<<8) ]
*/
void vssx(vec16u  a, vec16u &  b, vec16u &  c);


/**
 * Vector Sign Extension and Shift Right bit 8 (to 32-bit)
 *
 *@parameter a [in]
 *@parameter b [out] msb
 *@parameter c [out] lsb
 *@return [ b c ] = [ (a>>8) (a<<8) ]
*/
void vssx(vec16s  a, vec16s &  b, vec16u &  c);



/**
 *If the source is greater than the upper bound or smaller than the lower bound, it is set ("clamped") to the upper/lower bound (16-bit)
 *
 *@parameter va Source vector
 *@parameter vb Lower bound
 *@parameter vc Upper bound
 *@return if (va >= upper bound) upper bound, else if (va <= upper bound) lower bound, else va
*/
vec16s vsat(vec16s  va, vec16s  vb, vec16s  vc);

/**
*If the source is greater than the upper bound or smaller than the lower bound, it is set ("clamped") to the upper/lower bound (16-bit)
*
*@parameter va Source vector
*@parameter vb Lower bound
*@parameter vc Upper bound
*@return if (va >= upper bound) upper bound, else if (va <= upper bound) lower bound, else va
*/

vec16u vsat(vec16u  va, vec16u  vb, vec16u  vc);

//TODO
//void _vmac(vec32s& o, vec08u a, short b);



////////////////
//APU-C absolute value implementation
////////////////
template <class T>
APU_vec<T> vabs(const APU_vec<T>& arV)
{
	ADD_VECTOR_CYCLES_FUNCTION(T, vabs)
		APU_vec<T> ret;
	for (int i = 0; i < _tileWidthInChunks; ++i)
	{
		if (gEnabledCUs[i])
		{
			ret.mElements[i] = arV.mElements[i] < 0 ? -arV.mElements[i] : arV.mElements[i];
		}
	}
	return ret;
}

///////////// Function declarations


//these vector type string declarations are needed here
//see apu_cycles.hpp
template <> std::string GetVectorTypeString<vec08u>();
template <> std::string GetVectorTypeString<vec08s>();
template <> std::string GetVectorTypeString<vec16u>();
template <> std::string GetVectorTypeString<vec16s>();
template <> std::string GetVectorTypeString<vec32u>();
template <> std::string GetVectorTypeString<vec32s>();
template <> std::string GetVectorTypeString<int08u>();
template <> std::string GetVectorTypeString<int08s>();
template <> std::string GetVectorTypeString<int16u>();
template <> std::string GetVectorTypeString<int16s>();
template <> std::string GetVectorTypeString<int32u>();
template <> std::string GetVectorTypeString<int32s>();


}

#endif // _APU_VEC_H_
