#ifndef _ACF_PROCESS_APU_RGB888_TO_Y
#define _ACF_PROCESS_APU_RGB888_TO_Y

#include <acf_process_apu.h>
#include <RGB888_TO_Y_APU_LOAD.h> //APU load associated with this process
#include <stdint.h>


//SCENARIO LIST*************************************************
static acf_scenario_buffer_data gScenarioBufferData0_RGB888_TO_Y[] = {{2, 1, 2, 0, 0x0}, {2, 1, 2, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData1_RGB888_TO_Y[] = {{4, 1, 2, 0, 0x0}, {4, 1, 2, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData2_RGB888_TO_Y[] = {{6, 1, 2, 0, 0x0}, {6, 1, 2, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData3_RGB888_TO_Y[] = {{8, 1, 2, 0, 0x0}, {8, 1, 2, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData4_RGB888_TO_Y[] = {{10, 1, 2, 0, 0x0}, {10, 1, 2, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData5_RGB888_TO_Y[] = {{12, 1, 2, 0, 0x0}, {12, 1, 2, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData6_RGB888_TO_Y[] = {{14, 1, 2, 0, 0x0}, {14, 1, 2, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData7_RGB888_TO_Y[] = {{16, 1, 2, 0, 0x0}, {16, 1, 2, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData8_RGB888_TO_Y[] = {{18, 1, 2, 0, 0x0}, {18, 1, 2, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData9_RGB888_TO_Y[] = {{20, 1, 2, 0, 0x0}, {20, 1, 2, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData10_RGB888_TO_Y[] = {{22, 1, 2, 0, 0x0}, {22, 1, 2, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData11_RGB888_TO_Y[] = {{24, 1, 2, 0, 0x0}, {24, 1, 2, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData12_RGB888_TO_Y[] = {{26, 1, 2, 0, 0x0}, {26, 1, 2, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData13_RGB888_TO_Y[] = {{28, 1, 2, 0, 0x0}, {28, 1, 2, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData14_RGB888_TO_Y[] = {{30, 1, 2, 0, 0x0}, {30, 1, 2, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData15_RGB888_TO_Y[] = {{32, 1, 2, 0, 0x0}, {32, 1, 2, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData16_RGB888_TO_Y[] = {{2, 2, 2, 0, 0x0}, {2, 2, 2, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData17_RGB888_TO_Y[] = {{4, 2, 2, 0, 0x0}, {4, 2, 2, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData18_RGB888_TO_Y[] = {{6, 2, 2, 0, 0x0}, {6, 2, 2, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData19_RGB888_TO_Y[] = {{8, 2, 2, 0, 0x0}, {8, 2, 2, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData20_RGB888_TO_Y[] = {{10, 2, 2, 0, 0x0}, {10, 2, 2, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData21_RGB888_TO_Y[] = {{12, 2, 2, 0, 0x0}, {12, 2, 2, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData22_RGB888_TO_Y[] = {{14, 2, 2, 0, 0x0}, {14, 2, 2, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData23_RGB888_TO_Y[] = {{16, 2, 2, 0, 0x0}, {16, 2, 2, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData24_RGB888_TO_Y[] = {{18, 2, 2, 0, 0x0}, {18, 2, 2, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData25_RGB888_TO_Y[] = {{20, 2, 2, 0, 0x0}, {20, 2, 2, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData26_RGB888_TO_Y[] = {{22, 2, 2, 0, 0x0}, {22, 2, 2, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData27_RGB888_TO_Y[] = {{24, 2, 2, 0, 0x0}, {24, 2, 2, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData28_RGB888_TO_Y[] = {{26, 2, 2, 0, 0x0}, {26, 2, 2, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData29_RGB888_TO_Y[] = {{28, 2, 2, 0, 0x0}, {28, 2, 2, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData30_RGB888_TO_Y[] = {{30, 2, 2, 0, 0x0}, {30, 2, 2, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData31_RGB888_TO_Y[] = {{32, 2, 2, 0, 0x0}, {32, 2, 2, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData32_RGB888_TO_Y[] = {{2, 4, 2, 0, 0x0}, {2, 4, 2, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData33_RGB888_TO_Y[] = {{4, 4, 2, 0, 0x0}, {4, 4, 2, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData34_RGB888_TO_Y[] = {{6, 4, 2, 0, 0x0}, {6, 4, 2, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData35_RGB888_TO_Y[] = {{8, 4, 2, 0, 0x0}, {8, 4, 2, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData36_RGB888_TO_Y[] = {{10, 4, 2, 0, 0x0}, {10, 4, 2, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData37_RGB888_TO_Y[] = {{12, 4, 2, 0, 0x0}, {12, 4, 2, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData38_RGB888_TO_Y[] = {{14, 4, 2, 0, 0x0}, {14, 4, 2, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData39_RGB888_TO_Y[] = {{16, 4, 2, 0, 0x0}, {16, 4, 2, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData40_RGB888_TO_Y[] = {{18, 4, 2, 0, 0x0}, {18, 4, 2, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData41_RGB888_TO_Y[] = {{20, 4, 2, 0, 0x0}, {20, 4, 2, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData42_RGB888_TO_Y[] = {{22, 4, 2, 0, 0x0}, {22, 4, 2, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData43_RGB888_TO_Y[] = {{24, 4, 2, 0, 0x0}, {24, 4, 2, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData44_RGB888_TO_Y[] = {{26, 4, 2, 0, 0x0}, {26, 4, 2, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData45_RGB888_TO_Y[] = {{28, 4, 2, 0, 0x0}, {28, 4, 2, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData46_RGB888_TO_Y[] = {{30, 4, 2, 0, 0x0}, {30, 4, 2, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData47_RGB888_TO_Y[] = {{32, 4, 2, 0, 0x0}, {32, 4, 2, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData48_RGB888_TO_Y[] = {{2, 6, 2, 0, 0x0}, {2, 6, 2, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData49_RGB888_TO_Y[] = {{4, 6, 2, 0, 0x0}, {4, 6, 2, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData50_RGB888_TO_Y[] = {{6, 6, 2, 0, 0x0}, {6, 6, 2, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData51_RGB888_TO_Y[] = {{8, 6, 2, 0, 0x0}, {8, 6, 2, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData52_RGB888_TO_Y[] = {{10, 6, 2, 0, 0x0}, {10, 6, 2, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData53_RGB888_TO_Y[] = {{12, 6, 2, 0, 0x0}, {12, 6, 2, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData54_RGB888_TO_Y[] = {{14, 6, 2, 0, 0x0}, {14, 6, 2, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData55_RGB888_TO_Y[] = {{16, 6, 2, 0, 0x0}, {16, 6, 2, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData56_RGB888_TO_Y[] = {{18, 6, 2, 0, 0x0}, {18, 6, 2, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData57_RGB888_TO_Y[] = {{20, 6, 2, 0, 0x0}, {20, 6, 2, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData58_RGB888_TO_Y[] = {{22, 6, 2, 0, 0x0}, {22, 6, 2, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData59_RGB888_TO_Y[] = {{24, 6, 2, 0, 0x0}, {24, 6, 2, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData60_RGB888_TO_Y[] = {{26, 6, 2, 0, 0x0}, {26, 6, 2, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData61_RGB888_TO_Y[] = {{28, 6, 2, 0, 0x0}, {28, 6, 2, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData62_RGB888_TO_Y[] = {{30, 6, 2, 0, 0x0}, {30, 6, 2, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData63_RGB888_TO_Y[] = {{32, 6, 2, 0, 0x0}, {32, 6, 2, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData64_RGB888_TO_Y[] = {{2, 8, 2, 0, 0x0}, {2, 8, 2, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData65_RGB888_TO_Y[] = {{4, 8, 2, 0, 0x0}, {4, 8, 2, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData66_RGB888_TO_Y[] = {{6, 8, 2, 0, 0x0}, {6, 8, 2, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData67_RGB888_TO_Y[] = {{8, 8, 2, 0, 0x0}, {8, 8, 2, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData68_RGB888_TO_Y[] = {{10, 8, 2, 0, 0x0}, {10, 8, 2, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData69_RGB888_TO_Y[] = {{12, 8, 2, 0, 0x0}, {12, 8, 2, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData70_RGB888_TO_Y[] = {{14, 8, 2, 0, 0x0}, {14, 8, 2, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData71_RGB888_TO_Y[] = {{16, 8, 2, 0, 0x0}, {16, 8, 2, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData72_RGB888_TO_Y[] = {{18, 8, 2, 0, 0x0}, {18, 8, 2, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData73_RGB888_TO_Y[] = {{20, 8, 2, 0, 0x0}, {20, 8, 2, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData74_RGB888_TO_Y[] = {{22, 8, 2, 0, 0x0}, {22, 8, 2, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData75_RGB888_TO_Y[] = {{24, 8, 2, 0, 0x0}, {24, 8, 2, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData76_RGB888_TO_Y[] = {{26, 8, 2, 0, 0x0}, {26, 8, 2, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData77_RGB888_TO_Y[] = {{28, 8, 2, 0, 0x0}, {28, 8, 2, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData78_RGB888_TO_Y[] = {{30, 8, 2, 0, 0x0}, {30, 8, 2, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData79_RGB888_TO_Y[] = {{32, 8, 2, 0, 0x0}, {32, 8, 2, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData80_RGB888_TO_Y[] = {{2, 10, 2, 0, 0x0}, {2, 10, 2, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData81_RGB888_TO_Y[] = {{4, 10, 2, 0, 0x0}, {4, 10, 2, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData82_RGB888_TO_Y[] = {{6, 10, 2, 0, 0x0}, {6, 10, 2, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData83_RGB888_TO_Y[] = {{8, 10, 2, 0, 0x0}, {8, 10, 2, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData84_RGB888_TO_Y[] = {{10, 10, 2, 0, 0x0}, {10, 10, 2, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData85_RGB888_TO_Y[] = {{12, 10, 2, 0, 0x0}, {12, 10, 2, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData86_RGB888_TO_Y[] = {{14, 10, 2, 0, 0x0}, {14, 10, 2, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData87_RGB888_TO_Y[] = {{16, 10, 2, 0, 0x0}, {16, 10, 2, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData88_RGB888_TO_Y[] = {{18, 10, 2, 0, 0x0}, {18, 10, 2, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData89_RGB888_TO_Y[] = {{20, 10, 2, 0, 0x0}, {20, 10, 2, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData90_RGB888_TO_Y[] = {{22, 10, 2, 0, 0x0}, {22, 10, 2, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData91_RGB888_TO_Y[] = {{24, 10, 2, 0, 0x0}, {24, 10, 2, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData92_RGB888_TO_Y[] = {{26, 10, 2, 0, 0x0}, {26, 10, 2, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData93_RGB888_TO_Y[] = {{28, 10, 2, 0, 0x0}, {28, 10, 2, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData94_RGB888_TO_Y[] = {{30, 10, 2, 0, 0x0}, {30, 10, 2, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData95_RGB888_TO_Y[] = {{32, 10, 2, 0, 0x0}, {32, 10, 2, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData96_RGB888_TO_Y[] = {{2, 12, 2, 0, 0x0}, {2, 12, 2, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData97_RGB888_TO_Y[] = {{4, 12, 2, 0, 0x0}, {4, 12, 2, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData98_RGB888_TO_Y[] = {{6, 12, 2, 0, 0x0}, {6, 12, 2, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData99_RGB888_TO_Y[] = {{8, 12, 2, 0, 0x0}, {8, 12, 2, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData100_RGB888_TO_Y[] = {{10, 12, 2, 0, 0x0}, {10, 12, 2, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData101_RGB888_TO_Y[] = {{12, 12, 2, 0, 0x0}, {12, 12, 2, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData102_RGB888_TO_Y[] = {{14, 12, 2, 0, 0x0}, {14, 12, 2, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData103_RGB888_TO_Y[] = {{16, 12, 2, 0, 0x0}, {16, 12, 2, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData104_RGB888_TO_Y[] = {{18, 12, 2, 0, 0x0}, {18, 12, 2, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData105_RGB888_TO_Y[] = {{20, 12, 2, 0, 0x0}, {20, 12, 2, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData106_RGB888_TO_Y[] = {{22, 12, 2, 0, 0x0}, {22, 12, 2, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData107_RGB888_TO_Y[] = {{24, 12, 2, 0, 0x0}, {24, 12, 2, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData108_RGB888_TO_Y[] = {{26, 12, 2, 0, 0x0}, {26, 12, 2, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData109_RGB888_TO_Y[] = {{28, 12, 2, 0, 0x0}, {28, 12, 2, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData110_RGB888_TO_Y[] = {{30, 12, 2, 0, 0x0}, {30, 12, 2, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData111_RGB888_TO_Y[] = {{32, 12, 2, 0, 0x0}, {32, 12, 2, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData112_RGB888_TO_Y[] = {{2, 14, 2, 0, 0x0}, {2, 14, 2, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData113_RGB888_TO_Y[] = {{4, 14, 2, 0, 0x0}, {4, 14, 2, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData114_RGB888_TO_Y[] = {{6, 14, 2, 0, 0x0}, {6, 14, 2, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData115_RGB888_TO_Y[] = {{8, 14, 2, 0, 0x0}, {8, 14, 2, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData116_RGB888_TO_Y[] = {{10, 14, 2, 0, 0x0}, {10, 14, 2, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData117_RGB888_TO_Y[] = {{12, 14, 2, 0, 0x0}, {12, 14, 2, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData118_RGB888_TO_Y[] = {{14, 14, 2, 0, 0x0}, {14, 14, 2, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData119_RGB888_TO_Y[] = {{16, 14, 2, 0, 0x0}, {16, 14, 2, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData120_RGB888_TO_Y[] = {{18, 14, 2, 0, 0x0}, {18, 14, 2, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData121_RGB888_TO_Y[] = {{20, 14, 2, 0, 0x0}, {20, 14, 2, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData122_RGB888_TO_Y[] = {{22, 14, 2, 0, 0x0}, {22, 14, 2, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData123_RGB888_TO_Y[] = {{24, 14, 2, 0, 0x0}, {24, 14, 2, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData124_RGB888_TO_Y[] = {{26, 14, 2, 0, 0x0}, {26, 14, 2, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData125_RGB888_TO_Y[] = {{2, 16, 2, 0, 0x0}, {2, 16, 2, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData126_RGB888_TO_Y[] = {{4, 16, 2, 0, 0x0}, {4, 16, 2, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData127_RGB888_TO_Y[] = {{6, 16, 2, 0, 0x0}, {6, 16, 2, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData128_RGB888_TO_Y[] = {{8, 16, 2, 0, 0x0}, {8, 16, 2, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData129_RGB888_TO_Y[] = {{10, 16, 2, 0, 0x0}, {10, 16, 2, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData130_RGB888_TO_Y[] = {{12, 16, 2, 0, 0x0}, {12, 16, 2, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData131_RGB888_TO_Y[] = {{14, 16, 2, 0, 0x0}, {14, 16, 2, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData132_RGB888_TO_Y[] = {{16, 16, 2, 0, 0x0}, {16, 16, 2, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData133_RGB888_TO_Y[] = {{18, 16, 2, 0, 0x0}, {18, 16, 2, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData134_RGB888_TO_Y[] = {{20, 16, 2, 0, 0x0}, {20, 16, 2, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData135_RGB888_TO_Y[] = {{22, 16, 2, 0, 0x0}, {22, 16, 2, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData136_RGB888_TO_Y[] = {{24, 16, 2, 0, 0x0}, {24, 16, 2, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData137_RGB888_TO_Y[] = {{2, 18, 2, 0, 0x0}, {2, 18, 2, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData138_RGB888_TO_Y[] = {{4, 18, 2, 0, 0x0}, {4, 18, 2, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData139_RGB888_TO_Y[] = {{6, 18, 2, 0, 0x0}, {6, 18, 2, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData140_RGB888_TO_Y[] = {{8, 18, 2, 0, 0x0}, {8, 18, 2, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData141_RGB888_TO_Y[] = {{10, 18, 2, 0, 0x0}, {10, 18, 2, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData142_RGB888_TO_Y[] = {{12, 18, 2, 0, 0x0}, {12, 18, 2, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData143_RGB888_TO_Y[] = {{14, 18, 2, 0, 0x0}, {14, 18, 2, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData144_RGB888_TO_Y[] = {{16, 18, 2, 0, 0x0}, {16, 18, 2, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData145_RGB888_TO_Y[] = {{18, 18, 2, 0, 0x0}, {18, 18, 2, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData146_RGB888_TO_Y[] = {{20, 18, 2, 0, 0x0}, {20, 18, 2, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData147_RGB888_TO_Y[] = {{2, 20, 2, 0, 0x0}, {2, 20, 2, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData148_RGB888_TO_Y[] = {{4, 20, 2, 0, 0x0}, {4, 20, 2, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData149_RGB888_TO_Y[] = {{6, 20, 2, 0, 0x0}, {6, 20, 2, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData150_RGB888_TO_Y[] = {{8, 20, 2, 0, 0x0}, {8, 20, 2, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData151_RGB888_TO_Y[] = {{10, 20, 2, 0, 0x0}, {10, 20, 2, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData152_RGB888_TO_Y[] = {{12, 20, 2, 0, 0x0}, {12, 20, 2, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData153_RGB888_TO_Y[] = {{14, 20, 2, 0, 0x0}, {14, 20, 2, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData154_RGB888_TO_Y[] = {{16, 20, 2, 0, 0x0}, {16, 20, 2, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData155_RGB888_TO_Y[] = {{18, 20, 2, 0, 0x0}, {18, 20, 2, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData156_RGB888_TO_Y[] = {{2, 22, 2, 0, 0x0}, {2, 22, 2, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData157_RGB888_TO_Y[] = {{4, 22, 2, 0, 0x0}, {4, 22, 2, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData158_RGB888_TO_Y[] = {{6, 22, 2, 0, 0x0}, {6, 22, 2, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData159_RGB888_TO_Y[] = {{8, 22, 2, 0, 0x0}, {8, 22, 2, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData160_RGB888_TO_Y[] = {{10, 22, 2, 0, 0x0}, {10, 22, 2, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData161_RGB888_TO_Y[] = {{12, 22, 2, 0, 0x0}, {12, 22, 2, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData162_RGB888_TO_Y[] = {{14, 22, 2, 0, 0x0}, {14, 22, 2, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData163_RGB888_TO_Y[] = {{16, 22, 2, 0, 0x0}, {16, 22, 2, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData164_RGB888_TO_Y[] = {{2, 24, 2, 0, 0x0}, {2, 24, 2, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData165_RGB888_TO_Y[] = {{4, 24, 2, 0, 0x0}, {4, 24, 2, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData166_RGB888_TO_Y[] = {{6, 24, 2, 0, 0x0}, {6, 24, 2, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData167_RGB888_TO_Y[] = {{8, 24, 2, 0, 0x0}, {8, 24, 2, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData168_RGB888_TO_Y[] = {{10, 24, 2, 0, 0x0}, {10, 24, 2, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData169_RGB888_TO_Y[] = {{12, 24, 2, 0, 0x0}, {12, 24, 2, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData170_RGB888_TO_Y[] = {{14, 24, 2, 0, 0x0}, {14, 24, 2, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData171_RGB888_TO_Y[] = {{16, 24, 2, 0, 0x0}, {16, 24, 2, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData172_RGB888_TO_Y[] = {{2, 26, 2, 0, 0x0}, {2, 26, 2, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData173_RGB888_TO_Y[] = {{4, 26, 2, 0, 0x0}, {4, 26, 2, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData174_RGB888_TO_Y[] = {{6, 26, 2, 0, 0x0}, {6, 26, 2, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData175_RGB888_TO_Y[] = {{8, 26, 2, 0, 0x0}, {8, 26, 2, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData176_RGB888_TO_Y[] = {{10, 26, 2, 0, 0x0}, {10, 26, 2, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData177_RGB888_TO_Y[] = {{12, 26, 2, 0, 0x0}, {12, 26, 2, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData178_RGB888_TO_Y[] = {{14, 26, 2, 0, 0x0}, {14, 26, 2, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData179_RGB888_TO_Y[] = {{2, 28, 2, 0, 0x0}, {2, 28, 2, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData180_RGB888_TO_Y[] = {{4, 28, 2, 0, 0x0}, {4, 28, 2, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData181_RGB888_TO_Y[] = {{6, 28, 2, 0, 0x0}, {6, 28, 2, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData182_RGB888_TO_Y[] = {{8, 28, 2, 0, 0x0}, {8, 28, 2, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData183_RGB888_TO_Y[] = {{10, 28, 2, 0, 0x0}, {10, 28, 2, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData184_RGB888_TO_Y[] = {{12, 28, 2, 0, 0x0}, {12, 28, 2, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData185_RGB888_TO_Y[] = {{2, 30, 2, 0, 0x0}, {2, 30, 2, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData186_RGB888_TO_Y[] = {{4, 30, 2, 0, 0x0}, {4, 30, 2, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData187_RGB888_TO_Y[] = {{6, 30, 2, 0, 0x0}, {6, 30, 2, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData188_RGB888_TO_Y[] = {{8, 30, 2, 0, 0x0}, {8, 30, 2, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData189_RGB888_TO_Y[] = {{10, 30, 2, 0, 0x0}, {10, 30, 2, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData190_RGB888_TO_Y[] = {{12, 30, 2, 0, 0x0}, {12, 30, 2, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData191_RGB888_TO_Y[] = {{2, 32, 2, 0, 0x0}, {2, 32, 2, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData192_RGB888_TO_Y[] = {{4, 32, 2, 0, 0x0}, {4, 32, 2, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData193_RGB888_TO_Y[] = {{6, 32, 2, 0, 0x0}, {6, 32, 2, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData194_RGB888_TO_Y[] = {{8, 32, 2, 0, 0x0}, {8, 32, 2, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData195_RGB888_TO_Y[] = {{10, 32, 2, 0, 0x0}, {10, 32, 2, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData196_RGB888_TO_Y[] = {{12, 32, 2, 0, 0x0}, {12, 32, 2, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};

static acf_scenario_kernel_data gScenarioKernelData0_RGB888_TO_Y[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData1_RGB888_TO_Y[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData2_RGB888_TO_Y[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData3_RGB888_TO_Y[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData4_RGB888_TO_Y[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData5_RGB888_TO_Y[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData6_RGB888_TO_Y[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData7_RGB888_TO_Y[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData8_RGB888_TO_Y[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData9_RGB888_TO_Y[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData10_RGB888_TO_Y[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData11_RGB888_TO_Y[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData12_RGB888_TO_Y[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData13_RGB888_TO_Y[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData14_RGB888_TO_Y[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData15_RGB888_TO_Y[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData16_RGB888_TO_Y[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData17_RGB888_TO_Y[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData18_RGB888_TO_Y[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData19_RGB888_TO_Y[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData20_RGB888_TO_Y[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData21_RGB888_TO_Y[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData22_RGB888_TO_Y[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData23_RGB888_TO_Y[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData24_RGB888_TO_Y[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData25_RGB888_TO_Y[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData26_RGB888_TO_Y[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData27_RGB888_TO_Y[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData28_RGB888_TO_Y[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData29_RGB888_TO_Y[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData30_RGB888_TO_Y[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData31_RGB888_TO_Y[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData32_RGB888_TO_Y[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData33_RGB888_TO_Y[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData34_RGB888_TO_Y[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData35_RGB888_TO_Y[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData36_RGB888_TO_Y[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData37_RGB888_TO_Y[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData38_RGB888_TO_Y[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData39_RGB888_TO_Y[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData40_RGB888_TO_Y[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData41_RGB888_TO_Y[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData42_RGB888_TO_Y[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData43_RGB888_TO_Y[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData44_RGB888_TO_Y[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData45_RGB888_TO_Y[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData46_RGB888_TO_Y[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData47_RGB888_TO_Y[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData48_RGB888_TO_Y[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData49_RGB888_TO_Y[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData50_RGB888_TO_Y[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData51_RGB888_TO_Y[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData52_RGB888_TO_Y[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData53_RGB888_TO_Y[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData54_RGB888_TO_Y[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData55_RGB888_TO_Y[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData56_RGB888_TO_Y[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData57_RGB888_TO_Y[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData58_RGB888_TO_Y[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData59_RGB888_TO_Y[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData60_RGB888_TO_Y[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData61_RGB888_TO_Y[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData62_RGB888_TO_Y[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData63_RGB888_TO_Y[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData64_RGB888_TO_Y[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData65_RGB888_TO_Y[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData66_RGB888_TO_Y[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData67_RGB888_TO_Y[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData68_RGB888_TO_Y[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData69_RGB888_TO_Y[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData70_RGB888_TO_Y[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData71_RGB888_TO_Y[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData72_RGB888_TO_Y[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData73_RGB888_TO_Y[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData74_RGB888_TO_Y[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData75_RGB888_TO_Y[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData76_RGB888_TO_Y[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData77_RGB888_TO_Y[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData78_RGB888_TO_Y[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData79_RGB888_TO_Y[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData80_RGB888_TO_Y[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData81_RGB888_TO_Y[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData82_RGB888_TO_Y[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData83_RGB888_TO_Y[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData84_RGB888_TO_Y[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData85_RGB888_TO_Y[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData86_RGB888_TO_Y[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData87_RGB888_TO_Y[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData88_RGB888_TO_Y[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData89_RGB888_TO_Y[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData90_RGB888_TO_Y[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData91_RGB888_TO_Y[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData92_RGB888_TO_Y[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData93_RGB888_TO_Y[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData94_RGB888_TO_Y[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData95_RGB888_TO_Y[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData96_RGB888_TO_Y[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData97_RGB888_TO_Y[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData98_RGB888_TO_Y[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData99_RGB888_TO_Y[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData100_RGB888_TO_Y[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData101_RGB888_TO_Y[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData102_RGB888_TO_Y[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData103_RGB888_TO_Y[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData104_RGB888_TO_Y[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData105_RGB888_TO_Y[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData106_RGB888_TO_Y[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData107_RGB888_TO_Y[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData108_RGB888_TO_Y[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData109_RGB888_TO_Y[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData110_RGB888_TO_Y[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData111_RGB888_TO_Y[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData112_RGB888_TO_Y[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData113_RGB888_TO_Y[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData114_RGB888_TO_Y[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData115_RGB888_TO_Y[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData116_RGB888_TO_Y[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData117_RGB888_TO_Y[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData118_RGB888_TO_Y[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData119_RGB888_TO_Y[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData120_RGB888_TO_Y[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData121_RGB888_TO_Y[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData122_RGB888_TO_Y[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData123_RGB888_TO_Y[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData124_RGB888_TO_Y[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData125_RGB888_TO_Y[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData126_RGB888_TO_Y[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData127_RGB888_TO_Y[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData128_RGB888_TO_Y[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData129_RGB888_TO_Y[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData130_RGB888_TO_Y[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData131_RGB888_TO_Y[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData132_RGB888_TO_Y[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData133_RGB888_TO_Y[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData134_RGB888_TO_Y[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData135_RGB888_TO_Y[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData136_RGB888_TO_Y[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData137_RGB888_TO_Y[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData138_RGB888_TO_Y[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData139_RGB888_TO_Y[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData140_RGB888_TO_Y[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData141_RGB888_TO_Y[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData142_RGB888_TO_Y[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData143_RGB888_TO_Y[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData144_RGB888_TO_Y[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData145_RGB888_TO_Y[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData146_RGB888_TO_Y[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData147_RGB888_TO_Y[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData148_RGB888_TO_Y[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData149_RGB888_TO_Y[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData150_RGB888_TO_Y[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData151_RGB888_TO_Y[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData152_RGB888_TO_Y[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData153_RGB888_TO_Y[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData154_RGB888_TO_Y[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData155_RGB888_TO_Y[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData156_RGB888_TO_Y[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData157_RGB888_TO_Y[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData158_RGB888_TO_Y[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData159_RGB888_TO_Y[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData160_RGB888_TO_Y[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData161_RGB888_TO_Y[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData162_RGB888_TO_Y[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData163_RGB888_TO_Y[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData164_RGB888_TO_Y[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData165_RGB888_TO_Y[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData166_RGB888_TO_Y[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData167_RGB888_TO_Y[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData168_RGB888_TO_Y[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData169_RGB888_TO_Y[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData170_RGB888_TO_Y[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData171_RGB888_TO_Y[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData172_RGB888_TO_Y[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData173_RGB888_TO_Y[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData174_RGB888_TO_Y[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData175_RGB888_TO_Y[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData176_RGB888_TO_Y[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData177_RGB888_TO_Y[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData178_RGB888_TO_Y[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData179_RGB888_TO_Y[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData180_RGB888_TO_Y[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData181_RGB888_TO_Y[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData182_RGB888_TO_Y[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData183_RGB888_TO_Y[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData184_RGB888_TO_Y[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData185_RGB888_TO_Y[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData186_RGB888_TO_Y[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData187_RGB888_TO_Y[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData188_RGB888_TO_Y[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData189_RGB888_TO_Y[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData190_RGB888_TO_Y[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData191_RGB888_TO_Y[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData192_RGB888_TO_Y[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData193_RGB888_TO_Y[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData194_RGB888_TO_Y[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData195_RGB888_TO_Y[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData196_RGB888_TO_Y[] = {{0}};

static acf_scenario gScenarioArray_RGB888_TO_Y[] = {
{2, 1, 20, 24, 0, gScenarioBufferData0_RGB888_TO_Y, 50, gScenarioKernelData0_RGB888_TO_Y, 2},
{4, 1, 40, 24, 0, gScenarioBufferData1_RGB888_TO_Y, 50, gScenarioKernelData1_RGB888_TO_Y, 2},
{6, 1, 60, 24, 0, gScenarioBufferData2_RGB888_TO_Y, 50, gScenarioKernelData2_RGB888_TO_Y, 2},
{8, 1, 80, 24, 0, gScenarioBufferData3_RGB888_TO_Y, 50, gScenarioKernelData3_RGB888_TO_Y, 2},
{10, 1, 100, 24, 0, gScenarioBufferData4_RGB888_TO_Y, 50, gScenarioKernelData4_RGB888_TO_Y, 2},
{12, 1, 120, 24, 0, gScenarioBufferData5_RGB888_TO_Y, 50, gScenarioKernelData5_RGB888_TO_Y, 2},
{14, 1, 140, 24, 0, gScenarioBufferData6_RGB888_TO_Y, 50, gScenarioKernelData6_RGB888_TO_Y, 2},
{16, 1, 160, 24, 0, gScenarioBufferData7_RGB888_TO_Y, 50, gScenarioKernelData7_RGB888_TO_Y, 2},
{18, 1, 180, 24, 0, gScenarioBufferData8_RGB888_TO_Y, 50, gScenarioKernelData8_RGB888_TO_Y, 2},
{20, 1, 200, 24, 0, gScenarioBufferData9_RGB888_TO_Y, 50, gScenarioKernelData9_RGB888_TO_Y, 2},
{22, 1, 220, 24, 0, gScenarioBufferData10_RGB888_TO_Y, 50, gScenarioKernelData10_RGB888_TO_Y, 2},
{24, 1, 240, 24, 0, gScenarioBufferData11_RGB888_TO_Y, 50, gScenarioKernelData11_RGB888_TO_Y, 2},
{26, 1, 260, 24, 0, gScenarioBufferData12_RGB888_TO_Y, 50, gScenarioKernelData12_RGB888_TO_Y, 2},
{28, 1, 280, 24, 0, gScenarioBufferData13_RGB888_TO_Y, 50, gScenarioKernelData13_RGB888_TO_Y, 2},
{30, 1, 300, 24, 0, gScenarioBufferData14_RGB888_TO_Y, 50, gScenarioKernelData14_RGB888_TO_Y, 2},
{32, 1, 320, 24, 0, gScenarioBufferData15_RGB888_TO_Y, 50, gScenarioKernelData15_RGB888_TO_Y, 2},
{2, 2, 40, 24, 0, gScenarioBufferData16_RGB888_TO_Y, 50, gScenarioKernelData16_RGB888_TO_Y, 2},
{4, 2, 80, 24, 0, gScenarioBufferData17_RGB888_TO_Y, 50, gScenarioKernelData17_RGB888_TO_Y, 2},
{6, 2, 120, 24, 0, gScenarioBufferData18_RGB888_TO_Y, 50, gScenarioKernelData18_RGB888_TO_Y, 2},
{8, 2, 160, 24, 0, gScenarioBufferData19_RGB888_TO_Y, 50, gScenarioKernelData19_RGB888_TO_Y, 2},
{10, 2, 200, 24, 0, gScenarioBufferData20_RGB888_TO_Y, 50, gScenarioKernelData20_RGB888_TO_Y, 2},
{12, 2, 240, 24, 0, gScenarioBufferData21_RGB888_TO_Y, 50, gScenarioKernelData21_RGB888_TO_Y, 2},
{14, 2, 280, 24, 0, gScenarioBufferData22_RGB888_TO_Y, 50, gScenarioKernelData22_RGB888_TO_Y, 2},
{16, 2, 320, 24, 0, gScenarioBufferData23_RGB888_TO_Y, 50, gScenarioKernelData23_RGB888_TO_Y, 2},
{18, 2, 360, 24, 0, gScenarioBufferData24_RGB888_TO_Y, 50, gScenarioKernelData24_RGB888_TO_Y, 2},
{20, 2, 400, 24, 0, gScenarioBufferData25_RGB888_TO_Y, 50, gScenarioKernelData25_RGB888_TO_Y, 2},
{22, 2, 440, 24, 0, gScenarioBufferData26_RGB888_TO_Y, 50, gScenarioKernelData26_RGB888_TO_Y, 2},
{24, 2, 480, 24, 0, gScenarioBufferData27_RGB888_TO_Y, 50, gScenarioKernelData27_RGB888_TO_Y, 2},
{26, 2, 520, 24, 0, gScenarioBufferData28_RGB888_TO_Y, 50, gScenarioKernelData28_RGB888_TO_Y, 2},
{28, 2, 560, 24, 0, gScenarioBufferData29_RGB888_TO_Y, 50, gScenarioKernelData29_RGB888_TO_Y, 2},
{30, 2, 600, 24, 0, gScenarioBufferData30_RGB888_TO_Y, 50, gScenarioKernelData30_RGB888_TO_Y, 2},
{32, 2, 640, 24, 0, gScenarioBufferData31_RGB888_TO_Y, 50, gScenarioKernelData31_RGB888_TO_Y, 2},
{2, 4, 80, 24, 0, gScenarioBufferData32_RGB888_TO_Y, 50, gScenarioKernelData32_RGB888_TO_Y, 2},
{4, 4, 160, 24, 0, gScenarioBufferData33_RGB888_TO_Y, 50, gScenarioKernelData33_RGB888_TO_Y, 2},
{6, 4, 240, 24, 0, gScenarioBufferData34_RGB888_TO_Y, 50, gScenarioKernelData34_RGB888_TO_Y, 2},
{8, 4, 320, 24, 0, gScenarioBufferData35_RGB888_TO_Y, 50, gScenarioKernelData35_RGB888_TO_Y, 2},
{10, 4, 400, 24, 0, gScenarioBufferData36_RGB888_TO_Y, 50, gScenarioKernelData36_RGB888_TO_Y, 2},
{12, 4, 480, 24, 0, gScenarioBufferData37_RGB888_TO_Y, 50, gScenarioKernelData37_RGB888_TO_Y, 2},
{14, 4, 560, 24, 0, gScenarioBufferData38_RGB888_TO_Y, 50, gScenarioKernelData38_RGB888_TO_Y, 2},
{16, 4, 640, 24, 0, gScenarioBufferData39_RGB888_TO_Y, 50, gScenarioKernelData39_RGB888_TO_Y, 2},
{18, 4, 720, 24, 0, gScenarioBufferData40_RGB888_TO_Y, 50, gScenarioKernelData40_RGB888_TO_Y, 2},
{20, 4, 800, 24, 0, gScenarioBufferData41_RGB888_TO_Y, 50, gScenarioKernelData41_RGB888_TO_Y, 2},
{22, 4, 880, 24, 0, gScenarioBufferData42_RGB888_TO_Y, 50, gScenarioKernelData42_RGB888_TO_Y, 2},
{24, 4, 960, 24, 0, gScenarioBufferData43_RGB888_TO_Y, 50, gScenarioKernelData43_RGB888_TO_Y, 2},
{26, 4, 1040, 24, 0, gScenarioBufferData44_RGB888_TO_Y, 50, gScenarioKernelData44_RGB888_TO_Y, 2},
{28, 4, 1120, 24, 0, gScenarioBufferData45_RGB888_TO_Y, 50, gScenarioKernelData45_RGB888_TO_Y, 2},
{30, 4, 1200, 24, 0, gScenarioBufferData46_RGB888_TO_Y, 50, gScenarioKernelData46_RGB888_TO_Y, 2},
{32, 4, 1280, 24, 0, gScenarioBufferData47_RGB888_TO_Y, 50, gScenarioKernelData47_RGB888_TO_Y, 2},
{2, 6, 120, 24, 0, gScenarioBufferData48_RGB888_TO_Y, 50, gScenarioKernelData48_RGB888_TO_Y, 2},
{4, 6, 240, 24, 0, gScenarioBufferData49_RGB888_TO_Y, 50, gScenarioKernelData49_RGB888_TO_Y, 2},
{6, 6, 360, 24, 0, gScenarioBufferData50_RGB888_TO_Y, 50, gScenarioKernelData50_RGB888_TO_Y, 2},
{8, 6, 480, 24, 0, gScenarioBufferData51_RGB888_TO_Y, 50, gScenarioKernelData51_RGB888_TO_Y, 2},
{10, 6, 600, 24, 0, gScenarioBufferData52_RGB888_TO_Y, 50, gScenarioKernelData52_RGB888_TO_Y, 2},
{12, 6, 720, 24, 0, gScenarioBufferData53_RGB888_TO_Y, 50, gScenarioKernelData53_RGB888_TO_Y, 2},
{14, 6, 840, 24, 0, gScenarioBufferData54_RGB888_TO_Y, 50, gScenarioKernelData54_RGB888_TO_Y, 2},
{16, 6, 960, 24, 0, gScenarioBufferData55_RGB888_TO_Y, 50, gScenarioKernelData55_RGB888_TO_Y, 2},
{18, 6, 1080, 24, 0, gScenarioBufferData56_RGB888_TO_Y, 50, gScenarioKernelData56_RGB888_TO_Y, 2},
{20, 6, 1200, 24, 0, gScenarioBufferData57_RGB888_TO_Y, 50, gScenarioKernelData57_RGB888_TO_Y, 2},
{22, 6, 1320, 24, 0, gScenarioBufferData58_RGB888_TO_Y, 50, gScenarioKernelData58_RGB888_TO_Y, 2},
{24, 6, 1440, 24, 0, gScenarioBufferData59_RGB888_TO_Y, 50, gScenarioKernelData59_RGB888_TO_Y, 2},
{26, 6, 1560, 24, 0, gScenarioBufferData60_RGB888_TO_Y, 50, gScenarioKernelData60_RGB888_TO_Y, 2},
{28, 6, 1680, 24, 0, gScenarioBufferData61_RGB888_TO_Y, 50, gScenarioKernelData61_RGB888_TO_Y, 2},
{30, 6, 1800, 24, 0, gScenarioBufferData62_RGB888_TO_Y, 50, gScenarioKernelData62_RGB888_TO_Y, 2},
{32, 6, 1920, 24, 0, gScenarioBufferData63_RGB888_TO_Y, 50, gScenarioKernelData63_RGB888_TO_Y, 2},
{2, 8, 160, 24, 0, gScenarioBufferData64_RGB888_TO_Y, 50, gScenarioKernelData64_RGB888_TO_Y, 2},
{4, 8, 320, 24, 0, gScenarioBufferData65_RGB888_TO_Y, 50, gScenarioKernelData65_RGB888_TO_Y, 2},
{6, 8, 480, 24, 0, gScenarioBufferData66_RGB888_TO_Y, 50, gScenarioKernelData66_RGB888_TO_Y, 2},
{8, 8, 640, 24, 0, gScenarioBufferData67_RGB888_TO_Y, 50, gScenarioKernelData67_RGB888_TO_Y, 2},
{10, 8, 800, 24, 0, gScenarioBufferData68_RGB888_TO_Y, 50, gScenarioKernelData68_RGB888_TO_Y, 2},
{12, 8, 960, 24, 0, gScenarioBufferData69_RGB888_TO_Y, 50, gScenarioKernelData69_RGB888_TO_Y, 2},
{14, 8, 1120, 24, 0, gScenarioBufferData70_RGB888_TO_Y, 50, gScenarioKernelData70_RGB888_TO_Y, 2},
{16, 8, 1280, 24, 0, gScenarioBufferData71_RGB888_TO_Y, 50, gScenarioKernelData71_RGB888_TO_Y, 2},
{18, 8, 1440, 24, 0, gScenarioBufferData72_RGB888_TO_Y, 50, gScenarioKernelData72_RGB888_TO_Y, 2},
{20, 8, 1600, 24, 0, gScenarioBufferData73_RGB888_TO_Y, 50, gScenarioKernelData73_RGB888_TO_Y, 2},
{22, 8, 1760, 24, 0, gScenarioBufferData74_RGB888_TO_Y, 50, gScenarioKernelData74_RGB888_TO_Y, 2},
{24, 8, 1920, 24, 0, gScenarioBufferData75_RGB888_TO_Y, 50, gScenarioKernelData75_RGB888_TO_Y, 2},
{26, 8, 2080, 24, 0, gScenarioBufferData76_RGB888_TO_Y, 50, gScenarioKernelData76_RGB888_TO_Y, 2},
{28, 8, 2240, 24, 0, gScenarioBufferData77_RGB888_TO_Y, 50, gScenarioKernelData77_RGB888_TO_Y, 2},
{30, 8, 2400, 24, 0, gScenarioBufferData78_RGB888_TO_Y, 50, gScenarioKernelData78_RGB888_TO_Y, 2},
{32, 8, 2560, 24, 0, gScenarioBufferData79_RGB888_TO_Y, 50, gScenarioKernelData79_RGB888_TO_Y, 2},
{2, 10, 200, 24, 0, gScenarioBufferData80_RGB888_TO_Y, 50, gScenarioKernelData80_RGB888_TO_Y, 2},
{4, 10, 400, 24, 0, gScenarioBufferData81_RGB888_TO_Y, 50, gScenarioKernelData81_RGB888_TO_Y, 2},
{6, 10, 600, 24, 0, gScenarioBufferData82_RGB888_TO_Y, 50, gScenarioKernelData82_RGB888_TO_Y, 2},
{8, 10, 800, 24, 0, gScenarioBufferData83_RGB888_TO_Y, 50, gScenarioKernelData83_RGB888_TO_Y, 2},
{10, 10, 1000, 24, 0, gScenarioBufferData84_RGB888_TO_Y, 50, gScenarioKernelData84_RGB888_TO_Y, 2},
{12, 10, 1200, 24, 0, gScenarioBufferData85_RGB888_TO_Y, 50, gScenarioKernelData85_RGB888_TO_Y, 2},
{14, 10, 1400, 24, 0, gScenarioBufferData86_RGB888_TO_Y, 50, gScenarioKernelData86_RGB888_TO_Y, 2},
{16, 10, 1600, 24, 0, gScenarioBufferData87_RGB888_TO_Y, 50, gScenarioKernelData87_RGB888_TO_Y, 2},
{18, 10, 1800, 24, 0, gScenarioBufferData88_RGB888_TO_Y, 50, gScenarioKernelData88_RGB888_TO_Y, 2},
{20, 10, 2000, 24, 0, gScenarioBufferData89_RGB888_TO_Y, 50, gScenarioKernelData89_RGB888_TO_Y, 2},
{22, 10, 2200, 24, 0, gScenarioBufferData90_RGB888_TO_Y, 50, gScenarioKernelData90_RGB888_TO_Y, 2},
{24, 10, 2400, 24, 0, gScenarioBufferData91_RGB888_TO_Y, 50, gScenarioKernelData91_RGB888_TO_Y, 2},
{26, 10, 2600, 24, 0, gScenarioBufferData92_RGB888_TO_Y, 50, gScenarioKernelData92_RGB888_TO_Y, 2},
{28, 10, 2800, 24, 0, gScenarioBufferData93_RGB888_TO_Y, 50, gScenarioKernelData93_RGB888_TO_Y, 2},
{30, 10, 3000, 24, 0, gScenarioBufferData94_RGB888_TO_Y, 50, gScenarioKernelData94_RGB888_TO_Y, 2},
{32, 10, 3200, 24, 0, gScenarioBufferData95_RGB888_TO_Y, 50, gScenarioKernelData95_RGB888_TO_Y, 2},
{2, 12, 240, 24, 0, gScenarioBufferData96_RGB888_TO_Y, 50, gScenarioKernelData96_RGB888_TO_Y, 2},
{4, 12, 480, 24, 0, gScenarioBufferData97_RGB888_TO_Y, 50, gScenarioKernelData97_RGB888_TO_Y, 2},
{6, 12, 720, 24, 0, gScenarioBufferData98_RGB888_TO_Y, 50, gScenarioKernelData98_RGB888_TO_Y, 2},
{8, 12, 960, 24, 0, gScenarioBufferData99_RGB888_TO_Y, 50, gScenarioKernelData99_RGB888_TO_Y, 2},
{10, 12, 1200, 24, 0, gScenarioBufferData100_RGB888_TO_Y, 50, gScenarioKernelData100_RGB888_TO_Y, 2},
{12, 12, 1440, 24, 0, gScenarioBufferData101_RGB888_TO_Y, 50, gScenarioKernelData101_RGB888_TO_Y, 2},
{14, 12, 1680, 24, 0, gScenarioBufferData102_RGB888_TO_Y, 50, gScenarioKernelData102_RGB888_TO_Y, 2},
{16, 12, 1920, 24, 0, gScenarioBufferData103_RGB888_TO_Y, 50, gScenarioKernelData103_RGB888_TO_Y, 2},
{18, 12, 2160, 24, 0, gScenarioBufferData104_RGB888_TO_Y, 50, gScenarioKernelData104_RGB888_TO_Y, 2},
{20, 12, 2400, 24, 0, gScenarioBufferData105_RGB888_TO_Y, 50, gScenarioKernelData105_RGB888_TO_Y, 2},
{22, 12, 2640, 24, 0, gScenarioBufferData106_RGB888_TO_Y, 50, gScenarioKernelData106_RGB888_TO_Y, 2},
{24, 12, 2880, 24, 0, gScenarioBufferData107_RGB888_TO_Y, 50, gScenarioKernelData107_RGB888_TO_Y, 2},
{26, 12, 3120, 24, 0, gScenarioBufferData108_RGB888_TO_Y, 50, gScenarioKernelData108_RGB888_TO_Y, 2},
{28, 12, 3360, 24, 0, gScenarioBufferData109_RGB888_TO_Y, 50, gScenarioKernelData109_RGB888_TO_Y, 2},
{30, 12, 3600, 24, 0, gScenarioBufferData110_RGB888_TO_Y, 50, gScenarioKernelData110_RGB888_TO_Y, 2},
{32, 12, 3840, 24, 0, gScenarioBufferData111_RGB888_TO_Y, 50, gScenarioKernelData111_RGB888_TO_Y, 2},
{2, 14, 280, 24, 0, gScenarioBufferData112_RGB888_TO_Y, 50, gScenarioKernelData112_RGB888_TO_Y, 2},
{4, 14, 560, 24, 0, gScenarioBufferData113_RGB888_TO_Y, 50, gScenarioKernelData113_RGB888_TO_Y, 2},
{6, 14, 840, 24, 0, gScenarioBufferData114_RGB888_TO_Y, 50, gScenarioKernelData114_RGB888_TO_Y, 2},
{8, 14, 1120, 24, 0, gScenarioBufferData115_RGB888_TO_Y, 50, gScenarioKernelData115_RGB888_TO_Y, 2},
{10, 14, 1400, 24, 0, gScenarioBufferData116_RGB888_TO_Y, 50, gScenarioKernelData116_RGB888_TO_Y, 2},
{12, 14, 1680, 24, 0, gScenarioBufferData117_RGB888_TO_Y, 50, gScenarioKernelData117_RGB888_TO_Y, 2},
{14, 14, 1960, 24, 0, gScenarioBufferData118_RGB888_TO_Y, 50, gScenarioKernelData118_RGB888_TO_Y, 2},
{16, 14, 2240, 24, 0, gScenarioBufferData119_RGB888_TO_Y, 50, gScenarioKernelData119_RGB888_TO_Y, 2},
{18, 14, 2520, 24, 0, gScenarioBufferData120_RGB888_TO_Y, 50, gScenarioKernelData120_RGB888_TO_Y, 2},
{20, 14, 2800, 24, 0, gScenarioBufferData121_RGB888_TO_Y, 50, gScenarioKernelData121_RGB888_TO_Y, 2},
{22, 14, 3080, 24, 0, gScenarioBufferData122_RGB888_TO_Y, 50, gScenarioKernelData122_RGB888_TO_Y, 2},
{24, 14, 3360, 24, 0, gScenarioBufferData123_RGB888_TO_Y, 50, gScenarioKernelData123_RGB888_TO_Y, 2},
{26, 14, 3640, 24, 0, gScenarioBufferData124_RGB888_TO_Y, 50, gScenarioKernelData124_RGB888_TO_Y, 2},
{2, 16, 320, 24, 0, gScenarioBufferData125_RGB888_TO_Y, 50, gScenarioKernelData125_RGB888_TO_Y, 2},
{4, 16, 640, 24, 0, gScenarioBufferData126_RGB888_TO_Y, 50, gScenarioKernelData126_RGB888_TO_Y, 2},
{6, 16, 960, 24, 0, gScenarioBufferData127_RGB888_TO_Y, 50, gScenarioKernelData127_RGB888_TO_Y, 2},
{8, 16, 1280, 24, 0, gScenarioBufferData128_RGB888_TO_Y, 50, gScenarioKernelData128_RGB888_TO_Y, 2},
{10, 16, 1600, 24, 0, gScenarioBufferData129_RGB888_TO_Y, 50, gScenarioKernelData129_RGB888_TO_Y, 2},
{12, 16, 1920, 24, 0, gScenarioBufferData130_RGB888_TO_Y, 50, gScenarioKernelData130_RGB888_TO_Y, 2},
{14, 16, 2240, 24, 0, gScenarioBufferData131_RGB888_TO_Y, 50, gScenarioKernelData131_RGB888_TO_Y, 2},
{16, 16, 2560, 24, 0, gScenarioBufferData132_RGB888_TO_Y, 50, gScenarioKernelData132_RGB888_TO_Y, 2},
{18, 16, 2880, 24, 0, gScenarioBufferData133_RGB888_TO_Y, 50, gScenarioKernelData133_RGB888_TO_Y, 2},
{20, 16, 3200, 24, 0, gScenarioBufferData134_RGB888_TO_Y, 50, gScenarioKernelData134_RGB888_TO_Y, 2},
{22, 16, 3520, 24, 0, gScenarioBufferData135_RGB888_TO_Y, 50, gScenarioKernelData135_RGB888_TO_Y, 2},
{24, 16, 3840, 24, 0, gScenarioBufferData136_RGB888_TO_Y, 50, gScenarioKernelData136_RGB888_TO_Y, 2},
{2, 18, 360, 24, 0, gScenarioBufferData137_RGB888_TO_Y, 50, gScenarioKernelData137_RGB888_TO_Y, 2},
{4, 18, 720, 24, 0, gScenarioBufferData138_RGB888_TO_Y, 50, gScenarioKernelData138_RGB888_TO_Y, 2},
{6, 18, 1080, 24, 0, gScenarioBufferData139_RGB888_TO_Y, 50, gScenarioKernelData139_RGB888_TO_Y, 2},
{8, 18, 1440, 24, 0, gScenarioBufferData140_RGB888_TO_Y, 50, gScenarioKernelData140_RGB888_TO_Y, 2},
{10, 18, 1800, 24, 0, gScenarioBufferData141_RGB888_TO_Y, 50, gScenarioKernelData141_RGB888_TO_Y, 2},
{12, 18, 2160, 24, 0, gScenarioBufferData142_RGB888_TO_Y, 50, gScenarioKernelData142_RGB888_TO_Y, 2},
{14, 18, 2520, 24, 0, gScenarioBufferData143_RGB888_TO_Y, 50, gScenarioKernelData143_RGB888_TO_Y, 2},
{16, 18, 2880, 24, 0, gScenarioBufferData144_RGB888_TO_Y, 50, gScenarioKernelData144_RGB888_TO_Y, 2},
{18, 18, 3240, 24, 0, gScenarioBufferData145_RGB888_TO_Y, 50, gScenarioKernelData145_RGB888_TO_Y, 2},
{20, 18, 3600, 24, 0, gScenarioBufferData146_RGB888_TO_Y, 50, gScenarioKernelData146_RGB888_TO_Y, 2},
{2, 20, 400, 24, 0, gScenarioBufferData147_RGB888_TO_Y, 50, gScenarioKernelData147_RGB888_TO_Y, 2},
{4, 20, 800, 24, 0, gScenarioBufferData148_RGB888_TO_Y, 50, gScenarioKernelData148_RGB888_TO_Y, 2},
{6, 20, 1200, 24, 0, gScenarioBufferData149_RGB888_TO_Y, 50, gScenarioKernelData149_RGB888_TO_Y, 2},
{8, 20, 1600, 24, 0, gScenarioBufferData150_RGB888_TO_Y, 50, gScenarioKernelData150_RGB888_TO_Y, 2},
{10, 20, 2000, 24, 0, gScenarioBufferData151_RGB888_TO_Y, 50, gScenarioKernelData151_RGB888_TO_Y, 2},
{12, 20, 2400, 24, 0, gScenarioBufferData152_RGB888_TO_Y, 50, gScenarioKernelData152_RGB888_TO_Y, 2},
{14, 20, 2800, 24, 0, gScenarioBufferData153_RGB888_TO_Y, 50, gScenarioKernelData153_RGB888_TO_Y, 2},
{16, 20, 3200, 24, 0, gScenarioBufferData154_RGB888_TO_Y, 50, gScenarioKernelData154_RGB888_TO_Y, 2},
{18, 20, 3600, 24, 0, gScenarioBufferData155_RGB888_TO_Y, 50, gScenarioKernelData155_RGB888_TO_Y, 2},
{2, 22, 440, 24, 0, gScenarioBufferData156_RGB888_TO_Y, 50, gScenarioKernelData156_RGB888_TO_Y, 2},
{4, 22, 880, 24, 0, gScenarioBufferData157_RGB888_TO_Y, 50, gScenarioKernelData157_RGB888_TO_Y, 2},
{6, 22, 1320, 24, 0, gScenarioBufferData158_RGB888_TO_Y, 50, gScenarioKernelData158_RGB888_TO_Y, 2},
{8, 22, 1760, 24, 0, gScenarioBufferData159_RGB888_TO_Y, 50, gScenarioKernelData159_RGB888_TO_Y, 2},
{10, 22, 2200, 24, 0, gScenarioBufferData160_RGB888_TO_Y, 50, gScenarioKernelData160_RGB888_TO_Y, 2},
{12, 22, 2640, 24, 0, gScenarioBufferData161_RGB888_TO_Y, 50, gScenarioKernelData161_RGB888_TO_Y, 2},
{14, 22, 3080, 24, 0, gScenarioBufferData162_RGB888_TO_Y, 50, gScenarioKernelData162_RGB888_TO_Y, 2},
{16, 22, 3520, 24, 0, gScenarioBufferData163_RGB888_TO_Y, 50, gScenarioKernelData163_RGB888_TO_Y, 2},
{2, 24, 480, 24, 0, gScenarioBufferData164_RGB888_TO_Y, 50, gScenarioKernelData164_RGB888_TO_Y, 2},
{4, 24, 960, 24, 0, gScenarioBufferData165_RGB888_TO_Y, 50, gScenarioKernelData165_RGB888_TO_Y, 2},
{6, 24, 1440, 24, 0, gScenarioBufferData166_RGB888_TO_Y, 50, gScenarioKernelData166_RGB888_TO_Y, 2},
{8, 24, 1920, 24, 0, gScenarioBufferData167_RGB888_TO_Y, 50, gScenarioKernelData167_RGB888_TO_Y, 2},
{10, 24, 2400, 24, 0, gScenarioBufferData168_RGB888_TO_Y, 50, gScenarioKernelData168_RGB888_TO_Y, 2},
{12, 24, 2880, 24, 0, gScenarioBufferData169_RGB888_TO_Y, 50, gScenarioKernelData169_RGB888_TO_Y, 2},
{14, 24, 3360, 24, 0, gScenarioBufferData170_RGB888_TO_Y, 50, gScenarioKernelData170_RGB888_TO_Y, 2},
{16, 24, 3840, 24, 0, gScenarioBufferData171_RGB888_TO_Y, 50, gScenarioKernelData171_RGB888_TO_Y, 2},
{2, 26, 520, 24, 0, gScenarioBufferData172_RGB888_TO_Y, 50, gScenarioKernelData172_RGB888_TO_Y, 2},
{4, 26, 1040, 24, 0, gScenarioBufferData173_RGB888_TO_Y, 50, gScenarioKernelData173_RGB888_TO_Y, 2},
{6, 26, 1560, 24, 0, gScenarioBufferData174_RGB888_TO_Y, 50, gScenarioKernelData174_RGB888_TO_Y, 2},
{8, 26, 2080, 24, 0, gScenarioBufferData175_RGB888_TO_Y, 50, gScenarioKernelData175_RGB888_TO_Y, 2},
{10, 26, 2600, 24, 0, gScenarioBufferData176_RGB888_TO_Y, 50, gScenarioKernelData176_RGB888_TO_Y, 2},
{12, 26, 3120, 24, 0, gScenarioBufferData177_RGB888_TO_Y, 50, gScenarioKernelData177_RGB888_TO_Y, 2},
{14, 26, 3640, 24, 0, gScenarioBufferData178_RGB888_TO_Y, 50, gScenarioKernelData178_RGB888_TO_Y, 2},
{2, 28, 560, 24, 0, gScenarioBufferData179_RGB888_TO_Y, 50, gScenarioKernelData179_RGB888_TO_Y, 2},
{4, 28, 1120, 24, 0, gScenarioBufferData180_RGB888_TO_Y, 50, gScenarioKernelData180_RGB888_TO_Y, 2},
{6, 28, 1680, 24, 0, gScenarioBufferData181_RGB888_TO_Y, 50, gScenarioKernelData181_RGB888_TO_Y, 2},
{8, 28, 2240, 24, 0, gScenarioBufferData182_RGB888_TO_Y, 50, gScenarioKernelData182_RGB888_TO_Y, 2},
{10, 28, 2800, 24, 0, gScenarioBufferData183_RGB888_TO_Y, 50, gScenarioKernelData183_RGB888_TO_Y, 2},
{12, 28, 3360, 24, 0, gScenarioBufferData184_RGB888_TO_Y, 50, gScenarioKernelData184_RGB888_TO_Y, 2},
{2, 30, 600, 24, 0, gScenarioBufferData185_RGB888_TO_Y, 50, gScenarioKernelData185_RGB888_TO_Y, 2},
{4, 30, 1200, 24, 0, gScenarioBufferData186_RGB888_TO_Y, 50, gScenarioKernelData186_RGB888_TO_Y, 2},
{6, 30, 1800, 24, 0, gScenarioBufferData187_RGB888_TO_Y, 50, gScenarioKernelData187_RGB888_TO_Y, 2},
{8, 30, 2400, 24, 0, gScenarioBufferData188_RGB888_TO_Y, 50, gScenarioKernelData188_RGB888_TO_Y, 2},
{10, 30, 3000, 24, 0, gScenarioBufferData189_RGB888_TO_Y, 50, gScenarioKernelData189_RGB888_TO_Y, 2},
{12, 30, 3600, 24, 0, gScenarioBufferData190_RGB888_TO_Y, 50, gScenarioKernelData190_RGB888_TO_Y, 2},
{2, 32, 640, 24, 0, gScenarioBufferData191_RGB888_TO_Y, 50, gScenarioKernelData191_RGB888_TO_Y, 2},
{4, 32, 1280, 24, 0, gScenarioBufferData192_RGB888_TO_Y, 50, gScenarioKernelData192_RGB888_TO_Y, 2},
{6, 32, 1920, 24, 0, gScenarioBufferData193_RGB888_TO_Y, 50, gScenarioKernelData193_RGB888_TO_Y, 2},
{8, 32, 2560, 24, 0, gScenarioBufferData194_RGB888_TO_Y, 50, gScenarioKernelData194_RGB888_TO_Y, 2},
{10, 32, 3200, 24, 0, gScenarioBufferData195_RGB888_TO_Y, 50, gScenarioKernelData195_RGB888_TO_Y, 2},
{12, 32, 3840, 24, 0, gScenarioBufferData196_RGB888_TO_Y, 50, gScenarioKernelData196_RGB888_TO_Y, 2}
};

static acf_scenario_list gScenarioList_RGB888_TO_Y = {
197, //number of scenarios
gScenarioArray_RGB888_TO_Y};
//**************************************************************

class RGB888_TO_Y : public ACF_Process_APU
{
public:
   RGB888_TO_Y(int32_t apex_id = 0) : ACF_Process_APU(apex_id)
   {} 

   int32_t Initialize()
   {
      int32_t lRetVal = 0;

      if (!Initialized()) //initialization steps that only need to occur once
      {
         SetProcessIdentifier("RGB888_TO_Y");
         SetApuLoadInfo(RGB888_TO_Y_LOAD_SEGMENTS,
                        RGB888_TO_Y_LOAD_PMEM, RGB888_TO_Y_LOAD_PMEM_SIZE,
                        RGB888_TO_Y_LOAD_DMEM, RGB888_TO_Y_LOAD_DMEM_SIZE,
                        0, 0); //assuming _LOAD_CMEM does not exist

         //***NOTE: the order in which the following ports are added is meaningful; do not change!

         AddPort("INPUT_0", ICP_DATATYPE_08U, 4, 1, 2, 1, 0, 0, 0, 0, 0, 0, 0, 0x0);
         AddPort("R2Y", ICP_DATATYPE_32S, 1, 1, 1, 1, 0, 1, 1, 0, 1, 0, 2);
         AddPort("G2Y", ICP_DATATYPE_32S, 1, 1, 1, 1, 0, 1, 1, 0, 1, 0, 3);
         AddPort("B2Y", ICP_DATATYPE_32S, 1, 1, 1, 1, 0, 1, 1, 0, 1, 0, 4);
         AddPort("OUTPUT_0", ICP_DATATYPE_08U, 1, 1, 2, 1, 1, 0, 0, 0, 0, 0, 1);

         CfgScenarios(&gScenarioList_RGB888_TO_Y);

         FlagAsInitialized();
      }

      lRetVal = SelectApuConfiguration(mApuCfg, mApexId); //by default mApuCfg = ACF_APU_CFG__APEX0_DEFAULT and mApexId = 0

      return lRetVal;
   }
};

#endif //_ACF_PROCESS_APU_RGB888_TO_Y
