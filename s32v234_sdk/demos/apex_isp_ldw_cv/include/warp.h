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
#ifndef _WARP__H
#define _WARP__H

#include <opencv2/opencv.hpp>
#include "transform_lut.h"

#include <apex.h>
#include "LDWS_REMAP_SOBEL_MEDIAN.hpp"

/**
 * Class consists of function which warps an image into bird eye view
 */
class Warp
{
  public:
    /**
     * Constructor
     */
    Warp();
    
    /**
     * Function warps the input image into the output using pre-computed 
     * transformation.
     * Uses APEX subsystem.
     * @param in Input image
     * @param out Output bird eye image
     * @param transform Transformation LUTs to be used 
     */
    void Warp_BirdEye(cv::Mat &in, cv::Mat &out, Transform_LUT &transform);
    
  private:
    /**
     * Source image
     */
    icp::DataDescriptor src;
    
    /**
     * Destination image
     */
    icp::DataDescriptor dst;
    
    /**
     * Blocks indices
     */
    icp::DataDescriptor blocks;
    
    /**
     * Offsets indices
     */
    icp::DataDescriptor offsets;
    
    /**
     * Deltas values
     */
    icp::DataDescriptor deltas;
    
    /**
     * APEX remap process
     */
    LDWS_REMAP_SOBEL_MEDIAN apex_remap;
    
    /**
     * Warp initialised
     */
    bool warp_init;
};

#endif
