#ifndef _ACF_PROCESS_APU_CONVOLVE_SCALE_3X3_16S
#define _ACF_PROCESS_APU_CONVOLVE_SCALE_3X3_16S

#include <acf_process_apu.h>
#include <CONVOLVE_SCALE_3X3_16S_APU_LOAD.h> //APU load associated with this process
#include <stdint.h>


//SCENARIO LIST*************************************************
static acf_scenario_buffer_data gScenarioBufferData0_CONVOLVE_SCALE_3X3_16S[] = {{2, 1, 4, 0, 0x2211}, {2, 1, 2, 1, 0x0}, {9, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData1_CONVOLVE_SCALE_3X3_16S[] = {{4, 1, 4, 0, 0x2211}, {4, 1, 2, 1, 0x0}, {9, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData2_CONVOLVE_SCALE_3X3_16S[] = {{6, 1, 4, 0, 0x2211}, {6, 1, 2, 1, 0x0}, {9, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData3_CONVOLVE_SCALE_3X3_16S[] = {{8, 1, 4, 0, 0x2211}, {8, 1, 2, 1, 0x0}, {9, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData4_CONVOLVE_SCALE_3X3_16S[] = {{10, 1, 4, 0, 0x2211}, {10, 1, 2, 1, 0x0}, {9, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData5_CONVOLVE_SCALE_3X3_16S[] = {{12, 1, 4, 0, 0x2211}, {12, 1, 2, 1, 0x0}, {9, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData6_CONVOLVE_SCALE_3X3_16S[] = {{14, 1, 4, 0, 0x2211}, {14, 1, 2, 1, 0x0}, {9, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData7_CONVOLVE_SCALE_3X3_16S[] = {{16, 1, 4, 0, 0x2211}, {16, 1, 2, 1, 0x0}, {9, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData8_CONVOLVE_SCALE_3X3_16S[] = {{18, 1, 4, 0, 0x2211}, {18, 1, 2, 1, 0x0}, {9, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData9_CONVOLVE_SCALE_3X3_16S[] = {{20, 1, 4, 0, 0x2211}, {20, 1, 2, 1, 0x0}, {9, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData10_CONVOLVE_SCALE_3X3_16S[] = {{22, 1, 4, 0, 0x2211}, {22, 1, 2, 1, 0x0}, {9, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData11_CONVOLVE_SCALE_3X3_16S[] = {{24, 1, 4, 0, 0x2211}, {24, 1, 2, 1, 0x0}, {9, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData12_CONVOLVE_SCALE_3X3_16S[] = {{26, 1, 4, 0, 0x2211}, {26, 1, 2, 1, 0x0}, {9, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData13_CONVOLVE_SCALE_3X3_16S[] = {{28, 1, 4, 0, 0x2211}, {28, 1, 2, 1, 0x0}, {9, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData14_CONVOLVE_SCALE_3X3_16S[] = {{30, 1, 4, 0, 0x2211}, {30, 1, 2, 1, 0x0}, {9, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData15_CONVOLVE_SCALE_3X3_16S[] = {{32, 1, 4, 0, 0x2211}, {32, 1, 2, 1, 0x0}, {9, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData16_CONVOLVE_SCALE_3X3_16S[] = {{48, 1, 4, 0, 0x2211}, {48, 1, 2, 1, 0x0}, {9, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData17_CONVOLVE_SCALE_3X3_16S[] = {{64, 1, 4, 0, 0x2211}, {64, 1, 2, 1, 0x0}, {9, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData18_CONVOLVE_SCALE_3X3_16S[] = {{2, 2, 4, 0, 0x2211}, {2, 2, 2, 1, 0x0}, {9, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData19_CONVOLVE_SCALE_3X3_16S[] = {{4, 2, 4, 0, 0x2211}, {4, 2, 2, 1, 0x0}, {9, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData20_CONVOLVE_SCALE_3X3_16S[] = {{6, 2, 4, 0, 0x2211}, {6, 2, 2, 1, 0x0}, {9, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData21_CONVOLVE_SCALE_3X3_16S[] = {{8, 2, 4, 0, 0x2211}, {8, 2, 2, 1, 0x0}, {9, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData22_CONVOLVE_SCALE_3X3_16S[] = {{10, 2, 4, 0, 0x2211}, {10, 2, 2, 1, 0x0}, {9, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData23_CONVOLVE_SCALE_3X3_16S[] = {{12, 2, 4, 0, 0x2211}, {12, 2, 2, 1, 0x0}, {9, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData24_CONVOLVE_SCALE_3X3_16S[] = {{14, 2, 4, 0, 0x2211}, {14, 2, 2, 1, 0x0}, {9, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData25_CONVOLVE_SCALE_3X3_16S[] = {{16, 2, 4, 0, 0x2211}, {16, 2, 2, 1, 0x0}, {9, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData26_CONVOLVE_SCALE_3X3_16S[] = {{18, 2, 4, 0, 0x2211}, {18, 2, 2, 1, 0x0}, {9, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData27_CONVOLVE_SCALE_3X3_16S[] = {{20, 2, 4, 0, 0x2211}, {20, 2, 2, 1, 0x0}, {9, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData28_CONVOLVE_SCALE_3X3_16S[] = {{22, 2, 4, 0, 0x2211}, {22, 2, 2, 1, 0x0}, {9, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData29_CONVOLVE_SCALE_3X3_16S[] = {{24, 2, 4, 0, 0x2211}, {24, 2, 2, 1, 0x0}, {9, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData30_CONVOLVE_SCALE_3X3_16S[] = {{26, 2, 4, 0, 0x2211}, {26, 2, 2, 1, 0x0}, {9, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData31_CONVOLVE_SCALE_3X3_16S[] = {{28, 2, 4, 0, 0x2211}, {28, 2, 2, 1, 0x0}, {9, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData32_CONVOLVE_SCALE_3X3_16S[] = {{30, 2, 4, 0, 0x2211}, {30, 2, 2, 1, 0x0}, {9, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData33_CONVOLVE_SCALE_3X3_16S[] = {{32, 2, 4, 0, 0x2211}, {32, 2, 2, 1, 0x0}, {9, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData34_CONVOLVE_SCALE_3X3_16S[] = {{48, 2, 4, 0, 0x2211}, {48, 2, 2, 1, 0x0}, {9, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData35_CONVOLVE_SCALE_3X3_16S[] = {{64, 2, 4, 0, 0x2211}, {64, 2, 2, 1, 0x0}, {9, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData36_CONVOLVE_SCALE_3X3_16S[] = {{2, 4, 4, 0, 0x2211}, {2, 4, 2, 1, 0x0}, {9, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData37_CONVOLVE_SCALE_3X3_16S[] = {{4, 4, 4, 0, 0x2211}, {4, 4, 2, 1, 0x0}, {9, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData38_CONVOLVE_SCALE_3X3_16S[] = {{6, 4, 4, 0, 0x2211}, {6, 4, 2, 1, 0x0}, {9, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData39_CONVOLVE_SCALE_3X3_16S[] = {{8, 4, 4, 0, 0x2211}, {8, 4, 2, 1, 0x0}, {9, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData40_CONVOLVE_SCALE_3X3_16S[] = {{10, 4, 4, 0, 0x2211}, {10, 4, 2, 1, 0x0}, {9, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData41_CONVOLVE_SCALE_3X3_16S[] = {{12, 4, 4, 0, 0x2211}, {12, 4, 2, 1, 0x0}, {9, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData42_CONVOLVE_SCALE_3X3_16S[] = {{14, 4, 4, 0, 0x2211}, {14, 4, 2, 1, 0x0}, {9, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData43_CONVOLVE_SCALE_3X3_16S[] = {{16, 4, 4, 0, 0x2211}, {16, 4, 2, 1, 0x0}, {9, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData44_CONVOLVE_SCALE_3X3_16S[] = {{18, 4, 4, 0, 0x2211}, {18, 4, 2, 1, 0x0}, {9, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData45_CONVOLVE_SCALE_3X3_16S[] = {{20, 4, 4, 0, 0x2211}, {20, 4, 2, 1, 0x0}, {9, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData46_CONVOLVE_SCALE_3X3_16S[] = {{22, 4, 4, 0, 0x2211}, {22, 4, 2, 1, 0x0}, {9, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData47_CONVOLVE_SCALE_3X3_16S[] = {{24, 4, 4, 0, 0x2211}, {24, 4, 2, 1, 0x0}, {9, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData48_CONVOLVE_SCALE_3X3_16S[] = {{26, 4, 4, 0, 0x2211}, {26, 4, 2, 1, 0x0}, {9, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData49_CONVOLVE_SCALE_3X3_16S[] = {{28, 4, 4, 0, 0x2211}, {28, 4, 2, 1, 0x0}, {9, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData50_CONVOLVE_SCALE_3X3_16S[] = {{30, 4, 4, 0, 0x2211}, {30, 4, 2, 1, 0x0}, {9, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData51_CONVOLVE_SCALE_3X3_16S[] = {{32, 4, 4, 0, 0x2211}, {32, 4, 2, 1, 0x0}, {9, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData52_CONVOLVE_SCALE_3X3_16S[] = {{48, 4, 4, 0, 0x2211}, {48, 4, 2, 1, 0x0}, {9, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData53_CONVOLVE_SCALE_3X3_16S[] = {{64, 4, 4, 0, 0x2211}, {64, 4, 2, 1, 0x0}, {9, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData54_CONVOLVE_SCALE_3X3_16S[] = {{2, 6, 4, 0, 0x2211}, {2, 6, 2, 1, 0x0}, {9, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData55_CONVOLVE_SCALE_3X3_16S[] = {{4, 6, 4, 0, 0x2211}, {4, 6, 2, 1, 0x0}, {9, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData56_CONVOLVE_SCALE_3X3_16S[] = {{6, 6, 4, 0, 0x2211}, {6, 6, 2, 1, 0x0}, {9, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData57_CONVOLVE_SCALE_3X3_16S[] = {{8, 6, 4, 0, 0x2211}, {8, 6, 2, 1, 0x0}, {9, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData58_CONVOLVE_SCALE_3X3_16S[] = {{10, 6, 4, 0, 0x2211}, {10, 6, 2, 1, 0x0}, {9, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData59_CONVOLVE_SCALE_3X3_16S[] = {{12, 6, 4, 0, 0x2211}, {12, 6, 2, 1, 0x0}, {9, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData60_CONVOLVE_SCALE_3X3_16S[] = {{14, 6, 4, 0, 0x2211}, {14, 6, 2, 1, 0x0}, {9, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData61_CONVOLVE_SCALE_3X3_16S[] = {{16, 6, 4, 0, 0x2211}, {16, 6, 2, 1, 0x0}, {9, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData62_CONVOLVE_SCALE_3X3_16S[] = {{18, 6, 4, 0, 0x2211}, {18, 6, 2, 1, 0x0}, {9, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData63_CONVOLVE_SCALE_3X3_16S[] = {{20, 6, 4, 0, 0x2211}, {20, 6, 2, 1, 0x0}, {9, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData64_CONVOLVE_SCALE_3X3_16S[] = {{22, 6, 4, 0, 0x2211}, {22, 6, 2, 1, 0x0}, {9, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData65_CONVOLVE_SCALE_3X3_16S[] = {{24, 6, 4, 0, 0x2211}, {24, 6, 2, 1, 0x0}, {9, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData66_CONVOLVE_SCALE_3X3_16S[] = {{26, 6, 4, 0, 0x2211}, {26, 6, 2, 1, 0x0}, {9, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData67_CONVOLVE_SCALE_3X3_16S[] = {{28, 6, 4, 0, 0x2211}, {28, 6, 2, 1, 0x0}, {9, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData68_CONVOLVE_SCALE_3X3_16S[] = {{30, 6, 4, 0, 0x2211}, {30, 6, 2, 1, 0x0}, {9, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData69_CONVOLVE_SCALE_3X3_16S[] = {{32, 6, 4, 0, 0x2211}, {32, 6, 2, 1, 0x0}, {9, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData70_CONVOLVE_SCALE_3X3_16S[] = {{48, 6, 4, 0, 0x2211}, {48, 6, 2, 1, 0x0}, {9, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData71_CONVOLVE_SCALE_3X3_16S[] = {{64, 6, 4, 0, 0x2211}, {64, 6, 2, 1, 0x0}, {9, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData72_CONVOLVE_SCALE_3X3_16S[] = {{2, 8, 4, 0, 0x2211}, {2, 8, 2, 1, 0x0}, {9, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData73_CONVOLVE_SCALE_3X3_16S[] = {{4, 8, 4, 0, 0x2211}, {4, 8, 2, 1, 0x0}, {9, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData74_CONVOLVE_SCALE_3X3_16S[] = {{6, 8, 4, 0, 0x2211}, {6, 8, 2, 1, 0x0}, {9, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData75_CONVOLVE_SCALE_3X3_16S[] = {{8, 8, 4, 0, 0x2211}, {8, 8, 2, 1, 0x0}, {9, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData76_CONVOLVE_SCALE_3X3_16S[] = {{10, 8, 4, 0, 0x2211}, {10, 8, 2, 1, 0x0}, {9, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData77_CONVOLVE_SCALE_3X3_16S[] = {{12, 8, 4, 0, 0x2211}, {12, 8, 2, 1, 0x0}, {9, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData78_CONVOLVE_SCALE_3X3_16S[] = {{14, 8, 4, 0, 0x2211}, {14, 8, 2, 1, 0x0}, {9, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData79_CONVOLVE_SCALE_3X3_16S[] = {{16, 8, 4, 0, 0x2211}, {16, 8, 2, 1, 0x0}, {9, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData80_CONVOLVE_SCALE_3X3_16S[] = {{18, 8, 4, 0, 0x2211}, {18, 8, 2, 1, 0x0}, {9, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData81_CONVOLVE_SCALE_3X3_16S[] = {{20, 8, 4, 0, 0x2211}, {20, 8, 2, 1, 0x0}, {9, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData82_CONVOLVE_SCALE_3X3_16S[] = {{22, 8, 4, 0, 0x2211}, {22, 8, 2, 1, 0x0}, {9, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData83_CONVOLVE_SCALE_3X3_16S[] = {{24, 8, 4, 0, 0x2211}, {24, 8, 2, 1, 0x0}, {9, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData84_CONVOLVE_SCALE_3X3_16S[] = {{26, 8, 4, 0, 0x2211}, {26, 8, 2, 1, 0x0}, {9, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData85_CONVOLVE_SCALE_3X3_16S[] = {{28, 8, 4, 0, 0x2211}, {28, 8, 2, 1, 0x0}, {9, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData86_CONVOLVE_SCALE_3X3_16S[] = {{30, 8, 4, 0, 0x2211}, {30, 8, 2, 1, 0x0}, {9, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData87_CONVOLVE_SCALE_3X3_16S[] = {{32, 8, 4, 0, 0x2211}, {32, 8, 2, 1, 0x0}, {9, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData88_CONVOLVE_SCALE_3X3_16S[] = {{48, 8, 4, 0, 0x2211}, {48, 8, 2, 1, 0x0}, {9, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData89_CONVOLVE_SCALE_3X3_16S[] = {{2, 10, 4, 0, 0x2211}, {2, 10, 2, 1, 0x0}, {9, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData90_CONVOLVE_SCALE_3X3_16S[] = {{4, 10, 4, 0, 0x2211}, {4, 10, 2, 1, 0x0}, {9, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData91_CONVOLVE_SCALE_3X3_16S[] = {{6, 10, 4, 0, 0x2211}, {6, 10, 2, 1, 0x0}, {9, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData92_CONVOLVE_SCALE_3X3_16S[] = {{8, 10, 4, 0, 0x2211}, {8, 10, 2, 1, 0x0}, {9, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData93_CONVOLVE_SCALE_3X3_16S[] = {{10, 10, 4, 0, 0x2211}, {10, 10, 2, 1, 0x0}, {9, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData94_CONVOLVE_SCALE_3X3_16S[] = {{12, 10, 4, 0, 0x2211}, {12, 10, 2, 1, 0x0}, {9, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData95_CONVOLVE_SCALE_3X3_16S[] = {{14, 10, 4, 0, 0x2211}, {14, 10, 2, 1, 0x0}, {9, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData96_CONVOLVE_SCALE_3X3_16S[] = {{16, 10, 4, 0, 0x2211}, {16, 10, 2, 1, 0x0}, {9, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData97_CONVOLVE_SCALE_3X3_16S[] = {{18, 10, 4, 0, 0x2211}, {18, 10, 2, 1, 0x0}, {9, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData98_CONVOLVE_SCALE_3X3_16S[] = {{20, 10, 4, 0, 0x2211}, {20, 10, 2, 1, 0x0}, {9, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData99_CONVOLVE_SCALE_3X3_16S[] = {{22, 10, 4, 0, 0x2211}, {22, 10, 2, 1, 0x0}, {9, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData100_CONVOLVE_SCALE_3X3_16S[] = {{24, 10, 4, 0, 0x2211}, {24, 10, 2, 1, 0x0}, {9, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData101_CONVOLVE_SCALE_3X3_16S[] = {{26, 10, 4, 0, 0x2211}, {26, 10, 2, 1, 0x0}, {9, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData102_CONVOLVE_SCALE_3X3_16S[] = {{28, 10, 4, 0, 0x2211}, {28, 10, 2, 1, 0x0}, {9, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData103_CONVOLVE_SCALE_3X3_16S[] = {{30, 10, 4, 0, 0x2211}, {30, 10, 2, 1, 0x0}, {9, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData104_CONVOLVE_SCALE_3X3_16S[] = {{32, 10, 4, 0, 0x2211}, {32, 10, 2, 1, 0x0}, {9, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData105_CONVOLVE_SCALE_3X3_16S[] = {{2, 12, 4, 0, 0x2211}, {2, 12, 2, 1, 0x0}, {9, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData106_CONVOLVE_SCALE_3X3_16S[] = {{4, 12, 4, 0, 0x2211}, {4, 12, 2, 1, 0x0}, {9, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData107_CONVOLVE_SCALE_3X3_16S[] = {{6, 12, 4, 0, 0x2211}, {6, 12, 2, 1, 0x0}, {9, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData108_CONVOLVE_SCALE_3X3_16S[] = {{8, 12, 4, 0, 0x2211}, {8, 12, 2, 1, 0x0}, {9, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData109_CONVOLVE_SCALE_3X3_16S[] = {{10, 12, 4, 0, 0x2211}, {10, 12, 2, 1, 0x0}, {9, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData110_CONVOLVE_SCALE_3X3_16S[] = {{12, 12, 4, 0, 0x2211}, {12, 12, 2, 1, 0x0}, {9, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData111_CONVOLVE_SCALE_3X3_16S[] = {{14, 12, 4, 0, 0x2211}, {14, 12, 2, 1, 0x0}, {9, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData112_CONVOLVE_SCALE_3X3_16S[] = {{16, 12, 4, 0, 0x2211}, {16, 12, 2, 1, 0x0}, {9, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData113_CONVOLVE_SCALE_3X3_16S[] = {{18, 12, 4, 0, 0x2211}, {18, 12, 2, 1, 0x0}, {9, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData114_CONVOLVE_SCALE_3X3_16S[] = {{20, 12, 4, 0, 0x2211}, {20, 12, 2, 1, 0x0}, {9, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData115_CONVOLVE_SCALE_3X3_16S[] = {{22, 12, 4, 0, 0x2211}, {22, 12, 2, 1, 0x0}, {9, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData116_CONVOLVE_SCALE_3X3_16S[] = {{24, 12, 4, 0, 0x2211}, {24, 12, 2, 1, 0x0}, {9, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData117_CONVOLVE_SCALE_3X3_16S[] = {{26, 12, 4, 0, 0x2211}, {26, 12, 2, 1, 0x0}, {9, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData118_CONVOLVE_SCALE_3X3_16S[] = {{28, 12, 4, 0, 0x2211}, {28, 12, 2, 1, 0x0}, {9, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData119_CONVOLVE_SCALE_3X3_16S[] = {{30, 12, 4, 0, 0x2211}, {30, 12, 2, 1, 0x0}, {9, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData120_CONVOLVE_SCALE_3X3_16S[] = {{32, 12, 4, 0, 0x2211}, {32, 12, 2, 1, 0x0}, {9, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData121_CONVOLVE_SCALE_3X3_16S[] = {{2, 14, 4, 0, 0x2211}, {2, 14, 2, 1, 0x0}, {9, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData122_CONVOLVE_SCALE_3X3_16S[] = {{4, 14, 4, 0, 0x2211}, {4, 14, 2, 1, 0x0}, {9, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData123_CONVOLVE_SCALE_3X3_16S[] = {{6, 14, 4, 0, 0x2211}, {6, 14, 2, 1, 0x0}, {9, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData124_CONVOLVE_SCALE_3X3_16S[] = {{8, 14, 4, 0, 0x2211}, {8, 14, 2, 1, 0x0}, {9, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData125_CONVOLVE_SCALE_3X3_16S[] = {{10, 14, 4, 0, 0x2211}, {10, 14, 2, 1, 0x0}, {9, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData126_CONVOLVE_SCALE_3X3_16S[] = {{12, 14, 4, 0, 0x2211}, {12, 14, 2, 1, 0x0}, {9, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData127_CONVOLVE_SCALE_3X3_16S[] = {{14, 14, 4, 0, 0x2211}, {14, 14, 2, 1, 0x0}, {9, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData128_CONVOLVE_SCALE_3X3_16S[] = {{16, 14, 4, 0, 0x2211}, {16, 14, 2, 1, 0x0}, {9, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData129_CONVOLVE_SCALE_3X3_16S[] = {{18, 14, 4, 0, 0x2211}, {18, 14, 2, 1, 0x0}, {9, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData130_CONVOLVE_SCALE_3X3_16S[] = {{20, 14, 4, 0, 0x2211}, {20, 14, 2, 1, 0x0}, {9, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData131_CONVOLVE_SCALE_3X3_16S[] = {{22, 14, 4, 0, 0x2211}, {22, 14, 2, 1, 0x0}, {9, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData132_CONVOLVE_SCALE_3X3_16S[] = {{24, 14, 4, 0, 0x2211}, {24, 14, 2, 1, 0x0}, {9, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData133_CONVOLVE_SCALE_3X3_16S[] = {{26, 14, 4, 0, 0x2211}, {26, 14, 2, 1, 0x0}, {9, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData134_CONVOLVE_SCALE_3X3_16S[] = {{28, 14, 4, 0, 0x2211}, {28, 14, 2, 1, 0x0}, {9, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData135_CONVOLVE_SCALE_3X3_16S[] = {{30, 14, 4, 0, 0x2211}, {30, 14, 2, 1, 0x0}, {9, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData136_CONVOLVE_SCALE_3X3_16S[] = {{2, 16, 4, 0, 0x2211}, {2, 16, 2, 1, 0x0}, {9, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData137_CONVOLVE_SCALE_3X3_16S[] = {{4, 16, 4, 0, 0x2211}, {4, 16, 2, 1, 0x0}, {9, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData138_CONVOLVE_SCALE_3X3_16S[] = {{6, 16, 4, 0, 0x2211}, {6, 16, 2, 1, 0x0}, {9, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData139_CONVOLVE_SCALE_3X3_16S[] = {{8, 16, 4, 0, 0x2211}, {8, 16, 2, 1, 0x0}, {9, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData140_CONVOLVE_SCALE_3X3_16S[] = {{10, 16, 4, 0, 0x2211}, {10, 16, 2, 1, 0x0}, {9, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData141_CONVOLVE_SCALE_3X3_16S[] = {{12, 16, 4, 0, 0x2211}, {12, 16, 2, 1, 0x0}, {9, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData142_CONVOLVE_SCALE_3X3_16S[] = {{14, 16, 4, 0, 0x2211}, {14, 16, 2, 1, 0x0}, {9, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData143_CONVOLVE_SCALE_3X3_16S[] = {{16, 16, 4, 0, 0x2211}, {16, 16, 2, 1, 0x0}, {9, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData144_CONVOLVE_SCALE_3X3_16S[] = {{18, 16, 4, 0, 0x2211}, {18, 16, 2, 1, 0x0}, {9, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData145_CONVOLVE_SCALE_3X3_16S[] = {{20, 16, 4, 0, 0x2211}, {20, 16, 2, 1, 0x0}, {9, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData146_CONVOLVE_SCALE_3X3_16S[] = {{22, 16, 4, 0, 0x2211}, {22, 16, 2, 1, 0x0}, {9, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData147_CONVOLVE_SCALE_3X3_16S[] = {{24, 16, 4, 0, 0x2211}, {24, 16, 2, 1, 0x0}, {9, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData148_CONVOLVE_SCALE_3X3_16S[] = {{26, 16, 4, 0, 0x2211}, {26, 16, 2, 1, 0x0}, {9, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData149_CONVOLVE_SCALE_3X3_16S[] = {{2, 18, 4, 0, 0x2211}, {2, 18, 2, 1, 0x0}, {9, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData150_CONVOLVE_SCALE_3X3_16S[] = {{4, 18, 4, 0, 0x2211}, {4, 18, 2, 1, 0x0}, {9, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData151_CONVOLVE_SCALE_3X3_16S[] = {{6, 18, 4, 0, 0x2211}, {6, 18, 2, 1, 0x0}, {9, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData152_CONVOLVE_SCALE_3X3_16S[] = {{8, 18, 4, 0, 0x2211}, {8, 18, 2, 1, 0x0}, {9, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData153_CONVOLVE_SCALE_3X3_16S[] = {{10, 18, 4, 0, 0x2211}, {10, 18, 2, 1, 0x0}, {9, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData154_CONVOLVE_SCALE_3X3_16S[] = {{12, 18, 4, 0, 0x2211}, {12, 18, 2, 1, 0x0}, {9, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData155_CONVOLVE_SCALE_3X3_16S[] = {{14, 18, 4, 0, 0x2211}, {14, 18, 2, 1, 0x0}, {9, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData156_CONVOLVE_SCALE_3X3_16S[] = {{16, 18, 4, 0, 0x2211}, {16, 18, 2, 1, 0x0}, {9, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData157_CONVOLVE_SCALE_3X3_16S[] = {{18, 18, 4, 0, 0x2211}, {18, 18, 2, 1, 0x0}, {9, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData158_CONVOLVE_SCALE_3X3_16S[] = {{20, 18, 4, 0, 0x2211}, {20, 18, 2, 1, 0x0}, {9, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData159_CONVOLVE_SCALE_3X3_16S[] = {{22, 18, 4, 0, 0x2211}, {22, 18, 2, 1, 0x0}, {9, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData160_CONVOLVE_SCALE_3X3_16S[] = {{24, 18, 4, 0, 0x2211}, {24, 18, 2, 1, 0x0}, {9, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData161_CONVOLVE_SCALE_3X3_16S[] = {{2, 20, 4, 0, 0x2211}, {2, 20, 2, 1, 0x0}, {9, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData162_CONVOLVE_SCALE_3X3_16S[] = {{4, 20, 4, 0, 0x2211}, {4, 20, 2, 1, 0x0}, {9, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData163_CONVOLVE_SCALE_3X3_16S[] = {{6, 20, 4, 0, 0x2211}, {6, 20, 2, 1, 0x0}, {9, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData164_CONVOLVE_SCALE_3X3_16S[] = {{8, 20, 4, 0, 0x2211}, {8, 20, 2, 1, 0x0}, {9, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData165_CONVOLVE_SCALE_3X3_16S[] = {{10, 20, 4, 0, 0x2211}, {10, 20, 2, 1, 0x0}, {9, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData166_CONVOLVE_SCALE_3X3_16S[] = {{12, 20, 4, 0, 0x2211}, {12, 20, 2, 1, 0x0}, {9, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData167_CONVOLVE_SCALE_3X3_16S[] = {{14, 20, 4, 0, 0x2211}, {14, 20, 2, 1, 0x0}, {9, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData168_CONVOLVE_SCALE_3X3_16S[] = {{16, 20, 4, 0, 0x2211}, {16, 20, 2, 1, 0x0}, {9, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData169_CONVOLVE_SCALE_3X3_16S[] = {{18, 20, 4, 0, 0x2211}, {18, 20, 2, 1, 0x0}, {9, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData170_CONVOLVE_SCALE_3X3_16S[] = {{20, 20, 4, 0, 0x2211}, {20, 20, 2, 1, 0x0}, {9, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData171_CONVOLVE_SCALE_3X3_16S[] = {{2, 22, 4, 0, 0x2211}, {2, 22, 2, 1, 0x0}, {9, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData172_CONVOLVE_SCALE_3X3_16S[] = {{4, 22, 4, 0, 0x2211}, {4, 22, 2, 1, 0x0}, {9, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData173_CONVOLVE_SCALE_3X3_16S[] = {{6, 22, 4, 0, 0x2211}, {6, 22, 2, 1, 0x0}, {9, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData174_CONVOLVE_SCALE_3X3_16S[] = {{8, 22, 4, 0, 0x2211}, {8, 22, 2, 1, 0x0}, {9, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData175_CONVOLVE_SCALE_3X3_16S[] = {{10, 22, 4, 0, 0x2211}, {10, 22, 2, 1, 0x0}, {9, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData176_CONVOLVE_SCALE_3X3_16S[] = {{12, 22, 4, 0, 0x2211}, {12, 22, 2, 1, 0x0}, {9, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData177_CONVOLVE_SCALE_3X3_16S[] = {{14, 22, 4, 0, 0x2211}, {14, 22, 2, 1, 0x0}, {9, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData178_CONVOLVE_SCALE_3X3_16S[] = {{16, 22, 4, 0, 0x2211}, {16, 22, 2, 1, 0x0}, {9, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData179_CONVOLVE_SCALE_3X3_16S[] = {{18, 22, 4, 0, 0x2211}, {18, 22, 2, 1, 0x0}, {9, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData180_CONVOLVE_SCALE_3X3_16S[] = {{2, 24, 4, 0, 0x2211}, {2, 24, 2, 1, 0x0}, {9, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData181_CONVOLVE_SCALE_3X3_16S[] = {{4, 24, 4, 0, 0x2211}, {4, 24, 2, 1, 0x0}, {9, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData182_CONVOLVE_SCALE_3X3_16S[] = {{6, 24, 4, 0, 0x2211}, {6, 24, 2, 1, 0x0}, {9, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData183_CONVOLVE_SCALE_3X3_16S[] = {{8, 24, 4, 0, 0x2211}, {8, 24, 2, 1, 0x0}, {9, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData184_CONVOLVE_SCALE_3X3_16S[] = {{10, 24, 4, 0, 0x2211}, {10, 24, 2, 1, 0x0}, {9, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData185_CONVOLVE_SCALE_3X3_16S[] = {{12, 24, 4, 0, 0x2211}, {12, 24, 2, 1, 0x0}, {9, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData186_CONVOLVE_SCALE_3X3_16S[] = {{14, 24, 4, 0, 0x2211}, {14, 24, 2, 1, 0x0}, {9, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData187_CONVOLVE_SCALE_3X3_16S[] = {{16, 24, 4, 0, 0x2211}, {16, 24, 2, 1, 0x0}, {9, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData188_CONVOLVE_SCALE_3X3_16S[] = {{2, 26, 4, 0, 0x2211}, {2, 26, 2, 1, 0x0}, {9, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData189_CONVOLVE_SCALE_3X3_16S[] = {{4, 26, 4, 0, 0x2211}, {4, 26, 2, 1, 0x0}, {9, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData190_CONVOLVE_SCALE_3X3_16S[] = {{6, 26, 4, 0, 0x2211}, {6, 26, 2, 1, 0x0}, {9, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData191_CONVOLVE_SCALE_3X3_16S[] = {{8, 26, 4, 0, 0x2211}, {8, 26, 2, 1, 0x0}, {9, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData192_CONVOLVE_SCALE_3X3_16S[] = {{10, 26, 4, 0, 0x2211}, {10, 26, 2, 1, 0x0}, {9, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData193_CONVOLVE_SCALE_3X3_16S[] = {{12, 26, 4, 0, 0x2211}, {12, 26, 2, 1, 0x0}, {9, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData194_CONVOLVE_SCALE_3X3_16S[] = {{14, 26, 4, 0, 0x2211}, {14, 26, 2, 1, 0x0}, {9, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData195_CONVOLVE_SCALE_3X3_16S[] = {{16, 26, 4, 0, 0x2211}, {16, 26, 2, 1, 0x0}, {9, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData196_CONVOLVE_SCALE_3X3_16S[] = {{2, 28, 4, 0, 0x2211}, {2, 28, 2, 1, 0x0}, {9, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData197_CONVOLVE_SCALE_3X3_16S[] = {{4, 28, 4, 0, 0x2211}, {4, 28, 2, 1, 0x0}, {9, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData198_CONVOLVE_SCALE_3X3_16S[] = {{6, 28, 4, 0, 0x2211}, {6, 28, 2, 1, 0x0}, {9, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData199_CONVOLVE_SCALE_3X3_16S[] = {{8, 28, 4, 0, 0x2211}, {8, 28, 2, 1, 0x0}, {9, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData200_CONVOLVE_SCALE_3X3_16S[] = {{10, 28, 4, 0, 0x2211}, {10, 28, 2, 1, 0x0}, {9, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData201_CONVOLVE_SCALE_3X3_16S[] = {{12, 28, 4, 0, 0x2211}, {12, 28, 2, 1, 0x0}, {9, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData202_CONVOLVE_SCALE_3X3_16S[] = {{14, 28, 4, 0, 0x2211}, {14, 28, 2, 1, 0x0}, {9, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData203_CONVOLVE_SCALE_3X3_16S[] = {{2, 30, 4, 0, 0x2211}, {2, 30, 2, 1, 0x0}, {9, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData204_CONVOLVE_SCALE_3X3_16S[] = {{4, 30, 4, 0, 0x2211}, {4, 30, 2, 1, 0x0}, {9, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData205_CONVOLVE_SCALE_3X3_16S[] = {{6, 30, 4, 0, 0x2211}, {6, 30, 2, 1, 0x0}, {9, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData206_CONVOLVE_SCALE_3X3_16S[] = {{8, 30, 4, 0, 0x2211}, {8, 30, 2, 1, 0x0}, {9, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData207_CONVOLVE_SCALE_3X3_16S[] = {{10, 30, 4, 0, 0x2211}, {10, 30, 2, 1, 0x0}, {9, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData208_CONVOLVE_SCALE_3X3_16S[] = {{12, 30, 4, 0, 0x2211}, {12, 30, 2, 1, 0x0}, {9, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData209_CONVOLVE_SCALE_3X3_16S[] = {{2, 32, 4, 0, 0x2211}, {2, 32, 2, 1, 0x0}, {9, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData210_CONVOLVE_SCALE_3X3_16S[] = {{4, 32, 4, 0, 0x2211}, {4, 32, 2, 1, 0x0}, {9, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData211_CONVOLVE_SCALE_3X3_16S[] = {{6, 32, 4, 0, 0x2211}, {6, 32, 2, 1, 0x0}, {9, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData212_CONVOLVE_SCALE_3X3_16S[] = {{8, 32, 4, 0, 0x2211}, {8, 32, 2, 1, 0x0}, {9, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData213_CONVOLVE_SCALE_3X3_16S[] = {{10, 32, 4, 0, 0x2211}, {10, 32, 2, 1, 0x0}, {9, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData214_CONVOLVE_SCALE_3X3_16S[] = {{12, 32, 4, 0, 0x2211}, {12, 32, 2, 1, 0x0}, {9, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};

static acf_scenario_kernel_data gScenarioKernelData0_CONVOLVE_SCALE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData1_CONVOLVE_SCALE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData2_CONVOLVE_SCALE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData3_CONVOLVE_SCALE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData4_CONVOLVE_SCALE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData5_CONVOLVE_SCALE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData6_CONVOLVE_SCALE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData7_CONVOLVE_SCALE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData8_CONVOLVE_SCALE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData9_CONVOLVE_SCALE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData10_CONVOLVE_SCALE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData11_CONVOLVE_SCALE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData12_CONVOLVE_SCALE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData13_CONVOLVE_SCALE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData14_CONVOLVE_SCALE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData15_CONVOLVE_SCALE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData16_CONVOLVE_SCALE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData17_CONVOLVE_SCALE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData18_CONVOLVE_SCALE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData19_CONVOLVE_SCALE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData20_CONVOLVE_SCALE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData21_CONVOLVE_SCALE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData22_CONVOLVE_SCALE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData23_CONVOLVE_SCALE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData24_CONVOLVE_SCALE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData25_CONVOLVE_SCALE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData26_CONVOLVE_SCALE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData27_CONVOLVE_SCALE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData28_CONVOLVE_SCALE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData29_CONVOLVE_SCALE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData30_CONVOLVE_SCALE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData31_CONVOLVE_SCALE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData32_CONVOLVE_SCALE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData33_CONVOLVE_SCALE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData34_CONVOLVE_SCALE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData35_CONVOLVE_SCALE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData36_CONVOLVE_SCALE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData37_CONVOLVE_SCALE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData38_CONVOLVE_SCALE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData39_CONVOLVE_SCALE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData40_CONVOLVE_SCALE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData41_CONVOLVE_SCALE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData42_CONVOLVE_SCALE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData43_CONVOLVE_SCALE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData44_CONVOLVE_SCALE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData45_CONVOLVE_SCALE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData46_CONVOLVE_SCALE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData47_CONVOLVE_SCALE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData48_CONVOLVE_SCALE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData49_CONVOLVE_SCALE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData50_CONVOLVE_SCALE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData51_CONVOLVE_SCALE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData52_CONVOLVE_SCALE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData53_CONVOLVE_SCALE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData54_CONVOLVE_SCALE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData55_CONVOLVE_SCALE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData56_CONVOLVE_SCALE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData57_CONVOLVE_SCALE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData58_CONVOLVE_SCALE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData59_CONVOLVE_SCALE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData60_CONVOLVE_SCALE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData61_CONVOLVE_SCALE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData62_CONVOLVE_SCALE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData63_CONVOLVE_SCALE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData64_CONVOLVE_SCALE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData65_CONVOLVE_SCALE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData66_CONVOLVE_SCALE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData67_CONVOLVE_SCALE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData68_CONVOLVE_SCALE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData69_CONVOLVE_SCALE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData70_CONVOLVE_SCALE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData71_CONVOLVE_SCALE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData72_CONVOLVE_SCALE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData73_CONVOLVE_SCALE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData74_CONVOLVE_SCALE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData75_CONVOLVE_SCALE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData76_CONVOLVE_SCALE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData77_CONVOLVE_SCALE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData78_CONVOLVE_SCALE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData79_CONVOLVE_SCALE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData80_CONVOLVE_SCALE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData81_CONVOLVE_SCALE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData82_CONVOLVE_SCALE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData83_CONVOLVE_SCALE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData84_CONVOLVE_SCALE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData85_CONVOLVE_SCALE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData86_CONVOLVE_SCALE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData87_CONVOLVE_SCALE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData88_CONVOLVE_SCALE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData89_CONVOLVE_SCALE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData90_CONVOLVE_SCALE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData91_CONVOLVE_SCALE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData92_CONVOLVE_SCALE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData93_CONVOLVE_SCALE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData94_CONVOLVE_SCALE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData95_CONVOLVE_SCALE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData96_CONVOLVE_SCALE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData97_CONVOLVE_SCALE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData98_CONVOLVE_SCALE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData99_CONVOLVE_SCALE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData100_CONVOLVE_SCALE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData101_CONVOLVE_SCALE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData102_CONVOLVE_SCALE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData103_CONVOLVE_SCALE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData104_CONVOLVE_SCALE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData105_CONVOLVE_SCALE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData106_CONVOLVE_SCALE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData107_CONVOLVE_SCALE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData108_CONVOLVE_SCALE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData109_CONVOLVE_SCALE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData110_CONVOLVE_SCALE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData111_CONVOLVE_SCALE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData112_CONVOLVE_SCALE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData113_CONVOLVE_SCALE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData114_CONVOLVE_SCALE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData115_CONVOLVE_SCALE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData116_CONVOLVE_SCALE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData117_CONVOLVE_SCALE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData118_CONVOLVE_SCALE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData119_CONVOLVE_SCALE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData120_CONVOLVE_SCALE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData121_CONVOLVE_SCALE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData122_CONVOLVE_SCALE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData123_CONVOLVE_SCALE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData124_CONVOLVE_SCALE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData125_CONVOLVE_SCALE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData126_CONVOLVE_SCALE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData127_CONVOLVE_SCALE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData128_CONVOLVE_SCALE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData129_CONVOLVE_SCALE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData130_CONVOLVE_SCALE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData131_CONVOLVE_SCALE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData132_CONVOLVE_SCALE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData133_CONVOLVE_SCALE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData134_CONVOLVE_SCALE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData135_CONVOLVE_SCALE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData136_CONVOLVE_SCALE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData137_CONVOLVE_SCALE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData138_CONVOLVE_SCALE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData139_CONVOLVE_SCALE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData140_CONVOLVE_SCALE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData141_CONVOLVE_SCALE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData142_CONVOLVE_SCALE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData143_CONVOLVE_SCALE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData144_CONVOLVE_SCALE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData145_CONVOLVE_SCALE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData146_CONVOLVE_SCALE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData147_CONVOLVE_SCALE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData148_CONVOLVE_SCALE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData149_CONVOLVE_SCALE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData150_CONVOLVE_SCALE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData151_CONVOLVE_SCALE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData152_CONVOLVE_SCALE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData153_CONVOLVE_SCALE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData154_CONVOLVE_SCALE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData155_CONVOLVE_SCALE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData156_CONVOLVE_SCALE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData157_CONVOLVE_SCALE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData158_CONVOLVE_SCALE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData159_CONVOLVE_SCALE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData160_CONVOLVE_SCALE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData161_CONVOLVE_SCALE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData162_CONVOLVE_SCALE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData163_CONVOLVE_SCALE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData164_CONVOLVE_SCALE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData165_CONVOLVE_SCALE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData166_CONVOLVE_SCALE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData167_CONVOLVE_SCALE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData168_CONVOLVE_SCALE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData169_CONVOLVE_SCALE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData170_CONVOLVE_SCALE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData171_CONVOLVE_SCALE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData172_CONVOLVE_SCALE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData173_CONVOLVE_SCALE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData174_CONVOLVE_SCALE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData175_CONVOLVE_SCALE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData176_CONVOLVE_SCALE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData177_CONVOLVE_SCALE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData178_CONVOLVE_SCALE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData179_CONVOLVE_SCALE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData180_CONVOLVE_SCALE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData181_CONVOLVE_SCALE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData182_CONVOLVE_SCALE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData183_CONVOLVE_SCALE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData184_CONVOLVE_SCALE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData185_CONVOLVE_SCALE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData186_CONVOLVE_SCALE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData187_CONVOLVE_SCALE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData188_CONVOLVE_SCALE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData189_CONVOLVE_SCALE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData190_CONVOLVE_SCALE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData191_CONVOLVE_SCALE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData192_CONVOLVE_SCALE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData193_CONVOLVE_SCALE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData194_CONVOLVE_SCALE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData195_CONVOLVE_SCALE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData196_CONVOLVE_SCALE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData197_CONVOLVE_SCALE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData198_CONVOLVE_SCALE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData199_CONVOLVE_SCALE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData200_CONVOLVE_SCALE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData201_CONVOLVE_SCALE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData202_CONVOLVE_SCALE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData203_CONVOLVE_SCALE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData204_CONVOLVE_SCALE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData205_CONVOLVE_SCALE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData206_CONVOLVE_SCALE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData207_CONVOLVE_SCALE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData208_CONVOLVE_SCALE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData209_CONVOLVE_SCALE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData210_CONVOLVE_SCALE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData211_CONVOLVE_SCALE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData212_CONVOLVE_SCALE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData213_CONVOLVE_SCALE_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData214_CONVOLVE_SCALE_3X3_16S[] = {{1}};

static acf_scenario gScenarioArray_CONVOLVE_SCALE_3X3_16S[] = {
{2, 1, 44, 24, 1, gScenarioBufferData0_CONVOLVE_SCALE_3X3_16S, 40, gScenarioKernelData0_CONVOLVE_SCALE_3X3_16S, 2},
{4, 1, 64, 24, 1, gScenarioBufferData1_CONVOLVE_SCALE_3X3_16S, 40, gScenarioKernelData1_CONVOLVE_SCALE_3X3_16S, 2},
{6, 1, 84, 24, 1, gScenarioBufferData2_CONVOLVE_SCALE_3X3_16S, 40, gScenarioKernelData2_CONVOLVE_SCALE_3X3_16S, 2},
{8, 1, 104, 24, 1, gScenarioBufferData3_CONVOLVE_SCALE_3X3_16S, 40, gScenarioKernelData3_CONVOLVE_SCALE_3X3_16S, 2},
{10, 1, 124, 24, 1, gScenarioBufferData4_CONVOLVE_SCALE_3X3_16S, 40, gScenarioKernelData4_CONVOLVE_SCALE_3X3_16S, 2},
{12, 1, 144, 24, 1, gScenarioBufferData5_CONVOLVE_SCALE_3X3_16S, 40, gScenarioKernelData5_CONVOLVE_SCALE_3X3_16S, 2},
{14, 1, 164, 24, 1, gScenarioBufferData6_CONVOLVE_SCALE_3X3_16S, 40, gScenarioKernelData6_CONVOLVE_SCALE_3X3_16S, 2},
{16, 1, 184, 24, 1, gScenarioBufferData7_CONVOLVE_SCALE_3X3_16S, 40, gScenarioKernelData7_CONVOLVE_SCALE_3X3_16S, 2},
{18, 1, 204, 24, 1, gScenarioBufferData8_CONVOLVE_SCALE_3X3_16S, 40, gScenarioKernelData8_CONVOLVE_SCALE_3X3_16S, 2},
{20, 1, 224, 24, 1, gScenarioBufferData9_CONVOLVE_SCALE_3X3_16S, 40, gScenarioKernelData9_CONVOLVE_SCALE_3X3_16S, 2},
{22, 1, 244, 24, 1, gScenarioBufferData10_CONVOLVE_SCALE_3X3_16S, 40, gScenarioKernelData10_CONVOLVE_SCALE_3X3_16S, 2},
{24, 1, 264, 24, 1, gScenarioBufferData11_CONVOLVE_SCALE_3X3_16S, 40, gScenarioKernelData11_CONVOLVE_SCALE_3X3_16S, 2},
{26, 1, 284, 24, 1, gScenarioBufferData12_CONVOLVE_SCALE_3X3_16S, 40, gScenarioKernelData12_CONVOLVE_SCALE_3X3_16S, 2},
{28, 1, 304, 24, 1, gScenarioBufferData13_CONVOLVE_SCALE_3X3_16S, 40, gScenarioKernelData13_CONVOLVE_SCALE_3X3_16S, 2},
{30, 1, 324, 24, 1, gScenarioBufferData14_CONVOLVE_SCALE_3X3_16S, 40, gScenarioKernelData14_CONVOLVE_SCALE_3X3_16S, 2},
{32, 1, 344, 24, 1, gScenarioBufferData15_CONVOLVE_SCALE_3X3_16S, 40, gScenarioKernelData15_CONVOLVE_SCALE_3X3_16S, 2},
{48, 1, 504, 24, 1, gScenarioBufferData16_CONVOLVE_SCALE_3X3_16S, 40, gScenarioKernelData16_CONVOLVE_SCALE_3X3_16S, 2},
{64, 1, 664, 24, 1, gScenarioBufferData17_CONVOLVE_SCALE_3X3_16S, 40, gScenarioKernelData17_CONVOLVE_SCALE_3X3_16S, 2},
{2, 2, 76, 24, 1, gScenarioBufferData18_CONVOLVE_SCALE_3X3_16S, 40, gScenarioKernelData18_CONVOLVE_SCALE_3X3_16S, 2},
{4, 2, 112, 24, 1, gScenarioBufferData19_CONVOLVE_SCALE_3X3_16S, 40, gScenarioKernelData19_CONVOLVE_SCALE_3X3_16S, 2},
{6, 2, 148, 24, 1, gScenarioBufferData20_CONVOLVE_SCALE_3X3_16S, 40, gScenarioKernelData20_CONVOLVE_SCALE_3X3_16S, 2},
{8, 2, 184, 24, 1, gScenarioBufferData21_CONVOLVE_SCALE_3X3_16S, 40, gScenarioKernelData21_CONVOLVE_SCALE_3X3_16S, 2},
{10, 2, 220, 24, 1, gScenarioBufferData22_CONVOLVE_SCALE_3X3_16S, 40, gScenarioKernelData22_CONVOLVE_SCALE_3X3_16S, 2},
{12, 2, 256, 24, 1, gScenarioBufferData23_CONVOLVE_SCALE_3X3_16S, 40, gScenarioKernelData23_CONVOLVE_SCALE_3X3_16S, 2},
{14, 2, 292, 24, 1, gScenarioBufferData24_CONVOLVE_SCALE_3X3_16S, 40, gScenarioKernelData24_CONVOLVE_SCALE_3X3_16S, 2},
{16, 2, 328, 24, 1, gScenarioBufferData25_CONVOLVE_SCALE_3X3_16S, 40, gScenarioKernelData25_CONVOLVE_SCALE_3X3_16S, 2},
{18, 2, 364, 24, 1, gScenarioBufferData26_CONVOLVE_SCALE_3X3_16S, 40, gScenarioKernelData26_CONVOLVE_SCALE_3X3_16S, 2},
{20, 2, 400, 24, 1, gScenarioBufferData27_CONVOLVE_SCALE_3X3_16S, 40, gScenarioKernelData27_CONVOLVE_SCALE_3X3_16S, 2},
{22, 2, 436, 24, 1, gScenarioBufferData28_CONVOLVE_SCALE_3X3_16S, 40, gScenarioKernelData28_CONVOLVE_SCALE_3X3_16S, 2},
{24, 2, 472, 24, 1, gScenarioBufferData29_CONVOLVE_SCALE_3X3_16S, 40, gScenarioKernelData29_CONVOLVE_SCALE_3X3_16S, 2},
{26, 2, 508, 24, 1, gScenarioBufferData30_CONVOLVE_SCALE_3X3_16S, 40, gScenarioKernelData30_CONVOLVE_SCALE_3X3_16S, 2},
{28, 2, 544, 24, 1, gScenarioBufferData31_CONVOLVE_SCALE_3X3_16S, 40, gScenarioKernelData31_CONVOLVE_SCALE_3X3_16S, 2},
{30, 2, 580, 24, 1, gScenarioBufferData32_CONVOLVE_SCALE_3X3_16S, 40, gScenarioKernelData32_CONVOLVE_SCALE_3X3_16S, 2},
{32, 2, 616, 24, 1, gScenarioBufferData33_CONVOLVE_SCALE_3X3_16S, 40, gScenarioKernelData33_CONVOLVE_SCALE_3X3_16S, 2},
{48, 2, 904, 24, 1, gScenarioBufferData34_CONVOLVE_SCALE_3X3_16S, 40, gScenarioKernelData34_CONVOLVE_SCALE_3X3_16S, 2},
{64, 2, 1192, 24, 1, gScenarioBufferData35_CONVOLVE_SCALE_3X3_16S, 40, gScenarioKernelData35_CONVOLVE_SCALE_3X3_16S, 2},
{2, 4, 140, 24, 1, gScenarioBufferData36_CONVOLVE_SCALE_3X3_16S, 40, gScenarioKernelData36_CONVOLVE_SCALE_3X3_16S, 2},
{4, 4, 208, 24, 1, gScenarioBufferData37_CONVOLVE_SCALE_3X3_16S, 40, gScenarioKernelData37_CONVOLVE_SCALE_3X3_16S, 2},
{6, 4, 276, 24, 1, gScenarioBufferData38_CONVOLVE_SCALE_3X3_16S, 40, gScenarioKernelData38_CONVOLVE_SCALE_3X3_16S, 2},
{8, 4, 344, 24, 1, gScenarioBufferData39_CONVOLVE_SCALE_3X3_16S, 40, gScenarioKernelData39_CONVOLVE_SCALE_3X3_16S, 2},
{10, 4, 412, 24, 1, gScenarioBufferData40_CONVOLVE_SCALE_3X3_16S, 40, gScenarioKernelData40_CONVOLVE_SCALE_3X3_16S, 2},
{12, 4, 480, 24, 1, gScenarioBufferData41_CONVOLVE_SCALE_3X3_16S, 40, gScenarioKernelData41_CONVOLVE_SCALE_3X3_16S, 2},
{14, 4, 548, 24, 1, gScenarioBufferData42_CONVOLVE_SCALE_3X3_16S, 40, gScenarioKernelData42_CONVOLVE_SCALE_3X3_16S, 2},
{16, 4, 616, 24, 1, gScenarioBufferData43_CONVOLVE_SCALE_3X3_16S, 40, gScenarioKernelData43_CONVOLVE_SCALE_3X3_16S, 2},
{18, 4, 684, 24, 1, gScenarioBufferData44_CONVOLVE_SCALE_3X3_16S, 40, gScenarioKernelData44_CONVOLVE_SCALE_3X3_16S, 2},
{20, 4, 752, 24, 1, gScenarioBufferData45_CONVOLVE_SCALE_3X3_16S, 40, gScenarioKernelData45_CONVOLVE_SCALE_3X3_16S, 2},
{22, 4, 820, 24, 1, gScenarioBufferData46_CONVOLVE_SCALE_3X3_16S, 40, gScenarioKernelData46_CONVOLVE_SCALE_3X3_16S, 2},
{24, 4, 888, 24, 1, gScenarioBufferData47_CONVOLVE_SCALE_3X3_16S, 40, gScenarioKernelData47_CONVOLVE_SCALE_3X3_16S, 2},
{26, 4, 956, 24, 1, gScenarioBufferData48_CONVOLVE_SCALE_3X3_16S, 40, gScenarioKernelData48_CONVOLVE_SCALE_3X3_16S, 2},
{28, 4, 1024, 24, 1, gScenarioBufferData49_CONVOLVE_SCALE_3X3_16S, 40, gScenarioKernelData49_CONVOLVE_SCALE_3X3_16S, 2},
{30, 4, 1092, 24, 1, gScenarioBufferData50_CONVOLVE_SCALE_3X3_16S, 40, gScenarioKernelData50_CONVOLVE_SCALE_3X3_16S, 2},
{32, 4, 1160, 24, 1, gScenarioBufferData51_CONVOLVE_SCALE_3X3_16S, 40, gScenarioKernelData51_CONVOLVE_SCALE_3X3_16S, 2},
{48, 4, 1704, 24, 1, gScenarioBufferData52_CONVOLVE_SCALE_3X3_16S, 40, gScenarioKernelData52_CONVOLVE_SCALE_3X3_16S, 2},
{64, 4, 2248, 24, 1, gScenarioBufferData53_CONVOLVE_SCALE_3X3_16S, 40, gScenarioKernelData53_CONVOLVE_SCALE_3X3_16S, 2},
{2, 6, 204, 24, 1, gScenarioBufferData54_CONVOLVE_SCALE_3X3_16S, 40, gScenarioKernelData54_CONVOLVE_SCALE_3X3_16S, 2},
{4, 6, 304, 24, 1, gScenarioBufferData55_CONVOLVE_SCALE_3X3_16S, 40, gScenarioKernelData55_CONVOLVE_SCALE_3X3_16S, 2},
{6, 6, 404, 24, 1, gScenarioBufferData56_CONVOLVE_SCALE_3X3_16S, 40, gScenarioKernelData56_CONVOLVE_SCALE_3X3_16S, 2},
{8, 6, 504, 24, 1, gScenarioBufferData57_CONVOLVE_SCALE_3X3_16S, 40, gScenarioKernelData57_CONVOLVE_SCALE_3X3_16S, 2},
{10, 6, 604, 24, 1, gScenarioBufferData58_CONVOLVE_SCALE_3X3_16S, 40, gScenarioKernelData58_CONVOLVE_SCALE_3X3_16S, 2},
{12, 6, 704, 24, 1, gScenarioBufferData59_CONVOLVE_SCALE_3X3_16S, 40, gScenarioKernelData59_CONVOLVE_SCALE_3X3_16S, 2},
{14, 6, 804, 24, 1, gScenarioBufferData60_CONVOLVE_SCALE_3X3_16S, 40, gScenarioKernelData60_CONVOLVE_SCALE_3X3_16S, 2},
{16, 6, 904, 24, 1, gScenarioBufferData61_CONVOLVE_SCALE_3X3_16S, 40, gScenarioKernelData61_CONVOLVE_SCALE_3X3_16S, 2},
{18, 6, 1004, 24, 1, gScenarioBufferData62_CONVOLVE_SCALE_3X3_16S, 40, gScenarioKernelData62_CONVOLVE_SCALE_3X3_16S, 2},
{20, 6, 1104, 24, 1, gScenarioBufferData63_CONVOLVE_SCALE_3X3_16S, 40, gScenarioKernelData63_CONVOLVE_SCALE_3X3_16S, 2},
{22, 6, 1204, 24, 1, gScenarioBufferData64_CONVOLVE_SCALE_3X3_16S, 40, gScenarioKernelData64_CONVOLVE_SCALE_3X3_16S, 2},
{24, 6, 1304, 24, 1, gScenarioBufferData65_CONVOLVE_SCALE_3X3_16S, 40, gScenarioKernelData65_CONVOLVE_SCALE_3X3_16S, 2},
{26, 6, 1404, 24, 1, gScenarioBufferData66_CONVOLVE_SCALE_3X3_16S, 40, gScenarioKernelData66_CONVOLVE_SCALE_3X3_16S, 2},
{28, 6, 1504, 24, 1, gScenarioBufferData67_CONVOLVE_SCALE_3X3_16S, 40, gScenarioKernelData67_CONVOLVE_SCALE_3X3_16S, 2},
{30, 6, 1604, 24, 1, gScenarioBufferData68_CONVOLVE_SCALE_3X3_16S, 40, gScenarioKernelData68_CONVOLVE_SCALE_3X3_16S, 2},
{32, 6, 1704, 24, 1, gScenarioBufferData69_CONVOLVE_SCALE_3X3_16S, 40, gScenarioKernelData69_CONVOLVE_SCALE_3X3_16S, 2},
{48, 6, 2504, 24, 1, gScenarioBufferData70_CONVOLVE_SCALE_3X3_16S, 40, gScenarioKernelData70_CONVOLVE_SCALE_3X3_16S, 2},
{64, 6, 3304, 24, 1, gScenarioBufferData71_CONVOLVE_SCALE_3X3_16S, 40, gScenarioKernelData71_CONVOLVE_SCALE_3X3_16S, 2},
{2, 8, 268, 24, 1, gScenarioBufferData72_CONVOLVE_SCALE_3X3_16S, 40, gScenarioKernelData72_CONVOLVE_SCALE_3X3_16S, 2},
{4, 8, 400, 24, 1, gScenarioBufferData73_CONVOLVE_SCALE_3X3_16S, 40, gScenarioKernelData73_CONVOLVE_SCALE_3X3_16S, 2},
{6, 8, 532, 24, 1, gScenarioBufferData74_CONVOLVE_SCALE_3X3_16S, 40, gScenarioKernelData74_CONVOLVE_SCALE_3X3_16S, 2},
{8, 8, 664, 24, 1, gScenarioBufferData75_CONVOLVE_SCALE_3X3_16S, 40, gScenarioKernelData75_CONVOLVE_SCALE_3X3_16S, 2},
{10, 8, 796, 24, 1, gScenarioBufferData76_CONVOLVE_SCALE_3X3_16S, 40, gScenarioKernelData76_CONVOLVE_SCALE_3X3_16S, 2},
{12, 8, 928, 24, 1, gScenarioBufferData77_CONVOLVE_SCALE_3X3_16S, 40, gScenarioKernelData77_CONVOLVE_SCALE_3X3_16S, 2},
{14, 8, 1060, 24, 1, gScenarioBufferData78_CONVOLVE_SCALE_3X3_16S, 40, gScenarioKernelData78_CONVOLVE_SCALE_3X3_16S, 2},
{16, 8, 1192, 24, 1, gScenarioBufferData79_CONVOLVE_SCALE_3X3_16S, 40, gScenarioKernelData79_CONVOLVE_SCALE_3X3_16S, 2},
{18, 8, 1324, 24, 1, gScenarioBufferData80_CONVOLVE_SCALE_3X3_16S, 40, gScenarioKernelData80_CONVOLVE_SCALE_3X3_16S, 2},
{20, 8, 1456, 24, 1, gScenarioBufferData81_CONVOLVE_SCALE_3X3_16S, 40, gScenarioKernelData81_CONVOLVE_SCALE_3X3_16S, 2},
{22, 8, 1588, 24, 1, gScenarioBufferData82_CONVOLVE_SCALE_3X3_16S, 40, gScenarioKernelData82_CONVOLVE_SCALE_3X3_16S, 2},
{24, 8, 1720, 24, 1, gScenarioBufferData83_CONVOLVE_SCALE_3X3_16S, 40, gScenarioKernelData83_CONVOLVE_SCALE_3X3_16S, 2},
{26, 8, 1852, 24, 1, gScenarioBufferData84_CONVOLVE_SCALE_3X3_16S, 40, gScenarioKernelData84_CONVOLVE_SCALE_3X3_16S, 2},
{28, 8, 1984, 24, 1, gScenarioBufferData85_CONVOLVE_SCALE_3X3_16S, 40, gScenarioKernelData85_CONVOLVE_SCALE_3X3_16S, 2},
{30, 8, 2116, 24, 1, gScenarioBufferData86_CONVOLVE_SCALE_3X3_16S, 40, gScenarioKernelData86_CONVOLVE_SCALE_3X3_16S, 2},
{32, 8, 2248, 24, 1, gScenarioBufferData87_CONVOLVE_SCALE_3X3_16S, 40, gScenarioKernelData87_CONVOLVE_SCALE_3X3_16S, 2},
{48, 8, 3304, 24, 1, gScenarioBufferData88_CONVOLVE_SCALE_3X3_16S, 40, gScenarioKernelData88_CONVOLVE_SCALE_3X3_16S, 2},
{2, 10, 332, 24, 1, gScenarioBufferData89_CONVOLVE_SCALE_3X3_16S, 40, gScenarioKernelData89_CONVOLVE_SCALE_3X3_16S, 2},
{4, 10, 496, 24, 1, gScenarioBufferData90_CONVOLVE_SCALE_3X3_16S, 40, gScenarioKernelData90_CONVOLVE_SCALE_3X3_16S, 2},
{6, 10, 660, 24, 1, gScenarioBufferData91_CONVOLVE_SCALE_3X3_16S, 40, gScenarioKernelData91_CONVOLVE_SCALE_3X3_16S, 2},
{8, 10, 824, 24, 1, gScenarioBufferData92_CONVOLVE_SCALE_3X3_16S, 40, gScenarioKernelData92_CONVOLVE_SCALE_3X3_16S, 2},
{10, 10, 988, 24, 1, gScenarioBufferData93_CONVOLVE_SCALE_3X3_16S, 40, gScenarioKernelData93_CONVOLVE_SCALE_3X3_16S, 2},
{12, 10, 1152, 24, 1, gScenarioBufferData94_CONVOLVE_SCALE_3X3_16S, 40, gScenarioKernelData94_CONVOLVE_SCALE_3X3_16S, 2},
{14, 10, 1316, 24, 1, gScenarioBufferData95_CONVOLVE_SCALE_3X3_16S, 40, gScenarioKernelData95_CONVOLVE_SCALE_3X3_16S, 2},
{16, 10, 1480, 24, 1, gScenarioBufferData96_CONVOLVE_SCALE_3X3_16S, 40, gScenarioKernelData96_CONVOLVE_SCALE_3X3_16S, 2},
{18, 10, 1644, 24, 1, gScenarioBufferData97_CONVOLVE_SCALE_3X3_16S, 40, gScenarioKernelData97_CONVOLVE_SCALE_3X3_16S, 2},
{20, 10, 1808, 24, 1, gScenarioBufferData98_CONVOLVE_SCALE_3X3_16S, 40, gScenarioKernelData98_CONVOLVE_SCALE_3X3_16S, 2},
{22, 10, 1972, 24, 1, gScenarioBufferData99_CONVOLVE_SCALE_3X3_16S, 40, gScenarioKernelData99_CONVOLVE_SCALE_3X3_16S, 2},
{24, 10, 2136, 24, 1, gScenarioBufferData100_CONVOLVE_SCALE_3X3_16S, 40, gScenarioKernelData100_CONVOLVE_SCALE_3X3_16S, 2},
{26, 10, 2300, 24, 1, gScenarioBufferData101_CONVOLVE_SCALE_3X3_16S, 40, gScenarioKernelData101_CONVOLVE_SCALE_3X3_16S, 2},
{28, 10, 2464, 24, 1, gScenarioBufferData102_CONVOLVE_SCALE_3X3_16S, 40, gScenarioKernelData102_CONVOLVE_SCALE_3X3_16S, 2},
{30, 10, 2628, 24, 1, gScenarioBufferData103_CONVOLVE_SCALE_3X3_16S, 40, gScenarioKernelData103_CONVOLVE_SCALE_3X3_16S, 2},
{32, 10, 2792, 24, 1, gScenarioBufferData104_CONVOLVE_SCALE_3X3_16S, 40, gScenarioKernelData104_CONVOLVE_SCALE_3X3_16S, 2},
{2, 12, 396, 24, 1, gScenarioBufferData105_CONVOLVE_SCALE_3X3_16S, 40, gScenarioKernelData105_CONVOLVE_SCALE_3X3_16S, 2},
{4, 12, 592, 24, 1, gScenarioBufferData106_CONVOLVE_SCALE_3X3_16S, 40, gScenarioKernelData106_CONVOLVE_SCALE_3X3_16S, 2},
{6, 12, 788, 24, 1, gScenarioBufferData107_CONVOLVE_SCALE_3X3_16S, 40, gScenarioKernelData107_CONVOLVE_SCALE_3X3_16S, 2},
{8, 12, 984, 24, 1, gScenarioBufferData108_CONVOLVE_SCALE_3X3_16S, 40, gScenarioKernelData108_CONVOLVE_SCALE_3X3_16S, 2},
{10, 12, 1180, 24, 1, gScenarioBufferData109_CONVOLVE_SCALE_3X3_16S, 40, gScenarioKernelData109_CONVOLVE_SCALE_3X3_16S, 2},
{12, 12, 1376, 24, 1, gScenarioBufferData110_CONVOLVE_SCALE_3X3_16S, 40, gScenarioKernelData110_CONVOLVE_SCALE_3X3_16S, 2},
{14, 12, 1572, 24, 1, gScenarioBufferData111_CONVOLVE_SCALE_3X3_16S, 40, gScenarioKernelData111_CONVOLVE_SCALE_3X3_16S, 2},
{16, 12, 1768, 24, 1, gScenarioBufferData112_CONVOLVE_SCALE_3X3_16S, 40, gScenarioKernelData112_CONVOLVE_SCALE_3X3_16S, 2},
{18, 12, 1964, 24, 1, gScenarioBufferData113_CONVOLVE_SCALE_3X3_16S, 40, gScenarioKernelData113_CONVOLVE_SCALE_3X3_16S, 2},
{20, 12, 2160, 24, 1, gScenarioBufferData114_CONVOLVE_SCALE_3X3_16S, 40, gScenarioKernelData114_CONVOLVE_SCALE_3X3_16S, 2},
{22, 12, 2356, 24, 1, gScenarioBufferData115_CONVOLVE_SCALE_3X3_16S, 40, gScenarioKernelData115_CONVOLVE_SCALE_3X3_16S, 2},
{24, 12, 2552, 24, 1, gScenarioBufferData116_CONVOLVE_SCALE_3X3_16S, 40, gScenarioKernelData116_CONVOLVE_SCALE_3X3_16S, 2},
{26, 12, 2748, 24, 1, gScenarioBufferData117_CONVOLVE_SCALE_3X3_16S, 40, gScenarioKernelData117_CONVOLVE_SCALE_3X3_16S, 2},
{28, 12, 2944, 24, 1, gScenarioBufferData118_CONVOLVE_SCALE_3X3_16S, 40, gScenarioKernelData118_CONVOLVE_SCALE_3X3_16S, 2},
{30, 12, 3140, 24, 1, gScenarioBufferData119_CONVOLVE_SCALE_3X3_16S, 40, gScenarioKernelData119_CONVOLVE_SCALE_3X3_16S, 2},
{32, 12, 3336, 24, 1, gScenarioBufferData120_CONVOLVE_SCALE_3X3_16S, 40, gScenarioKernelData120_CONVOLVE_SCALE_3X3_16S, 2},
{2, 14, 460, 24, 1, gScenarioBufferData121_CONVOLVE_SCALE_3X3_16S, 40, gScenarioKernelData121_CONVOLVE_SCALE_3X3_16S, 2},
{4, 14, 688, 24, 1, gScenarioBufferData122_CONVOLVE_SCALE_3X3_16S, 40, gScenarioKernelData122_CONVOLVE_SCALE_3X3_16S, 2},
{6, 14, 916, 24, 1, gScenarioBufferData123_CONVOLVE_SCALE_3X3_16S, 40, gScenarioKernelData123_CONVOLVE_SCALE_3X3_16S, 2},
{8, 14, 1144, 24, 1, gScenarioBufferData124_CONVOLVE_SCALE_3X3_16S, 40, gScenarioKernelData124_CONVOLVE_SCALE_3X3_16S, 2},
{10, 14, 1372, 24, 1, gScenarioBufferData125_CONVOLVE_SCALE_3X3_16S, 40, gScenarioKernelData125_CONVOLVE_SCALE_3X3_16S, 2},
{12, 14, 1600, 24, 1, gScenarioBufferData126_CONVOLVE_SCALE_3X3_16S, 40, gScenarioKernelData126_CONVOLVE_SCALE_3X3_16S, 2},
{14, 14, 1828, 24, 1, gScenarioBufferData127_CONVOLVE_SCALE_3X3_16S, 40, gScenarioKernelData127_CONVOLVE_SCALE_3X3_16S, 2},
{16, 14, 2056, 24, 1, gScenarioBufferData128_CONVOLVE_SCALE_3X3_16S, 40, gScenarioKernelData128_CONVOLVE_SCALE_3X3_16S, 2},
{18, 14, 2284, 24, 1, gScenarioBufferData129_CONVOLVE_SCALE_3X3_16S, 40, gScenarioKernelData129_CONVOLVE_SCALE_3X3_16S, 2},
{20, 14, 2512, 24, 1, gScenarioBufferData130_CONVOLVE_SCALE_3X3_16S, 40, gScenarioKernelData130_CONVOLVE_SCALE_3X3_16S, 2},
{22, 14, 2740, 24, 1, gScenarioBufferData131_CONVOLVE_SCALE_3X3_16S, 40, gScenarioKernelData131_CONVOLVE_SCALE_3X3_16S, 2},
{24, 14, 2968, 24, 1, gScenarioBufferData132_CONVOLVE_SCALE_3X3_16S, 40, gScenarioKernelData132_CONVOLVE_SCALE_3X3_16S, 2},
{26, 14, 3196, 24, 1, gScenarioBufferData133_CONVOLVE_SCALE_3X3_16S, 40, gScenarioKernelData133_CONVOLVE_SCALE_3X3_16S, 2},
{28, 14, 3424, 24, 1, gScenarioBufferData134_CONVOLVE_SCALE_3X3_16S, 40, gScenarioKernelData134_CONVOLVE_SCALE_3X3_16S, 2},
{30, 14, 3652, 24, 1, gScenarioBufferData135_CONVOLVE_SCALE_3X3_16S, 40, gScenarioKernelData135_CONVOLVE_SCALE_3X3_16S, 2},
{2, 16, 524, 24, 1, gScenarioBufferData136_CONVOLVE_SCALE_3X3_16S, 40, gScenarioKernelData136_CONVOLVE_SCALE_3X3_16S, 2},
{4, 16, 784, 24, 1, gScenarioBufferData137_CONVOLVE_SCALE_3X3_16S, 40, gScenarioKernelData137_CONVOLVE_SCALE_3X3_16S, 2},
{6, 16, 1044, 24, 1, gScenarioBufferData138_CONVOLVE_SCALE_3X3_16S, 40, gScenarioKernelData138_CONVOLVE_SCALE_3X3_16S, 2},
{8, 16, 1304, 24, 1, gScenarioBufferData139_CONVOLVE_SCALE_3X3_16S, 40, gScenarioKernelData139_CONVOLVE_SCALE_3X3_16S, 2},
{10, 16, 1564, 24, 1, gScenarioBufferData140_CONVOLVE_SCALE_3X3_16S, 40, gScenarioKernelData140_CONVOLVE_SCALE_3X3_16S, 2},
{12, 16, 1824, 24, 1, gScenarioBufferData141_CONVOLVE_SCALE_3X3_16S, 40, gScenarioKernelData141_CONVOLVE_SCALE_3X3_16S, 2},
{14, 16, 2084, 24, 1, gScenarioBufferData142_CONVOLVE_SCALE_3X3_16S, 40, gScenarioKernelData142_CONVOLVE_SCALE_3X3_16S, 2},
{16, 16, 2344, 24, 1, gScenarioBufferData143_CONVOLVE_SCALE_3X3_16S, 40, gScenarioKernelData143_CONVOLVE_SCALE_3X3_16S, 2},
{18, 16, 2604, 24, 1, gScenarioBufferData144_CONVOLVE_SCALE_3X3_16S, 40, gScenarioKernelData144_CONVOLVE_SCALE_3X3_16S, 2},
{20, 16, 2864, 24, 1, gScenarioBufferData145_CONVOLVE_SCALE_3X3_16S, 40, gScenarioKernelData145_CONVOLVE_SCALE_3X3_16S, 2},
{22, 16, 3124, 24, 1, gScenarioBufferData146_CONVOLVE_SCALE_3X3_16S, 40, gScenarioKernelData146_CONVOLVE_SCALE_3X3_16S, 2},
{24, 16, 3384, 24, 1, gScenarioBufferData147_CONVOLVE_SCALE_3X3_16S, 40, gScenarioKernelData147_CONVOLVE_SCALE_3X3_16S, 2},
{26, 16, 3644, 24, 1, gScenarioBufferData148_CONVOLVE_SCALE_3X3_16S, 40, gScenarioKernelData148_CONVOLVE_SCALE_3X3_16S, 2},
{2, 18, 588, 24, 1, gScenarioBufferData149_CONVOLVE_SCALE_3X3_16S, 40, gScenarioKernelData149_CONVOLVE_SCALE_3X3_16S, 2},
{4, 18, 880, 24, 1, gScenarioBufferData150_CONVOLVE_SCALE_3X3_16S, 40, gScenarioKernelData150_CONVOLVE_SCALE_3X3_16S, 2},
{6, 18, 1172, 24, 1, gScenarioBufferData151_CONVOLVE_SCALE_3X3_16S, 40, gScenarioKernelData151_CONVOLVE_SCALE_3X3_16S, 2},
{8, 18, 1464, 24, 1, gScenarioBufferData152_CONVOLVE_SCALE_3X3_16S, 40, gScenarioKernelData152_CONVOLVE_SCALE_3X3_16S, 2},
{10, 18, 1756, 24, 1, gScenarioBufferData153_CONVOLVE_SCALE_3X3_16S, 40, gScenarioKernelData153_CONVOLVE_SCALE_3X3_16S, 2},
{12, 18, 2048, 24, 1, gScenarioBufferData154_CONVOLVE_SCALE_3X3_16S, 40, gScenarioKernelData154_CONVOLVE_SCALE_3X3_16S, 2},
{14, 18, 2340, 24, 1, gScenarioBufferData155_CONVOLVE_SCALE_3X3_16S, 40, gScenarioKernelData155_CONVOLVE_SCALE_3X3_16S, 2},
{16, 18, 2632, 24, 1, gScenarioBufferData156_CONVOLVE_SCALE_3X3_16S, 40, gScenarioKernelData156_CONVOLVE_SCALE_3X3_16S, 2},
{18, 18, 2924, 24, 1, gScenarioBufferData157_CONVOLVE_SCALE_3X3_16S, 40, gScenarioKernelData157_CONVOLVE_SCALE_3X3_16S, 2},
{20, 18, 3216, 24, 1, gScenarioBufferData158_CONVOLVE_SCALE_3X3_16S, 40, gScenarioKernelData158_CONVOLVE_SCALE_3X3_16S, 2},
{22, 18, 3508, 24, 1, gScenarioBufferData159_CONVOLVE_SCALE_3X3_16S, 40, gScenarioKernelData159_CONVOLVE_SCALE_3X3_16S, 2},
{24, 18, 3800, 24, 1, gScenarioBufferData160_CONVOLVE_SCALE_3X3_16S, 40, gScenarioKernelData160_CONVOLVE_SCALE_3X3_16S, 2},
{2, 20, 652, 24, 1, gScenarioBufferData161_CONVOLVE_SCALE_3X3_16S, 40, gScenarioKernelData161_CONVOLVE_SCALE_3X3_16S, 2},
{4, 20, 976, 24, 1, gScenarioBufferData162_CONVOLVE_SCALE_3X3_16S, 40, gScenarioKernelData162_CONVOLVE_SCALE_3X3_16S, 2},
{6, 20, 1300, 24, 1, gScenarioBufferData163_CONVOLVE_SCALE_3X3_16S, 40, gScenarioKernelData163_CONVOLVE_SCALE_3X3_16S, 2},
{8, 20, 1624, 24, 1, gScenarioBufferData164_CONVOLVE_SCALE_3X3_16S, 40, gScenarioKernelData164_CONVOLVE_SCALE_3X3_16S, 2},
{10, 20, 1948, 24, 1, gScenarioBufferData165_CONVOLVE_SCALE_3X3_16S, 40, gScenarioKernelData165_CONVOLVE_SCALE_3X3_16S, 2},
{12, 20, 2272, 24, 1, gScenarioBufferData166_CONVOLVE_SCALE_3X3_16S, 40, gScenarioKernelData166_CONVOLVE_SCALE_3X3_16S, 2},
{14, 20, 2596, 24, 1, gScenarioBufferData167_CONVOLVE_SCALE_3X3_16S, 40, gScenarioKernelData167_CONVOLVE_SCALE_3X3_16S, 2},
{16, 20, 2920, 24, 1, gScenarioBufferData168_CONVOLVE_SCALE_3X3_16S, 40, gScenarioKernelData168_CONVOLVE_SCALE_3X3_16S, 2},
{18, 20, 3244, 24, 1, gScenarioBufferData169_CONVOLVE_SCALE_3X3_16S, 40, gScenarioKernelData169_CONVOLVE_SCALE_3X3_16S, 2},
{20, 20, 3568, 24, 1, gScenarioBufferData170_CONVOLVE_SCALE_3X3_16S, 40, gScenarioKernelData170_CONVOLVE_SCALE_3X3_16S, 2},
{2, 22, 716, 24, 1, gScenarioBufferData171_CONVOLVE_SCALE_3X3_16S, 40, gScenarioKernelData171_CONVOLVE_SCALE_3X3_16S, 2},
{4, 22, 1072, 24, 1, gScenarioBufferData172_CONVOLVE_SCALE_3X3_16S, 40, gScenarioKernelData172_CONVOLVE_SCALE_3X3_16S, 2},
{6, 22, 1428, 24, 1, gScenarioBufferData173_CONVOLVE_SCALE_3X3_16S, 40, gScenarioKernelData173_CONVOLVE_SCALE_3X3_16S, 2},
{8, 22, 1784, 24, 1, gScenarioBufferData174_CONVOLVE_SCALE_3X3_16S, 40, gScenarioKernelData174_CONVOLVE_SCALE_3X3_16S, 2},
{10, 22, 2140, 24, 1, gScenarioBufferData175_CONVOLVE_SCALE_3X3_16S, 40, gScenarioKernelData175_CONVOLVE_SCALE_3X3_16S, 2},
{12, 22, 2496, 24, 1, gScenarioBufferData176_CONVOLVE_SCALE_3X3_16S, 40, gScenarioKernelData176_CONVOLVE_SCALE_3X3_16S, 2},
{14, 22, 2852, 24, 1, gScenarioBufferData177_CONVOLVE_SCALE_3X3_16S, 40, gScenarioKernelData177_CONVOLVE_SCALE_3X3_16S, 2},
{16, 22, 3208, 24, 1, gScenarioBufferData178_CONVOLVE_SCALE_3X3_16S, 40, gScenarioKernelData178_CONVOLVE_SCALE_3X3_16S, 2},
{18, 22, 3564, 24, 1, gScenarioBufferData179_CONVOLVE_SCALE_3X3_16S, 40, gScenarioKernelData179_CONVOLVE_SCALE_3X3_16S, 2},
{2, 24, 780, 24, 1, gScenarioBufferData180_CONVOLVE_SCALE_3X3_16S, 40, gScenarioKernelData180_CONVOLVE_SCALE_3X3_16S, 2},
{4, 24, 1168, 24, 1, gScenarioBufferData181_CONVOLVE_SCALE_3X3_16S, 40, gScenarioKernelData181_CONVOLVE_SCALE_3X3_16S, 2},
{6, 24, 1556, 24, 1, gScenarioBufferData182_CONVOLVE_SCALE_3X3_16S, 40, gScenarioKernelData182_CONVOLVE_SCALE_3X3_16S, 2},
{8, 24, 1944, 24, 1, gScenarioBufferData183_CONVOLVE_SCALE_3X3_16S, 40, gScenarioKernelData183_CONVOLVE_SCALE_3X3_16S, 2},
{10, 24, 2332, 24, 1, gScenarioBufferData184_CONVOLVE_SCALE_3X3_16S, 40, gScenarioKernelData184_CONVOLVE_SCALE_3X3_16S, 2},
{12, 24, 2720, 24, 1, gScenarioBufferData185_CONVOLVE_SCALE_3X3_16S, 40, gScenarioKernelData185_CONVOLVE_SCALE_3X3_16S, 2},
{14, 24, 3108, 24, 1, gScenarioBufferData186_CONVOLVE_SCALE_3X3_16S, 40, gScenarioKernelData186_CONVOLVE_SCALE_3X3_16S, 2},
{16, 24, 3496, 24, 1, gScenarioBufferData187_CONVOLVE_SCALE_3X3_16S, 40, gScenarioKernelData187_CONVOLVE_SCALE_3X3_16S, 2},
{2, 26, 844, 24, 1, gScenarioBufferData188_CONVOLVE_SCALE_3X3_16S, 40, gScenarioKernelData188_CONVOLVE_SCALE_3X3_16S, 2},
{4, 26, 1264, 24, 1, gScenarioBufferData189_CONVOLVE_SCALE_3X3_16S, 40, gScenarioKernelData189_CONVOLVE_SCALE_3X3_16S, 2},
{6, 26, 1684, 24, 1, gScenarioBufferData190_CONVOLVE_SCALE_3X3_16S, 40, gScenarioKernelData190_CONVOLVE_SCALE_3X3_16S, 2},
{8, 26, 2104, 24, 1, gScenarioBufferData191_CONVOLVE_SCALE_3X3_16S, 40, gScenarioKernelData191_CONVOLVE_SCALE_3X3_16S, 2},
{10, 26, 2524, 24, 1, gScenarioBufferData192_CONVOLVE_SCALE_3X3_16S, 40, gScenarioKernelData192_CONVOLVE_SCALE_3X3_16S, 2},
{12, 26, 2944, 24, 1, gScenarioBufferData193_CONVOLVE_SCALE_3X3_16S, 40, gScenarioKernelData193_CONVOLVE_SCALE_3X3_16S, 2},
{14, 26, 3364, 24, 1, gScenarioBufferData194_CONVOLVE_SCALE_3X3_16S, 40, gScenarioKernelData194_CONVOLVE_SCALE_3X3_16S, 2},
{16, 26, 3784, 24, 1, gScenarioBufferData195_CONVOLVE_SCALE_3X3_16S, 40, gScenarioKernelData195_CONVOLVE_SCALE_3X3_16S, 2},
{2, 28, 908, 24, 1, gScenarioBufferData196_CONVOLVE_SCALE_3X3_16S, 40, gScenarioKernelData196_CONVOLVE_SCALE_3X3_16S, 2},
{4, 28, 1360, 24, 1, gScenarioBufferData197_CONVOLVE_SCALE_3X3_16S, 40, gScenarioKernelData197_CONVOLVE_SCALE_3X3_16S, 2},
{6, 28, 1812, 24, 1, gScenarioBufferData198_CONVOLVE_SCALE_3X3_16S, 40, gScenarioKernelData198_CONVOLVE_SCALE_3X3_16S, 2},
{8, 28, 2264, 24, 1, gScenarioBufferData199_CONVOLVE_SCALE_3X3_16S, 40, gScenarioKernelData199_CONVOLVE_SCALE_3X3_16S, 2},
{10, 28, 2716, 24, 1, gScenarioBufferData200_CONVOLVE_SCALE_3X3_16S, 40, gScenarioKernelData200_CONVOLVE_SCALE_3X3_16S, 2},
{12, 28, 3168, 24, 1, gScenarioBufferData201_CONVOLVE_SCALE_3X3_16S, 40, gScenarioKernelData201_CONVOLVE_SCALE_3X3_16S, 2},
{14, 28, 3620, 24, 1, gScenarioBufferData202_CONVOLVE_SCALE_3X3_16S, 40, gScenarioKernelData202_CONVOLVE_SCALE_3X3_16S, 2},
{2, 30, 972, 24, 1, gScenarioBufferData203_CONVOLVE_SCALE_3X3_16S, 40, gScenarioKernelData203_CONVOLVE_SCALE_3X3_16S, 2},
{4, 30, 1456, 24, 1, gScenarioBufferData204_CONVOLVE_SCALE_3X3_16S, 40, gScenarioKernelData204_CONVOLVE_SCALE_3X3_16S, 2},
{6, 30, 1940, 24, 1, gScenarioBufferData205_CONVOLVE_SCALE_3X3_16S, 40, gScenarioKernelData205_CONVOLVE_SCALE_3X3_16S, 2},
{8, 30, 2424, 24, 1, gScenarioBufferData206_CONVOLVE_SCALE_3X3_16S, 40, gScenarioKernelData206_CONVOLVE_SCALE_3X3_16S, 2},
{10, 30, 2908, 24, 1, gScenarioBufferData207_CONVOLVE_SCALE_3X3_16S, 40, gScenarioKernelData207_CONVOLVE_SCALE_3X3_16S, 2},
{12, 30, 3392, 24, 1, gScenarioBufferData208_CONVOLVE_SCALE_3X3_16S, 40, gScenarioKernelData208_CONVOLVE_SCALE_3X3_16S, 2},
{2, 32, 1036, 24, 1, gScenarioBufferData209_CONVOLVE_SCALE_3X3_16S, 40, gScenarioKernelData209_CONVOLVE_SCALE_3X3_16S, 2},
{4, 32, 1552, 24, 1, gScenarioBufferData210_CONVOLVE_SCALE_3X3_16S, 40, gScenarioKernelData210_CONVOLVE_SCALE_3X3_16S, 2},
{6, 32, 2068, 24, 1, gScenarioBufferData211_CONVOLVE_SCALE_3X3_16S, 40, gScenarioKernelData211_CONVOLVE_SCALE_3X3_16S, 2},
{8, 32, 2584, 24, 1, gScenarioBufferData212_CONVOLVE_SCALE_3X3_16S, 40, gScenarioKernelData212_CONVOLVE_SCALE_3X3_16S, 2},
{10, 32, 3100, 24, 1, gScenarioBufferData213_CONVOLVE_SCALE_3X3_16S, 40, gScenarioKernelData213_CONVOLVE_SCALE_3X3_16S, 2},
{12, 32, 3616, 24, 1, gScenarioBufferData214_CONVOLVE_SCALE_3X3_16S, 40, gScenarioKernelData214_CONVOLVE_SCALE_3X3_16S, 2}
};

static acf_scenario_list gScenarioList_CONVOLVE_SCALE_3X3_16S = {
215, //number of scenarios
gScenarioArray_CONVOLVE_SCALE_3X3_16S};
//**************************************************************

class CONVOLVE_SCALE_3X3_16S : public ACF_Process_APU
{
public:
   CONVOLVE_SCALE_3X3_16S(int32_t apex_id = 0) : ACF_Process_APU(apex_id)
   {} 

   int32_t Initialize()
   {
      int32_t lRetVal = 0;

      if (!Initialized()) //initialization steps that only need to occur once
      {
         SetProcessIdentifier("CONVOLVE_SCALE_3X3_16S");
         SetApuLoadInfo(CONVOLVE_SCALE_3X3_16S_LOAD_SEGMENTS,
                        CONVOLVE_SCALE_3X3_16S_LOAD_PMEM, CONVOLVE_SCALE_3X3_16S_LOAD_PMEM_SIZE,
                        CONVOLVE_SCALE_3X3_16S_LOAD_DMEM, CONVOLVE_SCALE_3X3_16S_LOAD_DMEM_SIZE,
                        0, 0); //assuming _LOAD_CMEM does not exist
         FlagSpatialDep();

         //***NOTE: the order in which the following ports are added is meaningful; do not change!

         AddPort("INPUT_0", ICP_DATATYPE_08U, 1, 1, 2, 1, 0, 0, 0, 0, 0, 0, 0, 0x1010101);
         AddPort("F_COEFF", ICP_DATATYPE_08S, 1, 1, 9, 1, 0, 1, 1, 0, 1, 0, 2);
         AddPort("F_SCALE", ICP_DATATYPE_32S, 1, 1, 1, 1, 0, 1, 1, 0, 1, 0, 3);
         AddPort("OUTPUT_0", ICP_DATATYPE_16S, 1, 1, 2, 1, 1, 0, 0, 0, 0, 0, 1);

         CfgScenarios(&gScenarioList_CONVOLVE_SCALE_3X3_16S);

         FlagAsInitialized();
      }

      lRetVal = SelectApuConfiguration(mApuCfg, mApexId); //by default mApuCfg = ACF_APU_CFG__APEX0_DEFAULT and mApexId = 0

      return lRetVal;
   }
};

#endif //_ACF_PROCESS_APU_CONVOLVE_SCALE_3X3_16S
