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
* \brief APU ACF graph simulation
* \author Igor Aleksandrowicz
* \version
* \date 30-January-2014
****************************************************************************/

#ifndef _APU_ACF_GRAPH_H_
#define _APU_ACF_GRAPH_H_

#include "acf_kernel.hpp"
#include "acf_data_descriptor.hpp"

#include <string>
#include <vector>
#include <map>
#include <unordered_map>
using std::string;
using std::vector;
using std::map;
using std::unordered_map;
using std::pair;

using namespace std;

namespace APEX2
{

class ACF_Graph
{
public:
	const char* m_graphName;
	const char* m_inputName;

  //structure for storing data at graph internal connections (each kernel input or output port has its DataPlace)
  struct DataPlace
  {
	  unsigned int tileWidth;
	  unsigned int tileHeight;
	  unsigned int tileCount;
	  bool isInitialized;
	  
	  //One padding is used for all directions, it's equal to the largest of the directional spatial data dependencies.
	  //Doesn't matter when using the stride, wouldn't be equal to real ACF padding anyways (ACF merges, multiple spatial dependencies in a graph to one)
	  int padding;
	  int paddingVert;
	  PortDataType portDataType;

	  unsigned int e0Width;
	  unsigned int e0Height;

	  unsigned int ekWidth;
	  unsigned int ekHeight;
	  
	  bool vectorData;
	  bool fixedData;
	  bool staticData;

	  int actualSize;
	  void* dataPtr;

	  bool connected;

    DataPlace() :
		tileWidth(0), tileHeight(0), padding(0), paddingVert(0), actualSize(0), dataPtr(0), portDataType(d08u), connected(false), e0Width(1), e0Height(1), ekWidth(1), ekHeight(1), tileCount(1), vectorData(true), fixedData(false), staticData(false), isInitialized(false)
    {}

    void RequestMemory(int requestedSize)
    {
      if (requestedSize != actualSize)
      {
		  if (dataPtr != NULL) {
			  delete[]((unsigned char*)dataPtr);
		  }

        dataPtr = (void*)(new unsigned char[requestedSize]);
        actualSize = requestedSize;
      }
    }

    ~DataPlace()
    {
      delete[]((unsigned char*)dataPtr);
    }
  };

private:
  string identifier;

  //map of kernel instances present in the graph
  typedef map<string, ACF_Kernel> KernelMapType;
  KernelMapType kernels;

  //structure used for storing graph input and output ports
  struct GraphPortInfo
  {
    int chunkWidth;
    int chunkHeight;
    __port port;
	bool isInitialized;

    GraphPortInfo():
		chunkWidth(1), chunkHeight(1), isInitialized(false)
    {}

    GraphPortInfo(const __port& port):
		port(port), chunkWidth(1), chunkHeight(1), isInitialized(false)
    {}
  };

  //map of graph ports
  typedef unordered_map<string, GraphPortInfo> GraphPortInfoType;
  unordered_map<string, GraphPortInfo> graphPorts;

  //structure for storing data at graph inputs and outputs
  struct GraphDataInfo
  {
    bool isIndirect;
    //data can be different than the original data, allocation have to be handled manually
	//data will be equal to original data when the data are spanning all CUs or different to data and allocated in the lib otherwise, then they have to be allocated and deallocated in the lib
    DataDescriptor* data;
    DataDescriptor* offsets;

    //original data will be different from *data when width < CU count * chunk width (because we need to add the non-active CU's data)
    //original data are pointers to host memory, should never be deleted inside the lib!
    DataDescriptor* originalData;
    DataDescriptor* originalOffsets;

    //number of active CUs implied by this graph input
    int activeCUCount;

    GraphDataInfo():
      data(0), offsets(0), originalData(0), originalOffsets(0), isIndirect(false), activeCUCount(0)
    {}

    ~GraphDataInfo()
    {}
  };

  //map of graph I/O data
  typedef unordered_map<string, GraphDataInfo> GraphDataType;
  GraphDataType graphData;

