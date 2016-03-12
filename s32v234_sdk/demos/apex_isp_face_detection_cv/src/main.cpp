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
#include <opencv2/opencv.hpp>
#include "../../data/standalone/lbpcascade_frontalface.h"
#include "tinyxml2.h"
#include <kalman_filter.h>
#include <icp_data.h>
#include "apex.h"
//#include <APU_FACE_DETECTION_LBP_10.hpp>
//#include <APU_FACE_DETECTION_LBP_6.hpp>
#include <APU_FACE_DETECTION_LBP_4.hpp>
//#include <APU_FACE_DETECTION_LBP_2.hpp>


#include "frame_input_patterngen.h"
#include "frame_input_isp.h"
#include "frame_output_dcu.h"
#include "seq_public.h"


using namespace tinyxml2;
using namespace icp;
//***************************************************************************

// Possible to set input resolution (must be supported by the DCU)
#define WIDTH           1920 ///< width of DDR buffer in pixels
#define HEIGHT          1080 ///< height of DDR buffer in pixels
#define DDR_BUFFER_CNT  3    ///< number of DDR buffers per ISP stream

  const int RESX = 1280;
  const int RESY = 720;

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

//***************************************************************************
typedef int32_t STAGE_FIXED_POINT_TYPE;
const int STAGE_FRACTIONAL_BITS = 28;
const int STAGE_FIXED_POINT_MULTIPLIER = (1 << STAGE_FRACTIONAL_BITS);

int APEX_STAGES = 20;
const bool SKIP_ODD = true;

struct lbpFeature
{
  int rectangleIndex;
  int values[8];

  STAGE_FIXED_POINT_TYPE leafValuesFixed[2];

};

struct lbpRectangle
{
  int x, y, width, height;
};

struct lbpStage
{
  int firstFeatureIndex;
  int featureCount;
  STAGE_FIXED_POINT_TYPE thresholdFixed;
};

struct APEX_lbpFeature
{
  int32_t values[8];
  STAGE_FIXED_POINT_TYPE leafValues[2];
  uint8_t x, y, width, height;
};

struct APEX_lbpStage
{
  uint8_t featureCount;
  STAGE_FIXED_POINT_TYPE threshold;
};

struct FaceRectangle
{
  int x, y;
  int width, height;

  FaceRectangle(int aX, int aY, int aWidth, int aHeight) : x(aX), y(aY), width(aWidth), height(aHeight){}

  bool ContainsCenter(const FaceRectangle& otherRectangle) const
  {
    int cxOffset = otherRectangle.x + (otherRectangle.width >> 1) - x;
    int cyOffset = otherRectangle.y + (otherRectangle.height >> 1) - y;

    return (cxOffset >= 0 && cxOffset <= width && cyOffset >= 0 && cyOffset <= height);
  }
};

struct DetectedFace
{
  FaceRectangle testingFaceRectangle;

  FaceRectangle minFaceRectangle;
  FaceRectangle maxFaceRectangle;

  int faceRectangleCount;

  DetectedFace(const FaceRectangle& faceRectangle):
    testingFaceRectangle(faceRectangle),
    minFaceRectangle(faceRectangle),
    maxFaceRectangle(faceRectangle),
    faceRectangleCount(1)
  {}

  bool TryAddFaceRectangle(const FaceRectangle& faceRectangle)
  {
    if (!faceRectangle.ContainsCenter(testingFaceRectangle))
    {
      return false;
    }

    if (faceRectangle.x < minFaceRectangle.x) minFaceRectangle.x = faceRectangle.x;
    if (faceRectangle.y < minFaceRectangle.y) minFaceRectangle.y = faceRectangle.y;
    if (faceRectangle.width < minFaceRectangle.width) minFaceRectangle.width = faceRectangle.width;
    if (faceRectangle.height < minFaceRectangle.height) minFaceRectangle.height = faceRectangle.height;

    if (faceRectangle.x > maxFaceRectangle.x) maxFaceRectangle.x = faceRectangle.x;
    if (faceRectangle.y > maxFaceRectangle.y) maxFaceRectangle.y = faceRectangle.y;
    if (faceRectangle.width > maxFaceRectangle.width) maxFaceRectangle.width = faceRectangle.width;
    if (faceRectangle.height > maxFaceRectangle.height) maxFaceRectangle.height = faceRectangle.height;

    ++faceRectangleCount;

    return true;
  }

  FaceRectangle GetMidFaceRectangle()
  {
    return FaceRectangle(
      (minFaceRectangle.x + maxFaceRectangle.x) >> 1,
      (minFaceRectangle.y + maxFaceRectangle.y) >> 1,
      (minFaceRectangle.width + maxFaceRectangle.width) >> 1,
      (minFaceRectangle.height + maxFaceRectangle.height) >> 1);
  }
};

struct DetectedFaceFiltered
{
  DetectedFace _detectedFace;

  int framesNotDetected;
  int framesDetected;
  unsigned char color[3];
  
  KalmanFilter kalman_x;
  KalmanFilter kalman_y;
  KalmanFilter kalman_w;
  KalmanFilter kalman_h;
  
  DetectedFaceFiltered(DetectedFace& detectedFace):
    _detectedFace(detectedFace),
    framesNotDetected(0),
	framesDetected(0)
  {
	  FaceRectangle fr = detectedFace.GetMidFaceRectangle();
	  kalman_x.Initialize(0.01, 0.001, fr.x + (fr.width/2));
	  kalman_y.Initialize(0.01, 0.001, fr.y + (fr.height/2));
	  kalman_w.Initialize(0.5, 0.05, fr.width);
	  kalman_h.Initialize(0.5, 0.05, fr.height);
	  
	  color[0] = 0;
	  color[1] = 0;
	  color[2] = 0;
  }

  bool Update(DetectedFace& detectedFace)
  {
	  FaceRectangle fr = detectedFace.GetMidFaceRectangle();
	kalman_x.NextMeasurement(fr.x + (fr.width/2));
	kalman_y.NextMeasurement(fr.y + (fr.height/2));
	kalman_w.NextMeasurement(fr.width);
	kalman_h.NextMeasurement(fr.height);
    
	
	_detectedFace.testingFaceRectangle.width = kalman_w.GetValue();
	_detectedFace.testingFaceRectangle.height = kalman_h.GetValue();
	_detectedFace.testingFaceRectangle.x = kalman_x.GetValue() - (kalman_w.GetValue()/2);
	_detectedFace.testingFaceRectangle.y = kalman_y.GetValue() - (kalman_h.GetValue()/2);

	framesNotDetected = 0;
	framesDetected += 1;
    return true;
  }

/*  FaceRectangle GetMidFaceRectangle()
  {
    return FaceRectangle(
      (minFaceRectangle.x + maxFaceRectangle.x) >> 1,
      (minFaceRectangle.y + maxFaceRectangle.y) >> 1,
      (minFaceRectangle.width + maxFaceRectangle.width) >> 1,
      (minFaceRectangle.height + maxFaceRectangle.height) >> 1);
  }*/
};

