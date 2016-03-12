/*****************************************************************************
*
* Freescale Confidential Proprietary
*
* Copyright (c) 2013 Freescale Semiconductor;
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
/**
* \file image_video.h
* \brief Classes which read either videos or image sequences with the same interfaces.
* \author Anca Dima
* \version
* \date 11-February-2014
****************************************************************************/

#ifndef IMAGE_VIDEO_IO_H
#define IMAGE_VIDEO_IO_H

//#include "opencv2/video/tracking.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <string>

using namespace std;
using namespace cv;


inline static double square(int a)
{
	return a * a;
}



/**
 Base class to read sequences of data (either video/images)
*/
class CReadSeqData {
protected:
	std::string m_inputPath;
	std::string m_fileExt;
	int m_minIdx, m_maxIdx, m_crtIdx;

public:
	CReadSeqData(std::string& inputPath, std::string& fileExt, int minIdx, int maxIdx)
		: m_inputPath(inputPath)
		, m_fileExt(fileExt)
		, m_minIdx(minIdx)
		, m_maxIdx(maxIdx)
	{
		m_crtIdx = m_minIdx;
	}

	virtual ~CReadSeqData(){}

	virtual int GetNextFrame(Mat& nextFrame, int idxToGet = -1) = 0;
	inline int GetMaxNrFrames(){ return m_maxIdx; }
	inline int GetCrtNrFrame(){ return m_crtIdx - 1; }

};

/** Specialization class used for reading videos
*/
class CReadVideoSeqData : public CReadSeqData {
private:
	CvCapture	*m_input_video;
	CvSize		 m_frame_size;
public:
	CReadVideoSeqData(std::string& inputPath, std::string& fileExt, int minIdx, int maxIdx);

	virtual ~CReadVideoSeqData()
	{
		//delete m_input_video;// incomplete type. No destructor to be called
	}

	virtual int GetNextFrame(Mat& nextFrame, int idxToGet = -1);

	inline CvSize getFrameSz() {
		return m_frame_size;
	}

};

/** Specialization class used for reading image sequences, of images which have an index in their name
*/
class CReadImgSeqData : public CReadSeqData {
public:
	CReadImgSeqData(std::string& inputPath, std::string& fileExt, int minIdx, int maxIdx)
		: CReadSeqData(inputPath, fileExt, minIdx, maxIdx)
		, allFiles(NULL)
	{}

	virtual ~CReadImgSeqData(){
#ifndef __STANDALONE__
		if (allFiles != NULL) {
			fclose(allFiles);
		}
#endif
	}

	virtual int GetNextFrame(Mat& nextFrame, int idxToGet = -1);
	std::string GetFileName() {
		return m_fileName;
	}
	std::string GetDirName() {
		return m_inputPath;
	}
	std::string GetFilePath(){
		return m_filePath;
	}
private:
	FILE* allFiles;
	std::string m_fileName;
	std::string m_filePath;
};



#endif