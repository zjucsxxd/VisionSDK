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

#ifndef _ICP_CONTIGDATADESC
#define _ICP_CONTIGDATADESC

#include <icp_datatype.h>
#include <stdint.h>

#define ICP_CONTIGDATADESC_MIN_BYTE_ALIGNMENT 16 //choose from 4/8/16/32/64/128

/////////////////////////////////////////////////////////////////////////
/// \addtogroup icp_contigdatadesc ICP_ContigDataDesc
/// @{

//////////////////////////////////////////////////////////////////////////
/// ICP_ContigDataDesc is a container class designed to encapsulate
/// a contiguous region of data.  It does not allocate or deallocate
/// memory; it simply standardizes the representation of a contiguous
/// memory region so it can be used by framework level services.
//////////////////////////////////////////////////////////////////////////
class ICP_ContigDataDesc
{
public:

   ICP_ContigDataDesc();

   /////////////////////////////////////////////////////////////////////////
   /// \par Description
   /// Constructor that initializes a contiguous 2D data region.  Note that
   /// the data region must be physically contiguous in memory (not just
   /// contiguous from the OS point of view).
   ///
   /// Note that an 'element' (as referred to below) simply represents the
   /// smallest meaningful data granularity.
   ///
   /// For example, if an element is a single 32-bit signed value:
   /// \code{.cpp}
   /// lElementDataType = ICP_DATATYPE_32S
   /// lElementDimX     = 1
   /// lElementDimY     = 1
   /// \endcode
   ///
   /// If an element is an array of 4 8-bit unsigned values:
   /// \code{.cpp}
   /// lElementDataType = ICP_DATATYPE_08U
   /// lElementDimX     = 4
   /// lElementDimY     = 1
   /// \endcode
   ///
   /// \param[in] lpData
   /// Pointer to contiguous data region.
   /// \param[in] lpDataPhys
   /// Physical pointer to contiguous data region (for HW use).
   /// \param[in] lWidth
   /// Width (in elements) of the contiguous data region.
   /// \param[in] lHeight
   /// Height (in elements) of the contiguous data region.
   /// \param[in] lSpan
   /// Span is defined as the number of bytes required to jump from one
   /// line of bytes in memory to the 'next' line of bytes in memory.  Note
   /// that span must be divisible by N where
   /// N = RetIcpDataTypeSizeInBytes (lElementDataType).
   /// \param[in] lElementDataType
   /// The data type associated with an 'element' (i.e. the smallest unit of data)
   /// \param[in] lElementDimX
   /// The 'x' dimension (i.e. width) of an element in units of "lElementDataType"
   /// \param[in] lElementDimY
   /// The 'y' dimension (i.e. height) of an element in units of "lElementDataType"
   /// \param[in] lRoiInfoL,lRoiInfoR,lRoiInfoT,lRoiInfoB
   /// Indicate if edges should be padded with source data (instead of generated
   /// padding).  This is useful when the input is a 'region of interest' and you want
   /// input edge padding to come from the source data. For each edge, specify the
   /// number of elements available for padding (if any).  These all default to 0.
   /////////////////////////////////////////////////////////////////////////
   ICP_ContigDataDesc(void* const lpData,
                      void* const lpDataPhys,
                      int32_t lWidth,
                      int32_t lHeight,
                      int32_t lSpan,
                      ICP_DATATYPE lElementDataType,
                      int32_t lElementDimX,
                      int32_t lElementDimY,
                      int32_t lRoiInfoL = 0,
                      int32_t lRoiInfoR = 0,
                      int32_t lRoiInfoT = 0,
                      int32_t lRoiInfoB = 0);

   /////////////////////////////////////////////////////////////////////////
   /// \par Description
   /// Constructor that initializes a contiguous 1D data region.  Note that
   /// the data region must be physically contiguous in memory (not just
   /// contiguous from the OS point of view).
   ///
   /// \param[in] lpData
   /// Pointer to contiguous data region.
   /// \param[in] lpDataPhys
   /// Physical pointer to contiguous data region (for HW use).
   /// \param[in] lSize
   /// Size (in elements) of the contiguous data region.
   /// \param[in] lElementDataType
   /// The data type associated with an 'element' (i.e. the smallest unit of data)
   /// \param[in] lElementDimX
   /// The 'x' dimension (i.e. width) of an element in units of "lElementDataType".
   /// It is assumed that the 'y' dimension of the element is 1.
   /////////////////////////////////////////////////////////////////////////
   ICP_ContigDataDesc(void* const lpData,
                      void* const lpDataPhys,
                      int32_t lSize,
                      ICP_DATATYPE lElementDataType,
                      int32_t lElementDimX);

