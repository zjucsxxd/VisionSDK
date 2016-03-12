/******************************************************************************
 *  (C) Copyright CogniVue Corporation. 2011 All right reserved.
 *
 *  Confidential Information
 *
 *  All parts of the CogniVue Program Source are protected by copyright law
 *  and all rights are reserved.
 *  This documentation may not, in whole or in part, be copied, photocopied,
 *  reproduced, translated, or reduced to any electronic medium or machine
 *  readable form without prior consent, in writing, from CogniVue.
 ******************************************************************************/
#ifndef STIO_HAL_HPP___
#define STIO_HAL_HPP___

#include "apex_stio_hal.h"

//void stio_hal_config(APEX_642CL_STREAM_DMA_STREAM_DCR *r, unsigned int i);
void apexdriver_stio_hal_pollwait_sti0_done(int apexID);
void apexdriver_stio_hal_interruptclear_sti0_done(int apexID);
void apexdriver_stio_hal_interruptclear_sti1_done(int apexID);
void apexdriver_stio_hal_interruptclear_sti0_framestart(int apexID);
void apexdriver_stio_hal_interruptclear_sti1_framestart(int apexID);
void apexdriver_stio_hal_interruptclear_sto0_done(int apexID);
void apexdriver_stio_hal_interruptclear_sti_done(int apexID, int channel);
void apexdriver_stio_hal_interruptclear_sto_done(int apexID, int channel);


#endif //STIO_HAL_HPP___