int windowWidth = 1, windowHeight = 1;
vector<lbpFeature> lbpFeatures;
vector<lbpRectangle> lbpRectangles;
vector<lbpStage> lbpStages;

void FinishDetectionOnHost(cv::Mat& detectedMask, cv::Mat& integralImage, int firstStage, bool skipOdd)
{
  int skip = skipOdd ? 2 : 1;
  int sizey = integralImage.rows - windowHeight;
  int sizex = integralImage.cols - windowWidth;
  for (int y = 0; y < sizey; y += skip)
  {
    for (int x = 0; x < sizex; x += skip)
    {
      if (detectedMask.at<int8_t>(y + windowHeight, x) == 0)
      {
        continue;
      }

      bool detected = true;
      for (int si = firstStage; si < (int)lbpStages.size(); ++si)
      {
        lbpStage lbps = lbpStages[si];
		int lbps_for_count = lbps.firstFeatureIndex + lbps.featureCount;

        STAGE_FIXED_POINT_TYPE stageSumFixed = 0;

        for (int fi = lbps.firstFeatureIndex; fi < lbps_for_count; ++fi)
        {
          lbpFeature lbpf = lbpFeatures[fi];
          lbpRectangle lbpr = lbpRectangles[lbpf.rectangleIndex];

          //grid pattern values
          int gpv[16];

          int gridStartX = x + lbpr.x - 1;
          int gridStartY = y + lbpr.y - 1;
          int gridOffsetX = 0;
          int gridOffsetY = 0;

          int wpi = 0;
          for (int wpY = 0; wpY < 4; ++wpY)
          {
            gridOffsetX = 0;
            for (int wpX = 0; wpX < 4; ++wpX)
            {
              int finalX = gridStartX + gridOffsetX;
              int finalY = gridStartY + gridOffsetY;
              int value = 0;
              if (finalX >= 0 && finalY >= 0)
              {
                value = (int)integralImage.at<int32_t>(finalY, finalX);
              }
              gpv[wpi] = value;
              gridOffsetX += lbpr.width;

              ++wpi;
            }
            gridOffsetY += lbpr.height;
          }

          int center = gpv[5] + gpv[10] - gpv[6] - gpv[9];

          int c0 = gpv[0] + gpv[5] - gpv[1] - gpv[4];
          int c1 = gpv[1] + gpv[6] - gpv[2] - gpv[5];
          int c2 = gpv[2] + gpv[7] - gpv[3] - gpv[6];
          int c3 = gpv[6] + gpv[11] - gpv[7] - gpv[10];
          int c4 = gpv[10] + gpv[15] - gpv[11] - gpv[14];
          int c5 = gpv[9] + gpv[14] - gpv[10] - gpv[13];
          int c6 = gpv[8] + gpv[13] - gpv[9] - gpv[12];
          int c7 = gpv[4] + gpv[9] - gpv[5] - gpv[8];

          int code =
            (c0 >= center ? 0x0080 : 0) |
            (c1 >= center ? 0x0040 : 0) |
            (c2 >= center ? 0x0020 : 0) |
            (c3 >= center ? 0x0010 : 0) |
            (c4 >= center ? 0x0008 : 0) |
            (c5 >= center ? 0x0004 : 0) |
            (c6 >= center ? 0x0002 : 0) |
            (c7 >= center ? 0x0001 : 0);

          //get one of the 256 bits contained in values[8] indexed by code
          int featureVal = lbpf.values[code >> 5];

          int leafIndex = featureVal & (1 << (code & 0x1f)) ? 0 : 1;

          stageSumFixed += lbpf.leafValuesFixed[leafIndex];

        }


        if (stageSumFixed < lbps.thresholdFixed)

        {
          detected = false;
          break;
        }
      }

      if (!detected)
      {
        detectedMask.at<int8_t>(y + windowHeight, x) = 0;
      }
    }
  }
}




inline void neon_memcpy_1280(char* dst, char* src);
inline void neon_memcpy_rotate_1280(char* dst, char* src);
inline void neon_memcpy(char* dst, char* src, long size);
inline void neon_memcpy_1280_to_hd(char* dst, char* src);



inline void start_ddr_profiler(uint8_t module)
{
    switch(module)
    {
            case 0:
            MMDC_0.MADPCR0.B.DBG_RST=0X0; //start COUNTERS.
            MMDC_0.MADPCR1.B.PRF_AXI_ID_MASK=0xF00F;//mask all the AXI valid  id bit for GPU. 11xxxxxxx0001 
            MMDC_0.MADPCR1.B.PRF_AXI_ID=0x3000;// AXI id = bit.
            MMDC_0.MADPCR0.B.PRF_FRZ=0x0; //counter are  not frozen.
			MMDC_0.MADPCR0.B.DBG_EN = 1;
            break;
            case 1:
                MMDC_1.MADPCR0.B.DBG_RST=0X0; //start COUNTERS.
            MMDC_1.MADPCR1.B.PRF_AXI_ID_MASK=0xF00F;//mask all the AXI valid  id bit for GPU. 11xxxxxxx0001 
            MMDC_1.MADPCR1.B.PRF_AXI_ID=0x3000;// AXI id = bit.
            MMDC_1.MADPCR0.B.PRF_FRZ=0x0; //counter are  not frozen.
			MMDC_1.MADPCR0.B.DBG_EN = 1;
            break;
    }
}
 
inline void end_ddr_profiler(uint8_t module)
{
    switch(module)
    {
            case 0:
                MMDC_0.MADPCR0.B.PRF_FRZ=0x1; //counters are frozen.
            MMDC_0.MADPCR0.B.DBG_EN=0X0; //disable profiling
            break;
 
            case 1:
                MMDC_1.MADPCR0.B.PRF_FRZ=0x1; //counters are frozen.
            MMDC_1.MADPCR0.B.DBG_EN=0X0; //disable profiling
            break;
    }
 
}
 
uint32 values_profiler[10000];
int j = 0;

