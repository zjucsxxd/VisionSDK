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
* \brief APU ACF kernel simulation
* \author Igor Aleksandrowicz
* \version
* \date 30-January-2014
****************************************************************************/

#ifndef _APU_ACF_KN_H_
#define _APU_ACF_KN_H_

#ifndef ACF_KERNEL_METADATA
#define ACF_KERNEL_METADATA
#endif

#ifndef ACF_KERNEL_IMPLEMENTATION
#define ACF_KERNEL_IMPLEMENTATION
#endif

#include <string>
#include <unordered_map>
#include "apu_config.hpp"

using std::string;
using std::unordered_map;

namespace APEX2
{


//global variables used by ACF_RET_VAR function
extern bool _firstTile;
extern bool _lastTile;
extern int _tileWidthInChunks;
extern int _tileFirstCUID;

//enum for ACF_RET_VAR
enum ACF_VAR
{
  ACF_VAR_FIRST_TILE_FLAG,
  ACF_VAR_LAST_TILE_FLAG,
  ACF_VAR_TILE_WIDTH_IN_CHUNKS,
  ACF_VAR_FIRST_CUID,
};

int16u ACF_RET_VAR(ACF_VAR lVar);

//can be modified but kernel metadata struct and kernel struct have to be updated to accomodate the new limit
const int MAX_KN_PORTS = 16;

//kernel metadata __index struct
struct __index
{
  int index;
  __index(int index){this->index = index;}
};

//the kernel metada __identifier conflicts with MSVS __identifier
#ifdef _MSC_VER
#define __identifier __identifier(__identifier)
#endif

//kernel metadata __identifier struct
struct __identifier
{
  string identifier;
  __identifier(const string& identifier){this->identifier = identifier;}
};

//kernel attributes enum
enum Attributes
{
  ACF_ATTR_VEC_IN,
  ACF_ATTR_VEC_IN_FIXED,
  ACF_ATTR_VEC_IN_STATIC,
  ACF_ATTR_VEC_IN_STATIC_FIXED,
  ACF_ATTR_VEC_OUT,
  ACF_ATTR_VEC_OUT_FIXED,
  ACF_ATTR_VEC_OUT_STATIC,
  ACF_ATTR_VEC_OUT_STATIC_FIXED,
  //???
  //ACF_ATTR_VEC_OUT_FIFO,
  //ACF_ATTR_VEC_OUT_FIFO_FIXED,
  ACF_ATTR_SCL_IN,
  ACF_ATTR_SCL_IN_FIXED,
  ACF_ATTR_SCL_IN_STATIC,
  ACF_ATTR_SCL_IN_STATIC_FIXED,
  ACF_ATTR_SCL_OUT,
  ACF_ATTR_SCL_OUT_FIXED,
  ACF_ATTR_SCL_OUT_STATIC,
  ACF_ATTR_SCL_OUT_STATIC_FIXED,
  //deprecated
  ACF_ATTR_IN,
  ACF_ATTR_CFG,
  ACF_ATTR_OUT,
};

//kernel metadata __attributes struct
struct __attributes
{
  Attributes attributes;
  __attributes(Attributes attributes){this->attributes = attributes;}
};

//Attributes struct queries
bool IsOutputAttribute(Attributes attributes);
bool IsInputAttribute(Attributes attributes);
bool IsVectorAttribute(Attributes attributes);
bool IsScalarAttribute(Attributes attributes);
bool IsFixedAttribute(Attributes attributes);
bool IsStaticAttribute(Attributes attributes);

//returns an Attribues struct matching the requirements
Attributes ReturnAttribute(bool isInput, bool isVector, bool isStatic, bool isFixed);

//kernel metadata __spatial_dep struct
struct __spatial_dep
{
  int dependencies[4];
  __spatial_dep(int left, int right, int top, int bottom)
  {
    dependencies[0] = left;
    dependencies[1] = right;
    dependencies[2] = top;
    dependencies[3] = bottom;
  }
};

//kernel port data type enum
enum PortDataType
{
  d08u = 0,
  d08s = 1,
  d16u = 2,
  d16s = 3,
  d32u = 4,
  d32s = 5
};

//returns the size of bytes for a given kernel port data type
unsigned int PortDataTypeSize(PortDataType portDataType);

//kernel metadata __e0_data_type struct
struct __e0_data_type
{
  PortDataType dataType;
  __e0_data_type(PortDataType dataType){this->dataType = dataType;}
};

//kernel metadata __e0_size struct
struct __e0_size
{
  int size[2];
  __e0_size(int width, int height)
  {
    size[0] = width;
    size[1] = height;
  }
};

//kernel metadata __ek_size struct
struct __ek_size
{
  int size[2];
  __ek_size(int width, int height)
  {
    size[0] = width;
    size[1] = height;
  }
};

//kernel metadata port struct
struct __port
{
  __index index;
  __identifier identifier;
  __attributes attributes;
  __spatial_dep spatial_dep;
  __e0_data_type e0_data_type;
  __e0_size e0_size;
  __ek_size ek_size;

