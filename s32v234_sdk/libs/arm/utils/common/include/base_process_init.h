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
#ifndef CBASE_PROC_INIT_H
#define CBASE_PROC_INIT_H

#include <iostream>
#include <string>

using namespace std;

#ifdef APEX2_EMULATE
#include "acf_data_descriptor.hpp" 
using namespace APEX2; 
#else 
#include <icp_data.h>
#include <apex.h>
//#include<OAL.h>
using namespace icp;
#endif

#include "time_measure.h"
#include "stringify_macros.h"



/// Base class for composite processes (i.e. having more than one process). It defines the basic interface.
class CBase_CompositeProc {

public:
	int64_t m_apex_ticksBefore; /// ticks before loading data
	int64_t m_apex_ticks0;		/// ticks before starting the run 
	int64_t m_apex_ticks1;		/// ticks after end of run
	int64_t m_apex_ticksAfter;	/// ticks after unloading data
	bool	m_addToGlobal;		/// if true, then add the tick differences to the global variables

protected:
	int32_t m_errVal;

public:
	CBase_CompositeProc()
		: m_errVal(0)
	{}
	virtual ~CBase_CompositeProc(){}
	virtual int32_t Connect() = 0;
	virtual int32_t Start() = 0;
	virtual int32_t Wait() = 0;
	virtual int32_t Exec() = 0;
	virtual std::string ErrorMessage() = 0;

	virtual int32_t Exec(std::string
	                 #ifdef APEX2_EMULATE
	                   graphName
                         #endif
			) {

#ifdef APEX2_EMULATE
		std::cout << "\nExecuting graph: " << graphName << std::endl;
#endif

		m_errVal |= Start();
		m_errVal |= Wait();

#ifdef APEX2_EMULATE
		if (m_errVal) {
			std::cout << graphName << "Execution error" << std::endl;
			std::cout << ErrorMessage() << std::endl;
			char c;
			std::cin >> c;

		}
#endif

		return m_errVal;
	}

	int32_t Create_and_exec() {
		int lretVal = Connect();

		if (lretVal == 0)
			lretVal = Exec();

		return m_errVal;
	}

	virtual int32_t Error() {
		return m_errVal;
	}

};


/// Template base class for a single process. Defines the interface and basic operations
template <class ACF_Proc>
class CBase_ProcInit : public ACF_Proc {
protected:
	int32_t m_errVal;

#ifdef DEF_TIME_MEASURE
	uint64_t m_apex_ticksBefore; /// ticks before loading data
	uint64_t m_apex_ticks0;		/// ticks before starting the run 
	uint64_t m_apex_ticks1;		/// ticks after end of run
	uint64_t m_apex_ticksAfter;	/// ticks after unloading data
	bool	m_addToGlobal;		/// if true, then add the tick differences to the global variables
#endif

public:
        CBase_ProcInit()
		:
#ifdef APEX2_EMULATE
		ACF_Proc((APEX_ID)APEX_APEX0)
#else
		ACF_Proc(0)
#endif
		, m_errVal(false)

#ifdef DEF_TIME_MEASURE
		, m_addToGlobal(true)
#endif
	{
	}
	
	CBase_ProcInit(int apex_id)
		:
#ifdef APEX2_EMULATE
		ACF_Proc((APEX_ID)apex_id)
#else
		ACF_Proc(apex_id)
#endif
		, m_errVal(false)

#ifdef DEF_TIME_MEASURE
		, m_addToGlobal(true)
#endif
	{
	}

	CBase_ProcInit(bool addGlobal, int apex_id)
		:
#ifdef APEX2_EMULATE
		ACF_Proc((APEX_ID)apex_id)
#else
		ACF_Proc(apex_id)
#endif
		, m_errVal(false)

#ifdef DEF_TIME_MEASURE
		, m_addToGlobal(addGlobal)
#endif
	{
	}

