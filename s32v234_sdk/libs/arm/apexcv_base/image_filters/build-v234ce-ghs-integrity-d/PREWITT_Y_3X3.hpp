#ifndef _ACF_PROCESS_APU_PREWITT_Y_3X3
#define _ACF_PROCESS_APU_PREWITT_Y_3X3

#include <acf_process_apu.h>
#include <PREWITT_Y_3X3_APU_LOAD.h> //APU load associated with this process
#include <stdint.h>


//SCENARIO LIST*************************************************
static acf_scenario_buffer_data gScenarioBufferData0_PREWITT_Y_3X3[] = {{2, 1, 4, 0, 0x2211}, {2, 1, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData1_PREWITT_Y_3X3[] = {{4, 1, 4, 0, 0x2211}, {4, 1, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData2_PREWITT_Y_3X3[] = {{6, 1, 4, 0, 0x2211}, {6, 1, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData3_PREWITT_Y_3X3[] = {{8, 1, 4, 0, 0x2211}, {8, 1, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData4_PREWITT_Y_3X3[] = {{10, 1, 4, 0, 0x2211}, {10, 1, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData5_PREWITT_Y_3X3[] = {{12, 1, 4, 0, 0x2211}, {12, 1, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData6_PREWITT_Y_3X3[] = {{14, 1, 4, 0, 0x2211}, {14, 1, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData7_PREWITT_Y_3X3[] = {{16, 1, 4, 0, 0x2211}, {16, 1, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData8_PREWITT_Y_3X3[] = {{18, 1, 4, 0, 0x2211}, {18, 1, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData9_PREWITT_Y_3X3[] = {{20, 1, 4, 0, 0x2211}, {20, 1, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData10_PREWITT_Y_3X3[] = {{22, 1, 4, 0, 0x2211}, {22, 1, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData11_PREWITT_Y_3X3[] = {{24, 1, 4, 0, 0x2211}, {24, 1, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData12_PREWITT_Y_3X3[] = {{26, 1, 4, 0, 0x2211}, {26, 1, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData13_PREWITT_Y_3X3[] = {{28, 1, 4, 0, 0x2211}, {28, 1, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData14_PREWITT_Y_3X3[] = {{30, 1, 4, 0, 0x2211}, {30, 1, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData15_PREWITT_Y_3X3[] = {{32, 1, 4, 0, 0x2211}, {32, 1, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData16_PREWITT_Y_3X3[] = {{48, 1, 4, 0, 0x2211}, {48, 1, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData17_PREWITT_Y_3X3[] = {{64, 1, 4, 0, 0x2211}, {64, 1, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData18_PREWITT_Y_3X3[] = {{2, 2, 4, 0, 0x2211}, {2, 2, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData19_PREWITT_Y_3X3[] = {{4, 2, 4, 0, 0x2211}, {4, 2, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData20_PREWITT_Y_3X3[] = {{6, 2, 4, 0, 0x2211}, {6, 2, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData21_PREWITT_Y_3X3[] = {{8, 2, 4, 0, 0x2211}, {8, 2, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData22_PREWITT_Y_3X3[] = {{10, 2, 4, 0, 0x2211}, {10, 2, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData23_PREWITT_Y_3X3[] = {{12, 2, 4, 0, 0x2211}, {12, 2, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData24_PREWITT_Y_3X3[] = {{14, 2, 4, 0, 0x2211}, {14, 2, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData25_PREWITT_Y_3X3[] = {{16, 2, 4, 0, 0x2211}, {16, 2, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData26_PREWITT_Y_3X3[] = {{18, 2, 4, 0, 0x2211}, {18, 2, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData27_PREWITT_Y_3X3[] = {{20, 2, 4, 0, 0x2211}, {20, 2, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData28_PREWITT_Y_3X3[] = {{22, 2, 4, 0, 0x2211}, {22, 2, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData29_PREWITT_Y_3X3[] = {{24, 2, 4, 0, 0x2211}, {24, 2, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData30_PREWITT_Y_3X3[] = {{26, 2, 4, 0, 0x2211}, {26, 2, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData31_PREWITT_Y_3X3[] = {{28, 2, 4, 0, 0x2211}, {28, 2, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData32_PREWITT_Y_3X3[] = {{30, 2, 4, 0, 0x2211}, {30, 2, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData33_PREWITT_Y_3X3[] = {{32, 2, 4, 0, 0x2211}, {32, 2, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData34_PREWITT_Y_3X3[] = {{48, 2, 4, 0, 0x2211}, {48, 2, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData35_PREWITT_Y_3X3[] = {{64, 2, 4, 0, 0x2211}, {64, 2, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData36_PREWITT_Y_3X3[] = {{2, 4, 4, 0, 0x2211}, {2, 4, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData37_PREWITT_Y_3X3[] = {{4, 4, 4, 0, 0x2211}, {4, 4, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData38_PREWITT_Y_3X3[] = {{6, 4, 4, 0, 0x2211}, {6, 4, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData39_PREWITT_Y_3X3[] = {{8, 4, 4, 0, 0x2211}, {8, 4, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData40_PREWITT_Y_3X3[] = {{10, 4, 4, 0, 0x2211}, {10, 4, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData41_PREWITT_Y_3X3[] = {{12, 4, 4, 0, 0x2211}, {12, 4, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData42_PREWITT_Y_3X3[] = {{14, 4, 4, 0, 0x2211}, {14, 4, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData43_PREWITT_Y_3X3[] = {{16, 4, 4, 0, 0x2211}, {16, 4, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData44_PREWITT_Y_3X3[] = {{18, 4, 4, 0, 0x2211}, {18, 4, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData45_PREWITT_Y_3X3[] = {{20, 4, 4, 0, 0x2211}, {20, 4, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData46_PREWITT_Y_3X3[] = {{22, 4, 4, 0, 0x2211}, {22, 4, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData47_PREWITT_Y_3X3[] = {{24, 4, 4, 0, 0x2211}, {24, 4, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData48_PREWITT_Y_3X3[] = {{26, 4, 4, 0, 0x2211}, {26, 4, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData49_PREWITT_Y_3X3[] = {{28, 4, 4, 0, 0x2211}, {28, 4, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData50_PREWITT_Y_3X3[] = {{30, 4, 4, 0, 0x2211}, {30, 4, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData51_PREWITT_Y_3X3[] = {{32, 4, 4, 0, 0x2211}, {32, 4, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData52_PREWITT_Y_3X3[] = {{48, 4, 4, 0, 0x2211}, {48, 4, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData53_PREWITT_Y_3X3[] = {{64, 4, 4, 0, 0x2211}, {64, 4, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData54_PREWITT_Y_3X3[] = {{2, 6, 4, 0, 0x2211}, {2, 6, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData55_PREWITT_Y_3X3[] = {{4, 6, 4, 0, 0x2211}, {4, 6, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData56_PREWITT_Y_3X3[] = {{6, 6, 4, 0, 0x2211}, {6, 6, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData57_PREWITT_Y_3X3[] = {{8, 6, 4, 0, 0x2211}, {8, 6, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData58_PREWITT_Y_3X3[] = {{10, 6, 4, 0, 0x2211}, {10, 6, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData59_PREWITT_Y_3X3[] = {{12, 6, 4, 0, 0x2211}, {12, 6, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData60_PREWITT_Y_3X3[] = {{14, 6, 4, 0, 0x2211}, {14, 6, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData61_PREWITT_Y_3X3[] = {{16, 6, 4, 0, 0x2211}, {16, 6, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData62_PREWITT_Y_3X3[] = {{18, 6, 4, 0, 0x2211}, {18, 6, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData63_PREWITT_Y_3X3[] = {{20, 6, 4, 0, 0x2211}, {20, 6, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData64_PREWITT_Y_3X3[] = {{22, 6, 4, 0, 0x2211}, {22, 6, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData65_PREWITT_Y_3X3[] = {{24, 6, 4, 0, 0x2211}, {24, 6, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData66_PREWITT_Y_3X3[] = {{26, 6, 4, 0, 0x2211}, {26, 6, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData67_PREWITT_Y_3X3[] = {{28, 6, 4, 0, 0x2211}, {28, 6, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData68_PREWITT_Y_3X3[] = {{30, 6, 4, 0, 0x2211}, {30, 6, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData69_PREWITT_Y_3X3[] = {{32, 6, 4, 0, 0x2211}, {32, 6, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData70_PREWITT_Y_3X3[] = {{48, 6, 4, 0, 0x2211}, {48, 6, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData71_PREWITT_Y_3X3[] = {{64, 6, 4, 0, 0x2211}, {64, 6, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData72_PREWITT_Y_3X3[] = {{2, 8, 4, 0, 0x2211}, {2, 8, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData73_PREWITT_Y_3X3[] = {{4, 8, 4, 0, 0x2211}, {4, 8, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData74_PREWITT_Y_3X3[] = {{6, 8, 4, 0, 0x2211}, {6, 8, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData75_PREWITT_Y_3X3[] = {{8, 8, 4, 0, 0x2211}, {8, 8, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData76_PREWITT_Y_3X3[] = {{10, 8, 4, 0, 0x2211}, {10, 8, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData77_PREWITT_Y_3X3[] = {{12, 8, 4, 0, 0x2211}, {12, 8, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData78_PREWITT_Y_3X3[] = {{14, 8, 4, 0, 0x2211}, {14, 8, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData79_PREWITT_Y_3X3[] = {{16, 8, 4, 0, 0x2211}, {16, 8, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData80_PREWITT_Y_3X3[] = {{18, 8, 4, 0, 0x2211}, {18, 8, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData81_PREWITT_Y_3X3[] = {{20, 8, 4, 0, 0x2211}, {20, 8, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData82_PREWITT_Y_3X3[] = {{22, 8, 4, 0, 0x2211}, {22, 8, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData83_PREWITT_Y_3X3[] = {{24, 8, 4, 0, 0x2211}, {24, 8, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData84_PREWITT_Y_3X3[] = {{26, 8, 4, 0, 0x2211}, {26, 8, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData85_PREWITT_Y_3X3[] = {{28, 8, 4, 0, 0x2211}, {28, 8, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData86_PREWITT_Y_3X3[] = {{30, 8, 4, 0, 0x2211}, {30, 8, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData87_PREWITT_Y_3X3[] = {{32, 8, 4, 0, 0x2211}, {32, 8, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData88_PREWITT_Y_3X3[] = {{48, 8, 4, 0, 0x2211}, {48, 8, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData89_PREWITT_Y_3X3[] = {{2, 10, 4, 0, 0x2211}, {2, 10, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData90_PREWITT_Y_3X3[] = {{4, 10, 4, 0, 0x2211}, {4, 10, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData91_PREWITT_Y_3X3[] = {{6, 10, 4, 0, 0x2211}, {6, 10, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData92_PREWITT_Y_3X3[] = {{8, 10, 4, 0, 0x2211}, {8, 10, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData93_PREWITT_Y_3X3[] = {{10, 10, 4, 0, 0x2211}, {10, 10, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData94_PREWITT_Y_3X3[] = {{12, 10, 4, 0, 0x2211}, {12, 10, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData95_PREWITT_Y_3X3[] = {{14, 10, 4, 0, 0x2211}, {14, 10, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData96_PREWITT_Y_3X3[] = {{16, 10, 4, 0, 0x2211}, {16, 10, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData97_PREWITT_Y_3X3[] = {{18, 10, 4, 0, 0x2211}, {18, 10, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData98_PREWITT_Y_3X3[] = {{20, 10, 4, 0, 0x2211}, {20, 10, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData99_PREWITT_Y_3X3[] = {{22, 10, 4, 0, 0x2211}, {22, 10, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData100_PREWITT_Y_3X3[] = {{24, 10, 4, 0, 0x2211}, {24, 10, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData101_PREWITT_Y_3X3[] = {{26, 10, 4, 0, 0x2211}, {26, 10, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData102_PREWITT_Y_3X3[] = {{28, 10, 4, 0, 0x2211}, {28, 10, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData103_PREWITT_Y_3X3[] = {{30, 10, 4, 0, 0x2211}, {30, 10, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData104_PREWITT_Y_3X3[] = {{32, 10, 4, 0, 0x2211}, {32, 10, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData105_PREWITT_Y_3X3[] = {{2, 12, 4, 0, 0x2211}, {2, 12, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData106_PREWITT_Y_3X3[] = {{4, 12, 4, 0, 0x2211}, {4, 12, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData107_PREWITT_Y_3X3[] = {{6, 12, 4, 0, 0x2211}, {6, 12, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData108_PREWITT_Y_3X3[] = {{8, 12, 4, 0, 0x2211}, {8, 12, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData109_PREWITT_Y_3X3[] = {{10, 12, 4, 0, 0x2211}, {10, 12, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData110_PREWITT_Y_3X3[] = {{12, 12, 4, 0, 0x2211}, {12, 12, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData111_PREWITT_Y_3X3[] = {{14, 12, 4, 0, 0x2211}, {14, 12, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData112_PREWITT_Y_3X3[] = {{16, 12, 4, 0, 0x2211}, {16, 12, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData113_PREWITT_Y_3X3[] = {{18, 12, 4, 0, 0x2211}, {18, 12, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData114_PREWITT_Y_3X3[] = {{20, 12, 4, 0, 0x2211}, {20, 12, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData115_PREWITT_Y_3X3[] = {{22, 12, 4, 0, 0x2211}, {22, 12, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData116_PREWITT_Y_3X3[] = {{24, 12, 4, 0, 0x2211}, {24, 12, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData117_PREWITT_Y_3X3[] = {{26, 12, 4, 0, 0x2211}, {26, 12, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData118_PREWITT_Y_3X3[] = {{28, 12, 4, 0, 0x2211}, {28, 12, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData119_PREWITT_Y_3X3[] = {{30, 12, 4, 0, 0x2211}, {30, 12, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData120_PREWITT_Y_3X3[] = {{32, 12, 4, 0, 0x2211}, {32, 12, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData121_PREWITT_Y_3X3[] = {{2, 14, 4, 0, 0x2211}, {2, 14, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData122_PREWITT_Y_3X3[] = {{4, 14, 4, 0, 0x2211}, {4, 14, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData123_PREWITT_Y_3X3[] = {{6, 14, 4, 0, 0x2211}, {6, 14, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData124_PREWITT_Y_3X3[] = {{8, 14, 4, 0, 0x2211}, {8, 14, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData125_PREWITT_Y_3X3[] = {{10, 14, 4, 0, 0x2211}, {10, 14, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData126_PREWITT_Y_3X3[] = {{12, 14, 4, 0, 0x2211}, {12, 14, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData127_PREWITT_Y_3X3[] = {{14, 14, 4, 0, 0x2211}, {14, 14, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData128_PREWITT_Y_3X3[] = {{16, 14, 4, 0, 0x2211}, {16, 14, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData129_PREWITT_Y_3X3[] = {{18, 14, 4, 0, 0x2211}, {18, 14, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData130_PREWITT_Y_3X3[] = {{20, 14, 4, 0, 0x2211}, {20, 14, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData131_PREWITT_Y_3X3[] = {{22, 14, 4, 0, 0x2211}, {22, 14, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData132_PREWITT_Y_3X3[] = {{24, 14, 4, 0, 0x2211}, {24, 14, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData133_PREWITT_Y_3X3[] = {{26, 14, 4, 0, 0x2211}, {26, 14, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData134_PREWITT_Y_3X3[] = {{28, 14, 4, 0, 0x2211}, {28, 14, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData135_PREWITT_Y_3X3[] = {{30, 14, 4, 0, 0x2211}, {30, 14, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData136_PREWITT_Y_3X3[] = {{2, 16, 4, 0, 0x2211}, {2, 16, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData137_PREWITT_Y_3X3[] = {{4, 16, 4, 0, 0x2211}, {4, 16, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData138_PREWITT_Y_3X3[] = {{6, 16, 4, 0, 0x2211}, {6, 16, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData139_PREWITT_Y_3X3[] = {{8, 16, 4, 0, 0x2211}, {8, 16, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData140_PREWITT_Y_3X3[] = {{10, 16, 4, 0, 0x2211}, {10, 16, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData141_PREWITT_Y_3X3[] = {{12, 16, 4, 0, 0x2211}, {12, 16, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData142_PREWITT_Y_3X3[] = {{14, 16, 4, 0, 0x2211}, {14, 16, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData143_PREWITT_Y_3X3[] = {{16, 16, 4, 0, 0x2211}, {16, 16, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData144_PREWITT_Y_3X3[] = {{18, 16, 4, 0, 0x2211}, {18, 16, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData145_PREWITT_Y_3X3[] = {{20, 16, 4, 0, 0x2211}, {20, 16, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData146_PREWITT_Y_3X3[] = {{22, 16, 4, 0, 0x2211}, {22, 16, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData147_PREWITT_Y_3X3[] = {{24, 16, 4, 0, 0x2211}, {24, 16, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData148_PREWITT_Y_3X3[] = {{26, 16, 4, 0, 0x2211}, {26, 16, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData149_PREWITT_Y_3X3[] = {{2, 18, 4, 0, 0x2211}, {2, 18, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData150_PREWITT_Y_3X3[] = {{4, 18, 4, 0, 0x2211}, {4, 18, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData151_PREWITT_Y_3X3[] = {{6, 18, 4, 0, 0x2211}, {6, 18, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData152_PREWITT_Y_3X3[] = {{8, 18, 4, 0, 0x2211}, {8, 18, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData153_PREWITT_Y_3X3[] = {{10, 18, 4, 0, 0x2211}, {10, 18, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData154_PREWITT_Y_3X3[] = {{12, 18, 4, 0, 0x2211}, {12, 18, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData155_PREWITT_Y_3X3[] = {{14, 18, 4, 0, 0x2211}, {14, 18, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData156_PREWITT_Y_3X3[] = {{16, 18, 4, 0, 0x2211}, {16, 18, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData157_PREWITT_Y_3X3[] = {{18, 18, 4, 0, 0x2211}, {18, 18, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData158_PREWITT_Y_3X3[] = {{20, 18, 4, 0, 0x2211}, {20, 18, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData159_PREWITT_Y_3X3[] = {{22, 18, 4, 0, 0x2211}, {22, 18, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData160_PREWITT_Y_3X3[] = {{24, 18, 4, 0, 0x2211}, {24, 18, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData161_PREWITT_Y_3X3[] = {{2, 20, 4, 0, 0x2211}, {2, 20, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData162_PREWITT_Y_3X3[] = {{4, 20, 4, 0, 0x2211}, {4, 20, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData163_PREWITT_Y_3X3[] = {{6, 20, 4, 0, 0x2211}, {6, 20, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData164_PREWITT_Y_3X3[] = {{8, 20, 4, 0, 0x2211}, {8, 20, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData165_PREWITT_Y_3X3[] = {{10, 20, 4, 0, 0x2211}, {10, 20, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData166_PREWITT_Y_3X3[] = {{12, 20, 4, 0, 0x2211}, {12, 20, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData167_PREWITT_Y_3X3[] = {{14, 20, 4, 0, 0x2211}, {14, 20, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData168_PREWITT_Y_3X3[] = {{16, 20, 4, 0, 0x2211}, {16, 20, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData169_PREWITT_Y_3X3[] = {{18, 20, 4, 0, 0x2211}, {18, 20, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData170_PREWITT_Y_3X3[] = {{20, 20, 4, 0, 0x2211}, {20, 20, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData171_PREWITT_Y_3X3[] = {{2, 22, 4, 0, 0x2211}, {2, 22, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData172_PREWITT_Y_3X3[] = {{4, 22, 4, 0, 0x2211}, {4, 22, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData173_PREWITT_Y_3X3[] = {{6, 22, 4, 0, 0x2211}, {6, 22, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData174_PREWITT_Y_3X3[] = {{8, 22, 4, 0, 0x2211}, {8, 22, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData175_PREWITT_Y_3X3[] = {{10, 22, 4, 0, 0x2211}, {10, 22, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData176_PREWITT_Y_3X3[] = {{12, 22, 4, 0, 0x2211}, {12, 22, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData177_PREWITT_Y_3X3[] = {{14, 22, 4, 0, 0x2211}, {14, 22, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData178_PREWITT_Y_3X3[] = {{16, 22, 4, 0, 0x2211}, {16, 22, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData179_PREWITT_Y_3X3[] = {{18, 22, 4, 0, 0x2211}, {18, 22, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData180_PREWITT_Y_3X3[] = {{2, 24, 4, 0, 0x2211}, {2, 24, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData181_PREWITT_Y_3X3[] = {{4, 24, 4, 0, 0x2211}, {4, 24, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData182_PREWITT_Y_3X3[] = {{6, 24, 4, 0, 0x2211}, {6, 24, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData183_PREWITT_Y_3X3[] = {{8, 24, 4, 0, 0x2211}, {8, 24, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData184_PREWITT_Y_3X3[] = {{10, 24, 4, 0, 0x2211}, {10, 24, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData185_PREWITT_Y_3X3[] = {{12, 24, 4, 0, 0x2211}, {12, 24, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData186_PREWITT_Y_3X3[] = {{14, 24, 4, 0, 0x2211}, {14, 24, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData187_PREWITT_Y_3X3[] = {{16, 24, 4, 0, 0x2211}, {16, 24, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData188_PREWITT_Y_3X3[] = {{2, 26, 4, 0, 0x2211}, {2, 26, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData189_PREWITT_Y_3X3[] = {{4, 26, 4, 0, 0x2211}, {4, 26, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData190_PREWITT_Y_3X3[] = {{6, 26, 4, 0, 0x2211}, {6, 26, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData191_PREWITT_Y_3X3[] = {{8, 26, 4, 0, 0x2211}, {8, 26, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData192_PREWITT_Y_3X3[] = {{10, 26, 4, 0, 0x2211}, {10, 26, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData193_PREWITT_Y_3X3[] = {{12, 26, 4, 0, 0x2211}, {12, 26, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData194_PREWITT_Y_3X3[] = {{14, 26, 4, 0, 0x2211}, {14, 26, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData195_PREWITT_Y_3X3[] = {{16, 26, 4, 0, 0x2211}, {16, 26, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData196_PREWITT_Y_3X3[] = {{2, 28, 4, 0, 0x2211}, {2, 28, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData197_PREWITT_Y_3X3[] = {{4, 28, 4, 0, 0x2211}, {4, 28, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData198_PREWITT_Y_3X3[] = {{6, 28, 4, 0, 0x2211}, {6, 28, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData199_PREWITT_Y_3X3[] = {{8, 28, 4, 0, 0x2211}, {8, 28, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData200_PREWITT_Y_3X3[] = {{10, 28, 4, 0, 0x2211}, {10, 28, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData201_PREWITT_Y_3X3[] = {{12, 28, 4, 0, 0x2211}, {12, 28, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData202_PREWITT_Y_3X3[] = {{14, 28, 4, 0, 0x2211}, {14, 28, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData203_PREWITT_Y_3X3[] = {{2, 30, 4, 0, 0x2211}, {2, 30, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData204_PREWITT_Y_3X3[] = {{4, 30, 4, 0, 0x2211}, {4, 30, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData205_PREWITT_Y_3X3[] = {{6, 30, 4, 0, 0x2211}, {6, 30, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData206_PREWITT_Y_3X3[] = {{8, 30, 4, 0, 0x2211}, {8, 30, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData207_PREWITT_Y_3X3[] = {{10, 30, 4, 0, 0x2211}, {10, 30, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData208_PREWITT_Y_3X3[] = {{12, 30, 4, 0, 0x2211}, {12, 30, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData209_PREWITT_Y_3X3[] = {{2, 32, 4, 0, 0x2211}, {2, 32, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData210_PREWITT_Y_3X3[] = {{4, 32, 4, 0, 0x2211}, {4, 32, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData211_PREWITT_Y_3X3[] = {{6, 32, 4, 0, 0x2211}, {6, 32, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData212_PREWITT_Y_3X3[] = {{8, 32, 4, 0, 0x2211}, {8, 32, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData213_PREWITT_Y_3X3[] = {{10, 32, 4, 0, 0x2211}, {10, 32, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData214_PREWITT_Y_3X3[] = {{12, 32, 4, 0, 0x2211}, {12, 32, 2, 1, 0x0}};

static acf_scenario_kernel_data gScenarioKernelData0_PREWITT_Y_3X3[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData1_PREWITT_Y_3X3[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData2_PREWITT_Y_3X3[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData3_PREWITT_Y_3X3[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData4_PREWITT_Y_3X3[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData5_PREWITT_Y_3X3[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData6_PREWITT_Y_3X3[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData7_PREWITT_Y_3X3[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData8_PREWITT_Y_3X3[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData9_PREWITT_Y_3X3[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData10_PREWITT_Y_3X3[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData11_PREWITT_Y_3X3[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData12_PREWITT_Y_3X3[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData13_PREWITT_Y_3X3[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData14_PREWITT_Y_3X3[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData15_PREWITT_Y_3X3[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData16_PREWITT_Y_3X3[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData17_PREWITT_Y_3X3[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData18_PREWITT_Y_3X3[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData19_PREWITT_Y_3X3[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData20_PREWITT_Y_3X3[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData21_PREWITT_Y_3X3[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData22_PREWITT_Y_3X3[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData23_PREWITT_Y_3X3[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData24_PREWITT_Y_3X3[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData25_PREWITT_Y_3X3[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData26_PREWITT_Y_3X3[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData27_PREWITT_Y_3X3[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData28_PREWITT_Y_3X3[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData29_PREWITT_Y_3X3[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData30_PREWITT_Y_3X3[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData31_PREWITT_Y_3X3[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData32_PREWITT_Y_3X3[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData33_PREWITT_Y_3X3[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData34_PREWITT_Y_3X3[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData35_PREWITT_Y_3X3[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData36_PREWITT_Y_3X3[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData37_PREWITT_Y_3X3[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData38_PREWITT_Y_3X3[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData39_PREWITT_Y_3X3[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData40_PREWITT_Y_3X3[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData41_PREWITT_Y_3X3[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData42_PREWITT_Y_3X3[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData43_PREWITT_Y_3X3[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData44_PREWITT_Y_3X3[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData45_PREWITT_Y_3X3[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData46_PREWITT_Y_3X3[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData47_PREWITT_Y_3X3[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData48_PREWITT_Y_3X3[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData49_PREWITT_Y_3X3[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData50_PREWITT_Y_3X3[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData51_PREWITT_Y_3X3[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData52_PREWITT_Y_3X3[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData53_PREWITT_Y_3X3[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData54_PREWITT_Y_3X3[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData55_PREWITT_Y_3X3[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData56_PREWITT_Y_3X3[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData57_PREWITT_Y_3X3[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData58_PREWITT_Y_3X3[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData59_PREWITT_Y_3X3[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData60_PREWITT_Y_3X3[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData61_PREWITT_Y_3X3[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData62_PREWITT_Y_3X3[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData63_PREWITT_Y_3X3[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData64_PREWITT_Y_3X3[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData65_PREWITT_Y_3X3[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData66_PREWITT_Y_3X3[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData67_PREWITT_Y_3X3[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData68_PREWITT_Y_3X3[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData69_PREWITT_Y_3X3[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData70_PREWITT_Y_3X3[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData71_PREWITT_Y_3X3[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData72_PREWITT_Y_3X3[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData73_PREWITT_Y_3X3[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData74_PREWITT_Y_3X3[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData75_PREWITT_Y_3X3[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData76_PREWITT_Y_3X3[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData77_PREWITT_Y_3X3[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData78_PREWITT_Y_3X3[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData79_PREWITT_Y_3X3[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData80_PREWITT_Y_3X3[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData81_PREWITT_Y_3X3[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData82_PREWITT_Y_3X3[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData83_PREWITT_Y_3X3[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData84_PREWITT_Y_3X3[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData85_PREWITT_Y_3X3[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData86_PREWITT_Y_3X3[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData87_PREWITT_Y_3X3[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData88_PREWITT_Y_3X3[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData89_PREWITT_Y_3X3[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData90_PREWITT_Y_3X3[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData91_PREWITT_Y_3X3[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData92_PREWITT_Y_3X3[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData93_PREWITT_Y_3X3[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData94_PREWITT_Y_3X3[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData95_PREWITT_Y_3X3[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData96_PREWITT_Y_3X3[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData97_PREWITT_Y_3X3[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData98_PREWITT_Y_3X3[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData99_PREWITT_Y_3X3[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData100_PREWITT_Y_3X3[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData101_PREWITT_Y_3X3[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData102_PREWITT_Y_3X3[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData103_PREWITT_Y_3X3[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData104_PREWITT_Y_3X3[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData105_PREWITT_Y_3X3[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData106_PREWITT_Y_3X3[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData107_PREWITT_Y_3X3[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData108_PREWITT_Y_3X3[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData109_PREWITT_Y_3X3[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData110_PREWITT_Y_3X3[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData111_PREWITT_Y_3X3[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData112_PREWITT_Y_3X3[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData113_PREWITT_Y_3X3[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData114_PREWITT_Y_3X3[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData115_PREWITT_Y_3X3[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData116_PREWITT_Y_3X3[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData117_PREWITT_Y_3X3[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData118_PREWITT_Y_3X3[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData119_PREWITT_Y_3X3[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData120_PREWITT_Y_3X3[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData121_PREWITT_Y_3X3[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData122_PREWITT_Y_3X3[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData123_PREWITT_Y_3X3[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData124_PREWITT_Y_3X3[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData125_PREWITT_Y_3X3[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData126_PREWITT_Y_3X3[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData127_PREWITT_Y_3X3[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData128_PREWITT_Y_3X3[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData129_PREWITT_Y_3X3[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData130_PREWITT_Y_3X3[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData131_PREWITT_Y_3X3[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData132_PREWITT_Y_3X3[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData133_PREWITT_Y_3X3[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData134_PREWITT_Y_3X3[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData135_PREWITT_Y_3X3[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData136_PREWITT_Y_3X3[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData137_PREWITT_Y_3X3[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData138_PREWITT_Y_3X3[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData139_PREWITT_Y_3X3[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData140_PREWITT_Y_3X3[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData141_PREWITT_Y_3X3[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData142_PREWITT_Y_3X3[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData143_PREWITT_Y_3X3[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData144_PREWITT_Y_3X3[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData145_PREWITT_Y_3X3[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData146_PREWITT_Y_3X3[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData147_PREWITT_Y_3X3[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData148_PREWITT_Y_3X3[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData149_PREWITT_Y_3X3[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData150_PREWITT_Y_3X3[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData151_PREWITT_Y_3X3[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData152_PREWITT_Y_3X3[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData153_PREWITT_Y_3X3[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData154_PREWITT_Y_3X3[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData155_PREWITT_Y_3X3[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData156_PREWITT_Y_3X3[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData157_PREWITT_Y_3X3[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData158_PREWITT_Y_3X3[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData159_PREWITT_Y_3X3[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData160_PREWITT_Y_3X3[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData161_PREWITT_Y_3X3[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData162_PREWITT_Y_3X3[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData163_PREWITT_Y_3X3[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData164_PREWITT_Y_3X3[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData165_PREWITT_Y_3X3[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData166_PREWITT_Y_3X3[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData167_PREWITT_Y_3X3[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData168_PREWITT_Y_3X3[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData169_PREWITT_Y_3X3[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData170_PREWITT_Y_3X3[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData171_PREWITT_Y_3X3[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData172_PREWITT_Y_3X3[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData173_PREWITT_Y_3X3[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData174_PREWITT_Y_3X3[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData175_PREWITT_Y_3X3[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData176_PREWITT_Y_3X3[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData177_PREWITT_Y_3X3[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData178_PREWITT_Y_3X3[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData179_PREWITT_Y_3X3[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData180_PREWITT_Y_3X3[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData181_PREWITT_Y_3X3[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData182_PREWITT_Y_3X3[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData183_PREWITT_Y_3X3[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData184_PREWITT_Y_3X3[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData185_PREWITT_Y_3X3[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData186_PREWITT_Y_3X3[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData187_PREWITT_Y_3X3[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData188_PREWITT_Y_3X3[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData189_PREWITT_Y_3X3[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData190_PREWITT_Y_3X3[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData191_PREWITT_Y_3X3[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData192_PREWITT_Y_3X3[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData193_PREWITT_Y_3X3[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData194_PREWITT_Y_3X3[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData195_PREWITT_Y_3X3[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData196_PREWITT_Y_3X3[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData197_PREWITT_Y_3X3[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData198_PREWITT_Y_3X3[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData199_PREWITT_Y_3X3[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData200_PREWITT_Y_3X3[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData201_PREWITT_Y_3X3[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData202_PREWITT_Y_3X3[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData203_PREWITT_Y_3X3[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData204_PREWITT_Y_3X3[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData205_PREWITT_Y_3X3[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData206_PREWITT_Y_3X3[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData207_PREWITT_Y_3X3[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData208_PREWITT_Y_3X3[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData209_PREWITT_Y_3X3[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData210_PREWITT_Y_3X3[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData211_PREWITT_Y_3X3[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData212_PREWITT_Y_3X3[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData213_PREWITT_Y_3X3[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData214_PREWITT_Y_3X3[] = {{1}};

static acf_scenario gScenarioArray_PREWITT_Y_3X3[] = {
{2, 1, 44, 0, 1, gScenarioBufferData0_PREWITT_Y_3X3, 20, gScenarioKernelData0_PREWITT_Y_3X3, 2},
{4, 1, 64, 0, 1, gScenarioBufferData1_PREWITT_Y_3X3, 20, gScenarioKernelData1_PREWITT_Y_3X3, 2},
{6, 1, 84, 0, 1, gScenarioBufferData2_PREWITT_Y_3X3, 20, gScenarioKernelData2_PREWITT_Y_3X3, 2},
{8, 1, 104, 0, 1, gScenarioBufferData3_PREWITT_Y_3X3, 20, gScenarioKernelData3_PREWITT_Y_3X3, 2},
{10, 1, 124, 0, 1, gScenarioBufferData4_PREWITT_Y_3X3, 20, gScenarioKernelData4_PREWITT_Y_3X3, 2},
{12, 1, 144, 0, 1, gScenarioBufferData5_PREWITT_Y_3X3, 20, gScenarioKernelData5_PREWITT_Y_3X3, 2},
{14, 1, 164, 0, 1, gScenarioBufferData6_PREWITT_Y_3X3, 20, gScenarioKernelData6_PREWITT_Y_3X3, 2},
{16, 1, 184, 0, 1, gScenarioBufferData7_PREWITT_Y_3X3, 20, gScenarioKernelData7_PREWITT_Y_3X3, 2},
{18, 1, 204, 0, 1, gScenarioBufferData8_PREWITT_Y_3X3, 20, gScenarioKernelData8_PREWITT_Y_3X3, 2},
{20, 1, 224, 0, 1, gScenarioBufferData9_PREWITT_Y_3X3, 20, gScenarioKernelData9_PREWITT_Y_3X3, 2},
{22, 1, 244, 0, 1, gScenarioBufferData10_PREWITT_Y_3X3, 20, gScenarioKernelData10_PREWITT_Y_3X3, 2},
{24, 1, 264, 0, 1, gScenarioBufferData11_PREWITT_Y_3X3, 20, gScenarioKernelData11_PREWITT_Y_3X3, 2},
{26, 1, 284, 0, 1, gScenarioBufferData12_PREWITT_Y_3X3, 20, gScenarioKernelData12_PREWITT_Y_3X3, 2},
{28, 1, 304, 0, 1, gScenarioBufferData13_PREWITT_Y_3X3, 20, gScenarioKernelData13_PREWITT_Y_3X3, 2},
{30, 1, 324, 0, 1, gScenarioBufferData14_PREWITT_Y_3X3, 20, gScenarioKernelData14_PREWITT_Y_3X3, 2},
{32, 1, 344, 0, 1, gScenarioBufferData15_PREWITT_Y_3X3, 20, gScenarioKernelData15_PREWITT_Y_3X3, 2},
{48, 1, 504, 0, 1, gScenarioBufferData16_PREWITT_Y_3X3, 20, gScenarioKernelData16_PREWITT_Y_3X3, 2},
{64, 1, 664, 0, 1, gScenarioBufferData17_PREWITT_Y_3X3, 20, gScenarioKernelData17_PREWITT_Y_3X3, 2},
{2, 2, 76, 0, 1, gScenarioBufferData18_PREWITT_Y_3X3, 20, gScenarioKernelData18_PREWITT_Y_3X3, 2},
{4, 2, 112, 0, 1, gScenarioBufferData19_PREWITT_Y_3X3, 20, gScenarioKernelData19_PREWITT_Y_3X3, 2},
{6, 2, 148, 0, 1, gScenarioBufferData20_PREWITT_Y_3X3, 20, gScenarioKernelData20_PREWITT_Y_3X3, 2},
{8, 2, 184, 0, 1, gScenarioBufferData21_PREWITT_Y_3X3, 20, gScenarioKernelData21_PREWITT_Y_3X3, 2},
{10, 2, 220, 0, 1, gScenarioBufferData22_PREWITT_Y_3X3, 20, gScenarioKernelData22_PREWITT_Y_3X3, 2},
{12, 2, 256, 0, 1, gScenarioBufferData23_PREWITT_Y_3X3, 20, gScenarioKernelData23_PREWITT_Y_3X3, 2},
{14, 2, 292, 0, 1, gScenarioBufferData24_PREWITT_Y_3X3, 20, gScenarioKernelData24_PREWITT_Y_3X3, 2},
{16, 2, 328, 0, 1, gScenarioBufferData25_PREWITT_Y_3X3, 20, gScenarioKernelData25_PREWITT_Y_3X3, 2},
{18, 2, 364, 0, 1, gScenarioBufferData26_PREWITT_Y_3X3, 20, gScenarioKernelData26_PREWITT_Y_3X3, 2},
{20, 2, 400, 0, 1, gScenarioBufferData27_PREWITT_Y_3X3, 20, gScenarioKernelData27_PREWITT_Y_3X3, 2},
{22, 2, 436, 0, 1, gScenarioBufferData28_PREWITT_Y_3X3, 20, gScenarioKernelData28_PREWITT_Y_3X3, 2},
{24, 2, 472, 0, 1, gScenarioBufferData29_PREWITT_Y_3X3, 20, gScenarioKernelData29_PREWITT_Y_3X3, 2},
{26, 2, 508, 0, 1, gScenarioBufferData30_PREWITT_Y_3X3, 20, gScenarioKernelData30_PREWITT_Y_3X3, 2},
{28, 2, 544, 0, 1, gScenarioBufferData31_PREWITT_Y_3X3, 20, gScenarioKernelData31_PREWITT_Y_3X3, 2},
{30, 2, 580, 0, 1, gScenarioBufferData32_PREWITT_Y_3X3, 20, gScenarioKernelData32_PREWITT_Y_3X3, 2},
{32, 2, 616, 0, 1, gScenarioBufferData33_PREWITT_Y_3X3, 20, gScenarioKernelData33_PREWITT_Y_3X3, 2},
{48, 2, 904, 0, 1, gScenarioBufferData34_PREWITT_Y_3X3, 20, gScenarioKernelData34_PREWITT_Y_3X3, 2},
{64, 2, 1192, 0, 1, gScenarioBufferData35_PREWITT_Y_3X3, 20, gScenarioKernelData35_PREWITT_Y_3X3, 2},
{2, 4, 140, 0, 1, gScenarioBufferData36_PREWITT_Y_3X3, 20, gScenarioKernelData36_PREWITT_Y_3X3, 2},
{4, 4, 208, 0, 1, gScenarioBufferData37_PREWITT_Y_3X3, 20, gScenarioKernelData37_PREWITT_Y_3X3, 2},
{6, 4, 276, 0, 1, gScenarioBufferData38_PREWITT_Y_3X3, 20, gScenarioKernelData38_PREWITT_Y_3X3, 2},
{8, 4, 344, 0, 1, gScenarioBufferData39_PREWITT_Y_3X3, 20, gScenarioKernelData39_PREWITT_Y_3X3, 2},
{10, 4, 412, 0, 1, gScenarioBufferData40_PREWITT_Y_3X3, 20, gScenarioKernelData40_PREWITT_Y_3X3, 2},
{12, 4, 480, 0, 1, gScenarioBufferData41_PREWITT_Y_3X3, 20, gScenarioKernelData41_PREWITT_Y_3X3, 2},
{14, 4, 548, 0, 1, gScenarioBufferData42_PREWITT_Y_3X3, 20, gScenarioKernelData42_PREWITT_Y_3X3, 2},
{16, 4, 616, 0, 1, gScenarioBufferData43_PREWITT_Y_3X3, 20, gScenarioKernelData43_PREWITT_Y_3X3, 2},
{18, 4, 684, 0, 1, gScenarioBufferData44_PREWITT_Y_3X3, 20, gScenarioKernelData44_PREWITT_Y_3X3, 2},
{20, 4, 752, 0, 1, gScenarioBufferData45_PREWITT_Y_3X3, 20, gScenarioKernelData45_PREWITT_Y_3X3, 2},
{22, 4, 820, 0, 1, gScenarioBufferData46_PREWITT_Y_3X3, 20, gScenarioKernelData46_PREWITT_Y_3X3, 2},
{24, 4, 888, 0, 1, gScenarioBufferData47_PREWITT_Y_3X3, 20, gScenarioKernelData47_PREWITT_Y_3X3, 2},
{26, 4, 956, 0, 1, gScenarioBufferData48_PREWITT_Y_3X3, 20, gScenarioKernelData48_PREWITT_Y_3X3, 2},
{28, 4, 1024, 0, 1, gScenarioBufferData49_PREWITT_Y_3X3, 20, gScenarioKernelData49_PREWITT_Y_3X3, 2},
{30, 4, 1092, 0, 1, gScenarioBufferData50_PREWITT_Y_3X3, 20, gScenarioKernelData50_PREWITT_Y_3X3, 2},
{32, 4, 1160, 0, 1, gScenarioBufferData51_PREWITT_Y_3X3, 20, gScenarioKernelData51_PREWITT_Y_3X3, 2},
{48, 4, 1704, 0, 1, gScenarioBufferData52_PREWITT_Y_3X3, 20, gScenarioKernelData52_PREWITT_Y_3X3, 2},
{64, 4, 2248, 0, 1, gScenarioBufferData53_PREWITT_Y_3X3, 20, gScenarioKernelData53_PREWITT_Y_3X3, 2},
{2, 6, 204, 0, 1, gScenarioBufferData54_PREWITT_Y_3X3, 20, gScenarioKernelData54_PREWITT_Y_3X3, 2},
{4, 6, 304, 0, 1, gScenarioBufferData55_PREWITT_Y_3X3, 20, gScenarioKernelData55_PREWITT_Y_3X3, 2},
{6, 6, 404, 0, 1, gScenarioBufferData56_PREWITT_Y_3X3, 20, gScenarioKernelData56_PREWITT_Y_3X3, 2},
{8, 6, 504, 0, 1, gScenarioBufferData57_PREWITT_Y_3X3, 20, gScenarioKernelData57_PREWITT_Y_3X3, 2},
{10, 6, 604, 0, 1, gScenarioBufferData58_PREWITT_Y_3X3, 20, gScenarioKernelData58_PREWITT_Y_3X3, 2},
{12, 6, 704, 0, 1, gScenarioBufferData59_PREWITT_Y_3X3, 20, gScenarioKernelData59_PREWITT_Y_3X3, 2},
{14, 6, 804, 0, 1, gScenarioBufferData60_PREWITT_Y_3X3, 20, gScenarioKernelData60_PREWITT_Y_3X3, 2},
{16, 6, 904, 0, 1, gScenarioBufferData61_PREWITT_Y_3X3, 20, gScenarioKernelData61_PREWITT_Y_3X3, 2},
{18, 6, 1004, 0, 1, gScenarioBufferData62_PREWITT_Y_3X3, 20, gScenarioKernelData62_PREWITT_Y_3X3, 2},
{20, 6, 1104, 0, 1, gScenarioBufferData63_PREWITT_Y_3X3, 20, gScenarioKernelData63_PREWITT_Y_3X3, 2},
{22, 6, 1204, 0, 1, gScenarioBufferData64_PREWITT_Y_3X3, 20, gScenarioKernelData64_PREWITT_Y_3X3, 2},
{24, 6, 1304, 0, 1, gScenarioBufferData65_PREWITT_Y_3X3, 20, gScenarioKernelData65_PREWITT_Y_3X3, 2},
{26, 6, 1404, 0, 1, gScenarioBufferData66_PREWITT_Y_3X3, 20, gScenarioKernelData66_PREWITT_Y_3X3, 2},
{28, 6, 1504, 0, 1, gScenarioBufferData67_PREWITT_Y_3X3, 20, gScenarioKernelData67_PREWITT_Y_3X3, 2},
{30, 6, 1604, 0, 1, gScenarioBufferData68_PREWITT_Y_3X3, 20, gScenarioKernelData68_PREWITT_Y_3X3, 2},
{32, 6, 1704, 0, 1, gScenarioBufferData69_PREWITT_Y_3X3, 20, gScenarioKernelData69_PREWITT_Y_3X3, 2},
{48, 6, 2504, 0, 1, gScenarioBufferData70_PREWITT_Y_3X3, 20, gScenarioKernelData70_PREWITT_Y_3X3, 2},
{64, 6, 3304, 0, 1, gScenarioBufferData71_PREWITT_Y_3X3, 20, gScenarioKernelData71_PREWITT_Y_3X3, 2},
{2, 8, 268, 0, 1, gScenarioBufferData72_PREWITT_Y_3X3, 20, gScenarioKernelData72_PREWITT_Y_3X3, 2},
{4, 8, 400, 0, 1, gScenarioBufferData73_PREWITT_Y_3X3, 20, gScenarioKernelData73_PREWITT_Y_3X3, 2},
{6, 8, 532, 0, 1, gScenarioBufferData74_PREWITT_Y_3X3, 20, gScenarioKernelData74_PREWITT_Y_3X3, 2},
{8, 8, 664, 0, 1, gScenarioBufferData75_PREWITT_Y_3X3, 20, gScenarioKernelData75_PREWITT_Y_3X3, 2},
{10, 8, 796, 0, 1, gScenarioBufferData76_PREWITT_Y_3X3, 20, gScenarioKernelData76_PREWITT_Y_3X3, 2},
{12, 8, 928, 0, 1, gScenarioBufferData77_PREWITT_Y_3X3, 20, gScenarioKernelData77_PREWITT_Y_3X3, 2},
{14, 8, 1060, 0, 1, gScenarioBufferData78_PREWITT_Y_3X3, 20, gScenarioKernelData78_PREWITT_Y_3X3, 2},
{16, 8, 1192, 0, 1, gScenarioBufferData79_PREWITT_Y_3X3, 20, gScenarioKernelData79_PREWITT_Y_3X3, 2},
{18, 8, 1324, 0, 1, gScenarioBufferData80_PREWITT_Y_3X3, 20, gScenarioKernelData80_PREWITT_Y_3X3, 2},
{20, 8, 1456, 0, 1, gScenarioBufferData81_PREWITT_Y_3X3, 20, gScenarioKernelData81_PREWITT_Y_3X3, 2},
{22, 8, 1588, 0, 1, gScenarioBufferData82_PREWITT_Y_3X3, 20, gScenarioKernelData82_PREWITT_Y_3X3, 2},
{24, 8, 1720, 0, 1, gScenarioBufferData83_PREWITT_Y_3X3, 20, gScenarioKernelData83_PREWITT_Y_3X3, 2},
{26, 8, 1852, 0, 1, gScenarioBufferData84_PREWITT_Y_3X3, 20, gScenarioKernelData84_PREWITT_Y_3X3, 2},
{28, 8, 1984, 0, 1, gScenarioBufferData85_PREWITT_Y_3X3, 20, gScenarioKernelData85_PREWITT_Y_3X3, 2},
{30, 8, 2116, 0, 1, gScenarioBufferData86_PREWITT_Y_3X3, 20, gScenarioKernelData86_PREWITT_Y_3X3, 2},
{32, 8, 2248, 0, 1, gScenarioBufferData87_PREWITT_Y_3X3, 20, gScenarioKernelData87_PREWITT_Y_3X3, 2},
{48, 8, 3304, 0, 1, gScenarioBufferData88_PREWITT_Y_3X3, 20, gScenarioKernelData88_PREWITT_Y_3X3, 2},
{2, 10, 332, 0, 1, gScenarioBufferData89_PREWITT_Y_3X3, 20, gScenarioKernelData89_PREWITT_Y_3X3, 2},
{4, 10, 496, 0, 1, gScenarioBufferData90_PREWITT_Y_3X3, 20, gScenarioKernelData90_PREWITT_Y_3X3, 2},
{6, 10, 660, 0, 1, gScenarioBufferData91_PREWITT_Y_3X3, 20, gScenarioKernelData91_PREWITT_Y_3X3, 2},
{8, 10, 824, 0, 1, gScenarioBufferData92_PREWITT_Y_3X3, 20, gScenarioKernelData92_PREWITT_Y_3X3, 2},
{10, 10, 988, 0, 1, gScenarioBufferData93_PREWITT_Y_3X3, 20, gScenarioKernelData93_PREWITT_Y_3X3, 2},
{12, 10, 1152, 0, 1, gScenarioBufferData94_PREWITT_Y_3X3, 20, gScenarioKernelData94_PREWITT_Y_3X3, 2},
{14, 10, 1316, 0, 1, gScenarioBufferData95_PREWITT_Y_3X3, 20, gScenarioKernelData95_PREWITT_Y_3X3, 2},
{16, 10, 1480, 0, 1, gScenarioBufferData96_PREWITT_Y_3X3, 20, gScenarioKernelData96_PREWITT_Y_3X3, 2},
{18, 10, 1644, 0, 1, gScenarioBufferData97_PREWITT_Y_3X3, 20, gScenarioKernelData97_PREWITT_Y_3X3, 2},
{20, 10, 1808, 0, 1, gScenarioBufferData98_PREWITT_Y_3X3, 20, gScenarioKernelData98_PREWITT_Y_3X3, 2},
{22, 10, 1972, 0, 1, gScenarioBufferData99_PREWITT_Y_3X3, 20, gScenarioKernelData99_PREWITT_Y_3X3, 2},
{24, 10, 2136, 0, 1, gScenarioBufferData100_PREWITT_Y_3X3, 20, gScenarioKernelData100_PREWITT_Y_3X3, 2},
{26, 10, 2300, 0, 1, gScenarioBufferData101_PREWITT_Y_3X3, 20, gScenarioKernelData101_PREWITT_Y_3X3, 2},
{28, 10, 2464, 0, 1, gScenarioBufferData102_PREWITT_Y_3X3, 20, gScenarioKernelData102_PREWITT_Y_3X3, 2},
{30, 10, 2628, 0, 1, gScenarioBufferData103_PREWITT_Y_3X3, 20, gScenarioKernelData103_PREWITT_Y_3X3, 2},
{32, 10, 2792, 0, 1, gScenarioBufferData104_PREWITT_Y_3X3, 20, gScenarioKernelData104_PREWITT_Y_3X3, 2},
{2, 12, 396, 0, 1, gScenarioBufferData105_PREWITT_Y_3X3, 20, gScenarioKernelData105_PREWITT_Y_3X3, 2},
{4, 12, 592, 0, 1, gScenarioBufferData106_PREWITT_Y_3X3, 20, gScenarioKernelData106_PREWITT_Y_3X3, 2},
{6, 12, 788, 0, 1, gScenarioBufferData107_PREWITT_Y_3X3, 20, gScenarioKernelData107_PREWITT_Y_3X3, 2},
{8, 12, 984, 0, 1, gScenarioBufferData108_PREWITT_Y_3X3, 20, gScenarioKernelData108_PREWITT_Y_3X3, 2},
{10, 12, 1180, 0, 1, gScenarioBufferData109_PREWITT_Y_3X3, 20, gScenarioKernelData109_PREWITT_Y_3X3, 2},
{12, 12, 1376, 0, 1, gScenarioBufferData110_PREWITT_Y_3X3, 20, gScenarioKernelData110_PREWITT_Y_3X3, 2},
{14, 12, 1572, 0, 1, gScenarioBufferData111_PREWITT_Y_3X3, 20, gScenarioKernelData111_PREWITT_Y_3X3, 2},
{16, 12, 1768, 0, 1, gScenarioBufferData112_PREWITT_Y_3X3, 20, gScenarioKernelData112_PREWITT_Y_3X3, 2},
{18, 12, 1964, 0, 1, gScenarioBufferData113_PREWITT_Y_3X3, 20, gScenarioKernelData113_PREWITT_Y_3X3, 2},
{20, 12, 2160, 0, 1, gScenarioBufferData114_PREWITT_Y_3X3, 20, gScenarioKernelData114_PREWITT_Y_3X3, 2},
{22, 12, 2356, 0, 1, gScenarioBufferData115_PREWITT_Y_3X3, 20, gScenarioKernelData115_PREWITT_Y_3X3, 2},
{24, 12, 2552, 0, 1, gScenarioBufferData116_PREWITT_Y_3X3, 20, gScenarioKernelData116_PREWITT_Y_3X3, 2},
{26, 12, 2748, 0, 1, gScenarioBufferData117_PREWITT_Y_3X3, 20, gScenarioKernelData117_PREWITT_Y_3X3, 2},
{28, 12, 2944, 0, 1, gScenarioBufferData118_PREWITT_Y_3X3, 20, gScenarioKernelData118_PREWITT_Y_3X3, 2},
{30, 12, 3140, 0, 1, gScenarioBufferData119_PREWITT_Y_3X3, 20, gScenarioKernelData119_PREWITT_Y_3X3, 2},
{32, 12, 3336, 0, 1, gScenarioBufferData120_PREWITT_Y_3X3, 20, gScenarioKernelData120_PREWITT_Y_3X3, 2},
{2, 14, 460, 0, 1, gScenarioBufferData121_PREWITT_Y_3X3, 20, gScenarioKernelData121_PREWITT_Y_3X3, 2},
{4, 14, 688, 0, 1, gScenarioBufferData122_PREWITT_Y_3X3, 20, gScenarioKernelData122_PREWITT_Y_3X3, 2},
{6, 14, 916, 0, 1, gScenarioBufferData123_PREWITT_Y_3X3, 20, gScenarioKernelData123_PREWITT_Y_3X3, 2},
{8, 14, 1144, 0, 1, gScenarioBufferData124_PREWITT_Y_3X3, 20, gScenarioKernelData124_PREWITT_Y_3X3, 2},
{10, 14, 1372, 0, 1, gScenarioBufferData125_PREWITT_Y_3X3, 20, gScenarioKernelData125_PREWITT_Y_3X3, 2},
{12, 14, 1600, 0, 1, gScenarioBufferData126_PREWITT_Y_3X3, 20, gScenarioKernelData126_PREWITT_Y_3X3, 2},
{14, 14, 1828, 0, 1, gScenarioBufferData127_PREWITT_Y_3X3, 20, gScenarioKernelData127_PREWITT_Y_3X3, 2},
{16, 14, 2056, 0, 1, gScenarioBufferData128_PREWITT_Y_3X3, 20, gScenarioKernelData128_PREWITT_Y_3X3, 2},
{18, 14, 2284, 0, 1, gScenarioBufferData129_PREWITT_Y_3X3, 20, gScenarioKernelData129_PREWITT_Y_3X3, 2},
{20, 14, 2512, 0, 1, gScenarioBufferData130_PREWITT_Y_3X3, 20, gScenarioKernelData130_PREWITT_Y_3X3, 2},
{22, 14, 2740, 0, 1, gScenarioBufferData131_PREWITT_Y_3X3, 20, gScenarioKernelData131_PREWITT_Y_3X3, 2},
{24, 14, 2968, 0, 1, gScenarioBufferData132_PREWITT_Y_3X3, 20, gScenarioKernelData132_PREWITT_Y_3X3, 2},
{26, 14, 3196, 0, 1, gScenarioBufferData133_PREWITT_Y_3X3, 20, gScenarioKernelData133_PREWITT_Y_3X3, 2},
{28, 14, 3424, 0, 1, gScenarioBufferData134_PREWITT_Y_3X3, 20, gScenarioKernelData134_PREWITT_Y_3X3, 2},
{30, 14, 3652, 0, 1, gScenarioBufferData135_PREWITT_Y_3X3, 20, gScenarioKernelData135_PREWITT_Y_3X3, 2},
{2, 16, 524, 0, 1, gScenarioBufferData136_PREWITT_Y_3X3, 20, gScenarioKernelData136_PREWITT_Y_3X3, 2},
{4, 16, 784, 0, 1, gScenarioBufferData137_PREWITT_Y_3X3, 20, gScenarioKernelData137_PREWITT_Y_3X3, 2},
{6, 16, 1044, 0, 1, gScenarioBufferData138_PREWITT_Y_3X3, 20, gScenarioKernelData138_PREWITT_Y_3X3, 2},
{8, 16, 1304, 0, 1, gScenarioBufferData139_PREWITT_Y_3X3, 20, gScenarioKernelData139_PREWITT_Y_3X3, 2},
{10, 16, 1564, 0, 1, gScenarioBufferData140_PREWITT_Y_3X3, 20, gScenarioKernelData140_PREWITT_Y_3X3, 2},
{12, 16, 1824, 0, 1, gScenarioBufferData141_PREWITT_Y_3X3, 20, gScenarioKernelData141_PREWITT_Y_3X3, 2},
{14, 16, 2084, 0, 1, gScenarioBufferData142_PREWITT_Y_3X3, 20, gScenarioKernelData142_PREWITT_Y_3X3, 2},
{16, 16, 2344, 0, 1, gScenarioBufferData143_PREWITT_Y_3X3, 20, gScenarioKernelData143_PREWITT_Y_3X3, 2},
{18, 16, 2604, 0, 1, gScenarioBufferData144_PREWITT_Y_3X3, 20, gScenarioKernelData144_PREWITT_Y_3X3, 2},
{20, 16, 2864, 0, 1, gScenarioBufferData145_PREWITT_Y_3X3, 20, gScenarioKernelData145_PREWITT_Y_3X3, 2},
{22, 16, 3124, 0, 1, gScenarioBufferData146_PREWITT_Y_3X3, 20, gScenarioKernelData146_PREWITT_Y_3X3, 2},
{24, 16, 3384, 0, 1, gScenarioBufferData147_PREWITT_Y_3X3, 20, gScenarioKernelData147_PREWITT_Y_3X3, 2},
{26, 16, 3644, 0, 1, gScenarioBufferData148_PREWITT_Y_3X3, 20, gScenarioKernelData148_PREWITT_Y_3X3, 2},
{2, 18, 588, 0, 1, gScenarioBufferData149_PREWITT_Y_3X3, 20, gScenarioKernelData149_PREWITT_Y_3X3, 2},
{4, 18, 880, 0, 1, gScenarioBufferData150_PREWITT_Y_3X3, 20, gScenarioKernelData150_PREWITT_Y_3X3, 2},
{6, 18, 1172, 0, 1, gScenarioBufferData151_PREWITT_Y_3X3, 20, gScenarioKernelData151_PREWITT_Y_3X3, 2},
{8, 18, 1464, 0, 1, gScenarioBufferData152_PREWITT_Y_3X3, 20, gScenarioKernelData152_PREWITT_Y_3X3, 2},
{10, 18, 1756, 0, 1, gScenarioBufferData153_PREWITT_Y_3X3, 20, gScenarioKernelData153_PREWITT_Y_3X3, 2},
{12, 18, 2048, 0, 1, gScenarioBufferData154_PREWITT_Y_3X3, 20, gScenarioKernelData154_PREWITT_Y_3X3, 2},
{14, 18, 2340, 0, 1, gScenarioBufferData155_PREWITT_Y_3X3, 20, gScenarioKernelData155_PREWITT_Y_3X3, 2},
{16, 18, 2632, 0, 1, gScenarioBufferData156_PREWITT_Y_3X3, 20, gScenarioKernelData156_PREWITT_Y_3X3, 2},
{18, 18, 2924, 0, 1, gScenarioBufferData157_PREWITT_Y_3X3, 20, gScenarioKernelData157_PREWITT_Y_3X3, 2},
{20, 18, 3216, 0, 1, gScenarioBufferData158_PREWITT_Y_3X3, 20, gScenarioKernelData158_PREWITT_Y_3X3, 2},
{22, 18, 3508, 0, 1, gScenarioBufferData159_PREWITT_Y_3X3, 20, gScenarioKernelData159_PREWITT_Y_3X3, 2},
{24, 18, 3800, 0, 1, gScenarioBufferData160_PREWITT_Y_3X3, 20, gScenarioKernelData160_PREWITT_Y_3X3, 2},
{2, 20, 652, 0, 1, gScenarioBufferData161_PREWITT_Y_3X3, 20, gScenarioKernelData161_PREWITT_Y_3X3, 2},
{4, 20, 976, 0, 1, gScenarioBufferData162_PREWITT_Y_3X3, 20, gScenarioKernelData162_PREWITT_Y_3X3, 2},
{6, 20, 1300, 0, 1, gScenarioBufferData163_PREWITT_Y_3X3, 20, gScenarioKernelData163_PREWITT_Y_3X3, 2},
{8, 20, 1624, 0, 1, gScenarioBufferData164_PREWITT_Y_3X3, 20, gScenarioKernelData164_PREWITT_Y_3X3, 2},
{10, 20, 1948, 0, 1, gScenarioBufferData165_PREWITT_Y_3X3, 20, gScenarioKernelData165_PREWITT_Y_3X3, 2},
{12, 20, 2272, 0, 1, gScenarioBufferData166_PREWITT_Y_3X3, 20, gScenarioKernelData166_PREWITT_Y_3X3, 2},
{14, 20, 2596, 0, 1, gScenarioBufferData167_PREWITT_Y_3X3, 20, gScenarioKernelData167_PREWITT_Y_3X3, 2},
{16, 20, 2920, 0, 1, gScenarioBufferData168_PREWITT_Y_3X3, 20, gScenarioKernelData168_PREWITT_Y_3X3, 2},
{18, 20, 3244, 0, 1, gScenarioBufferData169_PREWITT_Y_3X3, 20, gScenarioKernelData169_PREWITT_Y_3X3, 2},
{20, 20, 3568, 0, 1, gScenarioBufferData170_PREWITT_Y_3X3, 20, gScenarioKernelData170_PREWITT_Y_3X3, 2},
{2, 22, 716, 0, 1, gScenarioBufferData171_PREWITT_Y_3X3, 20, gScenarioKernelData171_PREWITT_Y_3X3, 2},
{4, 22, 1072, 0, 1, gScenarioBufferData172_PREWITT_Y_3X3, 20, gScenarioKernelData172_PREWITT_Y_3X3, 2},
{6, 22, 1428, 0, 1, gScenarioBufferData173_PREWITT_Y_3X3, 20, gScenarioKernelData173_PREWITT_Y_3X3, 2},
{8, 22, 1784, 0, 1, gScenarioBufferData174_PREWITT_Y_3X3, 20, gScenarioKernelData174_PREWITT_Y_3X3, 2},
{10, 22, 2140, 0, 1, gScenarioBufferData175_PREWITT_Y_3X3, 20, gScenarioKernelData175_PREWITT_Y_3X3, 2},
{12, 22, 2496, 0, 1, gScenarioBufferData176_PREWITT_Y_3X3, 20, gScenarioKernelData176_PREWITT_Y_3X3, 2},
{14, 22, 2852, 0, 1, gScenarioBufferData177_PREWITT_Y_3X3, 20, gScenarioKernelData177_PREWITT_Y_3X3, 2},
{16, 22, 3208, 0, 1, gScenarioBufferData178_PREWITT_Y_3X3, 20, gScenarioKernelData178_PREWITT_Y_3X3, 2},
{18, 22, 3564, 0, 1, gScenarioBufferData179_PREWITT_Y_3X3, 20, gScenarioKernelData179_PREWITT_Y_3X3, 2},
{2, 24, 780, 0, 1, gScenarioBufferData180_PREWITT_Y_3X3, 20, gScenarioKernelData180_PREWITT_Y_3X3, 2},
{4, 24, 1168, 0, 1, gScenarioBufferData181_PREWITT_Y_3X3, 20, gScenarioKernelData181_PREWITT_Y_3X3, 2},
{6, 24, 1556, 0, 1, gScenarioBufferData182_PREWITT_Y_3X3, 20, gScenarioKernelData182_PREWITT_Y_3X3, 2},
{8, 24, 1944, 0, 1, gScenarioBufferData183_PREWITT_Y_3X3, 20, gScenarioKernelData183_PREWITT_Y_3X3, 2},
{10, 24, 2332, 0, 1, gScenarioBufferData184_PREWITT_Y_3X3, 20, gScenarioKernelData184_PREWITT_Y_3X3, 2},
{12, 24, 2720, 0, 1, gScenarioBufferData185_PREWITT_Y_3X3, 20, gScenarioKernelData185_PREWITT_Y_3X3, 2},
{14, 24, 3108, 0, 1, gScenarioBufferData186_PREWITT_Y_3X3, 20, gScenarioKernelData186_PREWITT_Y_3X3, 2},
{16, 24, 3496, 0, 1, gScenarioBufferData187_PREWITT_Y_3X3, 20, gScenarioKernelData187_PREWITT_Y_3X3, 2},
{2, 26, 844, 0, 1, gScenarioBufferData188_PREWITT_Y_3X3, 20, gScenarioKernelData188_PREWITT_Y_3X3, 2},
{4, 26, 1264, 0, 1, gScenarioBufferData189_PREWITT_Y_3X3, 20, gScenarioKernelData189_PREWITT_Y_3X3, 2},
{6, 26, 1684, 0, 1, gScenarioBufferData190_PREWITT_Y_3X3, 20, gScenarioKernelData190_PREWITT_Y_3X3, 2},
{8, 26, 2104, 0, 1, gScenarioBufferData191_PREWITT_Y_3X3, 20, gScenarioKernelData191_PREWITT_Y_3X3, 2},
{10, 26, 2524, 0, 1, gScenarioBufferData192_PREWITT_Y_3X3, 20, gScenarioKernelData192_PREWITT_Y_3X3, 2},
{12, 26, 2944, 0, 1, gScenarioBufferData193_PREWITT_Y_3X3, 20, gScenarioKernelData193_PREWITT_Y_3X3, 2},
{14, 26, 3364, 0, 1, gScenarioBufferData194_PREWITT_Y_3X3, 20, gScenarioKernelData194_PREWITT_Y_3X3, 2},
{16, 26, 3784, 0, 1, gScenarioBufferData195_PREWITT_Y_3X3, 20, gScenarioKernelData195_PREWITT_Y_3X3, 2},
{2, 28, 908, 0, 1, gScenarioBufferData196_PREWITT_Y_3X3, 20, gScenarioKernelData196_PREWITT_Y_3X3, 2},
{4, 28, 1360, 0, 1, gScenarioBufferData197_PREWITT_Y_3X3, 20, gScenarioKernelData197_PREWITT_Y_3X3, 2},
{6, 28, 1812, 0, 1, gScenarioBufferData198_PREWITT_Y_3X3, 20, gScenarioKernelData198_PREWITT_Y_3X3, 2},
{8, 28, 2264, 0, 1, gScenarioBufferData199_PREWITT_Y_3X3, 20, gScenarioKernelData199_PREWITT_Y_3X3, 2},
{10, 28, 2716, 0, 1, gScenarioBufferData200_PREWITT_Y_3X3, 20, gScenarioKernelData200_PREWITT_Y_3X3, 2},
{12, 28, 3168, 0, 1, gScenarioBufferData201_PREWITT_Y_3X3, 20, gScenarioKernelData201_PREWITT_Y_3X3, 2},
{14, 28, 3620, 0, 1, gScenarioBufferData202_PREWITT_Y_3X3, 20, gScenarioKernelData202_PREWITT_Y_3X3, 2},
{2, 30, 972, 0, 1, gScenarioBufferData203_PREWITT_Y_3X3, 20, gScenarioKernelData203_PREWITT_Y_3X3, 2},
{4, 30, 1456, 0, 1, gScenarioBufferData204_PREWITT_Y_3X3, 20, gScenarioKernelData204_PREWITT_Y_3X3, 2},
{6, 30, 1940, 0, 1, gScenarioBufferData205_PREWITT_Y_3X3, 20, gScenarioKernelData205_PREWITT_Y_3X3, 2},
{8, 30, 2424, 0, 1, gScenarioBufferData206_PREWITT_Y_3X3, 20, gScenarioKernelData206_PREWITT_Y_3X3, 2},
{10, 30, 2908, 0, 1, gScenarioBufferData207_PREWITT_Y_3X3, 20, gScenarioKernelData207_PREWITT_Y_3X3, 2},
{12, 30, 3392, 0, 1, gScenarioBufferData208_PREWITT_Y_3X3, 20, gScenarioKernelData208_PREWITT_Y_3X3, 2},
{2, 32, 1036, 0, 1, gScenarioBufferData209_PREWITT_Y_3X3, 20, gScenarioKernelData209_PREWITT_Y_3X3, 2},
{4, 32, 1552, 0, 1, gScenarioBufferData210_PREWITT_Y_3X3, 20, gScenarioKernelData210_PREWITT_Y_3X3, 2},
{6, 32, 2068, 0, 1, gScenarioBufferData211_PREWITT_Y_3X3, 20, gScenarioKernelData211_PREWITT_Y_3X3, 2},
{8, 32, 2584, 0, 1, gScenarioBufferData212_PREWITT_Y_3X3, 20, gScenarioKernelData212_PREWITT_Y_3X3, 2},
{10, 32, 3100, 0, 1, gScenarioBufferData213_PREWITT_Y_3X3, 20, gScenarioKernelData213_PREWITT_Y_3X3, 2},
{12, 32, 3616, 0, 1, gScenarioBufferData214_PREWITT_Y_3X3, 20, gScenarioKernelData214_PREWITT_Y_3X3, 2}
};

static acf_scenario_list gScenarioList_PREWITT_Y_3X3 = {
215, //number of scenarios
gScenarioArray_PREWITT_Y_3X3};
//**************************************************************

class PREWITT_Y_3X3 : public ACF_Process_APU
{
public:
   PREWITT_Y_3X3(int32_t apex_id = 0) : ACF_Process_APU(apex_id)
   {} 

   int32_t Initialize()
   {
      int32_t lRetVal = 0;

      if (!Initialized()) //initialization steps that only need to occur once
      {
         SetProcessIdentifier("PREWITT_Y_3X3");
         SetApuLoadInfo(PREWITT_Y_3X3_LOAD_SEGMENTS,
                        PREWITT_Y_3X3_LOAD_PMEM, PREWITT_Y_3X3_LOAD_PMEM_SIZE,
                        PREWITT_Y_3X3_LOAD_DMEM, PREWITT_Y_3X3_LOAD_DMEM_SIZE,
                        0, 0); //assuming _LOAD_CMEM does not exist
         FlagSpatialDep();

         //***NOTE: the order in which the following ports are added is meaningful; do not change!

         AddPort("INPUT_0", ICP_DATATYPE_08U, 1, 1, 2, 1, 0, 0, 0, 0, 0, 0, 0, 0x1010101);
         AddPort("OUTPUT_0", ICP_DATATYPE_16S, 1, 1, 2, 1, 1, 0, 0, 0, 0, 0, 1);

         CfgScenarios(&gScenarioList_PREWITT_Y_3X3);

         FlagAsInitialized();
      }

      lRetVal = SelectApuConfiguration(mApuCfg, mApexId); //by default mApuCfg = ACF_APU_CFG__APEX0_DEFAULT and mApexId = 0

      return lRetVal;
   }
};

#endif //_ACF_PROCESS_APU_PREWITT_Y_3X3
