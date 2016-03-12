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
#ifdef APEX2_EMULATE // This is needed only for the Target Compiler
#include "acf_lib.hpp"
#else
	#include <apex.h>
#endif

#include <iostream>
#include <ostream>
//#include <memory.h>
using namespace std;

#include "apu_gauss_5x5_graph.h"
#include "apu_gauss_5x5_process.h"

CGauss_5x5_Proc::~CGauss_5x5_Proc(){
	lOutput.SetFreeOnExit(true);
}


int CGauss_5x5_Proc::InitData(DataDescriptor *input)
{
	lInput = input;
	lOutput.Init(lInput->GetWidth(), lInput->GetHeight(), lInput->GetElementDataType());
	m_errVal |= !(lOutput.IsOK());
	return m_errVal;
}


int CGauss_5x5_Proc::Connect()
{

#ifdef APEX2_EMULATE
	cout << "\nInitializing graph:" << GAUSS_5x5_GN << endl;
#endif

	m_errVal |= Initialize();
	m_errVal |= ConnectIO(GAUSS_5x5_GRAPH_IN, *lInput);
	m_errVal |= ConnectIO(GAUSS_5x5_GRAPH_OUT, lOutput);

#ifdef APEX2_EMULATE
	cout << GAUSS_5x5_GN << " graph Plan: " << endl;
	cout << GetExecutionPlanDescription() << endl;
#endif


#ifdef APEX2_EMULATE
	if (m_errVal)
	{
		std::cout << GAUSS_5x5_GN << " plan error!" << endl;
		std::cout << ErrorMessage() << endl;
		char c;
		std::cin >> c;
	}
#endif

	return m_errVal;
}

