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
* \file APU_ACF.h
* \brief APU ACF process description simulation
* \author Igor Aleksandrowicz
* \version
* \date 12-February-2014
****************************************************************************/

#ifndef _APU_ACF_PROCESS_DESC_APU_H_
#define _APU_ACF_PROCESS_DESC_APU_H_

#include "acf_graph.hpp"

namespace APEX2
{

//ACF process descriptor implementation
//also contains the final process functionality
class ACF_Process_Desc_APU
{
private:
  ACF_Graph* _graphUsed;
  string name;

  bool errorOccured;
  string errorMessage;
  bool warningOccured;
  string warningMessages;

  void CheckCommonRuntimeErrors();
  //returns false if there were graph errors
  //the error will be reported as a graph error if reportAsGraphError is true, as a process error otherwise
  bool CheckGraph(bool reportAsGraphError);
public:
  ACF_Process_Desc_APU():
    errorOccured(false),
    errorMessage(""),
    warningOccured(false),
    warningMessages(""),
    _graphUsed(0)
  {
  }

  virtual ~ACF_Process_Desc_APU()
  {
  }

  //functions from ACF
  virtual void Create() = 0;
  void Initialize(ACF_Graph& graph, const string& name);

  void SetInputChunkSize(const string& portName, int chunkWidth, int chunkHeight);

  //error checking
  bool ErrorOccured(){ return errorOccured; }
  string ErrorMessage(){ return errorMessage; }
  bool WarningOccured();
  //multiple warning messages can be present (but only one error message)
  string WarningMessages();

  //functions from ACF
  int Initialize();

  /////////////////////////////////////////////////////////////////////////
  /// Connect the data region described by "dataDescriptor" to graph
  /// port "ioName".
  ///
  /// \param[in] ioName			- Graph port identifier.
  /// \param[in] dataDescriptor - Description of contiguous data region.
  ///
  /// \return  0 if successful, non-zero if an an error occurred.
  /////////////////////////////////////////////////////////////////////////
  int ConnectIO(const string ioName, DataDescriptor& dataDescriptor);

  /////////////////////////////////////////////////////////////////////////
  /// Connect the region of interest (ROI) described by "lContigDataDesc",
  /// "lROI_XOffset", "lROI_YOffset", "lROI_Width", and "lROI_Height"
  /// to graph port "lPortIdentifier".
  ///
  /// \param[in] lPortIdentifier - Graph port identifier.
  /// \param[in] lContigDataDesc - Description of contiguous data region that 'contains' the ROI.
  /// \param[in] lROI_XOffset	 - The X offset of the top left corner of the ROI (relative to the top left
  /// corner of the region described by "lContigDataDesc").
  /// \param[in] lROI_YOffset	-  The Y offset of the top left corner of the ROI (relative to the top left
  /// corner of the region described by "lContigDataDesc").
  /// \param[in] lROI_Width		- The width of the ROI.
  /// \param[in] lROI_Height	- The height of the ROI.
  ///
  /// \return  0 if successful, non-zero if an an error occurred.
  /////////////////////////////////////////////////////////////////////////
  int ConnectIO_ROI(std::string lPortIdentifier,
	  DataDescriptor& lContigDataDesc,
	  int ROI_left,
	  int ROI_width,
	  int ROI_top,
	  int ROI_height);

  int ConnectIndirectInput(const string& ioName, DataDescriptor& dataDescriptor, DataDescriptor& offsetDescriptor);
  int FlagInputAsChunkBasedIndirect(const string& ioName);
  int Start();
  int Wait();

  int Start_Prepare();

  int Start_Run();

  int Wait_NoReset(){
	  return Wait();
  }

  int NoWait_Reset(){
	  return 0;
  }

  //get the execution plan of the graph
  string GetExecutionPlanDescription();

  //get the intermediate result (DataPlace) from inside a graph, returns null if nothing found
  //doesn't set an error!
  ACF_Graph::DataPlace* GetDataPlacePtr(const string& kernelInstanceName, const string& portName);
  ACF_Graph::DataPlace* GetDataPlacePtr(const string& graphPortName)
  {
    return GetDataPlacePtr("", graphPortName);
  }
};

}

#endif // _APU_ACF_PROCESS_DESC_APU_H_