void publish_profiler_result(uint8_t module)
{
    volatile uint32_t read_bytes, write_bytes, total_byte, total_cycle, performance;
 
    switch(module)
    {
            case 0:
                read_bytes=MMDC_0.MADPSR4.R;
                write_bytes=MMDC_0.MADPSR5.R;
                total_byte=read_bytes+write_bytes;
                total_cycle=MMDC_0.MADPSR0.R;
                performance=(((total_byte*100/total_cycle)/8));
 
				/*values_profiler[j++] = MMDC_0.MADPSR0.R;
				values_profiler[j++] = MMDC_0.MADPSR1.R;
				values_profiler[j++] = MMDC_0.MADPSR2.R;
				values_profiler[j++] = MMDC_0.MADPSR3.R;
				values_profiler[j++] = MMDC_0.MADPSR4.R;
				values_profiler[j++] = MMDC_0.MADPSR5.R;*/
                printf("MMDC_0.MADPSR0 = %X\n",MMDC_0.MADPSR0.R);
                printf("MMDC_0.MADPSR1 = %X\n",MMDC_0.MADPSR1.R);
                printf("MMDC_0.MADPSR2 = %X\n",MMDC_0.MADPSR2.R);
                printf("MMDC_0.MADPSR3 = %X\n",MMDC_0.MADPSR3.R);
                printf("MMDC_0.MADPSR4 = %X\n",MMDC_0.MADPSR4.R);
                printf("MMDC_0.MADPSR5 = %X\n",MMDC_0.MADPSR5.R);
                MMDC_0.MADPCR0.B.DBG_RST=0X1; //CLEAR COUNTERS.
                break;
 
            case 1:
                read_bytes=MMDC_1.MADPSR4.R;
                write_bytes=MMDC_1.MADPSR5.R;
                total_byte=read_bytes+write_bytes;
                total_cycle=MMDC_1.MADPSR0.R;
                performance=(((total_byte*100/total_cycle)/8));
                
				/*values_profiler[j++] = MMDC_1.MADPSR0.R;
				values_profiler[j++] = MMDC_1.MADPSR1.R;
				values_profiler[j++] = MMDC_1.MADPSR2.R;
				values_profiler[j++] = MMDC_1.MADPSR3.R;
				values_profiler[j++] = MMDC_1.MADPSR4.R;
				values_profiler[j++] = MMDC_1.MADPSR5.R;*/
				
                printf("MMDC_1.MADPSR0 = %X\n",MMDC_1.MADPSR0.R);
                printf("MMDC_1.MADPSR1 = %X\n",MMDC_1.MADPSR1.R);
                printf("MMDC_1.MADPSR2 = %X\n",MMDC_1.MADPSR2.R);
                printf("MMDC_1.MADPSR3 = %X\n",MMDC_1.MADPSR3.R);
                printf("MMDC_1.MADPSR4 = %X\n",MMDC_1.MADPSR4.R);
                printf("MMDC_1.MADPSR5 = %X\n",MMDC_1.MADPSR5.R);
                MMDC_1.MADPCR0.B.DBG_RST=0X1; //CLEAR COUNTERS.
                break;
    }
}

void dmamemcpy(void *dst, void *src, unsigned int length)
{
	DMA.TCD[0].SADDR.R = (unsigned int)(long)src;
	DMA.TCD[0].SOFF.R = 0x0008;
	DMA.TCD[0].ATTR.R = 0x0303;
	DMA.TCD[0].NBYTES.MLNO.R = length;
	DMA.TCD[0].DADDR.R = (unsigned int)(long)dst;
	DMA.TCD[0].DOFF.R = 0x0008;
	DMA.TCD[0].CITER.ELINKNO.R = 0x0001;
	DMA.TCD[0].BITER.ELINKNO.R = 0x0001;
	DMA.TCD[0].CSR.B.START = 1;
	while (DMA.TCD[0].CSR.B.DONE != 1);
	DMA.TCD[0].CSR.B.DREQ = 1;
}
	void Resample(char *dst, char *src, int newWidth, int newHeight, int width, int height);
	void ResampleG(char *dst, char *src, int newWidth, int newHeight, int width, int height);
	void GrayScale(unsigned char *dst, unsigned char *src, int width, int height);
	void DrawRectangle(unsigned char *dst, int x, int y, int width, int height, unsigned char cR, unsigned char cG, unsigned char cB);

	extern "C"
	{
		unsigned long get_uptime_microS();
	}
	
std::vector<DetectedFaceFiltered> filtered_faces;	
std::vector<DetectedFaceFiltered> filtered_faces_now;

int color_i = 0xc;

