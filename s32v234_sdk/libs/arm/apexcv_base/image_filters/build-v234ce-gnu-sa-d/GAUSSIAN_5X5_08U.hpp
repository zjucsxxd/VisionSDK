#ifndef _ACF_PROCESS_APU_GAUSSIAN_5X5_08U
#define _ACF_PROCESS_APU_GAUSSIAN_5X5_08U

#include <acf_process_apu.h>
#include <GAUSSIAN_5X5_08U_APU_LOAD.h> //APU load associated with this process
#include <stdint.h>


//SCENARIO LIST*************************************************
static acf_scenario_buffer_data gScenarioBufferData0_GAUSSIAN_5X5_08U[] = {{2, 1, 7, 0, 0x2222}, {2, 1, 2, 2, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData1_GAUSSIAN_5X5_08U[] = {{4, 1, 7, 0, 0x2222}, {4, 1, 2, 2, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData2_GAUSSIAN_5X5_08U[] = {{6, 1, 7, 0, 0x2222}, {6, 1, 2, 2, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData3_GAUSSIAN_5X5_08U[] = {{8, 1, 7, 0, 0x2222}, {8, 1, 2, 2, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData4_GAUSSIAN_5X5_08U[] = {{10, 1, 7, 0, 0x2222}, {10, 1, 2, 2, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData5_GAUSSIAN_5X5_08U[] = {{12, 1, 7, 0, 0x2222}, {12, 1, 2, 2, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData6_GAUSSIAN_5X5_08U[] = {{14, 1, 7, 0, 0x2222}, {14, 1, 2, 2, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData7_GAUSSIAN_5X5_08U[] = {{16, 1, 7, 0, 0x2222}, {16, 1, 2, 2, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData8_GAUSSIAN_5X5_08U[] = {{18, 1, 7, 0, 0x2222}, {18, 1, 2, 2, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData9_GAUSSIAN_5X5_08U[] = {{20, 1, 7, 0, 0x2222}, {20, 1, 2, 2, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData10_GAUSSIAN_5X5_08U[] = {{22, 1, 7, 0, 0x2222}, {22, 1, 2, 2, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData11_GAUSSIAN_5X5_08U[] = {{24, 1, 7, 0, 0x2222}, {24, 1, 2, 2, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData12_GAUSSIAN_5X5_08U[] = {{26, 1, 7, 0, 0x2222}, {26, 1, 2, 2, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData13_GAUSSIAN_5X5_08U[] = {{28, 1, 7, 0, 0x2222}, {28, 1, 2, 2, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData14_GAUSSIAN_5X5_08U[] = {{30, 1, 7, 0, 0x2222}, {30, 1, 2, 2, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData15_GAUSSIAN_5X5_08U[] = {{32, 1, 7, 0, 0x2222}, {32, 1, 2, 2, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData16_GAUSSIAN_5X5_08U[] = {{48, 1, 7, 0, 0x2222}, {48, 1, 2, 2, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData17_GAUSSIAN_5X5_08U[] = {{64, 1, 7, 0, 0x2222}, {64, 1, 2, 2, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData18_GAUSSIAN_5X5_08U[] = {{96, 1, 7, 0, 0x2222}, {96, 1, 2, 2, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData19_GAUSSIAN_5X5_08U[] = {{112, 1, 7, 0, 0x2222}, {112, 1, 2, 2, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData20_GAUSSIAN_5X5_08U[] = {{128, 1, 7, 0, 0x2222}, {128, 1, 2, 2, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData21_GAUSSIAN_5X5_08U[] = {{2, 2, 4, 0, 0x2222}, {2, 2, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData22_GAUSSIAN_5X5_08U[] = {{4, 2, 4, 0, 0x2222}, {4, 2, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData23_GAUSSIAN_5X5_08U[] = {{6, 2, 4, 0, 0x2222}, {6, 2, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData24_GAUSSIAN_5X5_08U[] = {{8, 2, 4, 0, 0x2222}, {8, 2, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData25_GAUSSIAN_5X5_08U[] = {{10, 2, 4, 0, 0x2222}, {10, 2, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData26_GAUSSIAN_5X5_08U[] = {{12, 2, 4, 0, 0x2222}, {12, 2, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData27_GAUSSIAN_5X5_08U[] = {{14, 2, 4, 0, 0x2222}, {14, 2, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData28_GAUSSIAN_5X5_08U[] = {{16, 2, 4, 0, 0x2222}, {16, 2, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData29_GAUSSIAN_5X5_08U[] = {{18, 2, 4, 0, 0x2222}, {18, 2, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData30_GAUSSIAN_5X5_08U[] = {{20, 2, 4, 0, 0x2222}, {20, 2, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData31_GAUSSIAN_5X5_08U[] = {{22, 2, 4, 0, 0x2222}, {22, 2, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData32_GAUSSIAN_5X5_08U[] = {{24, 2, 4, 0, 0x2222}, {24, 2, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData33_GAUSSIAN_5X5_08U[] = {{26, 2, 4, 0, 0x2222}, {26, 2, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData34_GAUSSIAN_5X5_08U[] = {{28, 2, 4, 0, 0x2222}, {28, 2, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData35_GAUSSIAN_5X5_08U[] = {{30, 2, 4, 0, 0x2222}, {30, 2, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData36_GAUSSIAN_5X5_08U[] = {{32, 2, 4, 0, 0x2222}, {32, 2, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData37_GAUSSIAN_5X5_08U[] = {{48, 2, 4, 0, 0x2222}, {48, 2, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData38_GAUSSIAN_5X5_08U[] = {{64, 2, 4, 0, 0x2222}, {64, 2, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData39_GAUSSIAN_5X5_08U[] = {{96, 2, 4, 0, 0x2222}, {96, 2, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData40_GAUSSIAN_5X5_08U[] = {{112, 2, 4, 0, 0x2222}, {112, 2, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData41_GAUSSIAN_5X5_08U[] = {{128, 2, 4, 0, 0x2222}, {128, 2, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData42_GAUSSIAN_5X5_08U[] = {{2, 4, 4, 0, 0x2222}, {2, 4, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData43_GAUSSIAN_5X5_08U[] = {{4, 4, 4, 0, 0x2222}, {4, 4, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData44_GAUSSIAN_5X5_08U[] = {{6, 4, 4, 0, 0x2222}, {6, 4, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData45_GAUSSIAN_5X5_08U[] = {{8, 4, 4, 0, 0x2222}, {8, 4, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData46_GAUSSIAN_5X5_08U[] = {{10, 4, 4, 0, 0x2222}, {10, 4, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData47_GAUSSIAN_5X5_08U[] = {{12, 4, 4, 0, 0x2222}, {12, 4, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData48_GAUSSIAN_5X5_08U[] = {{14, 4, 4, 0, 0x2222}, {14, 4, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData49_GAUSSIAN_5X5_08U[] = {{16, 4, 4, 0, 0x2222}, {16, 4, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData50_GAUSSIAN_5X5_08U[] = {{18, 4, 4, 0, 0x2222}, {18, 4, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData51_GAUSSIAN_5X5_08U[] = {{20, 4, 4, 0, 0x2222}, {20, 4, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData52_GAUSSIAN_5X5_08U[] = {{22, 4, 4, 0, 0x2222}, {22, 4, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData53_GAUSSIAN_5X5_08U[] = {{24, 4, 4, 0, 0x2222}, {24, 4, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData54_GAUSSIAN_5X5_08U[] = {{26, 4, 4, 0, 0x2222}, {26, 4, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData55_GAUSSIAN_5X5_08U[] = {{28, 4, 4, 0, 0x2222}, {28, 4, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData56_GAUSSIAN_5X5_08U[] = {{30, 4, 4, 0, 0x2222}, {30, 4, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData57_GAUSSIAN_5X5_08U[] = {{32, 4, 4, 0, 0x2222}, {32, 4, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData58_GAUSSIAN_5X5_08U[] = {{48, 4, 4, 0, 0x2222}, {48, 4, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData59_GAUSSIAN_5X5_08U[] = {{64, 4, 4, 0, 0x2222}, {64, 4, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData60_GAUSSIAN_5X5_08U[] = {{96, 4, 4, 0, 0x2222}, {96, 4, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData61_GAUSSIAN_5X5_08U[] = {{112, 4, 4, 0, 0x2222}, {112, 4, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData62_GAUSSIAN_5X5_08U[] = {{128, 4, 4, 0, 0x2222}, {128, 4, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData63_GAUSSIAN_5X5_08U[] = {{2, 6, 4, 0, 0x2222}, {2, 6, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData64_GAUSSIAN_5X5_08U[] = {{4, 6, 4, 0, 0x2222}, {4, 6, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData65_GAUSSIAN_5X5_08U[] = {{6, 6, 4, 0, 0x2222}, {6, 6, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData66_GAUSSIAN_5X5_08U[] = {{8, 6, 4, 0, 0x2222}, {8, 6, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData67_GAUSSIAN_5X5_08U[] = {{10, 6, 4, 0, 0x2222}, {10, 6, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData68_GAUSSIAN_5X5_08U[] = {{12, 6, 4, 0, 0x2222}, {12, 6, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData69_GAUSSIAN_5X5_08U[] = {{14, 6, 4, 0, 0x2222}, {14, 6, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData70_GAUSSIAN_5X5_08U[] = {{16, 6, 4, 0, 0x2222}, {16, 6, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData71_GAUSSIAN_5X5_08U[] = {{18, 6, 4, 0, 0x2222}, {18, 6, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData72_GAUSSIAN_5X5_08U[] = {{20, 6, 4, 0, 0x2222}, {20, 6, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData73_GAUSSIAN_5X5_08U[] = {{22, 6, 4, 0, 0x2222}, {22, 6, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData74_GAUSSIAN_5X5_08U[] = {{24, 6, 4, 0, 0x2222}, {24, 6, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData75_GAUSSIAN_5X5_08U[] = {{26, 6, 4, 0, 0x2222}, {26, 6, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData76_GAUSSIAN_5X5_08U[] = {{28, 6, 4, 0, 0x2222}, {28, 6, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData77_GAUSSIAN_5X5_08U[] = {{30, 6, 4, 0, 0x2222}, {30, 6, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData78_GAUSSIAN_5X5_08U[] = {{32, 6, 4, 0, 0x2222}, {32, 6, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData79_GAUSSIAN_5X5_08U[] = {{48, 6, 4, 0, 0x2222}, {48, 6, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData80_GAUSSIAN_5X5_08U[] = {{64, 6, 4, 0, 0x2222}, {64, 6, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData81_GAUSSIAN_5X5_08U[] = {{2, 8, 4, 0, 0x2222}, {2, 8, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData82_GAUSSIAN_5X5_08U[] = {{4, 8, 4, 0, 0x2222}, {4, 8, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData83_GAUSSIAN_5X5_08U[] = {{6, 8, 4, 0, 0x2222}, {6, 8, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData84_GAUSSIAN_5X5_08U[] = {{8, 8, 4, 0, 0x2222}, {8, 8, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData85_GAUSSIAN_5X5_08U[] = {{10, 8, 4, 0, 0x2222}, {10, 8, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData86_GAUSSIAN_5X5_08U[] = {{12, 8, 4, 0, 0x2222}, {12, 8, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData87_GAUSSIAN_5X5_08U[] = {{14, 8, 4, 0, 0x2222}, {14, 8, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData88_GAUSSIAN_5X5_08U[] = {{16, 8, 4, 0, 0x2222}, {16, 8, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData89_GAUSSIAN_5X5_08U[] = {{18, 8, 4, 0, 0x2222}, {18, 8, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData90_GAUSSIAN_5X5_08U[] = {{20, 8, 4, 0, 0x2222}, {20, 8, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData91_GAUSSIAN_5X5_08U[] = {{22, 8, 4, 0, 0x2222}, {22, 8, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData92_GAUSSIAN_5X5_08U[] = {{24, 8, 4, 0, 0x2222}, {24, 8, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData93_GAUSSIAN_5X5_08U[] = {{26, 8, 4, 0, 0x2222}, {26, 8, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData94_GAUSSIAN_5X5_08U[] = {{28, 8, 4, 0, 0x2222}, {28, 8, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData95_GAUSSIAN_5X5_08U[] = {{30, 8, 4, 0, 0x2222}, {30, 8, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData96_GAUSSIAN_5X5_08U[] = {{32, 8, 4, 0, 0x2222}, {32, 8, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData97_GAUSSIAN_5X5_08U[] = {{48, 8, 4, 0, 0x2222}, {48, 8, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData98_GAUSSIAN_5X5_08U[] = {{64, 8, 4, 0, 0x2222}, {64, 8, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData99_GAUSSIAN_5X5_08U[] = {{2, 10, 4, 0, 0x2222}, {2, 10, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData100_GAUSSIAN_5X5_08U[] = {{4, 10, 4, 0, 0x2222}, {4, 10, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData101_GAUSSIAN_5X5_08U[] = {{6, 10, 4, 0, 0x2222}, {6, 10, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData102_GAUSSIAN_5X5_08U[] = {{8, 10, 4, 0, 0x2222}, {8, 10, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData103_GAUSSIAN_5X5_08U[] = {{10, 10, 4, 0, 0x2222}, {10, 10, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData104_GAUSSIAN_5X5_08U[] = {{12, 10, 4, 0, 0x2222}, {12, 10, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData105_GAUSSIAN_5X5_08U[] = {{14, 10, 4, 0, 0x2222}, {14, 10, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData106_GAUSSIAN_5X5_08U[] = {{16, 10, 4, 0, 0x2222}, {16, 10, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData107_GAUSSIAN_5X5_08U[] = {{18, 10, 4, 0, 0x2222}, {18, 10, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData108_GAUSSIAN_5X5_08U[] = {{20, 10, 4, 0, 0x2222}, {20, 10, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData109_GAUSSIAN_5X5_08U[] = {{22, 10, 4, 0, 0x2222}, {22, 10, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData110_GAUSSIAN_5X5_08U[] = {{24, 10, 4, 0, 0x2222}, {24, 10, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData111_GAUSSIAN_5X5_08U[] = {{26, 10, 4, 0, 0x2222}, {26, 10, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData112_GAUSSIAN_5X5_08U[] = {{28, 10, 4, 0, 0x2222}, {28, 10, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData113_GAUSSIAN_5X5_08U[] = {{30, 10, 4, 0, 0x2222}, {30, 10, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData114_GAUSSIAN_5X5_08U[] = {{32, 10, 4, 0, 0x2222}, {32, 10, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData115_GAUSSIAN_5X5_08U[] = {{48, 10, 4, 0, 0x2222}, {48, 10, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData116_GAUSSIAN_5X5_08U[] = {{2, 12, 4, 0, 0x2222}, {2, 12, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData117_GAUSSIAN_5X5_08U[] = {{4, 12, 4, 0, 0x2222}, {4, 12, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData118_GAUSSIAN_5X5_08U[] = {{6, 12, 4, 0, 0x2222}, {6, 12, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData119_GAUSSIAN_5X5_08U[] = {{8, 12, 4, 0, 0x2222}, {8, 12, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData120_GAUSSIAN_5X5_08U[] = {{10, 12, 4, 0, 0x2222}, {10, 12, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData121_GAUSSIAN_5X5_08U[] = {{12, 12, 4, 0, 0x2222}, {12, 12, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData122_GAUSSIAN_5X5_08U[] = {{14, 12, 4, 0, 0x2222}, {14, 12, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData123_GAUSSIAN_5X5_08U[] = {{16, 12, 4, 0, 0x2222}, {16, 12, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData124_GAUSSIAN_5X5_08U[] = {{18, 12, 4, 0, 0x2222}, {18, 12, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData125_GAUSSIAN_5X5_08U[] = {{20, 12, 4, 0, 0x2222}, {20, 12, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData126_GAUSSIAN_5X5_08U[] = {{22, 12, 4, 0, 0x2222}, {22, 12, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData127_GAUSSIAN_5X5_08U[] = {{24, 12, 4, 0, 0x2222}, {24, 12, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData128_GAUSSIAN_5X5_08U[] = {{26, 12, 4, 0, 0x2222}, {26, 12, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData129_GAUSSIAN_5X5_08U[] = {{28, 12, 4, 0, 0x2222}, {28, 12, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData130_GAUSSIAN_5X5_08U[] = {{30, 12, 4, 0, 0x2222}, {30, 12, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData131_GAUSSIAN_5X5_08U[] = {{32, 12, 4, 0, 0x2222}, {32, 12, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData132_GAUSSIAN_5X5_08U[] = {{2, 14, 4, 0, 0x2222}, {2, 14, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData133_GAUSSIAN_5X5_08U[] = {{4, 14, 4, 0, 0x2222}, {4, 14, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData134_GAUSSIAN_5X5_08U[] = {{6, 14, 4, 0, 0x2222}, {6, 14, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData135_GAUSSIAN_5X5_08U[] = {{8, 14, 4, 0, 0x2222}, {8, 14, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData136_GAUSSIAN_5X5_08U[] = {{10, 14, 4, 0, 0x2222}, {10, 14, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData137_GAUSSIAN_5X5_08U[] = {{12, 14, 4, 0, 0x2222}, {12, 14, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData138_GAUSSIAN_5X5_08U[] = {{14, 14, 4, 0, 0x2222}, {14, 14, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData139_GAUSSIAN_5X5_08U[] = {{16, 14, 4, 0, 0x2222}, {16, 14, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData140_GAUSSIAN_5X5_08U[] = {{18, 14, 4, 0, 0x2222}, {18, 14, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData141_GAUSSIAN_5X5_08U[] = {{20, 14, 4, 0, 0x2222}, {20, 14, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData142_GAUSSIAN_5X5_08U[] = {{22, 14, 4, 0, 0x2222}, {22, 14, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData143_GAUSSIAN_5X5_08U[] = {{24, 14, 4, 0, 0x2222}, {24, 14, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData144_GAUSSIAN_5X5_08U[] = {{26, 14, 4, 0, 0x2222}, {26, 14, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData145_GAUSSIAN_5X5_08U[] = {{28, 14, 4, 0, 0x2222}, {28, 14, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData146_GAUSSIAN_5X5_08U[] = {{30, 14, 4, 0, 0x2222}, {30, 14, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData147_GAUSSIAN_5X5_08U[] = {{32, 14, 4, 0, 0x2222}, {32, 14, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData148_GAUSSIAN_5X5_08U[] = {{2, 16, 4, 0, 0x2222}, {2, 16, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData149_GAUSSIAN_5X5_08U[] = {{4, 16, 4, 0, 0x2222}, {4, 16, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData150_GAUSSIAN_5X5_08U[] = {{6, 16, 4, 0, 0x2222}, {6, 16, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData151_GAUSSIAN_5X5_08U[] = {{8, 16, 4, 0, 0x2222}, {8, 16, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData152_GAUSSIAN_5X5_08U[] = {{10, 16, 4, 0, 0x2222}, {10, 16, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData153_GAUSSIAN_5X5_08U[] = {{12, 16, 4, 0, 0x2222}, {12, 16, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData154_GAUSSIAN_5X5_08U[] = {{14, 16, 4, 0, 0x2222}, {14, 16, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData155_GAUSSIAN_5X5_08U[] = {{16, 16, 4, 0, 0x2222}, {16, 16, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData156_GAUSSIAN_5X5_08U[] = {{18, 16, 4, 0, 0x2222}, {18, 16, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData157_GAUSSIAN_5X5_08U[] = {{20, 16, 4, 0, 0x2222}, {20, 16, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData158_GAUSSIAN_5X5_08U[] = {{22, 16, 4, 0, 0x2222}, {22, 16, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData159_GAUSSIAN_5X5_08U[] = {{24, 16, 4, 0, 0x2222}, {24, 16, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData160_GAUSSIAN_5X5_08U[] = {{26, 16, 4, 0, 0x2222}, {26, 16, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData161_GAUSSIAN_5X5_08U[] = {{28, 16, 4, 0, 0x2222}, {28, 16, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData162_GAUSSIAN_5X5_08U[] = {{30, 16, 4, 0, 0x2222}, {30, 16, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData163_GAUSSIAN_5X5_08U[] = {{32, 16, 4, 0, 0x2222}, {32, 16, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData164_GAUSSIAN_5X5_08U[] = {{2, 18, 4, 0, 0x2222}, {2, 18, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData165_GAUSSIAN_5X5_08U[] = {{4, 18, 4, 0, 0x2222}, {4, 18, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData166_GAUSSIAN_5X5_08U[] = {{6, 18, 4, 0, 0x2222}, {6, 18, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData167_GAUSSIAN_5X5_08U[] = {{8, 18, 4, 0, 0x2222}, {8, 18, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData168_GAUSSIAN_5X5_08U[] = {{10, 18, 4, 0, 0x2222}, {10, 18, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData169_GAUSSIAN_5X5_08U[] = {{12, 18, 4, 0, 0x2222}, {12, 18, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData170_GAUSSIAN_5X5_08U[] = {{14, 18, 4, 0, 0x2222}, {14, 18, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData171_GAUSSIAN_5X5_08U[] = {{16, 18, 4, 0, 0x2222}, {16, 18, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData172_GAUSSIAN_5X5_08U[] = {{18, 18, 4, 0, 0x2222}, {18, 18, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData173_GAUSSIAN_5X5_08U[] = {{20, 18, 4, 0, 0x2222}, {20, 18, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData174_GAUSSIAN_5X5_08U[] = {{22, 18, 4, 0, 0x2222}, {22, 18, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData175_GAUSSIAN_5X5_08U[] = {{24, 18, 4, 0, 0x2222}, {24, 18, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData176_GAUSSIAN_5X5_08U[] = {{26, 18, 4, 0, 0x2222}, {26, 18, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData177_GAUSSIAN_5X5_08U[] = {{28, 18, 4, 0, 0x2222}, {28, 18, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData178_GAUSSIAN_5X5_08U[] = {{30, 18, 4, 0, 0x2222}, {30, 18, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData179_GAUSSIAN_5X5_08U[] = {{2, 20, 4, 0, 0x2222}, {2, 20, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData180_GAUSSIAN_5X5_08U[] = {{4, 20, 4, 0, 0x2222}, {4, 20, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData181_GAUSSIAN_5X5_08U[] = {{6, 20, 4, 0, 0x2222}, {6, 20, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData182_GAUSSIAN_5X5_08U[] = {{8, 20, 4, 0, 0x2222}, {8, 20, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData183_GAUSSIAN_5X5_08U[] = {{10, 20, 4, 0, 0x2222}, {10, 20, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData184_GAUSSIAN_5X5_08U[] = {{12, 20, 4, 0, 0x2222}, {12, 20, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData185_GAUSSIAN_5X5_08U[] = {{14, 20, 4, 0, 0x2222}, {14, 20, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData186_GAUSSIAN_5X5_08U[] = {{16, 20, 4, 0, 0x2222}, {16, 20, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData187_GAUSSIAN_5X5_08U[] = {{18, 20, 4, 0, 0x2222}, {18, 20, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData188_GAUSSIAN_5X5_08U[] = {{20, 20, 4, 0, 0x2222}, {20, 20, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData189_GAUSSIAN_5X5_08U[] = {{22, 20, 4, 0, 0x2222}, {22, 20, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData190_GAUSSIAN_5X5_08U[] = {{24, 20, 4, 0, 0x2222}, {24, 20, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData191_GAUSSIAN_5X5_08U[] = {{26, 20, 4, 0, 0x2222}, {26, 20, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData192_GAUSSIAN_5X5_08U[] = {{28, 20, 4, 0, 0x2222}, {28, 20, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData193_GAUSSIAN_5X5_08U[] = {{2, 22, 4, 0, 0x2222}, {2, 22, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData194_GAUSSIAN_5X5_08U[] = {{4, 22, 4, 0, 0x2222}, {4, 22, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData195_GAUSSIAN_5X5_08U[] = {{6, 22, 4, 0, 0x2222}, {6, 22, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData196_GAUSSIAN_5X5_08U[] = {{8, 22, 4, 0, 0x2222}, {8, 22, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData197_GAUSSIAN_5X5_08U[] = {{10, 22, 4, 0, 0x2222}, {10, 22, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData198_GAUSSIAN_5X5_08U[] = {{12, 22, 4, 0, 0x2222}, {12, 22, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData199_GAUSSIAN_5X5_08U[] = {{14, 22, 4, 0, 0x2222}, {14, 22, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData200_GAUSSIAN_5X5_08U[] = {{16, 22, 4, 0, 0x2222}, {16, 22, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData201_GAUSSIAN_5X5_08U[] = {{18, 22, 4, 0, 0x2222}, {18, 22, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData202_GAUSSIAN_5X5_08U[] = {{20, 22, 4, 0, 0x2222}, {20, 22, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData203_GAUSSIAN_5X5_08U[] = {{22, 22, 4, 0, 0x2222}, {22, 22, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData204_GAUSSIAN_5X5_08U[] = {{24, 22, 4, 0, 0x2222}, {24, 22, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData205_GAUSSIAN_5X5_08U[] = {{2, 24, 4, 0, 0x2222}, {2, 24, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData206_GAUSSIAN_5X5_08U[] = {{4, 24, 4, 0, 0x2222}, {4, 24, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData207_GAUSSIAN_5X5_08U[] = {{6, 24, 4, 0, 0x2222}, {6, 24, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData208_GAUSSIAN_5X5_08U[] = {{8, 24, 4, 0, 0x2222}, {8, 24, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData209_GAUSSIAN_5X5_08U[] = {{10, 24, 4, 0, 0x2222}, {10, 24, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData210_GAUSSIAN_5X5_08U[] = {{12, 24, 4, 0, 0x2222}, {12, 24, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData211_GAUSSIAN_5X5_08U[] = {{14, 24, 4, 0, 0x2222}, {14, 24, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData212_GAUSSIAN_5X5_08U[] = {{16, 24, 4, 0, 0x2222}, {16, 24, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData213_GAUSSIAN_5X5_08U[] = {{18, 24, 4, 0, 0x2222}, {18, 24, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData214_GAUSSIAN_5X5_08U[] = {{20, 24, 4, 0, 0x2222}, {20, 24, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData215_GAUSSIAN_5X5_08U[] = {{22, 24, 4, 0, 0x2222}, {22, 24, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData216_GAUSSIAN_5X5_08U[] = {{2, 26, 4, 0, 0x2222}, {2, 26, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData217_GAUSSIAN_5X5_08U[] = {{4, 26, 4, 0, 0x2222}, {4, 26, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData218_GAUSSIAN_5X5_08U[] = {{6, 26, 4, 0, 0x2222}, {6, 26, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData219_GAUSSIAN_5X5_08U[] = {{8, 26, 4, 0, 0x2222}, {8, 26, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData220_GAUSSIAN_5X5_08U[] = {{10, 26, 4, 0, 0x2222}, {10, 26, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData221_GAUSSIAN_5X5_08U[] = {{12, 26, 4, 0, 0x2222}, {12, 26, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData222_GAUSSIAN_5X5_08U[] = {{14, 26, 4, 0, 0x2222}, {14, 26, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData223_GAUSSIAN_5X5_08U[] = {{16, 26, 4, 0, 0x2222}, {16, 26, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData224_GAUSSIAN_5X5_08U[] = {{18, 26, 4, 0, 0x2222}, {18, 26, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData225_GAUSSIAN_5X5_08U[] = {{20, 26, 4, 0, 0x2222}, {20, 26, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData226_GAUSSIAN_5X5_08U[] = {{2, 28, 4, 0, 0x2222}, {2, 28, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData227_GAUSSIAN_5X5_08U[] = {{4, 28, 4, 0, 0x2222}, {4, 28, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData228_GAUSSIAN_5X5_08U[] = {{6, 28, 4, 0, 0x2222}, {6, 28, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData229_GAUSSIAN_5X5_08U[] = {{8, 28, 4, 0, 0x2222}, {8, 28, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData230_GAUSSIAN_5X5_08U[] = {{10, 28, 4, 0, 0x2222}, {10, 28, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData231_GAUSSIAN_5X5_08U[] = {{12, 28, 4, 0, 0x2222}, {12, 28, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData232_GAUSSIAN_5X5_08U[] = {{14, 28, 4, 0, 0x2222}, {14, 28, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData233_GAUSSIAN_5X5_08U[] = {{16, 28, 4, 0, 0x2222}, {16, 28, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData234_GAUSSIAN_5X5_08U[] = {{18, 28, 4, 0, 0x2222}, {18, 28, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData235_GAUSSIAN_5X5_08U[] = {{2, 30, 4, 0, 0x2222}, {2, 30, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData236_GAUSSIAN_5X5_08U[] = {{4, 30, 4, 0, 0x2222}, {4, 30, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData237_GAUSSIAN_5X5_08U[] = {{6, 30, 4, 0, 0x2222}, {6, 30, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData238_GAUSSIAN_5X5_08U[] = {{8, 30, 4, 0, 0x2222}, {8, 30, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData239_GAUSSIAN_5X5_08U[] = {{10, 30, 4, 0, 0x2222}, {10, 30, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData240_GAUSSIAN_5X5_08U[] = {{12, 30, 4, 0, 0x2222}, {12, 30, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData241_GAUSSIAN_5X5_08U[] = {{14, 30, 4, 0, 0x2222}, {14, 30, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData242_GAUSSIAN_5X5_08U[] = {{16, 30, 4, 0, 0x2222}, {16, 30, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData243_GAUSSIAN_5X5_08U[] = {{18, 30, 4, 0, 0x2222}, {18, 30, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData244_GAUSSIAN_5X5_08U[] = {{2, 32, 4, 0, 0x2222}, {2, 32, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData245_GAUSSIAN_5X5_08U[] = {{4, 32, 4, 0, 0x2222}, {4, 32, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData246_GAUSSIAN_5X5_08U[] = {{6, 32, 4, 0, 0x2222}, {6, 32, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData247_GAUSSIAN_5X5_08U[] = {{8, 32, 4, 0, 0x2222}, {8, 32, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData248_GAUSSIAN_5X5_08U[] = {{10, 32, 4, 0, 0x2222}, {10, 32, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData249_GAUSSIAN_5X5_08U[] = {{12, 32, 4, 0, 0x2222}, {12, 32, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData250_GAUSSIAN_5X5_08U[] = {{14, 32, 4, 0, 0x2222}, {14, 32, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData251_GAUSSIAN_5X5_08U[] = {{16, 32, 4, 0, 0x2222}, {16, 32, 2, 1, 0x0}};

static acf_scenario_kernel_data gScenarioKernelData0_GAUSSIAN_5X5_08U[] = {{2}};
static acf_scenario_kernel_data gScenarioKernelData1_GAUSSIAN_5X5_08U[] = {{2}};
static acf_scenario_kernel_data gScenarioKernelData2_GAUSSIAN_5X5_08U[] = {{2}};
static acf_scenario_kernel_data gScenarioKernelData3_GAUSSIAN_5X5_08U[] = {{2}};
static acf_scenario_kernel_data gScenarioKernelData4_GAUSSIAN_5X5_08U[] = {{2}};
static acf_scenario_kernel_data gScenarioKernelData5_GAUSSIAN_5X5_08U[] = {{2}};
static acf_scenario_kernel_data gScenarioKernelData6_GAUSSIAN_5X5_08U[] = {{2}};
static acf_scenario_kernel_data gScenarioKernelData7_GAUSSIAN_5X5_08U[] = {{2}};
static acf_scenario_kernel_data gScenarioKernelData8_GAUSSIAN_5X5_08U[] = {{2}};
static acf_scenario_kernel_data gScenarioKernelData9_GAUSSIAN_5X5_08U[] = {{2}};
static acf_scenario_kernel_data gScenarioKernelData10_GAUSSIAN_5X5_08U[] = {{2}};
static acf_scenario_kernel_data gScenarioKernelData11_GAUSSIAN_5X5_08U[] = {{2}};
static acf_scenario_kernel_data gScenarioKernelData12_GAUSSIAN_5X5_08U[] = {{2}};
static acf_scenario_kernel_data gScenarioKernelData13_GAUSSIAN_5X5_08U[] = {{2}};
static acf_scenario_kernel_data gScenarioKernelData14_GAUSSIAN_5X5_08U[] = {{2}};
static acf_scenario_kernel_data gScenarioKernelData15_GAUSSIAN_5X5_08U[] = {{2}};
static acf_scenario_kernel_data gScenarioKernelData16_GAUSSIAN_5X5_08U[] = {{2}};
static acf_scenario_kernel_data gScenarioKernelData17_GAUSSIAN_5X5_08U[] = {{2}};
static acf_scenario_kernel_data gScenarioKernelData18_GAUSSIAN_5X5_08U[] = {{2}};
static acf_scenario_kernel_data gScenarioKernelData19_GAUSSIAN_5X5_08U[] = {{2}};
static acf_scenario_kernel_data gScenarioKernelData20_GAUSSIAN_5X5_08U[] = {{2}};
static acf_scenario_kernel_data gScenarioKernelData21_GAUSSIAN_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData22_GAUSSIAN_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData23_GAUSSIAN_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData24_GAUSSIAN_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData25_GAUSSIAN_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData26_GAUSSIAN_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData27_GAUSSIAN_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData28_GAUSSIAN_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData29_GAUSSIAN_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData30_GAUSSIAN_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData31_GAUSSIAN_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData32_GAUSSIAN_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData33_GAUSSIAN_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData34_GAUSSIAN_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData35_GAUSSIAN_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData36_GAUSSIAN_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData37_GAUSSIAN_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData38_GAUSSIAN_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData39_GAUSSIAN_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData40_GAUSSIAN_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData41_GAUSSIAN_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData42_GAUSSIAN_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData43_GAUSSIAN_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData44_GAUSSIAN_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData45_GAUSSIAN_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData46_GAUSSIAN_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData47_GAUSSIAN_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData48_GAUSSIAN_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData49_GAUSSIAN_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData50_GAUSSIAN_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData51_GAUSSIAN_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData52_GAUSSIAN_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData53_GAUSSIAN_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData54_GAUSSIAN_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData55_GAUSSIAN_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData56_GAUSSIAN_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData57_GAUSSIAN_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData58_GAUSSIAN_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData59_GAUSSIAN_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData60_GAUSSIAN_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData61_GAUSSIAN_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData62_GAUSSIAN_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData63_GAUSSIAN_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData64_GAUSSIAN_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData65_GAUSSIAN_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData66_GAUSSIAN_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData67_GAUSSIAN_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData68_GAUSSIAN_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData69_GAUSSIAN_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData70_GAUSSIAN_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData71_GAUSSIAN_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData72_GAUSSIAN_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData73_GAUSSIAN_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData74_GAUSSIAN_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData75_GAUSSIAN_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData76_GAUSSIAN_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData77_GAUSSIAN_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData78_GAUSSIAN_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData79_GAUSSIAN_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData80_GAUSSIAN_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData81_GAUSSIAN_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData82_GAUSSIAN_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData83_GAUSSIAN_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData84_GAUSSIAN_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData85_GAUSSIAN_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData86_GAUSSIAN_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData87_GAUSSIAN_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData88_GAUSSIAN_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData89_GAUSSIAN_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData90_GAUSSIAN_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData91_GAUSSIAN_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData92_GAUSSIAN_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData93_GAUSSIAN_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData94_GAUSSIAN_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData95_GAUSSIAN_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData96_GAUSSIAN_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData97_GAUSSIAN_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData98_GAUSSIAN_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData99_GAUSSIAN_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData100_GAUSSIAN_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData101_GAUSSIAN_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData102_GAUSSIAN_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData103_GAUSSIAN_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData104_GAUSSIAN_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData105_GAUSSIAN_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData106_GAUSSIAN_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData107_GAUSSIAN_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData108_GAUSSIAN_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData109_GAUSSIAN_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData110_GAUSSIAN_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData111_GAUSSIAN_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData112_GAUSSIAN_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData113_GAUSSIAN_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData114_GAUSSIAN_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData115_GAUSSIAN_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData116_GAUSSIAN_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData117_GAUSSIAN_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData118_GAUSSIAN_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData119_GAUSSIAN_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData120_GAUSSIAN_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData121_GAUSSIAN_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData122_GAUSSIAN_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData123_GAUSSIAN_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData124_GAUSSIAN_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData125_GAUSSIAN_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData126_GAUSSIAN_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData127_GAUSSIAN_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData128_GAUSSIAN_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData129_GAUSSIAN_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData130_GAUSSIAN_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData131_GAUSSIAN_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData132_GAUSSIAN_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData133_GAUSSIAN_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData134_GAUSSIAN_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData135_GAUSSIAN_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData136_GAUSSIAN_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData137_GAUSSIAN_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData138_GAUSSIAN_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData139_GAUSSIAN_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData140_GAUSSIAN_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData141_GAUSSIAN_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData142_GAUSSIAN_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData143_GAUSSIAN_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData144_GAUSSIAN_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData145_GAUSSIAN_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData146_GAUSSIAN_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData147_GAUSSIAN_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData148_GAUSSIAN_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData149_GAUSSIAN_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData150_GAUSSIAN_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData151_GAUSSIAN_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData152_GAUSSIAN_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData153_GAUSSIAN_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData154_GAUSSIAN_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData155_GAUSSIAN_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData156_GAUSSIAN_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData157_GAUSSIAN_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData158_GAUSSIAN_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData159_GAUSSIAN_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData160_GAUSSIAN_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData161_GAUSSIAN_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData162_GAUSSIAN_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData163_GAUSSIAN_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData164_GAUSSIAN_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData165_GAUSSIAN_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData166_GAUSSIAN_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData167_GAUSSIAN_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData168_GAUSSIAN_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData169_GAUSSIAN_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData170_GAUSSIAN_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData171_GAUSSIAN_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData172_GAUSSIAN_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData173_GAUSSIAN_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData174_GAUSSIAN_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData175_GAUSSIAN_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData176_GAUSSIAN_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData177_GAUSSIAN_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData178_GAUSSIAN_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData179_GAUSSIAN_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData180_GAUSSIAN_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData181_GAUSSIAN_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData182_GAUSSIAN_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData183_GAUSSIAN_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData184_GAUSSIAN_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData185_GAUSSIAN_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData186_GAUSSIAN_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData187_GAUSSIAN_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData188_GAUSSIAN_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData189_GAUSSIAN_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData190_GAUSSIAN_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData191_GAUSSIAN_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData192_GAUSSIAN_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData193_GAUSSIAN_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData194_GAUSSIAN_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData195_GAUSSIAN_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData196_GAUSSIAN_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData197_GAUSSIAN_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData198_GAUSSIAN_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData199_GAUSSIAN_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData200_GAUSSIAN_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData201_GAUSSIAN_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData202_GAUSSIAN_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData203_GAUSSIAN_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData204_GAUSSIAN_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData205_GAUSSIAN_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData206_GAUSSIAN_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData207_GAUSSIAN_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData208_GAUSSIAN_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData209_GAUSSIAN_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData210_GAUSSIAN_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData211_GAUSSIAN_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData212_GAUSSIAN_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData213_GAUSSIAN_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData214_GAUSSIAN_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData215_GAUSSIAN_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData216_GAUSSIAN_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData217_GAUSSIAN_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData218_GAUSSIAN_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData219_GAUSSIAN_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData220_GAUSSIAN_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData221_GAUSSIAN_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData222_GAUSSIAN_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData223_GAUSSIAN_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData224_GAUSSIAN_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData225_GAUSSIAN_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData226_GAUSSIAN_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData227_GAUSSIAN_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData228_GAUSSIAN_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData229_GAUSSIAN_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData230_GAUSSIAN_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData231_GAUSSIAN_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData232_GAUSSIAN_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData233_GAUSSIAN_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData234_GAUSSIAN_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData235_GAUSSIAN_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData236_GAUSSIAN_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData237_GAUSSIAN_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData238_GAUSSIAN_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData239_GAUSSIAN_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData240_GAUSSIAN_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData241_GAUSSIAN_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData242_GAUSSIAN_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData243_GAUSSIAN_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData244_GAUSSIAN_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData245_GAUSSIAN_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData246_GAUSSIAN_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData247_GAUSSIAN_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData248_GAUSSIAN_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData249_GAUSSIAN_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData250_GAUSSIAN_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData251_GAUSSIAN_5X5_08U[] = {{1}};

static acf_scenario gScenarioArray_GAUSSIAN_5X5_08U[] = {
{2, 1, 72, 0, 2, gScenarioBufferData0_GAUSSIAN_5X5_08U, 20, gScenarioKernelData0_GAUSSIAN_5X5_08U, 2},
{4, 1, 96, 0, 2, gScenarioBufferData1_GAUSSIAN_5X5_08U, 20, gScenarioKernelData1_GAUSSIAN_5X5_08U, 2},
{6, 1, 124, 0, 2, gScenarioBufferData2_GAUSSIAN_5X5_08U, 20, gScenarioKernelData2_GAUSSIAN_5X5_08U, 2},
{8, 1, 148, 0, 2, gScenarioBufferData3_GAUSSIAN_5X5_08U, 20, gScenarioKernelData3_GAUSSIAN_5X5_08U, 2},
{10, 1, 176, 0, 2, gScenarioBufferData4_GAUSSIAN_5X5_08U, 20, gScenarioKernelData4_GAUSSIAN_5X5_08U, 2},
{12, 1, 200, 0, 2, gScenarioBufferData5_GAUSSIAN_5X5_08U, 20, gScenarioKernelData5_GAUSSIAN_5X5_08U, 2},
{14, 1, 228, 0, 2, gScenarioBufferData6_GAUSSIAN_5X5_08U, 20, gScenarioKernelData6_GAUSSIAN_5X5_08U, 2},
{16, 1, 252, 0, 2, gScenarioBufferData7_GAUSSIAN_5X5_08U, 20, gScenarioKernelData7_GAUSSIAN_5X5_08U, 2},
{18, 1, 280, 0, 2, gScenarioBufferData8_GAUSSIAN_5X5_08U, 20, gScenarioKernelData8_GAUSSIAN_5X5_08U, 2},
{20, 1, 304, 0, 2, gScenarioBufferData9_GAUSSIAN_5X5_08U, 20, gScenarioKernelData9_GAUSSIAN_5X5_08U, 2},
{22, 1, 332, 0, 2, gScenarioBufferData10_GAUSSIAN_5X5_08U, 20, gScenarioKernelData10_GAUSSIAN_5X5_08U, 2},
{24, 1, 356, 0, 2, gScenarioBufferData11_GAUSSIAN_5X5_08U, 20, gScenarioKernelData11_GAUSSIAN_5X5_08U, 2},
{26, 1, 384, 0, 2, gScenarioBufferData12_GAUSSIAN_5X5_08U, 20, gScenarioKernelData12_GAUSSIAN_5X5_08U, 2},
{28, 1, 408, 0, 2, gScenarioBufferData13_GAUSSIAN_5X5_08U, 20, gScenarioKernelData13_GAUSSIAN_5X5_08U, 2},
{30, 1, 436, 0, 2, gScenarioBufferData14_GAUSSIAN_5X5_08U, 20, gScenarioKernelData14_GAUSSIAN_5X5_08U, 2},
{32, 1, 460, 0, 2, gScenarioBufferData15_GAUSSIAN_5X5_08U, 20, gScenarioKernelData15_GAUSSIAN_5X5_08U, 2},
{48, 1, 668, 0, 2, gScenarioBufferData16_GAUSSIAN_5X5_08U, 20, gScenarioKernelData16_GAUSSIAN_5X5_08U, 2},
{64, 1, 876, 0, 2, gScenarioBufferData17_GAUSSIAN_5X5_08U, 20, gScenarioKernelData17_GAUSSIAN_5X5_08U, 2},
{96, 1, 1292, 0, 2, gScenarioBufferData18_GAUSSIAN_5X5_08U, 20, gScenarioKernelData18_GAUSSIAN_5X5_08U, 2},
{112, 1, 1500, 0, 2, gScenarioBufferData19_GAUSSIAN_5X5_08U, 20, gScenarioKernelData19_GAUSSIAN_5X5_08U, 2},
{128, 1, 1708, 0, 2, gScenarioBufferData20_GAUSSIAN_5X5_08U, 20, gScenarioKernelData20_GAUSSIAN_5X5_08U, 2},
{2, 2, 80, 0, 1, gScenarioBufferData21_GAUSSIAN_5X5_08U, 20, gScenarioKernelData21_GAUSSIAN_5X5_08U, 2},
{4, 2, 112, 0, 1, gScenarioBufferData22_GAUSSIAN_5X5_08U, 20, gScenarioKernelData22_GAUSSIAN_5X5_08U, 2},
{6, 2, 144, 0, 1, gScenarioBufferData23_GAUSSIAN_5X5_08U, 20, gScenarioKernelData23_GAUSSIAN_5X5_08U, 2},
{8, 2, 176, 0, 1, gScenarioBufferData24_GAUSSIAN_5X5_08U, 20, gScenarioKernelData24_GAUSSIAN_5X5_08U, 2},
{10, 2, 208, 0, 1, gScenarioBufferData25_GAUSSIAN_5X5_08U, 20, gScenarioKernelData25_GAUSSIAN_5X5_08U, 2},
{12, 2, 240, 0, 1, gScenarioBufferData26_GAUSSIAN_5X5_08U, 20, gScenarioKernelData26_GAUSSIAN_5X5_08U, 2},
{14, 2, 272, 0, 1, gScenarioBufferData27_GAUSSIAN_5X5_08U, 20, gScenarioKernelData27_GAUSSIAN_5X5_08U, 2},
{16, 2, 304, 0, 1, gScenarioBufferData28_GAUSSIAN_5X5_08U, 20, gScenarioKernelData28_GAUSSIAN_5X5_08U, 2},
{18, 2, 336, 0, 1, gScenarioBufferData29_GAUSSIAN_5X5_08U, 20, gScenarioKernelData29_GAUSSIAN_5X5_08U, 2},
{20, 2, 368, 0, 1, gScenarioBufferData30_GAUSSIAN_5X5_08U, 20, gScenarioKernelData30_GAUSSIAN_5X5_08U, 2},
{22, 2, 400, 0, 1, gScenarioBufferData31_GAUSSIAN_5X5_08U, 20, gScenarioKernelData31_GAUSSIAN_5X5_08U, 2},
{24, 2, 432, 0, 1, gScenarioBufferData32_GAUSSIAN_5X5_08U, 20, gScenarioKernelData32_GAUSSIAN_5X5_08U, 2},
{26, 2, 464, 0, 1, gScenarioBufferData33_GAUSSIAN_5X5_08U, 20, gScenarioKernelData33_GAUSSIAN_5X5_08U, 2},
{28, 2, 496, 0, 1, gScenarioBufferData34_GAUSSIAN_5X5_08U, 20, gScenarioKernelData34_GAUSSIAN_5X5_08U, 2},
{30, 2, 528, 0, 1, gScenarioBufferData35_GAUSSIAN_5X5_08U, 20, gScenarioKernelData35_GAUSSIAN_5X5_08U, 2},
{32, 2, 560, 0, 1, gScenarioBufferData36_GAUSSIAN_5X5_08U, 20, gScenarioKernelData36_GAUSSIAN_5X5_08U, 2},
{48, 2, 816, 0, 1, gScenarioBufferData37_GAUSSIAN_5X5_08U, 20, gScenarioKernelData37_GAUSSIAN_5X5_08U, 2},
{64, 2, 1072, 0, 1, gScenarioBufferData38_GAUSSIAN_5X5_08U, 20, gScenarioKernelData38_GAUSSIAN_5X5_08U, 2},
{96, 2, 1584, 0, 1, gScenarioBufferData39_GAUSSIAN_5X5_08U, 20, gScenarioKernelData39_GAUSSIAN_5X5_08U, 2},
{112, 2, 1840, 0, 1, gScenarioBufferData40_GAUSSIAN_5X5_08U, 20, gScenarioKernelData40_GAUSSIAN_5X5_08U, 2},
{128, 2, 2096, 0, 1, gScenarioBufferData41_GAUSSIAN_5X5_08U, 20, gScenarioKernelData41_GAUSSIAN_5X5_08U, 2},
{2, 4, 136, 0, 1, gScenarioBufferData42_GAUSSIAN_5X5_08U, 20, gScenarioKernelData42_GAUSSIAN_5X5_08U, 2},
{4, 4, 192, 0, 1, gScenarioBufferData43_GAUSSIAN_5X5_08U, 20, gScenarioKernelData43_GAUSSIAN_5X5_08U, 2},
{6, 4, 248, 0, 1, gScenarioBufferData44_GAUSSIAN_5X5_08U, 20, gScenarioKernelData44_GAUSSIAN_5X5_08U, 2},
{8, 4, 304, 0, 1, gScenarioBufferData45_GAUSSIAN_5X5_08U, 20, gScenarioKernelData45_GAUSSIAN_5X5_08U, 2},
{10, 4, 360, 0, 1, gScenarioBufferData46_GAUSSIAN_5X5_08U, 20, gScenarioKernelData46_GAUSSIAN_5X5_08U, 2},
{12, 4, 416, 0, 1, gScenarioBufferData47_GAUSSIAN_5X5_08U, 20, gScenarioKernelData47_GAUSSIAN_5X5_08U, 2},
{14, 4, 472, 0, 1, gScenarioBufferData48_GAUSSIAN_5X5_08U, 20, gScenarioKernelData48_GAUSSIAN_5X5_08U, 2},
{16, 4, 528, 0, 1, gScenarioBufferData49_GAUSSIAN_5X5_08U, 20, gScenarioKernelData49_GAUSSIAN_5X5_08U, 2},
{18, 4, 584, 0, 1, gScenarioBufferData50_GAUSSIAN_5X5_08U, 20, gScenarioKernelData50_GAUSSIAN_5X5_08U, 2},
{20, 4, 640, 0, 1, gScenarioBufferData51_GAUSSIAN_5X5_08U, 20, gScenarioKernelData51_GAUSSIAN_5X5_08U, 2},
{22, 4, 696, 0, 1, gScenarioBufferData52_GAUSSIAN_5X5_08U, 20, gScenarioKernelData52_GAUSSIAN_5X5_08U, 2},
{24, 4, 752, 0, 1, gScenarioBufferData53_GAUSSIAN_5X5_08U, 20, gScenarioKernelData53_GAUSSIAN_5X5_08U, 2},
{26, 4, 808, 0, 1, gScenarioBufferData54_GAUSSIAN_5X5_08U, 20, gScenarioKernelData54_GAUSSIAN_5X5_08U, 2},
{28, 4, 864, 0, 1, gScenarioBufferData55_GAUSSIAN_5X5_08U, 20, gScenarioKernelData55_GAUSSIAN_5X5_08U, 2},
{30, 4, 920, 0, 1, gScenarioBufferData56_GAUSSIAN_5X5_08U, 20, gScenarioKernelData56_GAUSSIAN_5X5_08U, 2},
{32, 4, 976, 0, 1, gScenarioBufferData57_GAUSSIAN_5X5_08U, 20, gScenarioKernelData57_GAUSSIAN_5X5_08U, 2},
{48, 4, 1424, 0, 1, gScenarioBufferData58_GAUSSIAN_5X5_08U, 20, gScenarioKernelData58_GAUSSIAN_5X5_08U, 2},
{64, 4, 1872, 0, 1, gScenarioBufferData59_GAUSSIAN_5X5_08U, 20, gScenarioKernelData59_GAUSSIAN_5X5_08U, 2},
{96, 4, 2768, 0, 1, gScenarioBufferData60_GAUSSIAN_5X5_08U, 20, gScenarioKernelData60_GAUSSIAN_5X5_08U, 2},
{112, 4, 3216, 0, 1, gScenarioBufferData61_GAUSSIAN_5X5_08U, 20, gScenarioKernelData61_GAUSSIAN_5X5_08U, 2},
{128, 4, 3664, 0, 1, gScenarioBufferData62_GAUSSIAN_5X5_08U, 20, gScenarioKernelData62_GAUSSIAN_5X5_08U, 2},
{2, 6, 192, 0, 1, gScenarioBufferData63_GAUSSIAN_5X5_08U, 20, gScenarioKernelData63_GAUSSIAN_5X5_08U, 2},
{4, 6, 272, 0, 1, gScenarioBufferData64_GAUSSIAN_5X5_08U, 20, gScenarioKernelData64_GAUSSIAN_5X5_08U, 2},
{6, 6, 352, 0, 1, gScenarioBufferData65_GAUSSIAN_5X5_08U, 20, gScenarioKernelData65_GAUSSIAN_5X5_08U, 2},
{8, 6, 432, 0, 1, gScenarioBufferData66_GAUSSIAN_5X5_08U, 20, gScenarioKernelData66_GAUSSIAN_5X5_08U, 2},
{10, 6, 512, 0, 1, gScenarioBufferData67_GAUSSIAN_5X5_08U, 20, gScenarioKernelData67_GAUSSIAN_5X5_08U, 2},
{12, 6, 592, 0, 1, gScenarioBufferData68_GAUSSIAN_5X5_08U, 20, gScenarioKernelData68_GAUSSIAN_5X5_08U, 2},
{14, 6, 672, 0, 1, gScenarioBufferData69_GAUSSIAN_5X5_08U, 20, gScenarioKernelData69_GAUSSIAN_5X5_08U, 2},
{16, 6, 752, 0, 1, gScenarioBufferData70_GAUSSIAN_5X5_08U, 20, gScenarioKernelData70_GAUSSIAN_5X5_08U, 2},
{18, 6, 832, 0, 1, gScenarioBufferData71_GAUSSIAN_5X5_08U, 20, gScenarioKernelData71_GAUSSIAN_5X5_08U, 2},
{20, 6, 912, 0, 1, gScenarioBufferData72_GAUSSIAN_5X5_08U, 20, gScenarioKernelData72_GAUSSIAN_5X5_08U, 2},
{22, 6, 992, 0, 1, gScenarioBufferData73_GAUSSIAN_5X5_08U, 20, gScenarioKernelData73_GAUSSIAN_5X5_08U, 2},
{24, 6, 1072, 0, 1, gScenarioBufferData74_GAUSSIAN_5X5_08U, 20, gScenarioKernelData74_GAUSSIAN_5X5_08U, 2},
{26, 6, 1152, 0, 1, gScenarioBufferData75_GAUSSIAN_5X5_08U, 20, gScenarioKernelData75_GAUSSIAN_5X5_08U, 2},
{28, 6, 1232, 0, 1, gScenarioBufferData76_GAUSSIAN_5X5_08U, 20, gScenarioKernelData76_GAUSSIAN_5X5_08U, 2},
{30, 6, 1312, 0, 1, gScenarioBufferData77_GAUSSIAN_5X5_08U, 20, gScenarioKernelData77_GAUSSIAN_5X5_08U, 2},
{32, 6, 1392, 0, 1, gScenarioBufferData78_GAUSSIAN_5X5_08U, 20, gScenarioKernelData78_GAUSSIAN_5X5_08U, 2},
{48, 6, 2032, 0, 1, gScenarioBufferData79_GAUSSIAN_5X5_08U, 20, gScenarioKernelData79_GAUSSIAN_5X5_08U, 2},
{64, 6, 2672, 0, 1, gScenarioBufferData80_GAUSSIAN_5X5_08U, 20, gScenarioKernelData80_GAUSSIAN_5X5_08U, 2},
{2, 8, 248, 0, 1, gScenarioBufferData81_GAUSSIAN_5X5_08U, 20, gScenarioKernelData81_GAUSSIAN_5X5_08U, 2},
{4, 8, 352, 0, 1, gScenarioBufferData82_GAUSSIAN_5X5_08U, 20, gScenarioKernelData82_GAUSSIAN_5X5_08U, 2},
{6, 8, 456, 0, 1, gScenarioBufferData83_GAUSSIAN_5X5_08U, 20, gScenarioKernelData83_GAUSSIAN_5X5_08U, 2},
{8, 8, 560, 0, 1, gScenarioBufferData84_GAUSSIAN_5X5_08U, 20, gScenarioKernelData84_GAUSSIAN_5X5_08U, 2},
{10, 8, 664, 0, 1, gScenarioBufferData85_GAUSSIAN_5X5_08U, 20, gScenarioKernelData85_GAUSSIAN_5X5_08U, 2},
{12, 8, 768, 0, 1, gScenarioBufferData86_GAUSSIAN_5X5_08U, 20, gScenarioKernelData86_GAUSSIAN_5X5_08U, 2},
{14, 8, 872, 0, 1, gScenarioBufferData87_GAUSSIAN_5X5_08U, 20, gScenarioKernelData87_GAUSSIAN_5X5_08U, 2},
{16, 8, 976, 0, 1, gScenarioBufferData88_GAUSSIAN_5X5_08U, 20, gScenarioKernelData88_GAUSSIAN_5X5_08U, 2},
{18, 8, 1080, 0, 1, gScenarioBufferData89_GAUSSIAN_5X5_08U, 20, gScenarioKernelData89_GAUSSIAN_5X5_08U, 2},
{20, 8, 1184, 0, 1, gScenarioBufferData90_GAUSSIAN_5X5_08U, 20, gScenarioKernelData90_GAUSSIAN_5X5_08U, 2},
{22, 8, 1288, 0, 1, gScenarioBufferData91_GAUSSIAN_5X5_08U, 20, gScenarioKernelData91_GAUSSIAN_5X5_08U, 2},
{24, 8, 1392, 0, 1, gScenarioBufferData92_GAUSSIAN_5X5_08U, 20, gScenarioKernelData92_GAUSSIAN_5X5_08U, 2},
{26, 8, 1496, 0, 1, gScenarioBufferData93_GAUSSIAN_5X5_08U, 20, gScenarioKernelData93_GAUSSIAN_5X5_08U, 2},
{28, 8, 1600, 0, 1, gScenarioBufferData94_GAUSSIAN_5X5_08U, 20, gScenarioKernelData94_GAUSSIAN_5X5_08U, 2},
{30, 8, 1704, 0, 1, gScenarioBufferData95_GAUSSIAN_5X5_08U, 20, gScenarioKernelData95_GAUSSIAN_5X5_08U, 2},
{32, 8, 1808, 0, 1, gScenarioBufferData96_GAUSSIAN_5X5_08U, 20, gScenarioKernelData96_GAUSSIAN_5X5_08U, 2},
{48, 8, 2640, 0, 1, gScenarioBufferData97_GAUSSIAN_5X5_08U, 20, gScenarioKernelData97_GAUSSIAN_5X5_08U, 2},
{64, 8, 3472, 0, 1, gScenarioBufferData98_GAUSSIAN_5X5_08U, 20, gScenarioKernelData98_GAUSSIAN_5X5_08U, 2},
{2, 10, 304, 0, 1, gScenarioBufferData99_GAUSSIAN_5X5_08U, 20, gScenarioKernelData99_GAUSSIAN_5X5_08U, 2},
{4, 10, 432, 0, 1, gScenarioBufferData100_GAUSSIAN_5X5_08U, 20, gScenarioKernelData100_GAUSSIAN_5X5_08U, 2},
{6, 10, 560, 0, 1, gScenarioBufferData101_GAUSSIAN_5X5_08U, 20, gScenarioKernelData101_GAUSSIAN_5X5_08U, 2},
{8, 10, 688, 0, 1, gScenarioBufferData102_GAUSSIAN_5X5_08U, 20, gScenarioKernelData102_GAUSSIAN_5X5_08U, 2},
{10, 10, 816, 0, 1, gScenarioBufferData103_GAUSSIAN_5X5_08U, 20, gScenarioKernelData103_GAUSSIAN_5X5_08U, 2},
{12, 10, 944, 0, 1, gScenarioBufferData104_GAUSSIAN_5X5_08U, 20, gScenarioKernelData104_GAUSSIAN_5X5_08U, 2},
{14, 10, 1072, 0, 1, gScenarioBufferData105_GAUSSIAN_5X5_08U, 20, gScenarioKernelData105_GAUSSIAN_5X5_08U, 2},
{16, 10, 1200, 0, 1, gScenarioBufferData106_GAUSSIAN_5X5_08U, 20, gScenarioKernelData106_GAUSSIAN_5X5_08U, 2},
{18, 10, 1328, 0, 1, gScenarioBufferData107_GAUSSIAN_5X5_08U, 20, gScenarioKernelData107_GAUSSIAN_5X5_08U, 2},
{20, 10, 1456, 0, 1, gScenarioBufferData108_GAUSSIAN_5X5_08U, 20, gScenarioKernelData108_GAUSSIAN_5X5_08U, 2},
{22, 10, 1584, 0, 1, gScenarioBufferData109_GAUSSIAN_5X5_08U, 20, gScenarioKernelData109_GAUSSIAN_5X5_08U, 2},
{24, 10, 1712, 0, 1, gScenarioBufferData110_GAUSSIAN_5X5_08U, 20, gScenarioKernelData110_GAUSSIAN_5X5_08U, 2},
{26, 10, 1840, 0, 1, gScenarioBufferData111_GAUSSIAN_5X5_08U, 20, gScenarioKernelData111_GAUSSIAN_5X5_08U, 2},
{28, 10, 1968, 0, 1, gScenarioBufferData112_GAUSSIAN_5X5_08U, 20, gScenarioKernelData112_GAUSSIAN_5X5_08U, 2},
{30, 10, 2096, 0, 1, gScenarioBufferData113_GAUSSIAN_5X5_08U, 20, gScenarioKernelData113_GAUSSIAN_5X5_08U, 2},
{32, 10, 2224, 0, 1, gScenarioBufferData114_GAUSSIAN_5X5_08U, 20, gScenarioKernelData114_GAUSSIAN_5X5_08U, 2},
{48, 10, 3248, 0, 1, gScenarioBufferData115_GAUSSIAN_5X5_08U, 20, gScenarioKernelData115_GAUSSIAN_5X5_08U, 2},
{2, 12, 360, 0, 1, gScenarioBufferData116_GAUSSIAN_5X5_08U, 20, gScenarioKernelData116_GAUSSIAN_5X5_08U, 2},
{4, 12, 512, 0, 1, gScenarioBufferData117_GAUSSIAN_5X5_08U, 20, gScenarioKernelData117_GAUSSIAN_5X5_08U, 2},
{6, 12, 664, 0, 1, gScenarioBufferData118_GAUSSIAN_5X5_08U, 20, gScenarioKernelData118_GAUSSIAN_5X5_08U, 2},
{8, 12, 816, 0, 1, gScenarioBufferData119_GAUSSIAN_5X5_08U, 20, gScenarioKernelData119_GAUSSIAN_5X5_08U, 2},
{10, 12, 968, 0, 1, gScenarioBufferData120_GAUSSIAN_5X5_08U, 20, gScenarioKernelData120_GAUSSIAN_5X5_08U, 2},
{12, 12, 1120, 0, 1, gScenarioBufferData121_GAUSSIAN_5X5_08U, 20, gScenarioKernelData121_GAUSSIAN_5X5_08U, 2},
{14, 12, 1272, 0, 1, gScenarioBufferData122_GAUSSIAN_5X5_08U, 20, gScenarioKernelData122_GAUSSIAN_5X5_08U, 2},
{16, 12, 1424, 0, 1, gScenarioBufferData123_GAUSSIAN_5X5_08U, 20, gScenarioKernelData123_GAUSSIAN_5X5_08U, 2},
{18, 12, 1576, 0, 1, gScenarioBufferData124_GAUSSIAN_5X5_08U, 20, gScenarioKernelData124_GAUSSIAN_5X5_08U, 2},
{20, 12, 1728, 0, 1, gScenarioBufferData125_GAUSSIAN_5X5_08U, 20, gScenarioKernelData125_GAUSSIAN_5X5_08U, 2},
{22, 12, 1880, 0, 1, gScenarioBufferData126_GAUSSIAN_5X5_08U, 20, gScenarioKernelData126_GAUSSIAN_5X5_08U, 2},
{24, 12, 2032, 0, 1, gScenarioBufferData127_GAUSSIAN_5X5_08U, 20, gScenarioKernelData127_GAUSSIAN_5X5_08U, 2},
{26, 12, 2184, 0, 1, gScenarioBufferData128_GAUSSIAN_5X5_08U, 20, gScenarioKernelData128_GAUSSIAN_5X5_08U, 2},
{28, 12, 2336, 0, 1, gScenarioBufferData129_GAUSSIAN_5X5_08U, 20, gScenarioKernelData129_GAUSSIAN_5X5_08U, 2},
{30, 12, 2488, 0, 1, gScenarioBufferData130_GAUSSIAN_5X5_08U, 20, gScenarioKernelData130_GAUSSIAN_5X5_08U, 2},
{32, 12, 2640, 0, 1, gScenarioBufferData131_GAUSSIAN_5X5_08U, 20, gScenarioKernelData131_GAUSSIAN_5X5_08U, 2},
{2, 14, 416, 0, 1, gScenarioBufferData132_GAUSSIAN_5X5_08U, 20, gScenarioKernelData132_GAUSSIAN_5X5_08U, 2},
{4, 14, 592, 0, 1, gScenarioBufferData133_GAUSSIAN_5X5_08U, 20, gScenarioKernelData133_GAUSSIAN_5X5_08U, 2},
{6, 14, 768, 0, 1, gScenarioBufferData134_GAUSSIAN_5X5_08U, 20, gScenarioKernelData134_GAUSSIAN_5X5_08U, 2},
{8, 14, 944, 0, 1, gScenarioBufferData135_GAUSSIAN_5X5_08U, 20, gScenarioKernelData135_GAUSSIAN_5X5_08U, 2},
{10, 14, 1120, 0, 1, gScenarioBufferData136_GAUSSIAN_5X5_08U, 20, gScenarioKernelData136_GAUSSIAN_5X5_08U, 2},
{12, 14, 1296, 0, 1, gScenarioBufferData137_GAUSSIAN_5X5_08U, 20, gScenarioKernelData137_GAUSSIAN_5X5_08U, 2},
{14, 14, 1472, 0, 1, gScenarioBufferData138_GAUSSIAN_5X5_08U, 20, gScenarioKernelData138_GAUSSIAN_5X5_08U, 2},
{16, 14, 1648, 0, 1, gScenarioBufferData139_GAUSSIAN_5X5_08U, 20, gScenarioKernelData139_GAUSSIAN_5X5_08U, 2},
{18, 14, 1824, 0, 1, gScenarioBufferData140_GAUSSIAN_5X5_08U, 20, gScenarioKernelData140_GAUSSIAN_5X5_08U, 2},
{20, 14, 2000, 0, 1, gScenarioBufferData141_GAUSSIAN_5X5_08U, 20, gScenarioKernelData141_GAUSSIAN_5X5_08U, 2},
{22, 14, 2176, 0, 1, gScenarioBufferData142_GAUSSIAN_5X5_08U, 20, gScenarioKernelData142_GAUSSIAN_5X5_08U, 2},
{24, 14, 2352, 0, 1, gScenarioBufferData143_GAUSSIAN_5X5_08U, 20, gScenarioKernelData143_GAUSSIAN_5X5_08U, 2},
{26, 14, 2528, 0, 1, gScenarioBufferData144_GAUSSIAN_5X5_08U, 20, gScenarioKernelData144_GAUSSIAN_5X5_08U, 2},
{28, 14, 2704, 0, 1, gScenarioBufferData145_GAUSSIAN_5X5_08U, 20, gScenarioKernelData145_GAUSSIAN_5X5_08U, 2},
{30, 14, 2880, 0, 1, gScenarioBufferData146_GAUSSIAN_5X5_08U, 20, gScenarioKernelData146_GAUSSIAN_5X5_08U, 2},
{32, 14, 3056, 0, 1, gScenarioBufferData147_GAUSSIAN_5X5_08U, 20, gScenarioKernelData147_GAUSSIAN_5X5_08U, 2},
{2, 16, 472, 0, 1, gScenarioBufferData148_GAUSSIAN_5X5_08U, 20, gScenarioKernelData148_GAUSSIAN_5X5_08U, 2},
{4, 16, 672, 0, 1, gScenarioBufferData149_GAUSSIAN_5X5_08U, 20, gScenarioKernelData149_GAUSSIAN_5X5_08U, 2},
{6, 16, 872, 0, 1, gScenarioBufferData150_GAUSSIAN_5X5_08U, 20, gScenarioKernelData150_GAUSSIAN_5X5_08U, 2},
{8, 16, 1072, 0, 1, gScenarioBufferData151_GAUSSIAN_5X5_08U, 20, gScenarioKernelData151_GAUSSIAN_5X5_08U, 2},
{10, 16, 1272, 0, 1, gScenarioBufferData152_GAUSSIAN_5X5_08U, 20, gScenarioKernelData152_GAUSSIAN_5X5_08U, 2},
{12, 16, 1472, 0, 1, gScenarioBufferData153_GAUSSIAN_5X5_08U, 20, gScenarioKernelData153_GAUSSIAN_5X5_08U, 2},
{14, 16, 1672, 0, 1, gScenarioBufferData154_GAUSSIAN_5X5_08U, 20, gScenarioKernelData154_GAUSSIAN_5X5_08U, 2},
{16, 16, 1872, 0, 1, gScenarioBufferData155_GAUSSIAN_5X5_08U, 20, gScenarioKernelData155_GAUSSIAN_5X5_08U, 2},
{18, 16, 2072, 0, 1, gScenarioBufferData156_GAUSSIAN_5X5_08U, 20, gScenarioKernelData156_GAUSSIAN_5X5_08U, 2},
{20, 16, 2272, 0, 1, gScenarioBufferData157_GAUSSIAN_5X5_08U, 20, gScenarioKernelData157_GAUSSIAN_5X5_08U, 2},
{22, 16, 2472, 0, 1, gScenarioBufferData158_GAUSSIAN_5X5_08U, 20, gScenarioKernelData158_GAUSSIAN_5X5_08U, 2},
{24, 16, 2672, 0, 1, gScenarioBufferData159_GAUSSIAN_5X5_08U, 20, gScenarioKernelData159_GAUSSIAN_5X5_08U, 2},
{26, 16, 2872, 0, 1, gScenarioBufferData160_GAUSSIAN_5X5_08U, 20, gScenarioKernelData160_GAUSSIAN_5X5_08U, 2},
{28, 16, 3072, 0, 1, gScenarioBufferData161_GAUSSIAN_5X5_08U, 20, gScenarioKernelData161_GAUSSIAN_5X5_08U, 2},
{30, 16, 3272, 0, 1, gScenarioBufferData162_GAUSSIAN_5X5_08U, 20, gScenarioKernelData162_GAUSSIAN_5X5_08U, 2},
{32, 16, 3472, 0, 1, gScenarioBufferData163_GAUSSIAN_5X5_08U, 20, gScenarioKernelData163_GAUSSIAN_5X5_08U, 2},
{2, 18, 528, 0, 1, gScenarioBufferData164_GAUSSIAN_5X5_08U, 20, gScenarioKernelData164_GAUSSIAN_5X5_08U, 2},
{4, 18, 752, 0, 1, gScenarioBufferData165_GAUSSIAN_5X5_08U, 20, gScenarioKernelData165_GAUSSIAN_5X5_08U, 2},
{6, 18, 976, 0, 1, gScenarioBufferData166_GAUSSIAN_5X5_08U, 20, gScenarioKernelData166_GAUSSIAN_5X5_08U, 2},
{8, 18, 1200, 0, 1, gScenarioBufferData167_GAUSSIAN_5X5_08U, 20, gScenarioKernelData167_GAUSSIAN_5X5_08U, 2},
{10, 18, 1424, 0, 1, gScenarioBufferData168_GAUSSIAN_5X5_08U, 20, gScenarioKernelData168_GAUSSIAN_5X5_08U, 2},
{12, 18, 1648, 0, 1, gScenarioBufferData169_GAUSSIAN_5X5_08U, 20, gScenarioKernelData169_GAUSSIAN_5X5_08U, 2},
{14, 18, 1872, 0, 1, gScenarioBufferData170_GAUSSIAN_5X5_08U, 20, gScenarioKernelData170_GAUSSIAN_5X5_08U, 2},
{16, 18, 2096, 0, 1, gScenarioBufferData171_GAUSSIAN_5X5_08U, 20, gScenarioKernelData171_GAUSSIAN_5X5_08U, 2},
{18, 18, 2320, 0, 1, gScenarioBufferData172_GAUSSIAN_5X5_08U, 20, gScenarioKernelData172_GAUSSIAN_5X5_08U, 2},
{20, 18, 2544, 0, 1, gScenarioBufferData173_GAUSSIAN_5X5_08U, 20, gScenarioKernelData173_GAUSSIAN_5X5_08U, 2},
{22, 18, 2768, 0, 1, gScenarioBufferData174_GAUSSIAN_5X5_08U, 20, gScenarioKernelData174_GAUSSIAN_5X5_08U, 2},
{24, 18, 2992, 0, 1, gScenarioBufferData175_GAUSSIAN_5X5_08U, 20, gScenarioKernelData175_GAUSSIAN_5X5_08U, 2},
{26, 18, 3216, 0, 1, gScenarioBufferData176_GAUSSIAN_5X5_08U, 20, gScenarioKernelData176_GAUSSIAN_5X5_08U, 2},
{28, 18, 3440, 0, 1, gScenarioBufferData177_GAUSSIAN_5X5_08U, 20, gScenarioKernelData177_GAUSSIAN_5X5_08U, 2},
{30, 18, 3664, 0, 1, gScenarioBufferData178_GAUSSIAN_5X5_08U, 20, gScenarioKernelData178_GAUSSIAN_5X5_08U, 2},
{2, 20, 584, 0, 1, gScenarioBufferData179_GAUSSIAN_5X5_08U, 20, gScenarioKernelData179_GAUSSIAN_5X5_08U, 2},
{4, 20, 832, 0, 1, gScenarioBufferData180_GAUSSIAN_5X5_08U, 20, gScenarioKernelData180_GAUSSIAN_5X5_08U, 2},
{6, 20, 1080, 0, 1, gScenarioBufferData181_GAUSSIAN_5X5_08U, 20, gScenarioKernelData181_GAUSSIAN_5X5_08U, 2},
{8, 20, 1328, 0, 1, gScenarioBufferData182_GAUSSIAN_5X5_08U, 20, gScenarioKernelData182_GAUSSIAN_5X5_08U, 2},
{10, 20, 1576, 0, 1, gScenarioBufferData183_GAUSSIAN_5X5_08U, 20, gScenarioKernelData183_GAUSSIAN_5X5_08U, 2},
{12, 20, 1824, 0, 1, gScenarioBufferData184_GAUSSIAN_5X5_08U, 20, gScenarioKernelData184_GAUSSIAN_5X5_08U, 2},
{14, 20, 2072, 0, 1, gScenarioBufferData185_GAUSSIAN_5X5_08U, 20, gScenarioKernelData185_GAUSSIAN_5X5_08U, 2},
{16, 20, 2320, 0, 1, gScenarioBufferData186_GAUSSIAN_5X5_08U, 20, gScenarioKernelData186_GAUSSIAN_5X5_08U, 2},
{18, 20, 2568, 0, 1, gScenarioBufferData187_GAUSSIAN_5X5_08U, 20, gScenarioKernelData187_GAUSSIAN_5X5_08U, 2},
{20, 20, 2816, 0, 1, gScenarioBufferData188_GAUSSIAN_5X5_08U, 20, gScenarioKernelData188_GAUSSIAN_5X5_08U, 2},
{22, 20, 3064, 0, 1, gScenarioBufferData189_GAUSSIAN_5X5_08U, 20, gScenarioKernelData189_GAUSSIAN_5X5_08U, 2},
{24, 20, 3312, 0, 1, gScenarioBufferData190_GAUSSIAN_5X5_08U, 20, gScenarioKernelData190_GAUSSIAN_5X5_08U, 2},
{26, 20, 3560, 0, 1, gScenarioBufferData191_GAUSSIAN_5X5_08U, 20, gScenarioKernelData191_GAUSSIAN_5X5_08U, 2},
{28, 20, 3808, 0, 1, gScenarioBufferData192_GAUSSIAN_5X5_08U, 20, gScenarioKernelData192_GAUSSIAN_5X5_08U, 2},
{2, 22, 640, 0, 1, gScenarioBufferData193_GAUSSIAN_5X5_08U, 20, gScenarioKernelData193_GAUSSIAN_5X5_08U, 2},
{4, 22, 912, 0, 1, gScenarioBufferData194_GAUSSIAN_5X5_08U, 20, gScenarioKernelData194_GAUSSIAN_5X5_08U, 2},
{6, 22, 1184, 0, 1, gScenarioBufferData195_GAUSSIAN_5X5_08U, 20, gScenarioKernelData195_GAUSSIAN_5X5_08U, 2},
{8, 22, 1456, 0, 1, gScenarioBufferData196_GAUSSIAN_5X5_08U, 20, gScenarioKernelData196_GAUSSIAN_5X5_08U, 2},
{10, 22, 1728, 0, 1, gScenarioBufferData197_GAUSSIAN_5X5_08U, 20, gScenarioKernelData197_GAUSSIAN_5X5_08U, 2},
{12, 22, 2000, 0, 1, gScenarioBufferData198_GAUSSIAN_5X5_08U, 20, gScenarioKernelData198_GAUSSIAN_5X5_08U, 2},
{14, 22, 2272, 0, 1, gScenarioBufferData199_GAUSSIAN_5X5_08U, 20, gScenarioKernelData199_GAUSSIAN_5X5_08U, 2},
{16, 22, 2544, 0, 1, gScenarioBufferData200_GAUSSIAN_5X5_08U, 20, gScenarioKernelData200_GAUSSIAN_5X5_08U, 2},
{18, 22, 2816, 0, 1, gScenarioBufferData201_GAUSSIAN_5X5_08U, 20, gScenarioKernelData201_GAUSSIAN_5X5_08U, 2},
{20, 22, 3088, 0, 1, gScenarioBufferData202_GAUSSIAN_5X5_08U, 20, gScenarioKernelData202_GAUSSIAN_5X5_08U, 2},
{22, 22, 3360, 0, 1, gScenarioBufferData203_GAUSSIAN_5X5_08U, 20, gScenarioKernelData203_GAUSSIAN_5X5_08U, 2},
{24, 22, 3632, 0, 1, gScenarioBufferData204_GAUSSIAN_5X5_08U, 20, gScenarioKernelData204_GAUSSIAN_5X5_08U, 2},
{2, 24, 696, 0, 1, gScenarioBufferData205_GAUSSIAN_5X5_08U, 20, gScenarioKernelData205_GAUSSIAN_5X5_08U, 2},
{4, 24, 992, 0, 1, gScenarioBufferData206_GAUSSIAN_5X5_08U, 20, gScenarioKernelData206_GAUSSIAN_5X5_08U, 2},
{6, 24, 1288, 0, 1, gScenarioBufferData207_GAUSSIAN_5X5_08U, 20, gScenarioKernelData207_GAUSSIAN_5X5_08U, 2},
{8, 24, 1584, 0, 1, gScenarioBufferData208_GAUSSIAN_5X5_08U, 20, gScenarioKernelData208_GAUSSIAN_5X5_08U, 2},
{10, 24, 1880, 0, 1, gScenarioBufferData209_GAUSSIAN_5X5_08U, 20, gScenarioKernelData209_GAUSSIAN_5X5_08U, 2},
{12, 24, 2176, 0, 1, gScenarioBufferData210_GAUSSIAN_5X5_08U, 20, gScenarioKernelData210_GAUSSIAN_5X5_08U, 2},
{14, 24, 2472, 0, 1, gScenarioBufferData211_GAUSSIAN_5X5_08U, 20, gScenarioKernelData211_GAUSSIAN_5X5_08U, 2},
{16, 24, 2768, 0, 1, gScenarioBufferData212_GAUSSIAN_5X5_08U, 20, gScenarioKernelData212_GAUSSIAN_5X5_08U, 2},
{18, 24, 3064, 0, 1, gScenarioBufferData213_GAUSSIAN_5X5_08U, 20, gScenarioKernelData213_GAUSSIAN_5X5_08U, 2},
{20, 24, 3360, 0, 1, gScenarioBufferData214_GAUSSIAN_5X5_08U, 20, gScenarioKernelData214_GAUSSIAN_5X5_08U, 2},
{22, 24, 3656, 0, 1, gScenarioBufferData215_GAUSSIAN_5X5_08U, 20, gScenarioKernelData215_GAUSSIAN_5X5_08U, 2},
{2, 26, 752, 0, 1, gScenarioBufferData216_GAUSSIAN_5X5_08U, 20, gScenarioKernelData216_GAUSSIAN_5X5_08U, 2},
{4, 26, 1072, 0, 1, gScenarioBufferData217_GAUSSIAN_5X5_08U, 20, gScenarioKernelData217_GAUSSIAN_5X5_08U, 2},
{6, 26, 1392, 0, 1, gScenarioBufferData218_GAUSSIAN_5X5_08U, 20, gScenarioKernelData218_GAUSSIAN_5X5_08U, 2},
{8, 26, 1712, 0, 1, gScenarioBufferData219_GAUSSIAN_5X5_08U, 20, gScenarioKernelData219_GAUSSIAN_5X5_08U, 2},
{10, 26, 2032, 0, 1, gScenarioBufferData220_GAUSSIAN_5X5_08U, 20, gScenarioKernelData220_GAUSSIAN_5X5_08U, 2},
{12, 26, 2352, 0, 1, gScenarioBufferData221_GAUSSIAN_5X5_08U, 20, gScenarioKernelData221_GAUSSIAN_5X5_08U, 2},
{14, 26, 2672, 0, 1, gScenarioBufferData222_GAUSSIAN_5X5_08U, 20, gScenarioKernelData222_GAUSSIAN_5X5_08U, 2},
{16, 26, 2992, 0, 1, gScenarioBufferData223_GAUSSIAN_5X5_08U, 20, gScenarioKernelData223_GAUSSIAN_5X5_08U, 2},
{18, 26, 3312, 0, 1, gScenarioBufferData224_GAUSSIAN_5X5_08U, 20, gScenarioKernelData224_GAUSSIAN_5X5_08U, 2},
{20, 26, 3632, 0, 1, gScenarioBufferData225_GAUSSIAN_5X5_08U, 20, gScenarioKernelData225_GAUSSIAN_5X5_08U, 2},
{2, 28, 808, 0, 1, gScenarioBufferData226_GAUSSIAN_5X5_08U, 20, gScenarioKernelData226_GAUSSIAN_5X5_08U, 2},
{4, 28, 1152, 0, 1, gScenarioBufferData227_GAUSSIAN_5X5_08U, 20, gScenarioKernelData227_GAUSSIAN_5X5_08U, 2},
{6, 28, 1496, 0, 1, gScenarioBufferData228_GAUSSIAN_5X5_08U, 20, gScenarioKernelData228_GAUSSIAN_5X5_08U, 2},
{8, 28, 1840, 0, 1, gScenarioBufferData229_GAUSSIAN_5X5_08U, 20, gScenarioKernelData229_GAUSSIAN_5X5_08U, 2},
{10, 28, 2184, 0, 1, gScenarioBufferData230_GAUSSIAN_5X5_08U, 20, gScenarioKernelData230_GAUSSIAN_5X5_08U, 2},
{12, 28, 2528, 0, 1, gScenarioBufferData231_GAUSSIAN_5X5_08U, 20, gScenarioKernelData231_GAUSSIAN_5X5_08U, 2},
{14, 28, 2872, 0, 1, gScenarioBufferData232_GAUSSIAN_5X5_08U, 20, gScenarioKernelData232_GAUSSIAN_5X5_08U, 2},
{16, 28, 3216, 0, 1, gScenarioBufferData233_GAUSSIAN_5X5_08U, 20, gScenarioKernelData233_GAUSSIAN_5X5_08U, 2},
{18, 28, 3560, 0, 1, gScenarioBufferData234_GAUSSIAN_5X5_08U, 20, gScenarioKernelData234_GAUSSIAN_5X5_08U, 2},
{2, 30, 864, 0, 1, gScenarioBufferData235_GAUSSIAN_5X5_08U, 20, gScenarioKernelData235_GAUSSIAN_5X5_08U, 2},
{4, 30, 1232, 0, 1, gScenarioBufferData236_GAUSSIAN_5X5_08U, 20, gScenarioKernelData236_GAUSSIAN_5X5_08U, 2},
{6, 30, 1600, 0, 1, gScenarioBufferData237_GAUSSIAN_5X5_08U, 20, gScenarioKernelData237_GAUSSIAN_5X5_08U, 2},
{8, 30, 1968, 0, 1, gScenarioBufferData238_GAUSSIAN_5X5_08U, 20, gScenarioKernelData238_GAUSSIAN_5X5_08U, 2},
{10, 30, 2336, 0, 1, gScenarioBufferData239_GAUSSIAN_5X5_08U, 20, gScenarioKernelData239_GAUSSIAN_5X5_08U, 2},
{12, 30, 2704, 0, 1, gScenarioBufferData240_GAUSSIAN_5X5_08U, 20, gScenarioKernelData240_GAUSSIAN_5X5_08U, 2},
{14, 30, 3072, 0, 1, gScenarioBufferData241_GAUSSIAN_5X5_08U, 20, gScenarioKernelData241_GAUSSIAN_5X5_08U, 2},
{16, 30, 3440, 0, 1, gScenarioBufferData242_GAUSSIAN_5X5_08U, 20, gScenarioKernelData242_GAUSSIAN_5X5_08U, 2},
{18, 30, 3808, 0, 1, gScenarioBufferData243_GAUSSIAN_5X5_08U, 20, gScenarioKernelData243_GAUSSIAN_5X5_08U, 2},
{2, 32, 920, 0, 1, gScenarioBufferData244_GAUSSIAN_5X5_08U, 20, gScenarioKernelData244_GAUSSIAN_5X5_08U, 2},
{4, 32, 1312, 0, 1, gScenarioBufferData245_GAUSSIAN_5X5_08U, 20, gScenarioKernelData245_GAUSSIAN_5X5_08U, 2},
{6, 32, 1704, 0, 1, gScenarioBufferData246_GAUSSIAN_5X5_08U, 20, gScenarioKernelData246_GAUSSIAN_5X5_08U, 2},
{8, 32, 2096, 0, 1, gScenarioBufferData247_GAUSSIAN_5X5_08U, 20, gScenarioKernelData247_GAUSSIAN_5X5_08U, 2},
{10, 32, 2488, 0, 1, gScenarioBufferData248_GAUSSIAN_5X5_08U, 20, gScenarioKernelData248_GAUSSIAN_5X5_08U, 2},
{12, 32, 2880, 0, 1, gScenarioBufferData249_GAUSSIAN_5X5_08U, 20, gScenarioKernelData249_GAUSSIAN_5X5_08U, 2},
{14, 32, 3272, 0, 1, gScenarioBufferData250_GAUSSIAN_5X5_08U, 20, gScenarioKernelData250_GAUSSIAN_5X5_08U, 2},
{16, 32, 3664, 0, 1, gScenarioBufferData251_GAUSSIAN_5X5_08U, 20, gScenarioKernelData251_GAUSSIAN_5X5_08U, 2}
};

static acf_scenario_list gScenarioList_GAUSSIAN_5X5_08U = {
252, //number of scenarios
gScenarioArray_GAUSSIAN_5X5_08U};
//**************************************************************

class GAUSSIAN_5X5_08U : public ACF_Process_APU
{
public:
   GAUSSIAN_5X5_08U(int32_t apex_id = 0) : ACF_Process_APU(apex_id)
   {} 

   int32_t Initialize()
   {
      int32_t lRetVal = 0;

      if (!Initialized()) //initialization steps that only need to occur once
      {
         SetProcessIdentifier("GAUSSIAN_5X5_08U");
         SetApuLoadInfo(GAUSSIAN_5X5_08U_LOAD_SEGMENTS,
                        GAUSSIAN_5X5_08U_LOAD_PMEM, GAUSSIAN_5X5_08U_LOAD_PMEM_SIZE,
                        GAUSSIAN_5X5_08U_LOAD_DMEM, GAUSSIAN_5X5_08U_LOAD_DMEM_SIZE,
                        0, 0); //assuming _LOAD_CMEM does not exist
         FlagSpatialDep();

         //***NOTE: the order in which the following ports are added is meaningful; do not change!

         AddPort("INPUT_0", ICP_DATATYPE_08U, 1, 1, 2, 1, 0, 0, 0, 0, 0, 0, 0, 0x2020202);
         AddPort("OUTPUT_0", ICP_DATATYPE_08U, 1, 1, 2, 1, 1, 0, 0, 0, 0, 0, 1);

         CfgScenarios(&gScenarioList_GAUSSIAN_5X5_08U);

         FlagAsInitialized();
      }

      lRetVal = SelectApuConfiguration(mApuCfg, mApexId); //by default mApuCfg = ACF_APU_CFG__APEX0_DEFAULT and mApexId = 0

      return lRetVal;
   }
};

#endif //_ACF_PROCESS_APU_GAUSSIAN_5X5_08U
