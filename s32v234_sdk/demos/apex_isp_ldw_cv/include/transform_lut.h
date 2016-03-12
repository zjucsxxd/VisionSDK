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
#ifndef _TRANSFORM_LUT__H
#define _TRANSFORM_LUT__H

#include <opencv2/opencv.hpp>

/**
 * Function encapsulates look-up tables for APEX bird eye warp
 */
class Transform_LUT
{
  public:
    /**
     * Constructor
     */
    Transform_LUT();
    
    /**
     * Destructor
     */
    ~Transform_LUT();

    /**
     * Gets pointer to the array of ints - block look up table
     * @return Block look-up table
     */
    unsigned int *GetBlockPtr();
    
    /**
     * Gets pointer to the array of shorts - local offset look up table
     * * @return Local offset look-up table
     */
    unsigned short *GetLocalPtr();
    
    /**
     * Gets pointer to the array of pairs of chars - X, Y delta (decimal
     * part of local offset for bilinear approximation) 
     * @return decimal part of local offsets
     */
    unsigned char *GetDeltaPtr();
    
    /**
     * Returns H matrix - warp from bird eye to scene
     * @return H Matrix
     */
    cv::Mat GetHMat();
    
    /**
     * Returns inverse of H matrix - warp from scene to bird eye
     * @return Inverse H Matrix
     */
    cv::Mat GetInverseHMat();

  private:
    /**
     * Auxiliary function computes look-up tables
     */
    void CompLUTs();
    
    /**
     * Array which saves block indices
     */
    unsigned int *m_block;
    

    /**
     * Array which saves local indices
     */
    unsigned short *m_local;
    
    /**
     * Array which saves delta indices
     */
    unsigned char  *m_delta;
    
    /**
     * H Matrix
     */
    cv::Mat m_H;
    
    /**
     * Inverse H Matrix
     */
    cv::Mat m_invH;
};

#endif