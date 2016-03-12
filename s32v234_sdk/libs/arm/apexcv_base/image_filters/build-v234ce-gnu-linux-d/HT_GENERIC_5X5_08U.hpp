#ifndef _ACF_PROCESS_APU_HT_GENERIC_5X5_08U
#define _ACF_PROCESS_APU_HT_GENERIC_5X5_08U

#include <acf_process_apu.h>
#include <HT_GENERIC_5X5_08U_APU_LOAD.h> //APU load associated with this process
#include <stdint.h>


//SCENARIO LIST*************************************************
static acf_scenario_buffer_data gScenarioBufferData0_HT_GENERIC_5X5_08U[] = {{2, 1, 7, 0, 0x2222}, {2, 1, 2, 2, 0x0}, {25, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData1_HT_GENERIC_5X5_08U[] = {{4, 1, 7, 0, 0x2222}, {4, 1, 2, 2, 0x0}, {25, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData2_HT_GENERIC_5X5_08U[] = {{6, 1, 7, 0, 0x2222}, {6, 1, 2, 2, 0x0}, {25, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData3_HT_GENERIC_5X5_08U[] = {{8, 1, 7, 0, 0x2222}, {8, 1, 2, 2, 0x0}, {25, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData4_HT_GENERIC_5X5_08U[] = {{10, 1, 7, 0, 0x2222}, {10, 1, 2, 2, 0x0}, {25, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData5_HT_GENERIC_5X5_08U[] = {{12, 1, 7, 0, 0x2222}, {12, 1, 2, 2, 0x0}, {25, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData6_HT_GENERIC_5X5_08U[] = {{14, 1, 7, 0, 0x2222}, {14, 1, 2, 2, 0x0}, {25, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData7_HT_GENERIC_5X5_08U[] = {{16, 1, 7, 0, 0x2222}, {16, 1, 2, 2, 0x0}, {25, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData8_HT_GENERIC_5X5_08U[] = {{20, 1, 7, 0, 0x2222}, {20, 1, 2, 2, 0x0}, {25, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData9_HT_GENERIC_5X5_08U[] = {{24, 1, 7, 0, 0x2222}, {24, 1, 2, 2, 0x0}, {25, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData10_HT_GENERIC_5X5_08U[] = {{28, 1, 7, 0, 0x2222}, {28, 1, 2, 2, 0x0}, {25, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData11_HT_GENERIC_5X5_08U[] = {{32, 1, 7, 0, 0x2222}, {32, 1, 2, 2, 0x0}, {25, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData12_HT_GENERIC_5X5_08U[] = {{36, 1, 7, 0, 0x2222}, {36, 1, 2, 2, 0x0}, {25, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData13_HT_GENERIC_5X5_08U[] = {{40, 1, 7, 0, 0x2222}, {40, 1, 2, 2, 0x0}, {25, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData14_HT_GENERIC_5X5_08U[] = {{44, 1, 7, 0, 0x2222}, {44, 1, 2, 2, 0x0}, {25, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData15_HT_GENERIC_5X5_08U[] = {{48, 1, 7, 0, 0x2222}, {48, 1, 2, 2, 0x0}, {25, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData16_HT_GENERIC_5X5_08U[] = {{52, 1, 7, 0, 0x2222}, {52, 1, 2, 2, 0x0}, {25, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData17_HT_GENERIC_5X5_08U[] = {{56, 1, 7, 0, 0x2222}, {56, 1, 2, 2, 0x0}, {25, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData18_HT_GENERIC_5X5_08U[] = {{60, 1, 7, 0, 0x2222}, {60, 1, 2, 2, 0x0}, {25, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData19_HT_GENERIC_5X5_08U[] = {{64, 1, 7, 0, 0x2222}, {64, 1, 2, 2, 0x0}, {25, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData20_HT_GENERIC_5X5_08U[] = {{96, 1, 7, 0, 0x2222}, {96, 1, 2, 2, 0x0}, {25, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData21_HT_GENERIC_5X5_08U[] = {{128, 1, 7, 0, 0x2222}, {128, 1, 2, 2, 0x0}, {25, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData22_HT_GENERIC_5X5_08U[] = {{2, 2, 4, 0, 0x2222}, {2, 2, 2, 1, 0x0}, {25, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData23_HT_GENERIC_5X5_08U[] = {{4, 2, 4, 0, 0x2222}, {4, 2, 2, 1, 0x0}, {25, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData24_HT_GENERIC_5X5_08U[] = {{6, 2, 4, 0, 0x2222}, {6, 2, 2, 1, 0x0}, {25, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData25_HT_GENERIC_5X5_08U[] = {{8, 2, 4, 0, 0x2222}, {8, 2, 2, 1, 0x0}, {25, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData26_HT_GENERIC_5X5_08U[] = {{10, 2, 4, 0, 0x2222}, {10, 2, 2, 1, 0x0}, {25, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData27_HT_GENERIC_5X5_08U[] = {{12, 2, 4, 0, 0x2222}, {12, 2, 2, 1, 0x0}, {25, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData28_HT_GENERIC_5X5_08U[] = {{14, 2, 4, 0, 0x2222}, {14, 2, 2, 1, 0x0}, {25, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData29_HT_GENERIC_5X5_08U[] = {{16, 2, 4, 0, 0x2222}, {16, 2, 2, 1, 0x0}, {25, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData30_HT_GENERIC_5X5_08U[] = {{20, 2, 4, 0, 0x2222}, {20, 2, 2, 1, 0x0}, {25, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData31_HT_GENERIC_5X5_08U[] = {{24, 2, 4, 0, 0x2222}, {24, 2, 2, 1, 0x0}, {25, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData32_HT_GENERIC_5X5_08U[] = {{28, 2, 4, 0, 0x2222}, {28, 2, 2, 1, 0x0}, {25, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData33_HT_GENERIC_5X5_08U[] = {{32, 2, 4, 0, 0x2222}, {32, 2, 2, 1, 0x0}, {25, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData34_HT_GENERIC_5X5_08U[] = {{36, 2, 4, 0, 0x2222}, {36, 2, 2, 1, 0x0}, {25, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData35_HT_GENERIC_5X5_08U[] = {{40, 2, 4, 0, 0x2222}, {40, 2, 2, 1, 0x0}, {25, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData36_HT_GENERIC_5X5_08U[] = {{44, 2, 4, 0, 0x2222}, {44, 2, 2, 1, 0x0}, {25, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData37_HT_GENERIC_5X5_08U[] = {{48, 2, 4, 0, 0x2222}, {48, 2, 2, 1, 0x0}, {25, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData38_HT_GENERIC_5X5_08U[] = {{52, 2, 4, 0, 0x2222}, {52, 2, 2, 1, 0x0}, {25, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData39_HT_GENERIC_5X5_08U[] = {{56, 2, 4, 0, 0x2222}, {56, 2, 2, 1, 0x0}, {25, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData40_HT_GENERIC_5X5_08U[] = {{60, 2, 4, 0, 0x2222}, {60, 2, 2, 1, 0x0}, {25, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData41_HT_GENERIC_5X5_08U[] = {{64, 2, 4, 0, 0x2222}, {64, 2, 2, 1, 0x0}, {25, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData42_HT_GENERIC_5X5_08U[] = {{96, 2, 4, 0, 0x2222}, {96, 2, 2, 1, 0x0}, {25, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData43_HT_GENERIC_5X5_08U[] = {{128, 2, 4, 0, 0x2222}, {128, 2, 2, 1, 0x0}, {25, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData44_HT_GENERIC_5X5_08U[] = {{2, 4, 4, 0, 0x2222}, {2, 4, 2, 1, 0x0}, {25, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData45_HT_GENERIC_5X5_08U[] = {{4, 4, 4, 0, 0x2222}, {4, 4, 2, 1, 0x0}, {25, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData46_HT_GENERIC_5X5_08U[] = {{6, 4, 4, 0, 0x2222}, {6, 4, 2, 1, 0x0}, {25, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData47_HT_GENERIC_5X5_08U[] = {{8, 4, 4, 0, 0x2222}, {8, 4, 2, 1, 0x0}, {25, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData48_HT_GENERIC_5X5_08U[] = {{10, 4, 4, 0, 0x2222}, {10, 4, 2, 1, 0x0}, {25, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData49_HT_GENERIC_5X5_08U[] = {{12, 4, 4, 0, 0x2222}, {12, 4, 2, 1, 0x0}, {25, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData50_HT_GENERIC_5X5_08U[] = {{14, 4, 4, 0, 0x2222}, {14, 4, 2, 1, 0x0}, {25, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData51_HT_GENERIC_5X5_08U[] = {{16, 4, 4, 0, 0x2222}, {16, 4, 2, 1, 0x0}, {25, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData52_HT_GENERIC_5X5_08U[] = {{20, 4, 4, 0, 0x2222}, {20, 4, 2, 1, 0x0}, {25, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData53_HT_GENERIC_5X5_08U[] = {{24, 4, 4, 0, 0x2222}, {24, 4, 2, 1, 0x0}, {25, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData54_HT_GENERIC_5X5_08U[] = {{28, 4, 4, 0, 0x2222}, {28, 4, 2, 1, 0x0}, {25, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData55_HT_GENERIC_5X5_08U[] = {{32, 4, 4, 0, 0x2222}, {32, 4, 2, 1, 0x0}, {25, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData56_HT_GENERIC_5X5_08U[] = {{36, 4, 4, 0, 0x2222}, {36, 4, 2, 1, 0x0}, {25, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData57_HT_GENERIC_5X5_08U[] = {{40, 4, 4, 0, 0x2222}, {40, 4, 2, 1, 0x0}, {25, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData58_HT_GENERIC_5X5_08U[] = {{44, 4, 4, 0, 0x2222}, {44, 4, 2, 1, 0x0}, {25, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData59_HT_GENERIC_5X5_08U[] = {{48, 4, 4, 0, 0x2222}, {48, 4, 2, 1, 0x0}, {25, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData60_HT_GENERIC_5X5_08U[] = {{52, 4, 4, 0, 0x2222}, {52, 4, 2, 1, 0x0}, {25, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData61_HT_GENERIC_5X5_08U[] = {{56, 4, 4, 0, 0x2222}, {56, 4, 2, 1, 0x0}, {25, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData62_HT_GENERIC_5X5_08U[] = {{60, 4, 4, 0, 0x2222}, {60, 4, 2, 1, 0x0}, {25, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData63_HT_GENERIC_5X5_08U[] = {{64, 4, 4, 0, 0x2222}, {64, 4, 2, 1, 0x0}, {25, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData64_HT_GENERIC_5X5_08U[] = {{96, 4, 4, 0, 0x2222}, {96, 4, 2, 1, 0x0}, {25, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData65_HT_GENERIC_5X5_08U[] = {{128, 4, 4, 0, 0x2222}, {128, 4, 2, 1, 0x0}, {25, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData66_HT_GENERIC_5X5_08U[] = {{2, 6, 4, 0, 0x2222}, {2, 6, 2, 1, 0x0}, {25, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData67_HT_GENERIC_5X5_08U[] = {{4, 6, 4, 0, 0x2222}, {4, 6, 2, 1, 0x0}, {25, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData68_HT_GENERIC_5X5_08U[] = {{6, 6, 4, 0, 0x2222}, {6, 6, 2, 1, 0x0}, {25, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData69_HT_GENERIC_5X5_08U[] = {{8, 6, 4, 0, 0x2222}, {8, 6, 2, 1, 0x0}, {25, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData70_HT_GENERIC_5X5_08U[] = {{10, 6, 4, 0, 0x2222}, {10, 6, 2, 1, 0x0}, {25, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData71_HT_GENERIC_5X5_08U[] = {{12, 6, 4, 0, 0x2222}, {12, 6, 2, 1, 0x0}, {25, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData72_HT_GENERIC_5X5_08U[] = {{14, 6, 4, 0, 0x2222}, {14, 6, 2, 1, 0x0}, {25, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData73_HT_GENERIC_5X5_08U[] = {{16, 6, 4, 0, 0x2222}, {16, 6, 2, 1, 0x0}, {25, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData74_HT_GENERIC_5X5_08U[] = {{20, 6, 4, 0, 0x2222}, {20, 6, 2, 1, 0x0}, {25, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData75_HT_GENERIC_5X5_08U[] = {{24, 6, 4, 0, 0x2222}, {24, 6, 2, 1, 0x0}, {25, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData76_HT_GENERIC_5X5_08U[] = {{28, 6, 4, 0, 0x2222}, {28, 6, 2, 1, 0x0}, {25, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData77_HT_GENERIC_5X5_08U[] = {{32, 6, 4, 0, 0x2222}, {32, 6, 2, 1, 0x0}, {25, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData78_HT_GENERIC_5X5_08U[] = {{36, 6, 4, 0, 0x2222}, {36, 6, 2, 1, 0x0}, {25, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData79_HT_GENERIC_5X5_08U[] = {{40, 6, 4, 0, 0x2222}, {40, 6, 2, 1, 0x0}, {25, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData80_HT_GENERIC_5X5_08U[] = {{44, 6, 4, 0, 0x2222}, {44, 6, 2, 1, 0x0}, {25, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData81_HT_GENERIC_5X5_08U[] = {{48, 6, 4, 0, 0x2222}, {48, 6, 2, 1, 0x0}, {25, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData82_HT_GENERIC_5X5_08U[] = {{52, 6, 4, 0, 0x2222}, {52, 6, 2, 1, 0x0}, {25, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData83_HT_GENERIC_5X5_08U[] = {{56, 6, 4, 0, 0x2222}, {56, 6, 2, 1, 0x0}, {25, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData84_HT_GENERIC_5X5_08U[] = {{60, 6, 4, 0, 0x2222}, {60, 6, 2, 1, 0x0}, {25, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData85_HT_GENERIC_5X5_08U[] = {{64, 6, 4, 0, 0x2222}, {64, 6, 2, 1, 0x0}, {25, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData86_HT_GENERIC_5X5_08U[] = {{2, 8, 4, 0, 0x2222}, {2, 8, 2, 1, 0x0}, {25, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData87_HT_GENERIC_5X5_08U[] = {{4, 8, 4, 0, 0x2222}, {4, 8, 2, 1, 0x0}, {25, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData88_HT_GENERIC_5X5_08U[] = {{6, 8, 4, 0, 0x2222}, {6, 8, 2, 1, 0x0}, {25, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData89_HT_GENERIC_5X5_08U[] = {{8, 8, 4, 0, 0x2222}, {8, 8, 2, 1, 0x0}, {25, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData90_HT_GENERIC_5X5_08U[] = {{10, 8, 4, 0, 0x2222}, {10, 8, 2, 1, 0x0}, {25, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData91_HT_GENERIC_5X5_08U[] = {{12, 8, 4, 0, 0x2222}, {12, 8, 2, 1, 0x0}, {25, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData92_HT_GENERIC_5X5_08U[] = {{14, 8, 4, 0, 0x2222}, {14, 8, 2, 1, 0x0}, {25, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData93_HT_GENERIC_5X5_08U[] = {{16, 8, 4, 0, 0x2222}, {16, 8, 2, 1, 0x0}, {25, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData94_HT_GENERIC_5X5_08U[] = {{20, 8, 4, 0, 0x2222}, {20, 8, 2, 1, 0x0}, {25, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData95_HT_GENERIC_5X5_08U[] = {{24, 8, 4, 0, 0x2222}, {24, 8, 2, 1, 0x0}, {25, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData96_HT_GENERIC_5X5_08U[] = {{28, 8, 4, 0, 0x2222}, {28, 8, 2, 1, 0x0}, {25, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData97_HT_GENERIC_5X5_08U[] = {{32, 8, 4, 0, 0x2222}, {32, 8, 2, 1, 0x0}, {25, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData98_HT_GENERIC_5X5_08U[] = {{36, 8, 4, 0, 0x2222}, {36, 8, 2, 1, 0x0}, {25, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData99_HT_GENERIC_5X5_08U[] = {{40, 8, 4, 0, 0x2222}, {40, 8, 2, 1, 0x0}, {25, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData100_HT_GENERIC_5X5_08U[] = {{44, 8, 4, 0, 0x2222}, {44, 8, 2, 1, 0x0}, {25, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData101_HT_GENERIC_5X5_08U[] = {{48, 8, 4, 0, 0x2222}, {48, 8, 2, 1, 0x0}, {25, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData102_HT_GENERIC_5X5_08U[] = {{52, 8, 4, 0, 0x2222}, {52, 8, 2, 1, 0x0}, {25, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData103_HT_GENERIC_5X5_08U[] = {{56, 8, 4, 0, 0x2222}, {56, 8, 2, 1, 0x0}, {25, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData104_HT_GENERIC_5X5_08U[] = {{60, 8, 4, 0, 0x2222}, {60, 8, 2, 1, 0x0}, {25, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData105_HT_GENERIC_5X5_08U[] = {{64, 8, 4, 0, 0x2222}, {64, 8, 2, 1, 0x0}, {25, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData106_HT_GENERIC_5X5_08U[] = {{2, 10, 4, 0, 0x2222}, {2, 10, 2, 1, 0x0}, {25, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData107_HT_GENERIC_5X5_08U[] = {{4, 10, 4, 0, 0x2222}, {4, 10, 2, 1, 0x0}, {25, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData108_HT_GENERIC_5X5_08U[] = {{6, 10, 4, 0, 0x2222}, {6, 10, 2, 1, 0x0}, {25, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData109_HT_GENERIC_5X5_08U[] = {{8, 10, 4, 0, 0x2222}, {8, 10, 2, 1, 0x0}, {25, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData110_HT_GENERIC_5X5_08U[] = {{10, 10, 4, 0, 0x2222}, {10, 10, 2, 1, 0x0}, {25, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData111_HT_GENERIC_5X5_08U[] = {{12, 10, 4, 0, 0x2222}, {12, 10, 2, 1, 0x0}, {25, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData112_HT_GENERIC_5X5_08U[] = {{14, 10, 4, 0, 0x2222}, {14, 10, 2, 1, 0x0}, {25, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData113_HT_GENERIC_5X5_08U[] = {{16, 10, 4, 0, 0x2222}, {16, 10, 2, 1, 0x0}, {25, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData114_HT_GENERIC_5X5_08U[] = {{20, 10, 4, 0, 0x2222}, {20, 10, 2, 1, 0x0}, {25, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData115_HT_GENERIC_5X5_08U[] = {{24, 10, 4, 0, 0x2222}, {24, 10, 2, 1, 0x0}, {25, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData116_HT_GENERIC_5X5_08U[] = {{28, 10, 4, 0, 0x2222}, {28, 10, 2, 1, 0x0}, {25, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData117_HT_GENERIC_5X5_08U[] = {{32, 10, 4, 0, 0x2222}, {32, 10, 2, 1, 0x0}, {25, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData118_HT_GENERIC_5X5_08U[] = {{36, 10, 4, 0, 0x2222}, {36, 10, 2, 1, 0x0}, {25, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData119_HT_GENERIC_5X5_08U[] = {{40, 10, 4, 0, 0x2222}, {40, 10, 2, 1, 0x0}, {25, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData120_HT_GENERIC_5X5_08U[] = {{44, 10, 4, 0, 0x2222}, {44, 10, 2, 1, 0x0}, {25, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData121_HT_GENERIC_5X5_08U[] = {{48, 10, 4, 0, 0x2222}, {48, 10, 2, 1, 0x0}, {25, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData122_HT_GENERIC_5X5_08U[] = {{52, 10, 4, 0, 0x2222}, {52, 10, 2, 1, 0x0}, {25, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData123_HT_GENERIC_5X5_08U[] = {{56, 10, 4, 0, 0x2222}, {56, 10, 2, 1, 0x0}, {25, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData124_HT_GENERIC_5X5_08U[] = {{2, 12, 4, 0, 0x2222}, {2, 12, 2, 1, 0x0}, {25, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData125_HT_GENERIC_5X5_08U[] = {{4, 12, 4, 0, 0x2222}, {4, 12, 2, 1, 0x0}, {25, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData126_HT_GENERIC_5X5_08U[] = {{6, 12, 4, 0, 0x2222}, {6, 12, 2, 1, 0x0}, {25, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData127_HT_GENERIC_5X5_08U[] = {{8, 12, 4, 0, 0x2222}, {8, 12, 2, 1, 0x0}, {25, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData128_HT_GENERIC_5X5_08U[] = {{10, 12, 4, 0, 0x2222}, {10, 12, 2, 1, 0x0}, {25, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData129_HT_GENERIC_5X5_08U[] = {{12, 12, 4, 0, 0x2222}, {12, 12, 2, 1, 0x0}, {25, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData130_HT_GENERIC_5X5_08U[] = {{14, 12, 4, 0, 0x2222}, {14, 12, 2, 1, 0x0}, {25, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData131_HT_GENERIC_5X5_08U[] = {{16, 12, 4, 0, 0x2222}, {16, 12, 2, 1, 0x0}, {25, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData132_HT_GENERIC_5X5_08U[] = {{20, 12, 4, 0, 0x2222}, {20, 12, 2, 1, 0x0}, {25, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData133_HT_GENERIC_5X5_08U[] = {{24, 12, 4, 0, 0x2222}, {24, 12, 2, 1, 0x0}, {25, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData134_HT_GENERIC_5X5_08U[] = {{28, 12, 4, 0, 0x2222}, {28, 12, 2, 1, 0x0}, {25, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData135_HT_GENERIC_5X5_08U[] = {{32, 12, 4, 0, 0x2222}, {32, 12, 2, 1, 0x0}, {25, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData136_HT_GENERIC_5X5_08U[] = {{36, 12, 4, 0, 0x2222}, {36, 12, 2, 1, 0x0}, {25, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData137_HT_GENERIC_5X5_08U[] = {{40, 12, 4, 0, 0x2222}, {40, 12, 2, 1, 0x0}, {25, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData138_HT_GENERIC_5X5_08U[] = {{44, 12, 4, 0, 0x2222}, {44, 12, 2, 1, 0x0}, {25, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData139_HT_GENERIC_5X5_08U[] = {{2, 14, 4, 0, 0x2222}, {2, 14, 2, 1, 0x0}, {25, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData140_HT_GENERIC_5X5_08U[] = {{4, 14, 4, 0, 0x2222}, {4, 14, 2, 1, 0x0}, {25, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData141_HT_GENERIC_5X5_08U[] = {{6, 14, 4, 0, 0x2222}, {6, 14, 2, 1, 0x0}, {25, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData142_HT_GENERIC_5X5_08U[] = {{8, 14, 4, 0, 0x2222}, {8, 14, 2, 1, 0x0}, {25, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData143_HT_GENERIC_5X5_08U[] = {{10, 14, 4, 0, 0x2222}, {10, 14, 2, 1, 0x0}, {25, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData144_HT_GENERIC_5X5_08U[] = {{12, 14, 4, 0, 0x2222}, {12, 14, 2, 1, 0x0}, {25, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData145_HT_GENERIC_5X5_08U[] = {{14, 14, 4, 0, 0x2222}, {14, 14, 2, 1, 0x0}, {25, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData146_HT_GENERIC_5X5_08U[] = {{16, 14, 4, 0, 0x2222}, {16, 14, 2, 1, 0x0}, {25, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData147_HT_GENERIC_5X5_08U[] = {{20, 14, 4, 0, 0x2222}, {20, 14, 2, 1, 0x0}, {25, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData148_HT_GENERIC_5X5_08U[] = {{24, 14, 4, 0, 0x2222}, {24, 14, 2, 1, 0x0}, {25, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData149_HT_GENERIC_5X5_08U[] = {{28, 14, 4, 0, 0x2222}, {28, 14, 2, 1, 0x0}, {25, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData150_HT_GENERIC_5X5_08U[] = {{32, 14, 4, 0, 0x2222}, {32, 14, 2, 1, 0x0}, {25, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData151_HT_GENERIC_5X5_08U[] = {{36, 14, 4, 0, 0x2222}, {36, 14, 2, 1, 0x0}, {25, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData152_HT_GENERIC_5X5_08U[] = {{40, 14, 4, 0, 0x2222}, {40, 14, 2, 1, 0x0}, {25, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData153_HT_GENERIC_5X5_08U[] = {{2, 16, 4, 0, 0x2222}, {2, 16, 2, 1, 0x0}, {25, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData154_HT_GENERIC_5X5_08U[] = {{4, 16, 4, 0, 0x2222}, {4, 16, 2, 1, 0x0}, {25, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData155_HT_GENERIC_5X5_08U[] = {{6, 16, 4, 0, 0x2222}, {6, 16, 2, 1, 0x0}, {25, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData156_HT_GENERIC_5X5_08U[] = {{8, 16, 4, 0, 0x2222}, {8, 16, 2, 1, 0x0}, {25, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData157_HT_GENERIC_5X5_08U[] = {{10, 16, 4, 0, 0x2222}, {10, 16, 2, 1, 0x0}, {25, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData158_HT_GENERIC_5X5_08U[] = {{12, 16, 4, 0, 0x2222}, {12, 16, 2, 1, 0x0}, {25, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData159_HT_GENERIC_5X5_08U[] = {{14, 16, 4, 0, 0x2222}, {14, 16, 2, 1, 0x0}, {25, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData160_HT_GENERIC_5X5_08U[] = {{16, 16, 4, 0, 0x2222}, {16, 16, 2, 1, 0x0}, {25, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData161_HT_GENERIC_5X5_08U[] = {{20, 16, 4, 0, 0x2222}, {20, 16, 2, 1, 0x0}, {25, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData162_HT_GENERIC_5X5_08U[] = {{24, 16, 4, 0, 0x2222}, {24, 16, 2, 1, 0x0}, {25, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData163_HT_GENERIC_5X5_08U[] = {{28, 16, 4, 0, 0x2222}, {28, 16, 2, 1, 0x0}, {25, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData164_HT_GENERIC_5X5_08U[] = {{32, 16, 4, 0, 0x2222}, {32, 16, 2, 1, 0x0}, {25, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData165_HT_GENERIC_5X5_08U[] = {{2, 18, 4, 0, 0x2222}, {2, 18, 2, 1, 0x0}, {25, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData166_HT_GENERIC_5X5_08U[] = {{4, 18, 4, 0, 0x2222}, {4, 18, 2, 1, 0x0}, {25, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData167_HT_GENERIC_5X5_08U[] = {{6, 18, 4, 0, 0x2222}, {6, 18, 2, 1, 0x0}, {25, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData168_HT_GENERIC_5X5_08U[] = {{8, 18, 4, 0, 0x2222}, {8, 18, 2, 1, 0x0}, {25, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData169_HT_GENERIC_5X5_08U[] = {{10, 18, 4, 0, 0x2222}, {10, 18, 2, 1, 0x0}, {25, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData170_HT_GENERIC_5X5_08U[] = {{12, 18, 4, 0, 0x2222}, {12, 18, 2, 1, 0x0}, {25, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData171_HT_GENERIC_5X5_08U[] = {{14, 18, 4, 0, 0x2222}, {14, 18, 2, 1, 0x0}, {25, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData172_HT_GENERIC_5X5_08U[] = {{16, 18, 4, 0, 0x2222}, {16, 18, 2, 1, 0x0}, {25, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData173_HT_GENERIC_5X5_08U[] = {{20, 18, 4, 0, 0x2222}, {20, 18, 2, 1, 0x0}, {25, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData174_HT_GENERIC_5X5_08U[] = {{24, 18, 4, 0, 0x2222}, {24, 18, 2, 1, 0x0}, {25, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData175_HT_GENERIC_5X5_08U[] = {{28, 18, 4, 0, 0x2222}, {28, 18, 2, 1, 0x0}, {25, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData176_HT_GENERIC_5X5_08U[] = {{2, 20, 4, 0, 0x2222}, {2, 20, 2, 1, 0x0}, {25, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData177_HT_GENERIC_5X5_08U[] = {{4, 20, 4, 0, 0x2222}, {4, 20, 2, 1, 0x0}, {25, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData178_HT_GENERIC_5X5_08U[] = {{6, 20, 4, 0, 0x2222}, {6, 20, 2, 1, 0x0}, {25, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData179_HT_GENERIC_5X5_08U[] = {{8, 20, 4, 0, 0x2222}, {8, 20, 2, 1, 0x0}, {25, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData180_HT_GENERIC_5X5_08U[] = {{10, 20, 4, 0, 0x2222}, {10, 20, 2, 1, 0x0}, {25, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData181_HT_GENERIC_5X5_08U[] = {{12, 20, 4, 0, 0x2222}, {12, 20, 2, 1, 0x0}, {25, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData182_HT_GENERIC_5X5_08U[] = {{14, 20, 4, 0, 0x2222}, {14, 20, 2, 1, 0x0}, {25, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData183_HT_GENERIC_5X5_08U[] = {{16, 20, 4, 0, 0x2222}, {16, 20, 2, 1, 0x0}, {25, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData184_HT_GENERIC_5X5_08U[] = {{20, 20, 4, 0, 0x2222}, {20, 20, 2, 1, 0x0}, {25, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData185_HT_GENERIC_5X5_08U[] = {{24, 20, 4, 0, 0x2222}, {24, 20, 2, 1, 0x0}, {25, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData186_HT_GENERIC_5X5_08U[] = {{28, 20, 4, 0, 0x2222}, {28, 20, 2, 1, 0x0}, {25, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData187_HT_GENERIC_5X5_08U[] = {{2, 22, 4, 0, 0x2222}, {2, 22, 2, 1, 0x0}, {25, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData188_HT_GENERIC_5X5_08U[] = {{4, 22, 4, 0, 0x2222}, {4, 22, 2, 1, 0x0}, {25, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData189_HT_GENERIC_5X5_08U[] = {{6, 22, 4, 0, 0x2222}, {6, 22, 2, 1, 0x0}, {25, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData190_HT_GENERIC_5X5_08U[] = {{8, 22, 4, 0, 0x2222}, {8, 22, 2, 1, 0x0}, {25, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData191_HT_GENERIC_5X5_08U[] = {{10, 22, 4, 0, 0x2222}, {10, 22, 2, 1, 0x0}, {25, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData192_HT_GENERIC_5X5_08U[] = {{12, 22, 4, 0, 0x2222}, {12, 22, 2, 1, 0x0}, {25, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData193_HT_GENERIC_5X5_08U[] = {{14, 22, 4, 0, 0x2222}, {14, 22, 2, 1, 0x0}, {25, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData194_HT_GENERIC_5X5_08U[] = {{16, 22, 4, 0, 0x2222}, {16, 22, 2, 1, 0x0}, {25, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData195_HT_GENERIC_5X5_08U[] = {{20, 22, 4, 0, 0x2222}, {20, 22, 2, 1, 0x0}, {25, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData196_HT_GENERIC_5X5_08U[] = {{24, 22, 4, 0, 0x2222}, {24, 22, 2, 1, 0x0}, {25, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData197_HT_GENERIC_5X5_08U[] = {{2, 24, 4, 0, 0x2222}, {2, 24, 2, 1, 0x0}, {25, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData198_HT_GENERIC_5X5_08U[] = {{4, 24, 4, 0, 0x2222}, {4, 24, 2, 1, 0x0}, {25, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData199_HT_GENERIC_5X5_08U[] = {{6, 24, 4, 0, 0x2222}, {6, 24, 2, 1, 0x0}, {25, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData200_HT_GENERIC_5X5_08U[] = {{8, 24, 4, 0, 0x2222}, {8, 24, 2, 1, 0x0}, {25, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData201_HT_GENERIC_5X5_08U[] = {{10, 24, 4, 0, 0x2222}, {10, 24, 2, 1, 0x0}, {25, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData202_HT_GENERIC_5X5_08U[] = {{12, 24, 4, 0, 0x2222}, {12, 24, 2, 1, 0x0}, {25, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData203_HT_GENERIC_5X5_08U[] = {{14, 24, 4, 0, 0x2222}, {14, 24, 2, 1, 0x0}, {25, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData204_HT_GENERIC_5X5_08U[] = {{16, 24, 4, 0, 0x2222}, {16, 24, 2, 1, 0x0}, {25, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData205_HT_GENERIC_5X5_08U[] = {{20, 24, 4, 0, 0x2222}, {20, 24, 2, 1, 0x0}, {25, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData206_HT_GENERIC_5X5_08U[] = {{2, 26, 4, 0, 0x2222}, {2, 26, 2, 1, 0x0}, {25, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData207_HT_GENERIC_5X5_08U[] = {{4, 26, 4, 0, 0x2222}, {4, 26, 2, 1, 0x0}, {25, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData208_HT_GENERIC_5X5_08U[] = {{6, 26, 4, 0, 0x2222}, {6, 26, 2, 1, 0x0}, {25, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData209_HT_GENERIC_5X5_08U[] = {{8, 26, 4, 0, 0x2222}, {8, 26, 2, 1, 0x0}, {25, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData210_HT_GENERIC_5X5_08U[] = {{10, 26, 4, 0, 0x2222}, {10, 26, 2, 1, 0x0}, {25, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData211_HT_GENERIC_5X5_08U[] = {{12, 26, 4, 0, 0x2222}, {12, 26, 2, 1, 0x0}, {25, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData212_HT_GENERIC_5X5_08U[] = {{14, 26, 4, 0, 0x2222}, {14, 26, 2, 1, 0x0}, {25, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData213_HT_GENERIC_5X5_08U[] = {{16, 26, 4, 0, 0x2222}, {16, 26, 2, 1, 0x0}, {25, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData214_HT_GENERIC_5X5_08U[] = {{20, 26, 4, 0, 0x2222}, {20, 26, 2, 1, 0x0}, {25, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData215_HT_GENERIC_5X5_08U[] = {{2, 28, 4, 0, 0x2222}, {2, 28, 2, 1, 0x0}, {25, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData216_HT_GENERIC_5X5_08U[] = {{4, 28, 4, 0, 0x2222}, {4, 28, 2, 1, 0x0}, {25, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData217_HT_GENERIC_5X5_08U[] = {{6, 28, 4, 0, 0x2222}, {6, 28, 2, 1, 0x0}, {25, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData218_HT_GENERIC_5X5_08U[] = {{8, 28, 4, 0, 0x2222}, {8, 28, 2, 1, 0x0}, {25, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData219_HT_GENERIC_5X5_08U[] = {{10, 28, 4, 0, 0x2222}, {10, 28, 2, 1, 0x0}, {25, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData220_HT_GENERIC_5X5_08U[] = {{12, 28, 4, 0, 0x2222}, {12, 28, 2, 1, 0x0}, {25, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData221_HT_GENERIC_5X5_08U[] = {{14, 28, 4, 0, 0x2222}, {14, 28, 2, 1, 0x0}, {25, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData222_HT_GENERIC_5X5_08U[] = {{16, 28, 4, 0, 0x2222}, {16, 28, 2, 1, 0x0}, {25, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData223_HT_GENERIC_5X5_08U[] = {{2, 30, 4, 0, 0x2222}, {2, 30, 2, 1, 0x0}, {25, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData224_HT_GENERIC_5X5_08U[] = {{4, 30, 4, 0, 0x2222}, {4, 30, 2, 1, 0x0}, {25, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData225_HT_GENERIC_5X5_08U[] = {{6, 30, 4, 0, 0x2222}, {6, 30, 2, 1, 0x0}, {25, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData226_HT_GENERIC_5X5_08U[] = {{8, 30, 4, 0, 0x2222}, {8, 30, 2, 1, 0x0}, {25, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData227_HT_GENERIC_5X5_08U[] = {{10, 30, 4, 0, 0x2222}, {10, 30, 2, 1, 0x0}, {25, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData228_HT_GENERIC_5X5_08U[] = {{12, 30, 4, 0, 0x2222}, {12, 30, 2, 1, 0x0}, {25, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData229_HT_GENERIC_5X5_08U[] = {{14, 30, 4, 0, 0x2222}, {14, 30, 2, 1, 0x0}, {25, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData230_HT_GENERIC_5X5_08U[] = {{16, 30, 4, 0, 0x2222}, {16, 30, 2, 1, 0x0}, {25, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData231_HT_GENERIC_5X5_08U[] = {{2, 32, 4, 0, 0x2222}, {2, 32, 2, 1, 0x0}, {25, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData232_HT_GENERIC_5X5_08U[] = {{4, 32, 4, 0, 0x2222}, {4, 32, 2, 1, 0x0}, {25, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData233_HT_GENERIC_5X5_08U[] = {{6, 32, 4, 0, 0x2222}, {6, 32, 2, 1, 0x0}, {25, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData234_HT_GENERIC_5X5_08U[] = {{8, 32, 4, 0, 0x2222}, {8, 32, 2, 1, 0x0}, {25, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData235_HT_GENERIC_5X5_08U[] = {{10, 32, 4, 0, 0x2222}, {10, 32, 2, 1, 0x0}, {25, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData236_HT_GENERIC_5X5_08U[] = {{12, 32, 4, 0, 0x2222}, {12, 32, 2, 1, 0x0}, {25, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData237_HT_GENERIC_5X5_08U[] = {{14, 32, 4, 0, 0x2222}, {14, 32, 2, 1, 0x0}, {25, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData238_HT_GENERIC_5X5_08U[] = {{16, 32, 4, 0, 0x2222}, {16, 32, 2, 1, 0x0}, {25, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};

static acf_scenario_kernel_data gScenarioKernelData0_HT_GENERIC_5X5_08U[] = {{2}};
static acf_scenario_kernel_data gScenarioKernelData1_HT_GENERIC_5X5_08U[] = {{2}};
static acf_scenario_kernel_data gScenarioKernelData2_HT_GENERIC_5X5_08U[] = {{2}};
static acf_scenario_kernel_data gScenarioKernelData3_HT_GENERIC_5X5_08U[] = {{2}};
static acf_scenario_kernel_data gScenarioKernelData4_HT_GENERIC_5X5_08U[] = {{2}};
static acf_scenario_kernel_data gScenarioKernelData5_HT_GENERIC_5X5_08U[] = {{2}};
static acf_scenario_kernel_data gScenarioKernelData6_HT_GENERIC_5X5_08U[] = {{2}};
static acf_scenario_kernel_data gScenarioKernelData7_HT_GENERIC_5X5_08U[] = {{2}};
static acf_scenario_kernel_data gScenarioKernelData8_HT_GENERIC_5X5_08U[] = {{2}};
static acf_scenario_kernel_data gScenarioKernelData9_HT_GENERIC_5X5_08U[] = {{2}};
static acf_scenario_kernel_data gScenarioKernelData10_HT_GENERIC_5X5_08U[] = {{2}};
static acf_scenario_kernel_data gScenarioKernelData11_HT_GENERIC_5X5_08U[] = {{2}};
static acf_scenario_kernel_data gScenarioKernelData12_HT_GENERIC_5X5_08U[] = {{2}};
static acf_scenario_kernel_data gScenarioKernelData13_HT_GENERIC_5X5_08U[] = {{2}};
static acf_scenario_kernel_data gScenarioKernelData14_HT_GENERIC_5X5_08U[] = {{2}};
static acf_scenario_kernel_data gScenarioKernelData15_HT_GENERIC_5X5_08U[] = {{2}};
static acf_scenario_kernel_data gScenarioKernelData16_HT_GENERIC_5X5_08U[] = {{2}};
static acf_scenario_kernel_data gScenarioKernelData17_HT_GENERIC_5X5_08U[] = {{2}};
static acf_scenario_kernel_data gScenarioKernelData18_HT_GENERIC_5X5_08U[] = {{2}};
static acf_scenario_kernel_data gScenarioKernelData19_HT_GENERIC_5X5_08U[] = {{2}};
static acf_scenario_kernel_data gScenarioKernelData20_HT_GENERIC_5X5_08U[] = {{2}};
static acf_scenario_kernel_data gScenarioKernelData21_HT_GENERIC_5X5_08U[] = {{2}};
static acf_scenario_kernel_data gScenarioKernelData22_HT_GENERIC_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData23_HT_GENERIC_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData24_HT_GENERIC_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData25_HT_GENERIC_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData26_HT_GENERIC_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData27_HT_GENERIC_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData28_HT_GENERIC_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData29_HT_GENERIC_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData30_HT_GENERIC_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData31_HT_GENERIC_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData32_HT_GENERIC_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData33_HT_GENERIC_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData34_HT_GENERIC_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData35_HT_GENERIC_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData36_HT_GENERIC_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData37_HT_GENERIC_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData38_HT_GENERIC_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData39_HT_GENERIC_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData40_HT_GENERIC_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData41_HT_GENERIC_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData42_HT_GENERIC_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData43_HT_GENERIC_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData44_HT_GENERIC_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData45_HT_GENERIC_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData46_HT_GENERIC_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData47_HT_GENERIC_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData48_HT_GENERIC_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData49_HT_GENERIC_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData50_HT_GENERIC_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData51_HT_GENERIC_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData52_HT_GENERIC_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData53_HT_GENERIC_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData54_HT_GENERIC_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData55_HT_GENERIC_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData56_HT_GENERIC_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData57_HT_GENERIC_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData58_HT_GENERIC_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData59_HT_GENERIC_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData60_HT_GENERIC_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData61_HT_GENERIC_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData62_HT_GENERIC_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData63_HT_GENERIC_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData64_HT_GENERIC_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData65_HT_GENERIC_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData66_HT_GENERIC_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData67_HT_GENERIC_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData68_HT_GENERIC_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData69_HT_GENERIC_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData70_HT_GENERIC_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData71_HT_GENERIC_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData72_HT_GENERIC_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData73_HT_GENERIC_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData74_HT_GENERIC_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData75_HT_GENERIC_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData76_HT_GENERIC_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData77_HT_GENERIC_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData78_HT_GENERIC_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData79_HT_GENERIC_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData80_HT_GENERIC_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData81_HT_GENERIC_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData82_HT_GENERIC_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData83_HT_GENERIC_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData84_HT_GENERIC_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData85_HT_GENERIC_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData86_HT_GENERIC_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData87_HT_GENERIC_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData88_HT_GENERIC_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData89_HT_GENERIC_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData90_HT_GENERIC_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData91_HT_GENERIC_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData92_HT_GENERIC_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData93_HT_GENERIC_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData94_HT_GENERIC_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData95_HT_GENERIC_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData96_HT_GENERIC_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData97_HT_GENERIC_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData98_HT_GENERIC_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData99_HT_GENERIC_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData100_HT_GENERIC_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData101_HT_GENERIC_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData102_HT_GENERIC_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData103_HT_GENERIC_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData104_HT_GENERIC_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData105_HT_GENERIC_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData106_HT_GENERIC_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData107_HT_GENERIC_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData108_HT_GENERIC_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData109_HT_GENERIC_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData110_HT_GENERIC_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData111_HT_GENERIC_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData112_HT_GENERIC_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData113_HT_GENERIC_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData114_HT_GENERIC_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData115_HT_GENERIC_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData116_HT_GENERIC_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData117_HT_GENERIC_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData118_HT_GENERIC_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData119_HT_GENERIC_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData120_HT_GENERIC_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData121_HT_GENERIC_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData122_HT_GENERIC_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData123_HT_GENERIC_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData124_HT_GENERIC_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData125_HT_GENERIC_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData126_HT_GENERIC_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData127_HT_GENERIC_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData128_HT_GENERIC_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData129_HT_GENERIC_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData130_HT_GENERIC_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData131_HT_GENERIC_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData132_HT_GENERIC_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData133_HT_GENERIC_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData134_HT_GENERIC_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData135_HT_GENERIC_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData136_HT_GENERIC_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData137_HT_GENERIC_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData138_HT_GENERIC_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData139_HT_GENERIC_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData140_HT_GENERIC_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData141_HT_GENERIC_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData142_HT_GENERIC_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData143_HT_GENERIC_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData144_HT_GENERIC_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData145_HT_GENERIC_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData146_HT_GENERIC_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData147_HT_GENERIC_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData148_HT_GENERIC_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData149_HT_GENERIC_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData150_HT_GENERIC_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData151_HT_GENERIC_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData152_HT_GENERIC_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData153_HT_GENERIC_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData154_HT_GENERIC_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData155_HT_GENERIC_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData156_HT_GENERIC_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData157_HT_GENERIC_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData158_HT_GENERIC_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData159_HT_GENERIC_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData160_HT_GENERIC_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData161_HT_GENERIC_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData162_HT_GENERIC_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData163_HT_GENERIC_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData164_HT_GENERIC_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData165_HT_GENERIC_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData166_HT_GENERIC_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData167_HT_GENERIC_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData168_HT_GENERIC_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData169_HT_GENERIC_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData170_HT_GENERIC_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData171_HT_GENERIC_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData172_HT_GENERIC_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData173_HT_GENERIC_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData174_HT_GENERIC_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData175_HT_GENERIC_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData176_HT_GENERIC_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData177_HT_GENERIC_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData178_HT_GENERIC_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData179_HT_GENERIC_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData180_HT_GENERIC_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData181_HT_GENERIC_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData182_HT_GENERIC_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData183_HT_GENERIC_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData184_HT_GENERIC_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData185_HT_GENERIC_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData186_HT_GENERIC_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData187_HT_GENERIC_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData188_HT_GENERIC_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData189_HT_GENERIC_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData190_HT_GENERIC_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData191_HT_GENERIC_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData192_HT_GENERIC_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData193_HT_GENERIC_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData194_HT_GENERIC_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData195_HT_GENERIC_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData196_HT_GENERIC_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData197_HT_GENERIC_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData198_HT_GENERIC_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData199_HT_GENERIC_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData200_HT_GENERIC_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData201_HT_GENERIC_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData202_HT_GENERIC_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData203_HT_GENERIC_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData204_HT_GENERIC_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData205_HT_GENERIC_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData206_HT_GENERIC_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData207_HT_GENERIC_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData208_HT_GENERIC_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData209_HT_GENERIC_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData210_HT_GENERIC_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData211_HT_GENERIC_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData212_HT_GENERIC_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData213_HT_GENERIC_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData214_HT_GENERIC_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData215_HT_GENERIC_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData216_HT_GENERIC_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData217_HT_GENERIC_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData218_HT_GENERIC_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData219_HT_GENERIC_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData220_HT_GENERIC_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData221_HT_GENERIC_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData222_HT_GENERIC_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData223_HT_GENERIC_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData224_HT_GENERIC_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData225_HT_GENERIC_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData226_HT_GENERIC_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData227_HT_GENERIC_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData228_HT_GENERIC_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData229_HT_GENERIC_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData230_HT_GENERIC_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData231_HT_GENERIC_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData232_HT_GENERIC_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData233_HT_GENERIC_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData234_HT_GENERIC_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData235_HT_GENERIC_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData236_HT_GENERIC_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData237_HT_GENERIC_5X5_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData238_HT_GENERIC_5X5_08U[] = {{1}};

static acf_scenario gScenarioArray_HT_GENERIC_5X5_08U[] = {
{1, 1, 72, 40, 2, gScenarioBufferData0_HT_GENERIC_5X5_08U, 40, gScenarioKernelData0_HT_GENERIC_5X5_08U, 2},
{2, 1, 96, 40, 2, gScenarioBufferData1_HT_GENERIC_5X5_08U, 40, gScenarioKernelData1_HT_GENERIC_5X5_08U, 2},
{3, 1, 124, 40, 2, gScenarioBufferData2_HT_GENERIC_5X5_08U, 40, gScenarioKernelData2_HT_GENERIC_5X5_08U, 2},
{4, 1, 148, 40, 2, gScenarioBufferData3_HT_GENERIC_5X5_08U, 40, gScenarioKernelData3_HT_GENERIC_5X5_08U, 2},
{5, 1, 176, 40, 2, gScenarioBufferData4_HT_GENERIC_5X5_08U, 40, gScenarioKernelData4_HT_GENERIC_5X5_08U, 2},
{6, 1, 200, 40, 2, gScenarioBufferData5_HT_GENERIC_5X5_08U, 40, gScenarioKernelData5_HT_GENERIC_5X5_08U, 2},
{7, 1, 228, 40, 2, gScenarioBufferData6_HT_GENERIC_5X5_08U, 40, gScenarioKernelData6_HT_GENERIC_5X5_08U, 2},
{8, 1, 252, 40, 2, gScenarioBufferData7_HT_GENERIC_5X5_08U, 40, gScenarioKernelData7_HT_GENERIC_5X5_08U, 2},
{10, 1, 304, 40, 2, gScenarioBufferData8_HT_GENERIC_5X5_08U, 40, gScenarioKernelData8_HT_GENERIC_5X5_08U, 2},
{12, 1, 356, 40, 2, gScenarioBufferData9_HT_GENERIC_5X5_08U, 40, gScenarioKernelData9_HT_GENERIC_5X5_08U, 2},
{14, 1, 408, 40, 2, gScenarioBufferData10_HT_GENERIC_5X5_08U, 40, gScenarioKernelData10_HT_GENERIC_5X5_08U, 2},
{16, 1, 460, 40, 2, gScenarioBufferData11_HT_GENERIC_5X5_08U, 40, gScenarioKernelData11_HT_GENERIC_5X5_08U, 2},
{18, 1, 512, 40, 2, gScenarioBufferData12_HT_GENERIC_5X5_08U, 40, gScenarioKernelData12_HT_GENERIC_5X5_08U, 2},
{20, 1, 564, 40, 2, gScenarioBufferData13_HT_GENERIC_5X5_08U, 40, gScenarioKernelData13_HT_GENERIC_5X5_08U, 2},
{22, 1, 616, 40, 2, gScenarioBufferData14_HT_GENERIC_5X5_08U, 40, gScenarioKernelData14_HT_GENERIC_5X5_08U, 2},
{24, 1, 668, 40, 2, gScenarioBufferData15_HT_GENERIC_5X5_08U, 40, gScenarioKernelData15_HT_GENERIC_5X5_08U, 2},
{26, 1, 720, 40, 2, gScenarioBufferData16_HT_GENERIC_5X5_08U, 40, gScenarioKernelData16_HT_GENERIC_5X5_08U, 2},
{28, 1, 772, 40, 2, gScenarioBufferData17_HT_GENERIC_5X5_08U, 40, gScenarioKernelData17_HT_GENERIC_5X5_08U, 2},
{30, 1, 824, 40, 2, gScenarioBufferData18_HT_GENERIC_5X5_08U, 40, gScenarioKernelData18_HT_GENERIC_5X5_08U, 2},
{32, 1, 876, 40, 2, gScenarioBufferData19_HT_GENERIC_5X5_08U, 40, gScenarioKernelData19_HT_GENERIC_5X5_08U, 2},
{48, 1, 1292, 40, 2, gScenarioBufferData20_HT_GENERIC_5X5_08U, 40, gScenarioKernelData20_HT_GENERIC_5X5_08U, 2},
{64, 1, 1708, 40, 2, gScenarioBufferData21_HT_GENERIC_5X5_08U, 40, gScenarioKernelData21_HT_GENERIC_5X5_08U, 2},
{1, 2, 80, 40, 1, gScenarioBufferData22_HT_GENERIC_5X5_08U, 40, gScenarioKernelData22_HT_GENERIC_5X5_08U, 2},
{2, 2, 112, 40, 1, gScenarioBufferData23_HT_GENERIC_5X5_08U, 40, gScenarioKernelData23_HT_GENERIC_5X5_08U, 2},
{3, 2, 144, 40, 1, gScenarioBufferData24_HT_GENERIC_5X5_08U, 40, gScenarioKernelData24_HT_GENERIC_5X5_08U, 2},
{4, 2, 176, 40, 1, gScenarioBufferData25_HT_GENERIC_5X5_08U, 40, gScenarioKernelData25_HT_GENERIC_5X5_08U, 2},
{5, 2, 208, 40, 1, gScenarioBufferData26_HT_GENERIC_5X5_08U, 40, gScenarioKernelData26_HT_GENERIC_5X5_08U, 2},
{6, 2, 240, 40, 1, gScenarioBufferData27_HT_GENERIC_5X5_08U, 40, gScenarioKernelData27_HT_GENERIC_5X5_08U, 2},
{7, 2, 272, 40, 1, gScenarioBufferData28_HT_GENERIC_5X5_08U, 40, gScenarioKernelData28_HT_GENERIC_5X5_08U, 2},
{8, 2, 304, 40, 1, gScenarioBufferData29_HT_GENERIC_5X5_08U, 40, gScenarioKernelData29_HT_GENERIC_5X5_08U, 2},
{10, 2, 368, 40, 1, gScenarioBufferData30_HT_GENERIC_5X5_08U, 40, gScenarioKernelData30_HT_GENERIC_5X5_08U, 2},
{12, 2, 432, 40, 1, gScenarioBufferData31_HT_GENERIC_5X5_08U, 40, gScenarioKernelData31_HT_GENERIC_5X5_08U, 2},
{14, 2, 496, 40, 1, gScenarioBufferData32_HT_GENERIC_5X5_08U, 40, gScenarioKernelData32_HT_GENERIC_5X5_08U, 2},
{16, 2, 560, 40, 1, gScenarioBufferData33_HT_GENERIC_5X5_08U, 40, gScenarioKernelData33_HT_GENERIC_5X5_08U, 2},
{18, 2, 624, 40, 1, gScenarioBufferData34_HT_GENERIC_5X5_08U, 40, gScenarioKernelData34_HT_GENERIC_5X5_08U, 2},
{20, 2, 688, 40, 1, gScenarioBufferData35_HT_GENERIC_5X5_08U, 40, gScenarioKernelData35_HT_GENERIC_5X5_08U, 2},
{22, 2, 752, 40, 1, gScenarioBufferData36_HT_GENERIC_5X5_08U, 40, gScenarioKernelData36_HT_GENERIC_5X5_08U, 2},
{24, 2, 816, 40, 1, gScenarioBufferData37_HT_GENERIC_5X5_08U, 40, gScenarioKernelData37_HT_GENERIC_5X5_08U, 2},
{26, 2, 880, 40, 1, gScenarioBufferData38_HT_GENERIC_5X5_08U, 40, gScenarioKernelData38_HT_GENERIC_5X5_08U, 2},
{28, 2, 944, 40, 1, gScenarioBufferData39_HT_GENERIC_5X5_08U, 40, gScenarioKernelData39_HT_GENERIC_5X5_08U, 2},
{30, 2, 1008, 40, 1, gScenarioBufferData40_HT_GENERIC_5X5_08U, 40, gScenarioKernelData40_HT_GENERIC_5X5_08U, 2},
{32, 2, 1072, 40, 1, gScenarioBufferData41_HT_GENERIC_5X5_08U, 40, gScenarioKernelData41_HT_GENERIC_5X5_08U, 2},
{48, 2, 1584, 40, 1, gScenarioBufferData42_HT_GENERIC_5X5_08U, 40, gScenarioKernelData42_HT_GENERIC_5X5_08U, 2},
{64, 2, 2096, 40, 1, gScenarioBufferData43_HT_GENERIC_5X5_08U, 40, gScenarioKernelData43_HT_GENERIC_5X5_08U, 2},
{1, 4, 136, 40, 1, gScenarioBufferData44_HT_GENERIC_5X5_08U, 40, gScenarioKernelData44_HT_GENERIC_5X5_08U, 2},
{2, 4, 192, 40, 1, gScenarioBufferData45_HT_GENERIC_5X5_08U, 40, gScenarioKernelData45_HT_GENERIC_5X5_08U, 2},
{3, 4, 248, 40, 1, gScenarioBufferData46_HT_GENERIC_5X5_08U, 40, gScenarioKernelData46_HT_GENERIC_5X5_08U, 2},
{4, 4, 304, 40, 1, gScenarioBufferData47_HT_GENERIC_5X5_08U, 40, gScenarioKernelData47_HT_GENERIC_5X5_08U, 2},
{5, 4, 360, 40, 1, gScenarioBufferData48_HT_GENERIC_5X5_08U, 40, gScenarioKernelData48_HT_GENERIC_5X5_08U, 2},
{6, 4, 416, 40, 1, gScenarioBufferData49_HT_GENERIC_5X5_08U, 40, gScenarioKernelData49_HT_GENERIC_5X5_08U, 2},
{7, 4, 472, 40, 1, gScenarioBufferData50_HT_GENERIC_5X5_08U, 40, gScenarioKernelData50_HT_GENERIC_5X5_08U, 2},
{8, 4, 528, 40, 1, gScenarioBufferData51_HT_GENERIC_5X5_08U, 40, gScenarioKernelData51_HT_GENERIC_5X5_08U, 2},
{10, 4, 640, 40, 1, gScenarioBufferData52_HT_GENERIC_5X5_08U, 40, gScenarioKernelData52_HT_GENERIC_5X5_08U, 2},
{12, 4, 752, 40, 1, gScenarioBufferData53_HT_GENERIC_5X5_08U, 40, gScenarioKernelData53_HT_GENERIC_5X5_08U, 2},
{14, 4, 864, 40, 1, gScenarioBufferData54_HT_GENERIC_5X5_08U, 40, gScenarioKernelData54_HT_GENERIC_5X5_08U, 2},
{16, 4, 976, 40, 1, gScenarioBufferData55_HT_GENERIC_5X5_08U, 40, gScenarioKernelData55_HT_GENERIC_5X5_08U, 2},
{18, 4, 1088, 40, 1, gScenarioBufferData56_HT_GENERIC_5X5_08U, 40, gScenarioKernelData56_HT_GENERIC_5X5_08U, 2},
{20, 4, 1200, 40, 1, gScenarioBufferData57_HT_GENERIC_5X5_08U, 40, gScenarioKernelData57_HT_GENERIC_5X5_08U, 2},
{22, 4, 1312, 40, 1, gScenarioBufferData58_HT_GENERIC_5X5_08U, 40, gScenarioKernelData58_HT_GENERIC_5X5_08U, 2},
{24, 4, 1424, 40, 1, gScenarioBufferData59_HT_GENERIC_5X5_08U, 40, gScenarioKernelData59_HT_GENERIC_5X5_08U, 2},
{26, 4, 1536, 40, 1, gScenarioBufferData60_HT_GENERIC_5X5_08U, 40, gScenarioKernelData60_HT_GENERIC_5X5_08U, 2},
{28, 4, 1648, 40, 1, gScenarioBufferData61_HT_GENERIC_5X5_08U, 40, gScenarioKernelData61_HT_GENERIC_5X5_08U, 2},
{30, 4, 1760, 40, 1, gScenarioBufferData62_HT_GENERIC_5X5_08U, 40, gScenarioKernelData62_HT_GENERIC_5X5_08U, 2},
{32, 4, 1872, 40, 1, gScenarioBufferData63_HT_GENERIC_5X5_08U, 40, gScenarioKernelData63_HT_GENERIC_5X5_08U, 2},
{48, 4, 2768, 40, 1, gScenarioBufferData64_HT_GENERIC_5X5_08U, 40, gScenarioKernelData64_HT_GENERIC_5X5_08U, 2},
{64, 4, 3664, 40, 1, gScenarioBufferData65_HT_GENERIC_5X5_08U, 40, gScenarioKernelData65_HT_GENERIC_5X5_08U, 2},
{1, 6, 192, 40, 1, gScenarioBufferData66_HT_GENERIC_5X5_08U, 40, gScenarioKernelData66_HT_GENERIC_5X5_08U, 2},
{2, 6, 272, 40, 1, gScenarioBufferData67_HT_GENERIC_5X5_08U, 40, gScenarioKernelData67_HT_GENERIC_5X5_08U, 2},
{3, 6, 352, 40, 1, gScenarioBufferData68_HT_GENERIC_5X5_08U, 40, gScenarioKernelData68_HT_GENERIC_5X5_08U, 2},
{4, 6, 432, 40, 1, gScenarioBufferData69_HT_GENERIC_5X5_08U, 40, gScenarioKernelData69_HT_GENERIC_5X5_08U, 2},
{5, 6, 512, 40, 1, gScenarioBufferData70_HT_GENERIC_5X5_08U, 40, gScenarioKernelData70_HT_GENERIC_5X5_08U, 2},
{6, 6, 592, 40, 1, gScenarioBufferData71_HT_GENERIC_5X5_08U, 40, gScenarioKernelData71_HT_GENERIC_5X5_08U, 2},
{7, 6, 672, 40, 1, gScenarioBufferData72_HT_GENERIC_5X5_08U, 40, gScenarioKernelData72_HT_GENERIC_5X5_08U, 2},
{8, 6, 752, 40, 1, gScenarioBufferData73_HT_GENERIC_5X5_08U, 40, gScenarioKernelData73_HT_GENERIC_5X5_08U, 2},
{10, 6, 912, 40, 1, gScenarioBufferData74_HT_GENERIC_5X5_08U, 40, gScenarioKernelData74_HT_GENERIC_5X5_08U, 2},
{12, 6, 1072, 40, 1, gScenarioBufferData75_HT_GENERIC_5X5_08U, 40, gScenarioKernelData75_HT_GENERIC_5X5_08U, 2},
{14, 6, 1232, 40, 1, gScenarioBufferData76_HT_GENERIC_5X5_08U, 40, gScenarioKernelData76_HT_GENERIC_5X5_08U, 2},
{16, 6, 1392, 40, 1, gScenarioBufferData77_HT_GENERIC_5X5_08U, 40, gScenarioKernelData77_HT_GENERIC_5X5_08U, 2},
{18, 6, 1552, 40, 1, gScenarioBufferData78_HT_GENERIC_5X5_08U, 40, gScenarioKernelData78_HT_GENERIC_5X5_08U, 2},
{20, 6, 1712, 40, 1, gScenarioBufferData79_HT_GENERIC_5X5_08U, 40, gScenarioKernelData79_HT_GENERIC_5X5_08U, 2},
{22, 6, 1872, 40, 1, gScenarioBufferData80_HT_GENERIC_5X5_08U, 40, gScenarioKernelData80_HT_GENERIC_5X5_08U, 2},
{24, 6, 2032, 40, 1, gScenarioBufferData81_HT_GENERIC_5X5_08U, 40, gScenarioKernelData81_HT_GENERIC_5X5_08U, 2},
{26, 6, 2192, 40, 1, gScenarioBufferData82_HT_GENERIC_5X5_08U, 40, gScenarioKernelData82_HT_GENERIC_5X5_08U, 2},
{28, 6, 2352, 40, 1, gScenarioBufferData83_HT_GENERIC_5X5_08U, 40, gScenarioKernelData83_HT_GENERIC_5X5_08U, 2},
{30, 6, 2512, 40, 1, gScenarioBufferData84_HT_GENERIC_5X5_08U, 40, gScenarioKernelData84_HT_GENERIC_5X5_08U, 2},
{32, 6, 2672, 40, 1, gScenarioBufferData85_HT_GENERIC_5X5_08U, 40, gScenarioKernelData85_HT_GENERIC_5X5_08U, 2},
{1, 8, 248, 40, 1, gScenarioBufferData86_HT_GENERIC_5X5_08U, 40, gScenarioKernelData86_HT_GENERIC_5X5_08U, 2},
{2, 8, 352, 40, 1, gScenarioBufferData87_HT_GENERIC_5X5_08U, 40, gScenarioKernelData87_HT_GENERIC_5X5_08U, 2},
{3, 8, 456, 40, 1, gScenarioBufferData88_HT_GENERIC_5X5_08U, 40, gScenarioKernelData88_HT_GENERIC_5X5_08U, 2},
{4, 8, 560, 40, 1, gScenarioBufferData89_HT_GENERIC_5X5_08U, 40, gScenarioKernelData89_HT_GENERIC_5X5_08U, 2},
{5, 8, 664, 40, 1, gScenarioBufferData90_HT_GENERIC_5X5_08U, 40, gScenarioKernelData90_HT_GENERIC_5X5_08U, 2},
{6, 8, 768, 40, 1, gScenarioBufferData91_HT_GENERIC_5X5_08U, 40, gScenarioKernelData91_HT_GENERIC_5X5_08U, 2},
{7, 8, 872, 40, 1, gScenarioBufferData92_HT_GENERIC_5X5_08U, 40, gScenarioKernelData92_HT_GENERIC_5X5_08U, 2},
{8, 8, 976, 40, 1, gScenarioBufferData93_HT_GENERIC_5X5_08U, 40, gScenarioKernelData93_HT_GENERIC_5X5_08U, 2},
{10, 8, 1184, 40, 1, gScenarioBufferData94_HT_GENERIC_5X5_08U, 40, gScenarioKernelData94_HT_GENERIC_5X5_08U, 2},
{12, 8, 1392, 40, 1, gScenarioBufferData95_HT_GENERIC_5X5_08U, 40, gScenarioKernelData95_HT_GENERIC_5X5_08U, 2},
{14, 8, 1600, 40, 1, gScenarioBufferData96_HT_GENERIC_5X5_08U, 40, gScenarioKernelData96_HT_GENERIC_5X5_08U, 2},
{16, 8, 1808, 40, 1, gScenarioBufferData97_HT_GENERIC_5X5_08U, 40, gScenarioKernelData97_HT_GENERIC_5X5_08U, 2},
{18, 8, 2016, 40, 1, gScenarioBufferData98_HT_GENERIC_5X5_08U, 40, gScenarioKernelData98_HT_GENERIC_5X5_08U, 2},
{20, 8, 2224, 40, 1, gScenarioBufferData99_HT_GENERIC_5X5_08U, 40, gScenarioKernelData99_HT_GENERIC_5X5_08U, 2},
{22, 8, 2432, 40, 1, gScenarioBufferData100_HT_GENERIC_5X5_08U, 40, gScenarioKernelData100_HT_GENERIC_5X5_08U, 2},
{24, 8, 2640, 40, 1, gScenarioBufferData101_HT_GENERIC_5X5_08U, 40, gScenarioKernelData101_HT_GENERIC_5X5_08U, 2},
{26, 8, 2848, 40, 1, gScenarioBufferData102_HT_GENERIC_5X5_08U, 40, gScenarioKernelData102_HT_GENERIC_5X5_08U, 2},
{28, 8, 3056, 40, 1, gScenarioBufferData103_HT_GENERIC_5X5_08U, 40, gScenarioKernelData103_HT_GENERIC_5X5_08U, 2},
{30, 8, 3264, 40, 1, gScenarioBufferData104_HT_GENERIC_5X5_08U, 40, gScenarioKernelData104_HT_GENERIC_5X5_08U, 2},
{32, 8, 3472, 40, 1, gScenarioBufferData105_HT_GENERIC_5X5_08U, 40, gScenarioKernelData105_HT_GENERIC_5X5_08U, 2},
{1, 10, 304, 40, 1, gScenarioBufferData106_HT_GENERIC_5X5_08U, 40, gScenarioKernelData106_HT_GENERIC_5X5_08U, 2},
{2, 10, 432, 40, 1, gScenarioBufferData107_HT_GENERIC_5X5_08U, 40, gScenarioKernelData107_HT_GENERIC_5X5_08U, 2},
{3, 10, 560, 40, 1, gScenarioBufferData108_HT_GENERIC_5X5_08U, 40, gScenarioKernelData108_HT_GENERIC_5X5_08U, 2},
{4, 10, 688, 40, 1, gScenarioBufferData109_HT_GENERIC_5X5_08U, 40, gScenarioKernelData109_HT_GENERIC_5X5_08U, 2},
{5, 10, 816, 40, 1, gScenarioBufferData110_HT_GENERIC_5X5_08U, 40, gScenarioKernelData110_HT_GENERIC_5X5_08U, 2},
{6, 10, 944, 40, 1, gScenarioBufferData111_HT_GENERIC_5X5_08U, 40, gScenarioKernelData111_HT_GENERIC_5X5_08U, 2},
{7, 10, 1072, 40, 1, gScenarioBufferData112_HT_GENERIC_5X5_08U, 40, gScenarioKernelData112_HT_GENERIC_5X5_08U, 2},
{8, 10, 1200, 40, 1, gScenarioBufferData113_HT_GENERIC_5X5_08U, 40, gScenarioKernelData113_HT_GENERIC_5X5_08U, 2},
{10, 10, 1456, 40, 1, gScenarioBufferData114_HT_GENERIC_5X5_08U, 40, gScenarioKernelData114_HT_GENERIC_5X5_08U, 2},
{12, 10, 1712, 40, 1, gScenarioBufferData115_HT_GENERIC_5X5_08U, 40, gScenarioKernelData115_HT_GENERIC_5X5_08U, 2},
{14, 10, 1968, 40, 1, gScenarioBufferData116_HT_GENERIC_5X5_08U, 40, gScenarioKernelData116_HT_GENERIC_5X5_08U, 2},
{16, 10, 2224, 40, 1, gScenarioBufferData117_HT_GENERIC_5X5_08U, 40, gScenarioKernelData117_HT_GENERIC_5X5_08U, 2},
{18, 10, 2480, 40, 1, gScenarioBufferData118_HT_GENERIC_5X5_08U, 40, gScenarioKernelData118_HT_GENERIC_5X5_08U, 2},
{20, 10, 2736, 40, 1, gScenarioBufferData119_HT_GENERIC_5X5_08U, 40, gScenarioKernelData119_HT_GENERIC_5X5_08U, 2},
{22, 10, 2992, 40, 1, gScenarioBufferData120_HT_GENERIC_5X5_08U, 40, gScenarioKernelData120_HT_GENERIC_5X5_08U, 2},
{24, 10, 3248, 40, 1, gScenarioBufferData121_HT_GENERIC_5X5_08U, 40, gScenarioKernelData121_HT_GENERIC_5X5_08U, 2},
{26, 10, 3504, 40, 1, gScenarioBufferData122_HT_GENERIC_5X5_08U, 40, gScenarioKernelData122_HT_GENERIC_5X5_08U, 2},
{28, 10, 3760, 40, 1, gScenarioBufferData123_HT_GENERIC_5X5_08U, 40, gScenarioKernelData123_HT_GENERIC_5X5_08U, 2},
{1, 12, 360, 40, 1, gScenarioBufferData124_HT_GENERIC_5X5_08U, 40, gScenarioKernelData124_HT_GENERIC_5X5_08U, 2},
{2, 12, 512, 40, 1, gScenarioBufferData125_HT_GENERIC_5X5_08U, 40, gScenarioKernelData125_HT_GENERIC_5X5_08U, 2},
{3, 12, 664, 40, 1, gScenarioBufferData126_HT_GENERIC_5X5_08U, 40, gScenarioKernelData126_HT_GENERIC_5X5_08U, 2},
{4, 12, 816, 40, 1, gScenarioBufferData127_HT_GENERIC_5X5_08U, 40, gScenarioKernelData127_HT_GENERIC_5X5_08U, 2},
{5, 12, 968, 40, 1, gScenarioBufferData128_HT_GENERIC_5X5_08U, 40, gScenarioKernelData128_HT_GENERIC_5X5_08U, 2},
{6, 12, 1120, 40, 1, gScenarioBufferData129_HT_GENERIC_5X5_08U, 40, gScenarioKernelData129_HT_GENERIC_5X5_08U, 2},
{7, 12, 1272, 40, 1, gScenarioBufferData130_HT_GENERIC_5X5_08U, 40, gScenarioKernelData130_HT_GENERIC_5X5_08U, 2},
{8, 12, 1424, 40, 1, gScenarioBufferData131_HT_GENERIC_5X5_08U, 40, gScenarioKernelData131_HT_GENERIC_5X5_08U, 2},
{10, 12, 1728, 40, 1, gScenarioBufferData132_HT_GENERIC_5X5_08U, 40, gScenarioKernelData132_HT_GENERIC_5X5_08U, 2},
{12, 12, 2032, 40, 1, gScenarioBufferData133_HT_GENERIC_5X5_08U, 40, gScenarioKernelData133_HT_GENERIC_5X5_08U, 2},
{14, 12, 2336, 40, 1, gScenarioBufferData134_HT_GENERIC_5X5_08U, 40, gScenarioKernelData134_HT_GENERIC_5X5_08U, 2},
{16, 12, 2640, 40, 1, gScenarioBufferData135_HT_GENERIC_5X5_08U, 40, gScenarioKernelData135_HT_GENERIC_5X5_08U, 2},
{18, 12, 2944, 40, 1, gScenarioBufferData136_HT_GENERIC_5X5_08U, 40, gScenarioKernelData136_HT_GENERIC_5X5_08U, 2},
{20, 12, 3248, 40, 1, gScenarioBufferData137_HT_GENERIC_5X5_08U, 40, gScenarioKernelData137_HT_GENERIC_5X5_08U, 2},
{22, 12, 3552, 40, 1, gScenarioBufferData138_HT_GENERIC_5X5_08U, 40, gScenarioKernelData138_HT_GENERIC_5X5_08U, 2},
{1, 14, 416, 40, 1, gScenarioBufferData139_HT_GENERIC_5X5_08U, 40, gScenarioKernelData139_HT_GENERIC_5X5_08U, 2},
{2, 14, 592, 40, 1, gScenarioBufferData140_HT_GENERIC_5X5_08U, 40, gScenarioKernelData140_HT_GENERIC_5X5_08U, 2},
{3, 14, 768, 40, 1, gScenarioBufferData141_HT_GENERIC_5X5_08U, 40, gScenarioKernelData141_HT_GENERIC_5X5_08U, 2},
{4, 14, 944, 40, 1, gScenarioBufferData142_HT_GENERIC_5X5_08U, 40, gScenarioKernelData142_HT_GENERIC_5X5_08U, 2},
{5, 14, 1120, 40, 1, gScenarioBufferData143_HT_GENERIC_5X5_08U, 40, gScenarioKernelData143_HT_GENERIC_5X5_08U, 2},
{6, 14, 1296, 40, 1, gScenarioBufferData144_HT_GENERIC_5X5_08U, 40, gScenarioKernelData144_HT_GENERIC_5X5_08U, 2},
{7, 14, 1472, 40, 1, gScenarioBufferData145_HT_GENERIC_5X5_08U, 40, gScenarioKernelData145_HT_GENERIC_5X5_08U, 2},
{8, 14, 1648, 40, 1, gScenarioBufferData146_HT_GENERIC_5X5_08U, 40, gScenarioKernelData146_HT_GENERIC_5X5_08U, 2},
{10, 14, 2000, 40, 1, gScenarioBufferData147_HT_GENERIC_5X5_08U, 40, gScenarioKernelData147_HT_GENERIC_5X5_08U, 2},
{12, 14, 2352, 40, 1, gScenarioBufferData148_HT_GENERIC_5X5_08U, 40, gScenarioKernelData148_HT_GENERIC_5X5_08U, 2},
{14, 14, 2704, 40, 1, gScenarioBufferData149_HT_GENERIC_5X5_08U, 40, gScenarioKernelData149_HT_GENERIC_5X5_08U, 2},
{16, 14, 3056, 40, 1, gScenarioBufferData150_HT_GENERIC_5X5_08U, 40, gScenarioKernelData150_HT_GENERIC_5X5_08U, 2},
{18, 14, 3408, 40, 1, gScenarioBufferData151_HT_GENERIC_5X5_08U, 40, gScenarioKernelData151_HT_GENERIC_5X5_08U, 2},
{20, 14, 3760, 40, 1, gScenarioBufferData152_HT_GENERIC_5X5_08U, 40, gScenarioKernelData152_HT_GENERIC_5X5_08U, 2},
{1, 16, 472, 40, 1, gScenarioBufferData153_HT_GENERIC_5X5_08U, 40, gScenarioKernelData153_HT_GENERIC_5X5_08U, 2},
{2, 16, 672, 40, 1, gScenarioBufferData154_HT_GENERIC_5X5_08U, 40, gScenarioKernelData154_HT_GENERIC_5X5_08U, 2},
{3, 16, 872, 40, 1, gScenarioBufferData155_HT_GENERIC_5X5_08U, 40, gScenarioKernelData155_HT_GENERIC_5X5_08U, 2},
{4, 16, 1072, 40, 1, gScenarioBufferData156_HT_GENERIC_5X5_08U, 40, gScenarioKernelData156_HT_GENERIC_5X5_08U, 2},
{5, 16, 1272, 40, 1, gScenarioBufferData157_HT_GENERIC_5X5_08U, 40, gScenarioKernelData157_HT_GENERIC_5X5_08U, 2},
{6, 16, 1472, 40, 1, gScenarioBufferData158_HT_GENERIC_5X5_08U, 40, gScenarioKernelData158_HT_GENERIC_5X5_08U, 2},
{7, 16, 1672, 40, 1, gScenarioBufferData159_HT_GENERIC_5X5_08U, 40, gScenarioKernelData159_HT_GENERIC_5X5_08U, 2},
{8, 16, 1872, 40, 1, gScenarioBufferData160_HT_GENERIC_5X5_08U, 40, gScenarioKernelData160_HT_GENERIC_5X5_08U, 2},
{10, 16, 2272, 40, 1, gScenarioBufferData161_HT_GENERIC_5X5_08U, 40, gScenarioKernelData161_HT_GENERIC_5X5_08U, 2},
{12, 16, 2672, 40, 1, gScenarioBufferData162_HT_GENERIC_5X5_08U, 40, gScenarioKernelData162_HT_GENERIC_5X5_08U, 2},
{14, 16, 3072, 40, 1, gScenarioBufferData163_HT_GENERIC_5X5_08U, 40, gScenarioKernelData163_HT_GENERIC_5X5_08U, 2},
{16, 16, 3472, 40, 1, gScenarioBufferData164_HT_GENERIC_5X5_08U, 40, gScenarioKernelData164_HT_GENERIC_5X5_08U, 2},
{1, 18, 528, 40, 1, gScenarioBufferData165_HT_GENERIC_5X5_08U, 40, gScenarioKernelData165_HT_GENERIC_5X5_08U, 2},
{2, 18, 752, 40, 1, gScenarioBufferData166_HT_GENERIC_5X5_08U, 40, gScenarioKernelData166_HT_GENERIC_5X5_08U, 2},
{3, 18, 976, 40, 1, gScenarioBufferData167_HT_GENERIC_5X5_08U, 40, gScenarioKernelData167_HT_GENERIC_5X5_08U, 2},
{4, 18, 1200, 40, 1, gScenarioBufferData168_HT_GENERIC_5X5_08U, 40, gScenarioKernelData168_HT_GENERIC_5X5_08U, 2},
{5, 18, 1424, 40, 1, gScenarioBufferData169_HT_GENERIC_5X5_08U, 40, gScenarioKernelData169_HT_GENERIC_5X5_08U, 2},
{6, 18, 1648, 40, 1, gScenarioBufferData170_HT_GENERIC_5X5_08U, 40, gScenarioKernelData170_HT_GENERIC_5X5_08U, 2},
{7, 18, 1872, 40, 1, gScenarioBufferData171_HT_GENERIC_5X5_08U, 40, gScenarioKernelData171_HT_GENERIC_5X5_08U, 2},
{8, 18, 2096, 40, 1, gScenarioBufferData172_HT_GENERIC_5X5_08U, 40, gScenarioKernelData172_HT_GENERIC_5X5_08U, 2},
{10, 18, 2544, 40, 1, gScenarioBufferData173_HT_GENERIC_5X5_08U, 40, gScenarioKernelData173_HT_GENERIC_5X5_08U, 2},
{12, 18, 2992, 40, 1, gScenarioBufferData174_HT_GENERIC_5X5_08U, 40, gScenarioKernelData174_HT_GENERIC_5X5_08U, 2},
{14, 18, 3440, 40, 1, gScenarioBufferData175_HT_GENERIC_5X5_08U, 40, gScenarioKernelData175_HT_GENERIC_5X5_08U, 2},
{1, 20, 584, 40, 1, gScenarioBufferData176_HT_GENERIC_5X5_08U, 40, gScenarioKernelData176_HT_GENERIC_5X5_08U, 2},
{2, 20, 832, 40, 1, gScenarioBufferData177_HT_GENERIC_5X5_08U, 40, gScenarioKernelData177_HT_GENERIC_5X5_08U, 2},
{3, 20, 1080, 40, 1, gScenarioBufferData178_HT_GENERIC_5X5_08U, 40, gScenarioKernelData178_HT_GENERIC_5X5_08U, 2},
{4, 20, 1328, 40, 1, gScenarioBufferData179_HT_GENERIC_5X5_08U, 40, gScenarioKernelData179_HT_GENERIC_5X5_08U, 2},
{5, 20, 1576, 40, 1, gScenarioBufferData180_HT_GENERIC_5X5_08U, 40, gScenarioKernelData180_HT_GENERIC_5X5_08U, 2},
{6, 20, 1824, 40, 1, gScenarioBufferData181_HT_GENERIC_5X5_08U, 40, gScenarioKernelData181_HT_GENERIC_5X5_08U, 2},
{7, 20, 2072, 40, 1, gScenarioBufferData182_HT_GENERIC_5X5_08U, 40, gScenarioKernelData182_HT_GENERIC_5X5_08U, 2},
{8, 20, 2320, 40, 1, gScenarioBufferData183_HT_GENERIC_5X5_08U, 40, gScenarioKernelData183_HT_GENERIC_5X5_08U, 2},
{10, 20, 2816, 40, 1, gScenarioBufferData184_HT_GENERIC_5X5_08U, 40, gScenarioKernelData184_HT_GENERIC_5X5_08U, 2},
{12, 20, 3312, 40, 1, gScenarioBufferData185_HT_GENERIC_5X5_08U, 40, gScenarioKernelData185_HT_GENERIC_5X5_08U, 2},
{14, 20, 3808, 40, 1, gScenarioBufferData186_HT_GENERIC_5X5_08U, 40, gScenarioKernelData186_HT_GENERIC_5X5_08U, 2},
{1, 22, 640, 40, 1, gScenarioBufferData187_HT_GENERIC_5X5_08U, 40, gScenarioKernelData187_HT_GENERIC_5X5_08U, 2},
{2, 22, 912, 40, 1, gScenarioBufferData188_HT_GENERIC_5X5_08U, 40, gScenarioKernelData188_HT_GENERIC_5X5_08U, 2},
{3, 22, 1184, 40, 1, gScenarioBufferData189_HT_GENERIC_5X5_08U, 40, gScenarioKernelData189_HT_GENERIC_5X5_08U, 2},
{4, 22, 1456, 40, 1, gScenarioBufferData190_HT_GENERIC_5X5_08U, 40, gScenarioKernelData190_HT_GENERIC_5X5_08U, 2},
{5, 22, 1728, 40, 1, gScenarioBufferData191_HT_GENERIC_5X5_08U, 40, gScenarioKernelData191_HT_GENERIC_5X5_08U, 2},
{6, 22, 2000, 40, 1, gScenarioBufferData192_HT_GENERIC_5X5_08U, 40, gScenarioKernelData192_HT_GENERIC_5X5_08U, 2},
{7, 22, 2272, 40, 1, gScenarioBufferData193_HT_GENERIC_5X5_08U, 40, gScenarioKernelData193_HT_GENERIC_5X5_08U, 2},
{8, 22, 2544, 40, 1, gScenarioBufferData194_HT_GENERIC_5X5_08U, 40, gScenarioKernelData194_HT_GENERIC_5X5_08U, 2},
{10, 22, 3088, 40, 1, gScenarioBufferData195_HT_GENERIC_5X5_08U, 40, gScenarioKernelData195_HT_GENERIC_5X5_08U, 2},
{12, 22, 3632, 40, 1, gScenarioBufferData196_HT_GENERIC_5X5_08U, 40, gScenarioKernelData196_HT_GENERIC_5X5_08U, 2},
{1, 24, 696, 40, 1, gScenarioBufferData197_HT_GENERIC_5X5_08U, 40, gScenarioKernelData197_HT_GENERIC_5X5_08U, 2},
{2, 24, 992, 40, 1, gScenarioBufferData198_HT_GENERIC_5X5_08U, 40, gScenarioKernelData198_HT_GENERIC_5X5_08U, 2},
{3, 24, 1288, 40, 1, gScenarioBufferData199_HT_GENERIC_5X5_08U, 40, gScenarioKernelData199_HT_GENERIC_5X5_08U, 2},
{4, 24, 1584, 40, 1, gScenarioBufferData200_HT_GENERIC_5X5_08U, 40, gScenarioKernelData200_HT_GENERIC_5X5_08U, 2},
{5, 24, 1880, 40, 1, gScenarioBufferData201_HT_GENERIC_5X5_08U, 40, gScenarioKernelData201_HT_GENERIC_5X5_08U, 2},
{6, 24, 2176, 40, 1, gScenarioBufferData202_HT_GENERIC_5X5_08U, 40, gScenarioKernelData202_HT_GENERIC_5X5_08U, 2},
{7, 24, 2472, 40, 1, gScenarioBufferData203_HT_GENERIC_5X5_08U, 40, gScenarioKernelData203_HT_GENERIC_5X5_08U, 2},
{8, 24, 2768, 40, 1, gScenarioBufferData204_HT_GENERIC_5X5_08U, 40, gScenarioKernelData204_HT_GENERIC_5X5_08U, 2},
{10, 24, 3360, 40, 1, gScenarioBufferData205_HT_GENERIC_5X5_08U, 40, gScenarioKernelData205_HT_GENERIC_5X5_08U, 2},
{1, 26, 752, 40, 1, gScenarioBufferData206_HT_GENERIC_5X5_08U, 40, gScenarioKernelData206_HT_GENERIC_5X5_08U, 2},
{2, 26, 1072, 40, 1, gScenarioBufferData207_HT_GENERIC_5X5_08U, 40, gScenarioKernelData207_HT_GENERIC_5X5_08U, 2},
{3, 26, 1392, 40, 1, gScenarioBufferData208_HT_GENERIC_5X5_08U, 40, gScenarioKernelData208_HT_GENERIC_5X5_08U, 2},
{4, 26, 1712, 40, 1, gScenarioBufferData209_HT_GENERIC_5X5_08U, 40, gScenarioKernelData209_HT_GENERIC_5X5_08U, 2},
{5, 26, 2032, 40, 1, gScenarioBufferData210_HT_GENERIC_5X5_08U, 40, gScenarioKernelData210_HT_GENERIC_5X5_08U, 2},
{6, 26, 2352, 40, 1, gScenarioBufferData211_HT_GENERIC_5X5_08U, 40, gScenarioKernelData211_HT_GENERIC_5X5_08U, 2},
{7, 26, 2672, 40, 1, gScenarioBufferData212_HT_GENERIC_5X5_08U, 40, gScenarioKernelData212_HT_GENERIC_5X5_08U, 2},
{8, 26, 2992, 40, 1, gScenarioBufferData213_HT_GENERIC_5X5_08U, 40, gScenarioKernelData213_HT_GENERIC_5X5_08U, 2},
{10, 26, 3632, 40, 1, gScenarioBufferData214_HT_GENERIC_5X5_08U, 40, gScenarioKernelData214_HT_GENERIC_5X5_08U, 2},
{1, 28, 808, 40, 1, gScenarioBufferData215_HT_GENERIC_5X5_08U, 40, gScenarioKernelData215_HT_GENERIC_5X5_08U, 2},
{2, 28, 1152, 40, 1, gScenarioBufferData216_HT_GENERIC_5X5_08U, 40, gScenarioKernelData216_HT_GENERIC_5X5_08U, 2},
{3, 28, 1496, 40, 1, gScenarioBufferData217_HT_GENERIC_5X5_08U, 40, gScenarioKernelData217_HT_GENERIC_5X5_08U, 2},
{4, 28, 1840, 40, 1, gScenarioBufferData218_HT_GENERIC_5X5_08U, 40, gScenarioKernelData218_HT_GENERIC_5X5_08U, 2},
{5, 28, 2184, 40, 1, gScenarioBufferData219_HT_GENERIC_5X5_08U, 40, gScenarioKernelData219_HT_GENERIC_5X5_08U, 2},
{6, 28, 2528, 40, 1, gScenarioBufferData220_HT_GENERIC_5X5_08U, 40, gScenarioKernelData220_HT_GENERIC_5X5_08U, 2},
{7, 28, 2872, 40, 1, gScenarioBufferData221_HT_GENERIC_5X5_08U, 40, gScenarioKernelData221_HT_GENERIC_5X5_08U, 2},
{8, 28, 3216, 40, 1, gScenarioBufferData222_HT_GENERIC_5X5_08U, 40, gScenarioKernelData222_HT_GENERIC_5X5_08U, 2},
{1, 30, 864, 40, 1, gScenarioBufferData223_HT_GENERIC_5X5_08U, 40, gScenarioKernelData223_HT_GENERIC_5X5_08U, 2},
{2, 30, 1232, 40, 1, gScenarioBufferData224_HT_GENERIC_5X5_08U, 40, gScenarioKernelData224_HT_GENERIC_5X5_08U, 2},
{3, 30, 1600, 40, 1, gScenarioBufferData225_HT_GENERIC_5X5_08U, 40, gScenarioKernelData225_HT_GENERIC_5X5_08U, 2},
{4, 30, 1968, 40, 1, gScenarioBufferData226_HT_GENERIC_5X5_08U, 40, gScenarioKernelData226_HT_GENERIC_5X5_08U, 2},
{5, 30, 2336, 40, 1, gScenarioBufferData227_HT_GENERIC_5X5_08U, 40, gScenarioKernelData227_HT_GENERIC_5X5_08U, 2},
{6, 30, 2704, 40, 1, gScenarioBufferData228_HT_GENERIC_5X5_08U, 40, gScenarioKernelData228_HT_GENERIC_5X5_08U, 2},
{7, 30, 3072, 40, 1, gScenarioBufferData229_HT_GENERIC_5X5_08U, 40, gScenarioKernelData229_HT_GENERIC_5X5_08U, 2},
{8, 30, 3440, 40, 1, gScenarioBufferData230_HT_GENERIC_5X5_08U, 40, gScenarioKernelData230_HT_GENERIC_5X5_08U, 2},
{1, 32, 920, 40, 1, gScenarioBufferData231_HT_GENERIC_5X5_08U, 40, gScenarioKernelData231_HT_GENERIC_5X5_08U, 2},
{2, 32, 1312, 40, 1, gScenarioBufferData232_HT_GENERIC_5X5_08U, 40, gScenarioKernelData232_HT_GENERIC_5X5_08U, 2},
{3, 32, 1704, 40, 1, gScenarioBufferData233_HT_GENERIC_5X5_08U, 40, gScenarioKernelData233_HT_GENERIC_5X5_08U, 2},
{4, 32, 2096, 40, 1, gScenarioBufferData234_HT_GENERIC_5X5_08U, 40, gScenarioKernelData234_HT_GENERIC_5X5_08U, 2},
{5, 32, 2488, 40, 1, gScenarioBufferData235_HT_GENERIC_5X5_08U, 40, gScenarioKernelData235_HT_GENERIC_5X5_08U, 2},
{6, 32, 2880, 40, 1, gScenarioBufferData236_HT_GENERIC_5X5_08U, 40, gScenarioKernelData236_HT_GENERIC_5X5_08U, 2},
{7, 32, 3272, 40, 1, gScenarioBufferData237_HT_GENERIC_5X5_08U, 40, gScenarioKernelData237_HT_GENERIC_5X5_08U, 2},
{8, 32, 3664, 40, 1, gScenarioBufferData238_HT_GENERIC_5X5_08U, 40, gScenarioKernelData238_HT_GENERIC_5X5_08U, 2}
};

static acf_scenario_list gScenarioList_HT_GENERIC_5X5_08U = {
239, //number of scenarios
gScenarioArray_HT_GENERIC_5X5_08U};
//**************************************************************

class HT_GENERIC_5X5_08U : public ACF_Process_APU
{
public:
   HT_GENERIC_5X5_08U(int32_t apex_id = 0) : ACF_Process_APU(apex_id)
   {} 

   int32_t Initialize()
   {
      int32_t lRetVal = 0;

      if (!Initialized()) //initialization steps that only need to occur once
      {
         SetProcessIdentifier("HT_GENERIC_5X5_08U");
         SetApuLoadInfo(HT_GENERIC_5X5_08U_LOAD_SEGMENTS,
                        HT_GENERIC_5X5_08U_LOAD_PMEM, HT_GENERIC_5X5_08U_LOAD_PMEM_SIZE,
                        HT_GENERIC_5X5_08U_LOAD_DMEM, HT_GENERIC_5X5_08U_LOAD_DMEM_SIZE,
                        0, 0); //assuming _LOAD_CMEM does not exist
         FlagSpatialDep();

         //***NOTE: the order in which the following ports are added is meaningful; do not change!

         AddPort("INPUT_0", ICP_DATATYPE_08U, 1, 1, 2, 1, 0, 0, 0, 0, 0, 0, 0, 0x2020202);
         AddPort("F_COEFF", ICP_DATATYPE_08S, 1, 1, 25, 1, 0, 1, 1, 0, 1, 0, 2);
         AddPort("F_SCALE", ICP_DATATYPE_08S, 1, 1, 1, 1, 0, 1, 1, 0, 1, 0, 3);
         AddPort("OUTPUT_0", ICP_DATATYPE_08U, 1, 1, 2, 1, 1, 0, 0, 0, 0, 0, 1);

         CfgScenarios(&gScenarioList_HT_GENERIC_5X5_08U);

         FlagAsInitialized();
      }

      lRetVal = SelectApuConfiguration(mApuCfg, mApexId); //by default mApuCfg = ACF_APU_CFG__APEX0_DEFAULT and mApexId = 0

      return lRetVal;
   }
};

#endif //_ACF_PROCESS_APU_HT_GENERIC_5X5_08U
