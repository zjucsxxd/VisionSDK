#ifndef _ACF_PROCESS_APU_CLZ_08S
#define _ACF_PROCESS_APU_CLZ_08S

#include <acf_process_apu.h>
#include <CLZ_08S_APU_LOAD.h> //APU load associated with this process
#include <stdint.h>


//SCENARIO LIST*************************************************
static acf_scenario_buffer_data gScenarioBufferData0_CLZ_08S[] = {{2, 1, 2, 0, 0x0}, {2, 1, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData1_CLZ_08S[] = {{4, 1, 2, 0, 0x0}, {4, 1, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData2_CLZ_08S[] = {{6, 1, 2, 0, 0x0}, {6, 1, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData3_CLZ_08S[] = {{8, 1, 2, 0, 0x0}, {8, 1, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData4_CLZ_08S[] = {{10, 1, 2, 0, 0x0}, {10, 1, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData5_CLZ_08S[] = {{12, 1, 2, 0, 0x0}, {12, 1, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData6_CLZ_08S[] = {{14, 1, 2, 0, 0x0}, {14, 1, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData7_CLZ_08S[] = {{16, 1, 2, 0, 0x0}, {16, 1, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData8_CLZ_08S[] = {{18, 1, 2, 0, 0x0}, {18, 1, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData9_CLZ_08S[] = {{20, 1, 2, 0, 0x0}, {20, 1, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData10_CLZ_08S[] = {{22, 1, 2, 0, 0x0}, {22, 1, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData11_CLZ_08S[] = {{24, 1, 2, 0, 0x0}, {24, 1, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData12_CLZ_08S[] = {{26, 1, 2, 0, 0x0}, {26, 1, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData13_CLZ_08S[] = {{28, 1, 2, 0, 0x0}, {28, 1, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData14_CLZ_08S[] = {{30, 1, 2, 0, 0x0}, {30, 1, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData15_CLZ_08S[] = {{32, 1, 2, 0, 0x0}, {32, 1, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData16_CLZ_08S[] = {{48, 1, 2, 0, 0x0}, {48, 1, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData17_CLZ_08S[] = {{64, 1, 2, 0, 0x0}, {64, 1, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData18_CLZ_08S[] = {{96, 1, 2, 0, 0x0}, {96, 1, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData19_CLZ_08S[] = {{112, 1, 2, 0, 0x0}, {112, 1, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData20_CLZ_08S[] = {{128, 1, 2, 0, 0x0}, {128, 1, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData21_CLZ_08S[] = {{2, 2, 2, 0, 0x0}, {2, 2, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData22_CLZ_08S[] = {{4, 2, 2, 0, 0x0}, {4, 2, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData23_CLZ_08S[] = {{6, 2, 2, 0, 0x0}, {6, 2, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData24_CLZ_08S[] = {{8, 2, 2, 0, 0x0}, {8, 2, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData25_CLZ_08S[] = {{10, 2, 2, 0, 0x0}, {10, 2, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData26_CLZ_08S[] = {{12, 2, 2, 0, 0x0}, {12, 2, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData27_CLZ_08S[] = {{14, 2, 2, 0, 0x0}, {14, 2, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData28_CLZ_08S[] = {{16, 2, 2, 0, 0x0}, {16, 2, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData29_CLZ_08S[] = {{18, 2, 2, 0, 0x0}, {18, 2, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData30_CLZ_08S[] = {{20, 2, 2, 0, 0x0}, {20, 2, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData31_CLZ_08S[] = {{22, 2, 2, 0, 0x0}, {22, 2, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData32_CLZ_08S[] = {{24, 2, 2, 0, 0x0}, {24, 2, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData33_CLZ_08S[] = {{26, 2, 2, 0, 0x0}, {26, 2, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData34_CLZ_08S[] = {{28, 2, 2, 0, 0x0}, {28, 2, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData35_CLZ_08S[] = {{30, 2, 2, 0, 0x0}, {30, 2, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData36_CLZ_08S[] = {{32, 2, 2, 0, 0x0}, {32, 2, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData37_CLZ_08S[] = {{48, 2, 2, 0, 0x0}, {48, 2, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData38_CLZ_08S[] = {{64, 2, 2, 0, 0x0}, {64, 2, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData39_CLZ_08S[] = {{96, 2, 2, 0, 0x0}, {96, 2, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData40_CLZ_08S[] = {{112, 2, 2, 0, 0x0}, {112, 2, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData41_CLZ_08S[] = {{128, 2, 2, 0, 0x0}, {128, 2, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData42_CLZ_08S[] = {{2, 4, 2, 0, 0x0}, {2, 4, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData43_CLZ_08S[] = {{4, 4, 2, 0, 0x0}, {4, 4, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData44_CLZ_08S[] = {{6, 4, 2, 0, 0x0}, {6, 4, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData45_CLZ_08S[] = {{8, 4, 2, 0, 0x0}, {8, 4, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData46_CLZ_08S[] = {{10, 4, 2, 0, 0x0}, {10, 4, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData47_CLZ_08S[] = {{12, 4, 2, 0, 0x0}, {12, 4, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData48_CLZ_08S[] = {{14, 4, 2, 0, 0x0}, {14, 4, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData49_CLZ_08S[] = {{16, 4, 2, 0, 0x0}, {16, 4, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData50_CLZ_08S[] = {{18, 4, 2, 0, 0x0}, {18, 4, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData51_CLZ_08S[] = {{20, 4, 2, 0, 0x0}, {20, 4, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData52_CLZ_08S[] = {{22, 4, 2, 0, 0x0}, {22, 4, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData53_CLZ_08S[] = {{24, 4, 2, 0, 0x0}, {24, 4, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData54_CLZ_08S[] = {{26, 4, 2, 0, 0x0}, {26, 4, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData55_CLZ_08S[] = {{28, 4, 2, 0, 0x0}, {28, 4, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData56_CLZ_08S[] = {{30, 4, 2, 0, 0x0}, {30, 4, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData57_CLZ_08S[] = {{32, 4, 2, 0, 0x0}, {32, 4, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData58_CLZ_08S[] = {{48, 4, 2, 0, 0x0}, {48, 4, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData59_CLZ_08S[] = {{64, 4, 2, 0, 0x0}, {64, 4, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData60_CLZ_08S[] = {{96, 4, 2, 0, 0x0}, {96, 4, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData61_CLZ_08S[] = {{112, 4, 2, 0, 0x0}, {112, 4, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData62_CLZ_08S[] = {{128, 4, 2, 0, 0x0}, {128, 4, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData63_CLZ_08S[] = {{2, 6, 2, 0, 0x0}, {2, 6, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData64_CLZ_08S[] = {{4, 6, 2, 0, 0x0}, {4, 6, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData65_CLZ_08S[] = {{6, 6, 2, 0, 0x0}, {6, 6, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData66_CLZ_08S[] = {{8, 6, 2, 0, 0x0}, {8, 6, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData67_CLZ_08S[] = {{10, 6, 2, 0, 0x0}, {10, 6, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData68_CLZ_08S[] = {{12, 6, 2, 0, 0x0}, {12, 6, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData69_CLZ_08S[] = {{14, 6, 2, 0, 0x0}, {14, 6, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData70_CLZ_08S[] = {{16, 6, 2, 0, 0x0}, {16, 6, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData71_CLZ_08S[] = {{18, 6, 2, 0, 0x0}, {18, 6, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData72_CLZ_08S[] = {{20, 6, 2, 0, 0x0}, {20, 6, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData73_CLZ_08S[] = {{22, 6, 2, 0, 0x0}, {22, 6, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData74_CLZ_08S[] = {{24, 6, 2, 0, 0x0}, {24, 6, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData75_CLZ_08S[] = {{26, 6, 2, 0, 0x0}, {26, 6, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData76_CLZ_08S[] = {{28, 6, 2, 0, 0x0}, {28, 6, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData77_CLZ_08S[] = {{30, 6, 2, 0, 0x0}, {30, 6, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData78_CLZ_08S[] = {{32, 6, 2, 0, 0x0}, {32, 6, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData79_CLZ_08S[] = {{48, 6, 2, 0, 0x0}, {48, 6, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData80_CLZ_08S[] = {{64, 6, 2, 0, 0x0}, {64, 6, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData81_CLZ_08S[] = {{96, 6, 2, 0, 0x0}, {96, 6, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData82_CLZ_08S[] = {{112, 6, 2, 0, 0x0}, {112, 6, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData83_CLZ_08S[] = {{128, 6, 2, 0, 0x0}, {128, 6, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData84_CLZ_08S[] = {{2, 8, 2, 0, 0x0}, {2, 8, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData85_CLZ_08S[] = {{4, 8, 2, 0, 0x0}, {4, 8, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData86_CLZ_08S[] = {{6, 8, 2, 0, 0x0}, {6, 8, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData87_CLZ_08S[] = {{8, 8, 2, 0, 0x0}, {8, 8, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData88_CLZ_08S[] = {{10, 8, 2, 0, 0x0}, {10, 8, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData89_CLZ_08S[] = {{12, 8, 2, 0, 0x0}, {12, 8, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData90_CLZ_08S[] = {{14, 8, 2, 0, 0x0}, {14, 8, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData91_CLZ_08S[] = {{16, 8, 2, 0, 0x0}, {16, 8, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData92_CLZ_08S[] = {{18, 8, 2, 0, 0x0}, {18, 8, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData93_CLZ_08S[] = {{20, 8, 2, 0, 0x0}, {20, 8, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData94_CLZ_08S[] = {{22, 8, 2, 0, 0x0}, {22, 8, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData95_CLZ_08S[] = {{24, 8, 2, 0, 0x0}, {24, 8, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData96_CLZ_08S[] = {{26, 8, 2, 0, 0x0}, {26, 8, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData97_CLZ_08S[] = {{28, 8, 2, 0, 0x0}, {28, 8, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData98_CLZ_08S[] = {{30, 8, 2, 0, 0x0}, {30, 8, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData99_CLZ_08S[] = {{32, 8, 2, 0, 0x0}, {32, 8, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData100_CLZ_08S[] = {{48, 8, 2, 0, 0x0}, {48, 8, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData101_CLZ_08S[] = {{64, 8, 2, 0, 0x0}, {64, 8, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData102_CLZ_08S[] = {{96, 8, 2, 0, 0x0}, {96, 8, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData103_CLZ_08S[] = {{112, 8, 2, 0, 0x0}, {112, 8, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData104_CLZ_08S[] = {{2, 10, 2, 0, 0x0}, {2, 10, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData105_CLZ_08S[] = {{4, 10, 2, 0, 0x0}, {4, 10, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData106_CLZ_08S[] = {{6, 10, 2, 0, 0x0}, {6, 10, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData107_CLZ_08S[] = {{8, 10, 2, 0, 0x0}, {8, 10, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData108_CLZ_08S[] = {{10, 10, 2, 0, 0x0}, {10, 10, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData109_CLZ_08S[] = {{12, 10, 2, 0, 0x0}, {12, 10, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData110_CLZ_08S[] = {{14, 10, 2, 0, 0x0}, {14, 10, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData111_CLZ_08S[] = {{16, 10, 2, 0, 0x0}, {16, 10, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData112_CLZ_08S[] = {{18, 10, 2, 0, 0x0}, {18, 10, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData113_CLZ_08S[] = {{20, 10, 2, 0, 0x0}, {20, 10, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData114_CLZ_08S[] = {{22, 10, 2, 0, 0x0}, {22, 10, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData115_CLZ_08S[] = {{24, 10, 2, 0, 0x0}, {24, 10, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData116_CLZ_08S[] = {{26, 10, 2, 0, 0x0}, {26, 10, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData117_CLZ_08S[] = {{28, 10, 2, 0, 0x0}, {28, 10, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData118_CLZ_08S[] = {{30, 10, 2, 0, 0x0}, {30, 10, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData119_CLZ_08S[] = {{32, 10, 2, 0, 0x0}, {32, 10, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData120_CLZ_08S[] = {{48, 10, 2, 0, 0x0}, {48, 10, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData121_CLZ_08S[] = {{64, 10, 2, 0, 0x0}, {64, 10, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData122_CLZ_08S[] = {{96, 10, 2, 0, 0x0}, {96, 10, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData123_CLZ_08S[] = {{2, 12, 2, 0, 0x0}, {2, 12, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData124_CLZ_08S[] = {{4, 12, 2, 0, 0x0}, {4, 12, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData125_CLZ_08S[] = {{6, 12, 2, 0, 0x0}, {6, 12, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData126_CLZ_08S[] = {{8, 12, 2, 0, 0x0}, {8, 12, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData127_CLZ_08S[] = {{10, 12, 2, 0, 0x0}, {10, 12, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData128_CLZ_08S[] = {{12, 12, 2, 0, 0x0}, {12, 12, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData129_CLZ_08S[] = {{14, 12, 2, 0, 0x0}, {14, 12, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData130_CLZ_08S[] = {{16, 12, 2, 0, 0x0}, {16, 12, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData131_CLZ_08S[] = {{18, 12, 2, 0, 0x0}, {18, 12, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData132_CLZ_08S[] = {{20, 12, 2, 0, 0x0}, {20, 12, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData133_CLZ_08S[] = {{22, 12, 2, 0, 0x0}, {22, 12, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData134_CLZ_08S[] = {{24, 12, 2, 0, 0x0}, {24, 12, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData135_CLZ_08S[] = {{26, 12, 2, 0, 0x0}, {26, 12, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData136_CLZ_08S[] = {{28, 12, 2, 0, 0x0}, {28, 12, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData137_CLZ_08S[] = {{30, 12, 2, 0, 0x0}, {30, 12, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData138_CLZ_08S[] = {{32, 12, 2, 0, 0x0}, {32, 12, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData139_CLZ_08S[] = {{48, 12, 2, 0, 0x0}, {48, 12, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData140_CLZ_08S[] = {{64, 12, 2, 0, 0x0}, {64, 12, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData141_CLZ_08S[] = {{2, 14, 2, 0, 0x0}, {2, 14, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData142_CLZ_08S[] = {{4, 14, 2, 0, 0x0}, {4, 14, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData143_CLZ_08S[] = {{6, 14, 2, 0, 0x0}, {6, 14, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData144_CLZ_08S[] = {{8, 14, 2, 0, 0x0}, {8, 14, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData145_CLZ_08S[] = {{10, 14, 2, 0, 0x0}, {10, 14, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData146_CLZ_08S[] = {{12, 14, 2, 0, 0x0}, {12, 14, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData147_CLZ_08S[] = {{14, 14, 2, 0, 0x0}, {14, 14, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData148_CLZ_08S[] = {{16, 14, 2, 0, 0x0}, {16, 14, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData149_CLZ_08S[] = {{18, 14, 2, 0, 0x0}, {18, 14, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData150_CLZ_08S[] = {{20, 14, 2, 0, 0x0}, {20, 14, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData151_CLZ_08S[] = {{22, 14, 2, 0, 0x0}, {22, 14, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData152_CLZ_08S[] = {{24, 14, 2, 0, 0x0}, {24, 14, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData153_CLZ_08S[] = {{26, 14, 2, 0, 0x0}, {26, 14, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData154_CLZ_08S[] = {{28, 14, 2, 0, 0x0}, {28, 14, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData155_CLZ_08S[] = {{30, 14, 2, 0, 0x0}, {30, 14, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData156_CLZ_08S[] = {{32, 14, 2, 0, 0x0}, {32, 14, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData157_CLZ_08S[] = {{48, 14, 2, 0, 0x0}, {48, 14, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData158_CLZ_08S[] = {{64, 14, 2, 0, 0x0}, {64, 14, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData159_CLZ_08S[] = {{2, 16, 2, 0, 0x0}, {2, 16, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData160_CLZ_08S[] = {{4, 16, 2, 0, 0x0}, {4, 16, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData161_CLZ_08S[] = {{6, 16, 2, 0, 0x0}, {6, 16, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData162_CLZ_08S[] = {{8, 16, 2, 0, 0x0}, {8, 16, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData163_CLZ_08S[] = {{10, 16, 2, 0, 0x0}, {10, 16, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData164_CLZ_08S[] = {{12, 16, 2, 0, 0x0}, {12, 16, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData165_CLZ_08S[] = {{14, 16, 2, 0, 0x0}, {14, 16, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData166_CLZ_08S[] = {{16, 16, 2, 0, 0x0}, {16, 16, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData167_CLZ_08S[] = {{18, 16, 2, 0, 0x0}, {18, 16, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData168_CLZ_08S[] = {{20, 16, 2, 0, 0x0}, {20, 16, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData169_CLZ_08S[] = {{22, 16, 2, 0, 0x0}, {22, 16, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData170_CLZ_08S[] = {{24, 16, 2, 0, 0x0}, {24, 16, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData171_CLZ_08S[] = {{26, 16, 2, 0, 0x0}, {26, 16, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData172_CLZ_08S[] = {{28, 16, 2, 0, 0x0}, {28, 16, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData173_CLZ_08S[] = {{30, 16, 2, 0, 0x0}, {30, 16, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData174_CLZ_08S[] = {{32, 16, 2, 0, 0x0}, {32, 16, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData175_CLZ_08S[] = {{48, 16, 2, 0, 0x0}, {48, 16, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData176_CLZ_08S[] = {{2, 18, 2, 0, 0x0}, {2, 18, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData177_CLZ_08S[] = {{4, 18, 2, 0, 0x0}, {4, 18, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData178_CLZ_08S[] = {{6, 18, 2, 0, 0x0}, {6, 18, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData179_CLZ_08S[] = {{8, 18, 2, 0, 0x0}, {8, 18, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData180_CLZ_08S[] = {{10, 18, 2, 0, 0x0}, {10, 18, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData181_CLZ_08S[] = {{12, 18, 2, 0, 0x0}, {12, 18, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData182_CLZ_08S[] = {{14, 18, 2, 0, 0x0}, {14, 18, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData183_CLZ_08S[] = {{16, 18, 2, 0, 0x0}, {16, 18, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData184_CLZ_08S[] = {{18, 18, 2, 0, 0x0}, {18, 18, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData185_CLZ_08S[] = {{20, 18, 2, 0, 0x0}, {20, 18, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData186_CLZ_08S[] = {{22, 18, 2, 0, 0x0}, {22, 18, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData187_CLZ_08S[] = {{24, 18, 2, 0, 0x0}, {24, 18, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData188_CLZ_08S[] = {{26, 18, 2, 0, 0x0}, {26, 18, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData189_CLZ_08S[] = {{28, 18, 2, 0, 0x0}, {28, 18, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData190_CLZ_08S[] = {{30, 18, 2, 0, 0x0}, {30, 18, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData191_CLZ_08S[] = {{32, 18, 2, 0, 0x0}, {32, 18, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData192_CLZ_08S[] = {{48, 18, 2, 0, 0x0}, {48, 18, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData193_CLZ_08S[] = {{2, 20, 2, 0, 0x0}, {2, 20, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData194_CLZ_08S[] = {{4, 20, 2, 0, 0x0}, {4, 20, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData195_CLZ_08S[] = {{6, 20, 2, 0, 0x0}, {6, 20, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData196_CLZ_08S[] = {{8, 20, 2, 0, 0x0}, {8, 20, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData197_CLZ_08S[] = {{10, 20, 2, 0, 0x0}, {10, 20, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData198_CLZ_08S[] = {{12, 20, 2, 0, 0x0}, {12, 20, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData199_CLZ_08S[] = {{14, 20, 2, 0, 0x0}, {14, 20, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData200_CLZ_08S[] = {{16, 20, 2, 0, 0x0}, {16, 20, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData201_CLZ_08S[] = {{18, 20, 2, 0, 0x0}, {18, 20, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData202_CLZ_08S[] = {{20, 20, 2, 0, 0x0}, {20, 20, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData203_CLZ_08S[] = {{22, 20, 2, 0, 0x0}, {22, 20, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData204_CLZ_08S[] = {{24, 20, 2, 0, 0x0}, {24, 20, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData205_CLZ_08S[] = {{26, 20, 2, 0, 0x0}, {26, 20, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData206_CLZ_08S[] = {{28, 20, 2, 0, 0x0}, {28, 20, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData207_CLZ_08S[] = {{30, 20, 2, 0, 0x0}, {30, 20, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData208_CLZ_08S[] = {{32, 20, 2, 0, 0x0}, {32, 20, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData209_CLZ_08S[] = {{48, 20, 2, 0, 0x0}, {48, 20, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData210_CLZ_08S[] = {{2, 22, 2, 0, 0x0}, {2, 22, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData211_CLZ_08S[] = {{4, 22, 2, 0, 0x0}, {4, 22, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData212_CLZ_08S[] = {{6, 22, 2, 0, 0x0}, {6, 22, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData213_CLZ_08S[] = {{8, 22, 2, 0, 0x0}, {8, 22, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData214_CLZ_08S[] = {{10, 22, 2, 0, 0x0}, {10, 22, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData215_CLZ_08S[] = {{12, 22, 2, 0, 0x0}, {12, 22, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData216_CLZ_08S[] = {{14, 22, 2, 0, 0x0}, {14, 22, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData217_CLZ_08S[] = {{16, 22, 2, 0, 0x0}, {16, 22, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData218_CLZ_08S[] = {{18, 22, 2, 0, 0x0}, {18, 22, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData219_CLZ_08S[] = {{20, 22, 2, 0, 0x0}, {20, 22, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData220_CLZ_08S[] = {{22, 22, 2, 0, 0x0}, {22, 22, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData221_CLZ_08S[] = {{24, 22, 2, 0, 0x0}, {24, 22, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData222_CLZ_08S[] = {{26, 22, 2, 0, 0x0}, {26, 22, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData223_CLZ_08S[] = {{28, 22, 2, 0, 0x0}, {28, 22, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData224_CLZ_08S[] = {{30, 22, 2, 0, 0x0}, {30, 22, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData225_CLZ_08S[] = {{32, 22, 2, 0, 0x0}, {32, 22, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData226_CLZ_08S[] = {{2, 24, 2, 0, 0x0}, {2, 24, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData227_CLZ_08S[] = {{4, 24, 2, 0, 0x0}, {4, 24, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData228_CLZ_08S[] = {{6, 24, 2, 0, 0x0}, {6, 24, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData229_CLZ_08S[] = {{8, 24, 2, 0, 0x0}, {8, 24, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData230_CLZ_08S[] = {{10, 24, 2, 0, 0x0}, {10, 24, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData231_CLZ_08S[] = {{12, 24, 2, 0, 0x0}, {12, 24, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData232_CLZ_08S[] = {{14, 24, 2, 0, 0x0}, {14, 24, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData233_CLZ_08S[] = {{16, 24, 2, 0, 0x0}, {16, 24, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData234_CLZ_08S[] = {{18, 24, 2, 0, 0x0}, {18, 24, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData235_CLZ_08S[] = {{20, 24, 2, 0, 0x0}, {20, 24, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData236_CLZ_08S[] = {{22, 24, 2, 0, 0x0}, {22, 24, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData237_CLZ_08S[] = {{24, 24, 2, 0, 0x0}, {24, 24, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData238_CLZ_08S[] = {{26, 24, 2, 0, 0x0}, {26, 24, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData239_CLZ_08S[] = {{28, 24, 2, 0, 0x0}, {28, 24, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData240_CLZ_08S[] = {{30, 24, 2, 0, 0x0}, {30, 24, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData241_CLZ_08S[] = {{32, 24, 2, 0, 0x0}, {32, 24, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData242_CLZ_08S[] = {{2, 26, 2, 0, 0x0}, {2, 26, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData243_CLZ_08S[] = {{4, 26, 2, 0, 0x0}, {4, 26, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData244_CLZ_08S[] = {{6, 26, 2, 0, 0x0}, {6, 26, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData245_CLZ_08S[] = {{8, 26, 2, 0, 0x0}, {8, 26, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData246_CLZ_08S[] = {{10, 26, 2, 0, 0x0}, {10, 26, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData247_CLZ_08S[] = {{12, 26, 2, 0, 0x0}, {12, 26, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData248_CLZ_08S[] = {{14, 26, 2, 0, 0x0}, {14, 26, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData249_CLZ_08S[] = {{16, 26, 2, 0, 0x0}, {16, 26, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData250_CLZ_08S[] = {{18, 26, 2, 0, 0x0}, {18, 26, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData251_CLZ_08S[] = {{20, 26, 2, 0, 0x0}, {20, 26, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData252_CLZ_08S[] = {{22, 26, 2, 0, 0x0}, {22, 26, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData253_CLZ_08S[] = {{24, 26, 2, 0, 0x0}, {24, 26, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData254_CLZ_08S[] = {{26, 26, 2, 0, 0x0}, {26, 26, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData255_CLZ_08S[] = {{28, 26, 2, 0, 0x0}, {28, 26, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData256_CLZ_08S[] = {{30, 26, 2, 0, 0x0}, {30, 26, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData257_CLZ_08S[] = {{32, 26, 2, 0, 0x0}, {32, 26, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData258_CLZ_08S[] = {{2, 28, 2, 0, 0x0}, {2, 28, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData259_CLZ_08S[] = {{4, 28, 2, 0, 0x0}, {4, 28, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData260_CLZ_08S[] = {{6, 28, 2, 0, 0x0}, {6, 28, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData261_CLZ_08S[] = {{8, 28, 2, 0, 0x0}, {8, 28, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData262_CLZ_08S[] = {{10, 28, 2, 0, 0x0}, {10, 28, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData263_CLZ_08S[] = {{12, 28, 2, 0, 0x0}, {12, 28, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData264_CLZ_08S[] = {{14, 28, 2, 0, 0x0}, {14, 28, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData265_CLZ_08S[] = {{16, 28, 2, 0, 0x0}, {16, 28, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData266_CLZ_08S[] = {{18, 28, 2, 0, 0x0}, {18, 28, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData267_CLZ_08S[] = {{20, 28, 2, 0, 0x0}, {20, 28, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData268_CLZ_08S[] = {{22, 28, 2, 0, 0x0}, {22, 28, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData269_CLZ_08S[] = {{24, 28, 2, 0, 0x0}, {24, 28, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData270_CLZ_08S[] = {{26, 28, 2, 0, 0x0}, {26, 28, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData271_CLZ_08S[] = {{28, 28, 2, 0, 0x0}, {28, 28, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData272_CLZ_08S[] = {{30, 28, 2, 0, 0x0}, {30, 28, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData273_CLZ_08S[] = {{32, 28, 2, 0, 0x0}, {32, 28, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData274_CLZ_08S[] = {{2, 30, 2, 0, 0x0}, {2, 30, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData275_CLZ_08S[] = {{4, 30, 2, 0, 0x0}, {4, 30, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData276_CLZ_08S[] = {{6, 30, 2, 0, 0x0}, {6, 30, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData277_CLZ_08S[] = {{8, 30, 2, 0, 0x0}, {8, 30, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData278_CLZ_08S[] = {{10, 30, 2, 0, 0x0}, {10, 30, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData279_CLZ_08S[] = {{12, 30, 2, 0, 0x0}, {12, 30, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData280_CLZ_08S[] = {{14, 30, 2, 0, 0x0}, {14, 30, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData281_CLZ_08S[] = {{16, 30, 2, 0, 0x0}, {16, 30, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData282_CLZ_08S[] = {{18, 30, 2, 0, 0x0}, {18, 30, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData283_CLZ_08S[] = {{20, 30, 2, 0, 0x0}, {20, 30, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData284_CLZ_08S[] = {{22, 30, 2, 0, 0x0}, {22, 30, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData285_CLZ_08S[] = {{24, 30, 2, 0, 0x0}, {24, 30, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData286_CLZ_08S[] = {{26, 30, 2, 0, 0x0}, {26, 30, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData287_CLZ_08S[] = {{28, 30, 2, 0, 0x0}, {28, 30, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData288_CLZ_08S[] = {{30, 30, 2, 0, 0x0}, {30, 30, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData289_CLZ_08S[] = {{32, 30, 2, 0, 0x0}, {32, 30, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData290_CLZ_08S[] = {{2, 32, 2, 0, 0x0}, {2, 32, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData291_CLZ_08S[] = {{4, 32, 2, 0, 0x0}, {4, 32, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData292_CLZ_08S[] = {{6, 32, 2, 0, 0x0}, {6, 32, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData293_CLZ_08S[] = {{8, 32, 2, 0, 0x0}, {8, 32, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData294_CLZ_08S[] = {{10, 32, 2, 0, 0x0}, {10, 32, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData295_CLZ_08S[] = {{12, 32, 2, 0, 0x0}, {12, 32, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData296_CLZ_08S[] = {{14, 32, 2, 0, 0x0}, {14, 32, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData297_CLZ_08S[] = {{16, 32, 2, 0, 0x0}, {16, 32, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData298_CLZ_08S[] = {{18, 32, 2, 0, 0x0}, {18, 32, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData299_CLZ_08S[] = {{20, 32, 2, 0, 0x0}, {20, 32, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData300_CLZ_08S[] = {{22, 32, 2, 0, 0x0}, {22, 32, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData301_CLZ_08S[] = {{24, 32, 2, 0, 0x0}, {24, 32, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData302_CLZ_08S[] = {{26, 32, 2, 0, 0x0}, {26, 32, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData303_CLZ_08S[] = {{28, 32, 2, 0, 0x0}, {28, 32, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData304_CLZ_08S[] = {{30, 32, 2, 0, 0x0}, {30, 32, 2, 0, 0x0}};

static acf_scenario_kernel_data gScenarioKernelData0_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData1_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData2_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData3_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData4_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData5_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData6_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData7_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData8_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData9_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData10_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData11_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData12_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData13_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData14_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData15_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData16_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData17_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData18_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData19_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData20_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData21_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData22_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData23_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData24_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData25_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData26_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData27_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData28_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData29_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData30_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData31_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData32_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData33_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData34_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData35_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData36_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData37_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData38_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData39_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData40_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData41_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData42_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData43_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData44_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData45_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData46_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData47_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData48_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData49_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData50_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData51_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData52_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData53_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData54_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData55_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData56_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData57_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData58_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData59_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData60_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData61_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData62_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData63_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData64_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData65_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData66_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData67_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData68_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData69_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData70_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData71_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData72_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData73_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData74_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData75_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData76_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData77_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData78_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData79_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData80_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData81_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData82_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData83_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData84_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData85_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData86_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData87_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData88_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData89_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData90_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData91_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData92_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData93_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData94_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData95_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData96_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData97_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData98_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData99_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData100_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData101_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData102_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData103_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData104_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData105_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData106_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData107_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData108_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData109_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData110_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData111_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData112_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData113_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData114_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData115_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData116_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData117_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData118_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData119_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData120_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData121_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData122_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData123_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData124_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData125_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData126_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData127_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData128_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData129_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData130_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData131_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData132_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData133_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData134_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData135_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData136_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData137_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData138_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData139_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData140_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData141_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData142_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData143_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData144_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData145_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData146_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData147_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData148_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData149_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData150_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData151_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData152_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData153_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData154_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData155_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData156_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData157_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData158_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData159_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData160_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData161_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData162_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData163_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData164_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData165_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData166_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData167_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData168_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData169_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData170_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData171_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData172_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData173_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData174_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData175_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData176_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData177_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData178_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData179_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData180_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData181_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData182_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData183_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData184_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData185_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData186_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData187_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData188_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData189_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData190_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData191_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData192_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData193_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData194_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData195_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData196_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData197_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData198_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData199_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData200_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData201_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData202_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData203_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData204_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData205_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData206_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData207_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData208_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData209_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData210_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData211_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData212_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData213_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData214_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData215_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData216_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData217_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData218_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData219_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData220_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData221_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData222_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData223_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData224_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData225_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData226_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData227_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData228_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData229_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData230_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData231_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData232_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData233_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData234_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData235_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData236_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData237_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData238_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData239_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData240_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData241_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData242_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData243_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData244_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData245_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData246_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData247_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData248_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData249_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData250_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData251_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData252_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData253_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData254_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData255_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData256_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData257_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData258_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData259_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData260_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData261_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData262_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData263_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData264_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData265_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData266_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData267_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData268_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData269_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData270_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData271_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData272_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData273_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData274_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData275_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData276_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData277_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData278_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData279_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData280_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData281_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData282_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData283_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData284_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData285_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData286_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData287_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData288_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData289_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData290_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData291_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData292_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData293_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData294_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData295_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData296_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData297_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData298_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData299_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData300_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData301_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData302_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData303_CLZ_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData304_CLZ_08S[] = {{0}};

static acf_scenario gScenarioArray_CLZ_08S[] = {
{2, 1, 8, 0, 0, gScenarioBufferData0_CLZ_08S, 20, gScenarioKernelData0_CLZ_08S, 2},
{4, 1, 16, 0, 0, gScenarioBufferData1_CLZ_08S, 20, gScenarioKernelData1_CLZ_08S, 2},
{6, 1, 24, 0, 0, gScenarioBufferData2_CLZ_08S, 20, gScenarioKernelData2_CLZ_08S, 2},
{8, 1, 32, 0, 0, gScenarioBufferData3_CLZ_08S, 20, gScenarioKernelData3_CLZ_08S, 2},
{10, 1, 40, 0, 0, gScenarioBufferData4_CLZ_08S, 20, gScenarioKernelData4_CLZ_08S, 2},
{12, 1, 48, 0, 0, gScenarioBufferData5_CLZ_08S, 20, gScenarioKernelData5_CLZ_08S, 2},
{14, 1, 56, 0, 0, gScenarioBufferData6_CLZ_08S, 20, gScenarioKernelData6_CLZ_08S, 2},
{16, 1, 64, 0, 0, gScenarioBufferData7_CLZ_08S, 20, gScenarioKernelData7_CLZ_08S, 2},
{18, 1, 72, 0, 0, gScenarioBufferData8_CLZ_08S, 20, gScenarioKernelData8_CLZ_08S, 2},
{20, 1, 80, 0, 0, gScenarioBufferData9_CLZ_08S, 20, gScenarioKernelData9_CLZ_08S, 2},
{22, 1, 88, 0, 0, gScenarioBufferData10_CLZ_08S, 20, gScenarioKernelData10_CLZ_08S, 2},
{24, 1, 96, 0, 0, gScenarioBufferData11_CLZ_08S, 20, gScenarioKernelData11_CLZ_08S, 2},
{26, 1, 104, 0, 0, gScenarioBufferData12_CLZ_08S, 20, gScenarioKernelData12_CLZ_08S, 2},
{28, 1, 112, 0, 0, gScenarioBufferData13_CLZ_08S, 20, gScenarioKernelData13_CLZ_08S, 2},
{30, 1, 120, 0, 0, gScenarioBufferData14_CLZ_08S, 20, gScenarioKernelData14_CLZ_08S, 2},
{32, 1, 128, 0, 0, gScenarioBufferData15_CLZ_08S, 20, gScenarioKernelData15_CLZ_08S, 2},
{48, 1, 192, 0, 0, gScenarioBufferData16_CLZ_08S, 20, gScenarioKernelData16_CLZ_08S, 2},
{64, 1, 256, 0, 0, gScenarioBufferData17_CLZ_08S, 20, gScenarioKernelData17_CLZ_08S, 2},
{96, 1, 384, 0, 0, gScenarioBufferData18_CLZ_08S, 20, gScenarioKernelData18_CLZ_08S, 2},
{112, 1, 448, 0, 0, gScenarioBufferData19_CLZ_08S, 20, gScenarioKernelData19_CLZ_08S, 2},
{128, 1, 512, 0, 0, gScenarioBufferData20_CLZ_08S, 20, gScenarioKernelData20_CLZ_08S, 2},
{2, 2, 16, 0, 0, gScenarioBufferData21_CLZ_08S, 20, gScenarioKernelData21_CLZ_08S, 2},
{4, 2, 32, 0, 0, gScenarioBufferData22_CLZ_08S, 20, gScenarioKernelData22_CLZ_08S, 2},
{6, 2, 48, 0, 0, gScenarioBufferData23_CLZ_08S, 20, gScenarioKernelData23_CLZ_08S, 2},
{8, 2, 64, 0, 0, gScenarioBufferData24_CLZ_08S, 20, gScenarioKernelData24_CLZ_08S, 2},
{10, 2, 80, 0, 0, gScenarioBufferData25_CLZ_08S, 20, gScenarioKernelData25_CLZ_08S, 2},
{12, 2, 96, 0, 0, gScenarioBufferData26_CLZ_08S, 20, gScenarioKernelData26_CLZ_08S, 2},
{14, 2, 112, 0, 0, gScenarioBufferData27_CLZ_08S, 20, gScenarioKernelData27_CLZ_08S, 2},
{16, 2, 128, 0, 0, gScenarioBufferData28_CLZ_08S, 20, gScenarioKernelData28_CLZ_08S, 2},
{18, 2, 144, 0, 0, gScenarioBufferData29_CLZ_08S, 20, gScenarioKernelData29_CLZ_08S, 2},
{20, 2, 160, 0, 0, gScenarioBufferData30_CLZ_08S, 20, gScenarioKernelData30_CLZ_08S, 2},
{22, 2, 176, 0, 0, gScenarioBufferData31_CLZ_08S, 20, gScenarioKernelData31_CLZ_08S, 2},
{24, 2, 192, 0, 0, gScenarioBufferData32_CLZ_08S, 20, gScenarioKernelData32_CLZ_08S, 2},
{26, 2, 208, 0, 0, gScenarioBufferData33_CLZ_08S, 20, gScenarioKernelData33_CLZ_08S, 2},
{28, 2, 224, 0, 0, gScenarioBufferData34_CLZ_08S, 20, gScenarioKernelData34_CLZ_08S, 2},
{30, 2, 240, 0, 0, gScenarioBufferData35_CLZ_08S, 20, gScenarioKernelData35_CLZ_08S, 2},
{32, 2, 256, 0, 0, gScenarioBufferData36_CLZ_08S, 20, gScenarioKernelData36_CLZ_08S, 2},
{48, 2, 384, 0, 0, gScenarioBufferData37_CLZ_08S, 20, gScenarioKernelData37_CLZ_08S, 2},
{64, 2, 512, 0, 0, gScenarioBufferData38_CLZ_08S, 20, gScenarioKernelData38_CLZ_08S, 2},
{96, 2, 768, 0, 0, gScenarioBufferData39_CLZ_08S, 20, gScenarioKernelData39_CLZ_08S, 2},
{112, 2, 896, 0, 0, gScenarioBufferData40_CLZ_08S, 20, gScenarioKernelData40_CLZ_08S, 2},
{128, 2, 1024, 0, 0, gScenarioBufferData41_CLZ_08S, 20, gScenarioKernelData41_CLZ_08S, 2},
{2, 4, 32, 0, 0, gScenarioBufferData42_CLZ_08S, 20, gScenarioKernelData42_CLZ_08S, 2},
{4, 4, 64, 0, 0, gScenarioBufferData43_CLZ_08S, 20, gScenarioKernelData43_CLZ_08S, 2},
{6, 4, 96, 0, 0, gScenarioBufferData44_CLZ_08S, 20, gScenarioKernelData44_CLZ_08S, 2},
{8, 4, 128, 0, 0, gScenarioBufferData45_CLZ_08S, 20, gScenarioKernelData45_CLZ_08S, 2},
{10, 4, 160, 0, 0, gScenarioBufferData46_CLZ_08S, 20, gScenarioKernelData46_CLZ_08S, 2},
{12, 4, 192, 0, 0, gScenarioBufferData47_CLZ_08S, 20, gScenarioKernelData47_CLZ_08S, 2},
{14, 4, 224, 0, 0, gScenarioBufferData48_CLZ_08S, 20, gScenarioKernelData48_CLZ_08S, 2},
{16, 4, 256, 0, 0, gScenarioBufferData49_CLZ_08S, 20, gScenarioKernelData49_CLZ_08S, 2},
{18, 4, 288, 0, 0, gScenarioBufferData50_CLZ_08S, 20, gScenarioKernelData50_CLZ_08S, 2},
{20, 4, 320, 0, 0, gScenarioBufferData51_CLZ_08S, 20, gScenarioKernelData51_CLZ_08S, 2},
{22, 4, 352, 0, 0, gScenarioBufferData52_CLZ_08S, 20, gScenarioKernelData52_CLZ_08S, 2},
{24, 4, 384, 0, 0, gScenarioBufferData53_CLZ_08S, 20, gScenarioKernelData53_CLZ_08S, 2},
{26, 4, 416, 0, 0, gScenarioBufferData54_CLZ_08S, 20, gScenarioKernelData54_CLZ_08S, 2},
{28, 4, 448, 0, 0, gScenarioBufferData55_CLZ_08S, 20, gScenarioKernelData55_CLZ_08S, 2},
{30, 4, 480, 0, 0, gScenarioBufferData56_CLZ_08S, 20, gScenarioKernelData56_CLZ_08S, 2},
{32, 4, 512, 0, 0, gScenarioBufferData57_CLZ_08S, 20, gScenarioKernelData57_CLZ_08S, 2},
{48, 4, 768, 0, 0, gScenarioBufferData58_CLZ_08S, 20, gScenarioKernelData58_CLZ_08S, 2},
{64, 4, 1024, 0, 0, gScenarioBufferData59_CLZ_08S, 20, gScenarioKernelData59_CLZ_08S, 2},
{96, 4, 1536, 0, 0, gScenarioBufferData60_CLZ_08S, 20, gScenarioKernelData60_CLZ_08S, 2},
{112, 4, 1792, 0, 0, gScenarioBufferData61_CLZ_08S, 20, gScenarioKernelData61_CLZ_08S, 2},
{128, 4, 2048, 0, 0, gScenarioBufferData62_CLZ_08S, 20, gScenarioKernelData62_CLZ_08S, 2},
{2, 6, 48, 0, 0, gScenarioBufferData63_CLZ_08S, 20, gScenarioKernelData63_CLZ_08S, 2},
{4, 6, 96, 0, 0, gScenarioBufferData64_CLZ_08S, 20, gScenarioKernelData64_CLZ_08S, 2},
{6, 6, 144, 0, 0, gScenarioBufferData65_CLZ_08S, 20, gScenarioKernelData65_CLZ_08S, 2},
{8, 6, 192, 0, 0, gScenarioBufferData66_CLZ_08S, 20, gScenarioKernelData66_CLZ_08S, 2},
{10, 6, 240, 0, 0, gScenarioBufferData67_CLZ_08S, 20, gScenarioKernelData67_CLZ_08S, 2},
{12, 6, 288, 0, 0, gScenarioBufferData68_CLZ_08S, 20, gScenarioKernelData68_CLZ_08S, 2},
{14, 6, 336, 0, 0, gScenarioBufferData69_CLZ_08S, 20, gScenarioKernelData69_CLZ_08S, 2},
{16, 6, 384, 0, 0, gScenarioBufferData70_CLZ_08S, 20, gScenarioKernelData70_CLZ_08S, 2},
{18, 6, 432, 0, 0, gScenarioBufferData71_CLZ_08S, 20, gScenarioKernelData71_CLZ_08S, 2},
{20, 6, 480, 0, 0, gScenarioBufferData72_CLZ_08S, 20, gScenarioKernelData72_CLZ_08S, 2},
{22, 6, 528, 0, 0, gScenarioBufferData73_CLZ_08S, 20, gScenarioKernelData73_CLZ_08S, 2},
{24, 6, 576, 0, 0, gScenarioBufferData74_CLZ_08S, 20, gScenarioKernelData74_CLZ_08S, 2},
{26, 6, 624, 0, 0, gScenarioBufferData75_CLZ_08S, 20, gScenarioKernelData75_CLZ_08S, 2},
{28, 6, 672, 0, 0, gScenarioBufferData76_CLZ_08S, 20, gScenarioKernelData76_CLZ_08S, 2},
{30, 6, 720, 0, 0, gScenarioBufferData77_CLZ_08S, 20, gScenarioKernelData77_CLZ_08S, 2},
{32, 6, 768, 0, 0, gScenarioBufferData78_CLZ_08S, 20, gScenarioKernelData78_CLZ_08S, 2},
{48, 6, 1152, 0, 0, gScenarioBufferData79_CLZ_08S, 20, gScenarioKernelData79_CLZ_08S, 2},
{64, 6, 1536, 0, 0, gScenarioBufferData80_CLZ_08S, 20, gScenarioKernelData80_CLZ_08S, 2},
{96, 6, 2304, 0, 0, gScenarioBufferData81_CLZ_08S, 20, gScenarioKernelData81_CLZ_08S, 2},
{112, 6, 2688, 0, 0, gScenarioBufferData82_CLZ_08S, 20, gScenarioKernelData82_CLZ_08S, 2},
{128, 6, 3072, 0, 0, gScenarioBufferData83_CLZ_08S, 20, gScenarioKernelData83_CLZ_08S, 2},
{2, 8, 64, 0, 0, gScenarioBufferData84_CLZ_08S, 20, gScenarioKernelData84_CLZ_08S, 2},
{4, 8, 128, 0, 0, gScenarioBufferData85_CLZ_08S, 20, gScenarioKernelData85_CLZ_08S, 2},
{6, 8, 192, 0, 0, gScenarioBufferData86_CLZ_08S, 20, gScenarioKernelData86_CLZ_08S, 2},
{8, 8, 256, 0, 0, gScenarioBufferData87_CLZ_08S, 20, gScenarioKernelData87_CLZ_08S, 2},
{10, 8, 320, 0, 0, gScenarioBufferData88_CLZ_08S, 20, gScenarioKernelData88_CLZ_08S, 2},
{12, 8, 384, 0, 0, gScenarioBufferData89_CLZ_08S, 20, gScenarioKernelData89_CLZ_08S, 2},
{14, 8, 448, 0, 0, gScenarioBufferData90_CLZ_08S, 20, gScenarioKernelData90_CLZ_08S, 2},
{16, 8, 512, 0, 0, gScenarioBufferData91_CLZ_08S, 20, gScenarioKernelData91_CLZ_08S, 2},
{18, 8, 576, 0, 0, gScenarioBufferData92_CLZ_08S, 20, gScenarioKernelData92_CLZ_08S, 2},
{20, 8, 640, 0, 0, gScenarioBufferData93_CLZ_08S, 20, gScenarioKernelData93_CLZ_08S, 2},
{22, 8, 704, 0, 0, gScenarioBufferData94_CLZ_08S, 20, gScenarioKernelData94_CLZ_08S, 2},
{24, 8, 768, 0, 0, gScenarioBufferData95_CLZ_08S, 20, gScenarioKernelData95_CLZ_08S, 2},
{26, 8, 832, 0, 0, gScenarioBufferData96_CLZ_08S, 20, gScenarioKernelData96_CLZ_08S, 2},
{28, 8, 896, 0, 0, gScenarioBufferData97_CLZ_08S, 20, gScenarioKernelData97_CLZ_08S, 2},
{30, 8, 960, 0, 0, gScenarioBufferData98_CLZ_08S, 20, gScenarioKernelData98_CLZ_08S, 2},
{32, 8, 1024, 0, 0, gScenarioBufferData99_CLZ_08S, 20, gScenarioKernelData99_CLZ_08S, 2},
{48, 8, 1536, 0, 0, gScenarioBufferData100_CLZ_08S, 20, gScenarioKernelData100_CLZ_08S, 2},
{64, 8, 2048, 0, 0, gScenarioBufferData101_CLZ_08S, 20, gScenarioKernelData101_CLZ_08S, 2},
{96, 8, 3072, 0, 0, gScenarioBufferData102_CLZ_08S, 20, gScenarioKernelData102_CLZ_08S, 2},
{112, 8, 3584, 0, 0, gScenarioBufferData103_CLZ_08S, 20, gScenarioKernelData103_CLZ_08S, 2},
{2, 10, 80, 0, 0, gScenarioBufferData104_CLZ_08S, 20, gScenarioKernelData104_CLZ_08S, 2},
{4, 10, 160, 0, 0, gScenarioBufferData105_CLZ_08S, 20, gScenarioKernelData105_CLZ_08S, 2},
{6, 10, 240, 0, 0, gScenarioBufferData106_CLZ_08S, 20, gScenarioKernelData106_CLZ_08S, 2},
{8, 10, 320, 0, 0, gScenarioBufferData107_CLZ_08S, 20, gScenarioKernelData107_CLZ_08S, 2},
{10, 10, 400, 0, 0, gScenarioBufferData108_CLZ_08S, 20, gScenarioKernelData108_CLZ_08S, 2},
{12, 10, 480, 0, 0, gScenarioBufferData109_CLZ_08S, 20, gScenarioKernelData109_CLZ_08S, 2},
{14, 10, 560, 0, 0, gScenarioBufferData110_CLZ_08S, 20, gScenarioKernelData110_CLZ_08S, 2},
{16, 10, 640, 0, 0, gScenarioBufferData111_CLZ_08S, 20, gScenarioKernelData111_CLZ_08S, 2},
{18, 10, 720, 0, 0, gScenarioBufferData112_CLZ_08S, 20, gScenarioKernelData112_CLZ_08S, 2},
{20, 10, 800, 0, 0, gScenarioBufferData113_CLZ_08S, 20, gScenarioKernelData113_CLZ_08S, 2},
{22, 10, 880, 0, 0, gScenarioBufferData114_CLZ_08S, 20, gScenarioKernelData114_CLZ_08S, 2},
{24, 10, 960, 0, 0, gScenarioBufferData115_CLZ_08S, 20, gScenarioKernelData115_CLZ_08S, 2},
{26, 10, 1040, 0, 0, gScenarioBufferData116_CLZ_08S, 20, gScenarioKernelData116_CLZ_08S, 2},
{28, 10, 1120, 0, 0, gScenarioBufferData117_CLZ_08S, 20, gScenarioKernelData117_CLZ_08S, 2},
{30, 10, 1200, 0, 0, gScenarioBufferData118_CLZ_08S, 20, gScenarioKernelData118_CLZ_08S, 2},
{32, 10, 1280, 0, 0, gScenarioBufferData119_CLZ_08S, 20, gScenarioKernelData119_CLZ_08S, 2},
{48, 10, 1920, 0, 0, gScenarioBufferData120_CLZ_08S, 20, gScenarioKernelData120_CLZ_08S, 2},
{64, 10, 2560, 0, 0, gScenarioBufferData121_CLZ_08S, 20, gScenarioKernelData121_CLZ_08S, 2},
{96, 10, 3840, 0, 0, gScenarioBufferData122_CLZ_08S, 20, gScenarioKernelData122_CLZ_08S, 2},
{2, 12, 96, 0, 0, gScenarioBufferData123_CLZ_08S, 20, gScenarioKernelData123_CLZ_08S, 2},
{4, 12, 192, 0, 0, gScenarioBufferData124_CLZ_08S, 20, gScenarioKernelData124_CLZ_08S, 2},
{6, 12, 288, 0, 0, gScenarioBufferData125_CLZ_08S, 20, gScenarioKernelData125_CLZ_08S, 2},
{8, 12, 384, 0, 0, gScenarioBufferData126_CLZ_08S, 20, gScenarioKernelData126_CLZ_08S, 2},
{10, 12, 480, 0, 0, gScenarioBufferData127_CLZ_08S, 20, gScenarioKernelData127_CLZ_08S, 2},
{12, 12, 576, 0, 0, gScenarioBufferData128_CLZ_08S, 20, gScenarioKernelData128_CLZ_08S, 2},
{14, 12, 672, 0, 0, gScenarioBufferData129_CLZ_08S, 20, gScenarioKernelData129_CLZ_08S, 2},
{16, 12, 768, 0, 0, gScenarioBufferData130_CLZ_08S, 20, gScenarioKernelData130_CLZ_08S, 2},
{18, 12, 864, 0, 0, gScenarioBufferData131_CLZ_08S, 20, gScenarioKernelData131_CLZ_08S, 2},
{20, 12, 960, 0, 0, gScenarioBufferData132_CLZ_08S, 20, gScenarioKernelData132_CLZ_08S, 2},
{22, 12, 1056, 0, 0, gScenarioBufferData133_CLZ_08S, 20, gScenarioKernelData133_CLZ_08S, 2},
{24, 12, 1152, 0, 0, gScenarioBufferData134_CLZ_08S, 20, gScenarioKernelData134_CLZ_08S, 2},
{26, 12, 1248, 0, 0, gScenarioBufferData135_CLZ_08S, 20, gScenarioKernelData135_CLZ_08S, 2},
{28, 12, 1344, 0, 0, gScenarioBufferData136_CLZ_08S, 20, gScenarioKernelData136_CLZ_08S, 2},
{30, 12, 1440, 0, 0, gScenarioBufferData137_CLZ_08S, 20, gScenarioKernelData137_CLZ_08S, 2},
{32, 12, 1536, 0, 0, gScenarioBufferData138_CLZ_08S, 20, gScenarioKernelData138_CLZ_08S, 2},
{48, 12, 2304, 0, 0, gScenarioBufferData139_CLZ_08S, 20, gScenarioKernelData139_CLZ_08S, 2},
{64, 12, 3072, 0, 0, gScenarioBufferData140_CLZ_08S, 20, gScenarioKernelData140_CLZ_08S, 2},
{2, 14, 112, 0, 0, gScenarioBufferData141_CLZ_08S, 20, gScenarioKernelData141_CLZ_08S, 2},
{4, 14, 224, 0, 0, gScenarioBufferData142_CLZ_08S, 20, gScenarioKernelData142_CLZ_08S, 2},
{6, 14, 336, 0, 0, gScenarioBufferData143_CLZ_08S, 20, gScenarioKernelData143_CLZ_08S, 2},
{8, 14, 448, 0, 0, gScenarioBufferData144_CLZ_08S, 20, gScenarioKernelData144_CLZ_08S, 2},
{10, 14, 560, 0, 0, gScenarioBufferData145_CLZ_08S, 20, gScenarioKernelData145_CLZ_08S, 2},
{12, 14, 672, 0, 0, gScenarioBufferData146_CLZ_08S, 20, gScenarioKernelData146_CLZ_08S, 2},
{14, 14, 784, 0, 0, gScenarioBufferData147_CLZ_08S, 20, gScenarioKernelData147_CLZ_08S, 2},
{16, 14, 896, 0, 0, gScenarioBufferData148_CLZ_08S, 20, gScenarioKernelData148_CLZ_08S, 2},
{18, 14, 1008, 0, 0, gScenarioBufferData149_CLZ_08S, 20, gScenarioKernelData149_CLZ_08S, 2},
{20, 14, 1120, 0, 0, gScenarioBufferData150_CLZ_08S, 20, gScenarioKernelData150_CLZ_08S, 2},
{22, 14, 1232, 0, 0, gScenarioBufferData151_CLZ_08S, 20, gScenarioKernelData151_CLZ_08S, 2},
{24, 14, 1344, 0, 0, gScenarioBufferData152_CLZ_08S, 20, gScenarioKernelData152_CLZ_08S, 2},
{26, 14, 1456, 0, 0, gScenarioBufferData153_CLZ_08S, 20, gScenarioKernelData153_CLZ_08S, 2},
{28, 14, 1568, 0, 0, gScenarioBufferData154_CLZ_08S, 20, gScenarioKernelData154_CLZ_08S, 2},
{30, 14, 1680, 0, 0, gScenarioBufferData155_CLZ_08S, 20, gScenarioKernelData155_CLZ_08S, 2},
{32, 14, 1792, 0, 0, gScenarioBufferData156_CLZ_08S, 20, gScenarioKernelData156_CLZ_08S, 2},
{48, 14, 2688, 0, 0, gScenarioBufferData157_CLZ_08S, 20, gScenarioKernelData157_CLZ_08S, 2},
{64, 14, 3584, 0, 0, gScenarioBufferData158_CLZ_08S, 20, gScenarioKernelData158_CLZ_08S, 2},
{2, 16, 128, 0, 0, gScenarioBufferData159_CLZ_08S, 20, gScenarioKernelData159_CLZ_08S, 2},
{4, 16, 256, 0, 0, gScenarioBufferData160_CLZ_08S, 20, gScenarioKernelData160_CLZ_08S, 2},
{6, 16, 384, 0, 0, gScenarioBufferData161_CLZ_08S, 20, gScenarioKernelData161_CLZ_08S, 2},
{8, 16, 512, 0, 0, gScenarioBufferData162_CLZ_08S, 20, gScenarioKernelData162_CLZ_08S, 2},
{10, 16, 640, 0, 0, gScenarioBufferData163_CLZ_08S, 20, gScenarioKernelData163_CLZ_08S, 2},
{12, 16, 768, 0, 0, gScenarioBufferData164_CLZ_08S, 20, gScenarioKernelData164_CLZ_08S, 2},
{14, 16, 896, 0, 0, gScenarioBufferData165_CLZ_08S, 20, gScenarioKernelData165_CLZ_08S, 2},
{16, 16, 1024, 0, 0, gScenarioBufferData166_CLZ_08S, 20, gScenarioKernelData166_CLZ_08S, 2},
{18, 16, 1152, 0, 0, gScenarioBufferData167_CLZ_08S, 20, gScenarioKernelData167_CLZ_08S, 2},
{20, 16, 1280, 0, 0, gScenarioBufferData168_CLZ_08S, 20, gScenarioKernelData168_CLZ_08S, 2},
{22, 16, 1408, 0, 0, gScenarioBufferData169_CLZ_08S, 20, gScenarioKernelData169_CLZ_08S, 2},
{24, 16, 1536, 0, 0, gScenarioBufferData170_CLZ_08S, 20, gScenarioKernelData170_CLZ_08S, 2},
{26, 16, 1664, 0, 0, gScenarioBufferData171_CLZ_08S, 20, gScenarioKernelData171_CLZ_08S, 2},
{28, 16, 1792, 0, 0, gScenarioBufferData172_CLZ_08S, 20, gScenarioKernelData172_CLZ_08S, 2},
{30, 16, 1920, 0, 0, gScenarioBufferData173_CLZ_08S, 20, gScenarioKernelData173_CLZ_08S, 2},
{32, 16, 2048, 0, 0, gScenarioBufferData174_CLZ_08S, 20, gScenarioKernelData174_CLZ_08S, 2},
{48, 16, 3072, 0, 0, gScenarioBufferData175_CLZ_08S, 20, gScenarioKernelData175_CLZ_08S, 2},
{2, 18, 144, 0, 0, gScenarioBufferData176_CLZ_08S, 20, gScenarioKernelData176_CLZ_08S, 2},
{4, 18, 288, 0, 0, gScenarioBufferData177_CLZ_08S, 20, gScenarioKernelData177_CLZ_08S, 2},
{6, 18, 432, 0, 0, gScenarioBufferData178_CLZ_08S, 20, gScenarioKernelData178_CLZ_08S, 2},
{8, 18, 576, 0, 0, gScenarioBufferData179_CLZ_08S, 20, gScenarioKernelData179_CLZ_08S, 2},
{10, 18, 720, 0, 0, gScenarioBufferData180_CLZ_08S, 20, gScenarioKernelData180_CLZ_08S, 2},
{12, 18, 864, 0, 0, gScenarioBufferData181_CLZ_08S, 20, gScenarioKernelData181_CLZ_08S, 2},
{14, 18, 1008, 0, 0, gScenarioBufferData182_CLZ_08S, 20, gScenarioKernelData182_CLZ_08S, 2},
{16, 18, 1152, 0, 0, gScenarioBufferData183_CLZ_08S, 20, gScenarioKernelData183_CLZ_08S, 2},
{18, 18, 1296, 0, 0, gScenarioBufferData184_CLZ_08S, 20, gScenarioKernelData184_CLZ_08S, 2},
{20, 18, 1440, 0, 0, gScenarioBufferData185_CLZ_08S, 20, gScenarioKernelData185_CLZ_08S, 2},
{22, 18, 1584, 0, 0, gScenarioBufferData186_CLZ_08S, 20, gScenarioKernelData186_CLZ_08S, 2},
{24, 18, 1728, 0, 0, gScenarioBufferData187_CLZ_08S, 20, gScenarioKernelData187_CLZ_08S, 2},
{26, 18, 1872, 0, 0, gScenarioBufferData188_CLZ_08S, 20, gScenarioKernelData188_CLZ_08S, 2},
{28, 18, 2016, 0, 0, gScenarioBufferData189_CLZ_08S, 20, gScenarioKernelData189_CLZ_08S, 2},
{30, 18, 2160, 0, 0, gScenarioBufferData190_CLZ_08S, 20, gScenarioKernelData190_CLZ_08S, 2},
{32, 18, 2304, 0, 0, gScenarioBufferData191_CLZ_08S, 20, gScenarioKernelData191_CLZ_08S, 2},
{48, 18, 3456, 0, 0, gScenarioBufferData192_CLZ_08S, 20, gScenarioKernelData192_CLZ_08S, 2},
{2, 20, 160, 0, 0, gScenarioBufferData193_CLZ_08S, 20, gScenarioKernelData193_CLZ_08S, 2},
{4, 20, 320, 0, 0, gScenarioBufferData194_CLZ_08S, 20, gScenarioKernelData194_CLZ_08S, 2},
{6, 20, 480, 0, 0, gScenarioBufferData195_CLZ_08S, 20, gScenarioKernelData195_CLZ_08S, 2},
{8, 20, 640, 0, 0, gScenarioBufferData196_CLZ_08S, 20, gScenarioKernelData196_CLZ_08S, 2},
{10, 20, 800, 0, 0, gScenarioBufferData197_CLZ_08S, 20, gScenarioKernelData197_CLZ_08S, 2},
{12, 20, 960, 0, 0, gScenarioBufferData198_CLZ_08S, 20, gScenarioKernelData198_CLZ_08S, 2},
{14, 20, 1120, 0, 0, gScenarioBufferData199_CLZ_08S, 20, gScenarioKernelData199_CLZ_08S, 2},
{16, 20, 1280, 0, 0, gScenarioBufferData200_CLZ_08S, 20, gScenarioKernelData200_CLZ_08S, 2},
{18, 20, 1440, 0, 0, gScenarioBufferData201_CLZ_08S, 20, gScenarioKernelData201_CLZ_08S, 2},
{20, 20, 1600, 0, 0, gScenarioBufferData202_CLZ_08S, 20, gScenarioKernelData202_CLZ_08S, 2},
{22, 20, 1760, 0, 0, gScenarioBufferData203_CLZ_08S, 20, gScenarioKernelData203_CLZ_08S, 2},
{24, 20, 1920, 0, 0, gScenarioBufferData204_CLZ_08S, 20, gScenarioKernelData204_CLZ_08S, 2},
{26, 20, 2080, 0, 0, gScenarioBufferData205_CLZ_08S, 20, gScenarioKernelData205_CLZ_08S, 2},
{28, 20, 2240, 0, 0, gScenarioBufferData206_CLZ_08S, 20, gScenarioKernelData206_CLZ_08S, 2},
{30, 20, 2400, 0, 0, gScenarioBufferData207_CLZ_08S, 20, gScenarioKernelData207_CLZ_08S, 2},
{32, 20, 2560, 0, 0, gScenarioBufferData208_CLZ_08S, 20, gScenarioKernelData208_CLZ_08S, 2},
{48, 20, 3840, 0, 0, gScenarioBufferData209_CLZ_08S, 20, gScenarioKernelData209_CLZ_08S, 2},
{2, 22, 176, 0, 0, gScenarioBufferData210_CLZ_08S, 20, gScenarioKernelData210_CLZ_08S, 2},
{4, 22, 352, 0, 0, gScenarioBufferData211_CLZ_08S, 20, gScenarioKernelData211_CLZ_08S, 2},
{6, 22, 528, 0, 0, gScenarioBufferData212_CLZ_08S, 20, gScenarioKernelData212_CLZ_08S, 2},
{8, 22, 704, 0, 0, gScenarioBufferData213_CLZ_08S, 20, gScenarioKernelData213_CLZ_08S, 2},
{10, 22, 880, 0, 0, gScenarioBufferData214_CLZ_08S, 20, gScenarioKernelData214_CLZ_08S, 2},
{12, 22, 1056, 0, 0, gScenarioBufferData215_CLZ_08S, 20, gScenarioKernelData215_CLZ_08S, 2},
{14, 22, 1232, 0, 0, gScenarioBufferData216_CLZ_08S, 20, gScenarioKernelData216_CLZ_08S, 2},
{16, 22, 1408, 0, 0, gScenarioBufferData217_CLZ_08S, 20, gScenarioKernelData217_CLZ_08S, 2},
{18, 22, 1584, 0, 0, gScenarioBufferData218_CLZ_08S, 20, gScenarioKernelData218_CLZ_08S, 2},
{20, 22, 1760, 0, 0, gScenarioBufferData219_CLZ_08S, 20, gScenarioKernelData219_CLZ_08S, 2},
{22, 22, 1936, 0, 0, gScenarioBufferData220_CLZ_08S, 20, gScenarioKernelData220_CLZ_08S, 2},
{24, 22, 2112, 0, 0, gScenarioBufferData221_CLZ_08S, 20, gScenarioKernelData221_CLZ_08S, 2},
{26, 22, 2288, 0, 0, gScenarioBufferData222_CLZ_08S, 20, gScenarioKernelData222_CLZ_08S, 2},
{28, 22, 2464, 0, 0, gScenarioBufferData223_CLZ_08S, 20, gScenarioKernelData223_CLZ_08S, 2},
{30, 22, 2640, 0, 0, gScenarioBufferData224_CLZ_08S, 20, gScenarioKernelData224_CLZ_08S, 2},
{32, 22, 2816, 0, 0, gScenarioBufferData225_CLZ_08S, 20, gScenarioKernelData225_CLZ_08S, 2},
{2, 24, 192, 0, 0, gScenarioBufferData226_CLZ_08S, 20, gScenarioKernelData226_CLZ_08S, 2},
{4, 24, 384, 0, 0, gScenarioBufferData227_CLZ_08S, 20, gScenarioKernelData227_CLZ_08S, 2},
{6, 24, 576, 0, 0, gScenarioBufferData228_CLZ_08S, 20, gScenarioKernelData228_CLZ_08S, 2},
{8, 24, 768, 0, 0, gScenarioBufferData229_CLZ_08S, 20, gScenarioKernelData229_CLZ_08S, 2},
{10, 24, 960, 0, 0, gScenarioBufferData230_CLZ_08S, 20, gScenarioKernelData230_CLZ_08S, 2},
{12, 24, 1152, 0, 0, gScenarioBufferData231_CLZ_08S, 20, gScenarioKernelData231_CLZ_08S, 2},
{14, 24, 1344, 0, 0, gScenarioBufferData232_CLZ_08S, 20, gScenarioKernelData232_CLZ_08S, 2},
{16, 24, 1536, 0, 0, gScenarioBufferData233_CLZ_08S, 20, gScenarioKernelData233_CLZ_08S, 2},
{18, 24, 1728, 0, 0, gScenarioBufferData234_CLZ_08S, 20, gScenarioKernelData234_CLZ_08S, 2},
{20, 24, 1920, 0, 0, gScenarioBufferData235_CLZ_08S, 20, gScenarioKernelData235_CLZ_08S, 2},
{22, 24, 2112, 0, 0, gScenarioBufferData236_CLZ_08S, 20, gScenarioKernelData236_CLZ_08S, 2},
{24, 24, 2304, 0, 0, gScenarioBufferData237_CLZ_08S, 20, gScenarioKernelData237_CLZ_08S, 2},
{26, 24, 2496, 0, 0, gScenarioBufferData238_CLZ_08S, 20, gScenarioKernelData238_CLZ_08S, 2},
{28, 24, 2688, 0, 0, gScenarioBufferData239_CLZ_08S, 20, gScenarioKernelData239_CLZ_08S, 2},
{30, 24, 2880, 0, 0, gScenarioBufferData240_CLZ_08S, 20, gScenarioKernelData240_CLZ_08S, 2},
{32, 24, 3072, 0, 0, gScenarioBufferData241_CLZ_08S, 20, gScenarioKernelData241_CLZ_08S, 2},
{2, 26, 208, 0, 0, gScenarioBufferData242_CLZ_08S, 20, gScenarioKernelData242_CLZ_08S, 2},
{4, 26, 416, 0, 0, gScenarioBufferData243_CLZ_08S, 20, gScenarioKernelData243_CLZ_08S, 2},
{6, 26, 624, 0, 0, gScenarioBufferData244_CLZ_08S, 20, gScenarioKernelData244_CLZ_08S, 2},
{8, 26, 832, 0, 0, gScenarioBufferData245_CLZ_08S, 20, gScenarioKernelData245_CLZ_08S, 2},
{10, 26, 1040, 0, 0, gScenarioBufferData246_CLZ_08S, 20, gScenarioKernelData246_CLZ_08S, 2},
{12, 26, 1248, 0, 0, gScenarioBufferData247_CLZ_08S, 20, gScenarioKernelData247_CLZ_08S, 2},
{14, 26, 1456, 0, 0, gScenarioBufferData248_CLZ_08S, 20, gScenarioKernelData248_CLZ_08S, 2},
{16, 26, 1664, 0, 0, gScenarioBufferData249_CLZ_08S, 20, gScenarioKernelData249_CLZ_08S, 2},
{18, 26, 1872, 0, 0, gScenarioBufferData250_CLZ_08S, 20, gScenarioKernelData250_CLZ_08S, 2},
{20, 26, 2080, 0, 0, gScenarioBufferData251_CLZ_08S, 20, gScenarioKernelData251_CLZ_08S, 2},
{22, 26, 2288, 0, 0, gScenarioBufferData252_CLZ_08S, 20, gScenarioKernelData252_CLZ_08S, 2},
{24, 26, 2496, 0, 0, gScenarioBufferData253_CLZ_08S, 20, gScenarioKernelData253_CLZ_08S, 2},
{26, 26, 2704, 0, 0, gScenarioBufferData254_CLZ_08S, 20, gScenarioKernelData254_CLZ_08S, 2},
{28, 26, 2912, 0, 0, gScenarioBufferData255_CLZ_08S, 20, gScenarioKernelData255_CLZ_08S, 2},
{30, 26, 3120, 0, 0, gScenarioBufferData256_CLZ_08S, 20, gScenarioKernelData256_CLZ_08S, 2},
{32, 26, 3328, 0, 0, gScenarioBufferData257_CLZ_08S, 20, gScenarioKernelData257_CLZ_08S, 2},
{2, 28, 224, 0, 0, gScenarioBufferData258_CLZ_08S, 20, gScenarioKernelData258_CLZ_08S, 2},
{4, 28, 448, 0, 0, gScenarioBufferData259_CLZ_08S, 20, gScenarioKernelData259_CLZ_08S, 2},
{6, 28, 672, 0, 0, gScenarioBufferData260_CLZ_08S, 20, gScenarioKernelData260_CLZ_08S, 2},
{8, 28, 896, 0, 0, gScenarioBufferData261_CLZ_08S, 20, gScenarioKernelData261_CLZ_08S, 2},
{10, 28, 1120, 0, 0, gScenarioBufferData262_CLZ_08S, 20, gScenarioKernelData262_CLZ_08S, 2},
{12, 28, 1344, 0, 0, gScenarioBufferData263_CLZ_08S, 20, gScenarioKernelData263_CLZ_08S, 2},
{14, 28, 1568, 0, 0, gScenarioBufferData264_CLZ_08S, 20, gScenarioKernelData264_CLZ_08S, 2},
{16, 28, 1792, 0, 0, gScenarioBufferData265_CLZ_08S, 20, gScenarioKernelData265_CLZ_08S, 2},
{18, 28, 2016, 0, 0, gScenarioBufferData266_CLZ_08S, 20, gScenarioKernelData266_CLZ_08S, 2},
{20, 28, 2240, 0, 0, gScenarioBufferData267_CLZ_08S, 20, gScenarioKernelData267_CLZ_08S, 2},
{22, 28, 2464, 0, 0, gScenarioBufferData268_CLZ_08S, 20, gScenarioKernelData268_CLZ_08S, 2},
{24, 28, 2688, 0, 0, gScenarioBufferData269_CLZ_08S, 20, gScenarioKernelData269_CLZ_08S, 2},
{26, 28, 2912, 0, 0, gScenarioBufferData270_CLZ_08S, 20, gScenarioKernelData270_CLZ_08S, 2},
{28, 28, 3136, 0, 0, gScenarioBufferData271_CLZ_08S, 20, gScenarioKernelData271_CLZ_08S, 2},
{30, 28, 3360, 0, 0, gScenarioBufferData272_CLZ_08S, 20, gScenarioKernelData272_CLZ_08S, 2},
{32, 28, 3584, 0, 0, gScenarioBufferData273_CLZ_08S, 20, gScenarioKernelData273_CLZ_08S, 2},
{2, 30, 240, 0, 0, gScenarioBufferData274_CLZ_08S, 20, gScenarioKernelData274_CLZ_08S, 2},
{4, 30, 480, 0, 0, gScenarioBufferData275_CLZ_08S, 20, gScenarioKernelData275_CLZ_08S, 2},
{6, 30, 720, 0, 0, gScenarioBufferData276_CLZ_08S, 20, gScenarioKernelData276_CLZ_08S, 2},
{8, 30, 960, 0, 0, gScenarioBufferData277_CLZ_08S, 20, gScenarioKernelData277_CLZ_08S, 2},
{10, 30, 1200, 0, 0, gScenarioBufferData278_CLZ_08S, 20, gScenarioKernelData278_CLZ_08S, 2},
{12, 30, 1440, 0, 0, gScenarioBufferData279_CLZ_08S, 20, gScenarioKernelData279_CLZ_08S, 2},
{14, 30, 1680, 0, 0, gScenarioBufferData280_CLZ_08S, 20, gScenarioKernelData280_CLZ_08S, 2},
{16, 30, 1920, 0, 0, gScenarioBufferData281_CLZ_08S, 20, gScenarioKernelData281_CLZ_08S, 2},
{18, 30, 2160, 0, 0, gScenarioBufferData282_CLZ_08S, 20, gScenarioKernelData282_CLZ_08S, 2},
{20, 30, 2400, 0, 0, gScenarioBufferData283_CLZ_08S, 20, gScenarioKernelData283_CLZ_08S, 2},
{22, 30, 2640, 0, 0, gScenarioBufferData284_CLZ_08S, 20, gScenarioKernelData284_CLZ_08S, 2},
{24, 30, 2880, 0, 0, gScenarioBufferData285_CLZ_08S, 20, gScenarioKernelData285_CLZ_08S, 2},
{26, 30, 3120, 0, 0, gScenarioBufferData286_CLZ_08S, 20, gScenarioKernelData286_CLZ_08S, 2},
{28, 30, 3360, 0, 0, gScenarioBufferData287_CLZ_08S, 20, gScenarioKernelData287_CLZ_08S, 2},
{30, 30, 3600, 0, 0, gScenarioBufferData288_CLZ_08S, 20, gScenarioKernelData288_CLZ_08S, 2},
{32, 30, 3840, 0, 0, gScenarioBufferData289_CLZ_08S, 20, gScenarioKernelData289_CLZ_08S, 2},
{2, 32, 256, 0, 0, gScenarioBufferData290_CLZ_08S, 20, gScenarioKernelData290_CLZ_08S, 2},
{4, 32, 512, 0, 0, gScenarioBufferData291_CLZ_08S, 20, gScenarioKernelData291_CLZ_08S, 2},
{6, 32, 768, 0, 0, gScenarioBufferData292_CLZ_08S, 20, gScenarioKernelData292_CLZ_08S, 2},
{8, 32, 1024, 0, 0, gScenarioBufferData293_CLZ_08S, 20, gScenarioKernelData293_CLZ_08S, 2},
{10, 32, 1280, 0, 0, gScenarioBufferData294_CLZ_08S, 20, gScenarioKernelData294_CLZ_08S, 2},
{12, 32, 1536, 0, 0, gScenarioBufferData295_CLZ_08S, 20, gScenarioKernelData295_CLZ_08S, 2},
{14, 32, 1792, 0, 0, gScenarioBufferData296_CLZ_08S, 20, gScenarioKernelData296_CLZ_08S, 2},
{16, 32, 2048, 0, 0, gScenarioBufferData297_CLZ_08S, 20, gScenarioKernelData297_CLZ_08S, 2},
{18, 32, 2304, 0, 0, gScenarioBufferData298_CLZ_08S, 20, gScenarioKernelData298_CLZ_08S, 2},
{20, 32, 2560, 0, 0, gScenarioBufferData299_CLZ_08S, 20, gScenarioKernelData299_CLZ_08S, 2},
{22, 32, 2816, 0, 0, gScenarioBufferData300_CLZ_08S, 20, gScenarioKernelData300_CLZ_08S, 2},
{24, 32, 3072, 0, 0, gScenarioBufferData301_CLZ_08S, 20, gScenarioKernelData301_CLZ_08S, 2},
{26, 32, 3328, 0, 0, gScenarioBufferData302_CLZ_08S, 20, gScenarioKernelData302_CLZ_08S, 2},
{28, 32, 3584, 0, 0, gScenarioBufferData303_CLZ_08S, 20, gScenarioKernelData303_CLZ_08S, 2},
{30, 32, 3840, 0, 0, gScenarioBufferData304_CLZ_08S, 20, gScenarioKernelData304_CLZ_08S, 2}
};

static acf_scenario_list gScenarioList_CLZ_08S = {
305, //number of scenarios
gScenarioArray_CLZ_08S};
//**************************************************************

class CLZ_08S : public ACF_Process_APU
{
public:
   CLZ_08S(int32_t apex_id = 0) : ACF_Process_APU(apex_id)
   {} 

   int32_t Initialize()
   {
      int32_t lRetVal = 0;

      if (!Initialized()) //initialization steps that only need to occur once
      {
         SetProcessIdentifier("CLZ_08S");
         SetApuLoadInfo(CLZ_08S_LOAD_SEGMENTS,
                        CLZ_08S_LOAD_PMEM, CLZ_08S_LOAD_PMEM_SIZE,
                        CLZ_08S_LOAD_DMEM, CLZ_08S_LOAD_DMEM_SIZE,
                        0, 0); //assuming _LOAD_CMEM does not exist

         //***NOTE: the order in which the following ports are added is meaningful; do not change!

         AddPort("INPUT_0", ICP_DATATYPE_08S, 1, 1, 2, 1, 0, 0, 0, 0, 0, 0, 0, 0x0);
         AddPort("OUTPUT_0", ICP_DATATYPE_08U, 1, 1, 2, 1, 1, 0, 0, 0, 0, 0, 1);

         CfgScenarios(&gScenarioList_CLZ_08S);

         FlagAsInitialized();
      }

      lRetVal = SelectApuConfiguration(mApuCfg, mApexId); //by default mApuCfg = ACF_APU_CFG__APEX0_DEFAULT and mApexId = 0

      return lRetVal;
   }
};

#endif //_ACF_PROCESS_APU_CLZ_08S
