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
* \brief APU ACF kernel simulation
* \author Igor Aleksandrowicz
* \version
* \date 31-January-2014
****************************************************************************/

#include "acf_kernel.hpp"
#include <sstream>

using namespace APEX2;

using std::stringstream;

unordered_map<string, ACF_Kernel> ACF_Kernel::ACFKernelDatabase;

//global variables used by ACF_RET_VAR function
bool APEX2::_firstTile = false;
bool APEX2::_lastTile = false;
int APEX2::_tileWidthInChunks = APU_VSIZE;
int APEX2::_tileFirstCUID = 0;

/****************************************************************************
* functions
****************************************************************************/

enum ACF_VAR
{
  ACF_VAR_FIRST_TILE_FLAG,
  ACF_VAR_LAST_TILE_FLAG,
  ACF_VAR_TILE_WIDTH_IN_CHUNKS,
  ACF_VAR_FIRST_CUID,
};

//ACF_RET_VAR... native ACF query function which can be used inside a kernel
int16u APEX2::ACF_RET_VAR(ACF_VAR lVar)
{
  switch (lVar)
  {
    case ACF_VAR_FIRST_TILE_FLAG:
      return _firstTile ? 1 : 0;
    case ACF_VAR_LAST_TILE_FLAG:
      return _lastTile ? 1 : 0;
    case ACF_VAR_TILE_WIDTH_IN_CHUNKS:
      return (int16u)_tileWidthInChunks;
    case ACF_VAR_FIRST_CUID:
      return (int16u)_tileFirstCUID;
  }

  return 0;
}

//////////various kernel metadata attribute query function implementations

unsigned int APEX2::PortDataTypeSize(PortDataType portDataType)
{
  switch (portDataType)
  {
    case d08u:
    case d08s:
      return 1;
    case d16u:
    case d16s:
      return 2;
    case d32u:
    case d32s:
      return 4;
  }
  return 1;
}

bool APEX2::IsOutputAttribute(Attributes attributes)
{
  switch (attributes)
  {
    case ACF_ATTR_VEC_OUT:
    case ACF_ATTR_VEC_OUT_FIXED:
    case ACF_ATTR_VEC_OUT_STATIC:
    case ACF_ATTR_VEC_OUT_STATIC_FIXED:
    case ACF_ATTR_SCL_OUT:
    case ACF_ATTR_SCL_OUT_FIXED:
    case ACF_ATTR_SCL_OUT_STATIC:
    case ACF_ATTR_SCL_OUT_STATIC_FIXED:
    case ACF_ATTR_OUT:
      return true;
  }
  return false;
}

bool APEX2::IsInputAttribute(Attributes attributes)
{
  switch (attributes)
  {
    case ACF_ATTR_VEC_IN:
    case ACF_ATTR_VEC_IN_FIXED:
    case ACF_ATTR_VEC_IN_STATIC:
    case ACF_ATTR_VEC_IN_STATIC_FIXED:
    case ACF_ATTR_SCL_IN:
    case ACF_ATTR_SCL_IN_FIXED:
    case ACF_ATTR_SCL_IN_STATIC:
    case ACF_ATTR_SCL_IN_STATIC_FIXED:
    case ACF_ATTR_IN:
    case ACF_ATTR_CFG:
      return true;
  }
  return false;
}

bool APEX2::IsVectorAttribute(Attributes attributes)
{
  switch (attributes)
  {
    case ACF_ATTR_VEC_IN:
    case ACF_ATTR_VEC_IN_FIXED:
    case ACF_ATTR_VEC_IN_STATIC:
    case ACF_ATTR_VEC_IN_STATIC_FIXED:
    case ACF_ATTR_VEC_OUT:
    case ACF_ATTR_VEC_OUT_FIXED:
    case ACF_ATTR_VEC_OUT_STATIC:
    case ACF_ATTR_VEC_OUT_STATIC_FIXED:
    case ACF_ATTR_IN:
    case ACF_ATTR_OUT:
      return true;
  }
  return false;
}

