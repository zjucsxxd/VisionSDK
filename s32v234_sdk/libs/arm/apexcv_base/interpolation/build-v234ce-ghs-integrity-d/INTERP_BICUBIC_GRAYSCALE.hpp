#ifndef _ACF_PROCESS_APU_INTERP_BICUBIC_GRAYSCALE
#define _ACF_PROCESS_APU_INTERP_BICUBIC_GRAYSCALE

#include <acf_process_apu.h>
#include <INTERP_BICUBIC_GRAYSCALE_APU_LOAD.h> //APU load associated with this process
#include <stdint.h>


//SCENARIO LIST*************************************************
static acf_scenario_buffer_data gScenarioBufferData0_INTERP_BICUBIC_GRAYSCALE[] = {{2, 1, 7, 0, 0x2222}, {2, 1, 2, 2, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData1_INTERP_BICUBIC_GRAYSCALE[] = {{4, 1, 7, 0, 0x2222}, {4, 1, 2, 2, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData2_INTERP_BICUBIC_GRAYSCALE[] = {{6, 1, 7, 0, 0x2222}, {6, 1, 2, 2, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData3_INTERP_BICUBIC_GRAYSCALE[] = {{8, 1, 7, 0, 0x2222}, {8, 1, 2, 2, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData4_INTERP_BICUBIC_GRAYSCALE[] = {{10, 1, 7, 0, 0x2222}, {10, 1, 2, 2, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData5_INTERP_BICUBIC_GRAYSCALE[] = {{12, 1, 7, 0, 0x2222}, {12, 1, 2, 2, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData6_INTERP_BICUBIC_GRAYSCALE[] = {{14, 1, 7, 0, 0x2222}, {14, 1, 2, 2, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData7_INTERP_BICUBIC_GRAYSCALE[] = {{16, 1, 7, 0, 0x2222}, {16, 1, 2, 2, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData8_INTERP_BICUBIC_GRAYSCALE[] = {{18, 1, 7, 0, 0x2222}, {18, 1, 2, 2, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData9_INTERP_BICUBIC_GRAYSCALE[] = {{20, 1, 7, 0, 0x2222}, {20, 1, 2, 2, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData10_INTERP_BICUBIC_GRAYSCALE[] = {{22, 1, 7, 0, 0x2222}, {22, 1, 2, 2, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData11_INTERP_BICUBIC_GRAYSCALE[] = {{24, 1, 7, 0, 0x2222}, {24, 1, 2, 2, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData12_INTERP_BICUBIC_GRAYSCALE[] = {{26, 1, 7, 0, 0x2222}, {26, 1, 2, 2, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData13_INTERP_BICUBIC_GRAYSCALE[] = {{28, 1, 7, 0, 0x2222}, {28, 1, 2, 2, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData14_INTERP_BICUBIC_GRAYSCALE[] = {{30, 1, 7, 0, 0x2222}, {30, 1, 2, 2, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData15_INTERP_BICUBIC_GRAYSCALE[] = {{32, 1, 7, 0, 0x2222}, {32, 1, 2, 2, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData16_INTERP_BICUBIC_GRAYSCALE[] = {{48, 1, 7, 0, 0x2222}, {48, 1, 2, 2, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData17_INTERP_BICUBIC_GRAYSCALE[] = {{64, 1, 7, 0, 0x2222}, {64, 1, 2, 2, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData18_INTERP_BICUBIC_GRAYSCALE[] = {{96, 1, 7, 0, 0x2222}, {96, 1, 2, 2, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData19_INTERP_BICUBIC_GRAYSCALE[] = {{112, 1, 7, 0, 0x2222}, {112, 1, 2, 2, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData20_INTERP_BICUBIC_GRAYSCALE[] = {{128, 1, 7, 0, 0x2222}, {128, 1, 2, 2, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData21_INTERP_BICUBIC_GRAYSCALE[] = {{2, 2, 4, 0, 0x2222}, {2, 2, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData22_INTERP_BICUBIC_GRAYSCALE[] = {{4, 2, 4, 0, 0x2222}, {4, 2, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData23_INTERP_BICUBIC_GRAYSCALE[] = {{6, 2, 4, 0, 0x2222}, {6, 2, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData24_INTERP_BICUBIC_GRAYSCALE[] = {{8, 2, 4, 0, 0x2222}, {8, 2, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData25_INTERP_BICUBIC_GRAYSCALE[] = {{10, 2, 4, 0, 0x2222}, {10, 2, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData26_INTERP_BICUBIC_GRAYSCALE[] = {{12, 2, 4, 0, 0x2222}, {12, 2, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData27_INTERP_BICUBIC_GRAYSCALE[] = {{14, 2, 4, 0, 0x2222}, {14, 2, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData28_INTERP_BICUBIC_GRAYSCALE[] = {{16, 2, 4, 0, 0x2222}, {16, 2, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData29_INTERP_BICUBIC_GRAYSCALE[] = {{18, 2, 4, 0, 0x2222}, {18, 2, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData30_INTERP_BICUBIC_GRAYSCALE[] = {{20, 2, 4, 0, 0x2222}, {20, 2, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData31_INTERP_BICUBIC_GRAYSCALE[] = {{22, 2, 4, 0, 0x2222}, {22, 2, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData32_INTERP_BICUBIC_GRAYSCALE[] = {{24, 2, 4, 0, 0x2222}, {24, 2, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData33_INTERP_BICUBIC_GRAYSCALE[] = {{26, 2, 4, 0, 0x2222}, {26, 2, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData34_INTERP_BICUBIC_GRAYSCALE[] = {{28, 2, 4, 0, 0x2222}, {28, 2, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData35_INTERP_BICUBIC_GRAYSCALE[] = {{30, 2, 4, 0, 0x2222}, {30, 2, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData36_INTERP_BICUBIC_GRAYSCALE[] = {{32, 2, 4, 0, 0x2222}, {32, 2, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData37_INTERP_BICUBIC_GRAYSCALE[] = {{48, 2, 4, 0, 0x2222}, {48, 2, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData38_INTERP_BICUBIC_GRAYSCALE[] = {{64, 2, 4, 0, 0x2222}, {64, 2, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData39_INTERP_BICUBIC_GRAYSCALE[] = {{96, 2, 4, 0, 0x2222}, {96, 2, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData40_INTERP_BICUBIC_GRAYSCALE[] = {{112, 2, 4, 0, 0x2222}, {112, 2, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData41_INTERP_BICUBIC_GRAYSCALE[] = {{128, 2, 4, 0, 0x2222}, {128, 2, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData42_INTERP_BICUBIC_GRAYSCALE[] = {{2, 4, 4, 0, 0x2222}, {2, 4, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData43_INTERP_BICUBIC_GRAYSCALE[] = {{4, 4, 4, 0, 0x2222}, {4, 4, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData44_INTERP_BICUBIC_GRAYSCALE[] = {{6, 4, 4, 0, 0x2222}, {6, 4, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData45_INTERP_BICUBIC_GRAYSCALE[] = {{8, 4, 4, 0, 0x2222}, {8, 4, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData46_INTERP_BICUBIC_GRAYSCALE[] = {{10, 4, 4, 0, 0x2222}, {10, 4, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData47_INTERP_BICUBIC_GRAYSCALE[] = {{12, 4, 4, 0, 0x2222}, {12, 4, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData48_INTERP_BICUBIC_GRAYSCALE[] = {{14, 4, 4, 0, 0x2222}, {14, 4, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData49_INTERP_BICUBIC_GRAYSCALE[] = {{16, 4, 4, 0, 0x2222}, {16, 4, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData50_INTERP_BICUBIC_GRAYSCALE[] = {{18, 4, 4, 0, 0x2222}, {18, 4, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData51_INTERP_BICUBIC_GRAYSCALE[] = {{20, 4, 4, 0, 0x2222}, {20, 4, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData52_INTERP_BICUBIC_GRAYSCALE[] = {{22, 4, 4, 0, 0x2222}, {22, 4, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData53_INTERP_BICUBIC_GRAYSCALE[] = {{24, 4, 4, 0, 0x2222}, {24, 4, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData54_INTERP_BICUBIC_GRAYSCALE[] = {{26, 4, 4, 0, 0x2222}, {26, 4, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData55_INTERP_BICUBIC_GRAYSCALE[] = {{28, 4, 4, 0, 0x2222}, {28, 4, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData56_INTERP_BICUBIC_GRAYSCALE[] = {{30, 4, 4, 0, 0x2222}, {30, 4, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData57_INTERP_BICUBIC_GRAYSCALE[] = {{32, 4, 4, 0, 0x2222}, {32, 4, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData58_INTERP_BICUBIC_GRAYSCALE[] = {{48, 4, 4, 0, 0x2222}, {48, 4, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData59_INTERP_BICUBIC_GRAYSCALE[] = {{64, 4, 4, 0, 0x2222}, {64, 4, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData60_INTERP_BICUBIC_GRAYSCALE[] = {{96, 4, 4, 0, 0x2222}, {96, 4, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData61_INTERP_BICUBIC_GRAYSCALE[] = {{112, 4, 4, 0, 0x2222}, {112, 4, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData62_INTERP_BICUBIC_GRAYSCALE[] = {{128, 4, 4, 0, 0x2222}, {128, 4, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData63_INTERP_BICUBIC_GRAYSCALE[] = {{2, 6, 4, 0, 0x2222}, {2, 6, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData64_INTERP_BICUBIC_GRAYSCALE[] = {{4, 6, 4, 0, 0x2222}, {4, 6, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData65_INTERP_BICUBIC_GRAYSCALE[] = {{6, 6, 4, 0, 0x2222}, {6, 6, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData66_INTERP_BICUBIC_GRAYSCALE[] = {{8, 6, 4, 0, 0x2222}, {8, 6, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData67_INTERP_BICUBIC_GRAYSCALE[] = {{10, 6, 4, 0, 0x2222}, {10, 6, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData68_INTERP_BICUBIC_GRAYSCALE[] = {{12, 6, 4, 0, 0x2222}, {12, 6, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData69_INTERP_BICUBIC_GRAYSCALE[] = {{14, 6, 4, 0, 0x2222}, {14, 6, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData70_INTERP_BICUBIC_GRAYSCALE[] = {{16, 6, 4, 0, 0x2222}, {16, 6, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData71_INTERP_BICUBIC_GRAYSCALE[] = {{18, 6, 4, 0, 0x2222}, {18, 6, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData72_INTERP_BICUBIC_GRAYSCALE[] = {{20, 6, 4, 0, 0x2222}, {20, 6, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData73_INTERP_BICUBIC_GRAYSCALE[] = {{22, 6, 4, 0, 0x2222}, {22, 6, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData74_INTERP_BICUBIC_GRAYSCALE[] = {{24, 6, 4, 0, 0x2222}, {24, 6, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData75_INTERP_BICUBIC_GRAYSCALE[] = {{26, 6, 4, 0, 0x2222}, {26, 6, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData76_INTERP_BICUBIC_GRAYSCALE[] = {{28, 6, 4, 0, 0x2222}, {28, 6, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData77_INTERP_BICUBIC_GRAYSCALE[] = {{30, 6, 4, 0, 0x2222}, {30, 6, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData78_INTERP_BICUBIC_GRAYSCALE[] = {{32, 6, 4, 0, 0x2222}, {32, 6, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData79_INTERP_BICUBIC_GRAYSCALE[] = {{48, 6, 4, 0, 0x2222}, {48, 6, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData80_INTERP_BICUBIC_GRAYSCALE[] = {{64, 6, 4, 0, 0x2222}, {64, 6, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData81_INTERP_BICUBIC_GRAYSCALE[] = {{2, 8, 4, 0, 0x2222}, {2, 8, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData82_INTERP_BICUBIC_GRAYSCALE[] = {{4, 8, 4, 0, 0x2222}, {4, 8, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData83_INTERP_BICUBIC_GRAYSCALE[] = {{6, 8, 4, 0, 0x2222}, {6, 8, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData84_INTERP_BICUBIC_GRAYSCALE[] = {{8, 8, 4, 0, 0x2222}, {8, 8, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData85_INTERP_BICUBIC_GRAYSCALE[] = {{10, 8, 4, 0, 0x2222}, {10, 8, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData86_INTERP_BICUBIC_GRAYSCALE[] = {{12, 8, 4, 0, 0x2222}, {12, 8, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData87_INTERP_BICUBIC_GRAYSCALE[] = {{14, 8, 4, 0, 0x2222}, {14, 8, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData88_INTERP_BICUBIC_GRAYSCALE[] = {{16, 8, 4, 0, 0x2222}, {16, 8, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData89_INTERP_BICUBIC_GRAYSCALE[] = {{18, 8, 4, 0, 0x2222}, {18, 8, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData90_INTERP_BICUBIC_GRAYSCALE[] = {{20, 8, 4, 0, 0x2222}, {20, 8, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData91_INTERP_BICUBIC_GRAYSCALE[] = {{22, 8, 4, 0, 0x2222}, {22, 8, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData92_INTERP_BICUBIC_GRAYSCALE[] = {{24, 8, 4, 0, 0x2222}, {24, 8, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData93_INTERP_BICUBIC_GRAYSCALE[] = {{26, 8, 4, 0, 0x2222}, {26, 8, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData94_INTERP_BICUBIC_GRAYSCALE[] = {{28, 8, 4, 0, 0x2222}, {28, 8, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData95_INTERP_BICUBIC_GRAYSCALE[] = {{30, 8, 4, 0, 0x2222}, {30, 8, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData96_INTERP_BICUBIC_GRAYSCALE[] = {{32, 8, 4, 0, 0x2222}, {32, 8, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData97_INTERP_BICUBIC_GRAYSCALE[] = {{48, 8, 4, 0, 0x2222}, {48, 8, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData98_INTERP_BICUBIC_GRAYSCALE[] = {{64, 8, 4, 0, 0x2222}, {64, 8, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData99_INTERP_BICUBIC_GRAYSCALE[] = {{2, 10, 4, 0, 0x2222}, {2, 10, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData100_INTERP_BICUBIC_GRAYSCALE[] = {{4, 10, 4, 0, 0x2222}, {4, 10, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData101_INTERP_BICUBIC_GRAYSCALE[] = {{6, 10, 4, 0, 0x2222}, {6, 10, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData102_INTERP_BICUBIC_GRAYSCALE[] = {{8, 10, 4, 0, 0x2222}, {8, 10, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData103_INTERP_BICUBIC_GRAYSCALE[] = {{10, 10, 4, 0, 0x2222}, {10, 10, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData104_INTERP_BICUBIC_GRAYSCALE[] = {{12, 10, 4, 0, 0x2222}, {12, 10, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData105_INTERP_BICUBIC_GRAYSCALE[] = {{14, 10, 4, 0, 0x2222}, {14, 10, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData106_INTERP_BICUBIC_GRAYSCALE[] = {{16, 10, 4, 0, 0x2222}, {16, 10, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData107_INTERP_BICUBIC_GRAYSCALE[] = {{18, 10, 4, 0, 0x2222}, {18, 10, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData108_INTERP_BICUBIC_GRAYSCALE[] = {{20, 10, 4, 0, 0x2222}, {20, 10, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData109_INTERP_BICUBIC_GRAYSCALE[] = {{22, 10, 4, 0, 0x2222}, {22, 10, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData110_INTERP_BICUBIC_GRAYSCALE[] = {{24, 10, 4, 0, 0x2222}, {24, 10, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData111_INTERP_BICUBIC_GRAYSCALE[] = {{26, 10, 4, 0, 0x2222}, {26, 10, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData112_INTERP_BICUBIC_GRAYSCALE[] = {{28, 10, 4, 0, 0x2222}, {28, 10, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData113_INTERP_BICUBIC_GRAYSCALE[] = {{30, 10, 4, 0, 0x2222}, {30, 10, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData114_INTERP_BICUBIC_GRAYSCALE[] = {{32, 10, 4, 0, 0x2222}, {32, 10, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData115_INTERP_BICUBIC_GRAYSCALE[] = {{48, 10, 4, 0, 0x2222}, {48, 10, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData116_INTERP_BICUBIC_GRAYSCALE[] = {{2, 12, 4, 0, 0x2222}, {2, 12, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData117_INTERP_BICUBIC_GRAYSCALE[] = {{4, 12, 4, 0, 0x2222}, {4, 12, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData118_INTERP_BICUBIC_GRAYSCALE[] = {{6, 12, 4, 0, 0x2222}, {6, 12, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData119_INTERP_BICUBIC_GRAYSCALE[] = {{8, 12, 4, 0, 0x2222}, {8, 12, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData120_INTERP_BICUBIC_GRAYSCALE[] = {{10, 12, 4, 0, 0x2222}, {10, 12, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData121_INTERP_BICUBIC_GRAYSCALE[] = {{12, 12, 4, 0, 0x2222}, {12, 12, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData122_INTERP_BICUBIC_GRAYSCALE[] = {{14, 12, 4, 0, 0x2222}, {14, 12, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData123_INTERP_BICUBIC_GRAYSCALE[] = {{16, 12, 4, 0, 0x2222}, {16, 12, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData124_INTERP_BICUBIC_GRAYSCALE[] = {{18, 12, 4, 0, 0x2222}, {18, 12, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData125_INTERP_BICUBIC_GRAYSCALE[] = {{20, 12, 4, 0, 0x2222}, {20, 12, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData126_INTERP_BICUBIC_GRAYSCALE[] = {{22, 12, 4, 0, 0x2222}, {22, 12, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData127_INTERP_BICUBIC_GRAYSCALE[] = {{24, 12, 4, 0, 0x2222}, {24, 12, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData128_INTERP_BICUBIC_GRAYSCALE[] = {{26, 12, 4, 0, 0x2222}, {26, 12, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData129_INTERP_BICUBIC_GRAYSCALE[] = {{28, 12, 4, 0, 0x2222}, {28, 12, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData130_INTERP_BICUBIC_GRAYSCALE[] = {{30, 12, 4, 0, 0x2222}, {30, 12, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData131_INTERP_BICUBIC_GRAYSCALE[] = {{32, 12, 4, 0, 0x2222}, {32, 12, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData132_INTERP_BICUBIC_GRAYSCALE[] = {{2, 14, 4, 0, 0x2222}, {2, 14, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData133_INTERP_BICUBIC_GRAYSCALE[] = {{4, 14, 4, 0, 0x2222}, {4, 14, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData134_INTERP_BICUBIC_GRAYSCALE[] = {{6, 14, 4, 0, 0x2222}, {6, 14, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData135_INTERP_BICUBIC_GRAYSCALE[] = {{8, 14, 4, 0, 0x2222}, {8, 14, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData136_INTERP_BICUBIC_GRAYSCALE[] = {{10, 14, 4, 0, 0x2222}, {10, 14, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData137_INTERP_BICUBIC_GRAYSCALE[] = {{12, 14, 4, 0, 0x2222}, {12, 14, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData138_INTERP_BICUBIC_GRAYSCALE[] = {{14, 14, 4, 0, 0x2222}, {14, 14, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData139_INTERP_BICUBIC_GRAYSCALE[] = {{16, 14, 4, 0, 0x2222}, {16, 14, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData140_INTERP_BICUBIC_GRAYSCALE[] = {{18, 14, 4, 0, 0x2222}, {18, 14, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData141_INTERP_BICUBIC_GRAYSCALE[] = {{20, 14, 4, 0, 0x2222}, {20, 14, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData142_INTERP_BICUBIC_GRAYSCALE[] = {{22, 14, 4, 0, 0x2222}, {22, 14, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData143_INTERP_BICUBIC_GRAYSCALE[] = {{24, 14, 4, 0, 0x2222}, {24, 14, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData144_INTERP_BICUBIC_GRAYSCALE[] = {{26, 14, 4, 0, 0x2222}, {26, 14, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData145_INTERP_BICUBIC_GRAYSCALE[] = {{28, 14, 4, 0, 0x2222}, {28, 14, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData146_INTERP_BICUBIC_GRAYSCALE[] = {{30, 14, 4, 0, 0x2222}, {30, 14, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData147_INTERP_BICUBIC_GRAYSCALE[] = {{32, 14, 4, 0, 0x2222}, {32, 14, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData148_INTERP_BICUBIC_GRAYSCALE[] = {{2, 16, 4, 0, 0x2222}, {2, 16, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData149_INTERP_BICUBIC_GRAYSCALE[] = {{4, 16, 4, 0, 0x2222}, {4, 16, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData150_INTERP_BICUBIC_GRAYSCALE[] = {{6, 16, 4, 0, 0x2222}, {6, 16, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData151_INTERP_BICUBIC_GRAYSCALE[] = {{8, 16, 4, 0, 0x2222}, {8, 16, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData152_INTERP_BICUBIC_GRAYSCALE[] = {{10, 16, 4, 0, 0x2222}, {10, 16, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData153_INTERP_BICUBIC_GRAYSCALE[] = {{12, 16, 4, 0, 0x2222}, {12, 16, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData154_INTERP_BICUBIC_GRAYSCALE[] = {{14, 16, 4, 0, 0x2222}, {14, 16, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData155_INTERP_BICUBIC_GRAYSCALE[] = {{16, 16, 4, 0, 0x2222}, {16, 16, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData156_INTERP_BICUBIC_GRAYSCALE[] = {{18, 16, 4, 0, 0x2222}, {18, 16, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData157_INTERP_BICUBIC_GRAYSCALE[] = {{20, 16, 4, 0, 0x2222}, {20, 16, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData158_INTERP_BICUBIC_GRAYSCALE[] = {{22, 16, 4, 0, 0x2222}, {22, 16, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData159_INTERP_BICUBIC_GRAYSCALE[] = {{24, 16, 4, 0, 0x2222}, {24, 16, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData160_INTERP_BICUBIC_GRAYSCALE[] = {{26, 16, 4, 0, 0x2222}, {26, 16, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData161_INTERP_BICUBIC_GRAYSCALE[] = {{28, 16, 4, 0, 0x2222}, {28, 16, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData162_INTERP_BICUBIC_GRAYSCALE[] = {{30, 16, 4, 0, 0x2222}, {30, 16, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData163_INTERP_BICUBIC_GRAYSCALE[] = {{32, 16, 4, 0, 0x2222}, {32, 16, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData164_INTERP_BICUBIC_GRAYSCALE[] = {{2, 18, 4, 0, 0x2222}, {2, 18, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData165_INTERP_BICUBIC_GRAYSCALE[] = {{4, 18, 4, 0, 0x2222}, {4, 18, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData166_INTERP_BICUBIC_GRAYSCALE[] = {{6, 18, 4, 0, 0x2222}, {6, 18, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData167_INTERP_BICUBIC_GRAYSCALE[] = {{8, 18, 4, 0, 0x2222}, {8, 18, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData168_INTERP_BICUBIC_GRAYSCALE[] = {{10, 18, 4, 0, 0x2222}, {10, 18, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData169_INTERP_BICUBIC_GRAYSCALE[] = {{12, 18, 4, 0, 0x2222}, {12, 18, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData170_INTERP_BICUBIC_GRAYSCALE[] = {{14, 18, 4, 0, 0x2222}, {14, 18, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData171_INTERP_BICUBIC_GRAYSCALE[] = {{16, 18, 4, 0, 0x2222}, {16, 18, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData172_INTERP_BICUBIC_GRAYSCALE[] = {{18, 18, 4, 0, 0x2222}, {18, 18, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData173_INTERP_BICUBIC_GRAYSCALE[] = {{20, 18, 4, 0, 0x2222}, {20, 18, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData174_INTERP_BICUBIC_GRAYSCALE[] = {{22, 18, 4, 0, 0x2222}, {22, 18, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData175_INTERP_BICUBIC_GRAYSCALE[] = {{24, 18, 4, 0, 0x2222}, {24, 18, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData176_INTERP_BICUBIC_GRAYSCALE[] = {{26, 18, 4, 0, 0x2222}, {26, 18, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData177_INTERP_BICUBIC_GRAYSCALE[] = {{28, 18, 4, 0, 0x2222}, {28, 18, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData178_INTERP_BICUBIC_GRAYSCALE[] = {{30, 18, 4, 0, 0x2222}, {30, 18, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData179_INTERP_BICUBIC_GRAYSCALE[] = {{2, 20, 4, 0, 0x2222}, {2, 20, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData180_INTERP_BICUBIC_GRAYSCALE[] = {{4, 20, 4, 0, 0x2222}, {4, 20, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData181_INTERP_BICUBIC_GRAYSCALE[] = {{6, 20, 4, 0, 0x2222}, {6, 20, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData182_INTERP_BICUBIC_GRAYSCALE[] = {{8, 20, 4, 0, 0x2222}, {8, 20, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData183_INTERP_BICUBIC_GRAYSCALE[] = {{10, 20, 4, 0, 0x2222}, {10, 20, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData184_INTERP_BICUBIC_GRAYSCALE[] = {{12, 20, 4, 0, 0x2222}, {12, 20, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData185_INTERP_BICUBIC_GRAYSCALE[] = {{14, 20, 4, 0, 0x2222}, {14, 20, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData186_INTERP_BICUBIC_GRAYSCALE[] = {{16, 20, 4, 0, 0x2222}, {16, 20, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData187_INTERP_BICUBIC_GRAYSCALE[] = {{18, 20, 4, 0, 0x2222}, {18, 20, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData188_INTERP_BICUBIC_GRAYSCALE[] = {{20, 20, 4, 0, 0x2222}, {20, 20, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData189_INTERP_BICUBIC_GRAYSCALE[] = {{22, 20, 4, 0, 0x2222}, {22, 20, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData190_INTERP_BICUBIC_GRAYSCALE[] = {{24, 20, 4, 0, 0x2222}, {24, 20, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData191_INTERP_BICUBIC_GRAYSCALE[] = {{26, 20, 4, 0, 0x2222}, {26, 20, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData192_INTERP_BICUBIC_GRAYSCALE[] = {{28, 20, 4, 0, 0x2222}, {28, 20, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData193_INTERP_BICUBIC_GRAYSCALE[] = {{2, 22, 4, 0, 0x2222}, {2, 22, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData194_INTERP_BICUBIC_GRAYSCALE[] = {{4, 22, 4, 0, 0x2222}, {4, 22, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData195_INTERP_BICUBIC_GRAYSCALE[] = {{6, 22, 4, 0, 0x2222}, {6, 22, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData196_INTERP_BICUBIC_GRAYSCALE[] = {{8, 22, 4, 0, 0x2222}, {8, 22, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData197_INTERP_BICUBIC_GRAYSCALE[] = {{10, 22, 4, 0, 0x2222}, {10, 22, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData198_INTERP_BICUBIC_GRAYSCALE[] = {{12, 22, 4, 0, 0x2222}, {12, 22, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData199_INTERP_BICUBIC_GRAYSCALE[] = {{14, 22, 4, 0, 0x2222}, {14, 22, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData200_INTERP_BICUBIC_GRAYSCALE[] = {{16, 22, 4, 0, 0x2222}, {16, 22, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData201_INTERP_BICUBIC_GRAYSCALE[] = {{18, 22, 4, 0, 0x2222}, {18, 22, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData202_INTERP_BICUBIC_GRAYSCALE[] = {{20, 22, 4, 0, 0x2222}, {20, 22, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData203_INTERP_BICUBIC_GRAYSCALE[] = {{22, 22, 4, 0, 0x2222}, {22, 22, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData204_INTERP_BICUBIC_GRAYSCALE[] = {{24, 22, 4, 0, 0x2222}, {24, 22, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData205_INTERP_BICUBIC_GRAYSCALE[] = {{2, 24, 4, 0, 0x2222}, {2, 24, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData206_INTERP_BICUBIC_GRAYSCALE[] = {{4, 24, 4, 0, 0x2222}, {4, 24, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData207_INTERP_BICUBIC_GRAYSCALE[] = {{6, 24, 4, 0, 0x2222}, {6, 24, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData208_INTERP_BICUBIC_GRAYSCALE[] = {{8, 24, 4, 0, 0x2222}, {8, 24, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData209_INTERP_BICUBIC_GRAYSCALE[] = {{10, 24, 4, 0, 0x2222}, {10, 24, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData210_INTERP_BICUBIC_GRAYSCALE[] = {{12, 24, 4, 0, 0x2222}, {12, 24, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData211_INTERP_BICUBIC_GRAYSCALE[] = {{14, 24, 4, 0, 0x2222}, {14, 24, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData212_INTERP_BICUBIC_GRAYSCALE[] = {{16, 24, 4, 0, 0x2222}, {16, 24, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData213_INTERP_BICUBIC_GRAYSCALE[] = {{18, 24, 4, 0, 0x2222}, {18, 24, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData214_INTERP_BICUBIC_GRAYSCALE[] = {{20, 24, 4, 0, 0x2222}, {20, 24, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData215_INTERP_BICUBIC_GRAYSCALE[] = {{22, 24, 4, 0, 0x2222}, {22, 24, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData216_INTERP_BICUBIC_GRAYSCALE[] = {{2, 26, 4, 0, 0x2222}, {2, 26, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData217_INTERP_BICUBIC_GRAYSCALE[] = {{4, 26, 4, 0, 0x2222}, {4, 26, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData218_INTERP_BICUBIC_GRAYSCALE[] = {{6, 26, 4, 0, 0x2222}, {6, 26, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData219_INTERP_BICUBIC_GRAYSCALE[] = {{8, 26, 4, 0, 0x2222}, {8, 26, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData220_INTERP_BICUBIC_GRAYSCALE[] = {{10, 26, 4, 0, 0x2222}, {10, 26, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData221_INTERP_BICUBIC_GRAYSCALE[] = {{12, 26, 4, 0, 0x2222}, {12, 26, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData222_INTERP_BICUBIC_GRAYSCALE[] = {{14, 26, 4, 0, 0x2222}, {14, 26, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData223_INTERP_BICUBIC_GRAYSCALE[] = {{16, 26, 4, 0, 0x2222}, {16, 26, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData224_INTERP_BICUBIC_GRAYSCALE[] = {{18, 26, 4, 0, 0x2222}, {18, 26, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData225_INTERP_BICUBIC_GRAYSCALE[] = {{20, 26, 4, 0, 0x2222}, {20, 26, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData226_INTERP_BICUBIC_GRAYSCALE[] = {{2, 28, 4, 0, 0x2222}, {2, 28, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData227_INTERP_BICUBIC_GRAYSCALE[] = {{4, 28, 4, 0, 0x2222}, {4, 28, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData228_INTERP_BICUBIC_GRAYSCALE[] = {{6, 28, 4, 0, 0x2222}, {6, 28, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData229_INTERP_BICUBIC_GRAYSCALE[] = {{8, 28, 4, 0, 0x2222}, {8, 28, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData230_INTERP_BICUBIC_GRAYSCALE[] = {{10, 28, 4, 0, 0x2222}, {10, 28, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData231_INTERP_BICUBIC_GRAYSCALE[] = {{12, 28, 4, 0, 0x2222}, {12, 28, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData232_INTERP_BICUBIC_GRAYSCALE[] = {{14, 28, 4, 0, 0x2222}, {14, 28, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData233_INTERP_BICUBIC_GRAYSCALE[] = {{16, 28, 4, 0, 0x2222}, {16, 28, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData234_INTERP_BICUBIC_GRAYSCALE[] = {{18, 28, 4, 0, 0x2222}, {18, 28, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData235_INTERP_BICUBIC_GRAYSCALE[] = {{2, 30, 4, 0, 0x2222}, {2, 30, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData236_INTERP_BICUBIC_GRAYSCALE[] = {{4, 30, 4, 0, 0x2222}, {4, 30, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData237_INTERP_BICUBIC_GRAYSCALE[] = {{6, 30, 4, 0, 0x2222}, {6, 30, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData238_INTERP_BICUBIC_GRAYSCALE[] = {{8, 30, 4, 0, 0x2222}, {8, 30, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData239_INTERP_BICUBIC_GRAYSCALE[] = {{10, 30, 4, 0, 0x2222}, {10, 30, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData240_INTERP_BICUBIC_GRAYSCALE[] = {{12, 30, 4, 0, 0x2222}, {12, 30, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData241_INTERP_BICUBIC_GRAYSCALE[] = {{14, 30, 4, 0, 0x2222}, {14, 30, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData242_INTERP_BICUBIC_GRAYSCALE[] = {{16, 30, 4, 0, 0x2222}, {16, 30, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData243_INTERP_BICUBIC_GRAYSCALE[] = {{18, 30, 4, 0, 0x2222}, {18, 30, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData244_INTERP_BICUBIC_GRAYSCALE[] = {{2, 32, 4, 0, 0x2222}, {2, 32, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData245_INTERP_BICUBIC_GRAYSCALE[] = {{4, 32, 4, 0, 0x2222}, {4, 32, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData246_INTERP_BICUBIC_GRAYSCALE[] = {{6, 32, 4, 0, 0x2222}, {6, 32, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData247_INTERP_BICUBIC_GRAYSCALE[] = {{8, 32, 4, 0, 0x2222}, {8, 32, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData248_INTERP_BICUBIC_GRAYSCALE[] = {{10, 32, 4, 0, 0x2222}, {10, 32, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData249_INTERP_BICUBIC_GRAYSCALE[] = {{12, 32, 4, 0, 0x2222}, {12, 32, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData250_INTERP_BICUBIC_GRAYSCALE[] = {{14, 32, 4, 0, 0x2222}, {14, 32, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData251_INTERP_BICUBIC_GRAYSCALE[] = {{16, 32, 4, 0, 0x2222}, {16, 32, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};

static acf_scenario_kernel_data gScenarioKernelData0_INTERP_BICUBIC_GRAYSCALE[] = {{2}};
static acf_scenario_kernel_data gScenarioKernelData1_INTERP_BICUBIC_GRAYSCALE[] = {{2}};
static acf_scenario_kernel_data gScenarioKernelData2_INTERP_BICUBIC_GRAYSCALE[] = {{2}};
static acf_scenario_kernel_data gScenarioKernelData3_INTERP_BICUBIC_GRAYSCALE[] = {{2}};
static acf_scenario_kernel_data gScenarioKernelData4_INTERP_BICUBIC_GRAYSCALE[] = {{2}};
static acf_scenario_kernel_data gScenarioKernelData5_INTERP_BICUBIC_GRAYSCALE[] = {{2}};
static acf_scenario_kernel_data gScenarioKernelData6_INTERP_BICUBIC_GRAYSCALE[] = {{2}};
static acf_scenario_kernel_data gScenarioKernelData7_INTERP_BICUBIC_GRAYSCALE[] = {{2}};
static acf_scenario_kernel_data gScenarioKernelData8_INTERP_BICUBIC_GRAYSCALE[] = {{2}};
static acf_scenario_kernel_data gScenarioKernelData9_INTERP_BICUBIC_GRAYSCALE[] = {{2}};
static acf_scenario_kernel_data gScenarioKernelData10_INTERP_BICUBIC_GRAYSCALE[] = {{2}};
static acf_scenario_kernel_data gScenarioKernelData11_INTERP_BICUBIC_GRAYSCALE[] = {{2}};
static acf_scenario_kernel_data gScenarioKernelData12_INTERP_BICUBIC_GRAYSCALE[] = {{2}};
static acf_scenario_kernel_data gScenarioKernelData13_INTERP_BICUBIC_GRAYSCALE[] = {{2}};
static acf_scenario_kernel_data gScenarioKernelData14_INTERP_BICUBIC_GRAYSCALE[] = {{2}};
static acf_scenario_kernel_data gScenarioKernelData15_INTERP_BICUBIC_GRAYSCALE[] = {{2}};
static acf_scenario_kernel_data gScenarioKernelData16_INTERP_BICUBIC_GRAYSCALE[] = {{2}};
static acf_scenario_kernel_data gScenarioKernelData17_INTERP_BICUBIC_GRAYSCALE[] = {{2}};
static acf_scenario_kernel_data gScenarioKernelData18_INTERP_BICUBIC_GRAYSCALE[] = {{2}};
static acf_scenario_kernel_data gScenarioKernelData19_INTERP_BICUBIC_GRAYSCALE[] = {{2}};
static acf_scenario_kernel_data gScenarioKernelData20_INTERP_BICUBIC_GRAYSCALE[] = {{2}};
static acf_scenario_kernel_data gScenarioKernelData21_INTERP_BICUBIC_GRAYSCALE[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData22_INTERP_BICUBIC_GRAYSCALE[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData23_INTERP_BICUBIC_GRAYSCALE[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData24_INTERP_BICUBIC_GRAYSCALE[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData25_INTERP_BICUBIC_GRAYSCALE[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData26_INTERP_BICUBIC_GRAYSCALE[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData27_INTERP_BICUBIC_GRAYSCALE[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData28_INTERP_BICUBIC_GRAYSCALE[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData29_INTERP_BICUBIC_GRAYSCALE[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData30_INTERP_BICUBIC_GRAYSCALE[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData31_INTERP_BICUBIC_GRAYSCALE[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData32_INTERP_BICUBIC_GRAYSCALE[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData33_INTERP_BICUBIC_GRAYSCALE[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData34_INTERP_BICUBIC_GRAYSCALE[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData35_INTERP_BICUBIC_GRAYSCALE[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData36_INTERP_BICUBIC_GRAYSCALE[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData37_INTERP_BICUBIC_GRAYSCALE[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData38_INTERP_BICUBIC_GRAYSCALE[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData39_INTERP_BICUBIC_GRAYSCALE[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData40_INTERP_BICUBIC_GRAYSCALE[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData41_INTERP_BICUBIC_GRAYSCALE[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData42_INTERP_BICUBIC_GRAYSCALE[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData43_INTERP_BICUBIC_GRAYSCALE[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData44_INTERP_BICUBIC_GRAYSCALE[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData45_INTERP_BICUBIC_GRAYSCALE[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData46_INTERP_BICUBIC_GRAYSCALE[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData47_INTERP_BICUBIC_GRAYSCALE[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData48_INTERP_BICUBIC_GRAYSCALE[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData49_INTERP_BICUBIC_GRAYSCALE[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData50_INTERP_BICUBIC_GRAYSCALE[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData51_INTERP_BICUBIC_GRAYSCALE[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData52_INTERP_BICUBIC_GRAYSCALE[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData53_INTERP_BICUBIC_GRAYSCALE[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData54_INTERP_BICUBIC_GRAYSCALE[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData55_INTERP_BICUBIC_GRAYSCALE[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData56_INTERP_BICUBIC_GRAYSCALE[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData57_INTERP_BICUBIC_GRAYSCALE[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData58_INTERP_BICUBIC_GRAYSCALE[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData59_INTERP_BICUBIC_GRAYSCALE[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData60_INTERP_BICUBIC_GRAYSCALE[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData61_INTERP_BICUBIC_GRAYSCALE[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData62_INTERP_BICUBIC_GRAYSCALE[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData63_INTERP_BICUBIC_GRAYSCALE[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData64_INTERP_BICUBIC_GRAYSCALE[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData65_INTERP_BICUBIC_GRAYSCALE[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData66_INTERP_BICUBIC_GRAYSCALE[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData67_INTERP_BICUBIC_GRAYSCALE[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData68_INTERP_BICUBIC_GRAYSCALE[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData69_INTERP_BICUBIC_GRAYSCALE[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData70_INTERP_BICUBIC_GRAYSCALE[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData71_INTERP_BICUBIC_GRAYSCALE[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData72_INTERP_BICUBIC_GRAYSCALE[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData73_INTERP_BICUBIC_GRAYSCALE[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData74_INTERP_BICUBIC_GRAYSCALE[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData75_INTERP_BICUBIC_GRAYSCALE[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData76_INTERP_BICUBIC_GRAYSCALE[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData77_INTERP_BICUBIC_GRAYSCALE[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData78_INTERP_BICUBIC_GRAYSCALE[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData79_INTERP_BICUBIC_GRAYSCALE[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData80_INTERP_BICUBIC_GRAYSCALE[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData81_INTERP_BICUBIC_GRAYSCALE[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData82_INTERP_BICUBIC_GRAYSCALE[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData83_INTERP_BICUBIC_GRAYSCALE[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData84_INTERP_BICUBIC_GRAYSCALE[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData85_INTERP_BICUBIC_GRAYSCALE[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData86_INTERP_BICUBIC_GRAYSCALE[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData87_INTERP_BICUBIC_GRAYSCALE[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData88_INTERP_BICUBIC_GRAYSCALE[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData89_INTERP_BICUBIC_GRAYSCALE[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData90_INTERP_BICUBIC_GRAYSCALE[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData91_INTERP_BICUBIC_GRAYSCALE[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData92_INTERP_BICUBIC_GRAYSCALE[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData93_INTERP_BICUBIC_GRAYSCALE[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData94_INTERP_BICUBIC_GRAYSCALE[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData95_INTERP_BICUBIC_GRAYSCALE[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData96_INTERP_BICUBIC_GRAYSCALE[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData97_INTERP_BICUBIC_GRAYSCALE[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData98_INTERP_BICUBIC_GRAYSCALE[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData99_INTERP_BICUBIC_GRAYSCALE[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData100_INTERP_BICUBIC_GRAYSCALE[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData101_INTERP_BICUBIC_GRAYSCALE[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData102_INTERP_BICUBIC_GRAYSCALE[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData103_INTERP_BICUBIC_GRAYSCALE[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData104_INTERP_BICUBIC_GRAYSCALE[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData105_INTERP_BICUBIC_GRAYSCALE[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData106_INTERP_BICUBIC_GRAYSCALE[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData107_INTERP_BICUBIC_GRAYSCALE[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData108_INTERP_BICUBIC_GRAYSCALE[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData109_INTERP_BICUBIC_GRAYSCALE[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData110_INTERP_BICUBIC_GRAYSCALE[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData111_INTERP_BICUBIC_GRAYSCALE[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData112_INTERP_BICUBIC_GRAYSCALE[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData113_INTERP_BICUBIC_GRAYSCALE[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData114_INTERP_BICUBIC_GRAYSCALE[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData115_INTERP_BICUBIC_GRAYSCALE[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData116_INTERP_BICUBIC_GRAYSCALE[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData117_INTERP_BICUBIC_GRAYSCALE[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData118_INTERP_BICUBIC_GRAYSCALE[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData119_INTERP_BICUBIC_GRAYSCALE[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData120_INTERP_BICUBIC_GRAYSCALE[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData121_INTERP_BICUBIC_GRAYSCALE[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData122_INTERP_BICUBIC_GRAYSCALE[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData123_INTERP_BICUBIC_GRAYSCALE[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData124_INTERP_BICUBIC_GRAYSCALE[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData125_INTERP_BICUBIC_GRAYSCALE[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData126_INTERP_BICUBIC_GRAYSCALE[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData127_INTERP_BICUBIC_GRAYSCALE[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData128_INTERP_BICUBIC_GRAYSCALE[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData129_INTERP_BICUBIC_GRAYSCALE[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData130_INTERP_BICUBIC_GRAYSCALE[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData131_INTERP_BICUBIC_GRAYSCALE[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData132_INTERP_BICUBIC_GRAYSCALE[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData133_INTERP_BICUBIC_GRAYSCALE[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData134_INTERP_BICUBIC_GRAYSCALE[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData135_INTERP_BICUBIC_GRAYSCALE[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData136_INTERP_BICUBIC_GRAYSCALE[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData137_INTERP_BICUBIC_GRAYSCALE[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData138_INTERP_BICUBIC_GRAYSCALE[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData139_INTERP_BICUBIC_GRAYSCALE[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData140_INTERP_BICUBIC_GRAYSCALE[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData141_INTERP_BICUBIC_GRAYSCALE[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData142_INTERP_BICUBIC_GRAYSCALE[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData143_INTERP_BICUBIC_GRAYSCALE[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData144_INTERP_BICUBIC_GRAYSCALE[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData145_INTERP_BICUBIC_GRAYSCALE[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData146_INTERP_BICUBIC_GRAYSCALE[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData147_INTERP_BICUBIC_GRAYSCALE[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData148_INTERP_BICUBIC_GRAYSCALE[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData149_INTERP_BICUBIC_GRAYSCALE[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData150_INTERP_BICUBIC_GRAYSCALE[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData151_INTERP_BICUBIC_GRAYSCALE[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData152_INTERP_BICUBIC_GRAYSCALE[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData153_INTERP_BICUBIC_GRAYSCALE[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData154_INTERP_BICUBIC_GRAYSCALE[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData155_INTERP_BICUBIC_GRAYSCALE[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData156_INTERP_BICUBIC_GRAYSCALE[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData157_INTERP_BICUBIC_GRAYSCALE[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData158_INTERP_BICUBIC_GRAYSCALE[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData159_INTERP_BICUBIC_GRAYSCALE[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData160_INTERP_BICUBIC_GRAYSCALE[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData161_INTERP_BICUBIC_GRAYSCALE[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData162_INTERP_BICUBIC_GRAYSCALE[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData163_INTERP_BICUBIC_GRAYSCALE[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData164_INTERP_BICUBIC_GRAYSCALE[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData165_INTERP_BICUBIC_GRAYSCALE[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData166_INTERP_BICUBIC_GRAYSCALE[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData167_INTERP_BICUBIC_GRAYSCALE[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData168_INTERP_BICUBIC_GRAYSCALE[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData169_INTERP_BICUBIC_GRAYSCALE[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData170_INTERP_BICUBIC_GRAYSCALE[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData171_INTERP_BICUBIC_GRAYSCALE[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData172_INTERP_BICUBIC_GRAYSCALE[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData173_INTERP_BICUBIC_GRAYSCALE[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData174_INTERP_BICUBIC_GRAYSCALE[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData175_INTERP_BICUBIC_GRAYSCALE[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData176_INTERP_BICUBIC_GRAYSCALE[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData177_INTERP_BICUBIC_GRAYSCALE[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData178_INTERP_BICUBIC_GRAYSCALE[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData179_INTERP_BICUBIC_GRAYSCALE[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData180_INTERP_BICUBIC_GRAYSCALE[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData181_INTERP_BICUBIC_GRAYSCALE[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData182_INTERP_BICUBIC_GRAYSCALE[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData183_INTERP_BICUBIC_GRAYSCALE[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData184_INTERP_BICUBIC_GRAYSCALE[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData185_INTERP_BICUBIC_GRAYSCALE[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData186_INTERP_BICUBIC_GRAYSCALE[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData187_INTERP_BICUBIC_GRAYSCALE[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData188_INTERP_BICUBIC_GRAYSCALE[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData189_INTERP_BICUBIC_GRAYSCALE[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData190_INTERP_BICUBIC_GRAYSCALE[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData191_INTERP_BICUBIC_GRAYSCALE[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData192_INTERP_BICUBIC_GRAYSCALE[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData193_INTERP_BICUBIC_GRAYSCALE[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData194_INTERP_BICUBIC_GRAYSCALE[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData195_INTERP_BICUBIC_GRAYSCALE[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData196_INTERP_BICUBIC_GRAYSCALE[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData197_INTERP_BICUBIC_GRAYSCALE[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData198_INTERP_BICUBIC_GRAYSCALE[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData199_INTERP_BICUBIC_GRAYSCALE[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData200_INTERP_BICUBIC_GRAYSCALE[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData201_INTERP_BICUBIC_GRAYSCALE[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData202_INTERP_BICUBIC_GRAYSCALE[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData203_INTERP_BICUBIC_GRAYSCALE[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData204_INTERP_BICUBIC_GRAYSCALE[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData205_INTERP_BICUBIC_GRAYSCALE[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData206_INTERP_BICUBIC_GRAYSCALE[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData207_INTERP_BICUBIC_GRAYSCALE[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData208_INTERP_BICUBIC_GRAYSCALE[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData209_INTERP_BICUBIC_GRAYSCALE[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData210_INTERP_BICUBIC_GRAYSCALE[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData211_INTERP_BICUBIC_GRAYSCALE[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData212_INTERP_BICUBIC_GRAYSCALE[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData213_INTERP_BICUBIC_GRAYSCALE[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData214_INTERP_BICUBIC_GRAYSCALE[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData215_INTERP_BICUBIC_GRAYSCALE[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData216_INTERP_BICUBIC_GRAYSCALE[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData217_INTERP_BICUBIC_GRAYSCALE[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData218_INTERP_BICUBIC_GRAYSCALE[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData219_INTERP_BICUBIC_GRAYSCALE[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData220_INTERP_BICUBIC_GRAYSCALE[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData221_INTERP_BICUBIC_GRAYSCALE[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData222_INTERP_BICUBIC_GRAYSCALE[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData223_INTERP_BICUBIC_GRAYSCALE[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData224_INTERP_BICUBIC_GRAYSCALE[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData225_INTERP_BICUBIC_GRAYSCALE[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData226_INTERP_BICUBIC_GRAYSCALE[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData227_INTERP_BICUBIC_GRAYSCALE[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData228_INTERP_BICUBIC_GRAYSCALE[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData229_INTERP_BICUBIC_GRAYSCALE[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData230_INTERP_BICUBIC_GRAYSCALE[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData231_INTERP_BICUBIC_GRAYSCALE[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData232_INTERP_BICUBIC_GRAYSCALE[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData233_INTERP_BICUBIC_GRAYSCALE[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData234_INTERP_BICUBIC_GRAYSCALE[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData235_INTERP_BICUBIC_GRAYSCALE[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData236_INTERP_BICUBIC_GRAYSCALE[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData237_INTERP_BICUBIC_GRAYSCALE[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData238_INTERP_BICUBIC_GRAYSCALE[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData239_INTERP_BICUBIC_GRAYSCALE[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData240_INTERP_BICUBIC_GRAYSCALE[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData241_INTERP_BICUBIC_GRAYSCALE[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData242_INTERP_BICUBIC_GRAYSCALE[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData243_INTERP_BICUBIC_GRAYSCALE[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData244_INTERP_BICUBIC_GRAYSCALE[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData245_INTERP_BICUBIC_GRAYSCALE[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData246_INTERP_BICUBIC_GRAYSCALE[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData247_INTERP_BICUBIC_GRAYSCALE[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData248_INTERP_BICUBIC_GRAYSCALE[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData249_INTERP_BICUBIC_GRAYSCALE[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData250_INTERP_BICUBIC_GRAYSCALE[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData251_INTERP_BICUBIC_GRAYSCALE[] = {{1}};

static acf_scenario gScenarioArray_INTERP_BICUBIC_GRAYSCALE[] = {
{2, 1, 72, 16, 2, gScenarioBufferData0_INTERP_BICUBIC_GRAYSCALE, 40, gScenarioKernelData0_INTERP_BICUBIC_GRAYSCALE, 2},
{4, 1, 96, 16, 2, gScenarioBufferData1_INTERP_BICUBIC_GRAYSCALE, 40, gScenarioKernelData1_INTERP_BICUBIC_GRAYSCALE, 2},
{6, 1, 124, 16, 2, gScenarioBufferData2_INTERP_BICUBIC_GRAYSCALE, 40, gScenarioKernelData2_INTERP_BICUBIC_GRAYSCALE, 2},
{8, 1, 148, 16, 2, gScenarioBufferData3_INTERP_BICUBIC_GRAYSCALE, 40, gScenarioKernelData3_INTERP_BICUBIC_GRAYSCALE, 2},
{10, 1, 176, 16, 2, gScenarioBufferData4_INTERP_BICUBIC_GRAYSCALE, 40, gScenarioKernelData4_INTERP_BICUBIC_GRAYSCALE, 2},
{12, 1, 200, 16, 2, gScenarioBufferData5_INTERP_BICUBIC_GRAYSCALE, 40, gScenarioKernelData5_INTERP_BICUBIC_GRAYSCALE, 2},
{14, 1, 228, 16, 2, gScenarioBufferData6_INTERP_BICUBIC_GRAYSCALE, 40, gScenarioKernelData6_INTERP_BICUBIC_GRAYSCALE, 2},
{16, 1, 252, 16, 2, gScenarioBufferData7_INTERP_BICUBIC_GRAYSCALE, 40, gScenarioKernelData7_INTERP_BICUBIC_GRAYSCALE, 2},
{18, 1, 280, 16, 2, gScenarioBufferData8_INTERP_BICUBIC_GRAYSCALE, 40, gScenarioKernelData8_INTERP_BICUBIC_GRAYSCALE, 2},
{20, 1, 304, 16, 2, gScenarioBufferData9_INTERP_BICUBIC_GRAYSCALE, 40, gScenarioKernelData9_INTERP_BICUBIC_GRAYSCALE, 2},
{22, 1, 332, 16, 2, gScenarioBufferData10_INTERP_BICUBIC_GRAYSCALE, 40, gScenarioKernelData10_INTERP_BICUBIC_GRAYSCALE, 2},
{24, 1, 356, 16, 2, gScenarioBufferData11_INTERP_BICUBIC_GRAYSCALE, 40, gScenarioKernelData11_INTERP_BICUBIC_GRAYSCALE, 2},
{26, 1, 384, 16, 2, gScenarioBufferData12_INTERP_BICUBIC_GRAYSCALE, 40, gScenarioKernelData12_INTERP_BICUBIC_GRAYSCALE, 2},
{28, 1, 408, 16, 2, gScenarioBufferData13_INTERP_BICUBIC_GRAYSCALE, 40, gScenarioKernelData13_INTERP_BICUBIC_GRAYSCALE, 2},
{30, 1, 436, 16, 2, gScenarioBufferData14_INTERP_BICUBIC_GRAYSCALE, 40, gScenarioKernelData14_INTERP_BICUBIC_GRAYSCALE, 2},
{32, 1, 460, 16, 2, gScenarioBufferData15_INTERP_BICUBIC_GRAYSCALE, 40, gScenarioKernelData15_INTERP_BICUBIC_GRAYSCALE, 2},
{48, 1, 668, 16, 2, gScenarioBufferData16_INTERP_BICUBIC_GRAYSCALE, 40, gScenarioKernelData16_INTERP_BICUBIC_GRAYSCALE, 2},
{64, 1, 876, 16, 2, gScenarioBufferData17_INTERP_BICUBIC_GRAYSCALE, 40, gScenarioKernelData17_INTERP_BICUBIC_GRAYSCALE, 2},
{96, 1, 1292, 16, 2, gScenarioBufferData18_INTERP_BICUBIC_GRAYSCALE, 40, gScenarioKernelData18_INTERP_BICUBIC_GRAYSCALE, 2},
{112, 1, 1500, 16, 2, gScenarioBufferData19_INTERP_BICUBIC_GRAYSCALE, 40, gScenarioKernelData19_INTERP_BICUBIC_GRAYSCALE, 2},
{128, 1, 1708, 16, 2, gScenarioBufferData20_INTERP_BICUBIC_GRAYSCALE, 40, gScenarioKernelData20_INTERP_BICUBIC_GRAYSCALE, 2},
{2, 2, 80, 16, 1, gScenarioBufferData21_INTERP_BICUBIC_GRAYSCALE, 40, gScenarioKernelData21_INTERP_BICUBIC_GRAYSCALE, 2},
{4, 2, 112, 16, 1, gScenarioBufferData22_INTERP_BICUBIC_GRAYSCALE, 40, gScenarioKernelData22_INTERP_BICUBIC_GRAYSCALE, 2},
{6, 2, 144, 16, 1, gScenarioBufferData23_INTERP_BICUBIC_GRAYSCALE, 40, gScenarioKernelData23_INTERP_BICUBIC_GRAYSCALE, 2},
{8, 2, 176, 16, 1, gScenarioBufferData24_INTERP_BICUBIC_GRAYSCALE, 40, gScenarioKernelData24_INTERP_BICUBIC_GRAYSCALE, 2},
{10, 2, 208, 16, 1, gScenarioBufferData25_INTERP_BICUBIC_GRAYSCALE, 40, gScenarioKernelData25_INTERP_BICUBIC_GRAYSCALE, 2},
{12, 2, 240, 16, 1, gScenarioBufferData26_INTERP_BICUBIC_GRAYSCALE, 40, gScenarioKernelData26_INTERP_BICUBIC_GRAYSCALE, 2},
{14, 2, 272, 16, 1, gScenarioBufferData27_INTERP_BICUBIC_GRAYSCALE, 40, gScenarioKernelData27_INTERP_BICUBIC_GRAYSCALE, 2},
{16, 2, 304, 16, 1, gScenarioBufferData28_INTERP_BICUBIC_GRAYSCALE, 40, gScenarioKernelData28_INTERP_BICUBIC_GRAYSCALE, 2},
{18, 2, 336, 16, 1, gScenarioBufferData29_INTERP_BICUBIC_GRAYSCALE, 40, gScenarioKernelData29_INTERP_BICUBIC_GRAYSCALE, 2},
{20, 2, 368, 16, 1, gScenarioBufferData30_INTERP_BICUBIC_GRAYSCALE, 40, gScenarioKernelData30_INTERP_BICUBIC_GRAYSCALE, 2},
{22, 2, 400, 16, 1, gScenarioBufferData31_INTERP_BICUBIC_GRAYSCALE, 40, gScenarioKernelData31_INTERP_BICUBIC_GRAYSCALE, 2},
{24, 2, 432, 16, 1, gScenarioBufferData32_INTERP_BICUBIC_GRAYSCALE, 40, gScenarioKernelData32_INTERP_BICUBIC_GRAYSCALE, 2},
{26, 2, 464, 16, 1, gScenarioBufferData33_INTERP_BICUBIC_GRAYSCALE, 40, gScenarioKernelData33_INTERP_BICUBIC_GRAYSCALE, 2},
{28, 2, 496, 16, 1, gScenarioBufferData34_INTERP_BICUBIC_GRAYSCALE, 40, gScenarioKernelData34_INTERP_BICUBIC_GRAYSCALE, 2},
{30, 2, 528, 16, 1, gScenarioBufferData35_INTERP_BICUBIC_GRAYSCALE, 40, gScenarioKernelData35_INTERP_BICUBIC_GRAYSCALE, 2},
{32, 2, 560, 16, 1, gScenarioBufferData36_INTERP_BICUBIC_GRAYSCALE, 40, gScenarioKernelData36_INTERP_BICUBIC_GRAYSCALE, 2},
{48, 2, 816, 16, 1, gScenarioBufferData37_INTERP_BICUBIC_GRAYSCALE, 40, gScenarioKernelData37_INTERP_BICUBIC_GRAYSCALE, 2},
{64, 2, 1072, 16, 1, gScenarioBufferData38_INTERP_BICUBIC_GRAYSCALE, 40, gScenarioKernelData38_INTERP_BICUBIC_GRAYSCALE, 2},
{96, 2, 1584, 16, 1, gScenarioBufferData39_INTERP_BICUBIC_GRAYSCALE, 40, gScenarioKernelData39_INTERP_BICUBIC_GRAYSCALE, 2},
{112, 2, 1840, 16, 1, gScenarioBufferData40_INTERP_BICUBIC_GRAYSCALE, 40, gScenarioKernelData40_INTERP_BICUBIC_GRAYSCALE, 2},
{128, 2, 2096, 16, 1, gScenarioBufferData41_INTERP_BICUBIC_GRAYSCALE, 40, gScenarioKernelData41_INTERP_BICUBIC_GRAYSCALE, 2},
{2, 4, 136, 16, 1, gScenarioBufferData42_INTERP_BICUBIC_GRAYSCALE, 40, gScenarioKernelData42_INTERP_BICUBIC_GRAYSCALE, 2},
{4, 4, 192, 16, 1, gScenarioBufferData43_INTERP_BICUBIC_GRAYSCALE, 40, gScenarioKernelData43_INTERP_BICUBIC_GRAYSCALE, 2},
{6, 4, 248, 16, 1, gScenarioBufferData44_INTERP_BICUBIC_GRAYSCALE, 40, gScenarioKernelData44_INTERP_BICUBIC_GRAYSCALE, 2},
{8, 4, 304, 16, 1, gScenarioBufferData45_INTERP_BICUBIC_GRAYSCALE, 40, gScenarioKernelData45_INTERP_BICUBIC_GRAYSCALE, 2},
{10, 4, 360, 16, 1, gScenarioBufferData46_INTERP_BICUBIC_GRAYSCALE, 40, gScenarioKernelData46_INTERP_BICUBIC_GRAYSCALE, 2},
{12, 4, 416, 16, 1, gScenarioBufferData47_INTERP_BICUBIC_GRAYSCALE, 40, gScenarioKernelData47_INTERP_BICUBIC_GRAYSCALE, 2},
{14, 4, 472, 16, 1, gScenarioBufferData48_INTERP_BICUBIC_GRAYSCALE, 40, gScenarioKernelData48_INTERP_BICUBIC_GRAYSCALE, 2},
{16, 4, 528, 16, 1, gScenarioBufferData49_INTERP_BICUBIC_GRAYSCALE, 40, gScenarioKernelData49_INTERP_BICUBIC_GRAYSCALE, 2},
{18, 4, 584, 16, 1, gScenarioBufferData50_INTERP_BICUBIC_GRAYSCALE, 40, gScenarioKernelData50_INTERP_BICUBIC_GRAYSCALE, 2},
{20, 4, 640, 16, 1, gScenarioBufferData51_INTERP_BICUBIC_GRAYSCALE, 40, gScenarioKernelData51_INTERP_BICUBIC_GRAYSCALE, 2},
{22, 4, 696, 16, 1, gScenarioBufferData52_INTERP_BICUBIC_GRAYSCALE, 40, gScenarioKernelData52_INTERP_BICUBIC_GRAYSCALE, 2},
{24, 4, 752, 16, 1, gScenarioBufferData53_INTERP_BICUBIC_GRAYSCALE, 40, gScenarioKernelData53_INTERP_BICUBIC_GRAYSCALE, 2},
{26, 4, 808, 16, 1, gScenarioBufferData54_INTERP_BICUBIC_GRAYSCALE, 40, gScenarioKernelData54_INTERP_BICUBIC_GRAYSCALE, 2},
{28, 4, 864, 16, 1, gScenarioBufferData55_INTERP_BICUBIC_GRAYSCALE, 40, gScenarioKernelData55_INTERP_BICUBIC_GRAYSCALE, 2},
{30, 4, 920, 16, 1, gScenarioBufferData56_INTERP_BICUBIC_GRAYSCALE, 40, gScenarioKernelData56_INTERP_BICUBIC_GRAYSCALE, 2},
{32, 4, 976, 16, 1, gScenarioBufferData57_INTERP_BICUBIC_GRAYSCALE, 40, gScenarioKernelData57_INTERP_BICUBIC_GRAYSCALE, 2},
{48, 4, 1424, 16, 1, gScenarioBufferData58_INTERP_BICUBIC_GRAYSCALE, 40, gScenarioKernelData58_INTERP_BICUBIC_GRAYSCALE, 2},
{64, 4, 1872, 16, 1, gScenarioBufferData59_INTERP_BICUBIC_GRAYSCALE, 40, gScenarioKernelData59_INTERP_BICUBIC_GRAYSCALE, 2},
{96, 4, 2768, 16, 1, gScenarioBufferData60_INTERP_BICUBIC_GRAYSCALE, 40, gScenarioKernelData60_INTERP_BICUBIC_GRAYSCALE, 2},
{112, 4, 3216, 16, 1, gScenarioBufferData61_INTERP_BICUBIC_GRAYSCALE, 40, gScenarioKernelData61_INTERP_BICUBIC_GRAYSCALE, 2},
{128, 4, 3664, 16, 1, gScenarioBufferData62_INTERP_BICUBIC_GRAYSCALE, 40, gScenarioKernelData62_INTERP_BICUBIC_GRAYSCALE, 2},
{2, 6, 192, 16, 1, gScenarioBufferData63_INTERP_BICUBIC_GRAYSCALE, 40, gScenarioKernelData63_INTERP_BICUBIC_GRAYSCALE, 2},
{4, 6, 272, 16, 1, gScenarioBufferData64_INTERP_BICUBIC_GRAYSCALE, 40, gScenarioKernelData64_INTERP_BICUBIC_GRAYSCALE, 2},
{6, 6, 352, 16, 1, gScenarioBufferData65_INTERP_BICUBIC_GRAYSCALE, 40, gScenarioKernelData65_INTERP_BICUBIC_GRAYSCALE, 2},
{8, 6, 432, 16, 1, gScenarioBufferData66_INTERP_BICUBIC_GRAYSCALE, 40, gScenarioKernelData66_INTERP_BICUBIC_GRAYSCALE, 2},
{10, 6, 512, 16, 1, gScenarioBufferData67_INTERP_BICUBIC_GRAYSCALE, 40, gScenarioKernelData67_INTERP_BICUBIC_GRAYSCALE, 2},
{12, 6, 592, 16, 1, gScenarioBufferData68_INTERP_BICUBIC_GRAYSCALE, 40, gScenarioKernelData68_INTERP_BICUBIC_GRAYSCALE, 2},
{14, 6, 672, 16, 1, gScenarioBufferData69_INTERP_BICUBIC_GRAYSCALE, 40, gScenarioKernelData69_INTERP_BICUBIC_GRAYSCALE, 2},
{16, 6, 752, 16, 1, gScenarioBufferData70_INTERP_BICUBIC_GRAYSCALE, 40, gScenarioKernelData70_INTERP_BICUBIC_GRAYSCALE, 2},
{18, 6, 832, 16, 1, gScenarioBufferData71_INTERP_BICUBIC_GRAYSCALE, 40, gScenarioKernelData71_INTERP_BICUBIC_GRAYSCALE, 2},
{20, 6, 912, 16, 1, gScenarioBufferData72_INTERP_BICUBIC_GRAYSCALE, 40, gScenarioKernelData72_INTERP_BICUBIC_GRAYSCALE, 2},
{22, 6, 992, 16, 1, gScenarioBufferData73_INTERP_BICUBIC_GRAYSCALE, 40, gScenarioKernelData73_INTERP_BICUBIC_GRAYSCALE, 2},
{24, 6, 1072, 16, 1, gScenarioBufferData74_INTERP_BICUBIC_GRAYSCALE, 40, gScenarioKernelData74_INTERP_BICUBIC_GRAYSCALE, 2},
{26, 6, 1152, 16, 1, gScenarioBufferData75_INTERP_BICUBIC_GRAYSCALE, 40, gScenarioKernelData75_INTERP_BICUBIC_GRAYSCALE, 2},
{28, 6, 1232, 16, 1, gScenarioBufferData76_INTERP_BICUBIC_GRAYSCALE, 40, gScenarioKernelData76_INTERP_BICUBIC_GRAYSCALE, 2},
{30, 6, 1312, 16, 1, gScenarioBufferData77_INTERP_BICUBIC_GRAYSCALE, 40, gScenarioKernelData77_INTERP_BICUBIC_GRAYSCALE, 2},
{32, 6, 1392, 16, 1, gScenarioBufferData78_INTERP_BICUBIC_GRAYSCALE, 40, gScenarioKernelData78_INTERP_BICUBIC_GRAYSCALE, 2},
{48, 6, 2032, 16, 1, gScenarioBufferData79_INTERP_BICUBIC_GRAYSCALE, 40, gScenarioKernelData79_INTERP_BICUBIC_GRAYSCALE, 2},
{64, 6, 2672, 16, 1, gScenarioBufferData80_INTERP_BICUBIC_GRAYSCALE, 40, gScenarioKernelData80_INTERP_BICUBIC_GRAYSCALE, 2},
{2, 8, 248, 16, 1, gScenarioBufferData81_INTERP_BICUBIC_GRAYSCALE, 40, gScenarioKernelData81_INTERP_BICUBIC_GRAYSCALE, 2},
{4, 8, 352, 16, 1, gScenarioBufferData82_INTERP_BICUBIC_GRAYSCALE, 40, gScenarioKernelData82_INTERP_BICUBIC_GRAYSCALE, 2},
{6, 8, 456, 16, 1, gScenarioBufferData83_INTERP_BICUBIC_GRAYSCALE, 40, gScenarioKernelData83_INTERP_BICUBIC_GRAYSCALE, 2},
{8, 8, 560, 16, 1, gScenarioBufferData84_INTERP_BICUBIC_GRAYSCALE, 40, gScenarioKernelData84_INTERP_BICUBIC_GRAYSCALE, 2},
{10, 8, 664, 16, 1, gScenarioBufferData85_INTERP_BICUBIC_GRAYSCALE, 40, gScenarioKernelData85_INTERP_BICUBIC_GRAYSCALE, 2},
{12, 8, 768, 16, 1, gScenarioBufferData86_INTERP_BICUBIC_GRAYSCALE, 40, gScenarioKernelData86_INTERP_BICUBIC_GRAYSCALE, 2},
{14, 8, 872, 16, 1, gScenarioBufferData87_INTERP_BICUBIC_GRAYSCALE, 40, gScenarioKernelData87_INTERP_BICUBIC_GRAYSCALE, 2},
{16, 8, 976, 16, 1, gScenarioBufferData88_INTERP_BICUBIC_GRAYSCALE, 40, gScenarioKernelData88_INTERP_BICUBIC_GRAYSCALE, 2},
{18, 8, 1080, 16, 1, gScenarioBufferData89_INTERP_BICUBIC_GRAYSCALE, 40, gScenarioKernelData89_INTERP_BICUBIC_GRAYSCALE, 2},
{20, 8, 1184, 16, 1, gScenarioBufferData90_INTERP_BICUBIC_GRAYSCALE, 40, gScenarioKernelData90_INTERP_BICUBIC_GRAYSCALE, 2},
{22, 8, 1288, 16, 1, gScenarioBufferData91_INTERP_BICUBIC_GRAYSCALE, 40, gScenarioKernelData91_INTERP_BICUBIC_GRAYSCALE, 2},
{24, 8, 1392, 16, 1, gScenarioBufferData92_INTERP_BICUBIC_GRAYSCALE, 40, gScenarioKernelData92_INTERP_BICUBIC_GRAYSCALE, 2},
{26, 8, 1496, 16, 1, gScenarioBufferData93_INTERP_BICUBIC_GRAYSCALE, 40, gScenarioKernelData93_INTERP_BICUBIC_GRAYSCALE, 2},
{28, 8, 1600, 16, 1, gScenarioBufferData94_INTERP_BICUBIC_GRAYSCALE, 40, gScenarioKernelData94_INTERP_BICUBIC_GRAYSCALE, 2},
{30, 8, 1704, 16, 1, gScenarioBufferData95_INTERP_BICUBIC_GRAYSCALE, 40, gScenarioKernelData95_INTERP_BICUBIC_GRAYSCALE, 2},
{32, 8, 1808, 16, 1, gScenarioBufferData96_INTERP_BICUBIC_GRAYSCALE, 40, gScenarioKernelData96_INTERP_BICUBIC_GRAYSCALE, 2},
{48, 8, 2640, 16, 1, gScenarioBufferData97_INTERP_BICUBIC_GRAYSCALE, 40, gScenarioKernelData97_INTERP_BICUBIC_GRAYSCALE, 2},
{64, 8, 3472, 16, 1, gScenarioBufferData98_INTERP_BICUBIC_GRAYSCALE, 40, gScenarioKernelData98_INTERP_BICUBIC_GRAYSCALE, 2},
{2, 10, 304, 16, 1, gScenarioBufferData99_INTERP_BICUBIC_GRAYSCALE, 40, gScenarioKernelData99_INTERP_BICUBIC_GRAYSCALE, 2},
{4, 10, 432, 16, 1, gScenarioBufferData100_INTERP_BICUBIC_GRAYSCALE, 40, gScenarioKernelData100_INTERP_BICUBIC_GRAYSCALE, 2},
{6, 10, 560, 16, 1, gScenarioBufferData101_INTERP_BICUBIC_GRAYSCALE, 40, gScenarioKernelData101_INTERP_BICUBIC_GRAYSCALE, 2},
{8, 10, 688, 16, 1, gScenarioBufferData102_INTERP_BICUBIC_GRAYSCALE, 40, gScenarioKernelData102_INTERP_BICUBIC_GRAYSCALE, 2},
{10, 10, 816, 16, 1, gScenarioBufferData103_INTERP_BICUBIC_GRAYSCALE, 40, gScenarioKernelData103_INTERP_BICUBIC_GRAYSCALE, 2},
{12, 10, 944, 16, 1, gScenarioBufferData104_INTERP_BICUBIC_GRAYSCALE, 40, gScenarioKernelData104_INTERP_BICUBIC_GRAYSCALE, 2},
{14, 10, 1072, 16, 1, gScenarioBufferData105_INTERP_BICUBIC_GRAYSCALE, 40, gScenarioKernelData105_INTERP_BICUBIC_GRAYSCALE, 2},
{16, 10, 1200, 16, 1, gScenarioBufferData106_INTERP_BICUBIC_GRAYSCALE, 40, gScenarioKernelData106_INTERP_BICUBIC_GRAYSCALE, 2},
{18, 10, 1328, 16, 1, gScenarioBufferData107_INTERP_BICUBIC_GRAYSCALE, 40, gScenarioKernelData107_INTERP_BICUBIC_GRAYSCALE, 2},
{20, 10, 1456, 16, 1, gScenarioBufferData108_INTERP_BICUBIC_GRAYSCALE, 40, gScenarioKernelData108_INTERP_BICUBIC_GRAYSCALE, 2},
{22, 10, 1584, 16, 1, gScenarioBufferData109_INTERP_BICUBIC_GRAYSCALE, 40, gScenarioKernelData109_INTERP_BICUBIC_GRAYSCALE, 2},
{24, 10, 1712, 16, 1, gScenarioBufferData110_INTERP_BICUBIC_GRAYSCALE, 40, gScenarioKernelData110_INTERP_BICUBIC_GRAYSCALE, 2},
{26, 10, 1840, 16, 1, gScenarioBufferData111_INTERP_BICUBIC_GRAYSCALE, 40, gScenarioKernelData111_INTERP_BICUBIC_GRAYSCALE, 2},
{28, 10, 1968, 16, 1, gScenarioBufferData112_INTERP_BICUBIC_GRAYSCALE, 40, gScenarioKernelData112_INTERP_BICUBIC_GRAYSCALE, 2},
{30, 10, 2096, 16, 1, gScenarioBufferData113_INTERP_BICUBIC_GRAYSCALE, 40, gScenarioKernelData113_INTERP_BICUBIC_GRAYSCALE, 2},
{32, 10, 2224, 16, 1, gScenarioBufferData114_INTERP_BICUBIC_GRAYSCALE, 40, gScenarioKernelData114_INTERP_BICUBIC_GRAYSCALE, 2},
{48, 10, 3248, 16, 1, gScenarioBufferData115_INTERP_BICUBIC_GRAYSCALE, 40, gScenarioKernelData115_INTERP_BICUBIC_GRAYSCALE, 2},
{2, 12, 360, 16, 1, gScenarioBufferData116_INTERP_BICUBIC_GRAYSCALE, 40, gScenarioKernelData116_INTERP_BICUBIC_GRAYSCALE, 2},
{4, 12, 512, 16, 1, gScenarioBufferData117_INTERP_BICUBIC_GRAYSCALE, 40, gScenarioKernelData117_INTERP_BICUBIC_GRAYSCALE, 2},
{6, 12, 664, 16, 1, gScenarioBufferData118_INTERP_BICUBIC_GRAYSCALE, 40, gScenarioKernelData118_INTERP_BICUBIC_GRAYSCALE, 2},
{8, 12, 816, 16, 1, gScenarioBufferData119_INTERP_BICUBIC_GRAYSCALE, 40, gScenarioKernelData119_INTERP_BICUBIC_GRAYSCALE, 2},
{10, 12, 968, 16, 1, gScenarioBufferData120_INTERP_BICUBIC_GRAYSCALE, 40, gScenarioKernelData120_INTERP_BICUBIC_GRAYSCALE, 2},
{12, 12, 1120, 16, 1, gScenarioBufferData121_INTERP_BICUBIC_GRAYSCALE, 40, gScenarioKernelData121_INTERP_BICUBIC_GRAYSCALE, 2},
{14, 12, 1272, 16, 1, gScenarioBufferData122_INTERP_BICUBIC_GRAYSCALE, 40, gScenarioKernelData122_INTERP_BICUBIC_GRAYSCALE, 2},
{16, 12, 1424, 16, 1, gScenarioBufferData123_INTERP_BICUBIC_GRAYSCALE, 40, gScenarioKernelData123_INTERP_BICUBIC_GRAYSCALE, 2},
{18, 12, 1576, 16, 1, gScenarioBufferData124_INTERP_BICUBIC_GRAYSCALE, 40, gScenarioKernelData124_INTERP_BICUBIC_GRAYSCALE, 2},
{20, 12, 1728, 16, 1, gScenarioBufferData125_INTERP_BICUBIC_GRAYSCALE, 40, gScenarioKernelData125_INTERP_BICUBIC_GRAYSCALE, 2},
{22, 12, 1880, 16, 1, gScenarioBufferData126_INTERP_BICUBIC_GRAYSCALE, 40, gScenarioKernelData126_INTERP_BICUBIC_GRAYSCALE, 2},
{24, 12, 2032, 16, 1, gScenarioBufferData127_INTERP_BICUBIC_GRAYSCALE, 40, gScenarioKernelData127_INTERP_BICUBIC_GRAYSCALE, 2},
{26, 12, 2184, 16, 1, gScenarioBufferData128_INTERP_BICUBIC_GRAYSCALE, 40, gScenarioKernelData128_INTERP_BICUBIC_GRAYSCALE, 2},
{28, 12, 2336, 16, 1, gScenarioBufferData129_INTERP_BICUBIC_GRAYSCALE, 40, gScenarioKernelData129_INTERP_BICUBIC_GRAYSCALE, 2},
{30, 12, 2488, 16, 1, gScenarioBufferData130_INTERP_BICUBIC_GRAYSCALE, 40, gScenarioKernelData130_INTERP_BICUBIC_GRAYSCALE, 2},
{32, 12, 2640, 16, 1, gScenarioBufferData131_INTERP_BICUBIC_GRAYSCALE, 40, gScenarioKernelData131_INTERP_BICUBIC_GRAYSCALE, 2},
{2, 14, 416, 16, 1, gScenarioBufferData132_INTERP_BICUBIC_GRAYSCALE, 40, gScenarioKernelData132_INTERP_BICUBIC_GRAYSCALE, 2},
{4, 14, 592, 16, 1, gScenarioBufferData133_INTERP_BICUBIC_GRAYSCALE, 40, gScenarioKernelData133_INTERP_BICUBIC_GRAYSCALE, 2},
{6, 14, 768, 16, 1, gScenarioBufferData134_INTERP_BICUBIC_GRAYSCALE, 40, gScenarioKernelData134_INTERP_BICUBIC_GRAYSCALE, 2},
{8, 14, 944, 16, 1, gScenarioBufferData135_INTERP_BICUBIC_GRAYSCALE, 40, gScenarioKernelData135_INTERP_BICUBIC_GRAYSCALE, 2},
{10, 14, 1120, 16, 1, gScenarioBufferData136_INTERP_BICUBIC_GRAYSCALE, 40, gScenarioKernelData136_INTERP_BICUBIC_GRAYSCALE, 2},
{12, 14, 1296, 16, 1, gScenarioBufferData137_INTERP_BICUBIC_GRAYSCALE, 40, gScenarioKernelData137_INTERP_BICUBIC_GRAYSCALE, 2},
{14, 14, 1472, 16, 1, gScenarioBufferData138_INTERP_BICUBIC_GRAYSCALE, 40, gScenarioKernelData138_INTERP_BICUBIC_GRAYSCALE, 2},
{16, 14, 1648, 16, 1, gScenarioBufferData139_INTERP_BICUBIC_GRAYSCALE, 40, gScenarioKernelData139_INTERP_BICUBIC_GRAYSCALE, 2},
{18, 14, 1824, 16, 1, gScenarioBufferData140_INTERP_BICUBIC_GRAYSCALE, 40, gScenarioKernelData140_INTERP_BICUBIC_GRAYSCALE, 2},
{20, 14, 2000, 16, 1, gScenarioBufferData141_INTERP_BICUBIC_GRAYSCALE, 40, gScenarioKernelData141_INTERP_BICUBIC_GRAYSCALE, 2},
{22, 14, 2176, 16, 1, gScenarioBufferData142_INTERP_BICUBIC_GRAYSCALE, 40, gScenarioKernelData142_INTERP_BICUBIC_GRAYSCALE, 2},
{24, 14, 2352, 16, 1, gScenarioBufferData143_INTERP_BICUBIC_GRAYSCALE, 40, gScenarioKernelData143_INTERP_BICUBIC_GRAYSCALE, 2},
{26, 14, 2528, 16, 1, gScenarioBufferData144_INTERP_BICUBIC_GRAYSCALE, 40, gScenarioKernelData144_INTERP_BICUBIC_GRAYSCALE, 2},
{28, 14, 2704, 16, 1, gScenarioBufferData145_INTERP_BICUBIC_GRAYSCALE, 40, gScenarioKernelData145_INTERP_BICUBIC_GRAYSCALE, 2},
{30, 14, 2880, 16, 1, gScenarioBufferData146_INTERP_BICUBIC_GRAYSCALE, 40, gScenarioKernelData146_INTERP_BICUBIC_GRAYSCALE, 2},
{32, 14, 3056, 16, 1, gScenarioBufferData147_INTERP_BICUBIC_GRAYSCALE, 40, gScenarioKernelData147_INTERP_BICUBIC_GRAYSCALE, 2},
{2, 16, 472, 16, 1, gScenarioBufferData148_INTERP_BICUBIC_GRAYSCALE, 40, gScenarioKernelData148_INTERP_BICUBIC_GRAYSCALE, 2},
{4, 16, 672, 16, 1, gScenarioBufferData149_INTERP_BICUBIC_GRAYSCALE, 40, gScenarioKernelData149_INTERP_BICUBIC_GRAYSCALE, 2},
{6, 16, 872, 16, 1, gScenarioBufferData150_INTERP_BICUBIC_GRAYSCALE, 40, gScenarioKernelData150_INTERP_BICUBIC_GRAYSCALE, 2},
{8, 16, 1072, 16, 1, gScenarioBufferData151_INTERP_BICUBIC_GRAYSCALE, 40, gScenarioKernelData151_INTERP_BICUBIC_GRAYSCALE, 2},
{10, 16, 1272, 16, 1, gScenarioBufferData152_INTERP_BICUBIC_GRAYSCALE, 40, gScenarioKernelData152_INTERP_BICUBIC_GRAYSCALE, 2},
{12, 16, 1472, 16, 1, gScenarioBufferData153_INTERP_BICUBIC_GRAYSCALE, 40, gScenarioKernelData153_INTERP_BICUBIC_GRAYSCALE, 2},
{14, 16, 1672, 16, 1, gScenarioBufferData154_INTERP_BICUBIC_GRAYSCALE, 40, gScenarioKernelData154_INTERP_BICUBIC_GRAYSCALE, 2},
{16, 16, 1872, 16, 1, gScenarioBufferData155_INTERP_BICUBIC_GRAYSCALE, 40, gScenarioKernelData155_INTERP_BICUBIC_GRAYSCALE, 2},
{18, 16, 2072, 16, 1, gScenarioBufferData156_INTERP_BICUBIC_GRAYSCALE, 40, gScenarioKernelData156_INTERP_BICUBIC_GRAYSCALE, 2},
{20, 16, 2272, 16, 1, gScenarioBufferData157_INTERP_BICUBIC_GRAYSCALE, 40, gScenarioKernelData157_INTERP_BICUBIC_GRAYSCALE, 2},
{22, 16, 2472, 16, 1, gScenarioBufferData158_INTERP_BICUBIC_GRAYSCALE, 40, gScenarioKernelData158_INTERP_BICUBIC_GRAYSCALE, 2},
{24, 16, 2672, 16, 1, gScenarioBufferData159_INTERP_BICUBIC_GRAYSCALE, 40, gScenarioKernelData159_INTERP_BICUBIC_GRAYSCALE, 2},
{26, 16, 2872, 16, 1, gScenarioBufferData160_INTERP_BICUBIC_GRAYSCALE, 40, gScenarioKernelData160_INTERP_BICUBIC_GRAYSCALE, 2},
{28, 16, 3072, 16, 1, gScenarioBufferData161_INTERP_BICUBIC_GRAYSCALE, 40, gScenarioKernelData161_INTERP_BICUBIC_GRAYSCALE, 2},
{30, 16, 3272, 16, 1, gScenarioBufferData162_INTERP_BICUBIC_GRAYSCALE, 40, gScenarioKernelData162_INTERP_BICUBIC_GRAYSCALE, 2},
{32, 16, 3472, 16, 1, gScenarioBufferData163_INTERP_BICUBIC_GRAYSCALE, 40, gScenarioKernelData163_INTERP_BICUBIC_GRAYSCALE, 2},
{2, 18, 528, 16, 1, gScenarioBufferData164_INTERP_BICUBIC_GRAYSCALE, 40, gScenarioKernelData164_INTERP_BICUBIC_GRAYSCALE, 2},
{4, 18, 752, 16, 1, gScenarioBufferData165_INTERP_BICUBIC_GRAYSCALE, 40, gScenarioKernelData165_INTERP_BICUBIC_GRAYSCALE, 2},
{6, 18, 976, 16, 1, gScenarioBufferData166_INTERP_BICUBIC_GRAYSCALE, 40, gScenarioKernelData166_INTERP_BICUBIC_GRAYSCALE, 2},
{8, 18, 1200, 16, 1, gScenarioBufferData167_INTERP_BICUBIC_GRAYSCALE, 40, gScenarioKernelData167_INTERP_BICUBIC_GRAYSCALE, 2},
{10, 18, 1424, 16, 1, gScenarioBufferData168_INTERP_BICUBIC_GRAYSCALE, 40, gScenarioKernelData168_INTERP_BICUBIC_GRAYSCALE, 2},
{12, 18, 1648, 16, 1, gScenarioBufferData169_INTERP_BICUBIC_GRAYSCALE, 40, gScenarioKernelData169_INTERP_BICUBIC_GRAYSCALE, 2},
{14, 18, 1872, 16, 1, gScenarioBufferData170_INTERP_BICUBIC_GRAYSCALE, 40, gScenarioKernelData170_INTERP_BICUBIC_GRAYSCALE, 2},
{16, 18, 2096, 16, 1, gScenarioBufferData171_INTERP_BICUBIC_GRAYSCALE, 40, gScenarioKernelData171_INTERP_BICUBIC_GRAYSCALE, 2},
{18, 18, 2320, 16, 1, gScenarioBufferData172_INTERP_BICUBIC_GRAYSCALE, 40, gScenarioKernelData172_INTERP_BICUBIC_GRAYSCALE, 2},
{20, 18, 2544, 16, 1, gScenarioBufferData173_INTERP_BICUBIC_GRAYSCALE, 40, gScenarioKernelData173_INTERP_BICUBIC_GRAYSCALE, 2},
{22, 18, 2768, 16, 1, gScenarioBufferData174_INTERP_BICUBIC_GRAYSCALE, 40, gScenarioKernelData174_INTERP_BICUBIC_GRAYSCALE, 2},
{24, 18, 2992, 16, 1, gScenarioBufferData175_INTERP_BICUBIC_GRAYSCALE, 40, gScenarioKernelData175_INTERP_BICUBIC_GRAYSCALE, 2},
{26, 18, 3216, 16, 1, gScenarioBufferData176_INTERP_BICUBIC_GRAYSCALE, 40, gScenarioKernelData176_INTERP_BICUBIC_GRAYSCALE, 2},
{28, 18, 3440, 16, 1, gScenarioBufferData177_INTERP_BICUBIC_GRAYSCALE, 40, gScenarioKernelData177_INTERP_BICUBIC_GRAYSCALE, 2},
{30, 18, 3664, 16, 1, gScenarioBufferData178_INTERP_BICUBIC_GRAYSCALE, 40, gScenarioKernelData178_INTERP_BICUBIC_GRAYSCALE, 2},
{2, 20, 584, 16, 1, gScenarioBufferData179_INTERP_BICUBIC_GRAYSCALE, 40, gScenarioKernelData179_INTERP_BICUBIC_GRAYSCALE, 2},
{4, 20, 832, 16, 1, gScenarioBufferData180_INTERP_BICUBIC_GRAYSCALE, 40, gScenarioKernelData180_INTERP_BICUBIC_GRAYSCALE, 2},
{6, 20, 1080, 16, 1, gScenarioBufferData181_INTERP_BICUBIC_GRAYSCALE, 40, gScenarioKernelData181_INTERP_BICUBIC_GRAYSCALE, 2},
{8, 20, 1328, 16, 1, gScenarioBufferData182_INTERP_BICUBIC_GRAYSCALE, 40, gScenarioKernelData182_INTERP_BICUBIC_GRAYSCALE, 2},
{10, 20, 1576, 16, 1, gScenarioBufferData183_INTERP_BICUBIC_GRAYSCALE, 40, gScenarioKernelData183_INTERP_BICUBIC_GRAYSCALE, 2},
{12, 20, 1824, 16, 1, gScenarioBufferData184_INTERP_BICUBIC_GRAYSCALE, 40, gScenarioKernelData184_INTERP_BICUBIC_GRAYSCALE, 2},
{14, 20, 2072, 16, 1, gScenarioBufferData185_INTERP_BICUBIC_GRAYSCALE, 40, gScenarioKernelData185_INTERP_BICUBIC_GRAYSCALE, 2},
{16, 20, 2320, 16, 1, gScenarioBufferData186_INTERP_BICUBIC_GRAYSCALE, 40, gScenarioKernelData186_INTERP_BICUBIC_GRAYSCALE, 2},
{18, 20, 2568, 16, 1, gScenarioBufferData187_INTERP_BICUBIC_GRAYSCALE, 40, gScenarioKernelData187_INTERP_BICUBIC_GRAYSCALE, 2},
{20, 20, 2816, 16, 1, gScenarioBufferData188_INTERP_BICUBIC_GRAYSCALE, 40, gScenarioKernelData188_INTERP_BICUBIC_GRAYSCALE, 2},
{22, 20, 3064, 16, 1, gScenarioBufferData189_INTERP_BICUBIC_GRAYSCALE, 40, gScenarioKernelData189_INTERP_BICUBIC_GRAYSCALE, 2},
{24, 20, 3312, 16, 1, gScenarioBufferData190_INTERP_BICUBIC_GRAYSCALE, 40, gScenarioKernelData190_INTERP_BICUBIC_GRAYSCALE, 2},
{26, 20, 3560, 16, 1, gScenarioBufferData191_INTERP_BICUBIC_GRAYSCALE, 40, gScenarioKernelData191_INTERP_BICUBIC_GRAYSCALE, 2},
{28, 20, 3808, 16, 1, gScenarioBufferData192_INTERP_BICUBIC_GRAYSCALE, 40, gScenarioKernelData192_INTERP_BICUBIC_GRAYSCALE, 2},
{2, 22, 640, 16, 1, gScenarioBufferData193_INTERP_BICUBIC_GRAYSCALE, 40, gScenarioKernelData193_INTERP_BICUBIC_GRAYSCALE, 2},
{4, 22, 912, 16, 1, gScenarioBufferData194_INTERP_BICUBIC_GRAYSCALE, 40, gScenarioKernelData194_INTERP_BICUBIC_GRAYSCALE, 2},
{6, 22, 1184, 16, 1, gScenarioBufferData195_INTERP_BICUBIC_GRAYSCALE, 40, gScenarioKernelData195_INTERP_BICUBIC_GRAYSCALE, 2},
{8, 22, 1456, 16, 1, gScenarioBufferData196_INTERP_BICUBIC_GRAYSCALE, 40, gScenarioKernelData196_INTERP_BICUBIC_GRAYSCALE, 2},
{10, 22, 1728, 16, 1, gScenarioBufferData197_INTERP_BICUBIC_GRAYSCALE, 40, gScenarioKernelData197_INTERP_BICUBIC_GRAYSCALE, 2},
{12, 22, 2000, 16, 1, gScenarioBufferData198_INTERP_BICUBIC_GRAYSCALE, 40, gScenarioKernelData198_INTERP_BICUBIC_GRAYSCALE, 2},
{14, 22, 2272, 16, 1, gScenarioBufferData199_INTERP_BICUBIC_GRAYSCALE, 40, gScenarioKernelData199_INTERP_BICUBIC_GRAYSCALE, 2},
{16, 22, 2544, 16, 1, gScenarioBufferData200_INTERP_BICUBIC_GRAYSCALE, 40, gScenarioKernelData200_INTERP_BICUBIC_GRAYSCALE, 2},
{18, 22, 2816, 16, 1, gScenarioBufferData201_INTERP_BICUBIC_GRAYSCALE, 40, gScenarioKernelData201_INTERP_BICUBIC_GRAYSCALE, 2},
{20, 22, 3088, 16, 1, gScenarioBufferData202_INTERP_BICUBIC_GRAYSCALE, 40, gScenarioKernelData202_INTERP_BICUBIC_GRAYSCALE, 2},
{22, 22, 3360, 16, 1, gScenarioBufferData203_INTERP_BICUBIC_GRAYSCALE, 40, gScenarioKernelData203_INTERP_BICUBIC_GRAYSCALE, 2},
{24, 22, 3632, 16, 1, gScenarioBufferData204_INTERP_BICUBIC_GRAYSCALE, 40, gScenarioKernelData204_INTERP_BICUBIC_GRAYSCALE, 2},
{2, 24, 696, 16, 1, gScenarioBufferData205_INTERP_BICUBIC_GRAYSCALE, 40, gScenarioKernelData205_INTERP_BICUBIC_GRAYSCALE, 2},
{4, 24, 992, 16, 1, gScenarioBufferData206_INTERP_BICUBIC_GRAYSCALE, 40, gScenarioKernelData206_INTERP_BICUBIC_GRAYSCALE, 2},
{6, 24, 1288, 16, 1, gScenarioBufferData207_INTERP_BICUBIC_GRAYSCALE, 40, gScenarioKernelData207_INTERP_BICUBIC_GRAYSCALE, 2},
{8, 24, 1584, 16, 1, gScenarioBufferData208_INTERP_BICUBIC_GRAYSCALE, 40, gScenarioKernelData208_INTERP_BICUBIC_GRAYSCALE, 2},
{10, 24, 1880, 16, 1, gScenarioBufferData209_INTERP_BICUBIC_GRAYSCALE, 40, gScenarioKernelData209_INTERP_BICUBIC_GRAYSCALE, 2},
{12, 24, 2176, 16, 1, gScenarioBufferData210_INTERP_BICUBIC_GRAYSCALE, 40, gScenarioKernelData210_INTERP_BICUBIC_GRAYSCALE, 2},
{14, 24, 2472, 16, 1, gScenarioBufferData211_INTERP_BICUBIC_GRAYSCALE, 40, gScenarioKernelData211_INTERP_BICUBIC_GRAYSCALE, 2},
{16, 24, 2768, 16, 1, gScenarioBufferData212_INTERP_BICUBIC_GRAYSCALE, 40, gScenarioKernelData212_INTERP_BICUBIC_GRAYSCALE, 2},
{18, 24, 3064, 16, 1, gScenarioBufferData213_INTERP_BICUBIC_GRAYSCALE, 40, gScenarioKernelData213_INTERP_BICUBIC_GRAYSCALE, 2},
{20, 24, 3360, 16, 1, gScenarioBufferData214_INTERP_BICUBIC_GRAYSCALE, 40, gScenarioKernelData214_INTERP_BICUBIC_GRAYSCALE, 2},
{22, 24, 3656, 16, 1, gScenarioBufferData215_INTERP_BICUBIC_GRAYSCALE, 40, gScenarioKernelData215_INTERP_BICUBIC_GRAYSCALE, 2},
{2, 26, 752, 16, 1, gScenarioBufferData216_INTERP_BICUBIC_GRAYSCALE, 40, gScenarioKernelData216_INTERP_BICUBIC_GRAYSCALE, 2},
{4, 26, 1072, 16, 1, gScenarioBufferData217_INTERP_BICUBIC_GRAYSCALE, 40, gScenarioKernelData217_INTERP_BICUBIC_GRAYSCALE, 2},
{6, 26, 1392, 16, 1, gScenarioBufferData218_INTERP_BICUBIC_GRAYSCALE, 40, gScenarioKernelData218_INTERP_BICUBIC_GRAYSCALE, 2},
{8, 26, 1712, 16, 1, gScenarioBufferData219_INTERP_BICUBIC_GRAYSCALE, 40, gScenarioKernelData219_INTERP_BICUBIC_GRAYSCALE, 2},
{10, 26, 2032, 16, 1, gScenarioBufferData220_INTERP_BICUBIC_GRAYSCALE, 40, gScenarioKernelData220_INTERP_BICUBIC_GRAYSCALE, 2},
{12, 26, 2352, 16, 1, gScenarioBufferData221_INTERP_BICUBIC_GRAYSCALE, 40, gScenarioKernelData221_INTERP_BICUBIC_GRAYSCALE, 2},
{14, 26, 2672, 16, 1, gScenarioBufferData222_INTERP_BICUBIC_GRAYSCALE, 40, gScenarioKernelData222_INTERP_BICUBIC_GRAYSCALE, 2},
{16, 26, 2992, 16, 1, gScenarioBufferData223_INTERP_BICUBIC_GRAYSCALE, 40, gScenarioKernelData223_INTERP_BICUBIC_GRAYSCALE, 2},
{18, 26, 3312, 16, 1, gScenarioBufferData224_INTERP_BICUBIC_GRAYSCALE, 40, gScenarioKernelData224_INTERP_BICUBIC_GRAYSCALE, 2},
{20, 26, 3632, 16, 1, gScenarioBufferData225_INTERP_BICUBIC_GRAYSCALE, 40, gScenarioKernelData225_INTERP_BICUBIC_GRAYSCALE, 2},
{2, 28, 808, 16, 1, gScenarioBufferData226_INTERP_BICUBIC_GRAYSCALE, 40, gScenarioKernelData226_INTERP_BICUBIC_GRAYSCALE, 2},
{4, 28, 1152, 16, 1, gScenarioBufferData227_INTERP_BICUBIC_GRAYSCALE, 40, gScenarioKernelData227_INTERP_BICUBIC_GRAYSCALE, 2},
{6, 28, 1496, 16, 1, gScenarioBufferData228_INTERP_BICUBIC_GRAYSCALE, 40, gScenarioKernelData228_INTERP_BICUBIC_GRAYSCALE, 2},
{8, 28, 1840, 16, 1, gScenarioBufferData229_INTERP_BICUBIC_GRAYSCALE, 40, gScenarioKernelData229_INTERP_BICUBIC_GRAYSCALE, 2},
{10, 28, 2184, 16, 1, gScenarioBufferData230_INTERP_BICUBIC_GRAYSCALE, 40, gScenarioKernelData230_INTERP_BICUBIC_GRAYSCALE, 2},
{12, 28, 2528, 16, 1, gScenarioBufferData231_INTERP_BICUBIC_GRAYSCALE, 40, gScenarioKernelData231_INTERP_BICUBIC_GRAYSCALE, 2},
{14, 28, 2872, 16, 1, gScenarioBufferData232_INTERP_BICUBIC_GRAYSCALE, 40, gScenarioKernelData232_INTERP_BICUBIC_GRAYSCALE, 2},
{16, 28, 3216, 16, 1, gScenarioBufferData233_INTERP_BICUBIC_GRAYSCALE, 40, gScenarioKernelData233_INTERP_BICUBIC_GRAYSCALE, 2},
{18, 28, 3560, 16, 1, gScenarioBufferData234_INTERP_BICUBIC_GRAYSCALE, 40, gScenarioKernelData234_INTERP_BICUBIC_GRAYSCALE, 2},
{2, 30, 864, 16, 1, gScenarioBufferData235_INTERP_BICUBIC_GRAYSCALE, 40, gScenarioKernelData235_INTERP_BICUBIC_GRAYSCALE, 2},
{4, 30, 1232, 16, 1, gScenarioBufferData236_INTERP_BICUBIC_GRAYSCALE, 40, gScenarioKernelData236_INTERP_BICUBIC_GRAYSCALE, 2},
{6, 30, 1600, 16, 1, gScenarioBufferData237_INTERP_BICUBIC_GRAYSCALE, 40, gScenarioKernelData237_INTERP_BICUBIC_GRAYSCALE, 2},
{8, 30, 1968, 16, 1, gScenarioBufferData238_INTERP_BICUBIC_GRAYSCALE, 40, gScenarioKernelData238_INTERP_BICUBIC_GRAYSCALE, 2},
{10, 30, 2336, 16, 1, gScenarioBufferData239_INTERP_BICUBIC_GRAYSCALE, 40, gScenarioKernelData239_INTERP_BICUBIC_GRAYSCALE, 2},
{12, 30, 2704, 16, 1, gScenarioBufferData240_INTERP_BICUBIC_GRAYSCALE, 40, gScenarioKernelData240_INTERP_BICUBIC_GRAYSCALE, 2},
{14, 30, 3072, 16, 1, gScenarioBufferData241_INTERP_BICUBIC_GRAYSCALE, 40, gScenarioKernelData241_INTERP_BICUBIC_GRAYSCALE, 2},
{16, 30, 3440, 16, 1, gScenarioBufferData242_INTERP_BICUBIC_GRAYSCALE, 40, gScenarioKernelData242_INTERP_BICUBIC_GRAYSCALE, 2},
{18, 30, 3808, 16, 1, gScenarioBufferData243_INTERP_BICUBIC_GRAYSCALE, 40, gScenarioKernelData243_INTERP_BICUBIC_GRAYSCALE, 2},
{2, 32, 920, 16, 1, gScenarioBufferData244_INTERP_BICUBIC_GRAYSCALE, 40, gScenarioKernelData244_INTERP_BICUBIC_GRAYSCALE, 2},
{4, 32, 1312, 16, 1, gScenarioBufferData245_INTERP_BICUBIC_GRAYSCALE, 40, gScenarioKernelData245_INTERP_BICUBIC_GRAYSCALE, 2},
{6, 32, 1704, 16, 1, gScenarioBufferData246_INTERP_BICUBIC_GRAYSCALE, 40, gScenarioKernelData246_INTERP_BICUBIC_GRAYSCALE, 2},
{8, 32, 2096, 16, 1, gScenarioBufferData247_INTERP_BICUBIC_GRAYSCALE, 40, gScenarioKernelData247_INTERP_BICUBIC_GRAYSCALE, 2},
{10, 32, 2488, 16, 1, gScenarioBufferData248_INTERP_BICUBIC_GRAYSCALE, 40, gScenarioKernelData248_INTERP_BICUBIC_GRAYSCALE, 2},
{12, 32, 2880, 16, 1, gScenarioBufferData249_INTERP_BICUBIC_GRAYSCALE, 40, gScenarioKernelData249_INTERP_BICUBIC_GRAYSCALE, 2},
{14, 32, 3272, 16, 1, gScenarioBufferData250_INTERP_BICUBIC_GRAYSCALE, 40, gScenarioKernelData250_INTERP_BICUBIC_GRAYSCALE, 2},
{16, 32, 3664, 16, 1, gScenarioBufferData251_INTERP_BICUBIC_GRAYSCALE, 40, gScenarioKernelData251_INTERP_BICUBIC_GRAYSCALE, 2}
};

static acf_scenario_list gScenarioList_INTERP_BICUBIC_GRAYSCALE = {
252, //number of scenarios
gScenarioArray_INTERP_BICUBIC_GRAYSCALE};
//**************************************************************

class INTERP_BICUBIC_GRAYSCALE : public ACF_Process_APU
{
public:
   INTERP_BICUBIC_GRAYSCALE(int32_t apex_id = 0) : ACF_Process_APU(apex_id)
   {} 

   int32_t Initialize()
   {
      int32_t lRetVal = 0;

      if (!Initialized()) //initialization steps that only need to occur once
      {
         SetProcessIdentifier("INTERP_BICUBIC_GRAYSCALE");
         SetApuLoadInfo(INTERP_BICUBIC_GRAYSCALE_LOAD_SEGMENTS,
                        INTERP_BICUBIC_GRAYSCALE_LOAD_PMEM, INTERP_BICUBIC_GRAYSCALE_LOAD_PMEM_SIZE,
                        INTERP_BICUBIC_GRAYSCALE_LOAD_DMEM, INTERP_BICUBIC_GRAYSCALE_LOAD_DMEM_SIZE,
                        0, 0); //assuming _LOAD_CMEM does not exist
         FlagSpatialDep();

         //***NOTE: the order in which the following ports are added is meaningful; do not change!

         AddPort("INPUT_0", ICP_DATATYPE_08U, 1, 1, 2, 1, 0, 0, 0, 0, 0, 0, 0, 0x2020202);
         AddPort("Y_OFFSET", ICP_DATATYPE_08U, 1, 1, 1, 1, 0, 1, 1, 0, 1, 0, 2);
         AddPort("X_OFFSET", ICP_DATATYPE_08U, 1, 1, 1, 1, 0, 1, 1, 0, 1, 0, 3);
         AddPort("OUTPUT_0", ICP_DATATYPE_08U, 1, 1, 2, 1, 1, 0, 0, 0, 0, 0, 1);

         CfgScenarios(&gScenarioList_INTERP_BICUBIC_GRAYSCALE);

         FlagAsInitialized();
      }

      lRetVal = SelectApuConfiguration(mApuCfg, mApexId); //by default mApuCfg = ACF_APU_CFG__APEX0_DEFAULT and mApexId = 0

      return lRetVal;
   }
};

#endif //_ACF_PROCESS_APU_INTERP_BICUBIC_GRAYSCALE
