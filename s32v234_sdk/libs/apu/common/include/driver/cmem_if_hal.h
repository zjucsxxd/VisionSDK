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

#ifndef _CMEM_IF_HAL_H_
#define _CMEM_IF_HAL_H_

#include <stdint.h>

//this enumeration is used to define logical resource sets
typedef enum
{
   //------------------
   //321 configurations
   //------------------

   //APU0 has ownership of CUs 0-31 and SMEM blocks 0-1 (64K)
   CFG_321__APU_0_CU_0_31_SMEM_0_1,

   //------------------
   //642 configurations
   //------------------

   //APU0 has ownership of CUs 0-63 and SMEM blocks 0-3 (128K)
   CFG_642__APU_0_CU_0_63_SMEM_0_3,

   //APU0 has ownership of CUs 0-31  and SMEM blocks 0-1 (64K)
   //APU1 has ownership of CUs 32-63 and SMEM blocks 2-3 (64K)
   CFG_642__APU_0_CU_0_31_SMEM_0_1__APU_1_CU_32_63_SMEM_2_3,

   //----------------------------------
   //error (i.e. unknown configuration)
   //----------------------------------
   CFG_UNKNOWN_CONFIGURATION

} CMEM_IF_APU_CFG;

void cmem_if_hal_set_apu_cfg(CMEM_IF_APU_CFG lApuCfg);
CMEM_IF_APU_CFG cmem_if_hal_query_apu_cfg();
void cmem_if_hal_set_apu_pmem_start(int32_t apuid, uint32_t address);
void cmem_if_hal_set_apu_dmem_start(int32_t apuid, uint32_t address);
uint32_t cmem_if_hal_query_apu_pmem_start(int32_t apuid);
uint32_t cmem_if_hal_query_apu_dmem_start(int32_t apuid);
uint32_t cmem_if_hal_query_cu_array_width(int32_t apuid);

#if 0
// Local Literals and Definitions
//

// Externally defined Global Variables
//


// Global Functions defined in this file.
//

void Cmem_if_hal_PutDataPattern(int cuMemOffset, int initialValue);
void Cmem_if_hal_PutDataConstant(int cuMemOffset, int initialValue);
int  Cmem_if_hal_PutTestData(int cuMemOffset, unsigned int data[]);
int  Cmem_if_hal_GetTestData(int cuMemOffset, unsigned int data[]);
int  Cmem_if_hal_CompareTestData(int cuMemOffset, unsigned int data[]);


void Cmem_if_hal_ArrayInit(void);

/****************************************************************************
 * Function   :   Cmem_if_hal_WriteMem32
 * Description:   Writes a 32 bit value to a group of 4 Cus.
 *                
 * Parameters :
 *    src               the offset into a specific cus memory.
 *    cuColumnIndex     specified as a cu column 0-47
 *    cuRowIndex        specified as a cu row 0-1
 *    value             the value to write
 * Return Value/Updated Parameters:
 *    None
 ****************************************************************************/ 
void Cmem_if_hal_WriteMem32(int cuColumnIndex, int memoryOffset, unsigned int value);


/****************************************************************************
 * Function   :   Cmem_if_hal_ReadMem32
 * Description:   Reads a 32 bit value from a group of 4 Cus.
 *                
 * Parameters :
 *    src               the offset into a specific cus memory.
 *    cuColumnIndex     specified as a cu column 0-23
 * Return Value/Updated Parameters:
 *    32 bit value of the contents of CMEM for a group of 4 cus.
 ****************************************************************************/
unsigned int Cmem_if_hal_ReadMem32(int cuColumnIndex, int memoryOffset);


/****************************************************************************
 * 
 *
 *
 ****************************************************************************/
volatile unsigned int *Cmem_if_hal_CalculateCuAddress (unsigned int cu, unsigned int addr);

void Cmem_if_hal_SnapshotRead(unsigned int address, unsigned int size,
                      unsigned int ngoc, const char *filename);

/****************************************************************************
 * Function   :   Cmem_if_hal_PutDataPattern
 * Description:   Writes a value to each CU. The value is incremented for
 *                each CU.
 * Parameters :
 *    cuMemOffset       the offset into a specific CUs memory.
 *    initialValue      the starting value to write to the CUs.
 * Return Value/Updated Parameters:
 *    none
 ****************************************************************************/