bool APEX2::IsScalarAttribute(Attributes attributes)
{
  switch (attributes)
  {
    case ACF_ATTR_SCL_IN:
    case ACF_ATTR_SCL_IN_FIXED:
    case ACF_ATTR_SCL_IN_STATIC:
    case ACF_ATTR_SCL_IN_STATIC_FIXED:
    case ACF_ATTR_SCL_OUT:
    case ACF_ATTR_SCL_OUT_FIXED:
    case ACF_ATTR_SCL_OUT_STATIC:
    case ACF_ATTR_SCL_OUT_STATIC_FIXED:
    case ACF_ATTR_CFG:
      return true;
  }
  return false;
}

bool APEX2::IsFixedAttribute(Attributes attributes)
{
  switch (attributes)
  {
    case ACF_ATTR_VEC_IN_FIXED:
    case ACF_ATTR_VEC_IN_STATIC_FIXED:
    case ACF_ATTR_VEC_OUT_FIXED:
    case ACF_ATTR_VEC_OUT_STATIC_FIXED:
    case ACF_ATTR_SCL_IN_FIXED:
    case ACF_ATTR_SCL_IN_STATIC_FIXED:
    case ACF_ATTR_SCL_OUT_FIXED:
    case ACF_ATTR_SCL_OUT_STATIC_FIXED:
    case ACF_ATTR_CFG:
      return true;
  }
  return false;
}

bool APEX2::IsStaticAttribute(Attributes attributes)
{
  switch (attributes)
  {
    case ACF_ATTR_VEC_IN_STATIC:
    case ACF_ATTR_VEC_IN_STATIC_FIXED:
    case ACF_ATTR_VEC_OUT_STATIC:
    case ACF_ATTR_VEC_OUT_STATIC_FIXED:
    case ACF_ATTR_SCL_IN_STATIC:
    case ACF_ATTR_SCL_IN_STATIC_FIXED:
    case ACF_ATTR_SCL_OUT_STATIC:
    case ACF_ATTR_SCL_OUT_STATIC_FIXED:
    case ACF_ATTR_CFG:
      return true;
  }
  return false;
}

Attributes APEX2::ReturnAttribute(bool isInput, bool isVector, bool isStatic, bool isFixed)
{
  if (isInput && isVector && isStatic && isFixed) return ACF_ATTR_VEC_IN_STATIC_FIXED;
  if (isInput && isVector && isStatic && !isFixed) return ACF_ATTR_VEC_IN_STATIC;
  if (isInput && isVector && !isStatic && isFixed) return ACF_ATTR_VEC_IN_FIXED;
  if (isInput && isVector && !isStatic && !isFixed) return ACF_ATTR_VEC_IN;
  if (isInput && !isVector && isStatic && isFixed) return ACF_ATTR_SCL_IN_STATIC_FIXED;
  if (isInput && !isVector && isStatic && !isFixed) return ACF_ATTR_SCL_IN_STATIC;
  if (isInput && !isVector && !isStatic && isFixed) return ACF_ATTR_SCL_IN_FIXED;
  if (isInput && !isVector && !isStatic && !isFixed) return ACF_ATTR_SCL_IN;
  if (!isInput && isVector && isStatic && isFixed) return ACF_ATTR_VEC_OUT_STATIC_FIXED;
  if (!isInput && isVector && isStatic && !isFixed) return ACF_ATTR_VEC_OUT_STATIC;
  if (!isInput && isVector && !isStatic && isFixed) return ACF_ATTR_VEC_OUT_FIXED;
  if (!isInput && isVector && !isStatic && !isFixed) return ACF_ATTR_VEC_OUT;
  if (!isInput && !isVector && isStatic && isFixed) return ACF_ATTR_SCL_OUT_STATIC_FIXED;
  if (!isInput && !isVector && isStatic && !isFixed) return ACF_ATTR_SCL_OUT_STATIC;
  if (!isInput && !isVector && !isStatic && isFixed) return ACF_ATTR_SCL_OUT_FIXED;
  if (!isInput && !isVector && !isStatic && !isFixed) return ACF_ATTR_SCL_OUT;
  return ACF_ATTR_VEC_IN;
}

