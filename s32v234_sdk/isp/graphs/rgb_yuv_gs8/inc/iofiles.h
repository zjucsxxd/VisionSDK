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
/**
 * \file    iofiles.h
 * \brief   ISP RGB, YUV and GreyScale8 graph
 * \author  Armin Strobl
 * \author
 * \version 0.1
 * \date    15-01-2016
 * \note    inital version
 ****************************************************************************/

#ifndef	IOFILES_H_
#define	IOFILES_H_

#define	NUM_CAM_LINES		729
#define	NUM_IN_LINES		728
#define	NUM_LINES		NUM_IN_LINES
#define	NUM_IN_M1		(NUM_IN_LINES-1)
#define	NUM_IN_M2		(NUM_IN_LINES-2)
#define	NUM_IN_M4		(NUM_IN_LINES-4)
#define	NUM_IN_M6		(NUM_IN_LINES-6)
#define	NUM_IN_M8		(NUM_IN_LINES-8)
#define	NUM_OUT_Y_SCALED_BYTES	640
#define	NUM_OUT_Y_SCALED_LINES	356
#define	NUM_OUT_PIXELS		1280
#define	NUM_OUT_Y_BYTES		(1*NUM_OUT_PIXELS)
#define	NUM_OUT_YUV_BYTES	(2*NUM_OUT_PIXELS)
#define	NUM_OUT_RGB_BYTES	(3*NUM_OUT_PIXELS)
#define	NUM_OUT_LINES		720

#endif // IOFILES_H_
