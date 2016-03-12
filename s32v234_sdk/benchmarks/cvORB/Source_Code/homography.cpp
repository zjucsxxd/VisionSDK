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

#include "fast9.h"
#include "nms.h"
#include "homography.h"

const int FAST9_THRESHOLD = 15; /// for pixel differences to centroid below this threshold, pixels are classified as being similar
const int MATCH_DIST_LIMIT = 40; /// the maximal allowed Hamming distance between two pixels in order to be considered for matching
const int RANGE_CHECK = 10; /// The minimal difference between the two most similar pixels of one Match
const double CONTRAST = 1.5; /// Not used

const unsigned int MAX_FEATURE_POINTS = 512; ///

#include "descriptor.h"
#include <opencv2/opencv.hpp>
#include <iostream>

#include <fstream>
#include <map>
#include <stdlib.h>
using namespace cv;
using namespace std;

int FindFeatures(const Mat& inDataDescriptor,
	Mat& outDataDescriptor0,
	vector<KeyPoint>& filteredKeyPoints,
	vector<Feature>& features,
	unsigned char* tempDataF,
	unsigned char* tempDataG)
{
	int lRetVal = 0;

	int xOffs = 3, yOffs = 3;

	int lSrcWidth = inDataDescriptor.cols;
	int lSrcHeight = inDataDescriptor.rows;
	
	Mat img1Score(lSrcWidth, lSrcHeight, inDataDescriptor.type());
		img1Score = 0;

	unsigned char aThreshold = FAST9_THRESHOLD;
	apu_fast9_unsuppressed_score(inDataDescriptor.data + yOffs*lSrcWidth + xOffs, img1Score.data + yOffs*lSrcWidth + xOffs,
		sizeof(unsigned char)*lSrcWidth, sizeof(unsigned char)*lSrcWidth,
		lSrcWidth-2*xOffs-1, lSrcHeight-2*yOffs-1, aThreshold);

	xOffs = 1; yOffs = 1;
	nms(img1Score.data + yOffs*lSrcWidth + xOffs, outDataDescriptor0.data + yOffs*lSrcWidth + xOffs, sizeof(unsigned char)*lSrcWidth, sizeof(unsigned char)*lSrcWidth, lSrcWidth-2*xOffs-1, lSrcHeight-2*yOffs-1);
	
	unsigned char *outDataF = (unsigned char *)outDataDescriptor0.data;
	unsigned char *outDataG = (unsigned char *)inDataDescriptor.data;

	const int minBorderDist = 30;

	memcpy(tempDataF, outDataF, lSrcWidth * lSrcHeight);
	memcpy(tempDataG, outDataG, lSrcWidth * lSrcHeight);
	
	multimap<unsigned char, Feature> featMap;

	// compute the image's descriptors
	for (int y = minBorderDist; y < lSrcHeight - minBorderDist; ++y)
	{
		for (int x = minBorderDist; x < lSrcWidth - minBorderDist; ++x)
		{
			Point p(x, y);
			int index = y * lSrcWidth + x;
			if (tempDataF[index] > 0)
			{
				Feature f;
				float xBase, yBase;
				//GetCentroidRotation(tempDataG, lSrcWidth, p, &xBase, &yBase);
				GetCentroidRotationLUT(tempDataG, lSrcWidth, p, &xBase, &yBase);
				f.descriptor = CreateDescriptorRotated(tempDataG, lSrcWidth, p, xBase, yBase);
				f.position = p;
				featMap.insert(make_pair(tempDataF[index], f));
				/*
				features.push_back(f);
				filteredKeyPoints.push_back(KeyPoint(p, 1.f));
				if (features.size() >= MAX_FEATURE_POINTS)
				{
					return lRetVal;
				}*/
			}
		}
	}

	int i = 0;
	for (multimap<unsigned char, Feature>::reverse_iterator it = featMap.rbegin(); it != featMap.rend() && i < MAX_FEATURE_POINTS; ++it, ++i) {
		Feature& f = it->second;
		features.push_back(f);
		filteredKeyPoints.push_back(KeyPoint(f.position, 1.f));
	}

	return lRetVal;
}

