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
* \brief APU ACF graph simulation
* \author Igor Aleksandrowicz
* \version
* \date 31-January-2014
****************************************************************************/

#include "acf_graph.hpp"
#include <algorithm>
#include <unordered_set>
#include "apu_config.hpp"
#include "apu_extras.hpp"
#include "apu_cond.hpp"
using std::unordered_set;
using std::make_pair;
using std::max;

using namespace APEX2;
using namespace std;

/****************************************************************************
* functions
****************************************************************************/
void ACF_Graph::AddKernel(const string& kernelInstanceName, const string& kernelName)
{
  if (errorOccured)
  {
    return;
  }

  //validation checks
  
  if (kernels.count(kernelInstanceName) > 0)
  {
    errorOccured = true;
    errorMessage = "duplicated kernel instance: " + kernelName;
    return;
  }

  ACF_Kernel kernelPrototype = ACF_Kernel::GetPrototypeFromDatabase(kernelName);
  if (kernelPrototype.GetName() != kernelName)
  {
    errorOccured = true;
    errorMessage = "undefined kernel: " + kernelName;
    return;
  }

  if (kernelPrototype.ErrorOccured())
  {
    //propagate the kernel error
    errorOccured = true;
    errorMessage = "invalid kernel (errors in the kernel): " + kernelName + ", kernel error: " + kernelPrototype.ErrorMessage();
    return;
  }

  //add the kernel instance into the map
  kernels[kernelInstanceName] = kernelPrototype;

  //create DataPlaces for all the kernel instance ports
  for (int i = 0; i < kernelPrototype.GetPortCount(); ++i)
  {
    DataPlace dataPlace;
	
    //use the maximal padding needed
    int padding = kernelPrototype.GetPort(i).spatial_dep.dependencies[0];
    padding = max(padding, kernelPrototype.GetPort(i).spatial_dep.dependencies[1]);
    int paddingVert = max(0, kernelPrototype.GetPort(i).spatial_dep.dependencies[2]);
    paddingVert = max(paddingVert, kernelPrototype.GetPort(i).spatial_dep.dependencies[3]);
    dataPlace.padding = padding;
	dataPlace.paddingVert = paddingVert;

    dataPlace.portDataType = kernelPrototype.GetPort(i).e0_data_type.dataType;

    dataPlace.e0Width = kernelPrototype.GetPort(i).e0_size.size[0];
    dataPlace.e0Height = kernelPrototype.GetPort(i).e0_size.size[1];

    dataPlace.ekWidth = kernelPrototype.GetPort(i).ek_size.size[0];
    dataPlace.ekHeight = kernelPrototype.GetPort(i).ek_size.size[1];

    Attributes attributes = kernelPrototype.GetPort(i).attributes.attributes;
    dataPlace.vectorData = IsVectorAttribute(attributes);
    dataPlace.fixedData = IsFixedAttribute(attributes);
    dataPlace.staticData = IsStaticAttribute(attributes);

    //fixed ports' tile sizes are defined by ek
    if (IsFixedAttribute(kernelPrototype.GetPort(i).attributes.attributes))
    {
      dataPlace.tileWidth = dataPlace.ekWidth;
      dataPlace.tileHeight = dataPlace.ekHeight;
    }

    dataPlaceMap[make_pair(kernelInstanceName, kernelPrototype.GetPort(i).identifier.identifier)] = dataPlace;
  }
}

void ACF_Graph::AddInputPort(const string& inputPortName)
{
  if (errorOccured)
  {
    return;
  }

  //validation check
  if (graphPorts.count(inputPortName) > 0)
  {
    errorOccured = true;
    errorMessage = "duplicated input graph port: " + inputPortName;
    return;
  }

  //create new input graph port
  GraphPortInfo graphPortInfo(__port(__index(0), __identifier(inputPortName), __attributes(ACF_ATTR_VEC_IN), __spatial_dep(0, 0, 0, 0), __e0_data_type(d08u), __e0_size(0, 0), __ek_size(0, 0)));
  graphPorts[inputPortName] = graphPortInfo;

  //create the corresponding DataPlace
  dataPlaceMap[make_pair("", inputPortName)] = DataPlace();
}

void ACF_Graph::AddOutputPort(const string& outputPortName)
{
  if (errorOccured)
  {
    return;
  }

  //validation check
  if (graphPorts.count(outputPortName) > 0)
  {
    errorOccured = true;
    errorMessage = "duplicated output graph port: " + outputPortName;
    return;
  }

  //create new output graph port
  __port port(__index(0), __identifier(outputPortName), __attributes(ACF_ATTR_VEC_OUT), __spatial_dep(0, 0, 0, 0), __e0_data_type(d08u), __e0_size(0, 0), __ek_size(0, 0));
  graphPorts[outputPortName] = port;

  //create the corresponding DataPlace
  dataPlaceMap[make_pair("", outputPortName)] = DataPlace();
}

ACF_Graph::PortDescriptor ACF_Graph::GraphPort(const string& graphPortName)
{
  ACF_Graph::PortDescriptor portDescriptor;
  //kernel name is a an empty string for graph ports
  portDescriptor.kernelInstanceName = "";
  if (errorOccured)
  {
    return portDescriptor;
  }
  
  //return the info from the database or report an error if not found
  unordered_map<string, GraphPortInfo>::iterator it = graphPorts.find(graphPortName);
  if (it != graphPorts.end())
  {
    portDescriptor.port = graphPorts[graphPortName].port;
  }
  else
  {
    errorOccured = true;
    errorMessage = "undefined graph port: " + graphPortName;
    portDescriptor.port.identifier.identifier = "";
  }
  return portDescriptor;
}

ACF_Graph::PortDescriptor ACF_Graph::KernelPort(const string& kernelInstanceName, const string& kernelPortName)
{
  ACF_Graph::PortDescriptor portDescriptor;
  portDescriptor.kernelInstanceName = kernelInstanceName;
  if (errorOccured)
  {
    return portDescriptor;
  }
  
  //find the kernel
  KernelMapType::iterator it = kernels.find(kernelInstanceName);
  if (it != kernels.end())
  {
    bool portFound = false;
    //search the kernel's ports
    for (int i = 0; i < MAX_KN_PORTS; ++i)
    {
      if (it->second.GetPort(i).identifier.identifier == kernelPortName)
      {
        portDescriptor.port = it->second.GetPort(i);
        portFound = true;
        break;
      }
    }
    if (!portFound)
    {
      errorOccured = true;
      errorMessage = "undefined port: " + kernelPortName + " in the kernel instance: " + kernelInstanceName;
    }
  }
  else
  {
    errorOccured = true;
    errorMessage = "undefined kernel instance: " + kernelInstanceName;
  }
  return portDescriptor;
}

