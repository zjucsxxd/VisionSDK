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
* \file APU_DataDescriptor.cpp
* \brief APU_lib I/O data descriptor
* \author Igor Aleksandrowicz, Rostislav Hulik
* \version
* \date 10-February-2014
****************************************************************************/
#ifndef _APU_DATADESCRIPTOR__H
#define _APU_DATADESCRIPTOR__H

#include <cstdlib>

namespace APEX2
{

/*==============================================================================*/

	/**
	- * Enum for specification of allocation of the image
	- */
typedef enum
{
	ALLOC_VIRT,
	ALLOC_CONTIGUOUS,
	ALLOC_CONTIGUOUS_CMA,
	ALLOC_UNKNOWN
} ALLOC;


/**
 * Enum for specification of data type in image
 */
typedef enum
{
   DATATYPE_08U = 0, ///<8-bit unsigned
   DATATYPE_08S = 1, ///<8-bit signed
   DATATYPE_16U = 2, ///<16-bit unsigned
   DATATYPE_16S = 3, ///<16-bit signed
   DATATYPE_32U = 4, ///<32-bit unsigned
   DATATYPE_32S = 5  ///<32-bit signed
} DATATYPE;

/**
* Enum for specification of the roi corners
*/
typedef enum
{
	_roiLeft = 0,
	_roiWidth = 1,
	_roiTop = 2,
	_roiHeight = 3
} ROI_CORNERS;


/**
* Class encapsulating a 1D or 2D image for ACF processing
*/
class DataDescriptor
{
public:
  /**
  * Constructor - creates an empty instance of the class
  */
  DataDescriptor();

  /**
  * OK
  */
  //DataDescriptor(DataDescriptor &copy);

  /**
  * Constructor - initializes the 2D image and allocates a space according to alloc type
  * Before destructor, the SetFreeOnExit(true) must be set to free the resources
  * @param width Width of the image (in pixels)
  * @param height Height of the image (in pixels)
  * @param elementType Type of the pixel
  * @param allocType Type of allocation
  */
  //DataDescriptor(unsigned int width, unsigned int height, DATATYPE elementType, ALLOC allocType = ALLOC_CONTIGUOUS);

  /**
  * Constructor - initializes the 2D image and allocates a space according to alloc type with specified element size
  * Before destructor, the SetFreeOnExit(true) must be set to free the resources
  * @param width Width of the image (in pixels)
  * @param height Height of the image (in pixels)
  * @param elementType Type of the pixel
  * @param XSize Width of the pixel (in data types)
  * @param YSize Height of the pixel (in data types)
  * @param dimensions The vector/image/volume dimension (i.e. 1,2,,3)
  * @param allocType Type of allocation
  */
  DataDescriptor(unsigned int width, unsigned int height, DATATYPE elementType, unsigned int XSize = 1, unsigned int YSize = 1, unsigned int dimensions = 1, ALLOC allocType = ALLOC_CONTIGUOUS);

  /**
  * Constructor - initializes the 1D image and allocates a space according to alloc type
  * Before destructor, the SetFreeOnExit(true) must be set to free the resources
  * @param size The size for allocation
  * @param elementType Type of the pixel
  * @param dimensions The vector/image/volume dimension (i.e. 1,2,,3)
  * @param allocType Type of allocation
  */
  DataDescriptor(unsigned int size, DATATYPE elementType, unsigned int dimensions = 1, ALLOC allocType = ALLOC_CONTIGUOUS);


  /** Inits a reference to the input's roi... No data is copied, but ptr to the data elements begins at ROI.top_left
  */
  DataDescriptor(DataDescriptor & original);

  /**
  * Destructor - destructs the image and free the resources if FreeOnExit is specified to be true
  * Before destructor of the last copy, the SetFreeOnExit(true) must be set to free the resources
  */
  ~DataDescriptor();

  /**
  * After constructor init - initializes the 2D image with existing data
  * Before destructor, the SetFreeOnExit(true) must be set to free the resources
  * @param width Width of the image (in pixels)
  * @param height Height of the image (in pixels)
  * @param dataPtr Pointer to the data array
  * @param elementType Type of the pixel
  * @param dimensions The vector/image/volume dimension (i.e. 1,2,,3)
  * @param allocType Type of allocation
  */
  void Init(unsigned int width, unsigned int height, void *dataPtr, DATATYPE elementType, unsigned int dimensions = 1, ALLOC allocType = ALLOC_UNKNOWN);
  void InitManual(unsigned int width, unsigned int height, void *dataVirtPtr, void *dataHwPtr, DATATYPE elementType, unsigned int XSize=1, unsigned int YSize=1, unsigned int Dimensions = 1, ALLOC allocType = ALLOC_UNKNOWN);

