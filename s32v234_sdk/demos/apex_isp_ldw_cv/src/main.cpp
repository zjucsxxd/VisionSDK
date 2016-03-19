/*****************************************************************************
*
* Freescale Confidential Proprietary
*
* Copyright (c) 2015 Freescale Semiconductor;
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
#include <config_ldw.h>
#include <visualisation.h>

#include "frame_input_patterngen.h"
#include "frame_input_isp.h"
#include "apex.h"

#ifdef __STANDALONE__
  #include "frame_output_dcu.h"
  #define CHNL_CNT io::IO_DATA_CH3
#else // #ifdef __STANDALONE__
  #include "frame_output_v234fb.h"
  #define CHNL_CNT io::IO_DATA_CH3
#endif // else from #ifdef __STANDALONE__

#include "seq_public.h"

void neon_memcpy_resize640(char* dst, char* src)
{


  char *dst_local1 = dst + (60 * 1920 * 3) + (320 * 3);
  char *dst_local2 = dst_local1 + 1920*3;
  char *src_local = (src + 16 * 1920 * 3);
  long line_size = (640 * 3) / 24;
  long line_iterations = line_size;
  long height_iterations = 480;
  long stride_src = 1280 * 3;
  long stride_dst = 640 * 3 + 1920*3;

    __asm volatile( "1: \n\t"
		      "LD3 {V0.8B, V1.8B, V2.8B}, [%[src_local]], #24	\n\t"
			  "ST3 {V0.B, V1.B, V2.B}[0], [%[dst_local1]], #3	\n\t"
			  "ST3 {V0.B, V1.B, V2.B}[0], [%[dst_local1]], #3	\n\t"
			  "ST3 {V0.B, V1.B, V2.B}[0], [%[dst_local2]], #3	\n\t"
			  "ST3 {V0.B, V1.B, V2.B}[0], [%[dst_local2]], #3	\n\t"

			  "ST3 {V0.B, V1.B, V2.B}[1], [%[dst_local1]], #3	\n\t"
			  "ST3 {V0.B, V1.B, V2.B}[1], [%[dst_local1]], #3	\n\t"
			  "ST3 {V0.B, V1.B, V2.B}[1], [%[dst_local2]], #3	\n\t"
			  "ST3 {V0.B, V1.B, V2.B}[1], [%[dst_local2]], #3	\n\t"

			  "ST3 {V0.B, V1.B, V2.B}[2], [%[dst_local1]], #3	\n\t"
			  "ST3 {V0.B, V1.B, V2.B}[2], [%[dst_local1]], #3	\n\t"
			  "ST3 {V0.B, V1.B, V2.B}[2], [%[dst_local2]], #3	\n\t"
			  "ST3 {V0.B, V1.B, V2.B}[2], [%[dst_local2]], #3	\n\t"

			  "ST3 {V0.B, V1.B, V2.B}[3], [%[dst_local1]], #3	\n\t"
			  "ST3 {V0.B, V1.B, V2.B}[3], [%[dst_local1]], #3	\n\t"
			  "ST3 {V0.B, V1.B, V2.B}[3], [%[dst_local2]], #3	\n\t"
			  "ST3 {V0.B, V1.B, V2.B}[3], [%[dst_local2]], #3	\n\t"

			  "ST3 {V0.B, V1.B, V2.B}[4], [%[dst_local1]], #3	\n\t"
			  "ST3 {V0.B, V1.B, V2.B}[4], [%[dst_local1]], #3	\n\t"
			  "ST3 {V0.B, V1.B, V2.B}[4], [%[dst_local2]], #3	\n\t"
			  "ST3 {V0.B, V1.B, V2.B}[4], [%[dst_local2]], #3	\n\t"

			  "ST3 {V0.B, V1.B, V2.B}[5], [%[dst_local1]], #3	\n\t"
			  "ST3 {V0.B, V1.B, V2.B}[5], [%[dst_local1]], #3	\n\t"
			  "ST3 {V0.B, V1.B, V2.B}[5], [%[dst_local2]], #3	\n\t"
			  "ST3 {V0.B, V1.B, V2.B}[5], [%[dst_local2]], #3	\n\t"

			  "ST3 {V0.B, V1.B, V2.B}[6], [%[dst_local1]], #3	\n\t"
			  "ST3 {V0.B, V1.B, V2.B}[6], [%[dst_local1]], #3	\n\t"
			  "ST3 {V0.B, V1.B, V2.B}[6], [%[dst_local2]], #3	\n\t"
			  "ST3 {V0.B, V1.B, V2.B}[6], [%[dst_local2]], #3	\n\t"

			  "ST3 {V0.B, V1.B, V2.B}[7], [%[dst_local1]], #3	\n\t"
			  "ST3 {V0.B, V1.B, V2.B}[7], [%[dst_local1]], #3	\n\t"
			  "ST3 {V0.B, V1.B, V2.B}[7], [%[dst_local2]], #3	\n\t"
			  "ST3 {V0.B, V1.B, V2.B}[7], [%[dst_local2]], #3	\n\t"

			  "subs %[line_iterations],%[line_iterations],#1 \n\t"
		      "bne 1b \n\t"
			  "mov %[line_iterations], %[line_size] \n\t"
			  "add %[dst_local1],%[dst_local1],%[stride_dst] \n\t"
			  "add %[dst_local2],%[dst_local2],%[stride_dst] \n\t"
			  "add %[src_local],%[src_local],%[stride_src] \n\t"

			  "subs %[height_iterations],%[height_iterations],#1 \n\t"
			  "bne 1b \n\t"


		      : [src_local]"+r"(src_local),
			    [dst_local1] "+r"(dst_local1),
				[dst_local2] "+r"(dst_local2),
				[line_iterations]"+r"(line_iterations),
				[height_iterations]"+r"(height_iterations),
				[line_size]"+r"(line_size),
				[stride_src]"+r"(stride_src),
				[stride_dst]"+r"(stride_dst)
		      :
		      //: "memory", "d0"
		   );

}

void neon_memcpy_to640(char* dst, char* src)
{
  char *dst_local = dst + 120 * 640 * 3;
  char *src_local = src;
  long line_size = (1280 * 3) / 24;
  long line_iterations = line_size;
  long height_iterations = 360;
  long stride_src = 1280 * 3;
  long stride_dst = 640 * 3;

    __asm volatile( "1: \n\t"
		      "LD3 {V0.8B, V1.8B, V2.8B}, [%[src_local]], #24	\n\t"
			  "ST3 {V0.B, V1.B, V2.B}[0], [%[dst_local]], #3	\n\t"
			  "ST3 {V0.B, V1.B, V2.B}[2], [%[dst_local]], #3	\n\t"
			  "ST3 {V0.B, V1.B, V2.B}[4], [%[dst_local]], #3	\n\t"
			  "ST3 {V0.B, V1.B, V2.B}[6], [%[dst_local]], #3	\n\t"


			  "subs %[line_iterations],%[line_iterations],#1 \n\t"
		      "bne 1b \n\t"
			  "mov %[line_iterations], %[line_size] \n\t"
			  //"add %[dst_local],%[dst_local],%[stride_dst] \n\t"
			  "add %[src_local],%[src_local],%[stride_src] \n\t"

			  "subs %[height_iterations],%[height_iterations],#1 \n\t"
			  "bne 1b \n\t"


		      : [src_local]"+r"(src_local),
			    [dst_local] "+r"(dst_local),
				[line_iterations]"+r"(line_iterations),
				[height_iterations]"+r"(height_iterations),
				[line_size]"+r"(line_size),
				[stride_src]"+r"(stride_src),
				[stride_dst]"+r"(stride_dst)
		      :
		      //: "memory", "d0"
		   );

}

inline void rotate_resize(unsigned char* src, unsigned char* dst, int width, int height, int size)
{
	using namespace std;

	int64_t inRow;
	inRow = width/8;

	int64_t rest = ((width % 8) * height) / 8;

	int64_t simd_iterations = 3*size / 24 - rest; //simd_pixels >> 2;		  //divide by 4

	uint64_t *offset = new uint64_t[8];
	/*	offset[0] = 2 * width * 3; 			//2x to get the to the next line line in 2x bigger image, 3x due to RGB format
		offset[1] = 4 * width * 3; 			//when end of the INPUT image is reached, it is necessary to skip 2 rows in OUTPUT image, to prevent overwriting
		offset[2] = width * 3; 				//RGB width
		offset[3] = 3 * size - 24; 			//end of the INPUT image
*/
	offset[0] = 2 * (640 + 320) * 3;  //2x to get the to the next line line in 2x bigger image, 3x due to RGB format
	offset[1] = 4 * (640 + 320) * 3;  //when end of the INPUT image is reached, it is necessary to skip 2 rows in OUTPUT image, to prevent overwriting
	offset[2] = 640 * 3;              //RGB width
    offset[3] = 3 * size - 24;        //end of the INPUT image
    offset[4] = (1080 - (2 * height)) /2 * (3 * 1920) + ((1920 - 2 * width)/2 * 3);

		asm volatile(
		"mov 							x14, %[inRow]   \n\t"
		"mov 				  			x4, #0			\n\t"
		"mov 				  			x7, #0			\n\t"
		"mov 				  			x10, #0			\n\t"
		"mov 				  			x11, #0			\n\t"

		"mov 							x4, %x2			\n\t"

		"ldr 							x10, [%x1]		\n\t"
		"add			     			%x1, %x1, #8	\n\t"
		"ldr 							x7, [%x1]		\n\t"
		"add			     			%x1, %x1, #8	\n\t"
		"ldr 							x12, [%x1]		\n\t"

		"add			     			%x1, %x1, #8	\n\t"
		"ldr 							x3, [%x1]		\n\t"

		"add 							x11, %x0, x3	\n\t"

		"add                            %x1, %x1, #8    \n\t"
		"ldr                            x3, [%x1]       \n\t"
		"add                            x4, x4, x3      \n\t"

		"3:												\n\t"
		"mov 							x3, x11			\n\t"
		"mov 				  			x8, #0			\n\t"
		"mov 				  			x6, #0			\n\t"
		"mov 							x6, x4			\n\t"

		"4:              		   					    \n\t"
		"LD3 {V0.8B, V1.8B, V2.8B},				[x11]	\n\t"
		"rev64 V0.8B, V0.8B								\n\t"
		"rev64 V1.8B, V1.8B								\n\t"
		"rev64 V2.8B, V2.8B								\n\t"

		"mov 							x8, x6			\n\t"	//abych se mohl posunout na zacatek dalsiho radku ne az za ten krok
		"mov 				  			x9, #0			\n\t"	//to move to the beginning of the next line and dont you address given by autoincrement
		"mov 				  			x9, x8			\n\t"

		"ST3 {V0.B, V1.B, V2.B}[0],			[x6],#3	\n\t"
		"ST3 {V0.B, V1.B, V2.B}[0],			[x6],#3	\n\t"

		"ST3 {V0.B, V1.B, V2.B}[1],			[x6],#3	\n\t"
		"ST3 {V0.B, V1.B, V2.B}[1],			[x6],#3	\n\t"

		"ST3 {V0.B, V1.B, V2.B}[2],			[x6],#3	\n\t"
		"ST3 {V0.B, V1.B, V2.B}[2],			[x6],#3	\n\t"

		"ST3 {V0.B, V1.B, V2.B}[3],			[x6],#3	\n\t"
		"ST3 {V0.B, V1.B, V2.B}[3],			[x6],#3	\n\t"

		"ST3 {V0.B, V1.B, V2.B}[4],			[x6],#3	\n\t"
		"ST3 {V0.B, V1.B, V2.B}[4],			[x6],#3	\n\t"

		"ST3 {V0.B, V1.B, V2.B}[5],			[x6],#3	\n\t"
		"ST3 {V0.B, V1.B, V2.B}[5],			[x6],#3	\n\t"

		"ST3 {V0.B, V1.B, V2.B}[6],			[x6],#3	\n\t"
		"ST3 {V0.B, V1.B, V2.B}[6],			[x6],#3	\n\t"

		"ST3 {V0.B, V1.B, V2.B}[7],			[x6],#3	\n\t"
		"ST3 {V0.B, V1.B, V2.B}[7],			[x6],#3	\n\t"


		"add							x8, x8, x10   	\n\t"

		"ST3 {V0.B, V1.B, V2.B}[0],			[x8],#3	\n\t"
		"ST3 {V0.B, V1.B, V2.B}[0],			[x8],#3	\n\t"

		"ST3 {V0.B, V1.B, V2.B}[1],			[x8],#3	\n\t"
		"ST3 {V0.B, V1.B, V2.B}[1],			[x8],#3	\n\t"

		"ST3 {V0.B, V1.B, V2.B}[2],			[x8],#3	\n\t"
		"ST3 {V0.B, V1.B, V2.B}[2],			[x8],#3	\n\t"

		"ST3 {V0.B, V1.B, V2.B}[3],			[x8],#3	\n\t"
		"ST3 {V0.B, V1.B, V2.B}[3],			[x8],#3	\n\t"

		"ST3 {V0.B, V1.B, V2.B}[4],			[x8],#3	\n\t"
		"ST3 {V0.B, V1.B, V2.B}[4],			[x8],#3	\n\t"

		"ST3 {V0.B, V1.B, V2.B}[5],			[x8],#3	\n\t"
		"ST3 {V0.B, V1.B, V2.B}[5],			[x8],#3	\n\t"

		"ST3 {V0.B, V1.B, V2.B}[6],			[x8],#3	\n\t"
		"ST3 {V0.B, V1.B, V2.B}[6],			[x8],#3	\n\t"

		"ST3 {V0.B, V1.B, V2.B}[7],			[x8],#3	\n\t"
		"ST3 {V0.B, V1.B, V2.B}[7],			[x8],#3	\n\t"

		"mov 				  			x8, #0			\n\t"
		"add							x8, x9, x10   	\n\t"
		"add							x8, x8, x10   	\n\t"
	    "sub 							x11, x11, #24	\n\t"	//decrement input image address

		"subs %[inRow], %[inRow], #1   			     \n\t"
		"bgt 4b                							 \n\t"

		"add %[inRow], %[inRow], x14	 			\n\t"

		"mov 							x11, #0			\n\t"	//this is protection, if image width is not divisible by 8
		"sub 							x11, x3, x12 	\n\t"

		"add 							x4, x4, x7  	\n\t"
		"subs   %[globalIteration], %[globalIteration], x14     \n\t"
		"bgt 3b          								\n\t"


		: [source]"+r"(src), [offset]"+r"(offset),[dest] "+r"(dst), [inRow]"+r"(inRow),[globalIteration]"+r"(simd_iterations)
		:  // no input parameters, they're all read-write so we put them in the output parameters
		: "memory", "r7", "r6", "r4", "r9" , "r3", "r10", "r12", "r3"
	);
}