void ACF_Graph::Connect(ACF_Graph::PortDescriptor a, ACF_Graph::PortDescriptor b)
{
  if (errorOccured)
  {
    return;
  }

  //validate the connection itself
  Connection connection = Connection(a, b);
  if (connection.a.kernelInstanceName == connection.b.kernelInstanceName && !connection.a.kernelInstanceName.empty())
  {
    errorOccured = true;
    errorMessage = "cycle on the kernel instance: " + connection.a.kernelInstanceName;
    return;
  }

  if (connection.a.kernelInstanceName.empty() && connection.b.kernelInstanceName.empty())
  {
    errorOccured = true;
    errorMessage = "can't connect 2 graph ports: " + connection.a.port.identifier.identifier + " -> " + connection.b.port.identifier.identifier;
    return;
  }

  //validate the connection against other connections
  for (unsigned int i = 0; i < connections.size(); ++i)
  {
    string separatorA = connection.a.kernelInstanceName == "" ? "" : ".";
    string separatorB = connection.b.kernelInstanceName == "" ? "" : ".";

    if (connections[i] == connection)
    {
      errorOccured = true;
      errorMessage = "duplicated connection: " +
        connection.a.kernelInstanceName + separatorA + connection.a.port.identifier.identifier +
        " -> " +
        connection.b.kernelInstanceName + separatorB + connection.b.port.identifier.identifier;
      return;
    }

    if (connections[i].b == connection.b)
    {
      errorOccured = true;
      errorMessage = "two connections to port: " +
        connection.b.kernelInstanceName + separatorB + connection.b.port.identifier.identifier;
      return;
    }
  }

  DataPlaceKey dpAK = make_pair(connection.a.kernelInstanceName, connection.a.port.identifier.identifier);
  DataPlaceKey dpBK = make_pair(connection.b.kernelInstanceName, connection.b.port.identifier.identifier);
  DataPlace& dpA = dataPlaceMap[dpAK];
  DataPlace& dpB = dataPlaceMap[dpBK];
  dpA.connected = true;
  dpB.connected = true;
  //prepare the graph port data places here, kernel port data places are defined by the kernels' metadata
  if (connection.a.IsGraphPort())
  {
    dpA.vectorData = IsVectorAttribute(connection.b.port.attributes.attributes);
    dpA.staticData = IsStaticAttribute(connection.b.port.attributes.attributes);
    dpA.fixedData = IsFixedAttribute(connection.b.port.attributes.attributes);
    dpA.portDataType = connection.b.port.e0_data_type.dataType;
    dpA.e0Width = connection.b.port.e0_size.size[0];
    dpA.e0Height = connection.b.port.e0_size.size[1];
    dpA.ekWidth = connection.b.port.ek_size.size[0];
    dpA.ekHeight = connection.b.port.ek_size.size[1];
    GraphPortInfo& graphPort = graphPorts[connection.a.port.identifier.identifier];
    graphPort.port.attributes = ReturnAttribute(true, dpA.vectorData, dpA.staticData, dpA.fixedData);
	graphPort.port.e0_data_type.dataType = connection.b.port.e0_data_type.dataType;
  }
  if (connection.b.IsGraphPort())
  {
    dpB.vectorData = IsVectorAttribute(connection.a.port.attributes.attributes);
    dpB.staticData = IsStaticAttribute(connection.a.port.attributes.attributes);
    dpB.fixedData = IsFixedAttribute(connection.a.port.attributes.attributes);
    dpB.portDataType = connection.a.port.e0_data_type.dataType;
    dpB.e0Width = connection.a.port.e0_size.size[0];
    dpB.e0Height = connection.a.port.e0_size.size[1];
    dpB.ekWidth = connection.a.port.ek_size.size[0];
    dpB.ekHeight = connection.a.port.ek_size.size[1];
    GraphPortInfo& graphPort = graphPorts[connection.b.port.identifier.identifier];
    graphPort.port.attributes = ReturnAttribute(false, dpB.vectorData, dpB.staticData, dpB.fixedData);
	graphPort.port.e0_data_type.dataType = connection.a.port.e0_data_type.dataType;
  }
  //add the connection to the database
  connections.push_back(connection);
}

void ACF_Graph::SetGraphPortTileSize(const string& graphPortName, int tileWidth, int tileHeight)
{
  if (errorOccured)
  {
    return;
  }

  //validate
  if (graphPorts.count(graphPortName) < 1)
  {
    errorOccured = true;
    errorMessage = "cannot set the chunk size for an undefined graph port: " + graphPortName;
    return;
  }

  graphPorts[graphPortName].isInitialized = true;

  if (!IsInputAttribute(graphPorts[graphPortName].port.attributes.attributes))
  {
    errorOccured = true;
    errorMessage = "cannot set the chunk size for a non-input graph port: " + graphPortName;
    return;
  }

  if (tileWidth < 1 || tileHeight < 1)
  {
    errorOccured = true;
    errorMessage = "invalid input chunk size: " + graphPortName;
    return;
  }

  //set the tile widths
  graphPorts[graphPortName].chunkWidth = tileWidth;
  graphPorts[graphPortName].chunkHeight = tileHeight;
}

bool ACF_Graph::MakeSerialPlan()
{
  if (errorOccured)
  {
    return false;
  }

  //check whether there are any graph inputs and outputs
  {
    int inputGraphPortCount = 0;
    int outputGraphPortCount = 0;
    for (GraphPortInfoType::iterator it = graphPorts.begin(); it != graphPorts.end(); ++it)
    {
      Attributes attributes = it->second.port.attributes.attributes;
      if (IsOutputAttribute(attributes))
      {
        ++outputGraphPortCount;
      }
      else if (IsInputAttribute(attributes))
      {
        ++inputGraphPortCount;
      }
    }
    if (inputGraphPortCount == 0)
    {
      errorOccured = true;
      errorMessage = "no graph input";
      return false;
    }
    if (outputGraphPortCount == 0)
    {
      errorOccured = true;
      errorMessage = "no graph output";
      return false;
    }
  }

  //topological sort http://en.wikipedia.org/wiki/Topological_sorting
  //not using sets of objects because of the const/updating issues
  struct GraphNode
  {
    int id;
    KernelMapType::iterator kernelInstance;
	//set of indices of predecessor nodes
    unordered_set<int> prev;
	//set of indices of successor nodes
    unordered_set<int> next;
  };

  //prepare the nodes
  vector<GraphNode> allGraphNodes;
  //kernel name to node id translation
  unordered_map<string, int> graphNodeMap;
  int index = 0;
  for (KernelMapType::iterator it = kernels.begin(); it != kernels.end(); ++it)
  {
    GraphNode n;
    n.id = index;
    n.kernelInstance = it;
    allGraphNodes.push_back(n);
    graphNodeMap[it->first] = index;
    ++index;
  }
  
  //prepare the edges, i.e. fill the prev and next node sets
  for (unsigned int ki = 0; ki < allGraphNodes.size(); ++ki)
  {
    KernelMapType::iterator kernelIt = allGraphNodes[ki].kernelInstance;
    for (unsigned int ci = 0; ci < connections.size(); ++ci)
    {
      if (connections[ci].a.kernelInstanceName == kernelIt->first)
      {
        string connectKernelName = connections[ci].b.kernelInstanceName;
        if (!connectKernelName.empty())
        {
          int connectGraphNodeID = graphNodeMap[connectKernelName];
          allGraphNodes[ki].next.insert(connectGraphNodeID);
        }
      }
      if (connections[ci].b.kernelInstanceName == kernelIt->first)
      {
        string connectKernelName = connections[ci].a.kernelInstanceName;
        if (!connectKernelName.empty())
        {
          int connectGraphNodeID = graphNodeMap[connectKernelName];
          allGraphNodes[ki].prev.insert(connectGraphNodeID);
        }
      }
    }
  }

  //first plan element - propagate graph inputs
  PlanElement firstPlanElement;
  //no kernel for the first element
  firstPlanElement.kernelInstance = kernels.end();
  for (unsigned int i = 0; i < connections.size(); ++i)
  {
    //for each connection with empty input kernel name (i.e. connections from graph ports)
    if (connections[i].a.kernelInstanceName == "")
    {
      DataPlaceKey inputGraphDataPlaceKey = make_pair("", connections[i].a.port.identifier.identifier);
      DataPlaceKey inputKernelDataPlaceKey = make_pair(connections[i].b.kernelInstanceName, connections[i].b.port.identifier.identifier);
	  //propagate the graph input to the kernel input
      firstPlanElement.dataPlacePropagations.push_back(make_pair(inputGraphDataPlaceKey, inputKernelDataPlaceKey));
    }
  }
  //don't use the first element if there are no graph inputs
  if (!firstPlanElement.dataPlacePropagations.empty())
  {
    kernelPlan.push_back(firstPlanElement);
  }

  //core topological sort
  unordered_set<int> remainingNodes;
  unordered_set<int> processedNodes;

  //add the nodes into pending nodes
  for (unsigned int i = 0; i < allGraphNodes.size(); ++i)
  {
    remainingNodes.insert(int(i));
  }

  while (!remainingNodes.empty())
  {
    bool nextNodeFound = false;
    //for the remaining kernel instances
    for (unordered_set<int>::iterator it = remainingNodes.begin(); it != remainingNodes.end(); ++it)
    {
      bool process = true;
      //check if there are some unprocessed predecessors
      for (unordered_set<int>::iterator it2 = allGraphNodes[*it].prev.begin(); it2 != allGraphNodes[*it].prev.end(); ++it2)
      {
        if (remainingNodes.count(*it2))
        {
          process = false;
          break;
        }
      }

      //there aren't, we found a node which we can add to our plan
      if (process)
      {
        processedNodes.insert(*it);
		
        //initialize the plan element
        PlanElement planElement;
        planElement.kernelInstance = allGraphNodes[*it].kernelInstance;
        string kernelInstanceName = planElement.kernelInstance->first;
        //handle dataPlace transforms
        for (int i = 0; i < planElement.kernelInstance->second.GetPortCount(); ++i)
        {
          string portIdentifier = planElement.kernelInstance->second.GetPort(i).identifier.identifier;
          DataPlaceKey dataPlaceKey = make_pair(kernelInstanceName, portIdentifier);
          //add the data place corresponding to the port to the plan
          planElement.kernelDataPlaces.push_back(dataPlaceKey);
          //find the DataPlace-DataPlace propagations corresponding to the kernel output connections
          for (unsigned int i = 0; i < connections.size(); ++i)
          {
            if (connections[i].a.kernelInstanceName == kernelInstanceName && connections[i].a.port.identifier.identifier == portIdentifier)
            {
              DataPlaceKey secondKey = make_pair(connections[i].b.kernelInstanceName, connections[i].b.port.identifier.identifier);
              //add the propagation into the plan element
              planElement.dataPlacePropagations.push_back(make_pair(dataPlaceKey, secondKey));
            }
          }
        }
        kernelPlan.push_back(planElement);
        remainingNodes.erase(it);
        nextNodeFound = true;
        break;
      }
    }
	
    //we couldn't use any of the remaining nodes, therefore the graph contains a cycle
    if (!nextNodeFound)
    {
      errorOccured = true;
      errorMessage = "cycles found in the graph: " + identifier;
      kernelPlan.clear();
      return false;
    }
  }

  return true;
}