int main(int, char **)
{
	ACF_Init();
	unsigned long last_reset = get_uptime_microS();
	for (int i = 0; i < 10000; ++i)
		values_profiler[i] = 0;
  /////////////////////////////////////////////////////////////////////////////
  // Algo setup
  char *lp_copied;
  lp_copied  = (char *)0x81000000;
  memset(lp_copied, 0, 0x1000000);
  
  char *lp_buffer = (char *)0x82000000;
  memset(lp_buffer, 0, 0x1000000);
  
  XMLDocument cascades;
  if (cascades.LoadString(lbpcascade_frontalface) != XML_SUCCESS)
  {
	printf("can't open the cascades file\n");
	return -1;
  }
  
  //start at the size node
  XMLNode* node = cascades.FirstChild()->NextSibling()->NextSibling()->FirstChild()->FirstChild()->NextSibling()->NextSibling();

  {
    stringstream ss(node->ToElement()->GetText());
    ss >> windowHeight;
  }

  node = node->NextSibling();

  {
    stringstream ss(node->ToElement()->GetText());
    ss >> windowWidth;
  }

  //TODO: stage params?

  //stages
  node = node->NextSibling()->NextSibling()->NextSibling()->NextSibling();

  //int windowViewScale = 20;

  XMLNode* stageNode = node->FirstChild();

  while (stageNode)
  {
    stageNode = stageNode->NextSibling();
    lbpStage lbps;
    lbps.firstFeatureIndex = (int)lbpFeatures.size();

    XMLNode* stageSumNode = stageNode->FirstChild()->NextSibling();
    stringstream sss(stageSumNode->ToElement()->GetText());

    double dThr;
    sss >> dThr;
    lbps.thresholdFixed = STAGE_FIXED_POINT_TYPE(dThr * STAGE_FIXED_POINT_MULTIPLIER);


    XMLNode* featureNode = stageSumNode->NextSibling()->FirstChild();
    while (featureNode)
    {
      featureNode = featureNode->NextSibling();
      lbpFeature lbpf;

      XMLNode* innerNode = featureNode->FirstChild();
      stringstream fss0(innerNode->ToElement()->GetText());
      string temp;
      fss0 >> temp >> temp >> lbpf.rectangleIndex >>
        lbpf.values[0] >> lbpf.values[1] >> lbpf.values[2] >> lbpf.values[3] >>
        lbpf.values[4] >> lbpf.values[5] >> lbpf.values[6] >> lbpf.values[7];

      innerNode = innerNode->NextSibling();

      stringstream fss1(innerNode->ToElement()->GetText());

      double dLV0, dLV1;
      fss1 >> dLV0 >> dLV1;
      lbpf.leafValuesFixed[0] = STAGE_FIXED_POINT_TYPE(dLV0 * STAGE_FIXED_POINT_MULTIPLIER);
      lbpf.leafValuesFixed[1] = STAGE_FIXED_POINT_TYPE(dLV1 * STAGE_FIXED_POINT_MULTIPLIER);

      lbpFeatures.push_back(lbpf);

      featureNode = featureNode->NextSibling();
    }

    lbps.featureCount = (int)lbpFeatures.size() - lbps.firstFeatureIndex;
    lbpStages.push_back(lbps);

    stageNode = stageNode->NextSibling();
  }

  node = node->NextSibling();
  XMLNode* rectangleNode = node->FirstChild();
  while (rectangleNode)
  {
    lbpRectangle lbpr;
    stringstream rss(rectangleNode->FirstChild()->ToElement()->GetText());
    rss >> lbpr.x >> lbpr.y >> lbpr.width >> lbpr.height;

    lbpRectangles.push_back(lbpr);

    rectangleNode = rectangleNode->NextSibling();
  }
	
  //apex structs
  APEX_lbpFeature* apexLBPFeatures = new APEX_lbpFeature[lbpFeatures.size()];
  APEX_lbpStage* apexLBPStages = new APEX_lbpStage[lbpStages.size()];
  int apexLBPFeaturesSize = lbpFeatures.size() * sizeof(APEX_lbpFeature);
  int apexLBPStagesSize = lbpStages.size() * sizeof(APEX_lbpStage);

  for (unsigned int i = 0; i < lbpFeatures.size(); ++i)
  {
    lbpFeature lbpf = lbpFeatures[i];
    lbpRectangle lbpr = lbpRectangles[lbpf.rectangleIndex];
    for (int j = 0; j < 8; ++j)
    {
      apexLBPFeatures[i].values[j] = lbpf.values[j];
    }
    apexLBPFeatures[i].leafValues[0] = lbpf.leafValuesFixed[0];
    apexLBPFeatures[i].leafValues[1] = lbpf.leafValuesFixed[1];
    apexLBPFeatures[i].x = lbpr.x;
    apexLBPFeatures[i].y = lbpr.y;
    apexLBPFeatures[i].width = lbpr.width;
    apexLBPFeatures[i].height = lbpr.height;
  }

  for (unsigned int i = 0; i < lbpStages.size(); ++i)
  {
    apexLBPStages[i].threshold = lbpStages[i].thresholdFixed;
    apexLBPStages[i].featureCount = lbpStages[i].featureCount;
  }
  /////////////////////////////////////////////////////////////////////////////
  // I/O serup
  
  
  cv::Mat /*frame640*/ frame, pyramidStartFrame;

  //has to be even
  const int SIZES = 12;
  assert((SIZES % 2) == 0);
  const int MIN_FACE_RECTANGLES = 2;
  //int cusActive[SIZES] = {64, 64, 54, 54, 44, 44 };
  //int cusActive[SIZES] = { 32, 32, 26, 26, 20, 20 };
  //int cusActive[SIZES] = { 16, 16, 14, 14, 10, 10 };
  //int cusActive[SIZES] = { 40, 37, 34, 30 };
  //int cusActive[SIZES] = { 40, 36, 34, 32, 30, 28 };
  //int cusActive[SIZES] = { 42, 38, 34, 30, 26, 22 };
  //int cusActive[SIZES] =   { 24, 22 ,20, 18, 16, 14, 12, 10 };//, 26, 22 };
  int cusActive[SIZES] =   { 40, 36, 32, 28, 24, 22 ,20, 18, 16, 14, 12, 10 };//, 26, 22 };

  //const int CHUNK_WIDTH_0 = 10;
  //const int CHUNK_WIDTH_1 = 6;
  const int CHUNK_WIDTH_0 = 4;
  const int CHUNK_WIDTH_1 = 4;

  //FACE_DETECTION_10_PI process0(APEX_APEX0);
  //FACE_DETECTION_6_PI process1(APEX_APEX1);
  APU_FACE_DETECTION_LBP_4 process0(APEX_APEX0);
  APU_FACE_DETECTION_LBP_4 process1(APEX_APEX1);

  cv::Size pyramidStartSize = cv::Size(cusActive[0] * CHUNK_WIDTH_0, int((cusActive[0] * CHUNK_WIDTH_0) * (float(RESY) / float(RESX))));

  cv::Mat inputs[SIZES];

  DataDescriptor dataInCascadeSizesAndSkip(3, 1, DATATYPE_16U);

  DataDescriptor dataInCascadeFeatures(10000, 1, DATATYPE_08U);
  DataDescriptor dataInCascadeStages(200, 1, DATATYPE_08U);

  DataDescriptor dataInPixelShiftsA(64, 1, DATATYPE_08U);
  DataDescriptor dataInPixelOffsetsA(64, 1, DATATYPE_08U);

  DataDescriptor dataInPixelShiftsB(64, 1, DATATYPE_08U);
  DataDescriptor dataInPixelOffsetsB(64, 1, DATATYPE_08U);

  DataDescriptor dataOuts[SIZES];
  DataDescriptor dataOutIntegralImages[SIZES];

  uint16_t* cascadeSizesAndSkipPtr = (uint16_t*)dataInCascadeSizesAndSkip.GetDataPtr();
  cascadeSizesAndSkipPtr[0] = uint16_t(lbpFeatures.size());
  //cascadeSizesAndSkipPtr[1] = uint16_t(lbpStages.size());
  
  //APEX_STAGES = lbpFeatures.size() - 1;
  if (APEX_STAGES < 0 || APEX_STAGES >= int(lbpFeatures.size()))
  {
    APEX_STAGES = 0;
  }
  printf("apex stages: %d\n", APEX_STAGES);
  cascadeSizesAndSkipPtr[1] = uint16_t(APEX_STAGES);
  cascadeSizesAndSkipPtr[2] = SKIP_ODD ? 1 : 0;

  memcpy(dataInCascadeFeatures.GetDataPtr(), apexLBPFeatures, apexLBPFeaturesSize);
  memcpy(dataInCascadeStages.GetDataPtr(), apexLBPStages, apexLBPStagesSize);

  uint8_t pixelShiftsA[64];
  uint8_t pixelOffsetsA[64];
  uint8_t pixelShiftsB[64];
  uint8_t pixelOffsetsB[64];
  for (int i = 0; i < 64; ++i)
  {
    pixelShiftsA[i] = uint8_t(i / CHUNK_WIDTH_0);
    pixelOffsetsA[i] = uint8_t(i % CHUNK_WIDTH_0);
    pixelShiftsB[i] = uint8_t(i / CHUNK_WIDTH_1);
    pixelOffsetsB[i] = uint8_t(i % CHUNK_WIDTH_1);
  }
  memcpy(dataInPixelShiftsA.GetDataPtr(), pixelShiftsA, 64);
  memcpy(dataInPixelOffsetsA.GetDataPtr(), pixelOffsetsA, 64);
  memcpy(dataInPixelShiftsB.GetDataPtr(), pixelShiftsB, 64);
  memcpy(dataInPixelOffsetsB.GetDataPtr(), pixelOffsetsB, 64);

  #define FACE_DET_GR_IN_IMG			"INPUT_IMAGE"
#define FACE_DET_GR_IN_CASC_SZ		"INPUT_CASCADE_SIZES_AND_SKIP"
#define FACE_DET_GR_IN_CASC_FEAT	"INPUT_CASCADE_FEATURES"
#define FACE_DET_GR_IN_CASC_STAGES	"INPUT_CASCADE_STAGES"
#define FACE_DET_GR_IN_PIX_SHFT		"INPUT_PIXEL_SHIFTS"
#define FACE_DET_GR_IN_PIX_OFFS		"INPUT_PIXEL_OFFSETS"
#define FACE_DET_GR_OUT				"OUTPUT"
#define FACE_DET_GR_OUT_INTEGR_IMG	"OUTPUT_INTEGRAL_IMAGE"

  int lRetVal = 0;
  lRetVal |= process0.Initialize();
  lRetVal |= process0.ConnectIO(FACE_DET_GR_IN_CASC_SZ, dataInCascadeSizesAndSkip);
  lRetVal |= process0.ConnectIO(FACE_DET_GR_IN_CASC_FEAT, dataInCascadeFeatures);
  lRetVal |= process0.ConnectIO(FACE_DET_GR_IN_CASC_STAGES, dataInCascadeStages);
  lRetVal |= process0.ConnectIO(FACE_DET_GR_IN_PIX_SHFT, dataInPixelShiftsA);
  lRetVal |= process0.ConnectIO(FACE_DET_GR_IN_PIX_OFFS, dataInPixelOffsetsA);
  lRetVal |= process1.Initialize();
  lRetVal |= process1.ConnectIO(FACE_DET_GR_IN_CASC_SZ, dataInCascadeSizesAndSkip);
  lRetVal |= process1.ConnectIO(FACE_DET_GR_IN_CASC_FEAT, dataInCascadeFeatures);
  lRetVal |= process1.ConnectIO(FACE_DET_GR_IN_CASC_STAGES, dataInCascadeStages);
  lRetVal |= process1.ConnectIO(FACE_DET_GR_IN_PIX_SHFT, dataInPixelShiftsB);
  lRetVal |= process1.ConnectIO(FACE_DET_GR_IN_PIX_OFFS, dataInPixelOffsetsB);

  /*capture >> frame;
  frame = imread("input_faces_multiscale.png");
  if (frame.empty())
  {
    cout << "input image not found" << endl;
    return -1;
  }
  resize(frame, frame640, Size(640, int(640 * ((float)frame.rows / (float)frame.cols) + .5f)));*/
  frame = cv::Mat::zeros(720, 1280, CV_8UC3);
  
  cv::resize(frame, pyramidStartFrame, pyramidStartSize, 0, 0, cv::INTER_NEAREST);
  //cvtColor(frame640, inputs[0], CV_BGR2GRAY);
  cv::cvtColor(pyramidStartFrame, inputs[0], CV_BGR2GRAY);

  //for 6 CUs
  resize(inputs[0], inputs[1], cv::Size((inputs[0].cols * CHUNK_WIDTH_1) / CHUNK_WIDTH_0, (inputs[0].rows * CHUNK_WIDTH_1) / CHUNK_WIDTH_0));

  cv::Size sizes[SIZES];
  float scales[SIZES];
  cv::Mat outputAPEXmasks[SIZES];
  cv::Mat outputIntegralImages[SIZES];
  cv::Mat disp(1080, 1920, CV_8UC3);
  
  sizes[0] = cv::Size(inputs[0].cols, inputs[0].rows);
  scales[0] = frame.cols / float(pyramidStartFrame.cols);

  /*for (int i = 0; i < SIZES; ++i)
  {
    int originalImageIndex = i % 2;

    sizes[i] = Size((inputs[originalImageIndex].cols * cusActive[i]) / (APU_VSIZE), (inputs[originalImageIndex].rows * cusActive[i]) / (APU_VSIZE));
    //sizes[i] = Size((frame.cols * cusActive[i]) / (APU_VSIZE), (frame.rows * cusActive[i]) / (APU_VSIZE));
    scales[i] = sizes[0].width / float(sizes[i].width);

    if (i > 1)
    {
      resize(inputs[originalImageIndex], inputs[i], sizes[i]);
    }
  }*/

  for (int i = 1; i < SIZES; ++i)
  {
    int originalImageIndex = i % 2;
    int chunkWidth = originalImageIndex == 0 ? CHUNK_WIDTH_0 : CHUNK_WIDTH_1;

    int width = cusActive[i] * chunkWidth;
    float interPyramidScale = width / float(sizes[0].width);
    int height = int(sizes[0].height * interPyramidScale);

    sizes[i] = cv::Size(width, height);
    //sizes[i] = Size((frame.cols * cusActive[i]) / (APU_VSIZE), (frame.rows * cusActive[i]) / (APU_VSIZE));
    scales[i] = frame.cols / float(width);

    resize(inputs[originalImageIndex], inputs[i], sizes[i]);
  }

  DataDescriptor dataInImages[SIZES];
  for (int i = 0; i < SIZES; ++i)
  {
    dataInImages[i] = DataDescriptor();
	dataInImages[i].InitManual(sizes[i].width, sizes[i].height, inputs[i].data, inputs[i].data, DATATYPE_08U);
	
    dataOuts[i] = DataDescriptor(sizes[i].width, sizes[i].height, DATATYPE_08U);
    dataOutIntegralImages[i] = DataDescriptor(sizes[i].width, sizes[i].height, DATATYPE_32U);

    outputAPEXmasks[i] = cv::Mat(inputs[i].rows, inputs[i].cols, CV_8UC1, dataOuts[i].GetDataPtr());
    outputIntegralImages[i] = cv::Mat(inputs[i].rows, inputs[i].cols, CV_32SC1, dataOutIntegralImages[i].GetDataPtr());
  }
  
  
  // DDR buffer pointers
  void*     lppFbsVirtual[DDR_BUFFER_CNT]; ///< virtual buffer pointers
  uint32_t  lpFbsPhysical[DDR_BUFFER_CNT]; ///< physical buffer adresses
  
  //*** Init DCU Output ***
  io::FrameOutputDCU lDcuOutput(
                        WIDTH, 
                        HEIGHT, 
                        io::IO_DATA_DEPTH_08, 
                        io::IO_DATA_CH3);
  
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
  lGeo.mHorFlip = 0;
  SONY_GeometrySet(CSI_IDX_0,&lGeo);
  
  lIsp.StartCam();
  
  frame = cv::Mat(720, 1280, CV_8UC3, lp_copied);
  /////////////////////////////////////////////////////////////////////////////
  // main loop
  unsigned long t[20];
  while((lpFrame = lIsp.GetFrame()))
  {
	  
	  t[0] = get_uptime_microS();
	  frame = cv::Mat(720, 1280, CV_8UC3, lpFrame);
	 // start_ddr_profiler(0);
	 // start_ddr_profiler(1);
	//neon_memcpy_1280(lp_copied, (char *)lpFrame);
	//neon_memcpy(lp_copied, (char *)lpFrame, 1920*1080*3);
	//neon_memcpy(lp_buffer, lp_copied, 1920*1080*3);
	//cv::resize(frame, pyramidStartFrame, pyramidStartSize, 0, 0, cv::INTER_NEAREST);
	Resample((char *)pyramidStartFrame.data, (char *)frame.data, pyramidStartSize.width, pyramidStartSize.height, 1280, 720);
	GrayScale(inputs[0].data, pyramidStartFrame.data, pyramidStartFrame.cols, pyramidStartFrame.rows);
    //cv::cvtColor(pyramidStartFrame, inputs[0], CV_BGR2GRAY);
    //for B CUs
	ResampleG((char *)inputs[1].data, (char *)inputs[0].data, (inputs[0].cols * CHUNK_WIDTH_1) / CHUNK_WIDTH_0 , (inputs[0].rows * CHUNK_WIDTH_1) / CHUNK_WIDTH_0,inputs[0].cols, inputs[0].rows);
    //resize(inputs[0], inputs[1], Size((inputs[0].cols * CHUNK_WIDTH_1) / CHUNK_WIDTH_0, (inputs[0].rows * CHUNK_WIDTH_1) / CHUNK_WIDTH_0), 0, 0, cv::INTER_NEAREST);
    for (int i = 1; i < SIZES; ++i)
    {
      int originalImageIndex = i % 2;
      //resize(inputs[originalImageIndex], inputs[i], sizes[i], 0, 0, cv::INTER_NEAREST);
	  ResampleG((char *)inputs[i].data, (char *)inputs[originalImageIndex].data, sizes[i].width, sizes[i].height, inputs[originalImageIndex].cols, inputs[originalImageIndex].rows);
    }
	t[1] = get_uptime_microS();
	/*uint32_t* diiPtr;
    for (int i = 0; i < SIZES; ++i)
    {
      diiPtr = (uint32_t*)dataInImages[i].GetDataPtr();
      memcpy(diiPtr, inputs[i].data, inputs[i].cols * inputs[i].rows);
    }*/

    {
      int index0 = SIZES - 2;
      int index1 = SIZES - 1;

      lRetVal |= process1.ConnectIO("INPUT_IMAGE", dataInImages[index1]);
      lRetVal |= process1.ConnectIO("OUTPUT", dataOuts[index1]);
      lRetVal |= process1.ConnectIO("OUTPUT_INTEGRAL_IMAGE", dataOutIntegralImages[index1]);
      lRetVal |= process1.Start();
      lRetVal |= process1.Wait();

      lRetVal |= process0.ConnectIO("INPUT_IMAGE", dataInImages[index0]);
      lRetVal |= process0.ConnectIO("OUTPUT", dataOuts[index0]);
      lRetVal |= process0.ConnectIO("OUTPUT_INTEGRAL_IMAGE", dataOutIntegralImages[index0]);
      lRetVal |= process0.Start();
      lRetVal |= process0.Wait();
    }

    int iLimit = (SIZES / 2) - 1;
    for (int i = iLimit; i >= 0; --i)
    {
      int armIndex0 = (i << 1);
      int armIndex1 = (i << 1) + 1;
      int apexIndex0 = armIndex0 - 2;
      int apexIndex1 = armIndex1 - 2;

      
      //memcpy(outputAPEXmasks[armIndex1].data, dataOuts[armIndex1].GetDataPtr(), inputs[armIndex1].cols * inputs[armIndex1].rows);
      //memcpy(outputIntegralImages[armIndex1].data, dataOutIntegralImages[armIndex1].GetDataPtr(), inputs[armIndex1].cols * inputs[armIndex1].rows * 4);

      if (i != 0)
      {
        lRetVal |= process1.ConnectIO("INPUT_IMAGE", dataInImages[apexIndex1]);
        lRetVal |= process1.ConnectIO("OUTPUT", dataOuts[apexIndex1]);
        lRetVal |= process1.ConnectIO("OUTPUT_INTEGRAL_IMAGE", dataOutIntegralImages[apexIndex1]);
        lRetVal |= process1.Start();
	lRetVal |= process1.Wait();
      }
t[7] = get_uptime_microS();
     // FinishDetectionOnHost(outputAPEXmasks[armIndex1], outputIntegralImages[armIndex1], APEX_STAGES, SKIP_ODD);
t[8] = get_uptime_microS();
      
      //memcpy(outputAPEXmasks[armIndex0].data, dataOuts[armIndex0].GetDataPtr(), inputs[armIndex0].cols * inputs[armIndex0].rows);
     // memcpy(outputIntegralImages[armIndex0].data, dataOutIntegralImages[armIndex0].GetDataPtr(), inputs[armIndex0].cols * inputs[armIndex0].rows * 4);

      if (i != 0)
      {
        lRetVal |= process0.ConnectIO("INPUT_IMAGE", dataInImages[apexIndex0]);
        lRetVal |= process0.ConnectIO("OUTPUT", dataOuts[apexIndex0]);
        lRetVal |= process0.ConnectIO("OUTPUT_INTEGRAL_IMAGE", dataOutIntegralImages[apexIndex0]);
        lRetVal |= process0.Start();
	lRetVal |= process0.Wait();
      }
t[9] = get_uptime_microS();
    //  FinishDetectionOnHost(outputAPEXmasks[armIndex0], outputIntegralImages[armIndex0], APEX_STAGES, SKIP_ODD);
t[10] = get_uptime_microS();
    } 
	
	
	//memcpy(lp_copied, (char *)lpFrame, 1920*1080*3);
	//memcpy(lp_buffer, lp_copied, 1920*1080*3);
	vector<DetectedFace> faces;

    for (int i = 0; i < SIZES; ++i)
    {
      int scaledWindowWidth = int(windowWidth * scales[i]);
      int scaledWindowHeight = int(windowHeight * scales[i]);
      for (int y = windowHeight; y < inputs[i].rows; y += 2)
      {
        for (int x = 0; x < inputs[i].cols - windowWidth; x += 2)
        {
          if (outputAPEXmasks[i].at<uint8_t>(y, x) != 0)
          {
            int realX = int(x * scales[i]);
            int realY = int(y * scales[i] - scaledWindowHeight);
            FaceRectangle fr(realX, realY, scaledWindowWidth, scaledWindowHeight);
			//printf("%d, %d: %d, %d\n", realX, realY, scaledWindowWidth, scaledWindowHeight);
            bool addNewFace = true;
            for (unsigned int j = 0; j < faces.size(); ++j)
            {
              if (faces[j].TryAddFaceRectangle(fr))
              {
                addNewFace = false;
                break;
              }
            }

            if (addNewFace)
            {
              faces.push_back(DetectedFace(fr));
            }
          }
        }
      }
    }
	
	for (int j = 0; j < filtered_faces.size(); ++j)
	{
		filtered_faces[j].framesNotDetected += 1;
	}
	
	filtered_faces_now.clear();
	unsigned long passed = 0x0;
	for (int i = 0; i < faces.size(); ++i)
	{
		bool found_match = false;
		int found_j = -1;
		int bestx = 9999;
		int besty = 9999;
		FaceRectangle fr = faces[i].GetMidFaceRectangle();
		for (int j = 0; j < filtered_faces.size(); ++j)
		{
			FaceRectangle fr_filtered = filtered_faces[j]._detectedFace.testingFaceRectangle;
			int xdiff = abs(    (fr.x + (fr.width >> 1)) - (fr_filtered.x + (fr_filtered.width >> 1)) );
			int ydiff = abs(    (fr.y + (fr.height >> 1)) - (fr_filtered.y + (fr_filtered.height >> 1)) );
			int wdiff = abs(    fr.width - fr_filtered.width);
			int hdiff = abs(    fr.height - fr_filtered.height);
			if ((passed & (1<<j)) == 0 && xdiff < fr.width && ydiff < fr.height && wdiff < fr.width && hdiff < fr.height &&  xdiff < bestx && ydiff < besty)
				{
					found_match = true;
					found_j = j;
					bestx = xdiff;
					besty = ydiff;
					passed |= 1 << j;
				}
		}
		if (found_match)
		{
			filtered_faces[found_j].Update(faces[i]);
			filtered_faces_now.push_back(filtered_faces[found_j]);
		}
		else
		{
			filtered_faces_now.push_back(DetectedFaceFiltered(faces[i]));
			if (filtered_faces_now.size() & 0x00000002) filtered_faces_now[filtered_faces_now.size() - 1].color[0] = 255;
			else filtered_faces_now[filtered_faces_now.size() - 1].color[0] = 0;
			if (filtered_faces_now.size() & 0x00000001) filtered_faces_now[filtered_faces_now.size() - 1].color[1] = 255;
			else filtered_faces_now[filtered_faces_now.size() - 1].color[1] = 0;
			if (filtered_faces_now.size() & 0x00000004) filtered_faces_now[filtered_faces_now.size() - 1].color[2] = 255;
			else filtered_faces_now[filtered_faces_now.size() - 1].color[2] = 0;
			++color_i;
		}			
	}
	
	for (int j = 0; j < filtered_faces.size(); ++j)
	{
		if ((passed & (1<<j)) == 0 && filtered_faces[j].framesNotDetected > 0 && filtered_faces[j].framesNotDetected < 8)
			
			filtered_faces_now.push_back(filtered_faces[j]);
	}
	filtered_faces.clear();
	for (int j = 0; j < filtered_faces_now.size(); ++j)
	{
		filtered_faces.push_back(filtered_faces_now[j]);
		
	}
	
	if (filtered_faces.size() == 0) color_i = 0xc;
	
    int finalFaceCount = 0;
    for (unsigned int i = 0; i < filtered_faces.size(); ++i)
    {
	
      if (filtered_faces[i].framesDetected >= 5)
      {
        ++finalFaceCount;
        FaceRectangle fr = filtered_faces[i]._detectedFace.testingFaceRectangle;
		DrawRectangle(frame.data, fr.x, fr.y, fr.width, fr.height, filtered_faces[i].color[0], filtered_faces[i].color[1], filtered_faces[i].color[2]);
      }
    }

	
	neon_memcpy_1280_to_hd((char *)lp_buffer, (char *)lpFrame);
	lDcuOutput.PutFrame(lp_buffer, false);
	t[2] = get_uptime_microS();
	printf("Frame done in %d ms.\n", (t[2] - t[0]) / 1000);
	
	unsigned long now = get_uptime_microS();
	if (now - last_reset > 1800000000)
	{ 
		*((uint32_t *)0x4004a004) = 0x00005AF0;
		*((uint32_t *)0x4004a004) = 0x0000A50F;
	}
	

  }
} // main()

