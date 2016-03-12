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
#ifndef _ACF_PROCESS_APU_HPP
#define _ACF_PROCESS_APU_HPP

#include <acf_process.h>
#include <acf_process_portinfo_apu.h>
#include <icp_data.h>
#include <stdint.h>
#include <string>
#include <vector>

/// \addtogroup acf_apu_cfg ACF_APU_CFG
/// @{

/// ACF_APU_CFG - the various APU configurations a process may be run on
typedef enum _ACF_APU_CFG
{
   ACF_APU_CFG__DEFAULT,                 ///< APU0 with all CUs and all SMEM
   ACF_APU_CFG__APU_0_CU_0_63_SMEM_0_3,  ///< APU0 with CUs 0-63 and 128K SMEM
   ACF_APU_CFG__APU_0_CU_0_31_SMEM_0_1,  ///< APU0 with CUs 0-31 and 64K  SMEM
   ACF_APU_CFG__APU_1_CU_32_63_SMEM_2_3  ///< APU1 with CUs 32-63 and 64K  SMEM
} ACF_APU_CFG;

/// @}

//TODO: these types are COPIED FROM apu_hal.h.  apu_hal.h should not be included here - some cleanup is required.
#ifndef SEG_HOST_TYPE
typedef uint64_t  SEG_HOST_TYPE;
typedef uint32_t SEG_MEM_TYPE;
#endif
typedef SEG_HOST_TYPE LOAD_SEGMENT_t[4];


/////////////////////////////////////////////////////////////////////////
/// \addtogroup acf_process_apu ACF_Process_APU
/// @{

//////////////////////////////////////////////////////////////////////////
/// ACF_Process_APU is the base class from which an APU process
/// is derived.  It provides access to all the methods required for
/// run-time configuration and execution of an APU process.
//////////////////////////////////////////////////////////////////////////
class ACF_Process_APU : public ACF_Process
{
public:
   
   ACF_Process_APU(int apexID);
   ~ACF_Process_APU();

   ////////////////////////////////////////////////////////////////////////
   /// Initialize the APU process.  This must be invoked prior
   /// to any configuration or execution calls.
   ///
   /// \return
   /// 0 if successful, non-zero if an error occurred.
   /////////////////////////////////////////////////////////////////////////
   virtual int32_t Initialize() = 0;

   ////////////////////////////////////////////////////////////////////////
   /// Launch the process.  This is a non-blocking call, and must (eventually)
   /// be paired with a Wait() call.
   ///
   /// \return
   /// 0 if successful, non-zero if an error occurred.
   /////////////////////////////////////////////////////////////////////////
   virtual int32_t Start();

   /////////////////////////////////////////////////////////////////////////
   /// Wait for a launched process to complete.
   ///
   /// \return
   /// 0 if successful, non-zero if an error occurred.
   /////////////////////////////////////////////////////////////////////////
   virtual int32_t Wait();

   /////////////////////////////////////////////////////////////////////////
   /// Explicitly select the scenario where port "lPortIdentifier" has a chunk width of
   /// "lChunkWidth" and a chunk height of "lChunkHeight".  If "lPortIdentifier" is "" and
   /// "lChunkWidth" and "lChunkHeight" are both 0, the ideal scenario will be selected.
   /// A successful SelectScenario(...) call will override the automatic scenario selection that
   /// typically takes place when Start() is called.
   ///
   /// \param[in] lPortIdentifier
   /// Graph port identifier.
   ///
   /// \param[in] lChunkWidth
   /// Desired chunk width associated with port "lPortIdentifier"
   ///
   /// \param[in] lChunkHeight
   /// Desired chunk height associated with port "lPortIdentifier"
   ///
   /// \return
   /// 0 if successful, non-zero if an an error occurred or if the desired
   /// scenario could not be found
   /////////////////////////////////////////////////////////////////////////
   int32_t SelectScenario(std::string lPortIdentifier, int32_t lChunkWidth, int32_t lChunkHeight);

   /////////////////////////////////////////////////////////////////////////
   /// Return the the chunk width and height associated with port "lPortIdentifier".
   /// It is only meaningful to call this method after a successful call to SelectScenario(...).
   ///
   /// \param[in] lPortIdentifier
   /// Graph port identifier.
   ///
   /// \param[out] lChunkWidth
   /// Chunk width associated with port "lPortIdentifier"
   ///
   /// \param[out] lChunkHeight
   /// Chunk height associated with port "lPortIdentifier"
   ///
   /// \return
   /// 0 if successful, non-zero if an an error occurred.
   /////////////////////////////////////////////////////////////////////////
   int32_t QueryPortChunkSize(std::string lPortIdentifier, int32_t& lChunkWidth, int32_t& lChunkHeight);

