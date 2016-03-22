/****************************************************************************
* University of Washington
* Jake Garrison, Ray Mui, Jisoo Jung, Daniel Wu
****************************************************************************/

/****************************************************************************
*
* Freescale Confidential Proprietary
*
* Copyright (c) 2016 Freescale Semiconductor;
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

#ifndef __STANDALONE__
  #include <signal.h>
#endif // #ifdef __STANDALONE__
#include <string.h>
#include "frame_input_patterngen.h"
#include "frame_input_isp.h"

#ifdef __STANDALONE__
  #include "frame_output_dcu.h"
  #define CHNL_CNT io::IO_DATA_CH3
#else // #ifdef __STANDALONE__
  #include "frame_output_v234fb.h"
  #define CHNL_CNT io::IO_DATA_CH3
#endif // else from #ifdef __STANDALONE__

#include "seq_public.h"
#include <ctime> // added to calculate FPS
#include <opencv2/opencv.hpp> // opencv classes and operations

using namespace cv;

//***************************************************************************
// Possible to set input resolution (must be supported by the DCU)
#define WIDTH           1280 ///< width of DDR buffer in pixels
#define HEIGHT          720 ///< height of DDR buffer in pixels
#define DDR_BUFFER_CNT  3    ///< number of DDR buffers per ISP stream
#define EXPOSURE_ENGINE 1,1

// 1 = correct orientation with 10 fps
// 0 = upside down orientation with 30 fps
#define ORIENTATION 0
/************************************************************************/
/** Allocates contiguous DDR buffers for one ISP stream.
  *
  * \param  appFbsVirtual array of virtual buffer pointers to be filled
  * \param  apFbsPhysical array of buffer physical addresses to be filled
  *
  * \return 0 if all OK
  *         < 0 otherwise
  ************************************************************************/
int32_t DdrBuffersAlloc(void** appFbsVirtual, uint32_t*  apFbsPhysical);

/************************************************************************/
/** Frees DDR buffers for one ISP stream.
  *
  * \param  appFbsVirtual array of virtual buffer pointers to be filled
  * \param  apFbsPhysical array of buffer physical addresses to be filled
  ************************************************************************/
void DdrBuffersFree(void** appFbsVirtual, uint32_t*  apFbsPhysical);

#ifndef __STANDALONE__
/************************************************************************/
/** SIGINT handler.
  *
  * \param  aSigNo
  ************************************************************************/
void SigintHandler(int aSigNo);

/************************************************************************/
/** SIGINT handler.
  *
  * \param  aSigNo
  *
  * \return SEQ_LIB_SUCCESS if all ok
  *         SEQ_LIB_FAILURE if failed
  ************************************************************************/
int32_t SigintSetup(void);

/************************************************************************/
/** Configures Sony camera settings
  ***********************************************************************/
void ExposureConfigure();

static bool sStop = false; ///< to signal Ctrl+c from command line

#endif // #ifndef __STANDALONE__