string ACF_Graph::GetPlanDescription()
{
  if (errorOccured)
  {
    return "no plan due to errors\n";
  }

  //create a text description of the plan
  string description;
  for (unsigned int i = 0; i < kernelPlan.size(); ++i)
  {
    KernelMapType::iterator kernelInstance = kernelPlan[i].kernelInstance;
    if (kernelInstance != kernels.end())
    {
      description.append("run the kernel: ");
      description.append(kernelPlan[i].kernelInstance->first);
      description.append("\n");
    }
    for (unsigned int j = 0; j < kernelPlan[i].dataPlacePropagations.size(); ++j)
    {
      description.append("propagate: ");
      string firstKernelName = kernelPlan[i].dataPlacePropagations[j].first.first;
      //don't include kernel name and . when dealing with graph port
      if (firstKernelName != "")
      {
        description.append(firstKernelName);
        description.append(".");
      }
      description.append(kernelPlan[i].dataPlacePropagations[j].first.second);

      description.append(" -> ");

      string secondKernelName = kernelPlan[i].dataPlacePropagations[j].second.first;
      //don't include kernel name and . when dealing with a graph port
      if (secondKernelName != "")
      {
        description.append(secondKernelName);
        description.append(".");
      }
      description.append(kernelPlan[i].dataPlacePropagations[j].second.second);
      description.append("\n");
    }
  }

  return description;
}

bool ACF_Graph::AutoIntializeChunkSizes(const string& graphPortName, DataDescriptor* data, int vectorWidth) {
	bool isError = false;
	GraphPortInfo& gpi = graphPorts[graphPortName];
		
	int   dw = data->GetWidth(), dh = data->GetHeight()
		, dEk_x = data->GetElementDimX(), dEk_y = data->GetElementDimY();
	int totWidth = dw*dEk_x, totHeight = dh*dEk_y;
	int chunkWidth = ((totWidth / vectorWidth + 1) >> 1)<< 1;
	int chunkHeight = totHeight % 2 == 0 ? 2 : (totHeight % 3 == 0 ? 3 : (totHeight % 5 == 0 ? 5 : 1));
	
	gpi.chunkWidth= chunkWidth;
	gpi.chunkHeight= chunkHeight;
	gpi.isInitialized = true;

	ComputeChunkSizes(); // TBD: might be inefficient here, because it is called for each not initialized graph port. 

	return isError;
}