inline void neon_memcpy_rotate_1280(char* dst, char* src)
{
  char *dst_local = dst ;//+ (180 * 1920 * 3) + 320 * 3;
  char *src_local = src + 1280*720*3 - 24;
  long line_size = (1280 * 3) / 24;
  long line_iterations = line_size;
  long height_iterations = 720;
  long stride_dst = 0;//640 * 3;

    __asm volatile( "1: \n\t"
			  "PRFM PLDL1KEEP, [%[src_local], #-24] \n\t"
		      "LD3 {V0.8B, V1.8B, V2.8B}, [%[src_local]]	\n\t"
			  "subs %[src_local],%[src_local],#24				\n\t"
			  "ST3 {V0.B, V1.B, V2.B}[7], [%[dst_local]], #3		\n\t"
			  "ST3 {V0.B, V1.B, V2.B}[6], [%[dst_local]], #3		\n\t"
			  "ST3 {V0.B, V1.B, V2.B}[5], [%[dst_local]], #3		\n\t"
			  "ST3 {V0.B, V1.B, V2.B}[4], [%[dst_local]], #3		\n\t"
			  "ST3 {V0.B, V1.B, V2.B}[3], [%[dst_local]], #3		\n\t"
			  "ST3 {V0.B, V1.B, V2.B}[2], [%[dst_local]], #3		\n\t"
			  "ST3 {V0.B, V1.B, V2.B}[1], [%[dst_local]], #3		\n\t"
			  "ST3 {V0.B, V1.B, V2.B}[0], [%[dst_local]], #3		\n\t"

			  //"DSB SY\n\t"
			  "subs %[line_iterations],%[line_iterations],#1 \n\t"
		      "bne 1b \n\t"

			  "mov %[line_iterations], %[line_size] \n\t"
			  "add %[dst_local],%[dst_local],%[stride_dst] \n\t"

			  "subs %[height_iterations],%[height_iterations],#1 \n\t"
			  "bne 1b \n\t"


		      : [src_local]"+r"(src_local),
			    [dst_local] "+r"(dst_local),
				[line_iterations]"+r"(line_iterations),
				[height_iterations]"+r"(height_iterations),
				[line_size]"+r"(line_size),
				[stride_dst]"+r"(stride_dst)
		      :
		   );
}
//***************************************************************************