ACF_Kernel::ACF_Kernel():
  errorOccured(true), errorMessage("empty kernel"), kernelInfo("", 0),
    fp00(0), fp01(0), fp02(0), fp03(0), fp04(0), fp05(0), fp06(0), fp07(0), fp08(0),
    fp09(0), fp10(0), fp11(0), fp12(0), fp13(0), fp14(0), fp15(0), fp16(0)
{
}

ACF_Kernel::ACF_Kernel(const KERNEL_INFO& kernelInfo, void* functionAddress):
  errorOccured(false), kernelInfo(kernelInfo),
  fp00(0), fp01(0), fp02(0), fp03(0), fp04(0), fp05(0), fp06(0), fp07(0), fp08(0),
    fp09(0), fp10(0), fp11(0), fp12(0), fp13(0), fp14(0), fp15(0), fp16(0)
{
  //only the function pointer with number of parameters matching the metadata will be used
  switch(kernelInfo.portCount)
  {
  case 0:
    fp00 = (void(*)())functionAddress;
    break;
  case 1:
    fp01 = (void(*)(kernel_io_desc))functionAddress;
    break;
  case 2:
    fp02 = (void(*)(kernel_io_desc, kernel_io_desc))functionAddress;
    break;
  case 3:
    fp03 = (void(*)(kernel_io_desc, kernel_io_desc, kernel_io_desc))functionAddress;
    break;
  case 4:
    fp04 = (void(*)(kernel_io_desc, kernel_io_desc, kernel_io_desc, kernel_io_desc))functionAddress;
    break;
  case 5:
    fp05 = (void(*)(kernel_io_desc, kernel_io_desc, kernel_io_desc, kernel_io_desc, kernel_io_desc))functionAddress;
    break;
  case 6:
    fp06 = (void(*)(kernel_io_desc, kernel_io_desc, kernel_io_desc, kernel_io_desc, kernel_io_desc, kernel_io_desc))functionAddress;
    break;
  case 7:
    fp07 = (void(*)(kernel_io_desc, kernel_io_desc, kernel_io_desc, kernel_io_desc, kernel_io_desc, kernel_io_desc, kernel_io_desc))functionAddress;
    break;
  case 8:
    fp08 = (void(*)(kernel_io_desc, kernel_io_desc, kernel_io_desc, kernel_io_desc, kernel_io_desc, kernel_io_desc, kernel_io_desc, kernel_io_desc))
      functionAddress;
    break;
  case 9:
    fp09 = (void(*)(kernel_io_desc, kernel_io_desc, kernel_io_desc, kernel_io_desc, kernel_io_desc, kernel_io_desc, kernel_io_desc, kernel_io_desc,
      kernel_io_desc))functionAddress;
    break;
  case 10:
    fp10 = (void(*)(kernel_io_desc, kernel_io_desc, kernel_io_desc, kernel_io_desc, kernel_io_desc, kernel_io_desc, kernel_io_desc, kernel_io_desc,
      kernel_io_desc, kernel_io_desc))functionAddress;
    break;
  case 11:
    fp11 = (void(*)(kernel_io_desc, kernel_io_desc, kernel_io_desc, kernel_io_desc, kernel_io_desc, kernel_io_desc, kernel_io_desc, kernel_io_desc,
      kernel_io_desc, kernel_io_desc, kernel_io_desc))functionAddress;
    break;
  case 12:
    fp12 = (void(*)(kernel_io_desc, kernel_io_desc, kernel_io_desc, kernel_io_desc, kernel_io_desc, kernel_io_desc, kernel_io_desc, kernel_io_desc,
      kernel_io_desc, kernel_io_desc, kernel_io_desc, kernel_io_desc))functionAddress;
    break;
  case 13:
    fp13 = (void(*)(kernel_io_desc, kernel_io_desc, kernel_io_desc, kernel_io_desc, kernel_io_desc, kernel_io_desc, kernel_io_desc, kernel_io_desc,
      kernel_io_desc, kernel_io_desc, kernel_io_desc, kernel_io_desc, kernel_io_desc))functionAddress;
    break;
  case 14:
    fp14 = (void(*)(kernel_io_desc, kernel_io_desc, kernel_io_desc, kernel_io_desc, kernel_io_desc, kernel_io_desc, kernel_io_desc, kernel_io_desc,
      kernel_io_desc, kernel_io_desc, kernel_io_desc, kernel_io_desc, kernel_io_desc, kernel_io_desc))functionAddress;
    break;
  case 15:
    fp15 = (void(*)(kernel_io_desc, kernel_io_desc, kernel_io_desc, kernel_io_desc, kernel_io_desc, kernel_io_desc, kernel_io_desc, kernel_io_desc,
      kernel_io_desc, kernel_io_desc, kernel_io_desc, kernel_io_desc, kernel_io_desc, kernel_io_desc, kernel_io_desc))functionAddress;
    break;
  case 16:
    fp16 = (void(*)(kernel_io_desc, kernel_io_desc, kernel_io_desc, kernel_io_desc, kernel_io_desc, kernel_io_desc, kernel_io_desc, kernel_io_desc,
      kernel_io_desc, kernel_io_desc, kernel_io_desc, kernel_io_desc, kernel_io_desc, kernel_io_desc, kernel_io_desc, kernel_io_desc))functionAddress;
    break;
  }

  if (kernelInfo.name == "")
  {
    errorOccured = true;
    errorMessage = "empty kernel name";
    return;
  }

  //does the kernelinfo port count match the number of ports provided?
  int filledPorts = 0;
  for (int i = 0; i < MAX_KN_PORTS; ++i)
  {
    if (kernelInfo.ports[i].index.index >= 0 || kernelInfo.ports[i].identifier.identifier != "")
    {
      ++filledPorts;
    }
  }

  if (filledPorts != kernelInfo.portCount)
  {
    errorOccured = true;
    errorMessage = "port count doesn't match the number of ports provided";
    return;
  }

  //validate the provided ports
  for (int i = 0; i < kernelInfo.portCount; ++i)
  {
    if (kernelInfo.ports[i].index.index < 0 || kernelInfo.ports[i].index.index >= kernelInfo.portCount)
    {
      errorOccured = true;
      stringstream ess;
      ess << "invalid port index: " << kernelInfo.ports[i].index.index;
      errorMessage = ess.str();
      return;
    }
 
    if (kernelInfo.ports[i].identifier.identifier == "")
    {
        errorOccured = true;
        errorMessage = "empty port identifier";
        return;
    }

    for (int j = 0; j < kernelInfo.portCount; ++j)
    {
      if (i == j)
      {
        continue;
      }

      if (kernelInfo.ports[i].index.index == kernelInfo.ports[j].index.index)
      {
        errorOccured = true;
        stringstream ess;
        ess << "duplicated port index: " << kernelInfo.ports[i].index.index;
        errorMessage = ess.str();
        return;
      }

      if (kernelInfo.ports[i].identifier.identifier == kernelInfo.ports[j].identifier.identifier)
      {
        errorOccured = true;
        errorMessage = "duplicated port identifier: " + kernelInfo.ports[i].identifier.identifier;
        return;
      }
    }

    if (kernelInfo.ports[i].spatial_dep.dependencies[0] < 0 || kernelInfo.ports[i].spatial_dep.dependencies[1] < 0 ||
        kernelInfo.ports[i].spatial_dep.dependencies[2] < 0 || kernelInfo.ports[i].spatial_dep.dependencies[3] < 0)
    {
        errorOccured = true;
        errorMessage = "invalid spatial dependencies for kernel port: " + kernelInfo.name + "." + kernelInfo.ports[i].identifier.identifier;
        return;
    }

    if (kernelInfo.ports[i].e0_size.size[0] < 1 || kernelInfo.ports[i].e0_size.size[1] < 1)
    {
        errorOccured = true;
        errorMessage = "invalid e0 size for kernel port: " + kernelInfo.name + "." + kernelInfo.ports[i].identifier.identifier;
        return;
    }

    if (kernelInfo.ports[i].ek_size.size[0] < 1 || kernelInfo.ports[i].ek_size.size[1] < 1)
    {
        errorOccured = true;
        errorMessage = "invalid ek size for kernel port: " + kernelInfo.name + "." + kernelInfo.ports[i].identifier.identifier;
        return;
    }
  }
}

