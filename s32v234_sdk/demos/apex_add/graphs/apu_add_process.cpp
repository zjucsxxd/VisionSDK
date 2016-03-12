/*****************************************************************************
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

#include <iostream>
#include <ostream>
using namespace std;

#include "apu_add_graph.h"
#include "apu_add_process.h"

CTemplate_Demo_Proc::~CTemplate_Demo_Proc(){
	// Deallocate only the data allocated by this process	
	lOutput.SetFreeOnExit(true);
}



int CTemplate_Demo_Proc::InitData(DataDescriptor *inputA, DataDescriptor *inputB){
	// set only the pointers of the input data
	lInputA = inputA;
	lInputB = inputB;
		
	lOutput.Init(lInputA->GetWidth(), lInputA->GetHeight(), DATATYPE_16U, lInputA->GetElementDimX(), lInputA->GetElementDimY(), lInputA->GetDimensions() );
	return 0;
}

int32_t CTemplate_Demo_Proc::Connect()
{

#ifdef APEX2_EMULATE
	cout << "\nInitializing graph:" << mGraph.m_graphName  << endl;
#endif

	int lRetVal = 0;
	lRetVal |= Initialize();
	lRetVal |= ConnectIO(ADD_GRAPH_INA, *lInputA);
	lRetVal |= ConnectIO(ADD_GRAPH_INB, *lInputB);

	lRetVal |= ConnectIO(ADD_GRAPH_OUT, lOutput);


#ifdef APEX2_EMULATE
	cout << mGraph.m_graphName << " graph Plan: " << endl;
	cout << GetExecutionPlanDescription() << endl;
#endif


#ifdef APEX2_EMULATE
	if (lRetVal)
	{
		std::cout << mGraph.m_graphName << " plan error!" << endl;
		std::cout << ErrorMessage() << endl;
		char c;
		std::cin >> c;
	}
#endif

	return lRetVal;
}