void Cmem_if_hal_PutDataPattern(int cuMemOffset, int initialValue);

/****************************************************************************
 * Function   :   Cmem_if_hal_PutDataConstant
 * Description:   Writes a the same value to each CU.
 *
 * Parameters :
 *    cuMemOffset       the offset into a specific CUs memory.
 *    initialValue      the value to write to each CU.
 * Return Value/Updated Parameters:
 *    none
 ****************************************************************************/
void Cmem_if_hal_PutDataConstant(int cuMemOffset, int initialValue);

/****************************************************************************
 *
 * Function   : Cmem_if_hal_PutTestData
 * Description: Copies data to the cmem array from a defined structure.
 *              Used to store data in cmem that was obtained from 
 *              the simd simulator
 * Parameters :
 *    cuMemOffset    location in cu memory to place the data.
 *    data[]         array containing the data to put in cmem
 *                   follows the following format:
 *                         unsigned int cuData[] = { 0x1234567,....0x1234567);
 *                         unsigned int cuDataInfo[] = {
 *                                  1,   // NumberOfFrames
 *                                  128, // Bytes Per Cu
 *                                  24,  // CuWidth
 *                                  3,   // CuHeight
 *                                  (unsigned int)(cuData)
 *                               };
 *
 * Return Value/Updated Parameters:
 *    MMP_SUCCESS
 ****************************************************************************/
int Cmem_if_hal_PutTestData(int cuMemOffset, unsigned int data[]);
//#ifdef ATD_HWSIM_DATA_GEN
/****************************************************************************
 * Function   :   Cmem_if_hal_Scan
 * Description:   Prints out the content of the same cmem 
 *                location for each CU.
 *
 * Parameters :
 *    cuMemOffset       the offset into a specific CUs memory.
 * Return Value/Updated Parameters:
 *    none
 ****************************************************************************/
void Cmem_if_hal_Scan(int cuMemOffset);

/****************************************************************************
 *
 * Function   : Cmem_if_hal_GetTestData
 * Description: Copies data from the cmem array to a defined structure.
 *              Used to extract data from cmem that can be used in  
 *              the simd simulator.
 * Parameters :
 *    cuMemOffset    location in cu memory to get the data from.
 *    data[]         array containing the data to put in cmem
 *                   follows the following format:
 *                         unsigned int cuData[] = { 0x1234567,....0x1234567);
 *                         unsigned int cuDataInfo[] = {
 *                                  1,   // NumberOfFrames
 *                                  128, // Bytes Per Cu
 *                                  24,  // CuWidth
 *                                  3,   // CuHeight
 *                                  (unsigned int)(cuData)
 *                               };
 *
 * Return Value/Updated Parameters:
 *    MMP_SUCCESS
 ****************************************************************************/
int Cmem_if_hal_GetTestData(int cuMemOffset, unsigned int data[]);
/****************************************************************************
 *
 * Function   : Cmem_if_hal_CompareTestData
 * Description: Compares the data in the cmem array to the data provided.
 *              Used to verify cmem data against data generated by the simulator.
 *
 * Parameters :
 *    cuMemOffset    location in cu memory to get the data from.
 *    data[]         array containing the data to put in cmem
 *                   follows the following format:
 *                         unsigned int cuData[] = { 0x1234567,....0x1234567);
 *                         unsigned int cuDataInfo[] = {
 *                                  1,   // NumberOfFrames
 *                                  128, // Bytes Per Cu
 *                                  24,  // CuWidth
 *                                  3,   // CuHeight
 *                                  (unsigned int)(cuData)
 *                               };
 *
 * Return Value/Updated Parameters:
 *    MMP_SUCCESS
 *    MMP_FAILURE
 ****************************************************************************/
int Cmem_if_hal_CompareTestData(int cuMemOffset, unsigned int data[]);

int CRAMCompareTestData(int cu_mem_offset, unsigned int data[]);

#endif //0

#endif //_CMEM_IF_HAL_H_