//***************************************************************************

void DrawRectangle(unsigned char *dst, int x, int y, int width, int height, unsigned char cR, unsigned char cG, unsigned char cB)
{
	int offx11 = x * 3;
	int offx12 = (x + 1) * 3;
	int offx13 = (x - 1) * 3;
	int offx21 = (x + width) * 3;
	int offx22 = (x + 1 + width) * 3;
	int offx23 = (x - 1 + width) * 3;
	for (int cy = y; cy < y + height; ++cy)
	{
		int offy = cy * 1280 * 3;
		if (cy > 1 && cy < 719)
		{
			if (x > 1 && x < 1279)
			{
				dst[offy + offx13] =     cR;
				dst[offy + offx13 + 1] = cG;
				dst[offy + offx13 + 2] = cB;
				dst[offy + offx11] =     cR;
				dst[offy + offx11 + 1] = cG;
				dst[offy + offx11 + 2] = cB;
				dst[offy + offx12] =     cR;
				dst[offy + offx12 + 1] = cG;
				dst[offy + offx12 + 2] = cB;
			}
			if ((x + width) > 0 && (x + width) < 1280)
			{
				dst[offy + offx23] =     cR;
				dst[offy + offx23 + 1] = cG;
				dst[offy + offx23 + 2] = cB;
				dst[offy + offx21] =     cR;
				dst[offy + offx21 + 1] = cG;
				dst[offy + offx21 + 2] = cB;
				dst[offy + offx22] =     cR;
				dst[offy + offx22 + 1] = cG;
				dst[offy + offx22 + 2] = cB;
			}
		}
	}
	int offy11 = y * 1280 * 3;
	int offy12 = (y + 1) * 1280 * 3;
	int offy13 = (y - 1) * 1280 * 3;
	int offy21 = (y + height) * 1280 * 3;
	int offy22 = (y + height + 1) * 1280 * 3;
	int offy23 = (y + height - 1) * 1280 * 3;
	
	for (int cx = x; cx < x + width; ++cx)
	{
		int offx = cx * 3;
		if (cx > 1 && cx < 1279)
		{
			if (y > 1 && y < 719)
			{
				dst[offy13 + offx] =     cR;
				dst[offy13 + offx + 1] = cG;
				dst[offy13 + offx + 2] = cB;
				dst[offy11 + offx] =     cR;
				dst[offy11 + offx + 1] = cG;
				dst[offy11 + offx + 2] = cB;
				dst[offy12 + offx] =     cR;
				dst[offy12 + offx + 1] = cG;
				dst[offy12 + offx + 2] = cB;
			}
			if ((y + height) > 1 && (y + height) < 719)
			{
				dst[offy23 + offx] =     cR;
				dst[offy23 + offx + 1] = cG;
				dst[offy23 + offx + 2] = cB;
				dst[offy21 + offx] =     cR;
				dst[offy21 + offx + 1] = cG;
				dst[offy21 + offx + 2] = cB;
				dst[offy22 + offx] =     cR;
				dst[offy22 + offx + 1] = cG;
				dst[offy22 + offx + 2] = cB;
			}
		}
	}
}