void ACF_Graph::ConnectData(const string& graphPortName, DataDescriptor* data)
{
  if (errorOccured)
  {
    return;
  }

  if (graphPorts.count(graphPortName) < 1)
  {
    errorOccured = true;
    errorMessage = "undefined graph port: " + graphPortName;
  }
  else
  {
	  Attributes attr = graphPorts.find(graphPortName)->second.port.attributes.attributes;

    GraphDataInfo& info = graphData[graphPortName];
    //delete the intermediate data if they were different than the original data
    if (info.data != info.originalData)
    {
      delete info.data;
      info.data = 0;
    }

    //get the corresponding DataPlace
    DataPlace& dp = dataPlaceMap[make_pair("", graphPortName)];
    int vectorWidth = dp.vectorData ? VSIZE : 1;
	if (IsInputAttribute(attr) && !dp.isInitialized && vectorWidth > 1) {
		AutoIntializeChunkSizes(graphPortName, data, vectorWidth);
	}
    unsigned int dpTileSpan = dp.tileWidth * dp.e0Width;
    unsigned int dpSliceHorSpan = dpTileSpan * vectorWidth;
    unsigned int dpSliceVerSpan = dp.tileHeight * dp.e0Height;
    unsigned int ddHorSpan = data->GetWidth() * data->GetElementDimX();
    unsigned int ddVerSpan = data->GetHeight() * data->GetElementDimY();
	unsigned int dpChunkWidth = dp.tileWidth * dp.e0Width * DataDescriptor::ReturnElementSize(data->GetElementDataType());
	const int allowedChunkWidth[32] = { 2,	4,	 6,	 8, 
										10, 12, 14, 16, 
										18, 20, 22, 24, 
										26, 28, 30, 32, 
										36, 40, 44, 48, 
										52, 56, 60, 64, 
										72, 80, 88, 96, 
										104, 112, 120, 128};
	if (dpChunkWidth % 2 != 0 && !dp.fixedData){
		errorOccured = true;
		char tmp[400];
		sprintf_s(tmp, "data chunk width %d is inappropriate for port %s. It has to be a multiple of 2", dpChunkWidth, graphPortName.c_str());
		//errorMessage = "input data type doesn't match the graph port data type: " + graphPortName;
		errorMessage = std::string(tmp);
		return;
	}
	
	if (dpChunkWidth > 128 && !dp.fixedData) {
		errorOccured = true;
		char tmp[400];
		sprintf_s(tmp, "data chunk width %d is too large maximum is %d for port %s ", dpChunkWidth, 128, graphPortName.c_str());
		//errorMessage = "input data type doesn't match the graph port data type: " + graphPortName;
		errorMessage = std::string(tmp);
		return;
	}

	bool allowedChunkWidthFound = false;
	for (int chwIdx = 0; chwIdx < 32; ++chwIdx){
		if (dpChunkWidth == allowedChunkWidth[chwIdx]) {
			allowedChunkWidthFound = true;
			break;
		}
	}

	if (allowedChunkWidthFound == false && !dp.fixedData) {
		errorOccured = true;
		char tmp[400];
		sprintf_s(tmp, "data chunk width is  %d inappropriateis for port %s. \n \
			Allowed chunk width are [2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 28, 30, 32, 36, 40, 44, 48, 52, 56, 60, 64, 72, 80, 88, 96, 104, 112, 120, 128]"
			, dpChunkWidth, graphPortName.c_str());
		//errorMessage = "input data type doesn't match the graph port data type: " + graphPortName;
		errorMessage = std::string(tmp);
		return;
	}

	if (dp.portDataType != data->GetElementDataType())
	{
		errorOccured = true;
		char tmp[400];
		sprintf_s(tmp, "input data type %d doesn't match the graph port data type %d: %s ", data->GetElementDataType(), dp.portDataType, graphPortName.c_str());
		//errorMessage = "input data type doesn't match the graph port data type: " + graphPortName;
		errorMessage = std::string(tmp);
		return;
	}

    //check width for scalar data
    if (!dp.vectorData && data->GetWidth() != dp.tileWidth)
    {
	char tmp[400];
	 errorOccured = true;
	  sprintf_s(tmp, "scalar input data width %d doesn't match the chunk width %d: %s", data->GetWidth(), dp.tileWidth, graphPortName.c_str());
	  errorMessage = std::string(tmp);
      return;
    }
    //check width compatibility for vector data
    else if (dp.vectorData && data->GetWidth() % dp.tileWidth != 0)
    {
      errorOccured = true;
	  char tmp[400];
	  sprintf_s(tmp, "vector input data width %d  is not divisible by chunk width %d : %s", data->GetWidth(), dp.tileWidth, graphPortName.c_str());
	  errorMessage = std::string(tmp);
      return;
    }
    //check whether there is enough CUs to handle the width
    else
    {
	 if (dp.vectorData) {
	 //info.activeCUCount = data->GetWidth() * data->GetElementDimX()/ dpTileSpan;
	  info.activeCUCount = data->GetWidth() / dp.tileWidth;
      if (info.activeCUCount > APU_VSIZE)
      {
        errorOccured = true;
		char tmp[400];
		sprintf_s(tmp, "vector input data width %d (== dataWidth/tileWidth, i.e.%d/%d ) is too large, max is %d: %s", info.activeCUCount, data->GetWidth(), dp.tileWidth, APU_VSIZE, graphPortName.c_str());
		errorMessage = std::string(tmp);
        return;
      }
    }
    }

    //direct/indirect mismatch
    if (info.isIndirect)
    {
      errorOccured = true;
      errorMessage = "cannot connect direct data to an indirect output: " + graphPortName;
    }
    //element data type mismatch
    else if (DataDescriptor::ReturnElementSize(data->GetElementDataType()) != PortDataTypeSize(dp.portDataType))
    {
      errorOccured = true;
	  char tmp[400];
	  sprintf_s(tmp, "incompatible data element type size (%d) / kernel element data type size () : %s ", DataDescriptor::ReturnElementSize(data->GetElementDataType()), PortDataTypeSize(dp.portDataType), graphPortName.c_str());
	  errorMessage = std::string(tmp);
    }
    //wrong element data size
    else if (data->GetElementDimX() != dp.e0Width) 
    {
      errorOccured = true;
	  char tmp[400];
	  sprintf_s(tmp, "data element size x %d doesn't match kernel e0 width %d for port: %s ", data->GetElementDimX(), dp.e0Width, graphPortName.c_str());
	  errorMessage = std::string(tmp);
	}
	//wrong element data size
	else if (data->GetElementDimY() != dp.e0Height)
	{
		errorOccured = true;
		char tmp[400];
		sprintf_s(tmp, "data element size y %d doesn't match kernel e0 height for port: %s ", data->GetElementDimY(), dp.e0Height, graphPortName.c_str());
		errorMessage = std::string(tmp);
	}
    //chunk height compatibility check
    else if ((!dp.staticData && ((ddVerSpan % dpSliceVerSpan) != 0)) )
    {
      errorOccured = true;
	  char tmp[400];
	  sprintf_s(tmp, "the data height %d is not divisible by the chunk height %d for port: %s", ddVerSpan, dpSliceVerSpan, graphPortName.c_str());
	  errorMessage = std::string(tmp);
    }
	//chunk height compatibility check
	else if ((dp.staticData && (dpSliceVerSpan > ddVerSpan)))
	{
		errorOccured = true;
		char tmp[400];
		sprintf_s(tmp, "the data height %d is lower than the chunk height %d for port: %s ", ddVerSpan, dpSliceVerSpan, graphPortName.c_str());
		errorMessage = std::string(tmp);
	}
    //everything ok
    else
    {
      info.originalData = data;
      //create temporary data which span all CUs if the width implies some CUs shouldn't be active
	  if (dp.vectorData && (dpSliceHorSpan != ddHorSpan || data->GetDimensions() > 1))
      { //if data has depth > 1 (i.e. is a volume), then flatten the volume to a big image. CAUTION: this does not work for very deep volumes, due to memory shortage!
        info.data = new DataDescriptor(dp.tileWidth* APU_VSIZE, data->GetHeight()*data->GetDimensions(), data->GetElementDataType(), data->GetElementDimX(), data->GetElementDimY());
        info.data->SetFreeOnExit(true);
      }
      else
      {
        info.data = data;
      }
    }
  }

}

