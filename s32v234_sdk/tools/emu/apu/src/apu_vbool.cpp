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
* \file APU_vbool.cpp
* \brief APU vector boolean implementation
* \author Igor Aleksandrowicz
* \version
* \date 26-August-2013
****************************************************************************/

#include "apu_vbool.hpp"

using namespace APEX2;

vbool::vbool()
{
  for (int i = 0; i < VSIZE; ++i)
  {
    mElements[i] = 0;
  }
}

//broadcast
vbool::vbool(const vbool_elem_T& arValue)
{
  ADD_VECTOR_CYCLES_BINARY_OPERATOR(vbool, =)
  for (int i = 0; i < VSIZE; ++i)
  {
    if (gEnabledCUs[i])
    {
      mElements[i] = arValue;
    }
  }
}

vbool& vbool::operator=(const vbool& arRhs)
{
  ADD_VECTOR_CYCLES_BINARY_OPERATOR(vbool, =)
  for (int i = 0; i < VSIZE; ++i)
  {
    if (gEnabledCUs[i])
    {
      mElements[i] = arRhs.mElements[i];
    }
  }
  return *this;
}

//vector boolean logical operations implementation

vbool vbool::operator== (const vbool& arOther) const
{
  ADD_VECTOR_CYCLES_BINARY_OPERATOR(vbool, ==)
  vbool r;
  for (int i = 0; i < VSIZE; ++i)
  {
    if (gEnabledCUs[i])
    {
      r.mElements[i] = (mElements[i] == arOther.mElements[i]);
    }
  }
  return r;
}

vbool vbool::operator!= (const vbool& arOther) const
{
  ADD_VECTOR_CYCLES_BINARY_OPERATOR(vbool, !=)
  return !(operator==(arOther));
}

vbool vbool::operator&& (const vbool& arOther) const
{
  ADD_VECTOR_CYCLES_BINARY_OPERATOR(vbool, &&)
  vbool r;
  for (int i = 0; i < VSIZE; ++i)
  {
    if (gEnabledCUs[i])
    {
      r.mElements[i] = mElements[i] && arOther.mElements[i];
    }
  }
  return r;
}

vbool vbool::operator|| (const vbool& arOther) const
{
  ADD_VECTOR_CYCLES_BINARY_OPERATOR(vbool, ||)
  vbool r;
  for (int i = 0; i < VSIZE; ++i)
  {
    if (gEnabledCUs[i])
    {
      r.mElements[i] = mElements[i] || arOther.mElements[i];
    }
  }
  return r;
}

vbool vbool::operator!() const
{
  ADD_VECTOR_CYCLES_UNARY_OPERATOR(vbool, !)
  vbool r;
  for (int i = 0; i < VSIZE; ++i)
  {
    if (gEnabledCUs[i])
    {
      r.mElements[i] = !mElements[i];
    }
  }
  return r;
}




vbool vbool::operator~() 
{
	ADD_VECTOR_CYCLES_UNARY_OPERATOR(vbool, !)	
	for (int i = 0; i < VSIZE; ++i)
	{
		if (gEnabledCUs[i])
		{
			mElements[i] = !mElements[i];
		}
	}
	return *this;
}

//vector boolean move shifts and move rotations implementation

vbool vbool::moveShiftLeft(const vbool& arFillVector) const
{
  vbool r = *this;
  for (int i = 0; i < VSIZE - 1; ++i)
  {
	//if (gEnabledCUs[i] && gEnabledCUs[i+1])
    {
      r.mElements[i] = mElements[i+1];
    }
  }
  //if (gEnabledCUs[VSIZE - 1])
  {
    r.mElements[VSIZE - 1] = arFillVector.mElements[VSIZE - 1];
  }
  return r;
}

vbool vbool::moveShiftRight(const vbool& arFillVector) const
{
  vbool r = *this;
  for (int i = 1; i < VSIZE; ++i)
  {
	//if (gEnabledCUs[i] && gEnabledCUs[i - 1])
	{
      r.mElements[i] = mElements[i-1];
    }
  }
 // if (gEnabledCUs[0])
  {
    r.mElements[0] = arFillVector.mElements[0];
  }
  return r;
}

vbool vbool::moveRotateLeft(const vbool& arFillVector) const
{
  vbool r = *this;
  for (int i = 0; i < VSIZE - 1; ++i)
  {
	if (gEnabledCUs[i] && gEnabledCUs[i + 1])
	{
      r.mElements[i] = mElements[i+1];
    }
  }
  if (gEnabledCUs[VSIZE - 1])
  {
    r.mElements[VSIZE - 1] = arFillVector.mElements[0];
  }
  return r;
}