  //ACF syntax-compatible port constructor
  __port(
  __index index,
  __identifier identifier,
  __attributes attributes,
  __spatial_dep spatial_dep,
  __e0_data_type e0_data_type,
  __e0_size e0_size,
  __ek_size ek_size
  ):
  index(index), identifier(identifier), attributes(attributes), spatial_dep(spatial_dep), e0_data_type(e0_data_type), e0_size(e0_size), ek_size(ek_size)
  {
  }

  __port():
    index(-1), identifier(""), attributes(ACF_ATTR_OUT), spatial_dep(0, 0, 0, 0), e0_data_type(d08u), e0_size(0, 0), ek_size(0, 0)
  {
  }
};

struct KERNEL_INFO
{
    string name;
    int portCount;
    __port ports[MAX_KN_PORTS];

    //ACF syntax-compatible metadata constructor
    KERNEL_INFO(const string& name, int portCount,
      __port p00 = __port(), __port p01 = __port(), __port p02 = __port(), __port p03 = __port(),
      __port p04 = __port(), __port p05 = __port(), __port p06 = __port(), __port p07 = __port(),
      __port p08 = __port(), __port p09 = __port(), __port p10 = __port(), __port p11 = __port(),
      __port p12 = __port(), __port p13 = __port(), __port p14 = __port(), __port p15 = __port()):
      name(name), portCount(portCount)
    {
      ports[ 0] = p00;
      ports[ 1] = p01;
      ports[ 2] = p02;
      ports[ 3] = p03;
      ports[ 4] = p04;
      ports[ 5] = p05;
      ports[ 6] = p06;
      ports[ 7] = p07;
      ports[ 8] = p08;
      ports[ 9] = p09;
      ports[10] = p10;
      ports[11] = p11;
      ports[12] = p12;
      ports[13] = p13;
      ports[14] = p14;
      ports[15] = p15;
    }
};

//kernel IO structure
struct kernel_io_desc
{
  void* pMem; //pointer to the chunk of data
  int chunkWidth; //width of the chunk in units of e0
  int chunkHeight; //height of the chunk in units of e0
  int chunkSpan; //number of bytes to skip to get to the next line of bytes
  //--------------------------------------
  //following fields are for framework use
  //--------------------------------------
  char  _framework_index;

