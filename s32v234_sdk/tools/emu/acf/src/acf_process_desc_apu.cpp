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
* \file APU_ACF.cpp
* \brief APU ACF process description simulation
* \author Igor Aleksandrowicz
* \version
* \date 12-February-2014
****************************************************************************/

#include "acf_process_desc_apu.hpp"

using namespace APEX2;

/****************************************************************************
* functions
****************************************************************************/

void ACF_Process_Desc_APU::Initialize(ACF_Graph& graph, const string& name)
{
  if (errorOccured)
  {
    return;
  }

  if (_graphUsed != 0)
  {
    errorOccured = true;
    errorMessage = "the process description is already initialized";
    return;
  }

  _graphUsed = &graph;
  this->name = name;
  _graphUsed->Create();
  if (!CheckGraph(true))
  {
    return;
  }

}

void ACF_Process_Desc_APU::SetInputChunkSize(const string& portName, int chunkWidth, int chunkHeight)
{
  CheckCommonRuntimeErrors();
  if (errorOccured)
  {
    return;
  }

  _graphUsed->SetGraphPortTileSize(portName, chunkWidth, chunkHeight);

  //report as a process error rather than a graph error
  CheckGraph(false);
}

void ACF_Process_Desc_APU::CheckCommonRuntimeErrors()
{
  if (errorOccured)
  {
    return;
  }

  if (_graphUsed == 0)
  {
    errorOccured = true;
    errorMessage = "no graph assigned to the process";
    return;
  }
}

bool ACF_Process_Desc_APU::CheckGraph(bool reportAsGraphError)
{
  if (_graphUsed->ErrorOccured())
  {
    errorOccured = true;
    errorMessage = reportAsGraphError ? "graph error: " + _graphUsed->ErrorMessage() : _graphUsed->ErrorMessage();
    return false;
  }

  return true;
}

int ACF_Process_Desc_APU::Initialize()
{
  Create();
  CheckCommonRuntimeErrors();
  if (errorOccured)
  {
    return 1;
  }

  //can be computed only once
  _graphUsed->MakeSerialPlan();
  _graphUsed->ComputeChunkSizes();
  if (!CheckGraph(true))
  {
    return 1;
  }

  return 0;
}

int ACF_Process_Desc_APU::ConnectIO(const string ioName, DataDescriptor& dataDescriptor)
{
  CheckCommonRuntimeErrors();
  if (errorOccured)
  {
    return 1;
  }

  _graphUsed->ConnectData(ioName, &dataDescriptor);
  //report as a process error rather than a graph error
  if (!CheckGraph(false))
  {
    return 1;
  }

  return 0;
}


int ACF_Process_Desc_APU::ConnectIO_ROI(std::string lPortIdentifier,
	DataDescriptor& lContigDataDesc,
	int ROI_left,
	int ROI_width,
	int ROI_top,
	int ROI_height)
{
	int lRetVal = 0;
	lContigDataDesc.SetROI(ROI_left, ROI_top, ROI_width, ROI_height);
	//DataDescriptor lDescRoi(lContigDataDesc); 

	lRetVal = ConnectIO(lPortIdentifier, lContigDataDesc);//lDescRoi);
//	lContigDataDesc.ClearROI();
	return lRetVal;
}


int ACF_Process_Desc_APU::ConnectIndirectInput(const string& ioName, DataDescriptor& dataDescriptor, DataDescriptor& offsetDescriptor)
{
  CheckCommonRuntimeErrors();
  if (errorOccured)
  {
    return 1;
  }

  _graphUsed->ConnectIndirectData(ioName, &dataDescriptor, &offsetDescriptor);
  //report as a process error rather than a graph error
  if (!CheckGraph(false))
  {
    return 1;
  }

  return 0;
}

int ACF_Process_Desc_APU::FlagInputAsChunkBasedIndirect(const string& ioName)
{
  CheckCommonRuntimeErrors();
  if (errorOccured)
  {
    return 1;
  }

  _graphUsed->FlagIndirect(ioName);
  //report as a process error rather than a graph error
  if (!CheckGraph(false))
  {
    return 1;
  }

  return 0;
}


int ACF_Process_Desc_APU::Start()
{
  CheckCommonRuntimeErrors();
  if (errorOccured)
  {
    return 1;
  }

  //have to be computed for each run (PrepareDataPlaces could be updated only when connecting other data)
  _graphUsed->PrepareDataPlaces();
  _graphUsed->Run();
  if (!CheckGraph(false))
  {
    return 1;
  }

  return 0;
}



int ACF_Process_Desc_APU::Start_Prepare() {
	CheckCommonRuntimeErrors();
	if (errorOccured)
	{
		return 1;
	}

	//have to be computed for each run (PrepareDataPlaces could be updated only when connecting other data)
	_graphUsed->PrepareDataPlaces();


	return 0;
}

int ACF_Process_Desc_APU::Start_Run(){
	CheckCommonRuntimeErrors();
	if (errorOccured)
	{
		return 1;
	}

	_graphUsed->Run();
	if (!CheckGraph(false))
	{
		return 1;
	}

	return 0;
}

int ACF_Process_Desc_APU::Wait()
{
  //this function doesn't really do anything except checking the errors, included for ACF compatibility reasons
  CheckCommonRuntimeErrors();
  if (errorOccured)
  {
    return 1;
  }

  return 0;
}

string ACF_Process_Desc_APU::GetExecutionPlanDescription()
{
  CheckCommonRuntimeErrors();
  if (errorOccured)
  {
    return "no plan due to errors\n";
  }

  return _graphUsed->GetPlanDescription();
}

ACF_Graph::DataPlace* ACF_Process_Desc_APU::GetDataPlacePtr(const string& kernelInstanceName, const string& portName)
{
  if (_graphUsed == 0)
  {
    return 0;
  }
  return _graphUsed->GetDataPlacePtr(kernelInstanceName, portName);
}

bool ACF_Process_Desc_APU::WarningOccured()
{
  return _graphUsed->WarningOccured() || warningOccured;
}

string ACF_Process_Desc_APU::WarningMessages()
{
  string ret;
  if (_graphUsed->WarningOccured())
  {
    ret += _graphUsed->WarningMessages();
  }
  ret += warningMessages;
  return ret;
}