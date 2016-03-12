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
* \brief APU_lib I/O data descriptor implementation
* \author Igor Aleksandrowicz
* \version
* \date 10-February-2014
****************************************************************************/

#include "acf_data_descriptor.hpp"
#include <cstring>
#include <climits>
#include <sstream>
#include <cstdint>
#include <ctime>
using namespace APEX2;

using std::stringstream;


/*==============================================================================*/
/* Returns a pixel width according to its type				  */
/*==============================================================================*/
unsigned int DataDescriptor::ReturnElementSize(DATATYPE type)
{
  unsigned int size;
      switch (type)
      {
	case DATATYPE_08S:
	case DATATYPE_08U:
	  size = 1;
	  break;
	case DATATYPE_16S:
	case DATATYPE_16U:
	  size = 2;
	  break;
	case DATATYPE_32S:
	case DATATYPE_32U:
	  size = 4;
	  break;
	default:
	  size = 1;
	  break;
      }
     return size;
}
  
/*==============================================================================*/
/* Constructor - creates an empty instance of the class			  */
/*==============================================================================*/
DataDescriptor::DataDescriptor()
{
	pData           = 0;
	pDataPhys       = 0;
	Width           = 0;
	Height          = 0;
	origPData = pData;
	origPDataPhys = pDataPhys;
	OrigWidth = Width;
	OrigHeight = Height;


	Span            = 0;
	SpanRow         = 0;

	DataSize        = 0;
	ElementDataType = DATATYPE_08U;
	ElementDimX     = 1;
	ElementDimY     = 1;
	Dim             = 1;
	DimOffset       = Width*Height*DataSize*ElementDimX*ElementDimY;
    
	AllocationType  = ALLOC_UNKNOWN;
	
	ROI[_roiLeft]   = 0;
	ROI[_roiTop]    = 0;
	ROI[_roiWidth]	= Width;
	ROI[_roiHeight] = Height;
    
	FreeOnExit      = false;
}
  
/*======================================================================================*/
/* Constructor - initializes the 2D image and allocates a space according to alloc type */
/* Before destructor, the SetFreeOnExit(true) must be set to free the resources	  */
/*======================================================================================*/
/*DataDescriptor::DataDescriptor( unsigned int width, unsigned int height, DATATYPE elementType, ALLOC allocType)
{
Init(width, height, elementType, allocType);
}*/
   
/*======================================================================================*/
/* Constructor - initializes the 2D image and allocates a space according to alloc type with specified element size */
/* Before destructor, the SetFreeOnExit(true) must be set to free the resources         */
/*======================================================================================*/
DataDescriptor::DataDescriptor(unsigned int width, unsigned int height, DATATYPE elementType, unsigned int XSize, unsigned int YSize, unsigned int dimensions, ALLOC allocType)
{
	Init(width, height, elementType, XSize, YSize, dimensions, allocType);
}
  
/*======================================================================================*/
/* Constructor - initializes the 1D image and allocates a space according to alloc type */
/* Before destructor, the SetFreeOnExit(true) must be set to free the resources	  */
/*======================================================================================*/
DataDescriptor::DataDescriptor(unsigned int size, DATATYPE elementType, unsigned int dimensions, ALLOC allocType)
{
	Init(size, elementType, dimensions, allocType);
}
/* 
Inits a reference to the input's roi
*/
DataDescriptor::DataDescriptor(DataDescriptor & original)
{
	InitROI(original);
}
  
