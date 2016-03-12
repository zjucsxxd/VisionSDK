#ifndef _ACF_PROCESS_APU_DILATE_3X3_16S
#define _ACF_PROCESS_APU_DILATE_3X3_16S

#include <acf_process_apu.h>
#include <DILATE_3X3_16S_APU_LOAD.h> //APU load associated with this process
#include <stdint.h>


//SCENARIO LIST*************************************************
static acf_scenario_buffer_data gScenarioBufferData0_DILATE_3X3_16S[] = {{2, 1, 4, 0, 0x1111}, {2, 1, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData1_DILATE_3X3_16S[] = {{4, 1, 4, 0, 0x1111}, {4, 1, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData2_DILATE_3X3_16S[] = {{6, 1, 4, 0, 0x1111}, {6, 1, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData3_DILATE_3X3_16S[] = {{8, 1, 4, 0, 0x1111}, {8, 1, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData4_DILATE_3X3_16S[] = {{10, 1, 4, 0, 0x1111}, {10, 1, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData5_DILATE_3X3_16S[] = {{12, 1, 4, 0, 0x1111}, {12, 1, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData6_DILATE_3X3_16S[] = {{14, 1, 4, 0, 0x1111}, {14, 1, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData7_DILATE_3X3_16S[] = {{16, 1, 4, 0, 0x1111}, {16, 1, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData8_DILATE_3X3_16S[] = {{20, 1, 4, 0, 0x1111}, {20, 1, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData9_DILATE_3X3_16S[] = {{24, 1, 4, 0, 0x1111}, {24, 1, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData10_DILATE_3X3_16S[] = {{28, 1, 4, 0, 0x1111}, {28, 1, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData11_DILATE_3X3_16S[] = {{32, 1, 4, 0, 0x1111}, {32, 1, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData12_DILATE_3X3_16S[] = {{36, 1, 4, 0, 0x1111}, {36, 1, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData13_DILATE_3X3_16S[] = {{40, 1, 4, 0, 0x1111}, {40, 1, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData14_DILATE_3X3_16S[] = {{44, 1, 4, 0, 0x1111}, {44, 1, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData15_DILATE_3X3_16S[] = {{48, 1, 4, 0, 0x1111}, {48, 1, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData16_DILATE_3X3_16S[] = {{52, 1, 4, 0, 0x1111}, {52, 1, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData17_DILATE_3X3_16S[] = {{56, 1, 4, 0, 0x1111}, {56, 1, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData18_DILATE_3X3_16S[] = {{60, 1, 4, 0, 0x1111}, {60, 1, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData19_DILATE_3X3_16S[] = {{64, 1, 4, 0, 0x1111}, {64, 1, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData20_DILATE_3X3_16S[] = {{2, 2, 4, 0, 0x1111}, {2, 2, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData21_DILATE_3X3_16S[] = {{4, 2, 4, 0, 0x1111}, {4, 2, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData22_DILATE_3X3_16S[] = {{6, 2, 4, 0, 0x1111}, {6, 2, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData23_DILATE_3X3_16S[] = {{8, 2, 4, 0, 0x1111}, {8, 2, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData24_DILATE_3X3_16S[] = {{10, 2, 4, 0, 0x1111}, {10, 2, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData25_DILATE_3X3_16S[] = {{12, 2, 4, 0, 0x1111}, {12, 2, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData26_DILATE_3X3_16S[] = {{14, 2, 4, 0, 0x1111}, {14, 2, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData27_DILATE_3X3_16S[] = {{16, 2, 4, 0, 0x1111}, {16, 2, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData28_DILATE_3X3_16S[] = {{20, 2, 4, 0, 0x1111}, {20, 2, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData29_DILATE_3X3_16S[] = {{24, 2, 4, 0, 0x1111}, {24, 2, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData30_DILATE_3X3_16S[] = {{28, 2, 4, 0, 0x1111}, {28, 2, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData31_DILATE_3X3_16S[] = {{32, 2, 4, 0, 0x1111}, {32, 2, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData32_DILATE_3X3_16S[] = {{36, 2, 4, 0, 0x1111}, {36, 2, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData33_DILATE_3X3_16S[] = {{40, 2, 4, 0, 0x1111}, {40, 2, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData34_DILATE_3X3_16S[] = {{44, 2, 4, 0, 0x1111}, {44, 2, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData35_DILATE_3X3_16S[] = {{48, 2, 4, 0, 0x1111}, {48, 2, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData36_DILATE_3X3_16S[] = {{52, 2, 4, 0, 0x1111}, {52, 2, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData37_DILATE_3X3_16S[] = {{56, 2, 4, 0, 0x1111}, {56, 2, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData38_DILATE_3X3_16S[] = {{60, 2, 4, 0, 0x1111}, {60, 2, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData39_DILATE_3X3_16S[] = {{64, 2, 4, 0, 0x1111}, {64, 2, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData40_DILATE_3X3_16S[] = {{2, 4, 4, 0, 0x1111}, {2, 4, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData41_DILATE_3X3_16S[] = {{4, 4, 4, 0, 0x1111}, {4, 4, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData42_DILATE_3X3_16S[] = {{6, 4, 4, 0, 0x1111}, {6, 4, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData43_DILATE_3X3_16S[] = {{8, 4, 4, 0, 0x1111}, {8, 4, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData44_DILATE_3X3_16S[] = {{10, 4, 4, 0, 0x1111}, {10, 4, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData45_DILATE_3X3_16S[] = {{12, 4, 4, 0, 0x1111}, {12, 4, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData46_DILATE_3X3_16S[] = {{14, 4, 4, 0, 0x1111}, {14, 4, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData47_DILATE_3X3_16S[] = {{16, 4, 4, 0, 0x1111}, {16, 4, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData48_DILATE_3X3_16S[] = {{20, 4, 4, 0, 0x1111}, {20, 4, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData49_DILATE_3X3_16S[] = {{24, 4, 4, 0, 0x1111}, {24, 4, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData50_DILATE_3X3_16S[] = {{28, 4, 4, 0, 0x1111}, {28, 4, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData51_DILATE_3X3_16S[] = {{32, 4, 4, 0, 0x1111}, {32, 4, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData52_DILATE_3X3_16S[] = {{36, 4, 4, 0, 0x1111}, {36, 4, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData53_DILATE_3X3_16S[] = {{40, 4, 4, 0, 0x1111}, {40, 4, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData54_DILATE_3X3_16S[] = {{44, 4, 4, 0, 0x1111}, {44, 4, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData55_DILATE_3X3_16S[] = {{48, 4, 4, 0, 0x1111}, {48, 4, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData56_DILATE_3X3_16S[] = {{52, 4, 4, 0, 0x1111}, {52, 4, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData57_DILATE_3X3_16S[] = {{56, 4, 4, 0, 0x1111}, {56, 4, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData58_DILATE_3X3_16S[] = {{60, 4, 4, 0, 0x1111}, {60, 4, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData59_DILATE_3X3_16S[] = {{64, 4, 4, 0, 0x1111}, {64, 4, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData60_DILATE_3X3_16S[] = {{2, 6, 4, 0, 0x1111}, {2, 6, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData61_DILATE_3X3_16S[] = {{4, 6, 4, 0, 0x1111}, {4, 6, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData62_DILATE_3X3_16S[] = {{6, 6, 4, 0, 0x1111}, {6, 6, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData63_DILATE_3X3_16S[] = {{8, 6, 4, 0, 0x1111}, {8, 6, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData64_DILATE_3X3_16S[] = {{10, 6, 4, 0, 0x1111}, {10, 6, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData65_DILATE_3X3_16S[] = {{12, 6, 4, 0, 0x1111}, {12, 6, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData66_DILATE_3X3_16S[] = {{14, 6, 4, 0, 0x1111}, {14, 6, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData67_DILATE_3X3_16S[] = {{16, 6, 4, 0, 0x1111}, {16, 6, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData68_DILATE_3X3_16S[] = {{20, 6, 4, 0, 0x1111}, {20, 6, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData69_DILATE_3X3_16S[] = {{24, 6, 4, 0, 0x1111}, {24, 6, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData70_DILATE_3X3_16S[] = {{28, 6, 4, 0, 0x1111}, {28, 6, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData71_DILATE_3X3_16S[] = {{32, 6, 4, 0, 0x1111}, {32, 6, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData72_DILATE_3X3_16S[] = {{36, 6, 4, 0, 0x1111}, {36, 6, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData73_DILATE_3X3_16S[] = {{40, 6, 4, 0, 0x1111}, {40, 6, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData74_DILATE_3X3_16S[] = {{44, 6, 4, 0, 0x1111}, {44, 6, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData75_DILATE_3X3_16S[] = {{48, 6, 4, 0, 0x1111}, {48, 6, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData76_DILATE_3X3_16S[] = {{2, 8, 4, 0, 0x1111}, {2, 8, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData77_DILATE_3X3_16S[] = {{4, 8, 4, 0, 0x1111}, {4, 8, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData78_DILATE_3X3_16S[] = {{6, 8, 4, 0, 0x1111}, {6, 8, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData79_DILATE_3X3_16S[] = {{8, 8, 4, 0, 0x1111}, {8, 8, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData80_DILATE_3X3_16S[] = {{10, 8, 4, 0, 0x1111}, {10, 8, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData81_DILATE_3X3_16S[] = {{12, 8, 4, 0, 0x1111}, {12, 8, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData82_DILATE_3X3_16S[] = {{14, 8, 4, 0, 0x1111}, {14, 8, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData83_DILATE_3X3_16S[] = {{16, 8, 4, 0, 0x1111}, {16, 8, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData84_DILATE_3X3_16S[] = {{20, 8, 4, 0, 0x1111}, {20, 8, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData85_DILATE_3X3_16S[] = {{24, 8, 4, 0, 0x1111}, {24, 8, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData86_DILATE_3X3_16S[] = {{28, 8, 4, 0, 0x1111}, {28, 8, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData87_DILATE_3X3_16S[] = {{32, 8, 4, 0, 0x1111}, {32, 8, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData88_DILATE_3X3_16S[] = {{36, 8, 4, 0, 0x1111}, {36, 8, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData89_DILATE_3X3_16S[] = {{2, 10, 4, 0, 0x1111}, {2, 10, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData90_DILATE_3X3_16S[] = {{4, 10, 4, 0, 0x1111}, {4, 10, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData91_DILATE_3X3_16S[] = {{6, 10, 4, 0, 0x1111}, {6, 10, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData92_DILATE_3X3_16S[] = {{8, 10, 4, 0, 0x1111}, {8, 10, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData93_DILATE_3X3_16S[] = {{10, 10, 4, 0, 0x1111}, {10, 10, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData94_DILATE_3X3_16S[] = {{12, 10, 4, 0, 0x1111}, {12, 10, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData95_DILATE_3X3_16S[] = {{14, 10, 4, 0, 0x1111}, {14, 10, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData96_DILATE_3X3_16S[] = {{16, 10, 4, 0, 0x1111}, {16, 10, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData97_DILATE_3X3_16S[] = {{20, 10, 4, 0, 0x1111}, {20, 10, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData98_DILATE_3X3_16S[] = {{24, 10, 4, 0, 0x1111}, {24, 10, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData99_DILATE_3X3_16S[] = {{28, 10, 4, 0, 0x1111}, {28, 10, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData100_DILATE_3X3_16S[] = {{2, 12, 4, 0, 0x1111}, {2, 12, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData101_DILATE_3X3_16S[] = {{4, 12, 4, 0, 0x1111}, {4, 12, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData102_DILATE_3X3_16S[] = {{6, 12, 4, 0, 0x1111}, {6, 12, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData103_DILATE_3X3_16S[] = {{8, 12, 4, 0, 0x1111}, {8, 12, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData104_DILATE_3X3_16S[] = {{10, 12, 4, 0, 0x1111}, {10, 12, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData105_DILATE_3X3_16S[] = {{12, 12, 4, 0, 0x1111}, {12, 12, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData106_DILATE_3X3_16S[] = {{14, 12, 4, 0, 0x1111}, {14, 12, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData107_DILATE_3X3_16S[] = {{16, 12, 4, 0, 0x1111}, {16, 12, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData108_DILATE_3X3_16S[] = {{20, 12, 4, 0, 0x1111}, {20, 12, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData109_DILATE_3X3_16S[] = {{24, 12, 4, 0, 0x1111}, {24, 12, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData110_DILATE_3X3_16S[] = {{2, 14, 4, 0, 0x1111}, {2, 14, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData111_DILATE_3X3_16S[] = {{4, 14, 4, 0, 0x1111}, {4, 14, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData112_DILATE_3X3_16S[] = {{6, 14, 4, 0, 0x1111}, {6, 14, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData113_DILATE_3X3_16S[] = {{8, 14, 4, 0, 0x1111}, {8, 14, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData114_DILATE_3X3_16S[] = {{10, 14, 4, 0, 0x1111}, {10, 14, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData115_DILATE_3X3_16S[] = {{12, 14, 4, 0, 0x1111}, {12, 14, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData116_DILATE_3X3_16S[] = {{14, 14, 4, 0, 0x1111}, {14, 14, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData117_DILATE_3X3_16S[] = {{16, 14, 4, 0, 0x1111}, {16, 14, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData118_DILATE_3X3_16S[] = {{20, 14, 4, 0, 0x1111}, {20, 14, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData119_DILATE_3X3_16S[] = {{2, 16, 4, 0, 0x1111}, {2, 16, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData120_DILATE_3X3_16S[] = {{4, 16, 4, 0, 0x1111}, {4, 16, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData121_DILATE_3X3_16S[] = {{6, 16, 4, 0, 0x1111}, {6, 16, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData122_DILATE_3X3_16S[] = {{8, 16, 4, 0, 0x1111}, {8, 16, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData123_DILATE_3X3_16S[] = {{10, 16, 4, 0, 0x1111}, {10, 16, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData124_DILATE_3X3_16S[] = {{12, 16, 4, 0, 0x1111}, {12, 16, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData125_DILATE_3X3_16S[] = {{14, 16, 4, 0, 0x1111}, {14, 16, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData126_DILATE_3X3_16S[] = {{16, 16, 4, 0, 0x1111}, {16, 16, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData127_DILATE_3X3_16S[] = {{2, 18, 4, 0, 0x1111}, {2, 18, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData128_DILATE_3X3_16S[] = {{4, 18, 4, 0, 0x1111}, {4, 18, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData129_DILATE_3X3_16S[] = {{6, 18, 4, 0, 0x1111}, {6, 18, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData130_DILATE_3X3_16S[] = {{8, 18, 4, 0, 0x1111}, {8, 18, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData131_DILATE_3X3_16S[] = {{10, 18, 4, 0, 0x1111}, {10, 18, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData132_DILATE_3X3_16S[] = {{12, 18, 4, 0, 0x1111}, {12, 18, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData133_DILATE_3X3_16S[] = {{14, 18, 4, 0, 0x1111}, {14, 18, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData134_DILATE_3X3_16S[] = {{16, 18, 4, 0, 0x1111}, {16, 18, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData135_DILATE_3X3_16S[] = {{2, 20, 4, 0, 0x1111}, {2, 20, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData136_DILATE_3X3_16S[] = {{4, 20, 4, 0, 0x1111}, {4, 20, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData137_DILATE_3X3_16S[] = {{6, 20, 4, 0, 0x1111}, {6, 20, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData138_DILATE_3X3_16S[] = {{8, 20, 4, 0, 0x1111}, {8, 20, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData139_DILATE_3X3_16S[] = {{10, 20, 4, 0, 0x1111}, {10, 20, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData140_DILATE_3X3_16S[] = {{12, 20, 4, 0, 0x1111}, {12, 20, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData141_DILATE_3X3_16S[] = {{14, 20, 4, 0, 0x1111}, {14, 20, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData142_DILATE_3X3_16S[] = {{2, 22, 4, 0, 0x1111}, {2, 22, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData143_DILATE_3X3_16S[] = {{4, 22, 4, 0, 0x1111}, {4, 22, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData144_DILATE_3X3_16S[] = {{6, 22, 4, 0, 0x1111}, {6, 22, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData145_DILATE_3X3_16S[] = {{8, 22, 4, 0, 0x1111}, {8, 22, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData146_DILATE_3X3_16S[] = {{10, 22, 4, 0, 0x1111}, {10, 22, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData147_DILATE_3X3_16S[] = {{12, 22, 4, 0, 0x1111}, {12, 22, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData148_DILATE_3X3_16S[] = {{2, 24, 4, 0, 0x1111}, {2, 24, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData149_DILATE_3X3_16S[] = {{4, 24, 4, 0, 0x1111}, {4, 24, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData150_DILATE_3X3_16S[] = {{6, 24, 4, 0, 0x1111}, {6, 24, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData151_DILATE_3X3_16S[] = {{8, 24, 4, 0, 0x1111}, {8, 24, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData152_DILATE_3X3_16S[] = {{10, 24, 4, 0, 0x1111}, {10, 24, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData153_DILATE_3X3_16S[] = {{2, 26, 4, 0, 0x1111}, {2, 26, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData154_DILATE_3X3_16S[] = {{4, 26, 4, 0, 0x1111}, {4, 26, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData155_DILATE_3X3_16S[] = {{6, 26, 4, 0, 0x1111}, {6, 26, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData156_DILATE_3X3_16S[] = {{8, 26, 4, 0, 0x1111}, {8, 26, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData157_DILATE_3X3_16S[] = {{10, 26, 4, 0, 0x1111}, {10, 26, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData158_DILATE_3X3_16S[] = {{2, 28, 4, 0, 0x1111}, {2, 28, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData159_DILATE_3X3_16S[] = {{4, 28, 4, 0, 0x1111}, {4, 28, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData160_DILATE_3X3_16S[] = {{6, 28, 4, 0, 0x1111}, {6, 28, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData161_DILATE_3X3_16S[] = {{8, 28, 4, 0, 0x1111}, {8, 28, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData162_DILATE_3X3_16S[] = {{2, 30, 4, 0, 0x1111}, {2, 30, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData163_DILATE_3X3_16S[] = {{4, 30, 4, 0, 0x1111}, {4, 30, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData164_DILATE_3X3_16S[] = {{6, 30, 4, 0, 0x1111}, {6, 30, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData165_DILATE_3X3_16S[] = {{8, 30, 4, 0, 0x1111}, {8, 30, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData166_DILATE_3X3_16S[] = {{2, 32, 4, 0, 0x1111}, {2, 32, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData167_DILATE_3X3_16S[] = {{4, 32, 4, 0, 0x1111}, {4, 32, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData168_DILATE_3X3_16S[] = {{6, 32, 4, 0, 0x1111}, {6, 32, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData169_DILATE_3X3_16S[] = {{8, 32, 4, 0, 0x1111}, {8, 32, 2, 1, 0x0}};

static acf_scenario_kernel_data gScenarioKernelData0_DILATE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData1_DILATE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData2_DILATE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData3_DILATE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData4_DILATE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData5_DILATE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData6_DILATE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData7_DILATE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData8_DILATE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData9_DILATE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData10_DILATE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData11_DILATE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData12_DILATE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData13_DILATE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData14_DILATE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData15_DILATE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData16_DILATE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData17_DILATE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData18_DILATE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData19_DILATE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData20_DILATE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData21_DILATE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData22_DILATE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData23_DILATE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData24_DILATE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData25_DILATE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData26_DILATE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData27_DILATE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData28_DILATE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData29_DILATE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData30_DILATE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData31_DILATE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData32_DILATE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData33_DILATE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData34_DILATE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData35_DILATE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData36_DILATE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData37_DILATE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData38_DILATE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData39_DILATE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData40_DILATE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData41_DILATE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData42_DILATE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData43_DILATE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData44_DILATE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData45_DILATE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData46_DILATE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData47_DILATE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData48_DILATE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData49_DILATE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData50_DILATE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData51_DILATE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData52_DILATE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData53_DILATE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData54_DILATE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData55_DILATE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData56_DILATE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData57_DILATE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData58_DILATE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData59_DILATE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData60_DILATE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData61_DILATE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData62_DILATE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData63_DILATE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData64_DILATE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData65_DILATE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData66_DILATE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData67_DILATE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData68_DILATE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData69_DILATE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData70_DILATE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData71_DILATE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData72_DILATE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData73_DILATE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData74_DILATE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData75_DILATE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData76_DILATE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData77_DILATE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData78_DILATE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData79_DILATE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData80_DILATE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData81_DILATE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData82_DILATE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData83_DILATE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData84_DILATE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData85_DILATE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData86_DILATE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData87_DILATE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData88_DILATE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData89_DILATE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData90_DILATE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData91_DILATE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData92_DILATE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData93_DILATE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData94_DILATE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData95_DILATE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData96_DILATE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData97_DILATE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData98_DILATE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData99_DILATE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData100_DILATE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData101_DILATE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData102_DILATE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData103_DILATE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData104_DILATE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData105_DILATE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData106_DILATE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData107_DILATE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData108_DILATE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData109_DILATE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData110_DILATE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData111_DILATE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData112_DILATE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData113_DILATE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData114_DILATE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData115_DILATE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData116_DILATE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData117_DILATE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData118_DILATE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData119_DILATE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData120_DILATE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData121_DILATE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData122_DILATE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData123_DILATE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData124_DILATE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData125_DILATE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData126_DILATE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData127_DILATE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData128_DILATE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData129_DILATE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData130_DILATE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData131_DILATE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData132_DILATE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData133_DILATE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData134_DILATE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData135_DILATE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData136_DILATE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData137_DILATE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData138_DILATE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData139_DILATE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData140_DILATE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData141_DILATE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData142_DILATE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData143_DILATE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData144_DILATE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData145_DILATE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData146_DILATE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData147_DILATE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData148_DILATE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData149_DILATE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData150_DILATE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData151_DILATE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData152_DILATE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData153_DILATE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData154_DILATE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData155_DILATE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData156_DILATE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData157_DILATE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData158_DILATE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData159_DILATE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData160_DILATE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData161_DILATE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData162_DILATE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData163_DILATE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData164_DILATE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData165_DILATE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData166_DILATE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData167_DILATE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData168_DILATE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData169_DILATE_3X3_16S[] = {{1}};

static acf_scenario gScenarioArray_DILATE_3X3_16S[] = {
{1, 1, 56, 0, 1, gScenarioBufferData0_DILATE_3X3_16S, 20, gScenarioKernelData0_DILATE_3X3_16S, 2},
{2, 1, 88, 0, 1, gScenarioBufferData1_DILATE_3X3_16S, 20, gScenarioKernelData1_DILATE_3X3_16S, 2},
{3, 1, 120, 0, 1, gScenarioBufferData2_DILATE_3X3_16S, 20, gScenarioKernelData2_DILATE_3X3_16S, 2},
{4, 1, 152, 0, 1, gScenarioBufferData3_DILATE_3X3_16S, 20, gScenarioKernelData3_DILATE_3X3_16S, 2},
{5, 1, 184, 0, 1, gScenarioBufferData4_DILATE_3X3_16S, 20, gScenarioKernelData4_DILATE_3X3_16S, 2},
{6, 1, 216, 0, 1, gScenarioBufferData5_DILATE_3X3_16S, 20, gScenarioKernelData5_DILATE_3X3_16S, 2},
{7, 1, 248, 0, 1, gScenarioBufferData6_DILATE_3X3_16S, 20, gScenarioKernelData6_DILATE_3X3_16S, 2},
{8, 1, 280, 0, 1, gScenarioBufferData7_DILATE_3X3_16S, 20, gScenarioKernelData7_DILATE_3X3_16S, 2},
{10, 1, 344, 0, 1, gScenarioBufferData8_DILATE_3X3_16S, 20, gScenarioKernelData8_DILATE_3X3_16S, 2},
{12, 1, 408, 0, 1, gScenarioBufferData9_DILATE_3X3_16S, 20, gScenarioKernelData9_DILATE_3X3_16S, 2},
{14, 1, 472, 0, 1, gScenarioBufferData10_DILATE_3X3_16S, 20, gScenarioKernelData10_DILATE_3X3_16S, 2},
{16, 1, 536, 0, 1, gScenarioBufferData11_DILATE_3X3_16S, 20, gScenarioKernelData11_DILATE_3X3_16S, 2},
{18, 1, 600, 0, 1, gScenarioBufferData12_DILATE_3X3_16S, 20, gScenarioKernelData12_DILATE_3X3_16S, 2},
{20, 1, 664, 0, 1, gScenarioBufferData13_DILATE_3X3_16S, 20, gScenarioKernelData13_DILATE_3X3_16S, 2},
{22, 1, 728, 0, 1, gScenarioBufferData14_DILATE_3X3_16S, 20, gScenarioKernelData14_DILATE_3X3_16S, 2},
{24, 1, 792, 0, 1, gScenarioBufferData15_DILATE_3X3_16S, 20, gScenarioKernelData15_DILATE_3X3_16S, 2},
{26, 1, 856, 0, 1, gScenarioBufferData16_DILATE_3X3_16S, 20, gScenarioKernelData16_DILATE_3X3_16S, 2},
{28, 1, 920, 0, 1, gScenarioBufferData17_DILATE_3X3_16S, 20, gScenarioKernelData17_DILATE_3X3_16S, 2},
{30, 1, 984, 0, 1, gScenarioBufferData18_DILATE_3X3_16S, 20, gScenarioKernelData18_DILATE_3X3_16S, 2},
{32, 1, 1048, 0, 1, gScenarioBufferData19_DILATE_3X3_16S, 20, gScenarioKernelData19_DILATE_3X3_16S, 2},
{1, 2, 96, 0, 1, gScenarioBufferData20_DILATE_3X3_16S, 20, gScenarioKernelData20_DILATE_3X3_16S, 2},
{2, 2, 152, 0, 1, gScenarioBufferData21_DILATE_3X3_16S, 20, gScenarioKernelData21_DILATE_3X3_16S, 2},
{3, 2, 208, 0, 1, gScenarioBufferData22_DILATE_3X3_16S, 20, gScenarioKernelData22_DILATE_3X3_16S, 2},
{4, 2, 264, 0, 1, gScenarioBufferData23_DILATE_3X3_16S, 20, gScenarioKernelData23_DILATE_3X3_16S, 2},
{5, 2, 320, 0, 1, gScenarioBufferData24_DILATE_3X3_16S, 20, gScenarioKernelData24_DILATE_3X3_16S, 2},
{6, 2, 376, 0, 1, gScenarioBufferData25_DILATE_3X3_16S, 20, gScenarioKernelData25_DILATE_3X3_16S, 2},
{7, 2, 432, 0, 1, gScenarioBufferData26_DILATE_3X3_16S, 20, gScenarioKernelData26_DILATE_3X3_16S, 2},
{8, 2, 488, 0, 1, gScenarioBufferData27_DILATE_3X3_16S, 20, gScenarioKernelData27_DILATE_3X3_16S, 2},
{10, 2, 600, 0, 1, gScenarioBufferData28_DILATE_3X3_16S, 20, gScenarioKernelData28_DILATE_3X3_16S, 2},
{12, 2, 712, 0, 1, gScenarioBufferData29_DILATE_3X3_16S, 20, gScenarioKernelData29_DILATE_3X3_16S, 2},
{14, 2, 824, 0, 1, gScenarioBufferData30_DILATE_3X3_16S, 20, gScenarioKernelData30_DILATE_3X3_16S, 2},
{16, 2, 936, 0, 1, gScenarioBufferData31_DILATE_3X3_16S, 20, gScenarioKernelData31_DILATE_3X3_16S, 2},
{18, 2, 1048, 0, 1, gScenarioBufferData32_DILATE_3X3_16S, 20, gScenarioKernelData32_DILATE_3X3_16S, 2},
{20, 2, 1160, 0, 1, gScenarioBufferData33_DILATE_3X3_16S, 20, gScenarioKernelData33_DILATE_3X3_16S, 2},
{22, 2, 1272, 0, 1, gScenarioBufferData34_DILATE_3X3_16S, 20, gScenarioKernelData34_DILATE_3X3_16S, 2},
{24, 2, 1384, 0, 1, gScenarioBufferData35_DILATE_3X3_16S, 20, gScenarioKernelData35_DILATE_3X3_16S, 2},
{26, 2, 1496, 0, 1, gScenarioBufferData36_DILATE_3X3_16S, 20, gScenarioKernelData36_DILATE_3X3_16S, 2},
{28, 2, 1608, 0, 1, gScenarioBufferData37_DILATE_3X3_16S, 20, gScenarioKernelData37_DILATE_3X3_16S, 2},
{30, 2, 1720, 0, 1, gScenarioBufferData38_DILATE_3X3_16S, 20, gScenarioKernelData38_DILATE_3X3_16S, 2},
{32, 2, 1832, 0, 1, gScenarioBufferData39_DILATE_3X3_16S, 20, gScenarioKernelData39_DILATE_3X3_16S, 2},
{1, 4, 176, 0, 1, gScenarioBufferData40_DILATE_3X3_16S, 20, gScenarioKernelData40_DILATE_3X3_16S, 2},
{2, 4, 280, 0, 1, gScenarioBufferData41_DILATE_3X3_16S, 20, gScenarioKernelData41_DILATE_3X3_16S, 2},
{3, 4, 384, 0, 1, gScenarioBufferData42_DILATE_3X3_16S, 20, gScenarioKernelData42_DILATE_3X3_16S, 2},
{4, 4, 488, 0, 1, gScenarioBufferData43_DILATE_3X3_16S, 20, gScenarioKernelData43_DILATE_3X3_16S, 2},
{5, 4, 592, 0, 1, gScenarioBufferData44_DILATE_3X3_16S, 20, gScenarioKernelData44_DILATE_3X3_16S, 2},
{6, 4, 696, 0, 1, gScenarioBufferData45_DILATE_3X3_16S, 20, gScenarioKernelData45_DILATE_3X3_16S, 2},
{7, 4, 800, 0, 1, gScenarioBufferData46_DILATE_3X3_16S, 20, gScenarioKernelData46_DILATE_3X3_16S, 2},
{8, 4, 904, 0, 1, gScenarioBufferData47_DILATE_3X3_16S, 20, gScenarioKernelData47_DILATE_3X3_16S, 2},
{10, 4, 1112, 0, 1, gScenarioBufferData48_DILATE_3X3_16S, 20, gScenarioKernelData48_DILATE_3X3_16S, 2},
{12, 4, 1320, 0, 1, gScenarioBufferData49_DILATE_3X3_16S, 20, gScenarioKernelData49_DILATE_3X3_16S, 2},
{14, 4, 1528, 0, 1, gScenarioBufferData50_DILATE_3X3_16S, 20, gScenarioKernelData50_DILATE_3X3_16S, 2},
{16, 4, 1736, 0, 1, gScenarioBufferData51_DILATE_3X3_16S, 20, gScenarioKernelData51_DILATE_3X3_16S, 2},
{18, 4, 1944, 0, 1, gScenarioBufferData52_DILATE_3X3_16S, 20, gScenarioKernelData52_DILATE_3X3_16S, 2},
{20, 4, 2152, 0, 1, gScenarioBufferData53_DILATE_3X3_16S, 20, gScenarioKernelData53_DILATE_3X3_16S, 2},
{22, 4, 2360, 0, 1, gScenarioBufferData54_DILATE_3X3_16S, 20, gScenarioKernelData54_DILATE_3X3_16S, 2},
{24, 4, 2568, 0, 1, gScenarioBufferData55_DILATE_3X3_16S, 20, gScenarioKernelData55_DILATE_3X3_16S, 2},
{26, 4, 2776, 0, 1, gScenarioBufferData56_DILATE_3X3_16S, 20, gScenarioKernelData56_DILATE_3X3_16S, 2},
{28, 4, 2984, 0, 1, gScenarioBufferData57_DILATE_3X3_16S, 20, gScenarioKernelData57_DILATE_3X3_16S, 2},
{30, 4, 3192, 0, 1, gScenarioBufferData58_DILATE_3X3_16S, 20, gScenarioKernelData58_DILATE_3X3_16S, 2},
{32, 4, 3400, 0, 1, gScenarioBufferData59_DILATE_3X3_16S, 20, gScenarioKernelData59_DILATE_3X3_16S, 2},
{1, 6, 256, 0, 1, gScenarioBufferData60_DILATE_3X3_16S, 20, gScenarioKernelData60_DILATE_3X3_16S, 2},
{2, 6, 408, 0, 1, gScenarioBufferData61_DILATE_3X3_16S, 20, gScenarioKernelData61_DILATE_3X3_16S, 2},
{3, 6, 560, 0, 1, gScenarioBufferData62_DILATE_3X3_16S, 20, gScenarioKernelData62_DILATE_3X3_16S, 2},
{4, 6, 712, 0, 1, gScenarioBufferData63_DILATE_3X3_16S, 20, gScenarioKernelData63_DILATE_3X3_16S, 2},
{5, 6, 864, 0, 1, gScenarioBufferData64_DILATE_3X3_16S, 20, gScenarioKernelData64_DILATE_3X3_16S, 2},
{6, 6, 1016, 0, 1, gScenarioBufferData65_DILATE_3X3_16S, 20, gScenarioKernelData65_DILATE_3X3_16S, 2},
{7, 6, 1168, 0, 1, gScenarioBufferData66_DILATE_3X3_16S, 20, gScenarioKernelData66_DILATE_3X3_16S, 2},
{8, 6, 1320, 0, 1, gScenarioBufferData67_DILATE_3X3_16S, 20, gScenarioKernelData67_DILATE_3X3_16S, 2},
{10, 6, 1624, 0, 1, gScenarioBufferData68_DILATE_3X3_16S, 20, gScenarioKernelData68_DILATE_3X3_16S, 2},
{12, 6, 1928, 0, 1, gScenarioBufferData69_DILATE_3X3_16S, 20, gScenarioKernelData69_DILATE_3X3_16S, 2},
{14, 6, 2232, 0, 1, gScenarioBufferData70_DILATE_3X3_16S, 20, gScenarioKernelData70_DILATE_3X3_16S, 2},
{16, 6, 2536, 0, 1, gScenarioBufferData71_DILATE_3X3_16S, 20, gScenarioKernelData71_DILATE_3X3_16S, 2},
{18, 6, 2840, 0, 1, gScenarioBufferData72_DILATE_3X3_16S, 20, gScenarioKernelData72_DILATE_3X3_16S, 2},
{20, 6, 3144, 0, 1, gScenarioBufferData73_DILATE_3X3_16S, 20, gScenarioKernelData73_DILATE_3X3_16S, 2},
{22, 6, 3448, 0, 1, gScenarioBufferData74_DILATE_3X3_16S, 20, gScenarioKernelData74_DILATE_3X3_16S, 2},
{24, 6, 3752, 0, 1, gScenarioBufferData75_DILATE_3X3_16S, 20, gScenarioKernelData75_DILATE_3X3_16S, 2},
{1, 8, 336, 0, 1, gScenarioBufferData76_DILATE_3X3_16S, 20, gScenarioKernelData76_DILATE_3X3_16S, 2},
{2, 8, 536, 0, 1, gScenarioBufferData77_DILATE_3X3_16S, 20, gScenarioKernelData77_DILATE_3X3_16S, 2},
{3, 8, 736, 0, 1, gScenarioBufferData78_DILATE_3X3_16S, 20, gScenarioKernelData78_DILATE_3X3_16S, 2},
{4, 8, 936, 0, 1, gScenarioBufferData79_DILATE_3X3_16S, 20, gScenarioKernelData79_DILATE_3X3_16S, 2},
{5, 8, 1136, 0, 1, gScenarioBufferData80_DILATE_3X3_16S, 20, gScenarioKernelData80_DILATE_3X3_16S, 2},
{6, 8, 1336, 0, 1, gScenarioBufferData81_DILATE_3X3_16S, 20, gScenarioKernelData81_DILATE_3X3_16S, 2},
{7, 8, 1536, 0, 1, gScenarioBufferData82_DILATE_3X3_16S, 20, gScenarioKernelData82_DILATE_3X3_16S, 2},
{8, 8, 1736, 0, 1, gScenarioBufferData83_DILATE_3X3_16S, 20, gScenarioKernelData83_DILATE_3X3_16S, 2},
{10, 8, 2136, 0, 1, gScenarioBufferData84_DILATE_3X3_16S, 20, gScenarioKernelData84_DILATE_3X3_16S, 2},
{12, 8, 2536, 0, 1, gScenarioBufferData85_DILATE_3X3_16S, 20, gScenarioKernelData85_DILATE_3X3_16S, 2},
{14, 8, 2936, 0, 1, gScenarioBufferData86_DILATE_3X3_16S, 20, gScenarioKernelData86_DILATE_3X3_16S, 2},
{16, 8, 3336, 0, 1, gScenarioBufferData87_DILATE_3X3_16S, 20, gScenarioKernelData87_DILATE_3X3_16S, 2},
{18, 8, 3736, 0, 1, gScenarioBufferData88_DILATE_3X3_16S, 20, gScenarioKernelData88_DILATE_3X3_16S, 2},
{1, 10, 416, 0, 1, gScenarioBufferData89_DILATE_3X3_16S, 20, gScenarioKernelData89_DILATE_3X3_16S, 2},
{2, 10, 664, 0, 1, gScenarioBufferData90_DILATE_3X3_16S, 20, gScenarioKernelData90_DILATE_3X3_16S, 2},
{3, 10, 912, 0, 1, gScenarioBufferData91_DILATE_3X3_16S, 20, gScenarioKernelData91_DILATE_3X3_16S, 2},
{4, 10, 1160, 0, 1, gScenarioBufferData92_DILATE_3X3_16S, 20, gScenarioKernelData92_DILATE_3X3_16S, 2},
{5, 10, 1408, 0, 1, gScenarioBufferData93_DILATE_3X3_16S, 20, gScenarioKernelData93_DILATE_3X3_16S, 2},
{6, 10, 1656, 0, 1, gScenarioBufferData94_DILATE_3X3_16S, 20, gScenarioKernelData94_DILATE_3X3_16S, 2},
{7, 10, 1904, 0, 1, gScenarioBufferData95_DILATE_3X3_16S, 20, gScenarioKernelData95_DILATE_3X3_16S, 2},
{8, 10, 2152, 0, 1, gScenarioBufferData96_DILATE_3X3_16S, 20, gScenarioKernelData96_DILATE_3X3_16S, 2},
{10, 10, 2648, 0, 1, gScenarioBufferData97_DILATE_3X3_16S, 20, gScenarioKernelData97_DILATE_3X3_16S, 2},
{12, 10, 3144, 0, 1, gScenarioBufferData98_DILATE_3X3_16S, 20, gScenarioKernelData98_DILATE_3X3_16S, 2},
{14, 10, 3640, 0, 1, gScenarioBufferData99_DILATE_3X3_16S, 20, gScenarioKernelData99_DILATE_3X3_16S, 2},
{1, 12, 496, 0, 1, gScenarioBufferData100_DILATE_3X3_16S, 20, gScenarioKernelData100_DILATE_3X3_16S, 2},
{2, 12, 792, 0, 1, gScenarioBufferData101_DILATE_3X3_16S, 20, gScenarioKernelData101_DILATE_3X3_16S, 2},
{3, 12, 1088, 0, 1, gScenarioBufferData102_DILATE_3X3_16S, 20, gScenarioKernelData102_DILATE_3X3_16S, 2},
{4, 12, 1384, 0, 1, gScenarioBufferData103_DILATE_3X3_16S, 20, gScenarioKernelData103_DILATE_3X3_16S, 2},
{5, 12, 1680, 0, 1, gScenarioBufferData104_DILATE_3X3_16S, 20, gScenarioKernelData104_DILATE_3X3_16S, 2},
{6, 12, 1976, 0, 1, gScenarioBufferData105_DILATE_3X3_16S, 20, gScenarioKernelData105_DILATE_3X3_16S, 2},
{7, 12, 2272, 0, 1, gScenarioBufferData106_DILATE_3X3_16S, 20, gScenarioKernelData106_DILATE_3X3_16S, 2},
{8, 12, 2568, 0, 1, gScenarioBufferData107_DILATE_3X3_16S, 20, gScenarioKernelData107_DILATE_3X3_16S, 2},
{10, 12, 3160, 0, 1, gScenarioBufferData108_DILATE_3X3_16S, 20, gScenarioKernelData108_DILATE_3X3_16S, 2},
{12, 12, 3752, 0, 1, gScenarioBufferData109_DILATE_3X3_16S, 20, gScenarioKernelData109_DILATE_3X3_16S, 2},
{1, 14, 576, 0, 1, gScenarioBufferData110_DILATE_3X3_16S, 20, gScenarioKernelData110_DILATE_3X3_16S, 2},
{2, 14, 920, 0, 1, gScenarioBufferData111_DILATE_3X3_16S, 20, gScenarioKernelData111_DILATE_3X3_16S, 2},
{3, 14, 1264, 0, 1, gScenarioBufferData112_DILATE_3X3_16S, 20, gScenarioKernelData112_DILATE_3X3_16S, 2},
{4, 14, 1608, 0, 1, gScenarioBufferData113_DILATE_3X3_16S, 20, gScenarioKernelData113_DILATE_3X3_16S, 2},
{5, 14, 1952, 0, 1, gScenarioBufferData114_DILATE_3X3_16S, 20, gScenarioKernelData114_DILATE_3X3_16S, 2},
{6, 14, 2296, 0, 1, gScenarioBufferData115_DILATE_3X3_16S, 20, gScenarioKernelData115_DILATE_3X3_16S, 2},
{7, 14, 2640, 0, 1, gScenarioBufferData116_DILATE_3X3_16S, 20, gScenarioKernelData116_DILATE_3X3_16S, 2},
{8, 14, 2984, 0, 1, gScenarioBufferData117_DILATE_3X3_16S, 20, gScenarioKernelData117_DILATE_3X3_16S, 2},
{10, 14, 3672, 0, 1, gScenarioBufferData118_DILATE_3X3_16S, 20, gScenarioKernelData118_DILATE_3X3_16S, 2},
{1, 16, 656, 0, 1, gScenarioBufferData119_DILATE_3X3_16S, 20, gScenarioKernelData119_DILATE_3X3_16S, 2},
{2, 16, 1048, 0, 1, gScenarioBufferData120_DILATE_3X3_16S, 20, gScenarioKernelData120_DILATE_3X3_16S, 2},
{3, 16, 1440, 0, 1, gScenarioBufferData121_DILATE_3X3_16S, 20, gScenarioKernelData121_DILATE_3X3_16S, 2},
{4, 16, 1832, 0, 1, gScenarioBufferData122_DILATE_3X3_16S, 20, gScenarioKernelData122_DILATE_3X3_16S, 2},
{5, 16, 2224, 0, 1, gScenarioBufferData123_DILATE_3X3_16S, 20, gScenarioKernelData123_DILATE_3X3_16S, 2},
{6, 16, 2616, 0, 1, gScenarioBufferData124_DILATE_3X3_16S, 20, gScenarioKernelData124_DILATE_3X3_16S, 2},
{7, 16, 3008, 0, 1, gScenarioBufferData125_DILATE_3X3_16S, 20, gScenarioKernelData125_DILATE_3X3_16S, 2},
{8, 16, 3400, 0, 1, gScenarioBufferData126_DILATE_3X3_16S, 20, gScenarioKernelData126_DILATE_3X3_16S, 2},
{1, 18, 736, 0, 1, gScenarioBufferData127_DILATE_3X3_16S, 20, gScenarioKernelData127_DILATE_3X3_16S, 2},
{2, 18, 1176, 0, 1, gScenarioBufferData128_DILATE_3X3_16S, 20, gScenarioKernelData128_DILATE_3X3_16S, 2},
{3, 18, 1616, 0, 1, gScenarioBufferData129_DILATE_3X3_16S, 20, gScenarioKernelData129_DILATE_3X3_16S, 2},
{4, 18, 2056, 0, 1, gScenarioBufferData130_DILATE_3X3_16S, 20, gScenarioKernelData130_DILATE_3X3_16S, 2},
{5, 18, 2496, 0, 1, gScenarioBufferData131_DILATE_3X3_16S, 20, gScenarioKernelData131_DILATE_3X3_16S, 2},
{6, 18, 2936, 0, 1, gScenarioBufferData132_DILATE_3X3_16S, 20, gScenarioKernelData132_DILATE_3X3_16S, 2},
{7, 18, 3376, 0, 1, gScenarioBufferData133_DILATE_3X3_16S, 20, gScenarioKernelData133_DILATE_3X3_16S, 2},
{8, 18, 3816, 0, 1, gScenarioBufferData134_DILATE_3X3_16S, 20, gScenarioKernelData134_DILATE_3X3_16S, 2},
{1, 20, 816, 0, 1, gScenarioBufferData135_DILATE_3X3_16S, 20, gScenarioKernelData135_DILATE_3X3_16S, 2},
{2, 20, 1304, 0, 1, gScenarioBufferData136_DILATE_3X3_16S, 20, gScenarioKernelData136_DILATE_3X3_16S, 2},
{3, 20, 1792, 0, 1, gScenarioBufferData137_DILATE_3X3_16S, 20, gScenarioKernelData137_DILATE_3X3_16S, 2},
{4, 20, 2280, 0, 1, gScenarioBufferData138_DILATE_3X3_16S, 20, gScenarioKernelData138_DILATE_3X3_16S, 2},
{5, 20, 2768, 0, 1, gScenarioBufferData139_DILATE_3X3_16S, 20, gScenarioKernelData139_DILATE_3X3_16S, 2},
{6, 20, 3256, 0, 1, gScenarioBufferData140_DILATE_3X3_16S, 20, gScenarioKernelData140_DILATE_3X3_16S, 2},
{7, 20, 3744, 0, 1, gScenarioBufferData141_DILATE_3X3_16S, 20, gScenarioKernelData141_DILATE_3X3_16S, 2},
{1, 22, 896, 0, 1, gScenarioBufferData142_DILATE_3X3_16S, 20, gScenarioKernelData142_DILATE_3X3_16S, 2},
{2, 22, 1432, 0, 1, gScenarioBufferData143_DILATE_3X3_16S, 20, gScenarioKernelData143_DILATE_3X3_16S, 2},
{3, 22, 1968, 0, 1, gScenarioBufferData144_DILATE_3X3_16S, 20, gScenarioKernelData144_DILATE_3X3_16S, 2},
{4, 22, 2504, 0, 1, gScenarioBufferData145_DILATE_3X3_16S, 20, gScenarioKernelData145_DILATE_3X3_16S, 2},
{5, 22, 3040, 0, 1, gScenarioBufferData146_DILATE_3X3_16S, 20, gScenarioKernelData146_DILATE_3X3_16S, 2},
{6, 22, 3576, 0, 1, gScenarioBufferData147_DILATE_3X3_16S, 20, gScenarioKernelData147_DILATE_3X3_16S, 2},
{1, 24, 976, 0, 1, gScenarioBufferData148_DILATE_3X3_16S, 20, gScenarioKernelData148_DILATE_3X3_16S, 2},
{2, 24, 1560, 0, 1, gScenarioBufferData149_DILATE_3X3_16S, 20, gScenarioKernelData149_DILATE_3X3_16S, 2},
{3, 24, 2144, 0, 1, gScenarioBufferData150_DILATE_3X3_16S, 20, gScenarioKernelData150_DILATE_3X3_16S, 2},
{4, 24, 2728, 0, 1, gScenarioBufferData151_DILATE_3X3_16S, 20, gScenarioKernelData151_DILATE_3X3_16S, 2},
{5, 24, 3312, 0, 1, gScenarioBufferData152_DILATE_3X3_16S, 20, gScenarioKernelData152_DILATE_3X3_16S, 2},
{1, 26, 1056, 0, 1, gScenarioBufferData153_DILATE_3X3_16S, 20, gScenarioKernelData153_DILATE_3X3_16S, 2},
{2, 26, 1688, 0, 1, gScenarioBufferData154_DILATE_3X3_16S, 20, gScenarioKernelData154_DILATE_3X3_16S, 2},
{3, 26, 2320, 0, 1, gScenarioBufferData155_DILATE_3X3_16S, 20, gScenarioKernelData155_DILATE_3X3_16S, 2},
{4, 26, 2952, 0, 1, gScenarioBufferData156_DILATE_3X3_16S, 20, gScenarioKernelData156_DILATE_3X3_16S, 2},
{5, 26, 3584, 0, 1, gScenarioBufferData157_DILATE_3X3_16S, 20, gScenarioKernelData157_DILATE_3X3_16S, 2},
{1, 28, 1136, 0, 1, gScenarioBufferData158_DILATE_3X3_16S, 20, gScenarioKernelData158_DILATE_3X3_16S, 2},
{2, 28, 1816, 0, 1, gScenarioBufferData159_DILATE_3X3_16S, 20, gScenarioKernelData159_DILATE_3X3_16S, 2},
{3, 28, 2496, 0, 1, gScenarioBufferData160_DILATE_3X3_16S, 20, gScenarioKernelData160_DILATE_3X3_16S, 2},
{4, 28, 3176, 0, 1, gScenarioBufferData161_DILATE_3X3_16S, 20, gScenarioKernelData161_DILATE_3X3_16S, 2},
{1, 30, 1216, 0, 1, gScenarioBufferData162_DILATE_3X3_16S, 20, gScenarioKernelData162_DILATE_3X3_16S, 2},
{2, 30, 1944, 0, 1, gScenarioBufferData163_DILATE_3X3_16S, 20, gScenarioKernelData163_DILATE_3X3_16S, 2},
{3, 30, 2672, 0, 1, gScenarioBufferData164_DILATE_3X3_16S, 20, gScenarioKernelData164_DILATE_3X3_16S, 2},
{4, 30, 3400, 0, 1, gScenarioBufferData165_DILATE_3X3_16S, 20, gScenarioKernelData165_DILATE_3X3_16S, 2},
{1, 32, 1296, 0, 1, gScenarioBufferData166_DILATE_3X3_16S, 20, gScenarioKernelData166_DILATE_3X3_16S, 2},
{2, 32, 2072, 0, 1, gScenarioBufferData167_DILATE_3X3_16S, 20, gScenarioKernelData167_DILATE_3X3_16S, 2},
{3, 32, 2848, 0, 1, gScenarioBufferData168_DILATE_3X3_16S, 20, gScenarioKernelData168_DILATE_3X3_16S, 2},
{4, 32, 3624, 0, 1, gScenarioBufferData169_DILATE_3X3_16S, 20, gScenarioKernelData169_DILATE_3X3_16S, 2}
};

static acf_scenario_list gScenarioList_DILATE_3X3_16S = {
170, //number of scenarios
gScenarioArray_DILATE_3X3_16S};
//**************************************************************

class DILATE_3X3_16S : public ACF_Process_APU
{
public:
   DILATE_3X3_16S(int32_t apex_id = 0) : ACF_Process_APU(apex_id)
   {} 

   int32_t Initialize()
   {
      int32_t lRetVal = 0;

      if (!Initialized()) //initialization steps that only need to occur once
      {
         SetProcessIdentifier("DILATE_3X3_16S");
         SetApuLoadInfo(DILATE_3X3_16S_LOAD_SEGMENTS,
                        DILATE_3X3_16S_LOAD_PMEM, DILATE_3X3_16S_LOAD_PMEM_SIZE,
                        DILATE_3X3_16S_LOAD_DMEM, DILATE_3X3_16S_LOAD_DMEM_SIZE,
                        0, 0); //assuming _LOAD_CMEM does not exist
         FlagSpatialDep();

         //***NOTE: the order in which the following ports are added is meaningful; do not change!

         AddPort("INPUT_0", ICP_DATATYPE_16S, 1, 1, 2, 1, 0, 0, 0, 0, 0, 0, 0, 0x1010101);
         AddPort("OUTPUT_0", ICP_DATATYPE_16S, 1, 1, 2, 1, 1, 0, 0, 0, 0, 0, 1);

         CfgScenarios(&gScenarioList_DILATE_3X3_16S);

         FlagAsInitialized();
      }

      lRetVal = SelectApuConfiguration(mApuCfg, mApexId); //by default mApuCfg = ACF_APU_CFG__APEX0_DEFAULT and mApexId = 0

      return lRetVal;
   }
};

#endif //_ACF_PROCESS_APU_DILATE_3X3_16S
