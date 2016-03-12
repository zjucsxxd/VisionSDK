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
 * \file    seq_graph_meta.h
 * \brief   ISP Graph metadata formats
 * \author
 * \version 0.1
 * \date    14-Oct-2014
 ****************************************************************************/
 
#ifndef SEQ_GRAPH_META_H
#define SEQ_GRAPH_META_H

#ifndef __KERNEL__
  #include <stdint.h>
#endif //#ifndef __KERNEL__

#define NUM_MIPI 2

typedef struct Object_t
{
  const void* mcpAddr;
  const uint32_t mcSize;
  const uint32_t mcOffset;
} Object_t;

typedef struct GraphLimits_t
{
  const uint32_t mcCSINumLines; // obsolete
} GraphLimits_t;

typedef enum CSI_CameraType_t
{
    NONE,
    SONY224,
    OV10640,
    MAX_SONY224,
    MAX_OV10640
} CSI_CameraType_t;

typedef struct GraphMipiCSIParam_t
{
    enum CSI_CameraType_t mcCameraType;
    const uint16_t mcNumCameras;
} GraphMipiCSIParam_t;

typedef struct GraphMetadata_t
{
  const uint32_t mMaxConsumer;
  const uint32_t mGraphSize;
  const Object_t *mpObjectList;
  const uint32_t mObjCnt;
  const uint32_t *mpPointerList;
  const uint32_t mPtrCnt;
  const uint32_t *mpBufferList;
  const uint32_t mBfrCnt;
  const GraphLimits_t mcGraphLimits;
  const GraphMipiCSIParam_t mcMipiCSIParams[NUM_MIPI];
} GraphMetadata_t;

#endif //#ifndef SEQ_GRAPH_META_H