/*======================================================================================*/
/* After constructor init - initializes the 2D image with existing dataPtr 		  */
/* Before destructor, the SetFreeOnExit(true) must be set to free the resource	  */
/*======================================================================================*/
void DataDescriptor::Init(unsigned int width, unsigned int height, void *dataPtr, DATATYPE elementType, unsigned int dimensions, ALLOC allocType)
  {  
	this->pData		= dataPtr;
	pDataPhys		= 0;
    Width           = width;
    Height          = height;
    AllocationType  = allocType;
    
	origPData = pData;
	origPDataPhys = pDataPhys;
	OrigWidth = Width;
	OrigHeight = Height;


    ElementDataType = elementType;
    ElementDimX     = 1;
    ElementDimY     = 1;
    
    DataSize        = ReturnElementSize(elementType);
	Span			= width * DataSize * ElementDimX * ElementDimY;
	SpanRow         = Span / ElementDimY;
    Dim             = dimensions;
    DimOffset       = Width*Height*DataSize*ElementDimX*ElementDimY;
    
    ROI[_roiLeft]   = 0;
    ROI[_roiTop]    = 0;
    ROI[_roiWidth]	= Width;
    ROI[_roiHeight] = Height;
    
    FreeOnExit      = false;
  }
  
void DataDescriptor::InitManual(unsigned int  width, unsigned int  height, void *dataVirtPtr, void *dataHwPtr, DATATYPE elementType, unsigned int  XSize, unsigned int  YSize, unsigned int  Dimensions, ALLOC allocType)
  {
    pData           = dataVirtPtr;
    pDataPhys       = dataHwPtr;
    Width           = width;
    Height          = height;
    AllocationType  = allocType;
    
	origPData = pData;
	origPDataPhys = pDataPhys;
	OrigWidth = Width;
	OrigHeight = Height;


    ElementDataType = elementType;
    ElementDimX     = XSize;
    ElementDimY     = YSize;
    
    DataSize        = ReturnElementSize(elementType);
	Span			= width * DataSize * ElementDimX * ElementDimY;
	SpanRow			= Span / ElementDimY;
    Dim             = Dimensions;
    DimOffset       = Width*Height*DataSize*ElementDimX*ElementDimY;
    

	ROI[_roiLeft]   = 0;
    ROI[_roiTop]    = 0;
    ROI[_roiWidth]	= Width;
    ROI[_roiHeight] = Height;

    FreeOnExit      = false;
  }
  /*======================================================================================*/
  /* After constructor init - initializes the 1D image with existing dataPtr 		  */
  /* Before destructor, the SetFreeOnExit(true) must be set to free the resource	  */
  /*======================================================================================*/
void DataDescriptor::Init(unsigned int size, DATATYPE elementType, void *dataPtr, unsigned int dimensions, ALLOC allocType)
  {
	pData = dataPtr;
	pDataPhys = 0;
    Width           = size;
    Height          = 1;
    AllocationType  = allocType;
	origPData = pData;
	origPDataPhys = pDataPhys;
	OrigWidth = Width;
	OrigHeight = Height;


    ElementDataType = elementType;
    ElementDimX     = 1;
    ElementDimY     = 1;

    DataSize        = ReturnElementSize(elementType);
    Span            = size * DataSize * ElementDimX * ElementDimY;
    SpanRow         = Span / ElementDimY;
	Dim				= dimensions;
	DimOffset		= Width*Height*DataSize*ElementDimX*ElementDimY;

	ROI[_roiLeft]   = 0;
    ROI[_roiTop]    = 0;
    ROI[_roiWidth]	= Width;
    ROI[_roiHeight] = Height;

    FreeOnExit      = false;
  }
  
void DataDescriptor::InitManual(unsigned int size, void *dataVirtPtr, void *dataHwPtr, DATATYPE elementType, unsigned int XSize, unsigned int YSize, unsigned int Dimensions, ALLOC allocType)
  {
    pData           = dataVirtPtr;
    pDataPhys       = dataHwPtr;
    Width           = size;
    Height          = 1;
    AllocationType  = allocType;
	origPData = pData;
	origPDataPhys = pDataPhys;
	OrigWidth = Width;
	OrigHeight = Height;


    ElementDataType = elementType;
    ElementDimX     = XSize;
    ElementDimY     = YSize;

    DataSize        = ReturnElementSize(elementType);
    Span            = size * DataSize * ElementDimX * ElementDimY;
    SpanRow         = Span / ElementDimY;
    Dim             = Dimensions;
    DimOffset       = Width*Height*DataSize*ElementDimX*ElementDimY;
    

	ROI[_roiLeft]   = 0;
    ROI[_roiTop]    = 0;
    ROI[_roiWidth]	= Width;
    ROI[_roiHeight] = Height;

    FreeOnExit      = false;
  }
  
  /*==================================================================================================*/
  /* After constructor init - initializes the 1D image and allocates a space according to alloc type  */
  /* Before destructor, the SetFreeOnExit(true) must be set to free the resource		      */
  /*==================================================================================================*/