//TODO: more checks for scalar data? vector data only?
void ACF_Graph::ConnectIndirectData(const string& graphPortName, DataDescriptor* data, DataDescriptor* offsets)
{
  if (errorOccured)
  {
    return;
  }

  if (graphPorts.count(graphPortName) < 1)
  {
    errorOccured = true;
    errorMessage = "undefined graph port: " + graphPortName;
  }
  else
  {
    GraphDataInfo& info = graphData[graphPortName];
    //delete the intermediate offsets if they were different than the original offsets
    if (info.offsets != info.originalOffsets)
    {
      delete info.offsets;
      info.offsets = 0;
    }

    info.activeCUCount = (int)offsets->GetWidth();
    //get the corresponding DataPlace
    DataPlace& dp = dataPlaceMap[make_pair("", graphPortName)];
    int vectorWidth = dp.vectorData ? APU_VSIZE : 1;
    //direct//indirect mismatch
    if (!info.isIndirect)
    {
      errorOccured = true;
	  char tmp[400];
	  sprintf_s(tmp,"graph input is not indirect: %s", graphPortName);
	  errorMessage = std::string(tmp);
    }
    //element data type mismatch
    else if (DataDescriptor::ReturnElementSize(data->GetElementDataType()) != PortDataTypeSize(dp.portDataType))
    {
      errorOccured = true;
	  char tmp[400];
	  sprintf_s(tmp, "incompatible data type size (%d)/kernel element data type size(%d): %s", DataDescriptor::ReturnElementSize(data->GetElementDataType()), PortDataTypeSize(dp.portDataType), graphPortName.c_str());
	  errorMessage = std::string(tmp);
    }
    //wrong element data size
    else if (data->GetElementDimX() != dp.e0Width)
    {
      errorOccured = true;
	  char tmp[400];
	  sprintf_s(tmp, "data element size x %d doesn't match kernel e0 width %d:  %s", data->GetElementDimX(), dp.e0Width, graphPortName.c_str());
	  errorMessage = std::string(tmp);
    }
	//wrong element data size
	else if (data->GetElementDimY() != dp.e0Height)
	{
		errorOccured = true;
		char tmp[400];
		sprintf_s(tmp, "data element size y %d doesn't match kernel e0 height %d:  %s", data->GetElementDimY(), dp.e0Height, graphPortName.c_str());
		errorMessage = std::string(tmp);
	}
    //offsets have to be 32-bit wide
    else if (offsets->GetElementDataType() != DATATYPE_32S && offsets->GetElementDataType() != DATATYPE_32U)
    {
      errorOccured = true;
	  char tmp[400];
	  sprintf_s(tmp, "only 32-bit offsets supported: %s", graphPortName.c_str());
	  errorMessage = std::string(tmp);
    }
    //offsets have to have 1x1 elements
    else if (offsets->GetElementDimX() != 1 || offsets->GetElementDimY() != 1)
    {
      errorOccured = true;
	  char tmp[400];
	  sprintf_s(tmp, "only 1x1 element offsets supported: %s", graphPortName.c_str());
	  errorMessage = std::string(tmp);
    }
    //only non-static vector data are supported for indirect inputs
    else if (dp.staticData || !dp.vectorData)
    {
      errorOccured = true;
	  char tmp[400];
	  sprintf_s(tmp, "indirect data not supported for scalar or static data: %s", graphPortName.c_str());
	  errorMessage = std::string(tmp);
    }
    //check whether there is enough CUs to handle the width
    else if ((int)offsets->GetWidth() > vectorWidth)
    {
      errorOccured = true;
	  char tmp[400];
	  sprintf_s(tmp, "offset data width %d too high, max is : %s", offsets->GetWidth(), vectorWidth, graphPortName.c_str());
	  errorMessage = std::string(tmp);
    }
    //everything ok
    else
    {
      info.data = data;
      info.originalData = data;
      info.originalOffsets = offsets;

      //create temporary data which span all CUs if the width implies some CUs shouldn't be active
	  if ((int)offsets->GetWidth() < vectorWidth || offsets->GetDimensions() > 1)
      {
        info.offsets = new DataDescriptor(vectorWidth, offsets->GetHeight()*offsets->GetDimensions(), offsets->GetElementDataType(), 1, 1);
        info.offsets->SetFreeOnExit(true);
      }
      else
      {
        info.offsets = offsets;
      }
    }
  }
}

void ACF_Graph::FlagIndirect(const string& graphPortName)
{
  if (errorOccured)
  {
    return;
  }

  //only already defined input ports can be flagged as indirect
  
  if (graphPorts.count(graphPortName) < 1)
  {
    errorOccured = true;
    errorMessage = "undefined graph port: " + graphPortName;
  }
  else
  {
    if (!IsInputAttribute(graphPorts[graphPortName].port.attributes.attributes))
    {
      errorOccured = true;
      errorMessage = "non-input port cannot be flagged as indirect: " + graphPortName;
    }
    else
    {
      graphData[graphPortName].isIndirect = true;
    }
  }
}

//greatest common divisor
static int gcd(int a, int b)
{
    for (;;)
    {
        if (a == 0) return b;
        b %= a;
        if (b == 0) return a;
        a %= b;
    }
    return 1;
}

//least common multiple
static int lcm(int a, int b)
{
    int temp = gcd(a, b);

    return temp ? (a / temp * b) : 0;
}


void ACF_Graph::ComputeChunkSizes()
{
  if (errorOccured)
  {
    return;
  }

  //propagate the input graph port info to corresponding DataPlaces
  for (GraphPortInfoType::iterator it = graphPorts.begin(); it != graphPorts.end(); ++it)
  {
    Attributes attributes = it->second.port.attributes.attributes;
    //TODO: attributes as bit masks?
    if (IsInputAttribute(attributes))
    {
      DataPlace& dp = dataPlaceMap[make_pair("", it->first)];
      //fixed chunk sizes are defined by ek
      if (!IsFixedAttribute(attributes))
      {
        dp.tileWidth = it->second.chunkWidth;
        dp.tileHeight = it->second.chunkHeight;
		dp.isInitialized = it->second.isInitialized;
      }
      else
      {
        dp.tileWidth = dp.ekWidth;
        dp.tileHeight = dp.ekHeight;
      }
    }
  }

  //propagate chunk size info using the execution plan
  for (unsigned int i = 0; i < kernelPlan.size(); ++i)
  {
    //if plan element contains kernel execution
    if (kernelPlan[i].kernelInstance != kernels.end())
    {
      ACF_Kernel& kp = kernelPlan[i].kernelInstance->second;
      string instanceName = kernelPlan[i].kernelInstance->first;

      unsigned int tileWidth = 1;
	  unsigned int tileHeight = 1;

      //input k-element sizes to use as numerators and denominators
      int kWidthNum = 1;
      int kWidthDenom = 1;
      int kHeightNum = 1;
      int kHeightDenom = 1;

      for (int j = 0; j < kp.GetPortCount(); ++j)
      {
        Attributes attributes = kp.GetPort(j).attributes.attributes;
        if (IsInputAttribute(attributes) && !IsFixedAttribute(attributes))
        {
          DataPlace& dp = dataPlaceMap[make_pair(instanceName, kp.GetPort(j).identifier.identifier)];
          //set the default tile size for the kernel to the maximum of all input tile sizes
          tileWidth = max(tileWidth, dp.tileWidth);
          tileHeight = max(tileHeight, dp.tileHeight);
          //set the k-element size numerators to the least common multiples of the output ek sizes
          kWidthNum = lcm(kWidthNum, dp.ekWidth);
          kHeightNum = lcm(kHeightNum, dp.ekHeight);
        }
        else if (IsOutputAttribute(attributes) && !IsFixedAttribute(attributes))
        {
          DataPlace& dp = dataPlaceMap[make_pair(instanceName, kp.GetPort(j).identifier.identifier)];
          //set the k-element size denominators to the least common multiples of the output ek sizes
          kWidthDenom = lcm(kWidthDenom, dp.ekWidth);
          kHeightDenom = lcm(kHeightDenom, dp.ekHeight);
        }
      }

      for (int j = 0; j < kp.GetPortCount(); ++j)
      {
        //try to divide the kernel output kernels' tile sizes (width + height) by (kNum/kDenom)
        if (IsOutputAttribute(kp.GetPort(j).attributes.attributes) && !IsFixedAttribute(kp.GetPort(j).attributes.attributes))
        {
          DataPlace& dp = dataPlaceMap[make_pair(instanceName, kp.GetPort(j).identifier.identifier)];
          int multTileWidth = tileWidth * kWidthDenom;
          int multTileHeight = tileHeight * kHeightDenom;
          if ((multTileWidth % kWidthNum != 0) || (multTileHeight % kHeightDenom != 0))
          {
			  char tmp[400];
			  sprintf_s(tmp, "input k size (%d,%d) not divisible with output element k size (%d,%d): %s ", multTileWidth, multTileHeight, kWidthNum, kHeightDenom, kp.GetName().c_str());
			  errorMessage = std::string(tmp);
            errorOccured = true;
            return;
          }
          dp.tileWidth = multTileWidth / kWidthNum;
          dp.tileHeight = multTileHeight / kHeightNum;
        }
      }
    }

    //use the planned propagation to copy the tile sizes into connected kernels' inputs
    for (unsigned int j = 0; j < kernelPlan[i].dataPlacePropagations.size(); ++j)
    {
      string a = kernelPlan[i].dataPlacePropagations[j].first.first + "." + kernelPlan[i].dataPlacePropagations[j].first.second;
      string b = kernelPlan[i].dataPlacePropagations[j].second.first + "." + kernelPlan[i].dataPlacePropagations[j].second.second;

      DataPlace& dpA = dataPlaceMap[kernelPlan[i].dataPlacePropagations[j].first];
      DataPlace& dpB = dataPlaceMap[kernelPlan[i].dataPlacePropagations[j].second];

      dpB.tileWidth = dpA.tileWidth;
      dpB.tileHeight = dpA.tileHeight;
    }
  }

  //propagate the tile size to output graph ports
  for (GraphPortInfoType::iterator it = graphPorts.begin(); it != graphPorts.end(); ++it)
  {
    Attributes attributes = it->second.port.attributes.attributes;
    if (IsOutputAttribute(attributes))
    {
      DataPlace& dp = dataPlaceMap[make_pair("", it->first)];
      it->second.chunkWidth = dp.tileWidth;
      it->second.chunkHeight = dp.tileHeight;
    }
  }
}