   /////////////////////////////////////////////////////////////////////////
   /// \par Description
   /// Initializes a contiguous 2D data region.  See the description of the
   /// 2D constructor for parameter details.
   /////////////////////////////////////////////////////////////////////////
   void Init2D (void* const lpData,
                void* const lpDataPhys,
                int32_t lWidth,
                int32_t lHeight,
                int32_t lSpan,
                ICP_DATATYPE lElementDataType,
                int32_t lElementDimX,
                int32_t lElementDimY,
                int32_t lRoiInfoL = 0,
                int32_t lRoiInfoR = 0,
                int32_t lRoiInfoT = 0,
                int32_t lRoiInfoB = 0);

   /////////////////////////////////////////////////////////////////////////
   /// Initializes a contiguous 2D data region as an ROI within the 'parent'
   /// region "lContigDataDesc"
   ///
   /// \param[in] lContigDataDesc
   /// Description of contiguous data region that 'contains' the ROI
   ///
   /// \param[in] lROI_XOffset
   /// The X offset of the top left corner of the ROI (relative to the top left
   /// corner of the region described by "lContigDataDesc").
   ///
   /// \param[in] lROI_YOffset
   /// The Y offset of the top left corner of the ROI (relative to the top left
   /// corner of the region described by "lContigDataDesc").
   ///
   /// \param[in] lROI_Width
   /// The width of the ROI.
   ///
   /// \param[in] lROI_Height
   /// The height of the ROI.
   ///
   /// \return
   /// 0 if successful, non-zero if an an error occurred.
   /////////////////////////////////////////////////////////////////////////
   int32_t Init2D_ROI(const ICP_ContigDataDesc& lContigDataDesc,
                      int32_t lROI_XOffset,
                      int32_t lROI_YOffset,
                      int32_t lROI_Width,
                      int32_t lROI_Height);

   /////////////////////////////////////////////////////////////////////////
   /// \par Description
   /// Initializes a contiguous 1D data region.  See the description of the
   /// 1D constructor for parameter details.
   /////////////////////////////////////////////////////////////////////////
   void Init1D (void* const lpData,
                void* const lpDataPhys,
                int32_t lSize,
                ICP_DATATYPE lElementDataType,
                int32_t lElementDimX);

   /////////////////////////////////////////////////////////////////////////
   /// \par Description
   /// Update the data pointers associated with the contiguous data region.
   ///
   /// \param[in] lpData
   /// Pointer to contiguous data region.
   /// \param[in] lpDataPhys
   /// Physical pointer to contiguous data region (for HW use).
   /////////////////////////////////////////////////////////////////////////
   void UpdatePtrs(void* const lpData,
                   void* const lpDataPhys);

   /////////////////////////////////////////////////////////////////////////
   /// \par Description
   /// Returns a void data pointer to the contiguous data region.
   ///
   /// \return
   /// A void data pointer to the contiguous data region.
   /////////////////////////////////////////////////////////////////////////
   void* RetDataPtr() const;

   /////////////////////////////////////////////////////////////////////////
   /// \par Description
   /// Returns a void 'physical' data pointer to the contiguous data region.
   ///
   /// \return
   /// A void 'physical' data pointer to the contiguous data region.
   /////////////////////////////////////////////////////////////////////////
   void* RetDataPtrPhys() const;

   /////////////////////////////////////////////////////////////////////////
   /// \par Description
   /// Returns the data type associated with the element.
   ///
   /// \return
   /// ICP_DATATYPE associated with the element.
   /////////////////////////////////////////////////////////////////////////
   ICP_DATATYPE RetElementDataType() const;

   /////////////////////////////////////////////////////////////////////////
   /// \par Description
   /// Returns the X dimension (i.e. width) of the element.
   ///
   /// \return
   /// The X dimension (i.e. width) of the element.
   /////////////////////////////////////////////////////////////////////////
   int32_t RetElementDimX() const;

