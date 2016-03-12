/******************************************************************************
 *  (C) Copyright CogniVue Corporation. 2012 All right reserved.
 *
 *  Confidential Information
 *
 *  All parts of the CogniVue Program Source are protected by copyright law
 *  and all rights are reserved.
 *  This documentation may not, in whole or in part, be copied, photocopied,
 *  reproduced, translated, or reduced to any electronic medium or machine
 *  readable form without prior consent, in writing, from CogniVue.
 ******************************************************************************/

#include "apexdriver_global_hal.h"

int global_hal_AllReset(int apexID)
{
	return apexdriver_global_hal_AllReset(apexID);
}

int global_hal_uSequencerReset(int apexID)
{
	return apexdriver_global_hal_uSequencerReset(apexID);
}

int global_hal_MotCmpDmaReset(int apexID)
{
	return apexdriver_global_hal_MotCmpDmaReset(apexID);
}

int global_hal_CmemDmaReset(int apexID)
{
	return apexdriver_global_hal_CmemDmaReset(apexID);
}

int global_hal_cmemIFReset(int apexID)
{
	return apexdriver_global_hal_cmemIFReset(apexID);
}

int global_hal_DmaReset(int apexID)
{
	return apexdriver_global_hal_DmaReset(apexID);
}

int global_hal_Apu0Reset(int apexID)
{
	return apexdriver_global_hal_Apu0Reset(apexID);
}

int global_hal_Apu1Reset(int apexID)
{
	return apexdriver_global_hal_Apu1Reset(apexID);
}

int global_hal_Vu0Reset(int apexID)
{
	return apexdriver_global_hal_Vu0Reset(apexID);
}

int global_hal_Vu1Reset(int apexID)
{
	return apexdriver_global_hal_Vu1Reset(apexID);
}

int global_hal_HrszReset(int apexID)
{
	return apexdriver_global_hal_HrszReset(apexID);
}

int global_hal_Dmem0Reset(int apexID)
{
	return apexdriver_global_hal_Dmem0Reset(apexID);
}

int global_hal_Dmem1Reset(int apexID)
{
	return apexdriver_global_hal_Dmem1Reset(apexID);
}

int global_hal_Apu0Enable(int apexID)
{
	return apexdriver_global_hal_Apu0Enable(apexID);
}

int global_hal_Apu1Enable(int apexID)
{
	return apexdriver_global_hal_Apu1Enable(apexID);
}

int global_hal_Apu0Disable(int apexID)
{
	return apexdriver_global_hal_Apu0Disable(apexID);
}

int global_hal_Apu1Disable(int apexID)
{
	return apexdriver_global_hal_Apu1Disable(apexID);
}

int global_hal_Apex2GlobalInterruptDisable(int apexID, APEX2_INTERRUPT_BITS intBit)
{
	return apexdriver_global_hal_Apex2GlobalInterruptDisable(apexID, intBit);
}

int global_hal_Apex2GlobalInterruptEnable(int apexID, APEX2_INTERRUPT_BITS intBit)
{
	return apexdriver_global_hal_Apex2GlobalInterruptEnable(apexID, intBit);
}

int global_hal_isApex2GlobalInterruptEnabled(int apexID, APEX2_INTERRUPT_BITS intBit)
{
	if (apexdriver_global_hal_isApex2GlobalInterruptEnabled(apexID, intBit))
		return 0;
	else return -1;
	
}

int global_hal_Apex2GlobalInterruptStatus(int apexID, APEX2_INTERRUPT_BITS intBit)
{
	return apexdriver_global_hal_Apex2GlobalInterruptStatus(apexID, intBit);
}

LIB_RESULT global_hal_Apex2GlobalInterruptPolling(int apexID, APEX2_INTERRUPT_BITS intBit)
{
	return apexdriver_global_hal_Apex2GlobalInterruptPolling(apexID, intBit);
}

int global_hal_RetHwVersion(int apexID)
{
	return apexdriver_global_hal_RetHwVersion(apexID);
}

int global_hal_RetSwVersion(int apexID)
{
	return apexdriver_global_hal_RetSwVersion(apexID);
}