void ACF_Graph::PrepareDataPlaces()
{
  if (errorOccured)
  {
    return;
  }

  //check whether all input ports are connected to data
  if (graphData.size() != graphPorts.size())
  {
    for (GraphPortInfoType::iterator gpIt = graphPorts.begin(); gpIt != graphPorts.end(); ++gpIt)
    {
      if (graphData.count(gpIt->first) < 1)
      {
        errorOccured = true;
        errorMessage = "data not connected to the graph port: " + gpIt->first;
        return;
      }
    }
  }

  //compute the number of iterations (data tiles) for graph input data
  unsigned int iterations = 0;

  for (GraphDataType::iterator it = graphData.begin(); it != graphData.end(); ++it)
  {
    DataDescriptor* pdd = it->second.data;
    bool isIndirect = it->second.isIndirect;
    DataDescriptor* offsets = it->second.offsets;

    GraphPortInfo& gpi = graphPorts[it->first];
    Attributes attributes = gpi.port.attributes.attributes;
    //fixed data shouldn't be checked
    if (IsFixedAttribute(attributes) && !isIndirect)
    {
      continue;
    }

	unsigned int width = isIndirect ? offsets->GetWidth() * gpi.chunkWidth : pdd->GetWidth();
    unsigned int height = isIndirect ? offsets->GetHeight() * gpi.chunkHeight : pdd->GetHeight();
    //connected data/port inconsistencies
    if ((width % gpi.chunkWidth != 0) || (height % gpi.chunkHeight != 0))
    {
        errorOccured = true;
		char tmp[400];
		sprintf_s(tmp, "graph port data size (%d,%d) not divisible by the port chunk size (%d,%d): %s ", width, height, gpi.chunkWidth, gpi.chunkHeight, it->first.c_str());
		errorMessage = std::string(tmp);
        return;
    }
    //number of iterations implied by the port
    unsigned int portIterations = height / gpi.chunkHeight;
    //iteration count should match across the inputs, static data should be ignored for this check
    if ((portIterations != iterations) && (iterations != 0) && (!IsStaticAttribute(attributes)))
    {
        errorOccured = true;
		char tmp[400];
		sprintf_s(tmp, "incompatible input graph port configurations (portIterations = dataHeight/chunkHeight, i.e. %d = %d/%d) ==> leads to slice count conflict: %d iterations: %s", portIterations, height, gpi.chunkHeight, iterations, it->first.c_str());
		errorMessage = std::string(tmp);
        return;
    }
    else
    {
	  //update the iteration count (won't be changed after setting it once)
      if (!IsStaticAttribute(attributes))
      {
        iterations = portIterations;
      }
    }
  }
  iterations = iterations == 0 ? 1 : iterations;

  //allocate the memory for all DataPlaces
  for (DataPlaceMapType::iterator it = dataPlaceMap.begin(); it != dataPlaceMap.end(); ++it)
  {
    it->second.tileCount = it->second.staticData || it->second.fixedData ? 1 : iterations;
    int allocateTiles = it->second.tileCount;
    int layoutCUCount = it->second.vectorData ? VSIZE : 1;
    //compute the amount of memory needed
    int dataSize = 1;
    if (it->second.fixedData)
    {
      dataSize = it->second.e0Width * it->second.e0Height * it->second.ekWidth * it->second.ekHeight * PortDataTypeSize(it->second.portDataType) * layoutCUCount * allocateTiles;
    }
    else
    {
      dataSize = allocateTiles *
		  CMEMArraySize(it->second.tileWidth, it->second.tileHeight, it->second.padding, it->second.paddingVert, layoutCUCount) *
        PortDataTypeSize(it->second.portDataType) * it->second.e0Width * it->second.e0Height;
    }
    //allocate the memory or don't do anything if the data are already allocated and have the correct size
    if (it->second.actualSize != dataSize)
    {
      it->second.RequestMemory(dataSize);
    }
  }
}

