#include <FaceDetector.h>
#include <sstream>

int windowWidth = 1, windowHeight = 1;
int APEX_STAGES = 0;
int cusActive[SIZES] =   { 26, 26, 24 ,22, 20, 18, 16, 14 };//, 26, 22 };

void DrawRectangle(unsigned char *dst, int x, int y, int width, int height)
{
	int offx11 = x * 3 + 1;
	int offx12 = (x + 1) * 3 + 1;
	int offx13 = (x - 1) * 3 + 1;
	int offx21 = (x + width) * 3 + 1;
	int offx22 = (x + 1 + width) * 3 + 1;
	int offx23 = (x - 1 + width) * 3 + 1;
	for (int cy = y; cy < y + height; ++cy)
	{
		int offy = cy * 1280 * 3;
		if (cy > 1 && cy < 719)
		{
			if (x > 1 && x < 1279)
			{
				dst[offy + offx13] = 255;
				dst[offy + offx11] = 255;
				dst[offy + offx12] = 255;
			}
			if ((x + width) > 0 && (x + width) < 1280)
			{
				dst[offy + offx23] = 255;
				dst[offy + offx21] = 255;
				dst[offy + offx22] = 255;
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
		int offx = cx * 3 + 1;
		if (cx > 1 && cx < 1279)
		{
			if (y > 1 && y < 719)
			{
				dst[offy13 + offx] = 255;
				dst[offy11 + offx] = 255;
				dst[offy12 + offx] = 255;
			}
			if ((y + height) > 1 && (y + height) < 719)
			{
				dst[offy23 + offx] = 255;
				dst[offy21 + offx] = 255;
				dst[offy22 + offx] = 255;
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
	
FaceDetector::FaceDetector(): process0(APEX_APEX0), process1(APEX_APEX1)
{
	using namespace icp;
	using namespace std;
  
	dataInCascadeSizesAndSkip.Init(3, 1, DATATYPE_16U);
	dataInCascadeFeatures.Init(10000, 1, DATATYPE_08U);
	dataInCascadeStages.Init(200, 1, DATATYPE_08U);
	dataInPixelShiftsA.Init(64, 1, DATATYPE_08U);
	dataInPixelOffsetsA.Init(64, 1, DATATYPE_08U);
	dataInPixelShiftsB.Init(64, 1, DATATYPE_08U);
	dataInPixelOffsetsB.Init(64, 1, DATATYPE_08U);
	
	InitCascades();
	InitData();
}

void FaceDetector::MarkFaces(void * lpFrame)
{
	int finalFaceCount = 0;
    for (unsigned int i = 0; i < faces.size(); ++i)
    {
      if (faces[i].faceRectangleCount >= MIN_FACE_RECTANGLES)
      {
        ++finalFaceCount;
        FaceRectangle fr = faces[i].GetMidFaceRectangle();
        
		DrawRectangle((unsigned char *)lpFrame, fr.x, fr.y, fr.width, fr.height);
		
      }
    }
}

void FaceDetector::GetFaces(void * lpFrame)
{
	using namespace icp;
	using namespace std;
	
	Resample((char *)pyramidStartFrame.GetDataPtr(), (char *)lpFrame, pyramidStartSize.width, pyramidStartSize.height, 1280, 720);
	GrayScale((unsigned char *)dataInImages[0].GetDataPtr(), (unsigned char *)pyramidStartFrame.GetDataPtr(), pyramidStartFrame.GetWidth(), pyramidStartFrame.GetHeight());
    ResampleG((char *)dataInImages[1].GetDataPtr(), (char *)dataInImages[0].GetDataPtr(), (sizes[0].width * CHUNK_WIDTH_1) / CHUNK_WIDTH_0 , (sizes[0].height * CHUNK_WIDTH_1) / CHUNK_WIDTH_0,sizes[0].width, sizes[0].height);
    for (int i = 1; i < SIZES; ++i)
    {
      int originalImageIndex = i % 2;
      ResampleG((char *)dataInImages[i].GetDataPtr(), (char *)dataInImages[originalImageIndex].GetDataPtr(), sizes[i].width, sizes[i].height, sizes[originalImageIndex].width, sizes[originalImageIndex].height);
    }
	
	int index0 = SIZES - 2;
    int index1 = SIZES - 1;

    lRetVal |= process1.ConnectIO("INPUT_IMAGE", dataInImages[index1]);
    lRetVal |= process1.ConnectIO("OUTPUT", dataOuts[index1]);
    lRetVal |= process1.ConnectIO("OUTPUT_INTEGRAL_IMAGE", dataOutIntegralImages[index1]);
    lRetVal |= process1.Start();

    lRetVal |= process0.ConnectIO("INPUT_IMAGE", dataInImages[index0]);
    lRetVal |= process0.ConnectIO("OUTPUT", dataOuts[index0]);
    lRetVal |= process0.ConnectIO("OUTPUT_INTEGRAL_IMAGE", dataOutIntegralImages[index0]);
    lRetVal |= process0.Start();
    
    int iLimit = (SIZES / 2) - 1;
    for (int i = iLimit; i >= 0; --i)
    {
      int armIndex0 = (i << 1);
      int armIndex1 = (i << 1) + 1;
      int apexIndex0 = armIndex0 - 2;
      int apexIndex1 = armIndex1 - 2;

      lRetVal |= process1.Wait();
    
      if (i != 0)
      {
        lRetVal |= process1.ConnectIO("INPUT_IMAGE", dataInImages[apexIndex1]);
        lRetVal |= process1.ConnectIO("OUTPUT", dataOuts[apexIndex1]);
        lRetVal |= process1.ConnectIO("OUTPUT_INTEGRAL_IMAGE", dataOutIntegralImages[apexIndex1]);
        lRetVal |= process1.Start();
      }

      FinishDetectionOnHost(armIndex1);

      lRetVal |= process0.Wait();

      if (i != 0)
      {
        lRetVal |= process0.ConnectIO("INPUT_IMAGE", dataInImages[apexIndex0]);
        lRetVal |= process0.ConnectIO("OUTPUT", dataOuts[apexIndex0]);
        lRetVal |= process0.ConnectIO("OUTPUT_INTEGRAL_IMAGE", dataOutIntegralImages[apexIndex0]);
        lRetVal |= process0.Start();
      }

      FinishDetectionOnHost(armIndex0);

    } 	
	faces.clear();
	
	for (int i = 0; i < SIZES; ++i)
    {
      int scaledWindowWidth = int(windowWidth * scales[i]);
      int scaledWindowHeight = int(windowHeight * scales[i]);
	  unsigned char *dataoutdata = (unsigned char *)dataOuts[i].GetDataPtr();
      for (int y = windowHeight; y < sizes[i].height; y += 2)
      {
        for (int x = 0; x < sizes[i].width - windowWidth; x += 2)
        {
          if (dataoutdata[y * dataOuts[i].GetWidth() + x] != 0)
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

	
    int finalFaceCount = 0;
    for (unsigned int i = 0; i < faces.size(); ++i)
    {
      if (faces[i].faceRectangleCount >= MIN_FACE_RECTANGLES)
      {
        ++finalFaceCount;
        FaceRectangle fr = faces[i].GetMidFaceRectangle();
        
		DrawRectangle((unsigned char *)lpFrame, fr.x, fr.y, fr.width, fr.height);
		
      }
    }
}

void FaceDetector::InitData()
{
  using namespace icp;
  using namespace std;


  pyramidStartSize.Set(cusActive[0] * CHUNK_WIDTH_0, int((cusActive[0] * CHUNK_WIDTH_0) * (float(RESY) / float(RESX))));
  pyramidStartFrame.Init(pyramidStartSize.width, pyramidStartSize.height, DATATYPE_08U);
  
 
  uint16_t* cascadeSizesAndSkipPtr = (uint16_t*)dataInCascadeSizesAndSkip.GetDataPtr();
  cascadeSizesAndSkipPtr[0] = uint16_t(lbpFeatures.size());
  
  if (APEX_STAGES < 0 || APEX_STAGES >= int(lbpFeatures.size()))
  {
    APEX_STAGES = 0;
  }
  
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
  #define FACE_DET_GR_IN_CASC_FEAT		"INPUT_CASCADE_FEATURES"
  #define FACE_DET_GR_IN_CASC_STAGES	"INPUT_CASCADE_STAGES"
  #define FACE_DET_GR_IN_PIX_SHFT		"INPUT_PIXEL_SHIFTS"
  #define FACE_DET_GR_IN_PIX_OFFS		"INPUT_PIXEL_OFFSETS"
  #define FACE_DET_GR_OUT				"OUTPUT"
  #define FACE_DET_GR_OUT_INTEGR_IMG	"OUTPUT_INTEGRAL_IMAGE"

  
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
  
  sizes[0].Set((pyramidStartSize.width * CHUNK_WIDTH_1) / CHUNK_WIDTH_0, (pyramidStartSize.height * CHUNK_WIDTH_1) / CHUNK_WIDTH_0);
  scales[0] = RESX / float(sizes[0].width);
  
  for (int i = 1; i < SIZES; ++i)
  {
    int originalImageIndex = i % 2;
    int chunkWidth = originalImageIndex == 0 ? CHUNK_WIDTH_0 : CHUNK_WIDTH_1;

    int width = cusActive[i] * chunkWidth;
    float interPyramidScale = width / float(sizes[0].width);
    int height = int(sizes[0].height * interPyramidScale);

    sizes[i].Set(width, height);
    scales[i] = RESX / float(width);

  }

  
  for (int i = 0; i < SIZES; ++i)
  {
	dataInImages[i].Init(sizes[i].width, sizes[i].height, DATATYPE_08U);
	
    dataOuts[i].Init(sizes[i].width, sizes[i].height, DATATYPE_08U);
    dataOutIntegralImages[i].Init(sizes[i].width, sizes[i].height, DATATYPE_32U);
  }
}

void FaceDetector::InitCascades()
{
  using namespace icp;
  using namespace std;
  using namespace tinyxml2;
  
  
  cascades.LoadString(lbpcascade_frontalface);
  
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

  //stages
  node = node->NextSibling()->NextSibling()->NextSibling()->NextSibling();

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
  apexLBPFeatures = new APEX_lbpFeature[lbpFeatures.size()];
  apexLBPStages = new APEX_lbpStage[lbpStages.size()];
  apexLBPFeaturesSize = lbpFeatures.size() * sizeof(APEX_lbpFeature);
  apexLBPStagesSize = lbpStages.size() * sizeof(APEX_lbpStage);

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
}



void FaceDetector::FinishDetectionOnHost(int index)
{
  int skip = SKIP_ODD ? 2 : 1;
  int sizey = dataOutIntegralImages[index].GetHeight() - windowHeight;
  int sizex = dataOutIntegralImages[index].GetWidth() - windowWidth;
  unsigned char *dataoutdata = (unsigned char *)dataOuts[index].GetDataPtr();
  int *iidata = (int *)dataOutIntegralImages[index].GetDataPtr();
  for (int y = 0; y < sizey; y += skip)
  {
    for (int x = 0; x < sizex; x += skip)
    {
      if (dataoutdata[(y + windowHeight) * dataOuts[index].GetWidth() + x] == 0)
      {
        continue;
      }

      bool detected = true;
      for (int si = APEX_STAGES; si < (int)lbpStages.size(); ++si)
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
                value = iidata[finalY * dataOutIntegralImages[index].GetWidth() + finalX];
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
		  dataoutdata[(y + windowHeight) * dataOuts[index].GetWidth() + x] = 0;
      }
    }
  }
}

FaceRectangle::FaceRectangle(int aX, int aY, int aWidth, int aHeight) : x(aX), y(aY), width(aWidth), height(aHeight){}

bool FaceRectangle::ContainsCenter(FaceRectangle& otherRectangle)
  {
    int cxOffset = otherRectangle.x + (otherRectangle.width >> 1) - x;
    int cyOffset = otherRectangle.y + (otherRectangle.height >> 1) - y;

    return (cxOffset >= 0 && cxOffset <= width && cyOffset >= 0 && cyOffset <= height);
  }
  
DetectedFace::DetectedFace(FaceRectangle& faceRectangle):
    testingFaceRectangle(faceRectangle),
    minFaceRectangle(faceRectangle),
    maxFaceRectangle(faceRectangle),
    faceRectangleCount(1)
  {}
  
bool DetectedFace::TryAddFaceRectangle(FaceRectangle& faceRectangle)
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

FaceRectangle DetectedFace::GetMidFaceRectangle()
  {
    return FaceRectangle(
      (minFaceRectangle.x + maxFaceRectangle.x) >> 1,
      (minFaceRectangle.y + maxFaceRectangle.y) >> 1,
      (minFaceRectangle.width + maxFaceRectangle.width) >> 1,
      (minFaceRectangle.height + maxFaceRectangle.height) >> 1);
  }