  kernel_io_desc():
    pMem(0), chunkWidth(0), chunkHeight(0), chunkSpan(0), _framework_index(0){}
};

class ACF_Kernel
{
private:
  KERNEL_INFO kernelInfo;
  //function pointers for different numbers of parameters
  void (*fp00)();
  void (*fp01)(kernel_io_desc);
  void (*fp02)(kernel_io_desc, kernel_io_desc);
  void (*fp03)(kernel_io_desc, kernel_io_desc, kernel_io_desc);
  void (*fp04)(kernel_io_desc, kernel_io_desc, kernel_io_desc, kernel_io_desc);
  void (*fp05)(kernel_io_desc, kernel_io_desc, kernel_io_desc, kernel_io_desc, kernel_io_desc);
  void (*fp06)(kernel_io_desc, kernel_io_desc, kernel_io_desc, kernel_io_desc, kernel_io_desc, kernel_io_desc);
  void (*fp07)(kernel_io_desc, kernel_io_desc, kernel_io_desc, kernel_io_desc, kernel_io_desc, kernel_io_desc, kernel_io_desc);
  void (*fp08)(kernel_io_desc, kernel_io_desc, kernel_io_desc, kernel_io_desc, kernel_io_desc, kernel_io_desc, kernel_io_desc, kernel_io_desc);
  void (*fp09)(kernel_io_desc, kernel_io_desc, kernel_io_desc, kernel_io_desc, kernel_io_desc, kernel_io_desc, kernel_io_desc, kernel_io_desc,
    kernel_io_desc);
  void (*fp10)(kernel_io_desc, kernel_io_desc, kernel_io_desc, kernel_io_desc, kernel_io_desc, kernel_io_desc, kernel_io_desc, kernel_io_desc,
    kernel_io_desc, kernel_io_desc);
  void (*fp11)(kernel_io_desc, kernel_io_desc, kernel_io_desc, kernel_io_desc, kernel_io_desc, kernel_io_desc, kernel_io_desc, kernel_io_desc,
    kernel_io_desc, kernel_io_desc, kernel_io_desc);
  void (*fp12)(kernel_io_desc, kernel_io_desc, kernel_io_desc, kernel_io_desc, kernel_io_desc, kernel_io_desc, kernel_io_desc, kernel_io_desc,
    kernel_io_desc, kernel_io_desc, kernel_io_desc, kernel_io_desc);
  void (*fp13)(kernel_io_desc, kernel_io_desc, kernel_io_desc, kernel_io_desc, kernel_io_desc, kernel_io_desc, kernel_io_desc, kernel_io_desc,
    kernel_io_desc, kernel_io_desc, kernel_io_desc, kernel_io_desc, kernel_io_desc);
  void (*fp14)(kernel_io_desc, kernel_io_desc, kernel_io_desc, kernel_io_desc, kernel_io_desc, kernel_io_desc, kernel_io_desc, kernel_io_desc,
    kernel_io_desc, kernel_io_desc, kernel_io_desc, kernel_io_desc, kernel_io_desc, kernel_io_desc);
  void (*fp15)(kernel_io_desc, kernel_io_desc, kernel_io_desc, kernel_io_desc, kernel_io_desc, kernel_io_desc, kernel_io_desc, kernel_io_desc,
    kernel_io_desc, kernel_io_desc, kernel_io_desc, kernel_io_desc, kernel_io_desc, kernel_io_desc, kernel_io_desc);
  void (*fp16)(kernel_io_desc, kernel_io_desc, kernel_io_desc, kernel_io_desc, kernel_io_desc, kernel_io_desc, kernel_io_desc, kernel_io_desc,
    kernel_io_desc, kernel_io_desc, kernel_io_desc, kernel_io_desc, kernel_io_desc, kernel_io_desc, kernel_io_desc, kernel_io_desc);

  bool errorOccured;
  string errorMessage;

  //database of available kernels
  static unordered_map<string, ACF_Kernel> ACFKernelDatabase;
public:
  void Run(const kernel_io_desc& io00 = kernel_io_desc(), const kernel_io_desc& io01 = kernel_io_desc(), const kernel_io_desc& io02 = kernel_io_desc(), const kernel_io_desc& io03 = kernel_io_desc(),
    const kernel_io_desc& io04 = kernel_io_desc(), const kernel_io_desc& io05 = kernel_io_desc(), const kernel_io_desc& io06 = kernel_io_desc(), const kernel_io_desc& io07 = kernel_io_desc(),
    const kernel_io_desc& io08 = kernel_io_desc(), const kernel_io_desc& io09 = kernel_io_desc(), const kernel_io_desc& io10 = kernel_io_desc(), const kernel_io_desc& io11 = kernel_io_desc(),
    const kernel_io_desc& io12 = kernel_io_desc(), const kernel_io_desc& io13 = kernel_io_desc(), const kernel_io_desc& io14 = kernel_io_desc(), const kernel_io_desc& io15 = kernel_io_desc());

  ACF_Kernel(const KERNEL_INFO& kernelInfo, void* functionAddress);
  ACF_Kernel();

  __port GetPort(int index)
  {
    return kernelInfo.ports[index];
  }

  string GetName()
  {
    return kernelInfo.name;
  }

  int GetPortCount()
  {
    return kernelInfo.portCount;
  }
  
  static void RegisterPrototypeInDatabase(const ACF_Kernel& kernel);
  //returns the default kernel if not found in the database
  static ACF_Kernel GetPrototypeFromDatabase(const string& kernelName);

  bool ErrorOccured(){return errorOccured;}
  string ErrorMessage(){return errorMessage;}
};

}

#endif // _APU_ACF_KN_H_