vbool vbool::moveRotateRight(const vbool& arFillVector) const
{
  vbool r = *this;
  for (int i = 1; i < VSIZE; ++i)
  {
	if (gEnabledCUs[i] && gEnabledCUs[i - 1])
	{
      r.mElements[i] = mElements[i-1];
    }
  }
  if (gEnabledCUs[0])
  {
    r.mElements[0] = arFillVector.mElements[VSIZE - 1];
  }
  return r;
}

//vector boolean accumulation function implementation
//use caution when combining vall, vany with vif/velse, in this library they take only active CUs into account, in real ACF vany works like that but vall seems to be incorrect, vall seems to always returns false when some CUs are inactive
vbool_elem_T vbool::all() const
{
  for (int i = 0; i < VSIZE; ++i)
  {
    if (gEnabledCUs[i] && !bool(mElements[i]))
    {
      return false;
    }
  }
  return vbool_elem_T(true);
}

vbool_elem_T vbool::any() const
{
  for (int i = 0; i < VSIZE; ++i)
  {
    if (gEnabledCUs[i] && bool(mElements[i]))
    {
      return true;
    }
  }
  return vbool_elem_T(false);
}



//APU-C vector boolean vget, vput implementation

vbool APEX2::vselect(const vbool& va, const vbool& vb, const vbool& vc)
{
	ADD_VECTOR_CYCLES_FUNCTION(int08u, vselect)
		vbool ret;
	for (int i = 0; i < VSIZE; ++i)
	{
		if (gEnabledCUs[i])
		{
			ret.mElements[i] = vc.mElements[i] ? va.mElements[i] : vb.mElements[i];
		}
	}
	return ret;
}

vbool_elem_T APEX2::vget(const vbool& arVector, int aIndex)
{
  ADD_VECTOR_CYCLES_FUNCTION(vbool, vget)
  assert(aIndex >= 0 && aIndex < VSIZE);
  return arVector.mElements[aIndex];
}

vbool APEX2::vput(const vbool& arVector, const vbool_elem_T& arValue, int aIndex)
{
  ADD_VECTOR_CYCLES_FUNCTION(vbool, vput)
  assert(aIndex >= 0 && aIndex < VSIZE);
  vbool r = arVector;
  r.mElements[aIndex] = arValue;
  return r;
}

//APU-C vector boolean move shifts and rotates implementation using the previously defined functions
vbool APEX2::vmsl(const vbool& arVectorShift, const vbool& arVectorFill)
{
  ADD_VECTOR_CYCLES_FUNCTION(vbool, vmsl)
  return arVectorShift.moveShiftLeft(arVectorFill);
}

vbool APEX2::vmsr(const vbool& arVectorShift, const vbool& arVectorFill)
{
  ADD_VECTOR_CYCLES_FUNCTION(vbool, vmsr)
  return arVectorShift.moveShiftRight(arVectorFill);
}

vbool APEX2::vmrl(const vbool& arVectorRotate, const vbool& arVectorFill)
{
  ADD_VECTOR_CYCLES_FUNCTION(vbool, vmrl)
  return arVectorRotate.moveRotateLeft(arVectorFill);
}

vbool APEX2::vmrr(const vbool& arVectorRotate, const vbool& arVectorFill)
{
  ADD_VECTOR_CYCLES_FUNCTION(vbool, vmrr)
  return arVectorRotate.moveRotateRight(arVectorFill);
}

vbool APEX2::vmsl(const vbool& arVectorShift)
{
  ADD_VECTOR_CYCLES_FUNCTION(vbool, vmsl)
  return arVectorShift.moveShiftLeft(0);
}

vbool APEX2::vmsr(const vbool& arVectorShift)
{
  ADD_VECTOR_CYCLES_FUNCTION(vbool, vmsr)
  return arVectorShift.moveShiftRight(0);
}

vbool APEX2::vmrl(const vbool& arVectorRotate)
{
  ADD_VECTOR_CYCLES_FUNCTION(vbool, vmrl)
  return arVectorRotate.moveRotateLeft(arVectorRotate);
}

vbool APEX2::vmrr(const vbool& arVectorRotate)
{
  ADD_VECTOR_CYCLES_FUNCTION(vbool, vmrr)
  return arVectorRotate.moveRotateRight(arVectorRotate);
}

//APU-C vector boolean accumulation functions implementation using the previously defined functions
bool APEX2::vall(const vbool& arCheck)
{
  ADD_VECTOR_CYCLES_FUNCTION(vbool, vall)
  return bool(arCheck.all());
}

bool APEX2::vany(const vbool& arCheck)
{
  ADD_VECTOR_CYCLES_FUNCTION(vbool, vany)
  return bool(arCheck.any());
}