int main(int, char **)
{
  // DDR buffer pointers
  void*     lppFbsVirtual[DDR_BUFFER_CNT]; ///< virtual buffer pointers
  uint32_t  lpFbsPhysical[DDR_BUFFER_CNT]; ///< physical buffer adresses

  #ifndef __STANDALONE__
    OAL_MemoryAllocInit();
  #endif

  //*** Init DCU Output ***
#ifdef __STANDALONE__
  io::FrameOutputDCU lDcuOutput(WIDTH,  // 1280
                                HEIGHT, // 720
                                io::IO_DATA_DEPTH_08,
                                CHNL_CNT);
#else // #ifdef __STANDALONE__
  // setup Ctrl+C handler
  if(SigintSetup() != SEQ_LIB_SUCCESS)
  {
    VDB_LOG_ERROR("Failed to register Ctrl+C signal handler.");
    return -1;
  }

  printf("Press Ctrl+C to terminate the demo.\n");
  io::FrameOutputV234Fb lDcuOutput(WIDTH,
                        HEIGHT,
                        io::IO_DATA_DEPTH_08,
                        CHNL_CNT);
#endif // else from #ifdef __STANDALONE__

  //*** allocate DDR buffers ***
  if(DdrBuffersAlloc(lppFbsVirtual, lpFbsPhysical) != 0)
  {
    VDB_LOG_ERROR("Failed to allocated DDR buffers.");
    return -1;
  } // if failed to allocate buffers

  //*** Init ISP input ***
  io::FrameInputISP lIsp;
  io::IspBufferStream lBufferStream;

  lBufferStream.mStreamIdx  = 0;
  lBufferStream.mCnt        = DDR_BUFFER_CNT;
  lBufferStream.mBaseShift  = 0;
  lBufferStream.mLineStride = WIDTH * (uint32_t)io::IO_DATA_CH3;
  lBufferStream.mLineCnt    = HEIGHT;	// 720

  lBufferStream.mpBuffers   = lpFbsPhysical;

  // init stream 0
  lIsp.DdrBuffersSet(lBufferStream);

  //*** Start ISP processing ***
  lIsp.Start();

  // sony camera configuration
  ExposureConfigure();

  // Frame buffer
  void *lpFrame = NULL;

  // Frame count to be displayed in the console
  uint32_t lFrmCnt = 0;

  lIsp.StartCam();

  lpFrame = lIsp.GetFrame();

  // FPS display information: size, location, color, content
  int size = 200;
  Point txtPt(10,HEIGHT - 20); // LEFT BOTTOM when (sony v=1,h=1)
  Scalar color(0, 255, 0); // Green. Scalar(B,G,R) each ranges 0-255
  string txt = "FPS: ";

  while(lpFrame)
  {
    // start measuring time for a single frame
    clock_t begin = clock();

    lpFrame = OAL_MemoryReturnAddress(
                          lpFrame,
                          ACCESS_PHY + 1); // get virtual address

    // Modifies matrix in lpFrame. Does not make a copy of new matrix;
    // it uses the same object. Modification in 'frame' will be reflected
    // in lpFrame.
    Mat frame = Mat(720, 1280, CV_8UC3, lpFrame);

    putText(frame, txt, txtPt, 1, 2, color, 2, false);

    // NOTE: ORIENTATION CHANGE
    // - 'flip' makes the proper text and display orientation
    //   but slows down to ~10 frames per second
    // - without 'flip' will maintain 30 frames per second
    //   but the display is upside down
    if (ORIENTATION) {
      flip(frame, frame, -1);
    }


    // Load the current frame on the board's display
    lDcuOutput.PutFrame(lpFrame, false);

    // Compute FPS
    lpFrame = lIsp.GetFrame();
    clock_t end = clock();
    double elapsedTime = double(end - begin) / CLOCKS_PER_SEC;
    double fps = 1 / elapsedTime;
    txt = "FPS: " + std::to_string(fps);
    printf("FRAME:  %.2lf FPS: %.2lf \n", (double)lFrmCnt, fps);
    lFrmCnt++;

    frame.release();

#ifndef __STANDALONE__
    if(sStop)
    {
      //*** Stop ISP processing ***
      lIsp.Stop();
      // Free buffers
      DdrBuffersFree(lppFbsVirtual, lpFbsPhysical);
      break; // break if Ctrl+C pressed
    } // if Ctrl+C
#endif //#ifndef __STANDALONE__
  } // while

  //*** Stop ISP processing ***
  lIsp.Stop();

#ifdef __STANDALONE__
  for(;;);  // *** don't return ***
#endif // #ifdef __STANDALONE__
  DdrBuffersFree(lppFbsVirtual, lpFbsPhysical);
//#endif
} // main()

