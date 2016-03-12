/*****************************************************************************
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

// ***************************************************************************

// Possible to set input resolution (must be supported by the DCU)
#define WIDTH           1280 ///< width of DDR buffer in pixels
#define HEIGHT          720 ///< height of DDR buffer in pixels
#define DDR_BUFFER_CNT  3    ///< number of DDR buffers per ISP stream

#define CAM_WIDTH 640
#define CAM_HEIGHT  360
#define INC_X   3
#define INC_Y   3
#define INC_W   3
#define INC_H   3

// ***************************************************************************

static void evalBox(void);
static void initISPregs(void);

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

//***************************************************************************

static bool sStop = false; ///< to signal Ctrl+c from command line

#endif // #ifndef __STANDALONE__

uint16_t sGain_R;
uint16_t sGain_G;
uint16_t sGain_B;
uint16_t sBox_X;
uint16_t sBox_Y;
uint16_t sBox_W;
uint16_t sBox_H;
uint16_t sBox_Rest;
uint16_t sBox_Right;
uint16_t sBox_Top;
uint16_t sXOR_R;
uint16_t sXOR_G;
uint16_t sXOR_B;

// ***************************************************************************

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
  io::FrameOutputDCU lDcuOutput(WIDTH, 
                                HEIGHT, 
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
  lBufferStream.mLineCnt    = CAM_HEIGHT;
    
  lBufferStream.mpBuffers   = lpFbsPhysical; 
  
  // init stream 0
  lIsp.DdrBuffersSet(lBufferStream);
  
  //*** Start ISP processing ***
  lIsp.Start();
    
  // Frame buffer
  void *lpFrame = NULL;

  // *** have to init globals till startup does not call compiler init code ***
  //sGain_R = 417;  // Armin (sun light)
  //sGain_G = 256;
  //sGain_B = 305;
  sGain_R = 400;  // Stephan (indoor)
  sGain_G = 256;
  sGain_B = 490;
  
  sBox_X	= CAM_WIDTH/4;
  sBox_Y	= CAM_HEIGHT/4;
  sBox_W	= (CAM_WIDTH-2*sBox_X);
  sBox_H	= (CAM_HEIGHT-2*sBox_Y);
  sXOR_R	= 0xffff;
  sXOR_G	= 0xffff;
  sXOR_B	= 0xffff;
  evalBox();

  //volatile uint32_t lCnt = 0;
  uint16_t box_X_inc = INC_X;
  uint16_t box_Y_inc = INC_Y;
  uint16_t box_W_inc = INC_W;
  uint16_t box_H_inc = INC_H;
  
  initISPregs();
  
  lIsp.StartCam();
  
  for(;;)
  {
    evalBox();
    initISPregs();

    // *** get frame ***
    if(NULL == (lpFrame = lIsp.GetFrame()))
    {
      break;
    }

    // *** W ***
    sBox_W += box_W_inc;
    if(sBox_W<(4*INC_W))
    {
      box_W_inc = INC_W;
    }
    if(sBox_W>(CAM_WIDTH/2))
    {
      box_W_inc = -INC_W;
    }

    // *** H ***
    sBox_H += box_H_inc;
    if(sBox_H<(4*INC_H))
    {
      box_H_inc = INC_H;
    }
    if(sBox_H>(CAM_HEIGHT/2))
    {
      box_H_inc = -INC_H;
    }

    // *** X ***
    sBox_X += box_X_inc;
    if(sBox_X<(4*INC_X))
    {
      box_X_inc = INC_X;
    }
    if(sBox_X>CAM_WIDTH)
    {
      box_X_inc = -INC_X;
    }

    // *** Y ***
    sBox_Y += box_Y_inc;
    if(sBox_Y<(4*INC_Y))
    {
      box_Y_inc = INC_Y;
    }
    if(sBox_Y>CAM_HEIGHT)
    {
      box_Y_inc = -INC_Y;
    }

    if(io::IO_OK != lDcuOutput.GetStatus())
    {
      break;
    }
    lpFrame = OAL_MemoryReturnAddress(
                      lpFrame, 
                      ACCESS_PHY + 1); // get virtual address    
    lDcuOutput.PutFrame(lpFrame, false);
    
#ifndef __STANDALONE__  
    if(sStop)
    {
      break; // break if Ctrl+C pressed
    } // if Ctrl+C
#endif //#ifndef __STANDALONE__  

  }

  //*** Stop ISP processing ***
  lIsp.Stop();

#ifdef __STANDALONE__  
  for(;;);  // *** don't return ***
#endif // #ifdef __STANDALONE__  

  DdrBuffersFree(lppFbsVirtual, lpFbsPhysical);
  
} // main()

// ***************************************************************************

static void evalBox(void)
{
  sBox_Rest	= (sBox_X+sBox_W);
  sBox_Right	= (CAM_WIDTH-sBox_W-sBox_X);
  sBox_Top	= sBox_H;

} // evalBox(void)

// ***************************************************************************

static void initISPregs(void)
{
  seq_setReg(1, 0, 0, 0x70, sGain_R);	// GPR0
  seq_setReg(1, 0, 0, 0x71, sGain_G);	// GPR1
  seq_setReg(1, 0, 0, 0x72, sGain_B);	// GPR2
  
  seq_setReg(1, 0, 0, 0x73, sBox_X);	// GPR3
  seq_setReg(1, 0, 0, 0x74, sBox_Y);	// GPR4
  seq_setReg(1, 0, 0, 0x75, sBox_Rest);	// GPR5
  seq_setReg(1, 0, 0, 0x76, sBox_W);	// GPR6
  seq_setReg(1, 0, 0, 0x77, sBox_Right);	// GPR7
  seq_setReg(1, 0, 0, 0x78, sBox_Top);	// GPR8

  seq_setReg(1, 0, 0, 0x79, sXOR_R);	// GPR9
  seq_setReg(1, 0, 0, 0x7a, sXOR_G);	// GPR10
  seq_setReg(1, 0, 0, 0x7b, sXOR_B);	// GPR11

} // initISPregs()

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

/*EOF*/