	virtual ~CBase_ProcInit(){}
	virtual int32_t Connect() = 0;
	virtual int32_t Exec() {

#ifdef APEX2_EMULATE
		cout << "\nExecuting graph: " << mGraph.m_graphName << endl;
#endif


#ifdef DEF_TIME_MEASURE
		m_apex_ticks0 = 0;
		m_apex_ticks1 = 0;
		m_apex_ticksAfter = 0;


		m_apex_ticksBefore = FSL_Ticks();
#endif		

		//m_errVal |= ACF_Proc::Start_Prepare();

#ifdef DEF_TIME_MEASURE
		m_apex_ticks0 = FSL_Ticks();
#endif		
			m_errVal |= ACF_Proc::Start();
			m_errVal |= ACF_Proc::Wait();

		//m_errVal |= ACF_Proc::Start_Run();
		//m_errVal |= ACF_Proc::Wait_NoReset();

#ifdef DEF_TIME_MEASURE
		m_apex_ticks1 = FSL_Ticks();
#endif
		//m_errVal |= ACF_Proc::NoWait_Reset();

#ifdef DEF_TIME_MEASURE
		m_apex_ticksAfter = FSL_Ticks();
		if (m_addToGlobal) {

			uint64_t apex_ticks = getRunTicks();
			total_apex_ticks += apex_ticks;
			total_load_ticks += getLoadTicks();

			//std::cout << "\nExec_End(): TIME MEASURED FOR APEX " << apex_ticks << ", and TOTAL : " << total_apex_ticks << " at time stamp " << FSL_Ticks() << endl;
		}
#endif		


#ifdef APEX2_EMULATE
		if (m_errVal) {
			std::cout << mGraph.m_graphName << " execution error" << endl;
			std::cout << ErrorMessage() << endl;
			char c;
			std::cin >> c;
		}
#endif
		return m_errVal;
	}

	virtual int32_t Start() {

#ifdef APEX2_EMULATE
		cout << "\nStarting graph: " << mGraph.m_graphName << endl;
#endif


#ifdef DEF_TIME_MEASURE
		m_apex_ticks0 = 0;
		m_apex_ticks1 = 0;
		m_apex_ticksAfter = 0;


		m_apex_ticksBefore = FSL_Ticks();
#endif		

		//m_errVal |= ACF_Proc::Start_Prepare();

#ifdef DEF_TIME_MEASURE
		m_apex_ticks0 = FSL_Ticks();
#endif			

		//m_errVal |= ACF_Proc::Start_Run();
		m_errVal |= ACF_Proc::Start();

		return m_errVal;
	}

	


	virtual int32_t Wait() {
		if (!m_errVal) {
			m_errVal |= ACF_Proc::Wait();


#ifdef DEF_TIME_MEASURE
			m_apex_ticks1 = FSL_Ticks();
#endif
			
		}
#ifdef DEF_TIME_MEASURE
		m_apex_ticksAfter = FSL_Ticks();
		if (m_addToGlobal) {

			uint64_t apex_ticks = getRunTicks();
			total_apex_ticks += apex_ticks;
			total_load_ticks += getLoadTicks();
			//std::cout << "\nWait_End(): TIME MEASURED FOR APEX " << apex_ticks << ", and TOTAL : " << total_apex_ticks << " at time stamp "<< FSL_Ticks() << endl;
		}
#endif		


#ifdef APEX2_EMULATE
		if (m_errVal) {
			std::cout << mGraph.m_graphName << " execution error" << endl;
			std::cout << ErrorMessage() << endl;
			char c;
			std::cin >> c;

		}
#endif
		return m_errVal;

	}


	virtual std::string ErrorMessage(){
#ifdef APEX2_EMULATE
		return ACF_Proc::ErrorMessage();
#else
		return ("");
#endif
	}

	virtual int32_t Error() {
		return m_errVal;
	}

	int64_t getStartTicks() {
#ifdef DEF_TIME_MEASURE
		return m_apex_ticksBefore;
#else 
		return (int64_t) 0;
#endif
	}

	uint64_t getEndTicks() {
#ifdef DEF_TIME_MEASURE
		return m_apex_ticksAfter;
#else 
		return (int64_t)0;
#endif
	}

	uint64_t getLoadTicks() {
#ifdef DEF_TIME_MEASURE
		return m_apex_ticks0 - m_apex_ticksBefore + m_apex_ticksAfter - m_apex_ticks1;
#else 
		return (int64_t)0;
#endif
	}

	uint64_t getRunTicks() {
#ifdef DEF_TIME_MEASURE
		return m_apex_ticks1 - m_apex_ticks0;
#else 
		return (int64_t)0;
#endif

	}
};

#endif