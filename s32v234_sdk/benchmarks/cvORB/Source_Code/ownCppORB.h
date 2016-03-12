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
#ifndef OWN_CPP_ORB_H
#define OWN_CPP_ORB_H

/// Simple CPP implementation for ORB 

#include <vector>
#include "descriptor.h"

class COwnOrb {
public:
	COwnOrb();
	virtual ~COwnOrb();
	void create(int lSrcWidth, int lSrcHeight);
	void doComputation(Mat& img1, Mat& img2, char* idxStr, std::string ext);

private:
	unsigned char* tempDataF;
	unsigned char* tempDataG;
	vector<KeyPoint> filteredKeyPoints;
	vector<KeyPoint> referenceKeyPoints;
	vector<Feature> features;
	vector<Feature> referenceFeatures;
	vector<DMatch> matches;

	Mat outMatches;
	Mat outM;
};

#endif