void DataDescriptor::Init(unsigned int size, DATATYPE elementType, unsigned int dimensions, ALLOC allocType)
{
    DataSize        = ReturnElementSize(elementType);
	pData			= (void*)new uint8_t[size*DataSize*dimensions];
	pDataPhys		= 0;
    Width           = size;
    Height          = 1;
    AllocationType  = allocType;
	origPData = pData;
	origPDataPhys = pDataPhys;
	OrigWidth = Width;
	OrigHeight = Height;


    ElementDataType = elementType;
    ElementDimX     = 1;
    ElementDimY     = 1;
    
    Span            = size * DataSize * ElementDimX * ElementDimY;
    SpanRow         = Span / ElementDimY;
    Dim             = dimensions;
    DimOffset       = Width*Height*DataSize*ElementDimX*ElementDimY;
    
    ROI[_roiLeft]   = 0;
    ROI[_roiTop]    = 0;
    ROI[_roiWidth]	= Width;
    ROI[_roiHeight] = Height;
    
    FreeOnExit      = false;
  }
  
  /*======================================================================================*/
  /* After constructor init - initializes the 2D image and allocates a space according to alloc type with specified element size */
  /* Before destructor, the SetFreeOnExit(true) must be set to free the resources         */
  /*======================================================================================*/
void DataDescriptor::Init(unsigned int width, unsigned int height, DATATYPE elementType, unsigned int XSize, unsigned int YSize, unsigned int dimensions, ALLOC allocType)
    {
    DataSize        = ReturnElementSize(elementType);
	pData			= (void*)new uint8_t[width*height*DataSize*XSize*YSize*dimensions];
	pDataPhys		= 0;
    Width           = width;
    Height          = height;
    AllocationType  = allocType;
	origPData = pData;
	origPDataPhys = pDataPhys;
	OrigWidth = Width;
	OrigHeight = Height;


    ElementDataType = elementType;
    ElementDimX     = XSize;
    ElementDimY     = YSize;    
    Dim = dimensions;
    DimOffset       = Width*Height*DataSize*ElementDimX*ElementDimY;

	Span			= width * DataSize * ElementDimX * ElementDimY;
	SpanRow			= Span / ElementDimY;

	ROI[_roiLeft]   = 0;
    ROI[_roiTop]    = 0;
    ROI[_roiWidth]	= Width;
    ROI[_roiHeight] = Height;

    FreeOnExit      = false;
  }
  

/** 
 * Inits a reference to the input's roi... No data is copied, but ptr to the data elements begins at ROI.top_left
*/
  void DataDescriptor::InitROI(DataDescriptor &original)
  {
	pData = (unsigned char *)original.pData + original.ROI[_roiTop] * original.Span + original.ROI[_roiLeft]; //TODO: is it not to be multibplied with original.ElementDimX?
	pDataPhys = (unsigned char *)original.pDataPhys + original.ROI[_roiTop] * original.Span + original.ROI[_roiLeft];
    
    Width           = original.ROI[_roiWidth]; // TODO: This could be buggy it is the margin at the right of the ROI
    Height          = original.ROI[_roiHeight];

	origPData = original.origPData;
	origPDataPhys = original.origPDataPhys;
	OrigWidth = original.OrigWidth;
	OrigHeight = original.OrigHeight;


    AllocationType  = original.AllocationType;
	
    ElementDataType = original.ElementDataType;
    ElementDimX     = original.ElementDimX;
    ElementDimY     = original.ElementDimY;

    DataSize        = original.DataSize;
    Span            = original.Span;
    SpanRow         = Span / ElementDimY;
    Dim             = original.Dim;
    DimOffset       = original.DimOffset;


	ROI[_roiLeft]   = 0;
    ROI[_roiTop]    = 0;
    ROI[_roiWidth]	= Width;
    ROI[_roiHeight] = Height;

    FreeOnExit      = false;
}
  
