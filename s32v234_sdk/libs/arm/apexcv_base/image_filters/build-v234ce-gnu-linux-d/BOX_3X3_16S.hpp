#ifndef _ACF_PROCESS_APU_BOX_3X3_16S
#define _ACF_PROCESS_APU_BOX_3X3_16S

#include <acf_process_apu.h>
#include <BOX_3X3_16S_APU_LOAD.h> //APU load associated with this process
#include <stdint.h>


//SCENARIO LIST*************************************************
static acf_scenario_buffer_data gScenarioBufferData0_BOX_3X3_16S[] = {{1, 1, 4, 0, 0x1111}, {1, 1, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData1_BOX_3X3_16S[] = {{2, 1, 4, 0, 0x1111}, {2, 1, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData2_BOX_3X3_16S[] = {{3, 1, 4, 0, 0x1111}, {3, 1, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData3_BOX_3X3_16S[] = {{4, 1, 4, 0, 0x1111}, {4, 1, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData4_BOX_3X3_16S[] = {{5, 1, 4, 0, 0x1111}, {5, 1, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData5_BOX_3X3_16S[] = {{6, 1, 4, 0, 0x1111}, {6, 1, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData6_BOX_3X3_16S[] = {{7, 1, 4, 0, 0x1111}, {7, 1, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData7_BOX_3X3_16S[] = {{8, 1, 4, 0, 0x1111}, {8, 1, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData8_BOX_3X3_16S[] = {{10, 1, 4, 0, 0x1111}, {10, 1, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData9_BOX_3X3_16S[] = {{12, 1, 4, 0, 0x1111}, {12, 1, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData10_BOX_3X3_16S[] = {{14, 1, 4, 0, 0x1111}, {14, 1, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData11_BOX_3X3_16S[] = {{16, 1, 4, 0, 0x1111}, {16, 1, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData12_BOX_3X3_16S[] = {{18, 1, 4, 0, 0x1111}, {18, 1, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData13_BOX_3X3_16S[] = {{20, 1, 4, 0, 0x1111}, {20, 1, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData14_BOX_3X3_16S[] = {{22, 1, 4, 0, 0x1111}, {22, 1, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData15_BOX_3X3_16S[] = {{24, 1, 4, 0, 0x1111}, {24, 1, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData16_BOX_3X3_16S[] = {{26, 1, 4, 0, 0x1111}, {26, 1, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData17_BOX_3X3_16S[] = {{28, 1, 4, 0, 0x1111}, {28, 1, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData18_BOX_3X3_16S[] = {{30, 1, 4, 0, 0x1111}, {30, 1, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData19_BOX_3X3_16S[] = {{32, 1, 4, 0, 0x1111}, {32, 1, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData20_BOX_3X3_16S[] = {{48, 1, 4, 0, 0x1111}, {48, 1, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData21_BOX_3X3_16S[] = {{64, 1, 4, 0, 0x1111}, {64, 1, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData22_BOX_3X3_16S[] = {{1, 2, 4, 0, 0x1111}, {1, 2, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData23_BOX_3X3_16S[] = {{2, 2, 4, 0, 0x1111}, {2, 2, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData24_BOX_3X3_16S[] = {{3, 2, 4, 0, 0x1111}, {3, 2, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData25_BOX_3X3_16S[] = {{4, 2, 4, 0, 0x1111}, {4, 2, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData26_BOX_3X3_16S[] = {{5, 2, 4, 0, 0x1111}, {5, 2, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData27_BOX_3X3_16S[] = {{6, 2, 4, 0, 0x1111}, {6, 2, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData28_BOX_3X3_16S[] = {{7, 2, 4, 0, 0x1111}, {7, 2, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData29_BOX_3X3_16S[] = {{8, 2, 4, 0, 0x1111}, {8, 2, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData30_BOX_3X3_16S[] = {{10, 2, 4, 0, 0x1111}, {10, 2, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData31_BOX_3X3_16S[] = {{12, 2, 4, 0, 0x1111}, {12, 2, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData32_BOX_3X3_16S[] = {{14, 2, 4, 0, 0x1111}, {14, 2, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData33_BOX_3X3_16S[] = {{16, 2, 4, 0, 0x1111}, {16, 2, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData34_BOX_3X3_16S[] = {{18, 2, 4, 0, 0x1111}, {18, 2, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData35_BOX_3X3_16S[] = {{20, 2, 4, 0, 0x1111}, {20, 2, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData36_BOX_3X3_16S[] = {{22, 2, 4, 0, 0x1111}, {22, 2, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData37_BOX_3X3_16S[] = {{24, 2, 4, 0, 0x1111}, {24, 2, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData38_BOX_3X3_16S[] = {{26, 2, 4, 0, 0x1111}, {26, 2, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData39_BOX_3X3_16S[] = {{28, 2, 4, 0, 0x1111}, {28, 2, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData40_BOX_3X3_16S[] = {{30, 2, 4, 0, 0x1111}, {30, 2, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData41_BOX_3X3_16S[] = {{32, 2, 4, 0, 0x1111}, {32, 2, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData42_BOX_3X3_16S[] = {{48, 2, 4, 0, 0x1111}, {48, 2, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData43_BOX_3X3_16S[] = {{64, 2, 4, 0, 0x1111}, {64, 2, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData44_BOX_3X3_16S[] = {{1, 4, 4, 0, 0x1111}, {1, 4, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData45_BOX_3X3_16S[] = {{2, 4, 4, 0, 0x1111}, {2, 4, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData46_BOX_3X3_16S[] = {{3, 4, 4, 0, 0x1111}, {3, 4, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData47_BOX_3X3_16S[] = {{4, 4, 4, 0, 0x1111}, {4, 4, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData48_BOX_3X3_16S[] = {{5, 4, 4, 0, 0x1111}, {5, 4, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData49_BOX_3X3_16S[] = {{6, 4, 4, 0, 0x1111}, {6, 4, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData50_BOX_3X3_16S[] = {{7, 4, 4, 0, 0x1111}, {7, 4, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData51_BOX_3X3_16S[] = {{8, 4, 4, 0, 0x1111}, {8, 4, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData52_BOX_3X3_16S[] = {{10, 4, 4, 0, 0x1111}, {10, 4, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData53_BOX_3X3_16S[] = {{12, 4, 4, 0, 0x1111}, {12, 4, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData54_BOX_3X3_16S[] = {{14, 4, 4, 0, 0x1111}, {14, 4, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData55_BOX_3X3_16S[] = {{16, 4, 4, 0, 0x1111}, {16, 4, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData56_BOX_3X3_16S[] = {{18, 4, 4, 0, 0x1111}, {18, 4, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData57_BOX_3X3_16S[] = {{20, 4, 4, 0, 0x1111}, {20, 4, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData58_BOX_3X3_16S[] = {{22, 4, 4, 0, 0x1111}, {22, 4, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData59_BOX_3X3_16S[] = {{24, 4, 4, 0, 0x1111}, {24, 4, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData60_BOX_3X3_16S[] = {{26, 4, 4, 0, 0x1111}, {26, 4, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData61_BOX_3X3_16S[] = {{28, 4, 4, 0, 0x1111}, {28, 4, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData62_BOX_3X3_16S[] = {{30, 4, 4, 0, 0x1111}, {30, 4, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData63_BOX_3X3_16S[] = {{32, 4, 4, 0, 0x1111}, {32, 4, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData64_BOX_3X3_16S[] = {{48, 4, 4, 0, 0x1111}, {48, 4, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData65_BOX_3X3_16S[] = {{64, 4, 4, 0, 0x1111}, {64, 4, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData66_BOX_3X3_16S[] = {{1, 6, 4, 0, 0x1111}, {1, 6, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData67_BOX_3X3_16S[] = {{2, 6, 4, 0, 0x1111}, {2, 6, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData68_BOX_3X3_16S[] = {{3, 6, 4, 0, 0x1111}, {3, 6, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData69_BOX_3X3_16S[] = {{4, 6, 4, 0, 0x1111}, {4, 6, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData70_BOX_3X3_16S[] = {{5, 6, 4, 0, 0x1111}, {5, 6, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData71_BOX_3X3_16S[] = {{6, 6, 4, 0, 0x1111}, {6, 6, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData72_BOX_3X3_16S[] = {{7, 6, 4, 0, 0x1111}, {7, 6, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData73_BOX_3X3_16S[] = {{8, 6, 4, 0, 0x1111}, {8, 6, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData74_BOX_3X3_16S[] = {{10, 6, 4, 0, 0x1111}, {10, 6, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData75_BOX_3X3_16S[] = {{12, 6, 4, 0, 0x1111}, {12, 6, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData76_BOX_3X3_16S[] = {{14, 6, 4, 0, 0x1111}, {14, 6, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData77_BOX_3X3_16S[] = {{16, 6, 4, 0, 0x1111}, {16, 6, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData78_BOX_3X3_16S[] = {{18, 6, 4, 0, 0x1111}, {18, 6, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData79_BOX_3X3_16S[] = {{20, 6, 4, 0, 0x1111}, {20, 6, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData80_BOX_3X3_16S[] = {{22, 6, 4, 0, 0x1111}, {22, 6, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData81_BOX_3X3_16S[] = {{24, 6, 4, 0, 0x1111}, {24, 6, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData82_BOX_3X3_16S[] = {{26, 6, 4, 0, 0x1111}, {26, 6, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData83_BOX_3X3_16S[] = {{28, 6, 4, 0, 0x1111}, {28, 6, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData84_BOX_3X3_16S[] = {{30, 6, 4, 0, 0x1111}, {30, 6, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData85_BOX_3X3_16S[] = {{32, 6, 4, 0, 0x1111}, {32, 6, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData86_BOX_3X3_16S[] = {{48, 6, 4, 0, 0x1111}, {48, 6, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData87_BOX_3X3_16S[] = {{1, 8, 4, 0, 0x1111}, {1, 8, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData88_BOX_3X3_16S[] = {{2, 8, 4, 0, 0x1111}, {2, 8, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData89_BOX_3X3_16S[] = {{3, 8, 4, 0, 0x1111}, {3, 8, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData90_BOX_3X3_16S[] = {{4, 8, 4, 0, 0x1111}, {4, 8, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData91_BOX_3X3_16S[] = {{5, 8, 4, 0, 0x1111}, {5, 8, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData92_BOX_3X3_16S[] = {{6, 8, 4, 0, 0x1111}, {6, 8, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData93_BOX_3X3_16S[] = {{7, 8, 4, 0, 0x1111}, {7, 8, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData94_BOX_3X3_16S[] = {{8, 8, 4, 0, 0x1111}, {8, 8, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData95_BOX_3X3_16S[] = {{10, 8, 4, 0, 0x1111}, {10, 8, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData96_BOX_3X3_16S[] = {{12, 8, 4, 0, 0x1111}, {12, 8, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData97_BOX_3X3_16S[] = {{14, 8, 4, 0, 0x1111}, {14, 8, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData98_BOX_3X3_16S[] = {{16, 8, 4, 0, 0x1111}, {16, 8, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData99_BOX_3X3_16S[] = {{18, 8, 4, 0, 0x1111}, {18, 8, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData100_BOX_3X3_16S[] = {{20, 8, 4, 0, 0x1111}, {20, 8, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData101_BOX_3X3_16S[] = {{22, 8, 4, 0, 0x1111}, {22, 8, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData102_BOX_3X3_16S[] = {{24, 8, 4, 0, 0x1111}, {24, 8, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData103_BOX_3X3_16S[] = {{26, 8, 4, 0, 0x1111}, {26, 8, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData104_BOX_3X3_16S[] = {{28, 8, 4, 0, 0x1111}, {28, 8, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData105_BOX_3X3_16S[] = {{30, 8, 4, 0, 0x1111}, {30, 8, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData106_BOX_3X3_16S[] = {{32, 8, 4, 0, 0x1111}, {32, 8, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData107_BOX_3X3_16S[] = {{1, 10, 4, 0, 0x1111}, {1, 10, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData108_BOX_3X3_16S[] = {{2, 10, 4, 0, 0x1111}, {2, 10, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData109_BOX_3X3_16S[] = {{3, 10, 4, 0, 0x1111}, {3, 10, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData110_BOX_3X3_16S[] = {{4, 10, 4, 0, 0x1111}, {4, 10, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData111_BOX_3X3_16S[] = {{5, 10, 4, 0, 0x1111}, {5, 10, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData112_BOX_3X3_16S[] = {{6, 10, 4, 0, 0x1111}, {6, 10, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData113_BOX_3X3_16S[] = {{7, 10, 4, 0, 0x1111}, {7, 10, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData114_BOX_3X3_16S[] = {{8, 10, 4, 0, 0x1111}, {8, 10, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData115_BOX_3X3_16S[] = {{10, 10, 4, 0, 0x1111}, {10, 10, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData116_BOX_3X3_16S[] = {{12, 10, 4, 0, 0x1111}, {12, 10, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData117_BOX_3X3_16S[] = {{14, 10, 4, 0, 0x1111}, {14, 10, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData118_BOX_3X3_16S[] = {{16, 10, 4, 0, 0x1111}, {16, 10, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData119_BOX_3X3_16S[] = {{18, 10, 4, 0, 0x1111}, {18, 10, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData120_BOX_3X3_16S[] = {{20, 10, 4, 0, 0x1111}, {20, 10, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData121_BOX_3X3_16S[] = {{22, 10, 4, 0, 0x1111}, {22, 10, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData122_BOX_3X3_16S[] = {{24, 10, 4, 0, 0x1111}, {24, 10, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData123_BOX_3X3_16S[] = {{26, 10, 4, 0, 0x1111}, {26, 10, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData124_BOX_3X3_16S[] = {{28, 10, 4, 0, 0x1111}, {28, 10, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData125_BOX_3X3_16S[] = {{1, 12, 4, 0, 0x1111}, {1, 12, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData126_BOX_3X3_16S[] = {{2, 12, 4, 0, 0x1111}, {2, 12, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData127_BOX_3X3_16S[] = {{3, 12, 4, 0, 0x1111}, {3, 12, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData128_BOX_3X3_16S[] = {{4, 12, 4, 0, 0x1111}, {4, 12, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData129_BOX_3X3_16S[] = {{5, 12, 4, 0, 0x1111}, {5, 12, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData130_BOX_3X3_16S[] = {{6, 12, 4, 0, 0x1111}, {6, 12, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData131_BOX_3X3_16S[] = {{7, 12, 4, 0, 0x1111}, {7, 12, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData132_BOX_3X3_16S[] = {{8, 12, 4, 0, 0x1111}, {8, 12, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData133_BOX_3X3_16S[] = {{10, 12, 4, 0, 0x1111}, {10, 12, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData134_BOX_3X3_16S[] = {{12, 12, 4, 0, 0x1111}, {12, 12, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData135_BOX_3X3_16S[] = {{14, 12, 4, 0, 0x1111}, {14, 12, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData136_BOX_3X3_16S[] = {{16, 12, 4, 0, 0x1111}, {16, 12, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData137_BOX_3X3_16S[] = {{18, 12, 4, 0, 0x1111}, {18, 12, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData138_BOX_3X3_16S[] = {{20, 12, 4, 0, 0x1111}, {20, 12, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData139_BOX_3X3_16S[] = {{22, 12, 4, 0, 0x1111}, {22, 12, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData140_BOX_3X3_16S[] = {{24, 12, 4, 0, 0x1111}, {24, 12, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData141_BOX_3X3_16S[] = {{1, 14, 4, 0, 0x1111}, {1, 14, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData142_BOX_3X3_16S[] = {{2, 14, 4, 0, 0x1111}, {2, 14, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData143_BOX_3X3_16S[] = {{3, 14, 4, 0, 0x1111}, {3, 14, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData144_BOX_3X3_16S[] = {{4, 14, 4, 0, 0x1111}, {4, 14, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData145_BOX_3X3_16S[] = {{5, 14, 4, 0, 0x1111}, {5, 14, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData146_BOX_3X3_16S[] = {{6, 14, 4, 0, 0x1111}, {6, 14, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData147_BOX_3X3_16S[] = {{7, 14, 4, 0, 0x1111}, {7, 14, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData148_BOX_3X3_16S[] = {{8, 14, 4, 0, 0x1111}, {8, 14, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData149_BOX_3X3_16S[] = {{10, 14, 4, 0, 0x1111}, {10, 14, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData150_BOX_3X3_16S[] = {{12, 14, 4, 0, 0x1111}, {12, 14, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData151_BOX_3X3_16S[] = {{14, 14, 4, 0, 0x1111}, {14, 14, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData152_BOX_3X3_16S[] = {{16, 14, 4, 0, 0x1111}, {16, 14, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData153_BOX_3X3_16S[] = {{18, 14, 4, 0, 0x1111}, {18, 14, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData154_BOX_3X3_16S[] = {{20, 14, 4, 0, 0x1111}, {20, 14, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData155_BOX_3X3_16S[] = {{1, 16, 4, 0, 0x1111}, {1, 16, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData156_BOX_3X3_16S[] = {{2, 16, 4, 0, 0x1111}, {2, 16, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData157_BOX_3X3_16S[] = {{3, 16, 4, 0, 0x1111}, {3, 16, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData158_BOX_3X3_16S[] = {{4, 16, 4, 0, 0x1111}, {4, 16, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData159_BOX_3X3_16S[] = {{5, 16, 4, 0, 0x1111}, {5, 16, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData160_BOX_3X3_16S[] = {{6, 16, 4, 0, 0x1111}, {6, 16, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData161_BOX_3X3_16S[] = {{7, 16, 4, 0, 0x1111}, {7, 16, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData162_BOX_3X3_16S[] = {{8, 16, 4, 0, 0x1111}, {8, 16, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData163_BOX_3X3_16S[] = {{10, 16, 4, 0, 0x1111}, {10, 16, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData164_BOX_3X3_16S[] = {{12, 16, 4, 0, 0x1111}, {12, 16, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData165_BOX_3X3_16S[] = {{14, 16, 4, 0, 0x1111}, {14, 16, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData166_BOX_3X3_16S[] = {{16, 16, 4, 0, 0x1111}, {16, 16, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData167_BOX_3X3_16S[] = {{18, 16, 4, 0, 0x1111}, {18, 16, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData168_BOX_3X3_16S[] = {{1, 18, 4, 0, 0x1111}, {1, 18, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData169_BOX_3X3_16S[] = {{2, 18, 4, 0, 0x1111}, {2, 18, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData170_BOX_3X3_16S[] = {{3, 18, 4, 0, 0x1111}, {3, 18, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData171_BOX_3X3_16S[] = {{4, 18, 4, 0, 0x1111}, {4, 18, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData172_BOX_3X3_16S[] = {{5, 18, 4, 0, 0x1111}, {5, 18, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData173_BOX_3X3_16S[] = {{6, 18, 4, 0, 0x1111}, {6, 18, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData174_BOX_3X3_16S[] = {{7, 18, 4, 0, 0x1111}, {7, 18, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData175_BOX_3X3_16S[] = {{8, 18, 4, 0, 0x1111}, {8, 18, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData176_BOX_3X3_16S[] = {{10, 18, 4, 0, 0x1111}, {10, 18, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData177_BOX_3X3_16S[] = {{12, 18, 4, 0, 0x1111}, {12, 18, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData178_BOX_3X3_16S[] = {{14, 18, 4, 0, 0x1111}, {14, 18, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData179_BOX_3X3_16S[] = {{16, 18, 4, 0, 0x1111}, {16, 18, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData180_BOX_3X3_16S[] = {{1, 20, 4, 0, 0x1111}, {1, 20, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData181_BOX_3X3_16S[] = {{2, 20, 4, 0, 0x1111}, {2, 20, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData182_BOX_3X3_16S[] = {{3, 20, 4, 0, 0x1111}, {3, 20, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData183_BOX_3X3_16S[] = {{4, 20, 4, 0, 0x1111}, {4, 20, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData184_BOX_3X3_16S[] = {{5, 20, 4, 0, 0x1111}, {5, 20, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData185_BOX_3X3_16S[] = {{6, 20, 4, 0, 0x1111}, {6, 20, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData186_BOX_3X3_16S[] = {{7, 20, 4, 0, 0x1111}, {7, 20, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData187_BOX_3X3_16S[] = {{8, 20, 4, 0, 0x1111}, {8, 20, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData188_BOX_3X3_16S[] = {{10, 20, 4, 0, 0x1111}, {10, 20, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData189_BOX_3X3_16S[] = {{12, 20, 4, 0, 0x1111}, {12, 20, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData190_BOX_3X3_16S[] = {{14, 20, 4, 0, 0x1111}, {14, 20, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData191_BOX_3X3_16S[] = {{1, 22, 4, 0, 0x1111}, {1, 22, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData192_BOX_3X3_16S[] = {{2, 22, 4, 0, 0x1111}, {2, 22, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData193_BOX_3X3_16S[] = {{3, 22, 4, 0, 0x1111}, {3, 22, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData194_BOX_3X3_16S[] = {{4, 22, 4, 0, 0x1111}, {4, 22, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData195_BOX_3X3_16S[] = {{5, 22, 4, 0, 0x1111}, {5, 22, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData196_BOX_3X3_16S[] = {{6, 22, 4, 0, 0x1111}, {6, 22, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData197_BOX_3X3_16S[] = {{7, 22, 4, 0, 0x1111}, {7, 22, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData198_BOX_3X3_16S[] = {{8, 22, 4, 0, 0x1111}, {8, 22, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData199_BOX_3X3_16S[] = {{10, 22, 4, 0, 0x1111}, {10, 22, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData200_BOX_3X3_16S[] = {{12, 22, 4, 0, 0x1111}, {12, 22, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData201_BOX_3X3_16S[] = {{1, 24, 4, 0, 0x1111}, {1, 24, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData202_BOX_3X3_16S[] = {{2, 24, 4, 0, 0x1111}, {2, 24, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData203_BOX_3X3_16S[] = {{3, 24, 4, 0, 0x1111}, {3, 24, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData204_BOX_3X3_16S[] = {{4, 24, 4, 0, 0x1111}, {4, 24, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData205_BOX_3X3_16S[] = {{5, 24, 4, 0, 0x1111}, {5, 24, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData206_BOX_3X3_16S[] = {{6, 24, 4, 0, 0x1111}, {6, 24, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData207_BOX_3X3_16S[] = {{7, 24, 4, 0, 0x1111}, {7, 24, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData208_BOX_3X3_16S[] = {{8, 24, 4, 0, 0x1111}, {8, 24, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData209_BOX_3X3_16S[] = {{10, 24, 4, 0, 0x1111}, {10, 24, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData210_BOX_3X3_16S[] = {{1, 26, 4, 0, 0x1111}, {1, 26, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData211_BOX_3X3_16S[] = {{2, 26, 4, 0, 0x1111}, {2, 26, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData212_BOX_3X3_16S[] = {{3, 26, 4, 0, 0x1111}, {3, 26, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData213_BOX_3X3_16S[] = {{4, 26, 4, 0, 0x1111}, {4, 26, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData214_BOX_3X3_16S[] = {{5, 26, 4, 0, 0x1111}, {5, 26, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData215_BOX_3X3_16S[] = {{6, 26, 4, 0, 0x1111}, {6, 26, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData216_BOX_3X3_16S[] = {{7, 26, 4, 0, 0x1111}, {7, 26, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData217_BOX_3X3_16S[] = {{8, 26, 4, 0, 0x1111}, {8, 26, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData218_BOX_3X3_16S[] = {{10, 26, 4, 0, 0x1111}, {10, 26, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData219_BOX_3X3_16S[] = {{1, 28, 4, 0, 0x1111}, {1, 28, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData220_BOX_3X3_16S[] = {{2, 28, 4, 0, 0x1111}, {2, 28, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData221_BOX_3X3_16S[] = {{3, 28, 4, 0, 0x1111}, {3, 28, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData222_BOX_3X3_16S[] = {{4, 28, 4, 0, 0x1111}, {4, 28, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData223_BOX_3X3_16S[] = {{5, 28, 4, 0, 0x1111}, {5, 28, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData224_BOX_3X3_16S[] = {{6, 28, 4, 0, 0x1111}, {6, 28, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData225_BOX_3X3_16S[] = {{7, 28, 4, 0, 0x1111}, {7, 28, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData226_BOX_3X3_16S[] = {{8, 28, 4, 0, 0x1111}, {8, 28, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData227_BOX_3X3_16S[] = {{1, 30, 4, 0, 0x1111}, {1, 30, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData228_BOX_3X3_16S[] = {{2, 30, 4, 0, 0x1111}, {2, 30, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData229_BOX_3X3_16S[] = {{3, 30, 4, 0, 0x1111}, {3, 30, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData230_BOX_3X3_16S[] = {{4, 30, 4, 0, 0x1111}, {4, 30, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData231_BOX_3X3_16S[] = {{5, 30, 4, 0, 0x1111}, {5, 30, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData232_BOX_3X3_16S[] = {{6, 30, 4, 0, 0x1111}, {6, 30, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData233_BOX_3X3_16S[] = {{7, 30, 4, 0, 0x1111}, {7, 30, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData234_BOX_3X3_16S[] = {{8, 30, 4, 0, 0x1111}, {8, 30, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData235_BOX_3X3_16S[] = {{1, 32, 4, 0, 0x1111}, {1, 32, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData236_BOX_3X3_16S[] = {{2, 32, 4, 0, 0x1111}, {2, 32, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData237_BOX_3X3_16S[] = {{3, 32, 4, 0, 0x1111}, {3, 32, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData238_BOX_3X3_16S[] = {{4, 32, 4, 0, 0x1111}, {4, 32, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData239_BOX_3X3_16S[] = {{5, 32, 4, 0, 0x1111}, {5, 32, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData240_BOX_3X3_16S[] = {{6, 32, 4, 0, 0x1111}, {6, 32, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData241_BOX_3X3_16S[] = {{7, 32, 4, 0, 0x1111}, {7, 32, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData242_BOX_3X3_16S[] = {{8, 32, 4, 0, 0x1111}, {8, 32, 2, 1, 0x0}};

static acf_scenario_kernel_data gScenarioKernelData0_BOX_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData1_BOX_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData2_BOX_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData3_BOX_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData4_BOX_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData5_BOX_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData6_BOX_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData7_BOX_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData8_BOX_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData9_BOX_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData10_BOX_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData11_BOX_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData12_BOX_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData13_BOX_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData14_BOX_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData15_BOX_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData16_BOX_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData17_BOX_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData18_BOX_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData19_BOX_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData20_BOX_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData21_BOX_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData22_BOX_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData23_BOX_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData24_BOX_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData25_BOX_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData26_BOX_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData27_BOX_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData28_BOX_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData29_BOX_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData30_BOX_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData31_BOX_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData32_BOX_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData33_BOX_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData34_BOX_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData35_BOX_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData36_BOX_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData37_BOX_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData38_BOX_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData39_BOX_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData40_BOX_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData41_BOX_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData42_BOX_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData43_BOX_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData44_BOX_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData45_BOX_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData46_BOX_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData47_BOX_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData48_BOX_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData49_BOX_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData50_BOX_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData51_BOX_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData52_BOX_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData53_BOX_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData54_BOX_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData55_BOX_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData56_BOX_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData57_BOX_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData58_BOX_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData59_BOX_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData60_BOX_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData61_BOX_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData62_BOX_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData63_BOX_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData64_BOX_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData65_BOX_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData66_BOX_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData67_BOX_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData68_BOX_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData69_BOX_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData70_BOX_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData71_BOX_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData72_BOX_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData73_BOX_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData74_BOX_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData75_BOX_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData76_BOX_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData77_BOX_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData78_BOX_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData79_BOX_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData80_BOX_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData81_BOX_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData82_BOX_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData83_BOX_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData84_BOX_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData85_BOX_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData86_BOX_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData87_BOX_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData88_BOX_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData89_BOX_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData90_BOX_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData91_BOX_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData92_BOX_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData93_BOX_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData94_BOX_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData95_BOX_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData96_BOX_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData97_BOX_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData98_BOX_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData99_BOX_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData100_BOX_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData101_BOX_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData102_BOX_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData103_BOX_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData104_BOX_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData105_BOX_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData106_BOX_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData107_BOX_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData108_BOX_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData109_BOX_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData110_BOX_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData111_BOX_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData112_BOX_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData113_BOX_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData114_BOX_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData115_BOX_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData116_BOX_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData117_BOX_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData118_BOX_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData119_BOX_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData120_BOX_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData121_BOX_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData122_BOX_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData123_BOX_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData124_BOX_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData125_BOX_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData126_BOX_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData127_BOX_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData128_BOX_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData129_BOX_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData130_BOX_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData131_BOX_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData132_BOX_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData133_BOX_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData134_BOX_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData135_BOX_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData136_BOX_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData137_BOX_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData138_BOX_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData139_BOX_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData140_BOX_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData141_BOX_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData142_BOX_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData143_BOX_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData144_BOX_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData145_BOX_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData146_BOX_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData147_BOX_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData148_BOX_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData149_BOX_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData150_BOX_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData151_BOX_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData152_BOX_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData153_BOX_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData154_BOX_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData155_BOX_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData156_BOX_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData157_BOX_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData158_BOX_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData159_BOX_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData160_BOX_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData161_BOX_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData162_BOX_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData163_BOX_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData164_BOX_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData165_BOX_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData166_BOX_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData167_BOX_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData168_BOX_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData169_BOX_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData170_BOX_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData171_BOX_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData172_BOX_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData173_BOX_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData174_BOX_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData175_BOX_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData176_BOX_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData177_BOX_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData178_BOX_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData179_BOX_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData180_BOX_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData181_BOX_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData182_BOX_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData183_BOX_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData184_BOX_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData185_BOX_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData186_BOX_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData187_BOX_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData188_BOX_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData189_BOX_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData190_BOX_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData191_BOX_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData192_BOX_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData193_BOX_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData194_BOX_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData195_BOX_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData196_BOX_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData197_BOX_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData198_BOX_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData199_BOX_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData200_BOX_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData201_BOX_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData202_BOX_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData203_BOX_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData204_BOX_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData205_BOX_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData206_BOX_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData207_BOX_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData208_BOX_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData209_BOX_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData210_BOX_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData211_BOX_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData212_BOX_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData213_BOX_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData214_BOX_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData215_BOX_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData216_BOX_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData217_BOX_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData218_BOX_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData219_BOX_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData220_BOX_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData221_BOX_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData222_BOX_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData223_BOX_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData224_BOX_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData225_BOX_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData226_BOX_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData227_BOX_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData228_BOX_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData229_BOX_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData230_BOX_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData231_BOX_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData232_BOX_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData233_BOX_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData234_BOX_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData235_BOX_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData236_BOX_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData237_BOX_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData238_BOX_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData239_BOX_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData240_BOX_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData241_BOX_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData242_BOX_3X3_16S[] = {{1}};

static acf_scenario gScenarioArray_BOX_3X3_16S[] = {
{1, 1, 40, 0, 1, gScenarioBufferData0_BOX_3X3_16S, 20, gScenarioKernelData0_BOX_3X3_16S, 2},
{2, 1, 56, 0, 1, gScenarioBufferData1_BOX_3X3_16S, 20, gScenarioKernelData1_BOX_3X3_16S, 2},
{3, 1, 72, 0, 1, gScenarioBufferData2_BOX_3X3_16S, 20, gScenarioKernelData2_BOX_3X3_16S, 2},
{4, 1, 88, 0, 1, gScenarioBufferData3_BOX_3X3_16S, 20, gScenarioKernelData3_BOX_3X3_16S, 2},
{5, 1, 104, 0, 1, gScenarioBufferData4_BOX_3X3_16S, 20, gScenarioKernelData4_BOX_3X3_16S, 2},
{6, 1, 120, 0, 1, gScenarioBufferData5_BOX_3X3_16S, 20, gScenarioKernelData5_BOX_3X3_16S, 2},
{7, 1, 136, 0, 1, gScenarioBufferData6_BOX_3X3_16S, 20, gScenarioKernelData6_BOX_3X3_16S, 2},
{8, 1, 152, 0, 1, gScenarioBufferData7_BOX_3X3_16S, 20, gScenarioKernelData7_BOX_3X3_16S, 2},
{10, 1, 184, 0, 1, gScenarioBufferData8_BOX_3X3_16S, 20, gScenarioKernelData8_BOX_3X3_16S, 2},
{12, 1, 216, 0, 1, gScenarioBufferData9_BOX_3X3_16S, 20, gScenarioKernelData9_BOX_3X3_16S, 2},
{14, 1, 248, 0, 1, gScenarioBufferData10_BOX_3X3_16S, 20, gScenarioKernelData10_BOX_3X3_16S, 2},
{16, 1, 280, 0, 1, gScenarioBufferData11_BOX_3X3_16S, 20, gScenarioKernelData11_BOX_3X3_16S, 2},
{18, 1, 312, 0, 1, gScenarioBufferData12_BOX_3X3_16S, 20, gScenarioKernelData12_BOX_3X3_16S, 2},
{20, 1, 344, 0, 1, gScenarioBufferData13_BOX_3X3_16S, 20, gScenarioKernelData13_BOX_3X3_16S, 2},
{22, 1, 376, 0, 1, gScenarioBufferData14_BOX_3X3_16S, 20, gScenarioKernelData14_BOX_3X3_16S, 2},
{24, 1, 408, 0, 1, gScenarioBufferData15_BOX_3X3_16S, 20, gScenarioKernelData15_BOX_3X3_16S, 2},
{26, 1, 440, 0, 1, gScenarioBufferData16_BOX_3X3_16S, 20, gScenarioKernelData16_BOX_3X3_16S, 2},
{28, 1, 472, 0, 1, gScenarioBufferData17_BOX_3X3_16S, 20, gScenarioKernelData17_BOX_3X3_16S, 2},
{30, 1, 504, 0, 1, gScenarioBufferData18_BOX_3X3_16S, 20, gScenarioKernelData18_BOX_3X3_16S, 2},
{32, 1, 536, 0, 1, gScenarioBufferData19_BOX_3X3_16S, 20, gScenarioKernelData19_BOX_3X3_16S, 2},
{48, 1, 792, 0, 1, gScenarioBufferData20_BOX_3X3_16S, 20, gScenarioKernelData20_BOX_3X3_16S, 2},
{64, 1, 1048, 0, 1, gScenarioBufferData21_BOX_3X3_16S, 20, gScenarioKernelData21_BOX_3X3_16S, 2},
{1, 2, 68, 0, 1, gScenarioBufferData22_BOX_3X3_16S, 20, gScenarioKernelData22_BOX_3X3_16S, 2},
{2, 2, 96, 0, 1, gScenarioBufferData23_BOX_3X3_16S, 20, gScenarioKernelData23_BOX_3X3_16S, 2},
{3, 2, 124, 0, 1, gScenarioBufferData24_BOX_3X3_16S, 20, gScenarioKernelData24_BOX_3X3_16S, 2},
{4, 2, 152, 0, 1, gScenarioBufferData25_BOX_3X3_16S, 20, gScenarioKernelData25_BOX_3X3_16S, 2},
{5, 2, 180, 0, 1, gScenarioBufferData26_BOX_3X3_16S, 20, gScenarioKernelData26_BOX_3X3_16S, 2},
{6, 2, 208, 0, 1, gScenarioBufferData27_BOX_3X3_16S, 20, gScenarioKernelData27_BOX_3X3_16S, 2},
{7, 2, 236, 0, 1, gScenarioBufferData28_BOX_3X3_16S, 20, gScenarioKernelData28_BOX_3X3_16S, 2},
{8, 2, 264, 0, 1, gScenarioBufferData29_BOX_3X3_16S, 20, gScenarioKernelData29_BOX_3X3_16S, 2},
{10, 2, 320, 0, 1, gScenarioBufferData30_BOX_3X3_16S, 20, gScenarioKernelData30_BOX_3X3_16S, 2},
{12, 2, 376, 0, 1, gScenarioBufferData31_BOX_3X3_16S, 20, gScenarioKernelData31_BOX_3X3_16S, 2},
{14, 2, 432, 0, 1, gScenarioBufferData32_BOX_3X3_16S, 20, gScenarioKernelData32_BOX_3X3_16S, 2},
{16, 2, 488, 0, 1, gScenarioBufferData33_BOX_3X3_16S, 20, gScenarioKernelData33_BOX_3X3_16S, 2},
{18, 2, 544, 0, 1, gScenarioBufferData34_BOX_3X3_16S, 20, gScenarioKernelData34_BOX_3X3_16S, 2},
{20, 2, 600, 0, 1, gScenarioBufferData35_BOX_3X3_16S, 20, gScenarioKernelData35_BOX_3X3_16S, 2},
{22, 2, 656, 0, 1, gScenarioBufferData36_BOX_3X3_16S, 20, gScenarioKernelData36_BOX_3X3_16S, 2},
{24, 2, 712, 0, 1, gScenarioBufferData37_BOX_3X3_16S, 20, gScenarioKernelData37_BOX_3X3_16S, 2},
{26, 2, 768, 0, 1, gScenarioBufferData38_BOX_3X3_16S, 20, gScenarioKernelData38_BOX_3X3_16S, 2},
{28, 2, 824, 0, 1, gScenarioBufferData39_BOX_3X3_16S, 20, gScenarioKernelData39_BOX_3X3_16S, 2},
{30, 2, 880, 0, 1, gScenarioBufferData40_BOX_3X3_16S, 20, gScenarioKernelData40_BOX_3X3_16S, 2},
{32, 2, 936, 0, 1, gScenarioBufferData41_BOX_3X3_16S, 20, gScenarioKernelData41_BOX_3X3_16S, 2},
{48, 2, 1384, 0, 1, gScenarioBufferData42_BOX_3X3_16S, 20, gScenarioKernelData42_BOX_3X3_16S, 2},
{64, 2, 1832, 0, 1, gScenarioBufferData43_BOX_3X3_16S, 20, gScenarioKernelData43_BOX_3X3_16S, 2},
{1, 4, 124, 0, 1, gScenarioBufferData44_BOX_3X3_16S, 20, gScenarioKernelData44_BOX_3X3_16S, 2},
{2, 4, 176, 0, 1, gScenarioBufferData45_BOX_3X3_16S, 20, gScenarioKernelData45_BOX_3X3_16S, 2},
{3, 4, 228, 0, 1, gScenarioBufferData46_BOX_3X3_16S, 20, gScenarioKernelData46_BOX_3X3_16S, 2},
{4, 4, 280, 0, 1, gScenarioBufferData47_BOX_3X3_16S, 20, gScenarioKernelData47_BOX_3X3_16S, 2},
{5, 4, 332, 0, 1, gScenarioBufferData48_BOX_3X3_16S, 20, gScenarioKernelData48_BOX_3X3_16S, 2},
{6, 4, 384, 0, 1, gScenarioBufferData49_BOX_3X3_16S, 20, gScenarioKernelData49_BOX_3X3_16S, 2},
{7, 4, 436, 0, 1, gScenarioBufferData50_BOX_3X3_16S, 20, gScenarioKernelData50_BOX_3X3_16S, 2},
{8, 4, 488, 0, 1, gScenarioBufferData51_BOX_3X3_16S, 20, gScenarioKernelData51_BOX_3X3_16S, 2},
{10, 4, 592, 0, 1, gScenarioBufferData52_BOX_3X3_16S, 20, gScenarioKernelData52_BOX_3X3_16S, 2},
{12, 4, 696, 0, 1, gScenarioBufferData53_BOX_3X3_16S, 20, gScenarioKernelData53_BOX_3X3_16S, 2},
{14, 4, 800, 0, 1, gScenarioBufferData54_BOX_3X3_16S, 20, gScenarioKernelData54_BOX_3X3_16S, 2},
{16, 4, 904, 0, 1, gScenarioBufferData55_BOX_3X3_16S, 20, gScenarioKernelData55_BOX_3X3_16S, 2},
{18, 4, 1008, 0, 1, gScenarioBufferData56_BOX_3X3_16S, 20, gScenarioKernelData56_BOX_3X3_16S, 2},
{20, 4, 1112, 0, 1, gScenarioBufferData57_BOX_3X3_16S, 20, gScenarioKernelData57_BOX_3X3_16S, 2},
{22, 4, 1216, 0, 1, gScenarioBufferData58_BOX_3X3_16S, 20, gScenarioKernelData58_BOX_3X3_16S, 2},
{24, 4, 1320, 0, 1, gScenarioBufferData59_BOX_3X3_16S, 20, gScenarioKernelData59_BOX_3X3_16S, 2},
{26, 4, 1424, 0, 1, gScenarioBufferData60_BOX_3X3_16S, 20, gScenarioKernelData60_BOX_3X3_16S, 2},
{28, 4, 1528, 0, 1, gScenarioBufferData61_BOX_3X3_16S, 20, gScenarioKernelData61_BOX_3X3_16S, 2},
{30, 4, 1632, 0, 1, gScenarioBufferData62_BOX_3X3_16S, 20, gScenarioKernelData62_BOX_3X3_16S, 2},
{32, 4, 1736, 0, 1, gScenarioBufferData63_BOX_3X3_16S, 20, gScenarioKernelData63_BOX_3X3_16S, 2},
{48, 4, 2568, 0, 1, gScenarioBufferData64_BOX_3X3_16S, 20, gScenarioKernelData64_BOX_3X3_16S, 2},
{64, 4, 3400, 0, 1, gScenarioBufferData65_BOX_3X3_16S, 20, gScenarioKernelData65_BOX_3X3_16S, 2},
{1, 6, 180, 0, 1, gScenarioBufferData66_BOX_3X3_16S, 20, gScenarioKernelData66_BOX_3X3_16S, 2},
{2, 6, 256, 0, 1, gScenarioBufferData67_BOX_3X3_16S, 20, gScenarioKernelData67_BOX_3X3_16S, 2},
{3, 6, 332, 0, 1, gScenarioBufferData68_BOX_3X3_16S, 20, gScenarioKernelData68_BOX_3X3_16S, 2},
{4, 6, 408, 0, 1, gScenarioBufferData69_BOX_3X3_16S, 20, gScenarioKernelData69_BOX_3X3_16S, 2},
{5, 6, 484, 0, 1, gScenarioBufferData70_BOX_3X3_16S, 20, gScenarioKernelData70_BOX_3X3_16S, 2},
{6, 6, 560, 0, 1, gScenarioBufferData71_BOX_3X3_16S, 20, gScenarioKernelData71_BOX_3X3_16S, 2},
{7, 6, 636, 0, 1, gScenarioBufferData72_BOX_3X3_16S, 20, gScenarioKernelData72_BOX_3X3_16S, 2},
{8, 6, 712, 0, 1, gScenarioBufferData73_BOX_3X3_16S, 20, gScenarioKernelData73_BOX_3X3_16S, 2},
{10, 6, 864, 0, 1, gScenarioBufferData74_BOX_3X3_16S, 20, gScenarioKernelData74_BOX_3X3_16S, 2},
{12, 6, 1016, 0, 1, gScenarioBufferData75_BOX_3X3_16S, 20, gScenarioKernelData75_BOX_3X3_16S, 2},
{14, 6, 1168, 0, 1, gScenarioBufferData76_BOX_3X3_16S, 20, gScenarioKernelData76_BOX_3X3_16S, 2},
{16, 6, 1320, 0, 1, gScenarioBufferData77_BOX_3X3_16S, 20, gScenarioKernelData77_BOX_3X3_16S, 2},
{18, 6, 1472, 0, 1, gScenarioBufferData78_BOX_3X3_16S, 20, gScenarioKernelData78_BOX_3X3_16S, 2},
{20, 6, 1624, 0, 1, gScenarioBufferData79_BOX_3X3_16S, 20, gScenarioKernelData79_BOX_3X3_16S, 2},
{22, 6, 1776, 0, 1, gScenarioBufferData80_BOX_3X3_16S, 20, gScenarioKernelData80_BOX_3X3_16S, 2},
{24, 6, 1928, 0, 1, gScenarioBufferData81_BOX_3X3_16S, 20, gScenarioKernelData81_BOX_3X3_16S, 2},
{26, 6, 2080, 0, 1, gScenarioBufferData82_BOX_3X3_16S, 20, gScenarioKernelData82_BOX_3X3_16S, 2},
{28, 6, 2232, 0, 1, gScenarioBufferData83_BOX_3X3_16S, 20, gScenarioKernelData83_BOX_3X3_16S, 2},
{30, 6, 2384, 0, 1, gScenarioBufferData84_BOX_3X3_16S, 20, gScenarioKernelData84_BOX_3X3_16S, 2},
{32, 6, 2536, 0, 1, gScenarioBufferData85_BOX_3X3_16S, 20, gScenarioKernelData85_BOX_3X3_16S, 2},
{48, 6, 3752, 0, 1, gScenarioBufferData86_BOX_3X3_16S, 20, gScenarioKernelData86_BOX_3X3_16S, 2},
{1, 8, 236, 0, 1, gScenarioBufferData87_BOX_3X3_16S, 20, gScenarioKernelData87_BOX_3X3_16S, 2},
{2, 8, 336, 0, 1, gScenarioBufferData88_BOX_3X3_16S, 20, gScenarioKernelData88_BOX_3X3_16S, 2},
{3, 8, 436, 0, 1, gScenarioBufferData89_BOX_3X3_16S, 20, gScenarioKernelData89_BOX_3X3_16S, 2},
{4, 8, 536, 0, 1, gScenarioBufferData90_BOX_3X3_16S, 20, gScenarioKernelData90_BOX_3X3_16S, 2},
{5, 8, 636, 0, 1, gScenarioBufferData91_BOX_3X3_16S, 20, gScenarioKernelData91_BOX_3X3_16S, 2},
{6, 8, 736, 0, 1, gScenarioBufferData92_BOX_3X3_16S, 20, gScenarioKernelData92_BOX_3X3_16S, 2},
{7, 8, 836, 0, 1, gScenarioBufferData93_BOX_3X3_16S, 20, gScenarioKernelData93_BOX_3X3_16S, 2},
{8, 8, 936, 0, 1, gScenarioBufferData94_BOX_3X3_16S, 20, gScenarioKernelData94_BOX_3X3_16S, 2},
{10, 8, 1136, 0, 1, gScenarioBufferData95_BOX_3X3_16S, 20, gScenarioKernelData95_BOX_3X3_16S, 2},
{12, 8, 1336, 0, 1, gScenarioBufferData96_BOX_3X3_16S, 20, gScenarioKernelData96_BOX_3X3_16S, 2},
{14, 8, 1536, 0, 1, gScenarioBufferData97_BOX_3X3_16S, 20, gScenarioKernelData97_BOX_3X3_16S, 2},
{16, 8, 1736, 0, 1, gScenarioBufferData98_BOX_3X3_16S, 20, gScenarioKernelData98_BOX_3X3_16S, 2},
{18, 8, 1936, 0, 1, gScenarioBufferData99_BOX_3X3_16S, 20, gScenarioKernelData99_BOX_3X3_16S, 2},
{20, 8, 2136, 0, 1, gScenarioBufferData100_BOX_3X3_16S, 20, gScenarioKernelData100_BOX_3X3_16S, 2},
{22, 8, 2336, 0, 1, gScenarioBufferData101_BOX_3X3_16S, 20, gScenarioKernelData101_BOX_3X3_16S, 2},
{24, 8, 2536, 0, 1, gScenarioBufferData102_BOX_3X3_16S, 20, gScenarioKernelData102_BOX_3X3_16S, 2},
{26, 8, 2736, 0, 1, gScenarioBufferData103_BOX_3X3_16S, 20, gScenarioKernelData103_BOX_3X3_16S, 2},
{28, 8, 2936, 0, 1, gScenarioBufferData104_BOX_3X3_16S, 20, gScenarioKernelData104_BOX_3X3_16S, 2},
{30, 8, 3136, 0, 1, gScenarioBufferData105_BOX_3X3_16S, 20, gScenarioKernelData105_BOX_3X3_16S, 2},
{32, 8, 3336, 0, 1, gScenarioBufferData106_BOX_3X3_16S, 20, gScenarioKernelData106_BOX_3X3_16S, 2},
{1, 10, 292, 0, 1, gScenarioBufferData107_BOX_3X3_16S, 20, gScenarioKernelData107_BOX_3X3_16S, 2},
{2, 10, 416, 0, 1, gScenarioBufferData108_BOX_3X3_16S, 20, gScenarioKernelData108_BOX_3X3_16S, 2},
{3, 10, 540, 0, 1, gScenarioBufferData109_BOX_3X3_16S, 20, gScenarioKernelData109_BOX_3X3_16S, 2},
{4, 10, 664, 0, 1, gScenarioBufferData110_BOX_3X3_16S, 20, gScenarioKernelData110_BOX_3X3_16S, 2},
{5, 10, 788, 0, 1, gScenarioBufferData111_BOX_3X3_16S, 20, gScenarioKernelData111_BOX_3X3_16S, 2},
{6, 10, 912, 0, 1, gScenarioBufferData112_BOX_3X3_16S, 20, gScenarioKernelData112_BOX_3X3_16S, 2},
{7, 10, 1036, 0, 1, gScenarioBufferData113_BOX_3X3_16S, 20, gScenarioKernelData113_BOX_3X3_16S, 2},
{8, 10, 1160, 0, 1, gScenarioBufferData114_BOX_3X3_16S, 20, gScenarioKernelData114_BOX_3X3_16S, 2},
{10, 10, 1408, 0, 1, gScenarioBufferData115_BOX_3X3_16S, 20, gScenarioKernelData115_BOX_3X3_16S, 2},
{12, 10, 1656, 0, 1, gScenarioBufferData116_BOX_3X3_16S, 20, gScenarioKernelData116_BOX_3X3_16S, 2},
{14, 10, 1904, 0, 1, gScenarioBufferData117_BOX_3X3_16S, 20, gScenarioKernelData117_BOX_3X3_16S, 2},
{16, 10, 2152, 0, 1, gScenarioBufferData118_BOX_3X3_16S, 20, gScenarioKernelData118_BOX_3X3_16S, 2},
{18, 10, 2400, 0, 1, gScenarioBufferData119_BOX_3X3_16S, 20, gScenarioKernelData119_BOX_3X3_16S, 2},
{20, 10, 2648, 0, 1, gScenarioBufferData120_BOX_3X3_16S, 20, gScenarioKernelData120_BOX_3X3_16S, 2},
{22, 10, 2896, 0, 1, gScenarioBufferData121_BOX_3X3_16S, 20, gScenarioKernelData121_BOX_3X3_16S, 2},
{24, 10, 3144, 0, 1, gScenarioBufferData122_BOX_3X3_16S, 20, gScenarioKernelData122_BOX_3X3_16S, 2},
{26, 10, 3392, 0, 1, gScenarioBufferData123_BOX_3X3_16S, 20, gScenarioKernelData123_BOX_3X3_16S, 2},
{28, 10, 3640, 0, 1, gScenarioBufferData124_BOX_3X3_16S, 20, gScenarioKernelData124_BOX_3X3_16S, 2},
{1, 12, 348, 0, 1, gScenarioBufferData125_BOX_3X3_16S, 20, gScenarioKernelData125_BOX_3X3_16S, 2},
{2, 12, 496, 0, 1, gScenarioBufferData126_BOX_3X3_16S, 20, gScenarioKernelData126_BOX_3X3_16S, 2},
{3, 12, 644, 0, 1, gScenarioBufferData127_BOX_3X3_16S, 20, gScenarioKernelData127_BOX_3X3_16S, 2},
{4, 12, 792, 0, 1, gScenarioBufferData128_BOX_3X3_16S, 20, gScenarioKernelData128_BOX_3X3_16S, 2},
{5, 12, 940, 0, 1, gScenarioBufferData129_BOX_3X3_16S, 20, gScenarioKernelData129_BOX_3X3_16S, 2},
{6, 12, 1088, 0, 1, gScenarioBufferData130_BOX_3X3_16S, 20, gScenarioKernelData130_BOX_3X3_16S, 2},
{7, 12, 1236, 0, 1, gScenarioBufferData131_BOX_3X3_16S, 20, gScenarioKernelData131_BOX_3X3_16S, 2},
{8, 12, 1384, 0, 1, gScenarioBufferData132_BOX_3X3_16S, 20, gScenarioKernelData132_BOX_3X3_16S, 2},
{10, 12, 1680, 0, 1, gScenarioBufferData133_BOX_3X3_16S, 20, gScenarioKernelData133_BOX_3X3_16S, 2},
{12, 12, 1976, 0, 1, gScenarioBufferData134_BOX_3X3_16S, 20, gScenarioKernelData134_BOX_3X3_16S, 2},
{14, 12, 2272, 0, 1, gScenarioBufferData135_BOX_3X3_16S, 20, gScenarioKernelData135_BOX_3X3_16S, 2},
{16, 12, 2568, 0, 1, gScenarioBufferData136_BOX_3X3_16S, 20, gScenarioKernelData136_BOX_3X3_16S, 2},
{18, 12, 2864, 0, 1, gScenarioBufferData137_BOX_3X3_16S, 20, gScenarioKernelData137_BOX_3X3_16S, 2},
{20, 12, 3160, 0, 1, gScenarioBufferData138_BOX_3X3_16S, 20, gScenarioKernelData138_BOX_3X3_16S, 2},
{22, 12, 3456, 0, 1, gScenarioBufferData139_BOX_3X3_16S, 20, gScenarioKernelData139_BOX_3X3_16S, 2},
{24, 12, 3752, 0, 1, gScenarioBufferData140_BOX_3X3_16S, 20, gScenarioKernelData140_BOX_3X3_16S, 2},
{1, 14, 404, 0, 1, gScenarioBufferData141_BOX_3X3_16S, 20, gScenarioKernelData141_BOX_3X3_16S, 2},
{2, 14, 576, 0, 1, gScenarioBufferData142_BOX_3X3_16S, 20, gScenarioKernelData142_BOX_3X3_16S, 2},
{3, 14, 748, 0, 1, gScenarioBufferData143_BOX_3X3_16S, 20, gScenarioKernelData143_BOX_3X3_16S, 2},
{4, 14, 920, 0, 1, gScenarioBufferData144_BOX_3X3_16S, 20, gScenarioKernelData144_BOX_3X3_16S, 2},
{5, 14, 1092, 0, 1, gScenarioBufferData145_BOX_3X3_16S, 20, gScenarioKernelData145_BOX_3X3_16S, 2},
{6, 14, 1264, 0, 1, gScenarioBufferData146_BOX_3X3_16S, 20, gScenarioKernelData146_BOX_3X3_16S, 2},
{7, 14, 1436, 0, 1, gScenarioBufferData147_BOX_3X3_16S, 20, gScenarioKernelData147_BOX_3X3_16S, 2},
{8, 14, 1608, 0, 1, gScenarioBufferData148_BOX_3X3_16S, 20, gScenarioKernelData148_BOX_3X3_16S, 2},
{10, 14, 1952, 0, 1, gScenarioBufferData149_BOX_3X3_16S, 20, gScenarioKernelData149_BOX_3X3_16S, 2},
{12, 14, 2296, 0, 1, gScenarioBufferData150_BOX_3X3_16S, 20, gScenarioKernelData150_BOX_3X3_16S, 2},
{14, 14, 2640, 0, 1, gScenarioBufferData151_BOX_3X3_16S, 20, gScenarioKernelData151_BOX_3X3_16S, 2},
{16, 14, 2984, 0, 1, gScenarioBufferData152_BOX_3X3_16S, 20, gScenarioKernelData152_BOX_3X3_16S, 2},
{18, 14, 3328, 0, 1, gScenarioBufferData153_BOX_3X3_16S, 20, gScenarioKernelData153_BOX_3X3_16S, 2},
{20, 14, 3672, 0, 1, gScenarioBufferData154_BOX_3X3_16S, 20, gScenarioKernelData154_BOX_3X3_16S, 2},
{1, 16, 460, 0, 1, gScenarioBufferData155_BOX_3X3_16S, 20, gScenarioKernelData155_BOX_3X3_16S, 2},
{2, 16, 656, 0, 1, gScenarioBufferData156_BOX_3X3_16S, 20, gScenarioKernelData156_BOX_3X3_16S, 2},
{3, 16, 852, 0, 1, gScenarioBufferData157_BOX_3X3_16S, 20, gScenarioKernelData157_BOX_3X3_16S, 2},
{4, 16, 1048, 0, 1, gScenarioBufferData158_BOX_3X3_16S, 20, gScenarioKernelData158_BOX_3X3_16S, 2},
{5, 16, 1244, 0, 1, gScenarioBufferData159_BOX_3X3_16S, 20, gScenarioKernelData159_BOX_3X3_16S, 2},
{6, 16, 1440, 0, 1, gScenarioBufferData160_BOX_3X3_16S, 20, gScenarioKernelData160_BOX_3X3_16S, 2},
{7, 16, 1636, 0, 1, gScenarioBufferData161_BOX_3X3_16S, 20, gScenarioKernelData161_BOX_3X3_16S, 2},
{8, 16, 1832, 0, 1, gScenarioBufferData162_BOX_3X3_16S, 20, gScenarioKernelData162_BOX_3X3_16S, 2},
{10, 16, 2224, 0, 1, gScenarioBufferData163_BOX_3X3_16S, 20, gScenarioKernelData163_BOX_3X3_16S, 2},
{12, 16, 2616, 0, 1, gScenarioBufferData164_BOX_3X3_16S, 20, gScenarioKernelData164_BOX_3X3_16S, 2},
{14, 16, 3008, 0, 1, gScenarioBufferData165_BOX_3X3_16S, 20, gScenarioKernelData165_BOX_3X3_16S, 2},
{16, 16, 3400, 0, 1, gScenarioBufferData166_BOX_3X3_16S, 20, gScenarioKernelData166_BOX_3X3_16S, 2},
{18, 16, 3792, 0, 1, gScenarioBufferData167_BOX_3X3_16S, 20, gScenarioKernelData167_BOX_3X3_16S, 2},
{1, 18, 516, 0, 1, gScenarioBufferData168_BOX_3X3_16S, 20, gScenarioKernelData168_BOX_3X3_16S, 2},
{2, 18, 736, 0, 1, gScenarioBufferData169_BOX_3X3_16S, 20, gScenarioKernelData169_BOX_3X3_16S, 2},
{3, 18, 956, 0, 1, gScenarioBufferData170_BOX_3X3_16S, 20, gScenarioKernelData170_BOX_3X3_16S, 2},
{4, 18, 1176, 0, 1, gScenarioBufferData171_BOX_3X3_16S, 20, gScenarioKernelData171_BOX_3X3_16S, 2},
{5, 18, 1396, 0, 1, gScenarioBufferData172_BOX_3X3_16S, 20, gScenarioKernelData172_BOX_3X3_16S, 2},
{6, 18, 1616, 0, 1, gScenarioBufferData173_BOX_3X3_16S, 20, gScenarioKernelData173_BOX_3X3_16S, 2},
{7, 18, 1836, 0, 1, gScenarioBufferData174_BOX_3X3_16S, 20, gScenarioKernelData174_BOX_3X3_16S, 2},
{8, 18, 2056, 0, 1, gScenarioBufferData175_BOX_3X3_16S, 20, gScenarioKernelData175_BOX_3X3_16S, 2},
{10, 18, 2496, 0, 1, gScenarioBufferData176_BOX_3X3_16S, 20, gScenarioKernelData176_BOX_3X3_16S, 2},
{12, 18, 2936, 0, 1, gScenarioBufferData177_BOX_3X3_16S, 20, gScenarioKernelData177_BOX_3X3_16S, 2},
{14, 18, 3376, 0, 1, gScenarioBufferData178_BOX_3X3_16S, 20, gScenarioKernelData178_BOX_3X3_16S, 2},
{16, 18, 3816, 0, 1, gScenarioBufferData179_BOX_3X3_16S, 20, gScenarioKernelData179_BOX_3X3_16S, 2},
{1, 20, 572, 0, 1, gScenarioBufferData180_BOX_3X3_16S, 20, gScenarioKernelData180_BOX_3X3_16S, 2},
{2, 20, 816, 0, 1, gScenarioBufferData181_BOX_3X3_16S, 20, gScenarioKernelData181_BOX_3X3_16S, 2},
{3, 20, 1060, 0, 1, gScenarioBufferData182_BOX_3X3_16S, 20, gScenarioKernelData182_BOX_3X3_16S, 2},
{4, 20, 1304, 0, 1, gScenarioBufferData183_BOX_3X3_16S, 20, gScenarioKernelData183_BOX_3X3_16S, 2},
{5, 20, 1548, 0, 1, gScenarioBufferData184_BOX_3X3_16S, 20, gScenarioKernelData184_BOX_3X3_16S, 2},
{6, 20, 1792, 0, 1, gScenarioBufferData185_BOX_3X3_16S, 20, gScenarioKernelData185_BOX_3X3_16S, 2},
{7, 20, 2036, 0, 1, gScenarioBufferData186_BOX_3X3_16S, 20, gScenarioKernelData186_BOX_3X3_16S, 2},
{8, 20, 2280, 0, 1, gScenarioBufferData187_BOX_3X3_16S, 20, gScenarioKernelData187_BOX_3X3_16S, 2},
{10, 20, 2768, 0, 1, gScenarioBufferData188_BOX_3X3_16S, 20, gScenarioKernelData188_BOX_3X3_16S, 2},
{12, 20, 3256, 0, 1, gScenarioBufferData189_BOX_3X3_16S, 20, gScenarioKernelData189_BOX_3X3_16S, 2},
{14, 20, 3744, 0, 1, gScenarioBufferData190_BOX_3X3_16S, 20, gScenarioKernelData190_BOX_3X3_16S, 2},
{1, 22, 628, 0, 1, gScenarioBufferData191_BOX_3X3_16S, 20, gScenarioKernelData191_BOX_3X3_16S, 2},
{2, 22, 896, 0, 1, gScenarioBufferData192_BOX_3X3_16S, 20, gScenarioKernelData192_BOX_3X3_16S, 2},
{3, 22, 1164, 0, 1, gScenarioBufferData193_BOX_3X3_16S, 20, gScenarioKernelData193_BOX_3X3_16S, 2},
{4, 22, 1432, 0, 1, gScenarioBufferData194_BOX_3X3_16S, 20, gScenarioKernelData194_BOX_3X3_16S, 2},
{5, 22, 1700, 0, 1, gScenarioBufferData195_BOX_3X3_16S, 20, gScenarioKernelData195_BOX_3X3_16S, 2},
{6, 22, 1968, 0, 1, gScenarioBufferData196_BOX_3X3_16S, 20, gScenarioKernelData196_BOX_3X3_16S, 2},
{7, 22, 2236, 0, 1, gScenarioBufferData197_BOX_3X3_16S, 20, gScenarioKernelData197_BOX_3X3_16S, 2},
{8, 22, 2504, 0, 1, gScenarioBufferData198_BOX_3X3_16S, 20, gScenarioKernelData198_BOX_3X3_16S, 2},
{10, 22, 3040, 0, 1, gScenarioBufferData199_BOX_3X3_16S, 20, gScenarioKernelData199_BOX_3X3_16S, 2},
{12, 22, 3576, 0, 1, gScenarioBufferData200_BOX_3X3_16S, 20, gScenarioKernelData200_BOX_3X3_16S, 2},
{1, 24, 684, 0, 1, gScenarioBufferData201_BOX_3X3_16S, 20, gScenarioKernelData201_BOX_3X3_16S, 2},
{2, 24, 976, 0, 1, gScenarioBufferData202_BOX_3X3_16S, 20, gScenarioKernelData202_BOX_3X3_16S, 2},
{3, 24, 1268, 0, 1, gScenarioBufferData203_BOX_3X3_16S, 20, gScenarioKernelData203_BOX_3X3_16S, 2},
{4, 24, 1560, 0, 1, gScenarioBufferData204_BOX_3X3_16S, 20, gScenarioKernelData204_BOX_3X3_16S, 2},
{5, 24, 1852, 0, 1, gScenarioBufferData205_BOX_3X3_16S, 20, gScenarioKernelData205_BOX_3X3_16S, 2},
{6, 24, 2144, 0, 1, gScenarioBufferData206_BOX_3X3_16S, 20, gScenarioKernelData206_BOX_3X3_16S, 2},
{7, 24, 2436, 0, 1, gScenarioBufferData207_BOX_3X3_16S, 20, gScenarioKernelData207_BOX_3X3_16S, 2},
{8, 24, 2728, 0, 1, gScenarioBufferData208_BOX_3X3_16S, 20, gScenarioKernelData208_BOX_3X3_16S, 2},
{10, 24, 3312, 0, 1, gScenarioBufferData209_BOX_3X3_16S, 20, gScenarioKernelData209_BOX_3X3_16S, 2},
{1, 26, 740, 0, 1, gScenarioBufferData210_BOX_3X3_16S, 20, gScenarioKernelData210_BOX_3X3_16S, 2},
{2, 26, 1056, 0, 1, gScenarioBufferData211_BOX_3X3_16S, 20, gScenarioKernelData211_BOX_3X3_16S, 2},
{3, 26, 1372, 0, 1, gScenarioBufferData212_BOX_3X3_16S, 20, gScenarioKernelData212_BOX_3X3_16S, 2},
{4, 26, 1688, 0, 1, gScenarioBufferData213_BOX_3X3_16S, 20, gScenarioKernelData213_BOX_3X3_16S, 2},
{5, 26, 2004, 0, 1, gScenarioBufferData214_BOX_3X3_16S, 20, gScenarioKernelData214_BOX_3X3_16S, 2},
{6, 26, 2320, 0, 1, gScenarioBufferData215_BOX_3X3_16S, 20, gScenarioKernelData215_BOX_3X3_16S, 2},
{7, 26, 2636, 0, 1, gScenarioBufferData216_BOX_3X3_16S, 20, gScenarioKernelData216_BOX_3X3_16S, 2},
{8, 26, 2952, 0, 1, gScenarioBufferData217_BOX_3X3_16S, 20, gScenarioKernelData217_BOX_3X3_16S, 2},
{10, 26, 3584, 0, 1, gScenarioBufferData218_BOX_3X3_16S, 20, gScenarioKernelData218_BOX_3X3_16S, 2},
{1, 28, 796, 0, 1, gScenarioBufferData219_BOX_3X3_16S, 20, gScenarioKernelData219_BOX_3X3_16S, 2},
{2, 28, 1136, 0, 1, gScenarioBufferData220_BOX_3X3_16S, 20, gScenarioKernelData220_BOX_3X3_16S, 2},
{3, 28, 1476, 0, 1, gScenarioBufferData221_BOX_3X3_16S, 20, gScenarioKernelData221_BOX_3X3_16S, 2},
{4, 28, 1816, 0, 1, gScenarioBufferData222_BOX_3X3_16S, 20, gScenarioKernelData222_BOX_3X3_16S, 2},
{5, 28, 2156, 0, 1, gScenarioBufferData223_BOX_3X3_16S, 20, gScenarioKernelData223_BOX_3X3_16S, 2},
{6, 28, 2496, 0, 1, gScenarioBufferData224_BOX_3X3_16S, 20, gScenarioKernelData224_BOX_3X3_16S, 2},
{7, 28, 2836, 0, 1, gScenarioBufferData225_BOX_3X3_16S, 20, gScenarioKernelData225_BOX_3X3_16S, 2},
{8, 28, 3176, 0, 1, gScenarioBufferData226_BOX_3X3_16S, 20, gScenarioKernelData226_BOX_3X3_16S, 2},
{1, 30, 852, 0, 1, gScenarioBufferData227_BOX_3X3_16S, 20, gScenarioKernelData227_BOX_3X3_16S, 2},
{2, 30, 1216, 0, 1, gScenarioBufferData228_BOX_3X3_16S, 20, gScenarioKernelData228_BOX_3X3_16S, 2},
{3, 30, 1580, 0, 1, gScenarioBufferData229_BOX_3X3_16S, 20, gScenarioKernelData229_BOX_3X3_16S, 2},
{4, 30, 1944, 0, 1, gScenarioBufferData230_BOX_3X3_16S, 20, gScenarioKernelData230_BOX_3X3_16S, 2},
{5, 30, 2308, 0, 1, gScenarioBufferData231_BOX_3X3_16S, 20, gScenarioKernelData231_BOX_3X3_16S, 2},
{6, 30, 2672, 0, 1, gScenarioBufferData232_BOX_3X3_16S, 20, gScenarioKernelData232_BOX_3X3_16S, 2},
{7, 30, 3036, 0, 1, gScenarioBufferData233_BOX_3X3_16S, 20, gScenarioKernelData233_BOX_3X3_16S, 2},
{8, 30, 3400, 0, 1, gScenarioBufferData234_BOX_3X3_16S, 20, gScenarioKernelData234_BOX_3X3_16S, 2},
{1, 32, 908, 0, 1, gScenarioBufferData235_BOX_3X3_16S, 20, gScenarioKernelData235_BOX_3X3_16S, 2},
{2, 32, 1296, 0, 1, gScenarioBufferData236_BOX_3X3_16S, 20, gScenarioKernelData236_BOX_3X3_16S, 2},
{3, 32, 1684, 0, 1, gScenarioBufferData237_BOX_3X3_16S, 20, gScenarioKernelData237_BOX_3X3_16S, 2},
{4, 32, 2072, 0, 1, gScenarioBufferData238_BOX_3X3_16S, 20, gScenarioKernelData238_BOX_3X3_16S, 2},
{5, 32, 2460, 0, 1, gScenarioBufferData239_BOX_3X3_16S, 20, gScenarioKernelData239_BOX_3X3_16S, 2},
{6, 32, 2848, 0, 1, gScenarioBufferData240_BOX_3X3_16S, 20, gScenarioKernelData240_BOX_3X3_16S, 2},
{7, 32, 3236, 0, 1, gScenarioBufferData241_BOX_3X3_16S, 20, gScenarioKernelData241_BOX_3X3_16S, 2},
{8, 32, 3624, 0, 1, gScenarioBufferData242_BOX_3X3_16S, 20, gScenarioKernelData242_BOX_3X3_16S, 2}
};

static acf_scenario_list gScenarioList_BOX_3X3_16S = {
243, //number of scenarios
gScenarioArray_BOX_3X3_16S};
//**************************************************************

class BOX_3X3_16S : public ACF_Process_APU
{
public:
   BOX_3X3_16S(int32_t apex_id = 0) : ACF_Process_APU(apex_id)
   {} 

   int32_t Initialize()
   {
      int32_t lRetVal = 0;

      if (!Initialized()) //initialization steps that only need to occur once
      {
         SetProcessIdentifier("BOX_3X3_16S");
         SetApuLoadInfo(BOX_3X3_16S_LOAD_SEGMENTS,
                        BOX_3X3_16S_LOAD_PMEM, BOX_3X3_16S_LOAD_PMEM_SIZE,
                        BOX_3X3_16S_LOAD_DMEM, BOX_3X3_16S_LOAD_DMEM_SIZE,
                        0, 0); //assuming _LOAD_CMEM does not exist
         FlagSpatialDep();

         //***NOTE: the order in which the following ports are added is meaningful; do not change!

         AddPort("INPUT_0", ICP_DATATYPE_16S, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0x1010101);
         AddPort("OUTPUT_0", ICP_DATATYPE_16S, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1);

         CfgScenarios(&gScenarioList_BOX_3X3_16S);

         FlagAsInitialized();
      }

      lRetVal = SelectApuConfiguration(mApuCfg, mApexId); //by default mApuCfg = ACF_APU_CFG__APEX0_DEFAULT and mApexId = 0

      return lRetVal;
   }
};

#endif //_ACF_PROCESS_APU_BOX_3X3_16S