// Possible to set input resolution (must be supported by the DCU)
#define WIDTH           1280 ///< width of DDR buffer in pixels
#define HEIGHT          720 ///< height of DDR buffer in pixels
#define DDR_BUFFER_CNT  3    ///< number of DDR buffers per ISP stream

//***************************************************************************

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

#define DDR_BUF_SIZE 1920*1080*3

int main(int, char **)
{
#ifndef APEX2_EMULATE
#ifndef __STANDALONE__
  OAL_MemoryAllocInit();
#endif
 	ACF_Init();
	using namespace icp;
#endif

  LaneDetector detector;


  // DDR buffer pointers
  void*     lppFbsVirtual[DDR_BUFFER_CNT]; ///< virtual buffer pointers
  uint32_t  lpFbsPhysical[DDR_BUFFER_CNT]; ///< physical buffer adresses

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

  // Frame buffer
  void *lp_copied = OAL_MemoryAllocFlag(
                      DDR_BUF_SIZE,
                      OAL_MEMORY_FLAG_ALIGN(ALIGN2_CACHELINE)|
                      OAL_MEMORY_FLAG_CONTIGUOUS);
  void *lp_buffer = OAL_MemoryAllocFlag(
                      DDR_BUF_SIZE,
                      OAL_MEMORY_FLAG_ALIGN(ALIGN2_CACHELINE)|
                      OAL_MEMORY_FLAG_CONTIGUOUS);

  memset(lp_copied, 0, DDR_BUF_SIZE);
  memset(lp_buffer, 0, DDR_BUF_SIZE);

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
  lBufferStream.mLineStride = 1280 * (uint32_t)io::IO_DATA_CH3;
  lBufferStream.mLineCnt    = 720;	//495;//HEIGHT;

  lBufferStream.mpBuffers   = lpFbsPhysical;

  // init stream 0
  lIsp.DdrBuffersSet(lBufferStream);

  //*** Start ISP processing ***
  lIsp.Start();

  // Frame buffer
  void *lpFrame = NULL;

  uint32_t lFrmCnt = 0;

  // modify camera geometry
  SONY_Geometry_t lGeo;
  SONY_GeometryGet(CSI_IDX_0, &lGeo);
  lGeo.mVerFlip = 1;
  lGeo.mHorFlip = 1;
  SONY_GeometrySet(CSI_IDX_0,&lGeo);


  lIsp.StartCam();

  cv::Mat rot_mat = getRotationMatrix2D(cv::Point2f(91, 160), 180, 1.0);

  while((lpFrame = lIsp.GetFrame()))
  {
    lpFrame = OAL_MemoryReturnAddress(
               lpFrame,
               ACCESS_PHY + 1); // get virtual address

    cv::Mat frame = cv::Mat(720, 1280, CV_8UC3, lpFrame);
    neon_memcpy_to640((char *)lp_copied, (char *)lpFrame);
//#ifdef __STANDALONE__
    // slow down to reduce exceptions
//    for(volatile uint32_t i = 0; i <100000; i++);
//#endif // #ifdef __STANDALONE__
    if (!detector.GetNextFrame((char *)lp_copied))
    break;


  //detector.m_bird_image.copyTo(frame(cv::Rect(0, 0, detector.m_bird_image.cols, detector.m_bird_image.rows)));

    detector.CheckLaneCross();

     //if (detector.m_left_warning)
//       visualisation::drawLeftWarning(frame);
     //if (detector.m_right_warning)
//       visualisation::drawRightWarning(frame);
     //if (detector.m_lane_healthy)
     visualisation::drawLineHealthy(frame, &detector);

     visualisation::drawLaneQuadrangle(frame, &detector);

     // output the frame
     //output.PutFrame(detector.m_color_image.data);

    //cv::Mat rgb_twice_rotated(1920, 1080, CV_8UC3);
    // rotate_resize((unsigned char *)detector.m_color_image.data, (unsigned char *)lp_buffer, 640, 480, 640*480);


    cv::Mat buff = cv::Mat(1080, 1920, CV_8UC3, lp_buffer);
    warpAffine(detector.m_bird_image, detector.m_bird_image, rot_mat, detector.m_bird_image.size());
    cvtColor(detector.m_bird_image, detector.m_bird_image, CV_GRAY2RGB);
    detector.m_bird_image.copyTo(buff(cv::Rect(50, 50, detector.m_bird_image.cols, detector.m_bird_image.rows)));
    neon_memcpy_rotate_1280((char *)lp_buffer, (char *)lpFrame);
    lDcuOutput.PutFrame(lp_buffer, false);

    lFrmCnt++;
#ifndef __STANDALONE__
    if(sStop)
    {
      printf("*** STOP ***\n");
      break; // break if Ctrl+C pressed
    } // if Ctrl+C
#endif //#ifndef __STANDALONE__
  }

  //*** Stop ISP processing ***
  lIsp.Stop();

#ifdef __STANDALONE__
  for(;;);  // *** don't return ***
#else
  if(lp_copied != NULL)
  {
    OAL_MemoryFree(lp_copied);
  }
  if(lp_buffer != NULL)
  {
    OAL_MemoryFree(lp_buffer);
  }
#endif // #ifdef __STANDALONE__

  DdrBuffersFree(lppFbsVirtual, lpFbsPhysical);
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
