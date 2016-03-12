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
/*!
* \file apu_histofgrad_impl.h
* \brief histogram of gradients computation for APEX
* \addtogroup histogram of gradients
* @{
****************************************************************************/

#ifndef _APU_LBP_DEFINES_H_
#define _APU_LBP_DEFINES_H_

#define LBP_NR_FEATURES_PER_HISTO		256
#define LBP_NR_SCALES					 1
#define LBP_NR_OVERLAPPING_WINDOWS		 4
#define LBP_NR_FEATURES_PER_BOX			 (LBP_NR_FEATURES_PER_HISTO  * LBP_NR_SCALES)
#define LBP_OVERLAP						 2
#define LBP_LAT_DEPENDENCY				 4

#endif //#ifdef 

/*! @} */