void ACF_Graph::Run()
{
  if (errorOccured)
  {
    return;
  }

  int activeCUCount = -1, activeCUCountFixed = -1;

  //propagate input DataDescriptor data to graph input DataPlaces
  for (GraphDataType::iterator it = graphData.begin(); it != graphData.end(); ++it)
  {
    Attributes attributes = graphPorts[it->first].port.attributes.attributes;

    //check and update the active CU count, the count can be set only once and has to match across non-static vector inputs
    if (IsVectorAttribute(attributes) && !IsFixedAttribute(attributes))
    {
      if (activeCUCount < 0)
      {
        activeCUCount = it->second.activeCUCount;
      }
      else if (it->second.activeCUCount != activeCUCount)
      {
        errorOccured = true;
		char tmp[400];
		sprintf_s(tmp, "inconsistent CU counts %d vs. %d implied by graph inputs: %s", it->second.activeCUCount, activeCUCount, it->first.c_str());
		errorMessage = std::string(tmp);
        return;
      }
    }
	activeCUCountFixed = IsFixedAttribute(attributes)  && IsVectorAttribute(attributes) && activeCUCount <= 0 ? APU_VSIZE : activeCUCount;

	if (IsInputAttribute(attributes))
	{
		//get information needed for transforming the data from raw format to CMEM format
		DataPlace& dp = dataPlaceMap[make_pair("", it->first)];
		void* dataPlacePtr = dp.dataPtr;
		GraphDataInfo gdi = it->second;
		DataDescriptor* dd = gdi.data;
		void* inputDataPtr = dd->GetDataPtr();
		void* offsetsDataPtr = gdi.isIndirect ? gdi.offsets->GetDataPtr() : 0;
		int dpWidth = dp.e0Width * (dp.fixedData ? dp.ekWidth : dp.tileWidth);
		int dpHeight = dp.tileCount * dp.e0Height * (dp.fixedData ? dp.ekHeight : dp.tileHeight);
		int dpPadding = dp.padding;
		int dpPaddingVert = dp.paddingVert;
		int layoutCUCount = dp.vectorData ? VSIZE : 1;
		unsigned int ddWidth = dd->GetWidth() * dd->GetElementDimX();
		unsigned int ddHeight = dd->GetHeight() * dd->GetElementDimY();
		string message;
		APEX2OperationResult result;
		/*if (IsFixedAttribute(attributes) && !gdi.isIndirect) {
			if (dd != gdi.originalData)
			{
				CopyChangeWidth(*dd, *gdi.originalData);
			}
			memcpy(dataPlacePtr, inputDataPtr, dp.actualSize);
		}
		else*/ {
			//handle inputs which are not spanning all CUs, use data and originalData pointers
			if (dd != gdi.originalData)
			{
				CopyChangeWidth(*dd, *gdi.originalData);
			}
			if (gdi.offsets != 0 && gdi.offsets != gdi.originalOffsets)
			{
				CopyChangeWidth(*gdi.offsets, *gdi.originalOffsets);
			}

			//copy the data from the input DataDescriptors to input graph DataPlaces including changing the format from raw to CMEM
			//handle both direct inputs and indirect inputs
			switch (dd->GetElementDataType())
			{
			case (DATATYPE_08U) :
			case (DATATYPE_08S) :
								if (!gdi.isIndirect)
								{
									//result = ArrayToCMEMData<int08u>((int08u*)dataPlacePtr, (int08u*)inputDataPtr, dpWidth, dpHeight, dpPadding, layoutCUCount, ddWidth, &message);
									result = ArrayToCMEMDataSym<int08u>((int08u*)dataPlacePtr, (int08u*)inputDataPtr, dpWidth, dpHeight, dpPadding, dpPaddingVert, layoutCUCount, ddWidth, &message);
								}
								else
								{
									result = ArrayToCMEMDataIndirect<int08u, int32u>((int08u*)dataPlacePtr, (int08u*)inputDataPtr, dpWidth, dp.tileHeight, dp.tileCount, layoutCUCount, ddWidth, ddHeight, (int32u*)offsetsDataPtr, &message);
								}
								break;
			case (DATATYPE_16U) :
			case (DATATYPE_16S) :
								if (!gdi.isIndirect)
								{
									// result = ArrayToCMEMData<int16u>((int16u*)dataPlacePtr, (int16u*)inputDataPtr, dpWidth, dpHeight, dpPadding, layoutCUCount, ddWidth, &message);
									result = ArrayToCMEMDataSym<int16u>((int16u*)dataPlacePtr, (int16u*)inputDataPtr, dpWidth, dpHeight, dpPadding, dpPaddingVert, layoutCUCount, ddWidth, &message);
								}
								else
								{
									result = ArrayToCMEMDataIndirect<int16u, int32u>((int16u*)dataPlacePtr, (int16u*)inputDataPtr, dpWidth, dp.tileHeight, dp.tileCount, layoutCUCount, ddWidth, ddHeight, (int32u*)offsetsDataPtr, &message);
								}
								break;
			case (DATATYPE_32U) :
			case (DATATYPE_32S) :
								if (!gdi.isIndirect)
								{
									//result = ArrayToCMEMData<int32u>((int32u*)dataPlacePtr, (int32u*)inputDataPtr, dpWidth, dpHeight, dpPadding, layoutCUCount, ddWidth, &message);
									result = ArrayToCMEMDataSym<int32u>((int32u*)dataPlacePtr, (int32u*)inputDataPtr, dpWidth, dpHeight, dpPadding, dpPaddingVert, layoutCUCount, ddWidth, &message);
								}
								else
								{
									result = ArrayToCMEMDataIndirect<int32u, int32u>((int32u*)dataPlacePtr, (int32u*)inputDataPtr, dpWidth, dp.tileHeight, dp.tileCount, layoutCUCount, ddWidth, ddHeight, (int32u*)offsetsDataPtr, &message);
								}
								break;
			}
			//check whether an error or a warning occurred during transforming the data
			if (result == APEX2_ERROR)
			{
				errorOccured = true;
				errorMessage = message;
				return;
			}
			else if (result == APEX2_WARNING)
			{
				warningOccured = true;
				warningMessages += message + "\n";
			}
		}
	}
  }

  activeCUCount = activeCUCount <= 0 ? activeCUCountFixed : activeCUCount;

  //execute the kernel plan
  for (unsigned int i = 0; i < kernelPlan.size(); ++i)
  {
    //if plan element contains kernel execution
    if (kernelPlan[i].kernelInstance != kernels.end())
    {
      ACF_Kernel& kp = kernelPlan[i].kernelInstance->second;
      string instanceName = kernelPlan[i].kernelInstance->first;

      kernel_io_desc kernelIO[MAX_KN_PORTS];

      //compute the iteration count and fill in the kernel_io_desc structures
      unsigned int iterations = 1;
      for (int j = 0; j < kp.GetPortCount(); ++j)
      {
        DataPlace& dp = dataPlaceMap[make_pair(instanceName, kp.GetPort(j).identifier.identifier)];
        kernelIO[j].chunkWidth = dp.tileWidth;
        kernelIO[j].chunkHeight = dp.tileHeight;
        int dataTypeSize = PortDataTypeSize(dp.portDataType);
        kernelIO[j].chunkSpan = (dp.tileWidth + 2 * dp.padding) * dataTypeSize * dp.e0Width * dp.e0Height;
        int layoutCUCount = IsVectorAttribute(kp.GetPort(j).attributes.attributes) ? VSIZE : 1;
        unsigned char* startPtr = (unsigned char*)dp.dataPtr;
        startPtr += (dp.paddingVert * kernelIO[j].chunkSpan + dp.padding * dataTypeSize * dp.e0Width) * layoutCUCount;
        kernelIO[j].pMem = (void*)startPtr;
        iterations = max(dp.tileCount, iterations);
      }

      //set the ACF-accessible info variables
      _tileWidthInChunks = activeCUCount;
      _tileFirstCUID = 0;
	  VectorConditionController::Instance().Init();

      //iterate through slices
      for (unsigned int tileNum = 0; tileNum < iterations; ++tileNum)
      {
        //set the ACF-accessible info variables
        _firstTile = (tileNum == 0);
        _lastTile = (tileNum == iterations - 1);
        
        //run the kernel using the filled kernel_io_desc structures
        kp.Run(
          kernelIO[0], kernelIO[1], kernelIO[2],  kernelIO[3],  kernelIO[4],  kernelIO[5],  kernelIO[6],  kernelIO[7],
          kernelIO[8], kernelIO[9], kernelIO[10], kernelIO[11], kernelIO[12], kernelIO[13], kernelIO[14], kernelIO[15]);
		  
        //update the kernel_io_desc pointers for the next iteration
        for (int j = 0; j < kp.GetPortCount(); ++j)
        {
          int layoutCUCount = IsVectorAttribute(kp.GetPort(j).attributes.attributes) ? VSIZE : 1;
          unsigned char* ptr = (unsigned char*)kernelIO[j].pMem;
          bool st = IsStaticAttribute(kp.GetPort(j).attributes.attributes);
          if (!st)
          {
            ptr += kernelIO[j].chunkHeight * kernelIO[j].chunkSpan * layoutCUCount;
          }
          kernelIO[j].pMem = (void*)ptr;
        }
      }

      //set the ACF-accessible info variables
      _firstTile = false;
      _lastTile = false;
      _tileWidthInChunks = 0;
      _tileFirstCUID = 0;
    }

    //kernel outputs to connected kernels' inputs data propagations
    for (unsigned int j = 0; j < kernelPlan[i].dataPlacePropagations.size(); ++j)
    {
      DataPlace& dpA = dataPlaceMap[kernelPlan[i].dataPlacePropagations[j].first];
      DataPlace& dpB = dataPlaceMap[kernelPlan[i].dataPlacePropagations[j].second];

	  int dpAHeight = 0, dpAWidth = 0, dpBHeight = 0, dpBWidth = 0;

	  //compute the variables needed for transferring the data between the kernel output DataPlaces and connected kernels' input DataPlaces
	  if (dpA.fixedData)
	  {
		  dpAHeight = dpA.e0Height * dpA.ekHeight * (dpA.staticData ? 1 : dpA.tileCount);
		  dpAWidth = dpA.e0Width * dpA.ekWidth;
	  }
	  else
	  {
		  dpAHeight = dpA.e0Height * (dpA.staticData ? dpA.tileHeight : dpA.tileHeight * dpA.tileCount);
		  dpAWidth = dpA.tileWidth * dpA.e0Width;
	  }

	  if (dpB.fixedData)
	  {
		  dpBHeight = dpB.e0Height * dpB.ekHeight * (dpB.staticData ? 1 : dpB.tileCount);
		  dpBWidth = dpB.e0Width * dpB.ekWidth;
	  }
	  else
	  {
		  dpBHeight = dpB.e0Height * (dpB.staticData ? dpB.tileHeight : dpB.tileHeight * dpB.tileCount);
		  dpBWidth = dpB.tileWidth * dpB.e0Width;
	  }
      
      int dpAPaddingX = dpA.padding * dpA.e0Width;
      int dpAPaddingY = dpA.paddingVert * dpA.e0Height;
      int dpBPaddingX = dpB.padding * dpB.e0Width;
      int dpBPaddingY = dpB.paddingVert * dpB.e0Height;
      int paddingsA[4] = {dpAPaddingX, dpAPaddingX, dpAPaddingY, dpAPaddingY};
      int paddingsB[4] = {dpBPaddingX, dpBPaddingX, dpBPaddingY, dpBPaddingY};
      int granularityX = dpB.e0Width;
      int granularityY = dpB.e0Height;

	  int layoutCUCount = dpB.vectorData ? VSIZE : 1;
	  int inImgW = activeCUCount * dpAWidth;

      //copy the data and change the padding if necessary
      switch (dpB.portDataType)
      {
        case d08u:
        case d08s:
          ChangePaddingCMEM<int08u>((int08u*)dpB.dataPtr, (int08u*)dpA.dataPtr, inImgW, dpBWidth, dpBHeight, paddingsB, paddingsA, layoutCUCount, granularityX, granularityY);
          break;
        case d16u:
        case d16s:
			ChangePaddingCMEM<int16u>((int16u*)dpB.dataPtr, (int16u*)dpA.dataPtr, inImgW, dpBWidth, dpBHeight, paddingsB, paddingsA, layoutCUCount, granularityX, granularityY);
          break;
        case d32u:
        case d32s:
			ChangePaddingCMEM<int32u>((int32u*)dpB.dataPtr, (int32u*)dpA.dataPtr, inImgW, dpBWidth, dpBHeight, paddingsB, paddingsA, layoutCUCount, granularityX, granularityY);
          break;
      }
    }
  }

  //propagate output data to graph outputs
  for (GraphDataType::iterator it = graphData.begin(); it != graphData.end(); ++it)
  {
    Attributes attributes = graphPorts[it->first].port.attributes.attributes;
    if (IsOutputAttribute(attributes))
    {
      //get information needed for transforming the data from CMEM format to raw format
      DataPlace& dp = dataPlaceMap[make_pair("", it->first)];
      void* dataPlacePtr = dp.dataPtr;
      GraphDataInfo gdi = it->second;
      DataDescriptor* dd = gdi.data;
      void* outputDataPtr = dd->GetDataPtr();
      void* offsetsDataPtr = gdi.isIndirect ? gdi.offsets->GetDataPtr() : 0;
      int dpWidth = dp.e0Width * (dp.fixedData ? dp.ekWidth : dp.tileWidth);
      int dpHeight = dp.tileCount * dp.e0Height * (dp.fixedData ? dp.ekHeight : dp.tileHeight);
      int dpPadding = dp.padding;
	  int dpPaddingVert = dp.paddingVert;
      int layoutCUCount = dp.vectorData ? VSIZE : 1;

      //copy the data from the output graph DataPlaces to output DataDescriptors including changing the format from CMEM to raw
      switch (dd->GetElementDataType())
      {
        case (DATATYPE_08U):
        case (DATATYPE_08S):
		  CMEMDataToArray<int08u>((int08u*)outputDataPtr, (int08u*)dataPlacePtr, dpWidth, dpHeight, dpPadding, dpPaddingVert, layoutCUCount);
          break;
        case (DATATYPE_16U):
        case (DATATYPE_16S):
          CMEMDataToArray<int16u>((int16u*)outputDataPtr, (int16u*)dataPlacePtr, dpWidth, dpHeight, dpPadding, dpPaddingVert, layoutCUCount);
          break;
        case (DATATYPE_32U):
        case (DATATYPE_32S):
          CMEMDataToArray<int32u>((int32u*)outputDataPtr, (int32u*)dataPlacePtr, dpWidth, dpHeight, dpPadding, dpPaddingVert, layoutCUCount);
          break;
      }

      //handle outputs which are not spanning all CUs, use data and originalData pointers
      if (dd != gdi.originalData)
      {
        CopyChangeWidth(*gdi.originalData, *dd);
      }
    }
  }
}

