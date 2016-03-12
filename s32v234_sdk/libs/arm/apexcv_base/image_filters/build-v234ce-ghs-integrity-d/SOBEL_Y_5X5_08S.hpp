#ifndef _ACF_PROCESS_APU_SOBEL_Y_5X5_08S
#define _ACF_PROCESS_APU_SOBEL_Y_5X5_08S

#include <acf_process_apu.h>
#include <SOBEL_Y_5X5_08S_APU_LOAD.h> //APU load associated with this process
#include <stdint.h>


//SCENARIO LIST*************************************************
static acf_scenario_buffer_data gScenarioBufferData0_SOBEL_Y_5X5_08S[] = {{2, 1, 7, 0, 0x2222}, {2, 1, 2, 2, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData1_SOBEL_Y_5X5_08S[] = {{4, 1, 7, 0, 0x2222}, {4, 1, 2, 2, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData2_SOBEL_Y_5X5_08S[] = {{6, 1, 7, 0, 0x2222}, {6, 1, 2, 2, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData3_SOBEL_Y_5X5_08S[] = {{8, 1, 7, 0, 0x2222}, {8, 1, 2, 2, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData4_SOBEL_Y_5X5_08S[] = {{10, 1, 7, 0, 0x2222}, {10, 1, 2, 2, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData5_SOBEL_Y_5X5_08S[] = {{12, 1, 7, 0, 0x2222}, {12, 1, 2, 2, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData6_SOBEL_Y_5X5_08S[] = {{14, 1, 7, 0, 0x2222}, {14, 1, 2, 2, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData7_SOBEL_Y_5X5_08S[] = {{16, 1, 7, 0, 0x2222}, {16, 1, 2, 2, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData8_SOBEL_Y_5X5_08S[] = {{18, 1, 7, 0, 0x2222}, {18, 1, 2, 2, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData9_SOBEL_Y_5X5_08S[] = {{20, 1, 7, 0, 0x2222}, {20, 1, 2, 2, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData10_SOBEL_Y_5X5_08S[] = {{22, 1, 7, 0, 0x2222}, {22, 1, 2, 2, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData11_SOBEL_Y_5X5_08S[] = {{24, 1, 7, 0, 0x2222}, {24, 1, 2, 2, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData12_SOBEL_Y_5X5_08S[] = {{26, 1, 7, 0, 0x2222}, {26, 1, 2, 2, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData13_SOBEL_Y_5X5_08S[] = {{28, 1, 7, 0, 0x2222}, {28, 1, 2, 2, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData14_SOBEL_Y_5X5_08S[] = {{30, 1, 7, 0, 0x2222}, {30, 1, 2, 2, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData15_SOBEL_Y_5X5_08S[] = {{32, 1, 7, 0, 0x2222}, {32, 1, 2, 2, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData16_SOBEL_Y_5X5_08S[] = {{48, 1, 7, 0, 0x2222}, {48, 1, 2, 2, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData17_SOBEL_Y_5X5_08S[] = {{64, 1, 7, 0, 0x2222}, {64, 1, 2, 2, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData18_SOBEL_Y_5X5_08S[] = {{96, 1, 7, 0, 0x2222}, {96, 1, 2, 2, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData19_SOBEL_Y_5X5_08S[] = {{112, 1, 7, 0, 0x2222}, {112, 1, 2, 2, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData20_SOBEL_Y_5X5_08S[] = {{128, 1, 7, 0, 0x2222}, {128, 1, 2, 2, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData21_SOBEL_Y_5X5_08S[] = {{2, 2, 4, 0, 0x2222}, {2, 2, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData22_SOBEL_Y_5X5_08S[] = {{4, 2, 4, 0, 0x2222}, {4, 2, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData23_SOBEL_Y_5X5_08S[] = {{6, 2, 4, 0, 0x2222}, {6, 2, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData24_SOBEL_Y_5X5_08S[] = {{8, 2, 4, 0, 0x2222}, {8, 2, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData25_SOBEL_Y_5X5_08S[] = {{10, 2, 4, 0, 0x2222}, {10, 2, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData26_SOBEL_Y_5X5_08S[] = {{12, 2, 4, 0, 0x2222}, {12, 2, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData27_SOBEL_Y_5X5_08S[] = {{14, 2, 4, 0, 0x2222}, {14, 2, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData28_SOBEL_Y_5X5_08S[] = {{16, 2, 4, 0, 0x2222}, {16, 2, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData29_SOBEL_Y_5X5_08S[] = {{18, 2, 4, 0, 0x2222}, {18, 2, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData30_SOBEL_Y_5X5_08S[] = {{20, 2, 4, 0, 0x2222}, {20, 2, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData31_SOBEL_Y_5X5_08S[] = {{22, 2, 4, 0, 0x2222}, {22, 2, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData32_SOBEL_Y_5X5_08S[] = {{24, 2, 4, 0, 0x2222}, {24, 2, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData33_SOBEL_Y_5X5_08S[] = {{26, 2, 4, 0, 0x2222}, {26, 2, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData34_SOBEL_Y_5X5_08S[] = {{28, 2, 4, 0, 0x2222}, {28, 2, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData35_SOBEL_Y_5X5_08S[] = {{30, 2, 4, 0, 0x2222}, {30, 2, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData36_SOBEL_Y_5X5_08S[] = {{32, 2, 4, 0, 0x2222}, {32, 2, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData37_SOBEL_Y_5X5_08S[] = {{48, 2, 4, 0, 0x2222}, {48, 2, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData38_SOBEL_Y_5X5_08S[] = {{64, 2, 4, 0, 0x2222}, {64, 2, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData39_SOBEL_Y_5X5_08S[] = {{96, 2, 4, 0, 0x2222}, {96, 2, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData40_SOBEL_Y_5X5_08S[] = {{112, 2, 4, 0, 0x2222}, {112, 2, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData41_SOBEL_Y_5X5_08S[] = {{128, 2, 4, 0, 0x2222}, {128, 2, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData42_SOBEL_Y_5X5_08S[] = {{2, 4, 4, 0, 0x2222}, {2, 4, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData43_SOBEL_Y_5X5_08S[] = {{4, 4, 4, 0, 0x2222}, {4, 4, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData44_SOBEL_Y_5X5_08S[] = {{6, 4, 4, 0, 0x2222}, {6, 4, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData45_SOBEL_Y_5X5_08S[] = {{8, 4, 4, 0, 0x2222}, {8, 4, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData46_SOBEL_Y_5X5_08S[] = {{10, 4, 4, 0, 0x2222}, {10, 4, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData47_SOBEL_Y_5X5_08S[] = {{12, 4, 4, 0, 0x2222}, {12, 4, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData48_SOBEL_Y_5X5_08S[] = {{14, 4, 4, 0, 0x2222}, {14, 4, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData49_SOBEL_Y_5X5_08S[] = {{16, 4, 4, 0, 0x2222}, {16, 4, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData50_SOBEL_Y_5X5_08S[] = {{18, 4, 4, 0, 0x2222}, {18, 4, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData51_SOBEL_Y_5X5_08S[] = {{20, 4, 4, 0, 0x2222}, {20, 4, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData52_SOBEL_Y_5X5_08S[] = {{22, 4, 4, 0, 0x2222}, {22, 4, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData53_SOBEL_Y_5X5_08S[] = {{24, 4, 4, 0, 0x2222}, {24, 4, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData54_SOBEL_Y_5X5_08S[] = {{26, 4, 4, 0, 0x2222}, {26, 4, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData55_SOBEL_Y_5X5_08S[] = {{28, 4, 4, 0, 0x2222}, {28, 4, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData56_SOBEL_Y_5X5_08S[] = {{30, 4, 4, 0, 0x2222}, {30, 4, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData57_SOBEL_Y_5X5_08S[] = {{32, 4, 4, 0, 0x2222}, {32, 4, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData58_SOBEL_Y_5X5_08S[] = {{48, 4, 4, 0, 0x2222}, {48, 4, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData59_SOBEL_Y_5X5_08S[] = {{64, 4, 4, 0, 0x2222}, {64, 4, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData60_SOBEL_Y_5X5_08S[] = {{96, 4, 4, 0, 0x2222}, {96, 4, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData61_SOBEL_Y_5X5_08S[] = {{112, 4, 4, 0, 0x2222}, {112, 4, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData62_SOBEL_Y_5X5_08S[] = {{128, 4, 4, 0, 0x2222}, {128, 4, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData63_SOBEL_Y_5X5_08S[] = {{2, 6, 4, 0, 0x2222}, {2, 6, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData64_SOBEL_Y_5X5_08S[] = {{4, 6, 4, 0, 0x2222}, {4, 6, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData65_SOBEL_Y_5X5_08S[] = {{6, 6, 4, 0, 0x2222}, {6, 6, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData66_SOBEL_Y_5X5_08S[] = {{8, 6, 4, 0, 0x2222}, {8, 6, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData67_SOBEL_Y_5X5_08S[] = {{10, 6, 4, 0, 0x2222}, {10, 6, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData68_SOBEL_Y_5X5_08S[] = {{12, 6, 4, 0, 0x2222}, {12, 6, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData69_SOBEL_Y_5X5_08S[] = {{14, 6, 4, 0, 0x2222}, {14, 6, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData70_SOBEL_Y_5X5_08S[] = {{16, 6, 4, 0, 0x2222}, {16, 6, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData71_SOBEL_Y_5X5_08S[] = {{18, 6, 4, 0, 0x2222}, {18, 6, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData72_SOBEL_Y_5X5_08S[] = {{20, 6, 4, 0, 0x2222}, {20, 6, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData73_SOBEL_Y_5X5_08S[] = {{22, 6, 4, 0, 0x2222}, {22, 6, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData74_SOBEL_Y_5X5_08S[] = {{24, 6, 4, 0, 0x2222}, {24, 6, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData75_SOBEL_Y_5X5_08S[] = {{26, 6, 4, 0, 0x2222}, {26, 6, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData76_SOBEL_Y_5X5_08S[] = {{28, 6, 4, 0, 0x2222}, {28, 6, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData77_SOBEL_Y_5X5_08S[] = {{30, 6, 4, 0, 0x2222}, {30, 6, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData78_SOBEL_Y_5X5_08S[] = {{32, 6, 4, 0, 0x2222}, {32, 6, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData79_SOBEL_Y_5X5_08S[] = {{48, 6, 4, 0, 0x2222}, {48, 6, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData80_SOBEL_Y_5X5_08S[] = {{64, 6, 4, 0, 0x2222}, {64, 6, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData81_SOBEL_Y_5X5_08S[] = {{2, 8, 4, 0, 0x2222}, {2, 8, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData82_SOBEL_Y_5X5_08S[] = {{4, 8, 4, 0, 0x2222}, {4, 8, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData83_SOBEL_Y_5X5_08S[] = {{6, 8, 4, 0, 0x2222}, {6, 8, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData84_SOBEL_Y_5X5_08S[] = {{8, 8, 4, 0, 0x2222}, {8, 8, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData85_SOBEL_Y_5X5_08S[] = {{10, 8, 4, 0, 0x2222}, {10, 8, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData86_SOBEL_Y_5X5_08S[] = {{12, 8, 4, 0, 0x2222}, {12, 8, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData87_SOBEL_Y_5X5_08S[] = {{14, 8, 4, 0, 0x2222}, {14, 8, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData88_SOBEL_Y_5X5_08S[] = {{16, 8, 4, 0, 0x2222}, {16, 8, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData89_SOBEL_Y_5X5_08S[] = {{18, 8, 4, 0, 0x2222}, {18, 8, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData90_SOBEL_Y_5X5_08S[] = {{20, 8, 4, 0, 0x2222}, {20, 8, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData91_SOBEL_Y_5X5_08S[] = {{22, 8, 4, 0, 0x2222}, {22, 8, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData92_SOBEL_Y_5X5_08S[] = {{24, 8, 4, 0, 0x2222}, {24, 8, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData93_SOBEL_Y_5X5_08S[] = {{26, 8, 4, 0, 0x2222}, {26, 8, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData94_SOBEL_Y_5X5_08S[] = {{28, 8, 4, 0, 0x2222}, {28, 8, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData95_SOBEL_Y_5X5_08S[] = {{30, 8, 4, 0, 0x2222}, {30, 8, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData96_SOBEL_Y_5X5_08S[] = {{32, 8, 4, 0, 0x2222}, {32, 8, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData97_SOBEL_Y_5X5_08S[] = {{48, 8, 4, 0, 0x2222}, {48, 8, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData98_SOBEL_Y_5X5_08S[] = {{64, 8, 4, 0, 0x2222}, {64, 8, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData99_SOBEL_Y_5X5_08S[] = {{2, 10, 4, 0, 0x2222}, {2, 10, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData100_SOBEL_Y_5X5_08S[] = {{4, 10, 4, 0, 0x2222}, {4, 10, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData101_SOBEL_Y_5X5_08S[] = {{6, 10, 4, 0, 0x2222}, {6, 10, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData102_SOBEL_Y_5X5_08S[] = {{8, 10, 4, 0, 0x2222}, {8, 10, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData103_SOBEL_Y_5X5_08S[] = {{10, 10, 4, 0, 0x2222}, {10, 10, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData104_SOBEL_Y_5X5_08S[] = {{12, 10, 4, 0, 0x2222}, {12, 10, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData105_SOBEL_Y_5X5_08S[] = {{14, 10, 4, 0, 0x2222}, {14, 10, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData106_SOBEL_Y_5X5_08S[] = {{16, 10, 4, 0, 0x2222}, {16, 10, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData107_SOBEL_Y_5X5_08S[] = {{18, 10, 4, 0, 0x2222}, {18, 10, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData108_SOBEL_Y_5X5_08S[] = {{20, 10, 4, 0, 0x2222}, {20, 10, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData109_SOBEL_Y_5X5_08S[] = {{22, 10, 4, 0, 0x2222}, {22, 10, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData110_SOBEL_Y_5X5_08S[] = {{24, 10, 4, 0, 0x2222}, {24, 10, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData111_SOBEL_Y_5X5_08S[] = {{26, 10, 4, 0, 0x2222}, {26, 10, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData112_SOBEL_Y_5X5_08S[] = {{28, 10, 4, 0, 0x2222}, {28, 10, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData113_SOBEL_Y_5X5_08S[] = {{30, 10, 4, 0, 0x2222}, {30, 10, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData114_SOBEL_Y_5X5_08S[] = {{32, 10, 4, 0, 0x2222}, {32, 10, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData115_SOBEL_Y_5X5_08S[] = {{48, 10, 4, 0, 0x2222}, {48, 10, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData116_SOBEL_Y_5X5_08S[] = {{2, 12, 4, 0, 0x2222}, {2, 12, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData117_SOBEL_Y_5X5_08S[] = {{4, 12, 4, 0, 0x2222}, {4, 12, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData118_SOBEL_Y_5X5_08S[] = {{6, 12, 4, 0, 0x2222}, {6, 12, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData119_SOBEL_Y_5X5_08S[] = {{8, 12, 4, 0, 0x2222}, {8, 12, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData120_SOBEL_Y_5X5_08S[] = {{10, 12, 4, 0, 0x2222}, {10, 12, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData121_SOBEL_Y_5X5_08S[] = {{12, 12, 4, 0, 0x2222}, {12, 12, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData122_SOBEL_Y_5X5_08S[] = {{14, 12, 4, 0, 0x2222}, {14, 12, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData123_SOBEL_Y_5X5_08S[] = {{16, 12, 4, 0, 0x2222}, {16, 12, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData124_SOBEL_Y_5X5_08S[] = {{18, 12, 4, 0, 0x2222}, {18, 12, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData125_SOBEL_Y_5X5_08S[] = {{20, 12, 4, 0, 0x2222}, {20, 12, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData126_SOBEL_Y_5X5_08S[] = {{22, 12, 4, 0, 0x2222}, {22, 12, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData127_SOBEL_Y_5X5_08S[] = {{24, 12, 4, 0, 0x2222}, {24, 12, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData128_SOBEL_Y_5X5_08S[] = {{26, 12, 4, 0, 0x2222}, {26, 12, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData129_SOBEL_Y_5X5_08S[] = {{28, 12, 4, 0, 0x2222}, {28, 12, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData130_SOBEL_Y_5X5_08S[] = {{30, 12, 4, 0, 0x2222}, {30, 12, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData131_SOBEL_Y_5X5_08S[] = {{32, 12, 4, 0, 0x2222}, {32, 12, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData132_SOBEL_Y_5X5_08S[] = {{2, 14, 4, 0, 0x2222}, {2, 14, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData133_SOBEL_Y_5X5_08S[] = {{4, 14, 4, 0, 0x2222}, {4, 14, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData134_SOBEL_Y_5X5_08S[] = {{6, 14, 4, 0, 0x2222}, {6, 14, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData135_SOBEL_Y_5X5_08S[] = {{8, 14, 4, 0, 0x2222}, {8, 14, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData136_SOBEL_Y_5X5_08S[] = {{10, 14, 4, 0, 0x2222}, {10, 14, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData137_SOBEL_Y_5X5_08S[] = {{12, 14, 4, 0, 0x2222}, {12, 14, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData138_SOBEL_Y_5X5_08S[] = {{14, 14, 4, 0, 0x2222}, {14, 14, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData139_SOBEL_Y_5X5_08S[] = {{16, 14, 4, 0, 0x2222}, {16, 14, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData140_SOBEL_Y_5X5_08S[] = {{18, 14, 4, 0, 0x2222}, {18, 14, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData141_SOBEL_Y_5X5_08S[] = {{20, 14, 4, 0, 0x2222}, {20, 14, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData142_SOBEL_Y_5X5_08S[] = {{22, 14, 4, 0, 0x2222}, {22, 14, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData143_SOBEL_Y_5X5_08S[] = {{24, 14, 4, 0, 0x2222}, {24, 14, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData144_SOBEL_Y_5X5_08S[] = {{26, 14, 4, 0, 0x2222}, {26, 14, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData145_SOBEL_Y_5X5_08S[] = {{28, 14, 4, 0, 0x2222}, {28, 14, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData146_SOBEL_Y_5X5_08S[] = {{30, 14, 4, 0, 0x2222}, {30, 14, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData147_SOBEL_Y_5X5_08S[] = {{32, 14, 4, 0, 0x2222}, {32, 14, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData148_SOBEL_Y_5X5_08S[] = {{2, 16, 4, 0, 0x2222}, {2, 16, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData149_SOBEL_Y_5X5_08S[] = {{4, 16, 4, 0, 0x2222}, {4, 16, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData150_SOBEL_Y_5X5_08S[] = {{6, 16, 4, 0, 0x2222}, {6, 16, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData151_SOBEL_Y_5X5_08S[] = {{8, 16, 4, 0, 0x2222}, {8, 16, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData152_SOBEL_Y_5X5_08S[] = {{10, 16, 4, 0, 0x2222}, {10, 16, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData153_SOBEL_Y_5X5_08S[] = {{12, 16, 4, 0, 0x2222}, {12, 16, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData154_SOBEL_Y_5X5_08S[] = {{14, 16, 4, 0, 0x2222}, {14, 16, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData155_SOBEL_Y_5X5_08S[] = {{16, 16, 4, 0, 0x2222}, {16, 16, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData156_SOBEL_Y_5X5_08S[] = {{18, 16, 4, 0, 0x2222}, {18, 16, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData157_SOBEL_Y_5X5_08S[] = {{20, 16, 4, 0, 0x2222}, {20, 16, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData158_SOBEL_Y_5X5_08S[] = {{22, 16, 4, 0, 0x2222}, {22, 16, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData159_SOBEL_Y_5X5_08S[] = {{24, 16, 4, 0, 0x2222}, {24, 16, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData160_SOBEL_Y_5X5_08S[] = {{26, 16, 4, 0, 0x2222}, {26, 16, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData161_SOBEL_Y_5X5_08S[] = {{28, 16, 4, 0, 0x2222}, {28, 16, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData162_SOBEL_Y_5X5_08S[] = {{30, 16, 4, 0, 0x2222}, {30, 16, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData163_SOBEL_Y_5X5_08S[] = {{32, 16, 4, 0, 0x2222}, {32, 16, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData164_SOBEL_Y_5X5_08S[] = {{2, 18, 4, 0, 0x2222}, {2, 18, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData165_SOBEL_Y_5X5_08S[] = {{4, 18, 4, 0, 0x2222}, {4, 18, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData166_SOBEL_Y_5X5_08S[] = {{6, 18, 4, 0, 0x2222}, {6, 18, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData167_SOBEL_Y_5X5_08S[] = {{8, 18, 4, 0, 0x2222}, {8, 18, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData168_SOBEL_Y_5X5_08S[] = {{10, 18, 4, 0, 0x2222}, {10, 18, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData169_SOBEL_Y_5X5_08S[] = {{12, 18, 4, 0, 0x2222}, {12, 18, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData170_SOBEL_Y_5X5_08S[] = {{14, 18, 4, 0, 0x2222}, {14, 18, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData171_SOBEL_Y_5X5_08S[] = {{16, 18, 4, 0, 0x2222}, {16, 18, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData172_SOBEL_Y_5X5_08S[] = {{18, 18, 4, 0, 0x2222}, {18, 18, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData173_SOBEL_Y_5X5_08S[] = {{20, 18, 4, 0, 0x2222}, {20, 18, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData174_SOBEL_Y_5X5_08S[] = {{22, 18, 4, 0, 0x2222}, {22, 18, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData175_SOBEL_Y_5X5_08S[] = {{24, 18, 4, 0, 0x2222}, {24, 18, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData176_SOBEL_Y_5X5_08S[] = {{26, 18, 4, 0, 0x2222}, {26, 18, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData177_SOBEL_Y_5X5_08S[] = {{28, 18, 4, 0, 0x2222}, {28, 18, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData178_SOBEL_Y_5X5_08S[] = {{30, 18, 4, 0, 0x2222}, {30, 18, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData179_SOBEL_Y_5X5_08S[] = {{2, 20, 4, 0, 0x2222}, {2, 20, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData180_SOBEL_Y_5X5_08S[] = {{4, 20, 4, 0, 0x2222}, {4, 20, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData181_SOBEL_Y_5X5_08S[] = {{6, 20, 4, 0, 0x2222}, {6, 20, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData182_SOBEL_Y_5X5_08S[] = {{8, 20, 4, 0, 0x2222}, {8, 20, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData183_SOBEL_Y_5X5_08S[] = {{10, 20, 4, 0, 0x2222}, {10, 20, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData184_SOBEL_Y_5X5_08S[] = {{12, 20, 4, 0, 0x2222}, {12, 20, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData185_SOBEL_Y_5X5_08S[] = {{14, 20, 4, 0, 0x2222}, {14, 20, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData186_SOBEL_Y_5X5_08S[] = {{16, 20, 4, 0, 0x2222}, {16, 20, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData187_SOBEL_Y_5X5_08S[] = {{18, 20, 4, 0, 0x2222}, {18, 20, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData188_SOBEL_Y_5X5_08S[] = {{20, 20, 4, 0, 0x2222}, {20, 20, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData189_SOBEL_Y_5X5_08S[] = {{22, 20, 4, 0, 0x2222}, {22, 20, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData190_SOBEL_Y_5X5_08S[] = {{24, 20, 4, 0, 0x2222}, {24, 20, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData191_SOBEL_Y_5X5_08S[] = {{26, 20, 4, 0, 0x2222}, {26, 20, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData192_SOBEL_Y_5X5_08S[] = {{28, 20, 4, 0, 0x2222}, {28, 20, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData193_SOBEL_Y_5X5_08S[] = {{2, 22, 4, 0, 0x2222}, {2, 22, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData194_SOBEL_Y_5X5_08S[] = {{4, 22, 4, 0, 0x2222}, {4, 22, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData195_SOBEL_Y_5X5_08S[] = {{6, 22, 4, 0, 0x2222}, {6, 22, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData196_SOBEL_Y_5X5_08S[] = {{8, 22, 4, 0, 0x2222}, {8, 22, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData197_SOBEL_Y_5X5_08S[] = {{10, 22, 4, 0, 0x2222}, {10, 22, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData198_SOBEL_Y_5X5_08S[] = {{12, 22, 4, 0, 0x2222}, {12, 22, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData199_SOBEL_Y_5X5_08S[] = {{14, 22, 4, 0, 0x2222}, {14, 22, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData200_SOBEL_Y_5X5_08S[] = {{16, 22, 4, 0, 0x2222}, {16, 22, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData201_SOBEL_Y_5X5_08S[] = {{18, 22, 4, 0, 0x2222}, {18, 22, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData202_SOBEL_Y_5X5_08S[] = {{20, 22, 4, 0, 0x2222}, {20, 22, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData203_SOBEL_Y_5X5_08S[] = {{22, 22, 4, 0, 0x2222}, {22, 22, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData204_SOBEL_Y_5X5_08S[] = {{24, 22, 4, 0, 0x2222}, {24, 22, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData205_SOBEL_Y_5X5_08S[] = {{2, 24, 4, 0, 0x2222}, {2, 24, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData206_SOBEL_Y_5X5_08S[] = {{4, 24, 4, 0, 0x2222}, {4, 24, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData207_SOBEL_Y_5X5_08S[] = {{6, 24, 4, 0, 0x2222}, {6, 24, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData208_SOBEL_Y_5X5_08S[] = {{8, 24, 4, 0, 0x2222}, {8, 24, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData209_SOBEL_Y_5X5_08S[] = {{10, 24, 4, 0, 0x2222}, {10, 24, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData210_SOBEL_Y_5X5_08S[] = {{12, 24, 4, 0, 0x2222}, {12, 24, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData211_SOBEL_Y_5X5_08S[] = {{14, 24, 4, 0, 0x2222}, {14, 24, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData212_SOBEL_Y_5X5_08S[] = {{16, 24, 4, 0, 0x2222}, {16, 24, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData213_SOBEL_Y_5X5_08S[] = {{18, 24, 4, 0, 0x2222}, {18, 24, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData214_SOBEL_Y_5X5_08S[] = {{20, 24, 4, 0, 0x2222}, {20, 24, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData215_SOBEL_Y_5X5_08S[] = {{22, 24, 4, 0, 0x2222}, {22, 24, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData216_SOBEL_Y_5X5_08S[] = {{2, 26, 4, 0, 0x2222}, {2, 26, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData217_SOBEL_Y_5X5_08S[] = {{4, 26, 4, 0, 0x2222}, {4, 26, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData218_SOBEL_Y_5X5_08S[] = {{6, 26, 4, 0, 0x2222}, {6, 26, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData219_SOBEL_Y_5X5_08S[] = {{8, 26, 4, 0, 0x2222}, {8, 26, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData220_SOBEL_Y_5X5_08S[] = {{10, 26, 4, 0, 0x2222}, {10, 26, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData221_SOBEL_Y_5X5_08S[] = {{12, 26, 4, 0, 0x2222}, {12, 26, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData222_SOBEL_Y_5X5_08S[] = {{14, 26, 4, 0, 0x2222}, {14, 26, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData223_SOBEL_Y_5X5_08S[] = {{16, 26, 4, 0, 0x2222}, {16, 26, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData224_SOBEL_Y_5X5_08S[] = {{18, 26, 4, 0, 0x2222}, {18, 26, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData225_SOBEL_Y_5X5_08S[] = {{20, 26, 4, 0, 0x2222}, {20, 26, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData226_SOBEL_Y_5X5_08S[] = {{2, 28, 4, 0, 0x2222}, {2, 28, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData227_SOBEL_Y_5X5_08S[] = {{4, 28, 4, 0, 0x2222}, {4, 28, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData228_SOBEL_Y_5X5_08S[] = {{6, 28, 4, 0, 0x2222}, {6, 28, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData229_SOBEL_Y_5X5_08S[] = {{8, 28, 4, 0, 0x2222}, {8, 28, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData230_SOBEL_Y_5X5_08S[] = {{10, 28, 4, 0, 0x2222}, {10, 28, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData231_SOBEL_Y_5X5_08S[] = {{12, 28, 4, 0, 0x2222}, {12, 28, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData232_SOBEL_Y_5X5_08S[] = {{14, 28, 4, 0, 0x2222}, {14, 28, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData233_SOBEL_Y_5X5_08S[] = {{16, 28, 4, 0, 0x2222}, {16, 28, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData234_SOBEL_Y_5X5_08S[] = {{18, 28, 4, 0, 0x2222}, {18, 28, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData235_SOBEL_Y_5X5_08S[] = {{2, 30, 4, 0, 0x2222}, {2, 30, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData236_SOBEL_Y_5X5_08S[] = {{4, 30, 4, 0, 0x2222}, {4, 30, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData237_SOBEL_Y_5X5_08S[] = {{6, 30, 4, 0, 0x2222}, {6, 30, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData238_SOBEL_Y_5X5_08S[] = {{8, 30, 4, 0, 0x2222}, {8, 30, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData239_SOBEL_Y_5X5_08S[] = {{10, 30, 4, 0, 0x2222}, {10, 30, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData240_SOBEL_Y_5X5_08S[] = {{12, 30, 4, 0, 0x2222}, {12, 30, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData241_SOBEL_Y_5X5_08S[] = {{14, 30, 4, 0, 0x2222}, {14, 30, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData242_SOBEL_Y_5X5_08S[] = {{16, 30, 4, 0, 0x2222}, {16, 30, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData243_SOBEL_Y_5X5_08S[] = {{18, 30, 4, 0, 0x2222}, {18, 30, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData244_SOBEL_Y_5X5_08S[] = {{2, 32, 4, 0, 0x2222}, {2, 32, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData245_SOBEL_Y_5X5_08S[] = {{4, 32, 4, 0, 0x2222}, {4, 32, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData246_SOBEL_Y_5X5_08S[] = {{6, 32, 4, 0, 0x2222}, {6, 32, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData247_SOBEL_Y_5X5_08S[] = {{8, 32, 4, 0, 0x2222}, {8, 32, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData248_SOBEL_Y_5X5_08S[] = {{10, 32, 4, 0, 0x2222}, {10, 32, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData249_SOBEL_Y_5X5_08S[] = {{12, 32, 4, 0, 0x2222}, {12, 32, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData250_SOBEL_Y_5X5_08S[] = {{14, 32, 4, 0, 0x2222}, {14, 32, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData251_SOBEL_Y_5X5_08S[] = {{16, 32, 4, 0, 0x2222}, {16, 32, 2, 1, 0x0}};

static acf_scenario_kernel_data gScenarioKernelData0_SOBEL_Y_5X5_08S[] = {{2}};
static acf_scenario_kernel_data gScenarioKernelData1_SOBEL_Y_5X5_08S[] = {{2}};
static acf_scenario_kernel_data gScenarioKernelData2_SOBEL_Y_5X5_08S[] = {{2}};
static acf_scenario_kernel_data gScenarioKernelData3_SOBEL_Y_5X5_08S[] = {{2}};
static acf_scenario_kernel_data gScenarioKernelData4_SOBEL_Y_5X5_08S[] = {{2}};
static acf_scenario_kernel_data gScenarioKernelData5_SOBEL_Y_5X5_08S[] = {{2}};
static acf_scenario_kernel_data gScenarioKernelData6_SOBEL_Y_5X5_08S[] = {{2}};
static acf_scenario_kernel_data gScenarioKernelData7_SOBEL_Y_5X5_08S[] = {{2}};
static acf_scenario_kernel_data gScenarioKernelData8_SOBEL_Y_5X5_08S[] = {{2}};
static acf_scenario_kernel_data gScenarioKernelData9_SOBEL_Y_5X5_08S[] = {{2}};
static acf_scenario_kernel_data gScenarioKernelData10_SOBEL_Y_5X5_08S[] = {{2}};
static acf_scenario_kernel_data gScenarioKernelData11_SOBEL_Y_5X5_08S[] = {{2}};
static acf_scenario_kernel_data gScenarioKernelData12_SOBEL_Y_5X5_08S[] = {{2}};
static acf_scenario_kernel_data gScenarioKernelData13_SOBEL_Y_5X5_08S[] = {{2}};
static acf_scenario_kernel_data gScenarioKernelData14_SOBEL_Y_5X5_08S[] = {{2}};
static acf_scenario_kernel_data gScenarioKernelData15_SOBEL_Y_5X5_08S[] = {{2}};
static acf_scenario_kernel_data gScenarioKernelData16_SOBEL_Y_5X5_08S[] = {{2}};
static acf_scenario_kernel_data gScenarioKernelData17_SOBEL_Y_5X5_08S[] = {{2}};
static acf_scenario_kernel_data gScenarioKernelData18_SOBEL_Y_5X5_08S[] = {{2}};
static acf_scenario_kernel_data gScenarioKernelData19_SOBEL_Y_5X5_08S[] = {{2}};
static acf_scenario_kernel_data gScenarioKernelData20_SOBEL_Y_5X5_08S[] = {{2}};
static acf_scenario_kernel_data gScenarioKernelData21_SOBEL_Y_5X5_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData22_SOBEL_Y_5X5_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData23_SOBEL_Y_5X5_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData24_SOBEL_Y_5X5_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData25_SOBEL_Y_5X5_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData26_SOBEL_Y_5X5_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData27_SOBEL_Y_5X5_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData28_SOBEL_Y_5X5_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData29_SOBEL_Y_5X5_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData30_SOBEL_Y_5X5_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData31_SOBEL_Y_5X5_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData32_SOBEL_Y_5X5_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData33_SOBEL_Y_5X5_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData34_SOBEL_Y_5X5_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData35_SOBEL_Y_5X5_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData36_SOBEL_Y_5X5_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData37_SOBEL_Y_5X5_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData38_SOBEL_Y_5X5_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData39_SOBEL_Y_5X5_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData40_SOBEL_Y_5X5_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData41_SOBEL_Y_5X5_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData42_SOBEL_Y_5X5_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData43_SOBEL_Y_5X5_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData44_SOBEL_Y_5X5_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData45_SOBEL_Y_5X5_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData46_SOBEL_Y_5X5_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData47_SOBEL_Y_5X5_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData48_SOBEL_Y_5X5_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData49_SOBEL_Y_5X5_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData50_SOBEL_Y_5X5_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData51_SOBEL_Y_5X5_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData52_SOBEL_Y_5X5_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData53_SOBEL_Y_5X5_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData54_SOBEL_Y_5X5_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData55_SOBEL_Y_5X5_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData56_SOBEL_Y_5X5_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData57_SOBEL_Y_5X5_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData58_SOBEL_Y_5X5_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData59_SOBEL_Y_5X5_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData60_SOBEL_Y_5X5_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData61_SOBEL_Y_5X5_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData62_SOBEL_Y_5X5_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData63_SOBEL_Y_5X5_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData64_SOBEL_Y_5X5_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData65_SOBEL_Y_5X5_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData66_SOBEL_Y_5X5_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData67_SOBEL_Y_5X5_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData68_SOBEL_Y_5X5_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData69_SOBEL_Y_5X5_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData70_SOBEL_Y_5X5_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData71_SOBEL_Y_5X5_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData72_SOBEL_Y_5X5_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData73_SOBEL_Y_5X5_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData74_SOBEL_Y_5X5_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData75_SOBEL_Y_5X5_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData76_SOBEL_Y_5X5_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData77_SOBEL_Y_5X5_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData78_SOBEL_Y_5X5_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData79_SOBEL_Y_5X5_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData80_SOBEL_Y_5X5_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData81_SOBEL_Y_5X5_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData82_SOBEL_Y_5X5_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData83_SOBEL_Y_5X5_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData84_SOBEL_Y_5X5_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData85_SOBEL_Y_5X5_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData86_SOBEL_Y_5X5_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData87_SOBEL_Y_5X5_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData88_SOBEL_Y_5X5_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData89_SOBEL_Y_5X5_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData90_SOBEL_Y_5X5_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData91_SOBEL_Y_5X5_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData92_SOBEL_Y_5X5_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData93_SOBEL_Y_5X5_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData94_SOBEL_Y_5X5_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData95_SOBEL_Y_5X5_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData96_SOBEL_Y_5X5_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData97_SOBEL_Y_5X5_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData98_SOBEL_Y_5X5_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData99_SOBEL_Y_5X5_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData100_SOBEL_Y_5X5_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData101_SOBEL_Y_5X5_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData102_SOBEL_Y_5X5_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData103_SOBEL_Y_5X5_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData104_SOBEL_Y_5X5_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData105_SOBEL_Y_5X5_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData106_SOBEL_Y_5X5_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData107_SOBEL_Y_5X5_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData108_SOBEL_Y_5X5_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData109_SOBEL_Y_5X5_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData110_SOBEL_Y_5X5_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData111_SOBEL_Y_5X5_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData112_SOBEL_Y_5X5_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData113_SOBEL_Y_5X5_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData114_SOBEL_Y_5X5_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData115_SOBEL_Y_5X5_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData116_SOBEL_Y_5X5_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData117_SOBEL_Y_5X5_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData118_SOBEL_Y_5X5_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData119_SOBEL_Y_5X5_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData120_SOBEL_Y_5X5_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData121_SOBEL_Y_5X5_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData122_SOBEL_Y_5X5_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData123_SOBEL_Y_5X5_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData124_SOBEL_Y_5X5_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData125_SOBEL_Y_5X5_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData126_SOBEL_Y_5X5_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData127_SOBEL_Y_5X5_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData128_SOBEL_Y_5X5_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData129_SOBEL_Y_5X5_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData130_SOBEL_Y_5X5_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData131_SOBEL_Y_5X5_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData132_SOBEL_Y_5X5_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData133_SOBEL_Y_5X5_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData134_SOBEL_Y_5X5_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData135_SOBEL_Y_5X5_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData136_SOBEL_Y_5X5_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData137_SOBEL_Y_5X5_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData138_SOBEL_Y_5X5_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData139_SOBEL_Y_5X5_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData140_SOBEL_Y_5X5_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData141_SOBEL_Y_5X5_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData142_SOBEL_Y_5X5_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData143_SOBEL_Y_5X5_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData144_SOBEL_Y_5X5_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData145_SOBEL_Y_5X5_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData146_SOBEL_Y_5X5_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData147_SOBEL_Y_5X5_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData148_SOBEL_Y_5X5_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData149_SOBEL_Y_5X5_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData150_SOBEL_Y_5X5_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData151_SOBEL_Y_5X5_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData152_SOBEL_Y_5X5_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData153_SOBEL_Y_5X5_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData154_SOBEL_Y_5X5_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData155_SOBEL_Y_5X5_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData156_SOBEL_Y_5X5_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData157_SOBEL_Y_5X5_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData158_SOBEL_Y_5X5_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData159_SOBEL_Y_5X5_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData160_SOBEL_Y_5X5_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData161_SOBEL_Y_5X5_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData162_SOBEL_Y_5X5_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData163_SOBEL_Y_5X5_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData164_SOBEL_Y_5X5_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData165_SOBEL_Y_5X5_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData166_SOBEL_Y_5X5_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData167_SOBEL_Y_5X5_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData168_SOBEL_Y_5X5_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData169_SOBEL_Y_5X5_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData170_SOBEL_Y_5X5_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData171_SOBEL_Y_5X5_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData172_SOBEL_Y_5X5_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData173_SOBEL_Y_5X5_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData174_SOBEL_Y_5X5_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData175_SOBEL_Y_5X5_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData176_SOBEL_Y_5X5_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData177_SOBEL_Y_5X5_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData178_SOBEL_Y_5X5_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData179_SOBEL_Y_5X5_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData180_SOBEL_Y_5X5_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData181_SOBEL_Y_5X5_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData182_SOBEL_Y_5X5_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData183_SOBEL_Y_5X5_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData184_SOBEL_Y_5X5_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData185_SOBEL_Y_5X5_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData186_SOBEL_Y_5X5_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData187_SOBEL_Y_5X5_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData188_SOBEL_Y_5X5_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData189_SOBEL_Y_5X5_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData190_SOBEL_Y_5X5_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData191_SOBEL_Y_5X5_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData192_SOBEL_Y_5X5_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData193_SOBEL_Y_5X5_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData194_SOBEL_Y_5X5_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData195_SOBEL_Y_5X5_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData196_SOBEL_Y_5X5_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData197_SOBEL_Y_5X5_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData198_SOBEL_Y_5X5_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData199_SOBEL_Y_5X5_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData200_SOBEL_Y_5X5_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData201_SOBEL_Y_5X5_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData202_SOBEL_Y_5X5_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData203_SOBEL_Y_5X5_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData204_SOBEL_Y_5X5_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData205_SOBEL_Y_5X5_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData206_SOBEL_Y_5X5_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData207_SOBEL_Y_5X5_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData208_SOBEL_Y_5X5_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData209_SOBEL_Y_5X5_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData210_SOBEL_Y_5X5_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData211_SOBEL_Y_5X5_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData212_SOBEL_Y_5X5_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData213_SOBEL_Y_5X5_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData214_SOBEL_Y_5X5_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData215_SOBEL_Y_5X5_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData216_SOBEL_Y_5X5_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData217_SOBEL_Y_5X5_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData218_SOBEL_Y_5X5_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData219_SOBEL_Y_5X5_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData220_SOBEL_Y_5X5_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData221_SOBEL_Y_5X5_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData222_SOBEL_Y_5X5_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData223_SOBEL_Y_5X5_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData224_SOBEL_Y_5X5_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData225_SOBEL_Y_5X5_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData226_SOBEL_Y_5X5_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData227_SOBEL_Y_5X5_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData228_SOBEL_Y_5X5_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData229_SOBEL_Y_5X5_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData230_SOBEL_Y_5X5_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData231_SOBEL_Y_5X5_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData232_SOBEL_Y_5X5_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData233_SOBEL_Y_5X5_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData234_SOBEL_Y_5X5_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData235_SOBEL_Y_5X5_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData236_SOBEL_Y_5X5_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData237_SOBEL_Y_5X5_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData238_SOBEL_Y_5X5_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData239_SOBEL_Y_5X5_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData240_SOBEL_Y_5X5_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData241_SOBEL_Y_5X5_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData242_SOBEL_Y_5X5_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData243_SOBEL_Y_5X5_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData244_SOBEL_Y_5X5_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData245_SOBEL_Y_5X5_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData246_SOBEL_Y_5X5_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData247_SOBEL_Y_5X5_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData248_SOBEL_Y_5X5_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData249_SOBEL_Y_5X5_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData250_SOBEL_Y_5X5_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData251_SOBEL_Y_5X5_08S[] = {{1}};

static acf_scenario gScenarioArray_SOBEL_Y_5X5_08S[] = {
{2, 1, 72, 0, 2, gScenarioBufferData0_SOBEL_Y_5X5_08S, 20, gScenarioKernelData0_SOBEL_Y_5X5_08S, 2},
{4, 1, 96, 0, 2, gScenarioBufferData1_SOBEL_Y_5X5_08S, 20, gScenarioKernelData1_SOBEL_Y_5X5_08S, 2},
{6, 1, 124, 0, 2, gScenarioBufferData2_SOBEL_Y_5X5_08S, 20, gScenarioKernelData2_SOBEL_Y_5X5_08S, 2},
{8, 1, 148, 0, 2, gScenarioBufferData3_SOBEL_Y_5X5_08S, 20, gScenarioKernelData3_SOBEL_Y_5X5_08S, 2},
{10, 1, 176, 0, 2, gScenarioBufferData4_SOBEL_Y_5X5_08S, 20, gScenarioKernelData4_SOBEL_Y_5X5_08S, 2},
{12, 1, 200, 0, 2, gScenarioBufferData5_SOBEL_Y_5X5_08S, 20, gScenarioKernelData5_SOBEL_Y_5X5_08S, 2},
{14, 1, 228, 0, 2, gScenarioBufferData6_SOBEL_Y_5X5_08S, 20, gScenarioKernelData6_SOBEL_Y_5X5_08S, 2},
{16, 1, 252, 0, 2, gScenarioBufferData7_SOBEL_Y_5X5_08S, 20, gScenarioKernelData7_SOBEL_Y_5X5_08S, 2},
{18, 1, 280, 0, 2, gScenarioBufferData8_SOBEL_Y_5X5_08S, 20, gScenarioKernelData8_SOBEL_Y_5X5_08S, 2},
{20, 1, 304, 0, 2, gScenarioBufferData9_SOBEL_Y_5X5_08S, 20, gScenarioKernelData9_SOBEL_Y_5X5_08S, 2},
{22, 1, 332, 0, 2, gScenarioBufferData10_SOBEL_Y_5X5_08S, 20, gScenarioKernelData10_SOBEL_Y_5X5_08S, 2},
{24, 1, 356, 0, 2, gScenarioBufferData11_SOBEL_Y_5X5_08S, 20, gScenarioKernelData11_SOBEL_Y_5X5_08S, 2},
{26, 1, 384, 0, 2, gScenarioBufferData12_SOBEL_Y_5X5_08S, 20, gScenarioKernelData12_SOBEL_Y_5X5_08S, 2},
{28, 1, 408, 0, 2, gScenarioBufferData13_SOBEL_Y_5X5_08S, 20, gScenarioKernelData13_SOBEL_Y_5X5_08S, 2},
{30, 1, 436, 0, 2, gScenarioBufferData14_SOBEL_Y_5X5_08S, 20, gScenarioKernelData14_SOBEL_Y_5X5_08S, 2},
{32, 1, 460, 0, 2, gScenarioBufferData15_SOBEL_Y_5X5_08S, 20, gScenarioKernelData15_SOBEL_Y_5X5_08S, 2},
{48, 1, 668, 0, 2, gScenarioBufferData16_SOBEL_Y_5X5_08S, 20, gScenarioKernelData16_SOBEL_Y_5X5_08S, 2},
{64, 1, 876, 0, 2, gScenarioBufferData17_SOBEL_Y_5X5_08S, 20, gScenarioKernelData17_SOBEL_Y_5X5_08S, 2},
{96, 1, 1292, 0, 2, gScenarioBufferData18_SOBEL_Y_5X5_08S, 20, gScenarioKernelData18_SOBEL_Y_5X5_08S, 2},
{112, 1, 1500, 0, 2, gScenarioBufferData19_SOBEL_Y_5X5_08S, 20, gScenarioKernelData19_SOBEL_Y_5X5_08S, 2},
{128, 1, 1708, 0, 2, gScenarioBufferData20_SOBEL_Y_5X5_08S, 20, gScenarioKernelData20_SOBEL_Y_5X5_08S, 2},
{2, 2, 80, 0, 1, gScenarioBufferData21_SOBEL_Y_5X5_08S, 20, gScenarioKernelData21_SOBEL_Y_5X5_08S, 2},
{4, 2, 112, 0, 1, gScenarioBufferData22_SOBEL_Y_5X5_08S, 20, gScenarioKernelData22_SOBEL_Y_5X5_08S, 2},
{6, 2, 144, 0, 1, gScenarioBufferData23_SOBEL_Y_5X5_08S, 20, gScenarioKernelData23_SOBEL_Y_5X5_08S, 2},
{8, 2, 176, 0, 1, gScenarioBufferData24_SOBEL_Y_5X5_08S, 20, gScenarioKernelData24_SOBEL_Y_5X5_08S, 2},
{10, 2, 208, 0, 1, gScenarioBufferData25_SOBEL_Y_5X5_08S, 20, gScenarioKernelData25_SOBEL_Y_5X5_08S, 2},
{12, 2, 240, 0, 1, gScenarioBufferData26_SOBEL_Y_5X5_08S, 20, gScenarioKernelData26_SOBEL_Y_5X5_08S, 2},
{14, 2, 272, 0, 1, gScenarioBufferData27_SOBEL_Y_5X5_08S, 20, gScenarioKernelData27_SOBEL_Y_5X5_08S, 2},
{16, 2, 304, 0, 1, gScenarioBufferData28_SOBEL_Y_5X5_08S, 20, gScenarioKernelData28_SOBEL_Y_5X5_08S, 2},
{18, 2, 336, 0, 1, gScenarioBufferData29_SOBEL_Y_5X5_08S, 20, gScenarioKernelData29_SOBEL_Y_5X5_08S, 2},
{20, 2, 368, 0, 1, gScenarioBufferData30_SOBEL_Y_5X5_08S, 20, gScenarioKernelData30_SOBEL_Y_5X5_08S, 2},
{22, 2, 400, 0, 1, gScenarioBufferData31_SOBEL_Y_5X5_08S, 20, gScenarioKernelData31_SOBEL_Y_5X5_08S, 2},
{24, 2, 432, 0, 1, gScenarioBufferData32_SOBEL_Y_5X5_08S, 20, gScenarioKernelData32_SOBEL_Y_5X5_08S, 2},
{26, 2, 464, 0, 1, gScenarioBufferData33_SOBEL_Y_5X5_08S, 20, gScenarioKernelData33_SOBEL_Y_5X5_08S, 2},
{28, 2, 496, 0, 1, gScenarioBufferData34_SOBEL_Y_5X5_08S, 20, gScenarioKernelData34_SOBEL_Y_5X5_08S, 2},
{30, 2, 528, 0, 1, gScenarioBufferData35_SOBEL_Y_5X5_08S, 20, gScenarioKernelData35_SOBEL_Y_5X5_08S, 2},
{32, 2, 560, 0, 1, gScenarioBufferData36_SOBEL_Y_5X5_08S, 20, gScenarioKernelData36_SOBEL_Y_5X5_08S, 2},
{48, 2, 816, 0, 1, gScenarioBufferData37_SOBEL_Y_5X5_08S, 20, gScenarioKernelData37_SOBEL_Y_5X5_08S, 2},
{64, 2, 1072, 0, 1, gScenarioBufferData38_SOBEL_Y_5X5_08S, 20, gScenarioKernelData38_SOBEL_Y_5X5_08S, 2},
{96, 2, 1584, 0, 1, gScenarioBufferData39_SOBEL_Y_5X5_08S, 20, gScenarioKernelData39_SOBEL_Y_5X5_08S, 2},
{112, 2, 1840, 0, 1, gScenarioBufferData40_SOBEL_Y_5X5_08S, 20, gScenarioKernelData40_SOBEL_Y_5X5_08S, 2},
{128, 2, 2096, 0, 1, gScenarioBufferData41_SOBEL_Y_5X5_08S, 20, gScenarioKernelData41_SOBEL_Y_5X5_08S, 2},
{2, 4, 136, 0, 1, gScenarioBufferData42_SOBEL_Y_5X5_08S, 20, gScenarioKernelData42_SOBEL_Y_5X5_08S, 2},
{4, 4, 192, 0, 1, gScenarioBufferData43_SOBEL_Y_5X5_08S, 20, gScenarioKernelData43_SOBEL_Y_5X5_08S, 2},
{6, 4, 248, 0, 1, gScenarioBufferData44_SOBEL_Y_5X5_08S, 20, gScenarioKernelData44_SOBEL_Y_5X5_08S, 2},
{8, 4, 304, 0, 1, gScenarioBufferData45_SOBEL_Y_5X5_08S, 20, gScenarioKernelData45_SOBEL_Y_5X5_08S, 2},
{10, 4, 360, 0, 1, gScenarioBufferData46_SOBEL_Y_5X5_08S, 20, gScenarioKernelData46_SOBEL_Y_5X5_08S, 2},
{12, 4, 416, 0, 1, gScenarioBufferData47_SOBEL_Y_5X5_08S, 20, gScenarioKernelData47_SOBEL_Y_5X5_08S, 2},
{14, 4, 472, 0, 1, gScenarioBufferData48_SOBEL_Y_5X5_08S, 20, gScenarioKernelData48_SOBEL_Y_5X5_08S, 2},
{16, 4, 528, 0, 1, gScenarioBufferData49_SOBEL_Y_5X5_08S, 20, gScenarioKernelData49_SOBEL_Y_5X5_08S, 2},
{18, 4, 584, 0, 1, gScenarioBufferData50_SOBEL_Y_5X5_08S, 20, gScenarioKernelData50_SOBEL_Y_5X5_08S, 2},
{20, 4, 640, 0, 1, gScenarioBufferData51_SOBEL_Y_5X5_08S, 20, gScenarioKernelData51_SOBEL_Y_5X5_08S, 2},
{22, 4, 696, 0, 1, gScenarioBufferData52_SOBEL_Y_5X5_08S, 20, gScenarioKernelData52_SOBEL_Y_5X5_08S, 2},
{24, 4, 752, 0, 1, gScenarioBufferData53_SOBEL_Y_5X5_08S, 20, gScenarioKernelData53_SOBEL_Y_5X5_08S, 2},
{26, 4, 808, 0, 1, gScenarioBufferData54_SOBEL_Y_5X5_08S, 20, gScenarioKernelData54_SOBEL_Y_5X5_08S, 2},
{28, 4, 864, 0, 1, gScenarioBufferData55_SOBEL_Y_5X5_08S, 20, gScenarioKernelData55_SOBEL_Y_5X5_08S, 2},
{30, 4, 920, 0, 1, gScenarioBufferData56_SOBEL_Y_5X5_08S, 20, gScenarioKernelData56_SOBEL_Y_5X5_08S, 2},
{32, 4, 976, 0, 1, gScenarioBufferData57_SOBEL_Y_5X5_08S, 20, gScenarioKernelData57_SOBEL_Y_5X5_08S, 2},
{48, 4, 1424, 0, 1, gScenarioBufferData58_SOBEL_Y_5X5_08S, 20, gScenarioKernelData58_SOBEL_Y_5X5_08S, 2},
{64, 4, 1872, 0, 1, gScenarioBufferData59_SOBEL_Y_5X5_08S, 20, gScenarioKernelData59_SOBEL_Y_5X5_08S, 2},
{96, 4, 2768, 0, 1, gScenarioBufferData60_SOBEL_Y_5X5_08S, 20, gScenarioKernelData60_SOBEL_Y_5X5_08S, 2},
{112, 4, 3216, 0, 1, gScenarioBufferData61_SOBEL_Y_5X5_08S, 20, gScenarioKernelData61_SOBEL_Y_5X5_08S, 2},
{128, 4, 3664, 0, 1, gScenarioBufferData62_SOBEL_Y_5X5_08S, 20, gScenarioKernelData62_SOBEL_Y_5X5_08S, 2},
{2, 6, 192, 0, 1, gScenarioBufferData63_SOBEL_Y_5X5_08S, 20, gScenarioKernelData63_SOBEL_Y_5X5_08S, 2},
{4, 6, 272, 0, 1, gScenarioBufferData64_SOBEL_Y_5X5_08S, 20, gScenarioKernelData64_SOBEL_Y_5X5_08S, 2},
{6, 6, 352, 0, 1, gScenarioBufferData65_SOBEL_Y_5X5_08S, 20, gScenarioKernelData65_SOBEL_Y_5X5_08S, 2},
{8, 6, 432, 0, 1, gScenarioBufferData66_SOBEL_Y_5X5_08S, 20, gScenarioKernelData66_SOBEL_Y_5X5_08S, 2},
{10, 6, 512, 0, 1, gScenarioBufferData67_SOBEL_Y_5X5_08S, 20, gScenarioKernelData67_SOBEL_Y_5X5_08S, 2},
{12, 6, 592, 0, 1, gScenarioBufferData68_SOBEL_Y_5X5_08S, 20, gScenarioKernelData68_SOBEL_Y_5X5_08S, 2},
{14, 6, 672, 0, 1, gScenarioBufferData69_SOBEL_Y_5X5_08S, 20, gScenarioKernelData69_SOBEL_Y_5X5_08S, 2},
{16, 6, 752, 0, 1, gScenarioBufferData70_SOBEL_Y_5X5_08S, 20, gScenarioKernelData70_SOBEL_Y_5X5_08S, 2},
{18, 6, 832, 0, 1, gScenarioBufferData71_SOBEL_Y_5X5_08S, 20, gScenarioKernelData71_SOBEL_Y_5X5_08S, 2},
{20, 6, 912, 0, 1, gScenarioBufferData72_SOBEL_Y_5X5_08S, 20, gScenarioKernelData72_SOBEL_Y_5X5_08S, 2},
{22, 6, 992, 0, 1, gScenarioBufferData73_SOBEL_Y_5X5_08S, 20, gScenarioKernelData73_SOBEL_Y_5X5_08S, 2},
{24, 6, 1072, 0, 1, gScenarioBufferData74_SOBEL_Y_5X5_08S, 20, gScenarioKernelData74_SOBEL_Y_5X5_08S, 2},
{26, 6, 1152, 0, 1, gScenarioBufferData75_SOBEL_Y_5X5_08S, 20, gScenarioKernelData75_SOBEL_Y_5X5_08S, 2},
{28, 6, 1232, 0, 1, gScenarioBufferData76_SOBEL_Y_5X5_08S, 20, gScenarioKernelData76_SOBEL_Y_5X5_08S, 2},
{30, 6, 1312, 0, 1, gScenarioBufferData77_SOBEL_Y_5X5_08S, 20, gScenarioKernelData77_SOBEL_Y_5X5_08S, 2},
{32, 6, 1392, 0, 1, gScenarioBufferData78_SOBEL_Y_5X5_08S, 20, gScenarioKernelData78_SOBEL_Y_5X5_08S, 2},
{48, 6, 2032, 0, 1, gScenarioBufferData79_SOBEL_Y_5X5_08S, 20, gScenarioKernelData79_SOBEL_Y_5X5_08S, 2},
{64, 6, 2672, 0, 1, gScenarioBufferData80_SOBEL_Y_5X5_08S, 20, gScenarioKernelData80_SOBEL_Y_5X5_08S, 2},
{2, 8, 248, 0, 1, gScenarioBufferData81_SOBEL_Y_5X5_08S, 20, gScenarioKernelData81_SOBEL_Y_5X5_08S, 2},
{4, 8, 352, 0, 1, gScenarioBufferData82_SOBEL_Y_5X5_08S, 20, gScenarioKernelData82_SOBEL_Y_5X5_08S, 2},
{6, 8, 456, 0, 1, gScenarioBufferData83_SOBEL_Y_5X5_08S, 20, gScenarioKernelData83_SOBEL_Y_5X5_08S, 2},
{8, 8, 560, 0, 1, gScenarioBufferData84_SOBEL_Y_5X5_08S, 20, gScenarioKernelData84_SOBEL_Y_5X5_08S, 2},
{10, 8, 664, 0, 1, gScenarioBufferData85_SOBEL_Y_5X5_08S, 20, gScenarioKernelData85_SOBEL_Y_5X5_08S, 2},
{12, 8, 768, 0, 1, gScenarioBufferData86_SOBEL_Y_5X5_08S, 20, gScenarioKernelData86_SOBEL_Y_5X5_08S, 2},
{14, 8, 872, 0, 1, gScenarioBufferData87_SOBEL_Y_5X5_08S, 20, gScenarioKernelData87_SOBEL_Y_5X5_08S, 2},
{16, 8, 976, 0, 1, gScenarioBufferData88_SOBEL_Y_5X5_08S, 20, gScenarioKernelData88_SOBEL_Y_5X5_08S, 2},
{18, 8, 1080, 0, 1, gScenarioBufferData89_SOBEL_Y_5X5_08S, 20, gScenarioKernelData89_SOBEL_Y_5X5_08S, 2},
{20, 8, 1184, 0, 1, gScenarioBufferData90_SOBEL_Y_5X5_08S, 20, gScenarioKernelData90_SOBEL_Y_5X5_08S, 2},
{22, 8, 1288, 0, 1, gScenarioBufferData91_SOBEL_Y_5X5_08S, 20, gScenarioKernelData91_SOBEL_Y_5X5_08S, 2},
{24, 8, 1392, 0, 1, gScenarioBufferData92_SOBEL_Y_5X5_08S, 20, gScenarioKernelData92_SOBEL_Y_5X5_08S, 2},
{26, 8, 1496, 0, 1, gScenarioBufferData93_SOBEL_Y_5X5_08S, 20, gScenarioKernelData93_SOBEL_Y_5X5_08S, 2},
{28, 8, 1600, 0, 1, gScenarioBufferData94_SOBEL_Y_5X5_08S, 20, gScenarioKernelData94_SOBEL_Y_5X5_08S, 2},
{30, 8, 1704, 0, 1, gScenarioBufferData95_SOBEL_Y_5X5_08S, 20, gScenarioKernelData95_SOBEL_Y_5X5_08S, 2},
{32, 8, 1808, 0, 1, gScenarioBufferData96_SOBEL_Y_5X5_08S, 20, gScenarioKernelData96_SOBEL_Y_5X5_08S, 2},
{48, 8, 2640, 0, 1, gScenarioBufferData97_SOBEL_Y_5X5_08S, 20, gScenarioKernelData97_SOBEL_Y_5X5_08S, 2},
{64, 8, 3472, 0, 1, gScenarioBufferData98_SOBEL_Y_5X5_08S, 20, gScenarioKernelData98_SOBEL_Y_5X5_08S, 2},
{2, 10, 304, 0, 1, gScenarioBufferData99_SOBEL_Y_5X5_08S, 20, gScenarioKernelData99_SOBEL_Y_5X5_08S, 2},
{4, 10, 432, 0, 1, gScenarioBufferData100_SOBEL_Y_5X5_08S, 20, gScenarioKernelData100_SOBEL_Y_5X5_08S, 2},
{6, 10, 560, 0, 1, gScenarioBufferData101_SOBEL_Y_5X5_08S, 20, gScenarioKernelData101_SOBEL_Y_5X5_08S, 2},
{8, 10, 688, 0, 1, gScenarioBufferData102_SOBEL_Y_5X5_08S, 20, gScenarioKernelData102_SOBEL_Y_5X5_08S, 2},
{10, 10, 816, 0, 1, gScenarioBufferData103_SOBEL_Y_5X5_08S, 20, gScenarioKernelData103_SOBEL_Y_5X5_08S, 2},
{12, 10, 944, 0, 1, gScenarioBufferData104_SOBEL_Y_5X5_08S, 20, gScenarioKernelData104_SOBEL_Y_5X5_08S, 2},
{14, 10, 1072, 0, 1, gScenarioBufferData105_SOBEL_Y_5X5_08S, 20, gScenarioKernelData105_SOBEL_Y_5X5_08S, 2},
{16, 10, 1200, 0, 1, gScenarioBufferData106_SOBEL_Y_5X5_08S, 20, gScenarioKernelData106_SOBEL_Y_5X5_08S, 2},
{18, 10, 1328, 0, 1, gScenarioBufferData107_SOBEL_Y_5X5_08S, 20, gScenarioKernelData107_SOBEL_Y_5X5_08S, 2},
{20, 10, 1456, 0, 1, gScenarioBufferData108_SOBEL_Y_5X5_08S, 20, gScenarioKernelData108_SOBEL_Y_5X5_08S, 2},
{22, 10, 1584, 0, 1, gScenarioBufferData109_SOBEL_Y_5X5_08S, 20, gScenarioKernelData109_SOBEL_Y_5X5_08S, 2},
{24, 10, 1712, 0, 1, gScenarioBufferData110_SOBEL_Y_5X5_08S, 20, gScenarioKernelData110_SOBEL_Y_5X5_08S, 2},
{26, 10, 1840, 0, 1, gScenarioBufferData111_SOBEL_Y_5X5_08S, 20, gScenarioKernelData111_SOBEL_Y_5X5_08S, 2},
{28, 10, 1968, 0, 1, gScenarioBufferData112_SOBEL_Y_5X5_08S, 20, gScenarioKernelData112_SOBEL_Y_5X5_08S, 2},
{30, 10, 2096, 0, 1, gScenarioBufferData113_SOBEL_Y_5X5_08S, 20, gScenarioKernelData113_SOBEL_Y_5X5_08S, 2},
{32, 10, 2224, 0, 1, gScenarioBufferData114_SOBEL_Y_5X5_08S, 20, gScenarioKernelData114_SOBEL_Y_5X5_08S, 2},
{48, 10, 3248, 0, 1, gScenarioBufferData115_SOBEL_Y_5X5_08S, 20, gScenarioKernelData115_SOBEL_Y_5X5_08S, 2},
{2, 12, 360, 0, 1, gScenarioBufferData116_SOBEL_Y_5X5_08S, 20, gScenarioKernelData116_SOBEL_Y_5X5_08S, 2},
{4, 12, 512, 0, 1, gScenarioBufferData117_SOBEL_Y_5X5_08S, 20, gScenarioKernelData117_SOBEL_Y_5X5_08S, 2},
{6, 12, 664, 0, 1, gScenarioBufferData118_SOBEL_Y_5X5_08S, 20, gScenarioKernelData118_SOBEL_Y_5X5_08S, 2},
{8, 12, 816, 0, 1, gScenarioBufferData119_SOBEL_Y_5X5_08S, 20, gScenarioKernelData119_SOBEL_Y_5X5_08S, 2},
{10, 12, 968, 0, 1, gScenarioBufferData120_SOBEL_Y_5X5_08S, 20, gScenarioKernelData120_SOBEL_Y_5X5_08S, 2},
{12, 12, 1120, 0, 1, gScenarioBufferData121_SOBEL_Y_5X5_08S, 20, gScenarioKernelData121_SOBEL_Y_5X5_08S, 2},
{14, 12, 1272, 0, 1, gScenarioBufferData122_SOBEL_Y_5X5_08S, 20, gScenarioKernelData122_SOBEL_Y_5X5_08S, 2},
{16, 12, 1424, 0, 1, gScenarioBufferData123_SOBEL_Y_5X5_08S, 20, gScenarioKernelData123_SOBEL_Y_5X5_08S, 2},
{18, 12, 1576, 0, 1, gScenarioBufferData124_SOBEL_Y_5X5_08S, 20, gScenarioKernelData124_SOBEL_Y_5X5_08S, 2},
{20, 12, 1728, 0, 1, gScenarioBufferData125_SOBEL_Y_5X5_08S, 20, gScenarioKernelData125_SOBEL_Y_5X5_08S, 2},
{22, 12, 1880, 0, 1, gScenarioBufferData126_SOBEL_Y_5X5_08S, 20, gScenarioKernelData126_SOBEL_Y_5X5_08S, 2},
{24, 12, 2032, 0, 1, gScenarioBufferData127_SOBEL_Y_5X5_08S, 20, gScenarioKernelData127_SOBEL_Y_5X5_08S, 2},
{26, 12, 2184, 0, 1, gScenarioBufferData128_SOBEL_Y_5X5_08S, 20, gScenarioKernelData128_SOBEL_Y_5X5_08S, 2},
{28, 12, 2336, 0, 1, gScenarioBufferData129_SOBEL_Y_5X5_08S, 20, gScenarioKernelData129_SOBEL_Y_5X5_08S, 2},
{30, 12, 2488, 0, 1, gScenarioBufferData130_SOBEL_Y_5X5_08S, 20, gScenarioKernelData130_SOBEL_Y_5X5_08S, 2},
{32, 12, 2640, 0, 1, gScenarioBufferData131_SOBEL_Y_5X5_08S, 20, gScenarioKernelData131_SOBEL_Y_5X5_08S, 2},
{2, 14, 416, 0, 1, gScenarioBufferData132_SOBEL_Y_5X5_08S, 20, gScenarioKernelData132_SOBEL_Y_5X5_08S, 2},
{4, 14, 592, 0, 1, gScenarioBufferData133_SOBEL_Y_5X5_08S, 20, gScenarioKernelData133_SOBEL_Y_5X5_08S, 2},
{6, 14, 768, 0, 1, gScenarioBufferData134_SOBEL_Y_5X5_08S, 20, gScenarioKernelData134_SOBEL_Y_5X5_08S, 2},
{8, 14, 944, 0, 1, gScenarioBufferData135_SOBEL_Y_5X5_08S, 20, gScenarioKernelData135_SOBEL_Y_5X5_08S, 2},
{10, 14, 1120, 0, 1, gScenarioBufferData136_SOBEL_Y_5X5_08S, 20, gScenarioKernelData136_SOBEL_Y_5X5_08S, 2},
{12, 14, 1296, 0, 1, gScenarioBufferData137_SOBEL_Y_5X5_08S, 20, gScenarioKernelData137_SOBEL_Y_5X5_08S, 2},
{14, 14, 1472, 0, 1, gScenarioBufferData138_SOBEL_Y_5X5_08S, 20, gScenarioKernelData138_SOBEL_Y_5X5_08S, 2},
{16, 14, 1648, 0, 1, gScenarioBufferData139_SOBEL_Y_5X5_08S, 20, gScenarioKernelData139_SOBEL_Y_5X5_08S, 2},
{18, 14, 1824, 0, 1, gScenarioBufferData140_SOBEL_Y_5X5_08S, 20, gScenarioKernelData140_SOBEL_Y_5X5_08S, 2},
{20, 14, 2000, 0, 1, gScenarioBufferData141_SOBEL_Y_5X5_08S, 20, gScenarioKernelData141_SOBEL_Y_5X5_08S, 2},
{22, 14, 2176, 0, 1, gScenarioBufferData142_SOBEL_Y_5X5_08S, 20, gScenarioKernelData142_SOBEL_Y_5X5_08S, 2},
{24, 14, 2352, 0, 1, gScenarioBufferData143_SOBEL_Y_5X5_08S, 20, gScenarioKernelData143_SOBEL_Y_5X5_08S, 2},
{26, 14, 2528, 0, 1, gScenarioBufferData144_SOBEL_Y_5X5_08S, 20, gScenarioKernelData144_SOBEL_Y_5X5_08S, 2},
{28, 14, 2704, 0, 1, gScenarioBufferData145_SOBEL_Y_5X5_08S, 20, gScenarioKernelData145_SOBEL_Y_5X5_08S, 2},
{30, 14, 2880, 0, 1, gScenarioBufferData146_SOBEL_Y_5X5_08S, 20, gScenarioKernelData146_SOBEL_Y_5X5_08S, 2},
{32, 14, 3056, 0, 1, gScenarioBufferData147_SOBEL_Y_5X5_08S, 20, gScenarioKernelData147_SOBEL_Y_5X5_08S, 2},
{2, 16, 472, 0, 1, gScenarioBufferData148_SOBEL_Y_5X5_08S, 20, gScenarioKernelData148_SOBEL_Y_5X5_08S, 2},
{4, 16, 672, 0, 1, gScenarioBufferData149_SOBEL_Y_5X5_08S, 20, gScenarioKernelData149_SOBEL_Y_5X5_08S, 2},
{6, 16, 872, 0, 1, gScenarioBufferData150_SOBEL_Y_5X5_08S, 20, gScenarioKernelData150_SOBEL_Y_5X5_08S, 2},
{8, 16, 1072, 0, 1, gScenarioBufferData151_SOBEL_Y_5X5_08S, 20, gScenarioKernelData151_SOBEL_Y_5X5_08S, 2},
{10, 16, 1272, 0, 1, gScenarioBufferData152_SOBEL_Y_5X5_08S, 20, gScenarioKernelData152_SOBEL_Y_5X5_08S, 2},
{12, 16, 1472, 0, 1, gScenarioBufferData153_SOBEL_Y_5X5_08S, 20, gScenarioKernelData153_SOBEL_Y_5X5_08S, 2},
{14, 16, 1672, 0, 1, gScenarioBufferData154_SOBEL_Y_5X5_08S, 20, gScenarioKernelData154_SOBEL_Y_5X5_08S, 2},
{16, 16, 1872, 0, 1, gScenarioBufferData155_SOBEL_Y_5X5_08S, 20, gScenarioKernelData155_SOBEL_Y_5X5_08S, 2},
{18, 16, 2072, 0, 1, gScenarioBufferData156_SOBEL_Y_5X5_08S, 20, gScenarioKernelData156_SOBEL_Y_5X5_08S, 2},
{20, 16, 2272, 0, 1, gScenarioBufferData157_SOBEL_Y_5X5_08S, 20, gScenarioKernelData157_SOBEL_Y_5X5_08S, 2},
{22, 16, 2472, 0, 1, gScenarioBufferData158_SOBEL_Y_5X5_08S, 20, gScenarioKernelData158_SOBEL_Y_5X5_08S, 2},
{24, 16, 2672, 0, 1, gScenarioBufferData159_SOBEL_Y_5X5_08S, 20, gScenarioKernelData159_SOBEL_Y_5X5_08S, 2},
{26, 16, 2872, 0, 1, gScenarioBufferData160_SOBEL_Y_5X5_08S, 20, gScenarioKernelData160_SOBEL_Y_5X5_08S, 2},
{28, 16, 3072, 0, 1, gScenarioBufferData161_SOBEL_Y_5X5_08S, 20, gScenarioKernelData161_SOBEL_Y_5X5_08S, 2},
{30, 16, 3272, 0, 1, gScenarioBufferData162_SOBEL_Y_5X5_08S, 20, gScenarioKernelData162_SOBEL_Y_5X5_08S, 2},
{32, 16, 3472, 0, 1, gScenarioBufferData163_SOBEL_Y_5X5_08S, 20, gScenarioKernelData163_SOBEL_Y_5X5_08S, 2},
{2, 18, 528, 0, 1, gScenarioBufferData164_SOBEL_Y_5X5_08S, 20, gScenarioKernelData164_SOBEL_Y_5X5_08S, 2},
{4, 18, 752, 0, 1, gScenarioBufferData165_SOBEL_Y_5X5_08S, 20, gScenarioKernelData165_SOBEL_Y_5X5_08S, 2},
{6, 18, 976, 0, 1, gScenarioBufferData166_SOBEL_Y_5X5_08S, 20, gScenarioKernelData166_SOBEL_Y_5X5_08S, 2},
{8, 18, 1200, 0, 1, gScenarioBufferData167_SOBEL_Y_5X5_08S, 20, gScenarioKernelData167_SOBEL_Y_5X5_08S, 2},
{10, 18, 1424, 0, 1, gScenarioBufferData168_SOBEL_Y_5X5_08S, 20, gScenarioKernelData168_SOBEL_Y_5X5_08S, 2},
{12, 18, 1648, 0, 1, gScenarioBufferData169_SOBEL_Y_5X5_08S, 20, gScenarioKernelData169_SOBEL_Y_5X5_08S, 2},
{14, 18, 1872, 0, 1, gScenarioBufferData170_SOBEL_Y_5X5_08S, 20, gScenarioKernelData170_SOBEL_Y_5X5_08S, 2},
{16, 18, 2096, 0, 1, gScenarioBufferData171_SOBEL_Y_5X5_08S, 20, gScenarioKernelData171_SOBEL_Y_5X5_08S, 2},
{18, 18, 2320, 0, 1, gScenarioBufferData172_SOBEL_Y_5X5_08S, 20, gScenarioKernelData172_SOBEL_Y_5X5_08S, 2},
{20, 18, 2544, 0, 1, gScenarioBufferData173_SOBEL_Y_5X5_08S, 20, gScenarioKernelData173_SOBEL_Y_5X5_08S, 2},
{22, 18, 2768, 0, 1, gScenarioBufferData174_SOBEL_Y_5X5_08S, 20, gScenarioKernelData174_SOBEL_Y_5X5_08S, 2},
{24, 18, 2992, 0, 1, gScenarioBufferData175_SOBEL_Y_5X5_08S, 20, gScenarioKernelData175_SOBEL_Y_5X5_08S, 2},
{26, 18, 3216, 0, 1, gScenarioBufferData176_SOBEL_Y_5X5_08S, 20, gScenarioKernelData176_SOBEL_Y_5X5_08S, 2},
{28, 18, 3440, 0, 1, gScenarioBufferData177_SOBEL_Y_5X5_08S, 20, gScenarioKernelData177_SOBEL_Y_5X5_08S, 2},
{30, 18, 3664, 0, 1, gScenarioBufferData178_SOBEL_Y_5X5_08S, 20, gScenarioKernelData178_SOBEL_Y_5X5_08S, 2},
{2, 20, 584, 0, 1, gScenarioBufferData179_SOBEL_Y_5X5_08S, 20, gScenarioKernelData179_SOBEL_Y_5X5_08S, 2},
{4, 20, 832, 0, 1, gScenarioBufferData180_SOBEL_Y_5X5_08S, 20, gScenarioKernelData180_SOBEL_Y_5X5_08S, 2},
{6, 20, 1080, 0, 1, gScenarioBufferData181_SOBEL_Y_5X5_08S, 20, gScenarioKernelData181_SOBEL_Y_5X5_08S, 2},
{8, 20, 1328, 0, 1, gScenarioBufferData182_SOBEL_Y_5X5_08S, 20, gScenarioKernelData182_SOBEL_Y_5X5_08S, 2},
{10, 20, 1576, 0, 1, gScenarioBufferData183_SOBEL_Y_5X5_08S, 20, gScenarioKernelData183_SOBEL_Y_5X5_08S, 2},
{12, 20, 1824, 0, 1, gScenarioBufferData184_SOBEL_Y_5X5_08S, 20, gScenarioKernelData184_SOBEL_Y_5X5_08S, 2},
{14, 20, 2072, 0, 1, gScenarioBufferData185_SOBEL_Y_5X5_08S, 20, gScenarioKernelData185_SOBEL_Y_5X5_08S, 2},
{16, 20, 2320, 0, 1, gScenarioBufferData186_SOBEL_Y_5X5_08S, 20, gScenarioKernelData186_SOBEL_Y_5X5_08S, 2},
{18, 20, 2568, 0, 1, gScenarioBufferData187_SOBEL_Y_5X5_08S, 20, gScenarioKernelData187_SOBEL_Y_5X5_08S, 2},
{20, 20, 2816, 0, 1, gScenarioBufferData188_SOBEL_Y_5X5_08S, 20, gScenarioKernelData188_SOBEL_Y_5X5_08S, 2},
{22, 20, 3064, 0, 1, gScenarioBufferData189_SOBEL_Y_5X5_08S, 20, gScenarioKernelData189_SOBEL_Y_5X5_08S, 2},
{24, 20, 3312, 0, 1, gScenarioBufferData190_SOBEL_Y_5X5_08S, 20, gScenarioKernelData190_SOBEL_Y_5X5_08S, 2},
{26, 20, 3560, 0, 1, gScenarioBufferData191_SOBEL_Y_5X5_08S, 20, gScenarioKernelData191_SOBEL_Y_5X5_08S, 2},
{28, 20, 3808, 0, 1, gScenarioBufferData192_SOBEL_Y_5X5_08S, 20, gScenarioKernelData192_SOBEL_Y_5X5_08S, 2},
{2, 22, 640, 0, 1, gScenarioBufferData193_SOBEL_Y_5X5_08S, 20, gScenarioKernelData193_SOBEL_Y_5X5_08S, 2},
{4, 22, 912, 0, 1, gScenarioBufferData194_SOBEL_Y_5X5_08S, 20, gScenarioKernelData194_SOBEL_Y_5X5_08S, 2},
{6, 22, 1184, 0, 1, gScenarioBufferData195_SOBEL_Y_5X5_08S, 20, gScenarioKernelData195_SOBEL_Y_5X5_08S, 2},
{8, 22, 1456, 0, 1, gScenarioBufferData196_SOBEL_Y_5X5_08S, 20, gScenarioKernelData196_SOBEL_Y_5X5_08S, 2},
{10, 22, 1728, 0, 1, gScenarioBufferData197_SOBEL_Y_5X5_08S, 20, gScenarioKernelData197_SOBEL_Y_5X5_08S, 2},
{12, 22, 2000, 0, 1, gScenarioBufferData198_SOBEL_Y_5X5_08S, 20, gScenarioKernelData198_SOBEL_Y_5X5_08S, 2},
{14, 22, 2272, 0, 1, gScenarioBufferData199_SOBEL_Y_5X5_08S, 20, gScenarioKernelData199_SOBEL_Y_5X5_08S, 2},
{16, 22, 2544, 0, 1, gScenarioBufferData200_SOBEL_Y_5X5_08S, 20, gScenarioKernelData200_SOBEL_Y_5X5_08S, 2},
{18, 22, 2816, 0, 1, gScenarioBufferData201_SOBEL_Y_5X5_08S, 20, gScenarioKernelData201_SOBEL_Y_5X5_08S, 2},
{20, 22, 3088, 0, 1, gScenarioBufferData202_SOBEL_Y_5X5_08S, 20, gScenarioKernelData202_SOBEL_Y_5X5_08S, 2},
{22, 22, 3360, 0, 1, gScenarioBufferData203_SOBEL_Y_5X5_08S, 20, gScenarioKernelData203_SOBEL_Y_5X5_08S, 2},
{24, 22, 3632, 0, 1, gScenarioBufferData204_SOBEL_Y_5X5_08S, 20, gScenarioKernelData204_SOBEL_Y_5X5_08S, 2},
{2, 24, 696, 0, 1, gScenarioBufferData205_SOBEL_Y_5X5_08S, 20, gScenarioKernelData205_SOBEL_Y_5X5_08S, 2},
{4, 24, 992, 0, 1, gScenarioBufferData206_SOBEL_Y_5X5_08S, 20, gScenarioKernelData206_SOBEL_Y_5X5_08S, 2},
{6, 24, 1288, 0, 1, gScenarioBufferData207_SOBEL_Y_5X5_08S, 20, gScenarioKernelData207_SOBEL_Y_5X5_08S, 2},
{8, 24, 1584, 0, 1, gScenarioBufferData208_SOBEL_Y_5X5_08S, 20, gScenarioKernelData208_SOBEL_Y_5X5_08S, 2},
{10, 24, 1880, 0, 1, gScenarioBufferData209_SOBEL_Y_5X5_08S, 20, gScenarioKernelData209_SOBEL_Y_5X5_08S, 2},
{12, 24, 2176, 0, 1, gScenarioBufferData210_SOBEL_Y_5X5_08S, 20, gScenarioKernelData210_SOBEL_Y_5X5_08S, 2},
{14, 24, 2472, 0, 1, gScenarioBufferData211_SOBEL_Y_5X5_08S, 20, gScenarioKernelData211_SOBEL_Y_5X5_08S, 2},
{16, 24, 2768, 0, 1, gScenarioBufferData212_SOBEL_Y_5X5_08S, 20, gScenarioKernelData212_SOBEL_Y_5X5_08S, 2},
{18, 24, 3064, 0, 1, gScenarioBufferData213_SOBEL_Y_5X5_08S, 20, gScenarioKernelData213_SOBEL_Y_5X5_08S, 2},
{20, 24, 3360, 0, 1, gScenarioBufferData214_SOBEL_Y_5X5_08S, 20, gScenarioKernelData214_SOBEL_Y_5X5_08S, 2},
{22, 24, 3656, 0, 1, gScenarioBufferData215_SOBEL_Y_5X5_08S, 20, gScenarioKernelData215_SOBEL_Y_5X5_08S, 2},
{2, 26, 752, 0, 1, gScenarioBufferData216_SOBEL_Y_5X5_08S, 20, gScenarioKernelData216_SOBEL_Y_5X5_08S, 2},
{4, 26, 1072, 0, 1, gScenarioBufferData217_SOBEL_Y_5X5_08S, 20, gScenarioKernelData217_SOBEL_Y_5X5_08S, 2},
{6, 26, 1392, 0, 1, gScenarioBufferData218_SOBEL_Y_5X5_08S, 20, gScenarioKernelData218_SOBEL_Y_5X5_08S, 2},
{8, 26, 1712, 0, 1, gScenarioBufferData219_SOBEL_Y_5X5_08S, 20, gScenarioKernelData219_SOBEL_Y_5X5_08S, 2},
{10, 26, 2032, 0, 1, gScenarioBufferData220_SOBEL_Y_5X5_08S, 20, gScenarioKernelData220_SOBEL_Y_5X5_08S, 2},
{12, 26, 2352, 0, 1, gScenarioBufferData221_SOBEL_Y_5X5_08S, 20, gScenarioKernelData221_SOBEL_Y_5X5_08S, 2},
{14, 26, 2672, 0, 1, gScenarioBufferData222_SOBEL_Y_5X5_08S, 20, gScenarioKernelData222_SOBEL_Y_5X5_08S, 2},
{16, 26, 2992, 0, 1, gScenarioBufferData223_SOBEL_Y_5X5_08S, 20, gScenarioKernelData223_SOBEL_Y_5X5_08S, 2},
{18, 26, 3312, 0, 1, gScenarioBufferData224_SOBEL_Y_5X5_08S, 20, gScenarioKernelData224_SOBEL_Y_5X5_08S, 2},
{20, 26, 3632, 0, 1, gScenarioBufferData225_SOBEL_Y_5X5_08S, 20, gScenarioKernelData225_SOBEL_Y_5X5_08S, 2},
{2, 28, 808, 0, 1, gScenarioBufferData226_SOBEL_Y_5X5_08S, 20, gScenarioKernelData226_SOBEL_Y_5X5_08S, 2},
{4, 28, 1152, 0, 1, gScenarioBufferData227_SOBEL_Y_5X5_08S, 20, gScenarioKernelData227_SOBEL_Y_5X5_08S, 2},
{6, 28, 1496, 0, 1, gScenarioBufferData228_SOBEL_Y_5X5_08S, 20, gScenarioKernelData228_SOBEL_Y_5X5_08S, 2},
{8, 28, 1840, 0, 1, gScenarioBufferData229_SOBEL_Y_5X5_08S, 20, gScenarioKernelData229_SOBEL_Y_5X5_08S, 2},
{10, 28, 2184, 0, 1, gScenarioBufferData230_SOBEL_Y_5X5_08S, 20, gScenarioKernelData230_SOBEL_Y_5X5_08S, 2},
{12, 28, 2528, 0, 1, gScenarioBufferData231_SOBEL_Y_5X5_08S, 20, gScenarioKernelData231_SOBEL_Y_5X5_08S, 2},
{14, 28, 2872, 0, 1, gScenarioBufferData232_SOBEL_Y_5X5_08S, 20, gScenarioKernelData232_SOBEL_Y_5X5_08S, 2},
{16, 28, 3216, 0, 1, gScenarioBufferData233_SOBEL_Y_5X5_08S, 20, gScenarioKernelData233_SOBEL_Y_5X5_08S, 2},
{18, 28, 3560, 0, 1, gScenarioBufferData234_SOBEL_Y_5X5_08S, 20, gScenarioKernelData234_SOBEL_Y_5X5_08S, 2},
{2, 30, 864, 0, 1, gScenarioBufferData235_SOBEL_Y_5X5_08S, 20, gScenarioKernelData235_SOBEL_Y_5X5_08S, 2},
{4, 30, 1232, 0, 1, gScenarioBufferData236_SOBEL_Y_5X5_08S, 20, gScenarioKernelData236_SOBEL_Y_5X5_08S, 2},
{6, 30, 1600, 0, 1, gScenarioBufferData237_SOBEL_Y_5X5_08S, 20, gScenarioKernelData237_SOBEL_Y_5X5_08S, 2},
{8, 30, 1968, 0, 1, gScenarioBufferData238_SOBEL_Y_5X5_08S, 20, gScenarioKernelData238_SOBEL_Y_5X5_08S, 2},
{10, 30, 2336, 0, 1, gScenarioBufferData239_SOBEL_Y_5X5_08S, 20, gScenarioKernelData239_SOBEL_Y_5X5_08S, 2},
{12, 30, 2704, 0, 1, gScenarioBufferData240_SOBEL_Y_5X5_08S, 20, gScenarioKernelData240_SOBEL_Y_5X5_08S, 2},
{14, 30, 3072, 0, 1, gScenarioBufferData241_SOBEL_Y_5X5_08S, 20, gScenarioKernelData241_SOBEL_Y_5X5_08S, 2},
{16, 30, 3440, 0, 1, gScenarioBufferData242_SOBEL_Y_5X5_08S, 20, gScenarioKernelData242_SOBEL_Y_5X5_08S, 2},
{18, 30, 3808, 0, 1, gScenarioBufferData243_SOBEL_Y_5X5_08S, 20, gScenarioKernelData243_SOBEL_Y_5X5_08S, 2},
{2, 32, 920, 0, 1, gScenarioBufferData244_SOBEL_Y_5X5_08S, 20, gScenarioKernelData244_SOBEL_Y_5X5_08S, 2},
{4, 32, 1312, 0, 1, gScenarioBufferData245_SOBEL_Y_5X5_08S, 20, gScenarioKernelData245_SOBEL_Y_5X5_08S, 2},
{6, 32, 1704, 0, 1, gScenarioBufferData246_SOBEL_Y_5X5_08S, 20, gScenarioKernelData246_SOBEL_Y_5X5_08S, 2},
{8, 32, 2096, 0, 1, gScenarioBufferData247_SOBEL_Y_5X5_08S, 20, gScenarioKernelData247_SOBEL_Y_5X5_08S, 2},
{10, 32, 2488, 0, 1, gScenarioBufferData248_SOBEL_Y_5X5_08S, 20, gScenarioKernelData248_SOBEL_Y_5X5_08S, 2},
{12, 32, 2880, 0, 1, gScenarioBufferData249_SOBEL_Y_5X5_08S, 20, gScenarioKernelData249_SOBEL_Y_5X5_08S, 2},
{14, 32, 3272, 0, 1, gScenarioBufferData250_SOBEL_Y_5X5_08S, 20, gScenarioKernelData250_SOBEL_Y_5X5_08S, 2},
{16, 32, 3664, 0, 1, gScenarioBufferData251_SOBEL_Y_5X5_08S, 20, gScenarioKernelData251_SOBEL_Y_5X5_08S, 2}
};

static acf_scenario_list gScenarioList_SOBEL_Y_5X5_08S = {
252, //number of scenarios
gScenarioArray_SOBEL_Y_5X5_08S};
//**************************************************************

class SOBEL_Y_5X5_08S : public ACF_Process_APU
{
public:
   SOBEL_Y_5X5_08S(int32_t apex_id = 0) : ACF_Process_APU(apex_id)
   {} 

   int32_t Initialize()
   {
      int32_t lRetVal = 0;

      if (!Initialized()) //initialization steps that only need to occur once
      {
         SetProcessIdentifier("SOBEL_Y_5X5_08S");
         SetApuLoadInfo(SOBEL_Y_5X5_08S_LOAD_SEGMENTS,
                        SOBEL_Y_5X5_08S_LOAD_PMEM, SOBEL_Y_5X5_08S_LOAD_PMEM_SIZE,
                        SOBEL_Y_5X5_08S_LOAD_DMEM, SOBEL_Y_5X5_08S_LOAD_DMEM_SIZE,
                        0, 0); //assuming _LOAD_CMEM does not exist
         FlagSpatialDep();

         //***NOTE: the order in which the following ports are added is meaningful; do not change!

         AddPort("INPUT_0", ICP_DATATYPE_08U, 1, 1, 2, 1, 0, 0, 0, 0, 0, 0, 0, 0x2020202);
         AddPort("OUTPUT_0", ICP_DATATYPE_08S, 1, 1, 2, 1, 1, 0, 0, 0, 0, 0, 1);

         CfgScenarios(&gScenarioList_SOBEL_Y_5X5_08S);

         FlagAsInitialized();
      }

      lRetVal = SelectApuConfiguration(mApuCfg, mApexId); //by default mApuCfg = ACF_APU_CFG__APEX0_DEFAULT and mApexId = 0

      return lRetVal;
   }
};

#endif //_ACF_PROCESS_APU_SOBEL_Y_5X5_08S
