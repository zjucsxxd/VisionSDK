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

/****************************************************************************
* Main function
****************************************************************************/

#include <qspi_driver.h>
#include <string.h>
#include "printf.h"

#define DATA_SIZE 256
#define QSPI_BASE 0x20000000

void print_data(unsigned char *data);

int main(int, char**)
{
	printf("\n\nFLASH WRITE DEMO\n\n");
	unsigned char data_local[DATA_SIZE];
	
	// Switch from SD card to QSPI
	quadspi_switch(SWITCH_QSPI);
	
	// Switch back to SD card if necessary
	// quadspi_switch(SWITCH_SD);

	// Set up the qspi
    QSPI_setup_hyp();
	
	// print what's in flash:
	memcpy(data_local, (void *)QSPI_BASE, DATA_SIZE);
	
	printf("Data in flash after init: \n");
	printf("=======================================\n\n");
	print_data(data_local);
		
	// Erase the flash
    quadspi_erase_hyp(QSPI_BASE);
	
	// print what's in flash:
	printf("Data in flash after delete: \n");
	printf("=======================================\n\n");
	print_data((unsigned char *)QSPI_BASE);
	
	// Increment all original values by one and write to flash
	for (int i = 0; i < DATA_SIZE; ++i)
		data_local[i] = data_local[i] + 1;
	
    quadspi_program_hyp(QSPI_BASE, (unsigned int *)data_local, DATA_SIZE);
	
	// print what's in flash:
	printf("Data in flash after saving ++original: \n");
	printf("========================================\n\n");
	print_data((unsigned char *)QSPI_BASE);
	
	printf("Done. \n\n");
	
	return 0;
}

void print_data(unsigned char *data)
{
	for (int i = 0; i < DATA_SIZE; ++i)
	{
		if (i % 10 == 0) printf("\n");
		
		// padding doesnt work now in printf
		if (data[i]< 10) printf("00%i ", data[i]);
		else if (data[i]< 100) printf("0%i ", data[i]);
		else printf("%i ", data[i]);
	}
	printf("\n\n=======================================\n");
}