void ACF_Kernel::Run(const kernel_io_desc& io00, const kernel_io_desc& io01, const kernel_io_desc& io02, const kernel_io_desc& io03,
    const kernel_io_desc& io04, const kernel_io_desc& io05, const kernel_io_desc& io06, const kernel_io_desc& io07,
    const kernel_io_desc& io08, const kernel_io_desc& io09, const kernel_io_desc& io10, const kernel_io_desc& io11,
    const kernel_io_desc& io12, const kernel_io_desc& io13, const kernel_io_desc& io14, const kernel_io_desc& io15)
{
   //select the correct function pointer and run the function
   switch(kernelInfo.portCount)
   {
   case 0:
     fp00();
     break;
   case 1:
     fp01(io00);
     break;
   case 2:
     fp02(io00, io01);
     break;
   case 3:
     fp03(io00, io01, io02);
     break;
   case 4:
     fp04(io00, io01, io02, io03);
     break;
   case 5:
     fp05(io00, io01, io02, io03, io04);
     break;
   case 6:
     fp06(io00, io01, io02, io03, io04, io05);
     break;
   case 7:
     fp07(io00, io01, io02, io03, io04, io05, io06);
     break;
   case 8:
     fp08(io00, io01, io02, io03, io04, io05, io06, io07);
     break;
   case 9:
     fp09(io00, io01, io02, io03, io04, io05, io06, io07, io08);
     break;
   case 10:
     fp10(io00, io01, io02, io03, io04, io05, io06, io07, io08, io09);
     break;
   case 11:
     fp11(io00, io01, io02, io03, io04, io05, io06, io07, io08, io09, io10);
     break;
   case 12:
     fp12(io00, io01, io02, io03, io04, io05, io06, io07, io08, io09, io10, io11);
     break;
   case 13:
     fp13(io00, io01, io02, io03, io04, io05, io06, io07, io08, io09, io10, io11, io12);
     break;
   case 14:
     fp14(io00, io01, io02, io03, io04, io05, io06, io07, io08, io09, io10, io11, io12, io13);
     break;
   case 15:
     fp15(io00, io01, io02, io03, io04, io05, io06, io07, io08, io09, io10, io11, io12, io13, io14);
     break;
   case 16:
     fp16(io00, io01, io02, io03, io04, io05, io06, io07, io08, io09, io10, io11, io12, io13, io14, io15);
     break;
   }
}

void ACF_Kernel::RegisterPrototypeInDatabase(const ACF_Kernel& kernel)
{
  //no need to check if the kernel is in the database already (see map::insert documentation)
  ACFKernelDatabase.insert(std::pair<string, ACF_Kernel>(kernel.kernelInfo.name, kernel));
}

ACF_Kernel ACF_Kernel::GetPrototypeFromDatabase(const string& kernelName)
{
  unordered_map<string, ACF_Kernel>::iterator it = ACFKernelDatabase.find(kernelName);
  //return empty kernel if the name doesn't exist in the database
  if (it != ACFKernelDatabase.end())
  {
    return it->second;
  }
  else
  {
    return ACF_Kernel();
  }
}
