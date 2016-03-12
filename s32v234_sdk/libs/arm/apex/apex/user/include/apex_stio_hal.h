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

#define STIO_INDEX_SOUT1_CONFIG_INDEX   0
#define STIO_INDEX_SOUT2_CONFIG_INDEX   1
#define STIO_INDEX_SOUT3_CONFIG_INDEX   2
#define STIO_INDEX_SOUT4_CONFIG_INDEX   3
#define STIO_INDEX_SIN1_CONFIG_INDEX    4
#define STIO_INDEX_SIN2_CONFIG_INDEX    5
#define STIO_INDEX_SIN3_CONFIG_INDEX    6
#define STIO_INDEX_SIN4_CONFIG_INDEX    7

enum STIO_LINETYPE
{
   STIO_LT_YUYV   = 0x10,
   STIO_LT_UVUV   = 0x20,
   STIO_LT_PLANAR = 0x30,

   STIO_LT_PLANAR44 = 0x40,
   STIO_LT_PLANAR22 = 0x50,
   
   STIO_LT_UYVY     = 0x60,
   STIO_LT_YVYU     = 0x70,

   STIO_LT_MAX      = 0x60

};

enum STIO_STREAMS
{
   STIO_OUT1       = 0,
   STIO_OUT2       = 1,   
   STIO_OUT3       = 2,
   STIO_OUT4       = 3,
   STIO_IN1        = 4,
   STIO_IN2        = 5,    
   STIO_IN3        = 6,
   STIO_IN4        = 7,
   STIO_IN1_SHADOW = 8,
   STIO_IN2_SHADOW = 9,
   STIO_IN3_SHADOW =10,
   STIO_IN4_SHADOW =11    
};

//void stio_hal_config(APEX_642CL_STREAM_DMA_STREAM_DCR *r, unsigned int i);
void stio_hal_pollwait_sti0_done(int apexID);
void stio_hal_interruptclear_sti0_done(int apexID);
void stio_hal_interruptclear_sti1_done(int apexID);
void stio_hal_interruptclear_sti0_framestart(int apexID);
void stio_hal_interruptclear_sti1_framestart(int apexID);
void stio_hal_interruptclear_sto0_done(int apexID);
void stio_hal_interruptclear_sti_done(int apexID, int channel);
void stio_hal_interruptclear_sto_done(int apexID, int channel);


#endif //STIO_HAL_HPP___