   /////////////////////////////////////////////////////////////////////////
   /// Select a specific APU configuration and a specific APEX on which to
   /// execute the process.  This method allows for multiple processes to be
   /// executed simultaneously on the same APEX (assuming HW resource availability).
   /// ***NOTE: currently only a single APEX is supported (i.e. lApexId = 0).
   ///
   /// For example, given a single 642 APEX configuration, run myProcessA
   /// on APU0 w/ 32 CUs and run myProcessB on APU1 w/ 32 CUs:
   /// \code{.cpp}
   /// if (0 == myProcessA.SelectApuConfiguration(ACF_APU_CFG__APU_0_CU_0_31_SMEM_0_1, 0) &&
   ///     0 == myProcessB.SelectApuConfiguration(ACF_APU_CFG__APU_1_CU_32_63_SMEM_2_3, 0))
   /// {
   ///    lRetVal |= myProcessA.Start();
   ///    lRetVal |= myProcessB.Start();
   ///
   ///    lRetVal |= myProcessA.Wait();
   ///    lRetVal |= myProcessB.Wait();
   /// }
   /// \endcode
   ///
   /// \param[in] lApuConfig
   /// Desired APU configuration (see definition of ACF_APU_CFG for available options)
   ///
   /// \param[in] lApexId
   /// The ID of the desired APEX (e.g if there are 2 APEXs, valid
   /// values for lApexId would be 0 and 1).
   ///
   /// \return
   /// 0 if successful, non-zero if an an error occurred.
   /////////////////////////////////////////////////////////////////////////
   int32_t SelectApuConfiguration(ACF_APU_CFG lApuConfig, int32_t lApexId);

   //--------------------------------------------------------------------
   //The following public methods are not 'officially' documented/exposed
   //--------------------------------------------------------------------

   //NOTE: this function should only be used to override the chunk size of ports that are  fixed; if you
   //      intend to override a port that is not fixed, you are responsible for overriding the sizes of any
   //      related ports to maintain consistency.
   int32_t OverridePortChunkSize(std::string lPortIdentifier, int32_t lChunkWidth, int32_t lChunkHeight);

   int32_t RetCuArrayWidth();
   int32_t RetCmemHeapSizeInBytes();
   acf_scenario* RetSelectedScenario();
   int32_t InitDoneInterrupt(void (*pCustomHandler) (void));
	
protected:
   
   int32_t DetectHwVersion();
   int32_t DetectAvailApexMemory();
   int32_t DetWorstCaseRoiInfo();

   void SetApuLoadInfo(const LOAD_SEGMENT_t* lLoadSegments,
                       const SEG_MEM_TYPE* lpLoadPmem, const int32_t lLoadPmemSize,
                       const SEG_MEM_TYPE* lpLoadDmem, const int32_t lLoadDmemSize,
                       const SEG_MEM_TYPE* lpLoadCmem, const int32_t lLoadCmemSize);

   void AddPort(std::string lPortIdentifier,
                icp::DATATYPE lE0DataType,
                int32_t lE0x, int32_t lE0y,
                int32_t lChunkWidth, int32_t lChunkHeight,
                int32_t lInputOutput,
                int32_t lCmemDmem,
                int32_t lNonstaticStatic,
                int32_t lDirectIndirect,
                int32_t lNonfixedFixed,
                int32_t lRegFifo,
                int32_t lLmIndex,
                int32_t lRoiDepInfo = 0);

   
   std::vector<ACF_Process_PortInfo_APU> mPortInfoApuVec;

   int32_t mApexId;       //which APEX instance to use
   ACF_APU_CFG mApuCfg;   //desired APU configuration
   int32_t mApuId;        //which APU to use
   int32_t mCuArrayWidth; //number of CUs in the CU array
   int32_t mHwVersion;    //0x321, 0x642, etc.

   //heap address/size info
   int32_t mDmemHeapBaseAddrOffset; //DMEM 'heap' offset (relative to base SMEM address)
   int32_t mDmemHeapSizeInBytes;    //DMEM 'heap' size
   int32_t mCmemHeapBaseAddrOffset; //CMEM 'heap' offset (relative to base CMEM address)
   int32_t mCmemHeapSizeInBytes;    //CMEM 'heap' size
   int32_t mPmemBaseAddrOffset;     //PMEM region offset (relative to base SMEM address)
   int32_t mPmemSizeInBytes;        //PMEM size
   int32_t mSmemBaseAddrOffset;     //SMEM offset (from start of contiguous monolithic SMEM region)

   //a pointer to an array where each array 'entry' is 4 integers (vs. int* mLoadSegments[4] which is an array of int pointers)
   
   const LOAD_SEGMENT_t* mLoadSegments;
   const SEG_MEM_TYPE* mpLoadPmem;
   int32_t mLoadPmemSize;
   const SEG_MEM_TYPE* mpLoadDmem;
   int32_t mLoadDmemSize;
   const SEG_MEM_TYPE* mpLoadCmem;
   int32_t mLoadCmemSize;

   void* mpPmemLoadOal;
   void* mpDmemLoadOal;
   void* mpCmemLoadOal;
   void* mpLoadSegmentsLLOal;
   bool mUseIRQ[2];

   //scenario stuff
   acf_scenario* mpSelectedScenario;
   void CfgScenarios(acf_scenario_list* lpScenarioList);
   acf_scenario_list* mpScenarioList;

   acf_res_info mAcfResInfo;

   //hw resource management stuff
   int32_t AllocateHwResources();
   int32_t DeallocateHwResources();
   uint32_t mUserId;
   uint32_t mNumResReq; //currently will request 1 RES__APEX__APU, up to 2 RES__APEX__CU_32, and up to 2 RES__SMEM_64K (worst case = 5)
   uint32_t mResReqArray[5][3];
   uint32_t mResAcqArray[5][5];
};

/// @}

#endif //_ACF_PROCESS_APU_HPP
