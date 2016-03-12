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
#ifndef FILTERING_GAUSS_HPP
#define FILTERING_GAUSS_HPP
#include "filtering.h"


template <class Tp>
Mat extendSymmetric(const Mat& img1, int fwidth, int fheight){
	Mat imgExt(img1.rows + 2 * fheight, img1.cols + 2 * fwidth, img1.type(), Scalar(0));

	Mat r(imgExt, cv::Rect(fwidth, fheight, img1.cols, img1.rows));
	img1.copyTo(r);

	for (int j = 0, l = fheight; j < img1.rows; ++j, l++) {
		for (int i = 1, k = fwidth; i <= fwidth; ++i, --k) {
			// extend symmetric to the left
			imgExt.at<Tp>(l, k) = img1.at<Tp>(j, i);

			// extend symmetric to the right
			short tmp = img1.at<Tp>(j, img1.cols - i);
			imgExt.at<Tp>(l, imgExt.cols - k) = img1.at<Tp>(j, img1.cols - i - 1);
		}
	}

	int botLastRow = img1.rows + fheight;
	for (int j = 0, l = fheight; j < fheight; ++j, --l) {
		for (int i = 0; i < imgExt.cols; ++i) {
			// extend symmetric to the top
			imgExt.at<Tp>(j, i) = imgExt.at<Tp>(fheight + l, i);

			// extend symmetric to the bottom
			imgExt.at<Tp>(botLastRow + j, i) = imgExt.at<Tp>(botLastRow - j - 2, i);
		}
	}

	return imgExt;
}

template <class Tp>
Mat applyFilter(const Mat& img1, short filt[KERNEL_HEIGHT][KERNEL_WIDTH], int fw, int fh)
{
	assert(!img1.empty());

	cv::Mat imgExt = extendSymmetric<Tp>(img1, fw / 2, fh / 2);
	cout << endl << "< applying filter..." << endl;

	cv::Mat filteredImg(img1.rows, img1.cols, img1.type());
	filteredImg = 0;

	float filtNorm = 0;
	for (int k = 0; k < fh; ++k) {
		for (int l = 0; l < fw; ++l) {
			filtNorm += abs(filt[k][l]);
		}
	}

	for (int j = 0; j < img1.rows; ++j) {
		for (int i = 0; i < img1.cols; ++i) {
			float temp = 0;
			for (int k = 0; k < fh; ++k) {
				for (int l = 0; l < fw; ++l) {
					temp += imgExt.at<Tp>(j + k, i + l) * ((float)filt[k][l]);
				}
			}

			filteredImg.at<Tp>(j, i) = (Tp)rint(temp / filtNorm);
		}
	}

	return filteredImg;
}

#endif