int FindMatches( vector<Feature>& features0,
	vector<Feature>& features1,
	vector<DMatch>& matches,
	unsigned int minDistLimit,
	unsigned int rangeCheck
	)
{
	int lRetVal = 0;

	// match the keypoints
	// TODO: now just simple and incorrect matching, should be a stable marriage problem?
	for (unsigned int i0 = 0; i0 < features0.size(); ++i0)
	{
		//for range testing
		int hamDistA = INT_MAX;
		int hamDistB = INT_MAX;
		Feature f0 = features0[i0];
		int f1Index = -1;
		for (unsigned int i1 = 0; i1 < features1.size(); ++i1)
		{
			Feature f1 = features1[i1];
			//popcount early exit didn't help
			int d = f0.descriptor.HammingDistance(f1.descriptor);
			if (f1.matchedTo >= 0)
			{
				//overwrite... what if it's not a final match after the overwrite?
				//if (d >= f1.matchDist)
				{
					continue;
				}

				features0[f1.matchedTo].matchedTo = -1;
				features1[i1].matchedTo = -1;
			}

			if (((unsigned int)d) <= minDistLimit)
			{
				if (d < hamDistA)
				{
					hamDistB = hamDistA < hamDistB ? hamDistA : hamDistB;
					hamDistA = d;
					f1Index = i1;
				}
				else if (d < hamDistB)
				{
					hamDistB = d;
				}
			}
			else if (d < hamDistB)
			{
				hamDistB = d;
			}
		}

		if (f1Index >= 0 && (hamDistB - hamDistA > RANGE_CHECK))
		{
			features0[i0].matchedTo = f1Index;
			features1[f1Index].matchedTo = i0;
			features0[i0].matchDist = features1[f1Index].matchDist = hamDistA;
		}
	}

	// can be performed in previous cycle when not using overwrites
	for (unsigned int i0 = 0; i0 < features0.size(); ++i0)
	{
		Feature f0 = features0[i0];
		if (f0.matchedTo >= 0)
		{
			DMatch m;
			m.imgIdx = 0;
			m.queryIdx = i0;
			m.trainIdx = f0.matchedTo;
			m.distance = float(f0.matchDist);
			matches.push_back(m);
		}
	}

	return lRetVal;
}