void Resample(char *dst, char *src, int newWidth, int newHeight, int width, int height)
    {
        double scaleWidth =  (double)newWidth / (double)width;
        double scaleHeight = (double)newHeight / (double)height;

        for(int cy = 0; cy < newHeight; cy++)
        {
            for(int cx = 0; cx < newWidth; cx++)
            {
                int pixel = (cy * (newWidth *3)) + (cx*3);
                int nearestMatch =  (((int)(cy / scaleHeight) * (width *3)) + ((int)(cx / scaleWidth) *3) );
                
                dst[pixel    ] =  src[nearestMatch    ];
                dst[pixel + 1] =  src[nearestMatch + 1];
                dst[pixel + 2] =  src[nearestMatch + 2];
            }
        }
    }
	
void ResampleG(char *dst, char *src, int newWidth, int newHeight, int width, int height)
    {
        double scaleWidth =  (double)newWidth / (double)width;
        double scaleHeight = (double)newHeight / (double)height;

        for(int cy = 0; cy < newHeight; cy++)
        {
            for(int cx = 0; cx < newWidth; cx++)
            {
                int pixel = (cy * (newWidth)) + (cx);
                int nearestMatch =  (((int)(cy / scaleHeight) * (width)) + ((int)(cx / scaleWidth)) );
                
                dst[pixel    ] =  src[nearestMatch    ];
            }
        }
    }
	
