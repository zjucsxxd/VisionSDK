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
* \file APU_cycles.h
* \brief APU cycles counter
* \author Igor Aleksandrowicz
* \version
* \date 04-March-2014
****************************************************************************/

#ifndef _APU_CYCLES_H_
#define _APU_CYCLES_H_

#include "apu_config.hpp"
#include <string>
#include <unordered_map>

using std::string;
using std::unordered_map;

namespace APEX2
{
	/// class needed to have an implicit counter value of 1 whenever an operation is not present in the database
	typedef unsigned long CycleCounterBaseTp;
	class CycleCounterType{
	protected:
		CycleCounterBaseTp _val;
	public:
		CycleCounterType() : _val(1){}
		CycleCounterType(unsigned long v) : _val(v){}
		CycleCounterType(const CycleCounterType& v) : _val(v._val){}
		virtual ~CycleCounterType(){}

		CycleCounterBaseTp& operator()(){ return _val; }
		CycleCounterBaseTp& operator = (unsigned long v){ _val = v; return _val; }
		CycleCounterBaseTp& operator += (unsigned long v){ _val += v;  return _val; }
		CycleCounterBaseTp& operator += (const CycleCounterType& v){ _val += v._val;  return _val; }
		CycleCounterBaseTp& operator ++ (){ return (++_val); }
	};

//global vector cycle counter and vector operation counter
extern CycleCounterType gVectorCycles;
extern CycleCounterType gVectorOperations;
//boolean for temporarily disabling the counting
extern bool gCycleCountPaused;
//a database assigning a cycle count to each vector operation
extern unordered_map<string, CycleCounterType> gCycleDatabase;

//returns vector name type for both vectors and scalars (e.g. int08u returns "vec08u")
//default implementation returns an empty string, specific types are implemented in apu_cycles.cpp
template <typename T>
string GetVectorTypeString()
{
  return "";
}

//cycle counting can be paused and resumed
void PauseCycleCounting();
void ResumeCycleCounting();

//increments the cycle counters
//the parameter T is used for determining which vector type should be searched for in the database
//isBinaryOperator should be used for distinguishing between unary and binary operations for operators having both variants
template<typename T>
void AddVectorCycles(const string& operationCode, bool isBinaryOperator = false)
{
  if (gCycleCountPaused)
  {
    return;
  }
  //search the database for the cycle count
  string cycleDatabaseIndex = GetVectorTypeString<T>() + (isBinaryOperator ? "_binary_" : "_") + operationCode;
  gVectorCycles += gCycleDatabase[cycleDatabaseIndex];
  ++gVectorOperations;
}

//non-parametrized version
//used for vif, velse
inline void AddVectorCycles(const string& operationCode)
{
  if (!gCycleCountPaused)
  {
    gVectorCycles += gCycleDatabase[operationCode];
    ++gVectorOperations;
  }
}

CycleCounterBaseTp GetVectorCyclesElapsed();
CycleCounterBaseTp GetVectorOperationsElapsed();
double GetEstimatedExecutionTime();

//don't include the cycle counting overhead if the counting is disabled
#if COUNT_CYCLES
#define ADD_VECTOR_CYCLES_UNARY_OPERATOR(DATATYPE, OPERATOR) AddVectorCycles<DATATYPE>(#OPERATOR, false);
#define ADD_VECTOR_CYCLES_BINARY_OPERATOR(DATATYPE, OPERATOR) AddVectorCycles<DATATYPE>(#OPERATOR, true);
#define ADD_VECTOR_CYCLES_FUNCTION(DATATYPE, OPERATOR) AddVectorCycles<DATATYPE>(#OPERATOR);
#define PAUSE_CYCLE_COUNTING PauseCycleCounting();
#define RESUME_CYCLE_COUNTING ResumeCycleCounting();
#define ADD_VECTOR_CYCLES(OPERATION) AddVectorCycles(#OPERATION);
#else
#define ADD_VECTOR_CYCLES_UNARY_OPERATOR(DATATYPE, OPERATOR)
#define ADD_VECTOR_CYCLES_BINARY_OPERATOR(DATATYPE, OPERATOR)
#define ADD_VECTOR_CYCLES_FUNCTION(DATATYPE, OPERATOR)
#define PAUSE_CYCLE_COUNTING
#define RESUME_CYCLE_COUNTING
#define ADD_VECTOR_CYCLES(OPERATION)
#endif
}

#endif // _APU_CYCLES_H_