ACF_Graph::DataPlace* ACF_Graph::GetDataPlacePtr(const string& kernelInstanceName, const string& portName)
{
  //return a pointer to requested DataPlace (debug functionality)
  DataPlaceKey dpKey = make_pair(kernelInstanceName, portName);
  DataPlaceMapType::iterator it = dataPlaceMap.find(dpKey);
  if (it != dataPlaceMap.end())
  {
    return &(it->second);
  }
  return 0;
}

ACF_Graph::~ACF_Graph()
{
  //deallocate the extra data used during handling the input/output data which don't span all CUs
  for (GraphDataType::iterator it = graphData.begin(); it != graphData.end(); ++it)
  {
    DataDescriptor* data = it->second.data;
    DataDescriptor* originalData = it->second.originalData;
    DataDescriptor* offsets = it->second.offsets;
    DataDescriptor* originalOffsets = it->second.originalOffsets;

    if (data != originalData)
    {
      delete data;
      data = 0;
    }

    if (offsets != originalOffsets)
    {
      delete offsets;
      offsets = 0;
    }
  }
}

void ACF_Graph::CopyChangeWidth(DataDescriptor& destination, DataDescriptor& source)
{
  //copy the data and include extra columns corresponding to non-active CUs
  int destinationElementsX = destination.GetWidth();
  int depth = destination.GetDimensions();
  int destinationElementsY = destination.GetHeight()*depth;

  int sourceElementsX = source.GetWidth();
  int elementBytesX = destination.GetElementDimX() * DataDescriptor::ReturnElementSize(destination.GetElementDataType());
  int elementSizeY = destination.GetElementDimY();
  uint8_t* srcPtr = (uint8_t*)source.GetDataPtr();
  uint8_t* dstPtr = (uint8_t*)destination.GetDataPtr();
	  for (int by = 0; by < destinationElementsY * elementSizeY; ++by)
	  {
		  uint8_t* srcRow = &(srcPtr[by * source.GetSpanRow()]);
		  uint8_t* dstRow = &(dstPtr[by * destination.GetSpanRow()]);
		  for (int rowElementIndex = 0; rowElementIndex < (int)destinationElementsX; ++rowElementIndex)
		  {
			  int srcRowElementIndex = rowElementIndex < sourceElementsX ? rowElementIndex : sourceElementsX - 1;
			  uint8_t* srcE = &(srcRow[srcRowElementIndex * elementBytesX]);
			  uint8_t* dstE = &(dstRow[rowElementIndex * elementBytesX]);
			  for (int bi = 0; bi < elementBytesX; ++bi)
			  {
				  dstE[bi] = srcE[bi];
			  }
		  }
	  }
}