void GrayScale(unsigned char *dst, unsigned char *src, int width, int height)
    {
        for(int cy = 0; cy < height; cy++)
        {
            for(int cx = 0; cx < width; cx++)
            {
				int pixel = (cy * (width * 3)) + (cx * 3);
				dst[(cy * (width)) + (cx)] = 0.1140 * src[pixel] + 0.5870 * src[pixel + 1] + 0.2989 * src[pixel + 2];
            }
        }
    }

	
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

inline void neon_memcpy(char* dst, char* src, long size)
{
  long simd_pixels = size & ~15; 
  long simd_iterations = simd_pixels / 64;
  long simd_sync = 20;
  
  char *dst_local = dst;
  char *src_local = src;
  __asm volatile( "neon_memcpy_loop: \n\t"
		      "LD1 {V0.16B, V1.16B, V2.16B, V3.16B}, [%[src_local]], #64	\n\t"
			  "ST1 {V0.16B, V1.16B, V2.16B, V3.16B}, [%[dst_local]], #64	\n\t"
			  
			  "subs %[sync],%[sync],#1 \n\t"
			  "bne neon_memcpy_next \n\t"
			  "mov %[sync], #20 \n\t"
			  "DSB SY\n\t"
			  "neon_memcpy_next: \n\t"
			  "subs %[iterations],%[iterations],#1 \n\t"
			  "bne neon_memcpy_loop \n\t"
			  
		      
		      : [src_local]"+r"(src_local), [dst_local] "+r"(dst_local), [iterations]"+r"(simd_iterations), [sync]"+r"(simd_sync)
		      : 
		   );
}