/*===============================================================================================*/
/* Destructor - destructs the image and free the resources if FreeOnExit is specified to be true */
/* Before destructor of the last copy, the SetFreeOnExit(true) must be set to free the resources */
/*===============================================================================================*/
DataDescriptor::~DataDescriptor()
{
    ClearROI();
    if (FreeOnExit && pData != NULL)
    {
		delete[] (uint8_t*)pData;
		pData = NULL;
    }
}
  
/*==============================================================================*/
/* Sets the ROI to the specified value					  */
/*==============================================================================*/
void 	DataDescriptor::SetROI(unsigned int roi[4])
{
    if (roi[_roiLeft] < Width &&
        roi[_roiLeft] + roi[_roiWidth] < Width &&
        roi[_roiTop] < Height &&
        roi[_roiTop] + roi[_roiHeight] < Height)
    {
    }
    else
    {
      printf("SetROI(...) -> The ROI does not fall within the specified parent data region ");
      return;
    }
    
    ROI[_roiLeft]   = roi[_roiLeft];
    ROI[_roiTop]    = roi[_roiTop];
    ROI[_roiWidth]  = roi[_roiWidth];
    ROI[_roiHeight] = roi[_roiHeight];

	pData = (unsigned char *) pData + ROI[_roiTop] * Span + ROI[_roiLeft]; //TODO: is it not to be multibplied with ElementDimX?
	pDataPhys = (unsigned char *)pDataPhys + ROI[_roiTop] * Span + ROI[_roiLeft];

	Width = ROI[_roiWidth]; // TODO: This could be buggy it is the margin at the right of the ROI
	Height = ROI[_roiHeight];

}
  
/*==============================================================================*/
/* Sets the ROI to the specified value					  */
/*==============================================================================*/
void 	DataDescriptor::ClearROI()
{
	ROI[_roiLeft]   = 0;
    ROI[_roiTop]    = 0;
    ROI[_roiWidth]  = OrigWidth;
    ROI[_roiHeight] = OrigHeight;

	pData = origPData;
	pDataPhys = origPDataPhys;
	
	Width = OrigWidth;
	Height = OrigHeight;
}
  
/*==============================================================================*/
/* Sets the ROI to the specified value					  */
/*==============================================================================*/
void 	DataDescriptor::SetROI(unsigned int left, unsigned int top, unsigned int width, unsigned int height)
{
    if (left < Width &&
        left + width < Width &&
        top < Height &&
        top + height < Height)
	{
	}
    else
    {
      printf("SetROI(...) -> The ROI does not fall within the specified parent data region ");
      return;
    }
    
	ROI[_roiLeft]   = left;
    ROI[_roiTop]    = top;
    ROI[_roiWidth]	= width;
    ROI[_roiHeight] = height;

	pData = (unsigned char *)pData + ROI[_roiTop] * Span + ROI[_roiLeft]; //TODO: is it not to be multibplied with ElementDimX?
	pDataPhys = (unsigned char *)pDataPhys + ROI[_roiTop] * Span + ROI[_roiLeft];

	Width = ROI[_roiWidth]; // TODO: This could be buggy it is the margin at the right of the ROI
	Height = ROI[_roiHeight];

}
   
/*=======================================================================================*/
/* Sets FreeOnExit flag to value. If the value is true, the data are freed on destructor */
/*=======================================================================================*/
void 	DataDescriptor::SetFreeOnExit(bool val)
{
	FreeOnExit = val;
}
  
/*==============================================================================*/
/* Returns a virtual data pointer to the pixel array				  */
/*==============================================================================*/
void* DataDescriptor::GetDataPtr(unsigned int dimension)
{ 
	if (dimension >= Dim) 
		return NULL;
	return ((unsigned char*)pData + (DimOffset * dimension));
}
  
