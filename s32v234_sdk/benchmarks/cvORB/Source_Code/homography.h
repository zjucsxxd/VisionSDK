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

#ifndef ORB_HOMOGRAPHY_H
#define ORB_HOMOGRAPHY_H

#include <opencv2/opencv.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <vector>
using namespace cv;
using namespace std;
#include "descriptor.h"


extern const int FAST9_THRESHOLD;
extern const int MATCH_DIST_LIMIT;
extern const int RANGE_CHECK;
extern const double CONTRAST;
extern const int NON_EMU_FRAMES;
extern const unsigned int MAX_FEATURE_POINTS;



//Finds feature points using the FAST9 algorithm and creates feature point descriptors
int FindFeatures(const Mat& inDataDescriptor, Mat& outDataDescriptor0,
	vector<KeyPoint>& filteredKeyPoints, vector<Feature>& features,	unsigned char* tempDataF,
	unsigned char* tempDataG);

//Matches two sets of feature point descriptors
int FindMatches( vector<Feature>& features0, vector<Feature>& features1, vector<DMatch>& matches
				, unsigned int minDistLimit,	unsigned int rangeCheck
				);
/*
//Feature point detection and matching combined in parallel (parallel only when using APEX descriptor matching)
int FindFeaturesAndMatchParallel(const Mat& f_input,
	DataDescriptor& f_inDataDescriptor,
	DataDescriptor& f_outDataDescriptor0,
	DataDescriptor& f_outDataDescriptor1,
	APU_FAST9& f_process,
	vector<KeyPoint>& f_filteredKeyPoints,
	vector<Feature>& f_features,
	unsigned char* f_inDescriptorDataF,
	unsigned char* f_inDescriptorDataG,
	unsigned char* f_outFeaturesDataF,
	unsigned char* f_outFeaturesDataG,
	vector<Feature>& m_features0,
	vector<Feature>& m_features1,
	vector<DMatch>& m_matches,
	unsigned int m_minDistLimit,
	unsigned int mRangeCheck,
	APU_MATCH_DESCRIPTORS& m_process,
	DataDescriptor& m_matchesData0,
	DataDescriptor& m_matchesData1,
	DataDescriptor& m_descriptorsData0,
	DataDescriptor& m_descriptorsData1,
	DataDescriptor& m_descriptorConfiguration,
	unsigned int m_matchingDataChunkX,
	unsigned int m_matchingDataChunkY,
	unsigned int m_cuCount,
	bool apu_matching
	);*/

#endif
