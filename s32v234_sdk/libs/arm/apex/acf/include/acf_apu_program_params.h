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
#ifndef _ACF_APUPROGRAMPARAMS_HPP
#define _ACF_APUPROGRAMPARAMS_HPP

#include <acf_process_portinfo.h>
#include <acf_process_portinfo_apu.h>
#include <vector>
#include <stdint.h>

//NOTE: a few fields (e.g. DMA channel info) are NOT configured by the 'GenApuProgramParams' method;
//      must also call the 'FinalizeProgramParams' method to completely generate the parameter list!!

int32_t CheckIf1D_pipeline (std::vector<ACF_Process_PortInfo> &lPortInfoVec);
int32_t GenApuProgramParams(std::vector<ACF_Process_PortInfo> &lPortInfoVec,
                            std::vector<ACF_Process_PortInfo_APU> &lPortInfoApuVec,
                            int32_t lRoiInfoL, int32_t lRoiInfoR, int32_t lRoiInfoT, int32_t lRoiInfoB,
                            int32_t lFlag1D,
                            int32_t lApuArrayWidth,
                            int32_t* lpParamList,
                            int32_t* lpParamListSize,
                            acf_scenario* lpScenario,
			    int32_t lApexID_mode = 0, int32_t lApexID = 0);

#endif //_ACF_APUPROGRAMPARAMS_HPP