  /**
  * After constructor init - initializes the 1D image with existing data
  * Before destructor, the SetFreeOnExit(true) must be set to free the resources
  * @param size Size of the image
  * @param dataPtr Pointer to the data array
  * @param elementType Type of the pixel
  * @param dimensions The vector/image/volume dimension (i.e. 1,2,,3)
  * @param allocType Type of allocation
  */
  void Init(unsigned int size, DATATYPE elementType, void *dataPtr, unsigned int dimensions, ALLOC allocType = ALLOC_UNKNOWN);
  void InitManual(unsigned int size, void *dataVirtPtr, void *dataHwPtr, DATATYPE elementType, unsigned intXSize, unsigned int YSize, unsigned int Dimensions, ALLOC allocType = ALLOC_UNKNOWN);
  /**
  * After constructor init - initializes the 2D image and allocates a space according to alloc type
  * Before destructor, the SetFreeOnExit(true) must be set to free the resources
  * @param width Width of the image (in pixels)
  * @param height Height of the image (in pixels)
  * @param elementType Type of the pixel
  * @param allocType Type of allocation
  */
  //void Init(unsigned int width, unsigned int height, DATATYPE elementType, ALLOC allocType = ALLOC_CONTIGUOUS);

  /**
  * After constructor init - initializes the 2D image and allocates a space according to alloc type with specified element size
  * Before destructor, the SetFreeOnExit(true) must be set to free the resources
  * @param width Width of the image (in pixels)
  * @param height Height of the image (in pixels)
  * @param elementType Type of the pixel
  * @param XSize Width of the pixel (in data types)
  * @param YSize Height of the pixel (in data types)
  * @param dimensions The vector/image/volume dimension (i.e. 1,2,,3)
  * @param allocType Type of allocation
  */
  void Init(unsigned int width, unsigned int height, DATATYPE elementType, unsigned int XSize = 1, unsigned int YSize = 1, unsigned int dimensions = 1, ALLOC allocType = ALLOC_UNKNOWN);

  /**
  * After constructor init - initializes the 1D image and allocates a space according to alloc type
  * Before destructor, the SetFreeOnExit(true) must be set to free the resources
  * @param size The size for allocation
  * @param elementType Type of the pixel
  * @param dimensions The vector/image/volume dimension (i.e. 1,2,,3)
  * @param allocType Type of allocation
  */
  void Init(unsigned int size, DATATYPE elementType, unsigned int dimensions = 1, ALLOC allocType = ALLOC_UNKNOWN);


  /** Inits a reference to the input's roi... No data is copied, but ptr to the data elements begins at ROI.top_left
  */
  void InitROI(DataDescriptor &original);

  /**
  * Sets the ROI to the specified value
  * @param roi ROI to be set, the array of (left, right, top, bottom)
  */
  void 	SetROI(unsigned int roi[4]);

  /**
  * Sets the ROI to the specified value
  */
  void 	ClearROI();

  /**
  * Sets the ROI to the specified value
  * @param left Left coordinate
  * @param top Top coordinate
  * @param width Width of the roi
  * @param height Height
  */
  void 	SetROI(unsigned int left, unsigned int top, unsigned int width, unsigned int height);

  /**
  * Sets FreeOnExit flag to value. If the value is true, the data are freed on destructor
  * @param val Value of FreeOnExit to be set
  */
  void 	SetFreeOnExit(bool val);

  /**
  * Returns the virtual data pointer to the pixel array
  * @return Virtual data pointer
  */
  void* GetDataPtr(unsigned int dimension = 0);

  /**
  * Returns the physical data pointer to the pixel array
  * @return Physical data pointer
  */
  void* GetDataPtrPhys(unsigned int dimension = 0);

  /**
  * Returns the data type of the DataDescriptor
  * @return Data type of the pixel
  */
  DATATYPE GetElementDataType() const;

  /**
  * Returns the pixel width
  * @return Pixel width
  */
  unsigned int GetElementDimX() const;

  /**
  * Returns the pixel height
  * @return Pixel height
  */
  unsigned int GetElementDimY() const;

  /**
  * Returns the width of the image in pixels
  * @return Width of the image in pixels
  */
  unsigned int GetWidth() const;

  /**
  * Returns the height of the image in pixels
  * @return Height of the image in pixels
  */
  unsigned int GetHeight() const;


  /*
   * Span and stride functions:
   * Here "Span" is always in bytes, "Stride" can be either in DataDescriptor's base data type.
   * "Line" refers to a line of pixels whereas "row" refers to a row of bytes inside the line of pixels.
   * e.g. for 8-bit base type, pixel size 3x3 and 100-pixel wide image, line has 100 pixels (900 bytes) whereas row has 300 bytes.
  /*

  /**
  * Returns the size of one line of pixels in bytes.
  * (pixels in line * pixel width * pixel height * data type size)
  * @return see the description
  */
  unsigned int GetSpan() const;