/*==============================================================================*/
/* Returns a physical data pointer to the pixel array				  */
/*==============================================================================*/
void* DataDescriptor::GetDataPtrPhys(unsigned int dimension)
{
	if (dimension >= this->Dim) 
		return NULL;
	return ((unsigned char *)pDataPhys + (DimOffset * dimension));
}
  
/*==============================================================================*/
/* Returns the data type of the DataDescriptor							  */
/*==============================================================================*/
DATATYPE DataDescriptor::GetElementDataType() const
{
	return ElementDataType;
}
    
/*==============================================================================*/
/* Returns the pixel width							  */
/*==============================================================================*/
unsigned int DataDescriptor::GetElementDimX() const
{
	return ElementDimX;
}
   
/*==============================================================================*/
/* Returns the pixel height							  */
/*==============================================================================*/
unsigned int DataDescriptor::GetElementDimY() const
{
	return ElementDimY;
}
  
/*==============================================================================*/
/* Returns the width of the image in pixels					  */
/*==============================================================================*/
unsigned int DataDescriptor::GetWidth() const
{
	return Width;
}
  
/*==============================================================================*/
/* Returns the height of the image in pixels					  */
/*==============================================================================*/
unsigned int DataDescriptor::GetHeight() const
{
	return Height;
}
  
/*==============================================================================*/
/* Returns the size of one line of pixels in bytes                	    */
/* (pixels in line * pixel width * pixel height * data type size)      */
/*==============================================================================*/
unsigned int DataDescriptor::GetSpan() const
{
	return Span;
}

/*==============================================================================*/
/* Returns a number of dimensions (parallel images) held by this structure		  */
/*==============================================================================*/
unsigned int DataDescriptor::GetDimensions() const
{
	return Dim;
}
/*==============================================================================*/
/* Returns the size of one row of pixels in bytes divided by pixel height in bytes.*/
/* This value can be used for jumping to the next row of the current pixel.*/
/* (pixels in line * pixel width * data type size)                            */
/*==============================================================================*/
unsigned int DataDescriptor::GetSpanRow() const
{
	return SpanRow;
}
  
/*==============================================================================*/
/* Returns the size of one line of pixels using the data type of the DataDescriptor (8-bit, 16-bit or 32-bit) as a unit*/
/* (pixels in line * pixel width * pixel height)                              */
/*==============================================================================*/
unsigned int DataDescriptor::GetStride_ElementDataType() const
{
	return Span / DataSize;
}
  
/*================================================================================*/
/* Returns the size of one line of pixels using the pixel width multiplied by data type size of the DataDescriptor (8-bit, 16-bit or 32-bit) as a unit*/
/* (pixels in line * pixel width * pixel height)                              */
/*================================================================================*/
unsigned int DataDescriptor::GetStride_ElementX() const
{
	return Span / (DataSize * ElementDimX);
}
  
/*==================================================================================================*/
/* Returns the size of one line of pixels using the pixel size (width * height) multiplied by data type size of the DataDescriptor (8-bit, 16-bit or 32-bit) as a unit*/
/* (pixels in line) */
/*==================================================================================================*/
unsigned int DataDescriptor::GetStride_Element() const
{    
	return Span / (DataSize * ElementDimY * ElementDimX);
}
  
/*==============================================================================*/
/* Returns a ROI left value							  */
/*==============================================================================*/
unsigned int DataDescriptor::GetRoiInfoL() const
{
	return ROI[_roiLeft];
}
  
/*==============================================================================*/
/* Returns a ROI right value							  */
/*==============================================================================*/
unsigned int DataDescriptor::GetRoiInfoR() const
{
	return Width - ROI[_roiLeft] - ROI[_roiWidth]; 
}
  
/*==============================================================================*/
/* Returns a ROI top value							  */
/*==============================================================================*/
unsigned int DataDescriptor::GetRoiInfoT() const
{
	return ROI[_roiTop];
}
  
/*==============================================================================*/
/* Returns a ROI bottom value							  */
/*==============================================================================*/
unsigned int DataDescriptor::GetRoiInfoB() const
{
	return Height - ROI[_roiTop] - ROI[_roiHeight]; 
}
  