   /////////////////////////////////////////////////////////////////////////
   /// \par Description
   /// Returns the Y dimension (i.e. height) of the element.
   ///
   /// \return
   /// The Y dimension (i.e. height) of the element.
   /////////////////////////////////////////////////////////////////////////
   int32_t RetElementDimY() const;

   /////////////////////////////////////////////////////////////////////////
   /// \par Description
   /// Returns the width of the data region (in elements).
   ///
   /// \return
   /// The width of the data region (in elements).
   /////////////////////////////////////////////////////////////////////////
   int32_t RetWidth() const;

   /////////////////////////////////////////////////////////////////////////
   /// \par Description
   /// Returns the height of the data region (in elements).
   ///
   /// \return
   /// The height of the data region (in elements).
   /////////////////////////////////////////////////////////////////////////
   int32_t RetHeight() const;

   /////////////////////////////////////////////////////////////////////////
   /// \par Description
   /// Returns the span of the data region (in bytes).  Span is defined as the
   /// number of bytes between vertically adjacent values in a 2D data region.
   ///
   /// \return
   /// The span of the data region (in units of bytes).
   /////////////////////////////////////////////////////////////////////////
   int32_t RetSpan() const;

   /////////////////////////////////////////////////////////////////////////
   /// \par Description
   /// Returns the stride of the data region in units of 'element data type'.
   /// Stride is defined as the number of 'units' between vertically adjacent
   /// values in a 2D data region.  In this case a unit = sizeof(element data type)
   /// (i.e. 8-bit = 1 byte, 16-bit = 2 bytes, 32-bit = 4 bytes).
   ///
   /// **NOTE: If the width of your data region is not equally divisible by
   ///         the aforementioned unit, the returned value of 'stride' is
   ///         undefined.
   ///
   /// \return
   /// The stride of the data region in units of 'element data type'.
   /////////////////////////////////////////////////////////////////////////
   int32_t RetStride_ElementDataType() const;

   /////////////////////////////////////////////////////////////////////////
   /// \par Description
   /// Returns the stride of the data region in units of 'elements' considering
   /// only the X dimension of the element.
   /// Stride is defined as the number of 'units' between vertically adjacent
   /// values in a 2D data region.  In this case a unit =
   /// sizeof(element data type)*(element dimension X)
   ///
   /// **NOTE: If the width of your data region is not equally divisible by
   ///         the aforementioned unit, the returned value of 'stride' is
   ///         undefined.
   ///
   /// \return
   /// The stride of the data region in units of 'elements' considering
   /// only the X dimension of the element.
   /////////////////////////////////////////////////////////////////////////
   int32_t RetStride_ElementX() const;

   /////////////////////////////////////////////////////////////////////////
   /// \par Description
   ///
   /// Equality operator.  Returns "true" if the data contained in "this"
   /// is equal to the data contained in "lCdd", otherwise returns
   /// "false".
   ///
   /// \param lCdd [input]
   /// Reference to a constant ICP_ContigDataDesc.
   ///
   /// \return
   /// "true" if data is the same, otherwise "false"
   /////////////////////////////////////////////////////////////////////////
   bool operator==(ICP_ContigDataDesc const& lCdd);

   void FillRandom(int32_t lSeedVal = 0);
   void FillZero();

   void E0Replicate(int32_t lPadSizeInE0L,
                    int32_t lPadSizeInE0R,
                    int32_t lPadSizeInE0T,
                    int32_t lPadSizeInE0B);

   int32_t RetRoiInfoL() const;
   int32_t RetRoiInfoR() const;
   int32_t RetRoiInfoT() const;
   int32_t RetRoiInfoB() const;

   int32_t DumpToFile(const char* lFilenameRoot);

private:

   void* mpData;     //for OS access
   void* mpDataPhys; //for HW access
   ICP_DATATYPE mElementDataType;
   int32_t mElementDimX;
   int32_t mElementDimY;
   int32_t mWidth;
   int32_t mHeight;
   int32_t mSpan;
   int32_t mRoiInfo[4];  //is there useful data beyond an 'edge'? (i.e. is this an ROI?)
                         //[numElementsLeft, numElementsRight, numElementsTop,  numElementsBot]

   int32_t VerifyPhysPtrAlignment();
};

/// @}

#endif //_ICP_CONTIGDATADESC