  //structure used for handling ports inside the graph
  struct PortDescriptor
  {
    //kernelInstanceName = "" means it's a graph port
    string kernelInstanceName;
    __port port;

    bool operator==(const PortDescriptor& other) const
    {
      return kernelInstanceName == other.kernelInstanceName && port.identifier.identifier == other.port.identifier.identifier;
    }

    bool IsGraphPort()
    {
      return kernelInstanceName == "";
    }
  };

  //port -> port connection
  struct Connection
  {
    PortDescriptor a;
    PortDescriptor b;

    Connection(PortDescriptor a, PortDescriptor b):a(a), b(b){}

    bool operator==(const Connection& other) const
    {
      return a == other.a && b == other.b;
    }
  };
  //all graph connections
  vector<Connection> connections;

  //data place database
  typedef pair<string, string> DataPlaceKey;
  typedef map<DataPlaceKey, DataPlace> DataPlaceMapType;
  DataPlaceMapType dataPlaceMap;

  //error handling data
  bool errorOccured;
  string errorMessage;
  bool warningOccured;
  string warningMessages;

  //one step of a graph execution plan
  struct PlanElement
  {
    //kernel instance, can be NULL - e.g. for the first propagation
    KernelMapType::iterator kernelInstance;
    //kernel data place indices
    vector<DataPlaceKey> kernelDataPlaces;
    //data place propagations which should occur after running the element
    vector<pair<DataPlaceKey, DataPlaceKey>> dataPlacePropagations;
  };

  //graph execution plan
  vector<PlanElement> kernelPlan;
public:
  ACF_Graph()
	  : errorOccured(false)
	  , errorMessage("")
    , warningOccured(false)
    , warningMessages("")
	  , m_graphName("")
	  , m_inputName("")
  {
  }

  ACF_Graph(const char* graphName, const char* inputName)
	  : errorOccured(false)
	  , errorMessage("")
    , warningOccured(false)
    , warningMessages("")
	  , m_graphName(graphName)
	  , m_inputName(inputName)
  {
  }

  virtual ~ACF_Graph();

  void SetIdentifier(const string& identifier)
  {
    if (errorOccured)
    {
      return;
    }
    this->identifier = identifier;
  }

  //from ACF
  void AddKernel(const string& kernelInstanceName, const string& kernelName);
  void AddInputPort(const string& inputPortName);
  void AddOutputPort(const string& outputPortName);
  //get a port descriptor that can be used in the Connect function
  PortDescriptor GraphPort(const string& graphPortName);
  PortDescriptor KernelPort(const string& kernelInstanceName, const string& kernelPortName);
  void Connect(PortDescriptor a, PortDescriptor b);

  //error handling
  bool ErrorOccured(){ return errorOccured; }
  string ErrorMessage(){ return errorMessage; }
  bool WarningOccured(){ return warningOccured; }
  string WarningMessages(){ return warningMessages; }

  virtual void Create() = 0;

private:
  string GetPlanDescription();

  //get the intermediate result from inside a graph, returns null if nothing found
  //doesn't set the error!
  DataPlace* GetDataPlacePtr(const string& kernelInstanceName, const string& portName);

  void SetGraphPortTileSize(const string& graphPortName, int tileWidth, int tileHeight);

  //creates the execution plan
  bool MakeSerialPlan();

  bool AutoIntializeChunkSizes(const string& graphPortName, DataDescriptor* data, int vectorWidth);

  //graph inputs setting functions
  void ConnectData(const string& graphPortName, DataDescriptor* data);
  void ConnectIndirectData(const string& graphPortName, DataDescriptor* data, DataDescriptor* offsets);
  void FlagIndirect(const string& graphPortName);

  //compute the chunks sizes startnig from graph inputs
  void ComputeChunkSizes();

  //prepare the connection data places
  void PrepareDataPlaces();
  //run the functions
  void Run();

  friend class ACF_Process_Desc_APU;

  //help function for handling active/inactive CUs by resizing data descriptors
  static void CopyChangeWidth(DataDescriptor& destination, DataDescriptor& source);
};

}

#endif // _APU_ACF_GRAPH_H_


