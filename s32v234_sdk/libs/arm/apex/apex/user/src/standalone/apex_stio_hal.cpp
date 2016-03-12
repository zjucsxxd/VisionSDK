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

#include "apexdriver_stio_hal.h"

void stio_hal_pollwait_sti0_done(int apexID)
{
	apexdriver_stio_hal_pollwait_sti0_done(apexID);
}

void stio_hal_interruptclear_sti0_done(int apexID)
{
	apexdriver_stio_hal_interruptclear_sti0_done(apexID);
}

void stio_hal_interruptclear_sti1_done(int apexID)
{
	apexdriver_stio_hal_interruptclear_sti1_done(apexID);
}

void stio_hal_interruptclear_sti0_framestart(int apexID)
{
	apexdriver_stio_hal_interruptclear_sti0_framestart(apexID);
}

void stio_hal_interruptclear_sti1_framestart(int apexID)
{
	apexdriver_stio_hal_interruptclear_sti1_framestart(apexID);
}

void stio_hal_interruptclear_sto0_done(int apexID)
{
	apexdriver_stio_hal_interruptclear_sto0_done(apexID);
}

void stio_hal_interruptclear_sti_done(int apexID, int channel)
{
	apexdriver_stio_hal_interruptclear_sti_done(apexID, channel);
}

void stio_hal_interruptclear_sto_done(int apexID, int channel)
{
	apexdriver_stio_hal_interruptclear_sto_done(apexID, channel);
}

