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
#ifndef apex_APU_COMM___
#define apex_APU_COMM___

#define FIFO_SIZE_LOG2 6
#define FIFO_SIZE      (1 << FIFO_SIZE_LOG2)

#define APU_MAX_NUMBER_OF_APUS 4

// *****************************************
#define _PROC_TARGET_ARM 0
#define _PROC_TARGET_APU 1

#define _PROC_TARGET _PROC_TARGET_ARM

#if (_PROC_TARGET == _PROC_TARGET_APU)

#define TX_FIFO_ID 0
#define RX_FIFO_ID 1

#else

#define TX_FIFO_ID 1
#define RX_FIFO_ID 0

#endif
// *****************************************



struct _FIFO
{
   unsigned int d[FIFO_SIZE];
   unsigned int r;
   unsigned int w;
};

struct _APU_COMM
{
   // From the point of view of the APUs
   // Tx : APU Writes
   // Rx : APU Reads
   // -------------------------------------------
   struct _FIFO FIFO[2];
};

typedef struct _APU_COMM APU_COMM;

#endif