/*==============================================================================*/
/* Comparison operator							  */
/*==============================================================================*/
bool DataDescriptor::operator==(DataDescriptor const& second)
{ 
    //if the comparison makes sense
    if (Width  == second.Width && Height == second.Height && ElementDataType == second.ElementDataType && ElementDimX == second.ElementDimX && ElementDimY == second.ElementDimY && Dim == second.Dim)
    {
		unsigned int width = Width * ElementDimX * DataSize;
		unsigned int height = Height * ElementDimY;
		unsigned char* pDataA = (unsigned char*)pData;
		unsigned char* pDataB = (unsigned char*)second.pData;
		unsigned int SpanA = SpanRow;
		unsigned int SpanB = second.SpanRow;
 
		for (unsigned int dim = 0; dim < Dim; ++dim) {
			for (unsigned int i = 0; i < height; ++i)
				for (unsigned int j = 0; j < width; ++j)
				{
					if (*(pDataA + (DimOffset*dim) + ((i)* SpanA + (j))) != *(pDataB + (second.DimOffset*dim) + ((i)* SpanB + (j)))) 
						return false;
				}
		}
    }
    else
      return false;
   
    return true;
}

/*==============================================================================*/
/* Fills the image with random values						  */
/*==============================================================================*/
void DataDescriptor::FillRandom(unsigned int seed)
{
    if (seed != 0)
    {
      srand(seed);
    }
    else
    {
    srand((unsigned int)time(NULL));
    }

	unsigned int width = Width*ElementDimX*DataSize;
	unsigned int height = Height * ElementDimY;
    
	unsigned char* lpData = (unsigned char*)pData;

	for (unsigned int i = 0; i < height; ++i) {
		for (unsigned int j = 0; j < width; j++) {
			for (unsigned int k = 0; k < ElementDimY; k++) {
				unsigned char value = rand() % 256;
				for (unsigned int dim = 0; dim < Dim; ++dim) {
					*(lpData + (DimOffset*dim) + ((i)* SpanRow + (j))) = rand() % 256;
				}
			 }
		  }
	  }
}
  
void DataDescriptor::FillRandomParallel(unsigned int seed)
{

    if (seed != 0)
    {
      srand(seed);
    }
    else
    {
		srand((unsigned int)time(NULL));
    }

	unsigned int width = Width*ElementDimX*DataSize;
	unsigned int height = Height * ElementDimY;
    
	unsigned char* lpData = (unsigned char*)pData;
	for (unsigned int i = 0; i < height; ++i) {
		for (unsigned int j = 0; j < width; j++) {
			for (unsigned int k = 0; k < ElementDimY; k++) {
				unsigned char value = rand() % 256;
				for (unsigned int dim = 0; dim < Dim; ++dim) {
					*(lpData + (DimOffset*dim) + ((i)* SpanRow + (j))) = value;
				}
			}
          }
      }
}
  
void DataDescriptor::FillValue(unsigned char value)
{

	unsigned int width = Width*ElementDimX*DataSize;
	unsigned int height = Height * ElementDimY;
    
	unsigned char* lpData = (unsigned char*)pData;
	for (unsigned int dim = 0; dim < Dim; ++dim) {
		for (unsigned int i = 0; i < height; ++i) {
			for (unsigned int j = 0; j < width; j++) {
				for (unsigned int k = 0; k < ElementDimY; k++) {
					*(lpData + (DimOffset*dim) + ((i)* SpanRow + (j))) = value;
				}
			}
		}
	}
}
  
  
/*==============================================================================*/
/* Check if the data are present and allocated				  */
/*==============================================================================*/
bool DataDescriptor::IsOK()
{
    if (pData != NULL) return true;
    else return false;
}
  
/*==============================================================================*/
/* Get/Set operator															   */
/*==============================================================================*/
void *DataDescriptor::operator()(unsigned int x, unsigned int y, unsigned int elx, unsigned int ely, unsigned int dim)
{
	return &((unsigned char *)pData + (dim*DimOffset))[y * Span + SpanRow*ely + (x*DataSize*(ElementDimX)) + elx*DataSize];
}