//***************************************************************************
int32_t DdrBuffersAlloc(void** appFbsVirtual, uint32_t*  apFbsPhysical)
{
  int32_t lRet    = 0;

  size_t lMemSize = WIDTH * HEIGHT * (uint32_t)io::IO_DATA_CH3;

  // allocate buffers & get physical addresses
  for(uint32_t i = 0; i < DDR_BUFFER_CNT; i++)
  {
    appFbsVirtual[i] = OAL_MemoryAllocFlag(
                          lMemSize,
                          OAL_MEMORY_FLAG_ALIGN(ALIGN2_CACHELINE)|
                          OAL_MEMORY_FLAG_CONTIGUOUS);

    if( appFbsVirtual[i] == NULL)
    {
      lRet = -1;
      break;
    }
    apFbsPhysical[i] = (uint32_t)(uintptr_t)OAL_MemoryReturnAddress(
                          appFbsVirtual[i],
                          ACCESS_PHY); // get physical address

    memset(appFbsVirtual[i], 0, lMemSize);
  } // for all framebuffers

  if(lRet != 0)
  {
    DdrBuffersFree(appFbsVirtual, apFbsPhysical);
  }

  return lRet;
} // DdrBuffersAlloc()

//***************************************************************************
void DdrBuffersFree(void** appFbsVirtual, uint32_t*  apFbsPhysical)
{
  for(uint32_t i = 0; i < DDR_BUFFER_CNT; i++)
  {
    if(appFbsVirtual[i] != NULL)
    {
      OAL_MemoryFree(appFbsVirtual[i]);
    } // if buffer allocated

    appFbsVirtual[i]   = NULL;
    apFbsPhysical[i]   = 0;
  } // for all framebuffers
} // DdrBuffersFree()

//***************************************************************************
void ExposureConfigure()
{
  // modify camera geometry
  SONY_Geometry_t lGeo;
  SONY_GeometryGet(CSI_IDX_0, &lGeo);
  lGeo.mVerFlip = 1;  // flip about y-axis
  lGeo.mHorFlip = 1;  // flip about x-axis
  //lGeo.mFps     = 20;
  SONY_GeometrySet(CSI_IDX_0,&lGeo);

  // update exposure engine (IPU) parameters
  seq_setReg(EXPOSURE_ENGINE, 0, 0x70, 0xf08);  // GPR0 (IPUS)
  seq_setReg(EXPOSURE_ENGINE, 0, 0x71, 0xf08);  // GPR1 (IPUS)
  seq_setReg(EXPOSURE_ENGINE, 0, 0x72, 0xf08);  // GPR2 (IPUS)
  seq_setReg(EXPOSURE_ENGINE, 0, 0x73, 0xf08);  // GPR3 (IPUS)
  seq_setReg(EXPOSURE_ENGINE, 0, 0x74, 490);  // GPR4 (IPUS)
  seq_setReg(EXPOSURE_ENGINE, 0, 0x75, 256);  // GPR5 (IPUS)
  seq_setReg(EXPOSURE_ENGINE, 0, 0x76, 256);  // GPR6 (IPUS)
  seq_setReg(EXPOSURE_ENGINE, 0, 0x77, 402);  // GPR7 (IPUS)
} // ExposureConfigure;

//***************************************************************************
#ifndef __STANDALONE__
void SigintHandler(int aSigNo)
{
  sStop = true;
} // SigintHandler()

//***************************************************************************
int32_t SigintSetup()
{
  int32_t lRet = SEQ_LIB_SUCCESS;

  // prepare internal signal handler
  struct sigaction lSa;
  memset(&lSa, 0, sizeof(lSa));
  lSa.sa_handler = SigintHandler;

  if( sigaction(SIGINT, &lSa, NULL) != 0)
  {
    VDB_LOG_ERROR("Failed to register signal handler.\n");
    lRet = SEQ_LIB_FAILURE;
  } // if signal not registered

  return lRet;
} // SigintSetup()

//***************************************************************************
#endif // #ifndef __STANDALONE__