/*
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
	unsigned int m_rangeCheck,
	APU_MATCH_DESCRIPTORS& m_process,
	DataDescriptor& m_matchesData0,
	DataDescriptor& /*m_matchesData1* /,
	DataDescriptor& m_descriptorsData0,
	DataDescriptor& m_descriptorsData1,
	DataDescriptor& m_descriptorConfiguration,
	unsigned int m_matchingDataChunkX,
	unsigned int m_matchingDataChunkY,
	unsigned int m_cuCount,
	bool apu_matching
	)
{
	int lRetVal = 0;

	int lSrcWidth = f_input.cols;
	int lSrcHeight = f_input.rows;

	// Load image into input data
	unsigned char *inData = (unsigned char *)f_inDataDescriptor.GetDataPtr();
	memcpy(inData, f_input.data, lSrcWidth * lSrcHeight);

	// Run the APEX process
	lRetVal |= f_process.Start();

	if (apu_matching)
	{
		uint16_t* descriptorConfigurationPtr = (uint16_t*)m_descriptorConfiguration.GetDataPtr();
		descriptorConfigurationPtr[0] = (uint16_t)m_features0.size();
		descriptorConfigurationPtr[1] = (uint16_t)m_features1.size();
		descriptorConfigurationPtr[2] = (uint16_t)m_minDistLimit;
		descriptorConfigurationPtr[3] = (uint16_t)m_rangeCheck;

		// fill the descriptor data
		uint8_t* descriptorsData0Ptr = (uint8_t*)m_descriptorsData0.GetDataPtr();
		for (unsigned int h = 0; h < m_matchingDataChunkY; ++h)
		{
			for (unsigned int i = 0; i < m_matchingDataChunkX; ++i)
			{
				unsigned int index = h * m_matchingDataChunkX + i;
				int rowOffset = h * m_matchingDataChunkX * m_cuCount;
				for (unsigned int j = 0; j < m_cuCount; ++j)
				{
					descriptorsData0Ptr[rowOffset + j * m_matchingDataChunkX + i] = index < m_features0.size() ? m_features0[index].descriptor.GetByte(j) : 0;
				}
			}
		}
		uint8_t* descriptorsData1Ptr = (uint8_t*)m_descriptorsData1.GetDataPtr();
		for (unsigned int h = 0; h < m_matchingDataChunkY; ++h)
		{
			for (unsigned int i = 0; i < m_matchingDataChunkX; ++i)
			{
				unsigned int index = h * m_matchingDataChunkX + i;
				int rowOffset = h * m_matchingDataChunkX * m_cuCount;
				for (unsigned int j = 0; j < m_cuCount; ++j)
				{
					descriptorsData1Ptr[rowOffset + j * m_matchingDataChunkX + i] = index < m_features1.size() ? m_features1[index].descriptor.GetByte(j) : 0;
				}
			}
		}
	}

	if (apu_matching)
	{
		lRetVal |= m_process.Start();
	}
	else
	{
		// match the keypoints
		// TODO: now just simple and incorrect matching, should be a stable marriage problem?
		for (unsigned int i0 = 0; i0 < m_features0.size(); ++i0)
		{
			//for range testing
			int hamDistA = INT_MAX;
			int hamDistB = INT_MAX;
			Feature f0 = m_features0[i0];
			int f1Index = -1;
			for (unsigned int i1 = 0; i1 < m_features1.size(); ++i1)
			{
				Feature f1 = m_features1[i1];
				//popcount early exit didn't help
				int d = f0.descriptor.HammingDistance(f1.descriptor);
				if (f1.matchedTo >= 0)
				{
					//overwrite... what if it's not a final match after the overwrite?
					//if (d >= f1.matchDist)
					{
						continue;
					}

					m_features0[f1.matchedTo].matchedTo = -1;
					m_features1[i1].matchedTo = -1;
				}

				if (((unsigned int)d) <= m_minDistLimit)
				{
					if (d < hamDistA)
					{
						hamDistB = hamDistA;
						hamDistA = d;
						f1Index = i1;
					}
					else if (d < hamDistB)
					{
						hamDistB = d;
					}
				}
				else if (d < hamDistB)
				{
					hamDistB = d;
				}
			}

			if (f1Index >= 0 && (hamDistB - hamDistA > RANGE_CHECK))
			{
				m_features0[i0].matchedTo = f1Index;
				m_features1[f1Index].matchedTo = i0;
				m_features0[i0].matchDist = m_features1[f1Index].matchDist = hamDistA;
			}
		}

		// can be performed in previous cycle when not using overwrites
		for (unsigned int i0 = 0; i0 < m_features0.size(); ++i0)
		{
			Feature f0 = m_features0[i0];
			if (f0.matchedTo >= 0)
			{
				DMatch m;
				m.imgIdx = 0;
				m.queryIdx = i0;
				m.trainIdx = f0.matchedTo;
				m.distance = float(f0.matchDist);
				m_matches.push_back(m);
			}
		}
	}

	// compute the image descriptors
	const int minBorderDist = 30;
	bool escape = false;
	for (int y = minBorderDist; y < lSrcHeight - minBorderDist; ++y)
	{
		if (escape)
		{
			break;
		}
		for (int x = minBorderDist; x < lSrcWidth - minBorderDist; ++x)
		{
			Point p(x, y);
			int index = y * lSrcWidth + x;
			if (f_inDescriptorDataF[index] > 0)
			{
				Feature f;
				float xBase, yBase;
				//GetCentroidRotation(tempDataG, lSrcWidth, p, &xBase, &yBase);
				GetCentroidRotationLUT(f_inDescriptorDataG, lSrcWidth, p, &xBase, &yBase);
				f.descriptor = CreateDescriptorRotated(f_inDescriptorDataG, lSrcWidth, p, xBase, yBase);
				f.position = p;
				f_features.push_back(f);
				f_filteredKeyPoints.push_back(KeyPoint(p, 1.f));
				if (f_features.size() >= MAX_FEATURE_POINTS)
				{
					escape = true;
					break;
				}
			}
		}
	}

	lRetVal |= f_process.Wait();
	unsigned char *outDataF = (unsigned char *)f_outDataDescriptor0.GetDataPtr();
	unsigned char *outDataG = (unsigned char *)f_outDataDescriptor1.GetDataPtr();

	if (apu_matching)
	{
		int16_t* matchesDataPtr = (int16_t*)m_matchesData0.GetDataPtr();
		lRetVal |= m_process.Wait();

		for (unsigned int i0 = 0; i0 < m_features0.size(); ++i0)
		{
			int matchedTo = (int)matchesDataPtr[i0];
			if (matchedTo >= 0)
			{
				DMatch m;
				m.imgIdx = 0;
				m.queryIdx = (int)i0;
				m.trainIdx = matchedTo;
				m.distance = float(.0f);
				m_matches.push_back(m);
			}
		}
	}

	memcpy(f_outFeaturesDataF, outDataF, lSrcWidth * lSrcHeight);
	memcpy(f_outFeaturesDataG, outDataG, lSrcWidth * lSrcHeight);

	return lRetVal;
}

*/