inline void neon_memcpy_1280(char* dst, char* src)
{
  char *dst_local = dst;
  char *src_local = src;
  long line_size = (1280 * 3) / 48;
  long line_iterations = line_size;
  long height_iterations = 720;
  long stride_src = 640 * 3;
 
    __asm volatile( "1: \n\t"
			  "PRFM PLDL1KEEP, [%[src_local]] \n\t"
		      "LD3 {V0.16B, V1.16B, V2.16B}, [%[src_local]], #48	\n\t"
			  "ST3 {V0.16B, V1.16B, V2.16B}, [%[dst_local]], #48	\n\t"
			  "DSB SY\n\t"
			  "subs %[line_iterations],%[line_iterations],#1 \n\t"
		      "bne 1b \n\t"
			  
			  "mov %[line_iterations], %[line_size] \n\t"
			  "add %[src_local],%[src_local],%[stride_src] \n\t"
			  
			  "subs %[height_iterations],%[height_iterations],#1 \n\t"
			  "bne 1b \n\t"
			  
			  
		      : [src_local]"+r"(src_local), 
			    [dst_local] "+r"(dst_local),  
				[line_iterations]"+r"(line_iterations),
				[height_iterations]"+r"(height_iterations),
				[line_size]"+r"(line_size),
				[stride_src]"+r"(stride_src)		
		      : 
		   );
    
}

inline void neon_memcpy_rotate_1280(char* dst, char* src)
{
  char *dst_local = dst + (180 * 1920 * 3) + 320 * 3;
  char *src_local = src + 1280*720*3 - 24;
  long line_size = (1280 * 3) / 24;
  long line_iterations = line_size;
  long height_iterations = 720;
  long stride_dst = 640 * 3;
 
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

inline void neon_memcpy_1280_to_hd(char* dst, char* src)
{
  char *dst_local = dst + (180 * 1920 * 3) + 320 * 3;
  char *src_local = src;
  long line_size = (1280 * 3) / 24;
  long line_iterations = line_size;
  long height_iterations = 720;
  long stride_dst = 640 * 3;
 
    __asm volatile( "1: \n\t"
			  "PRFM PLDL1KEEP, [%[src_local], #-24] \n\t"
		      "LD3 {V0.8B, V1.8B, V2.8B}, [%[src_local]], #24	\n\t"
			  "ST3 {V0.B, V1.B, V2.B}[0], [%[dst_local]], #3		\n\t"
			  "ST3 {V0.B, V1.B, V2.B}[1], [%[dst_local]], #3		\n\t"
			  "ST3 {V0.B, V1.B, V2.B}[2], [%[dst_local]], #3		\n\t"
			  "ST3 {V0.B, V1.B, V2.B}[3], [%[dst_local]], #3		\n\t"
			  "ST3 {V0.B, V1.B, V2.B}[4], [%[dst_local]], #3		\n\t"
			  "ST3 {V0.B, V1.B, V2.B}[5], [%[dst_local]], #3		\n\t"
			  "ST3 {V0.B, V1.B, V2.B}[6], [%[dst_local]], #3		\n\t"
			  "ST3 {V0.B, V1.B, V2.B}[7], [%[dst_local]], #3		\n\t"
			  
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