  /**
  * Returns a number of dimensions (parallel images) held by this structure
  * @return Number of dimensions
  */
  unsigned int GetDimensions() const;


  /**
  * Returns the size of one row of pixels in bytes divided by pixel height in bytes.
  * This value can be used for jumping to the next row of the current pixel.
  * (pixels in line * pixel width * data type size)
  * @return see the description
  */
  unsigned int GetSpanRow() const;

  /**
  * Returns the size of one line of pixels using the data type of the DataDescriptor (8-bit, 16-bit or 32-bit) as a unit.
  * (pixels in line * pixel width * pixel height)
  * @return see the description
  */
  unsigned int GetStride_ElementDataType() const;

  /**
  * Returns the size of one line of pixels using the pixel width multiplied by data type size of the DataDescriptor (8-bit, 16-bit or 32-bit) as a unit.
  * (pixels in line * pixel width * pixel height)
  * @return see the description
  */
  unsigned int GetStride_ElementX() const;

  /**
  * Returns the size of one line of pixels using the pixel size (width * height) multiplied by data type size of the DataDescriptor (8-bit, 16-bit or 32-bit) as a unit.
  * (pixels in line)
  * @return see the description
  */
  unsigned int GetStride_Element() const;

  /**
  * Comparison operator
  * @return True if images are equal
  */
  bool operator==(DataDescriptor const& second);

  /**
  * Get/Set operator
  * @return Value
  */
  void *operator()(unsigned int x, unsigned int y, unsigned int elx = 0, unsigned int ely = 0, unsigned int dim = 0);

  /**
  * Fills the image with random values
  * @param seed Optional random number generator seed
  */
  void FillRandom(unsigned int seed = 0);


  /**
  * Fills the image with random values to all dimensions the same value
  * @param seed Optional random number generator seed
  */
  void FillRandomParallel(unsigned int seed = 0);

  /**
  * Fills the image with specified values
  * @param value Value to be set on all elements
  */
  void FillValue(unsigned char value);

  /**
  * Returns a ROI left value
  * @return Left boundary of ROI
  */
  unsigned int GetRoiInfoL() const;

  /**
  * Returns a ROI right value
  * @return Right boundary of ROI
  */
  unsigned int GetRoiInfoR() const;

  /**
  * Returns a ROI top value
  * @return Top boundary of ROI
  */
  unsigned int GetRoiInfoT() const;

  /**
  * Returns a ROI bottom value
  * @return Bottom boundary of ROI
  */
  unsigned int GetRoiInfoB() const;

  /**
  * Returns a pixel width according to its type
  * @return Pixel data type
  */
  static unsigned int ReturnElementSize(DATATYPE type);

  /**
  * Check if the data are present and allocated
  * @return True if all is fine
  */
  bool IsOK();

private:
  /**
  * Pointer to data (virtual address)
  */
  void* 	pData;
  void*		origPData;

  /**
  * Pointer to data (physical address)
  */
  void* 	pDataPhys;
  void*		origPDataPhys;

  /**
  * Pixel data type
  */
  DATATYPE 	ElementDataType;

  /**
  * Allocation type (where are the data allocated from)
  */
  ALLOC 	AllocationType;

  /**
  * Pixel dimension in X
  */
  unsigned int 	ElementDimX;

  /**
  * Pixel dimension in Y
  */
  unsigned int 	ElementDimY;

  /**
  * Image width (in pixels)
  */
  unsigned int 	Width;

  /**
  * Image height (in pixels)
  */
  unsigned int 	Height;

  /**
  * Image width (in pixels)
  */
  unsigned int 	OrigWidth;

  /**
  * Image height (in pixels)
  */
  unsigned int 	OrigHeight;

  /**
  * Image span (in bytes)
  */
  unsigned int 	Span;

  /**
  * Image row span (one data type row) (in bytes)
  */
  unsigned int 	SpanRow;

  /**
  * Data type size
  */
  unsigned int 	DataSize;

  /**
  * Image ROI (left, right, top, bottom)
  */
  unsigned int 	ROI[4];

  /**
  * Dimension of array (i.e. can be 1,2 or 3
  */
  unsigned int Dim; 

  /**
  * Dimension offset where the second line or slice starts
  */
  unsigned int DimOffset;
  /**
  * If true, the data pointer is deallocated on destructor
  */
  bool FreeOnExit;
};

} /* namespace icp */



#endif // _APU_DATADESCRIPTOR__H
