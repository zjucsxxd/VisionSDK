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
#include <opencv2/opencv.hpp>
#include <stdint.h>

#pragma once

const int PATTERN_COUNT = 256;
typedef uint32_t DescBitArrayElementType;
const int DESC_BIT_ARRAY_ELEMENT_BITS = (sizeof(DescBitArrayElementType) * 8);
const int DESC_BIT_ARRAY_ELEMENT_COUNT = PATTERN_COUNT / DESC_BIT_ARRAY_ELEMENT_BITS;

struct Descriptor
{
	DescBitArrayElementType mBitArray[DESC_BIT_ARRAY_ELEMENT_COUNT];

	int HammingDistance(const Descriptor& other) const;
  uint8_t GetByte(int byteIndex) const;
};

//doesn't check bounds!
Descriptor CreateDescriptor(const unsigned char image[], int cols, const cv::Point& index);
//doesn't check bounds!
Descriptor CreateDescriptorRotated(const unsigned char image[], int cols, const cv::Point& index, float xBase, float yBase);
//doesn't check bounds!
void GetCentroidRotation(const unsigned char image[], int cols, const cv::Point& index, float* xBase, float* yBase);
//doesn't check bounds!
void GetCentroidRotationLUT(const unsigned char image[], int cols, const cv::Point& index, float* xBase, float* yBase);
