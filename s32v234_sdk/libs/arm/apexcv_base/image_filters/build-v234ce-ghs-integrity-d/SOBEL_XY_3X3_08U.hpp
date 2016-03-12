#ifndef _ACF_PROCESS_APU_SOBEL_XY_3X3_08U
#define _ACF_PROCESS_APU_SOBEL_XY_3X3_08U

#include <acf_process_apu.h>
#include <SOBEL_XY_3X3_08U_APU_LOAD.h> //APU load associated with this process
#include <stdint.h>


//SCENARIO LIST*************************************************
static acf_scenario_buffer_data gScenarioBufferData0_SOBEL_XY_3X3_08U[] = {{2, 1, 4, 0, 0x2211}, {2, 1, 2, 1, 0x0}, {2, 1, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData1_SOBEL_XY_3X3_08U[] = {{4, 1, 4, 0, 0x2211}, {4, 1, 2, 1, 0x0}, {4, 1, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData2_SOBEL_XY_3X3_08U[] = {{6, 1, 4, 0, 0x2211}, {6, 1, 2, 1, 0x0}, {6, 1, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData3_SOBEL_XY_3X3_08U[] = {{8, 1, 4, 0, 0x2211}, {8, 1, 2, 1, 0x0}, {8, 1, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData4_SOBEL_XY_3X3_08U[] = {{10, 1, 4, 0, 0x2211}, {10, 1, 2, 1, 0x0}, {10, 1, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData5_SOBEL_XY_3X3_08U[] = {{12, 1, 4, 0, 0x2211}, {12, 1, 2, 1, 0x0}, {12, 1, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData6_SOBEL_XY_3X3_08U[] = {{14, 1, 4, 0, 0x2211}, {14, 1, 2, 1, 0x0}, {14, 1, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData7_SOBEL_XY_3X3_08U[] = {{16, 1, 4, 0, 0x2211}, {16, 1, 2, 1, 0x0}, {16, 1, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData8_SOBEL_XY_3X3_08U[] = {{18, 1, 4, 0, 0x2211}, {18, 1, 2, 1, 0x0}, {18, 1, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData9_SOBEL_XY_3X3_08U[] = {{20, 1, 4, 0, 0x2211}, {20, 1, 2, 1, 0x0}, {20, 1, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData10_SOBEL_XY_3X3_08U[] = {{22, 1, 4, 0, 0x2211}, {22, 1, 2, 1, 0x0}, {22, 1, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData11_SOBEL_XY_3X3_08U[] = {{24, 1, 4, 0, 0x2211}, {24, 1, 2, 1, 0x0}, {24, 1, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData12_SOBEL_XY_3X3_08U[] = {{26, 1, 4, 0, 0x2211}, {26, 1, 2, 1, 0x0}, {26, 1, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData13_SOBEL_XY_3X3_08U[] = {{28, 1, 4, 0, 0x2211}, {28, 1, 2, 1, 0x0}, {28, 1, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData14_SOBEL_XY_3X3_08U[] = {{30, 1, 4, 0, 0x2211}, {30, 1, 2, 1, 0x0}, {30, 1, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData15_SOBEL_XY_3X3_08U[] = {{32, 1, 4, 0, 0x2211}, {32, 1, 2, 1, 0x0}, {32, 1, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData16_SOBEL_XY_3X3_08U[] = {{48, 1, 4, 0, 0x2211}, {48, 1, 2, 1, 0x0}, {48, 1, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData17_SOBEL_XY_3X3_08U[] = {{64, 1, 4, 0, 0x2211}, {64, 1, 2, 1, 0x0}, {64, 1, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData18_SOBEL_XY_3X3_08U[] = {{96, 1, 4, 0, 0x2211}, {96, 1, 2, 1, 0x0}, {96, 1, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData19_SOBEL_XY_3X3_08U[] = {{112, 1, 4, 0, 0x2211}, {112, 1, 2, 1, 0x0}, {112, 1, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData20_SOBEL_XY_3X3_08U[] = {{128, 1, 4, 0, 0x2211}, {128, 1, 2, 1, 0x0}, {128, 1, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData21_SOBEL_XY_3X3_08U[] = {{2, 2, 4, 0, 0x2211}, {2, 2, 2, 1, 0x0}, {2, 2, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData22_SOBEL_XY_3X3_08U[] = {{4, 2, 4, 0, 0x2211}, {4, 2, 2, 1, 0x0}, {4, 2, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData23_SOBEL_XY_3X3_08U[] = {{6, 2, 4, 0, 0x2211}, {6, 2, 2, 1, 0x0}, {6, 2, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData24_SOBEL_XY_3X3_08U[] = {{8, 2, 4, 0, 0x2211}, {8, 2, 2, 1, 0x0}, {8, 2, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData25_SOBEL_XY_3X3_08U[] = {{10, 2, 4, 0, 0x2211}, {10, 2, 2, 1, 0x0}, {10, 2, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData26_SOBEL_XY_3X3_08U[] = {{12, 2, 4, 0, 0x2211}, {12, 2, 2, 1, 0x0}, {12, 2, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData27_SOBEL_XY_3X3_08U[] = {{14, 2, 4, 0, 0x2211}, {14, 2, 2, 1, 0x0}, {14, 2, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData28_SOBEL_XY_3X3_08U[] = {{16, 2, 4, 0, 0x2211}, {16, 2, 2, 1, 0x0}, {16, 2, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData29_SOBEL_XY_3X3_08U[] = {{18, 2, 4, 0, 0x2211}, {18, 2, 2, 1, 0x0}, {18, 2, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData30_SOBEL_XY_3X3_08U[] = {{20, 2, 4, 0, 0x2211}, {20, 2, 2, 1, 0x0}, {20, 2, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData31_SOBEL_XY_3X3_08U[] = {{22, 2, 4, 0, 0x2211}, {22, 2, 2, 1, 0x0}, {22, 2, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData32_SOBEL_XY_3X3_08U[] = {{24, 2, 4, 0, 0x2211}, {24, 2, 2, 1, 0x0}, {24, 2, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData33_SOBEL_XY_3X3_08U[] = {{26, 2, 4, 0, 0x2211}, {26, 2, 2, 1, 0x0}, {26, 2, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData34_SOBEL_XY_3X3_08U[] = {{28, 2, 4, 0, 0x2211}, {28, 2, 2, 1, 0x0}, {28, 2, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData35_SOBEL_XY_3X3_08U[] = {{30, 2, 4, 0, 0x2211}, {30, 2, 2, 1, 0x0}, {30, 2, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData36_SOBEL_XY_3X3_08U[] = {{32, 2, 4, 0, 0x2211}, {32, 2, 2, 1, 0x0}, {32, 2, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData37_SOBEL_XY_3X3_08U[] = {{48, 2, 4, 0, 0x2211}, {48, 2, 2, 1, 0x0}, {48, 2, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData38_SOBEL_XY_3X3_08U[] = {{64, 2, 4, 0, 0x2211}, {64, 2, 2, 1, 0x0}, {64, 2, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData39_SOBEL_XY_3X3_08U[] = {{96, 2, 4, 0, 0x2211}, {96, 2, 2, 1, 0x0}, {96, 2, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData40_SOBEL_XY_3X3_08U[] = {{112, 2, 4, 0, 0x2211}, {112, 2, 2, 1, 0x0}, {112, 2, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData41_SOBEL_XY_3X3_08U[] = {{128, 2, 4, 0, 0x2211}, {128, 2, 2, 1, 0x0}, {128, 2, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData42_SOBEL_XY_3X3_08U[] = {{2, 4, 4, 0, 0x2211}, {2, 4, 2, 1, 0x0}, {2, 4, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData43_SOBEL_XY_3X3_08U[] = {{4, 4, 4, 0, 0x2211}, {4, 4, 2, 1, 0x0}, {4, 4, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData44_SOBEL_XY_3X3_08U[] = {{6, 4, 4, 0, 0x2211}, {6, 4, 2, 1, 0x0}, {6, 4, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData45_SOBEL_XY_3X3_08U[] = {{8, 4, 4, 0, 0x2211}, {8, 4, 2, 1, 0x0}, {8, 4, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData46_SOBEL_XY_3X3_08U[] = {{10, 4, 4, 0, 0x2211}, {10, 4, 2, 1, 0x0}, {10, 4, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData47_SOBEL_XY_3X3_08U[] = {{12, 4, 4, 0, 0x2211}, {12, 4, 2, 1, 0x0}, {12, 4, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData48_SOBEL_XY_3X3_08U[] = {{14, 4, 4, 0, 0x2211}, {14, 4, 2, 1, 0x0}, {14, 4, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData49_SOBEL_XY_3X3_08U[] = {{16, 4, 4, 0, 0x2211}, {16, 4, 2, 1, 0x0}, {16, 4, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData50_SOBEL_XY_3X3_08U[] = {{18, 4, 4, 0, 0x2211}, {18, 4, 2, 1, 0x0}, {18, 4, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData51_SOBEL_XY_3X3_08U[] = {{20, 4, 4, 0, 0x2211}, {20, 4, 2, 1, 0x0}, {20, 4, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData52_SOBEL_XY_3X3_08U[] = {{22, 4, 4, 0, 0x2211}, {22, 4, 2, 1, 0x0}, {22, 4, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData53_SOBEL_XY_3X3_08U[] = {{24, 4, 4, 0, 0x2211}, {24, 4, 2, 1, 0x0}, {24, 4, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData54_SOBEL_XY_3X3_08U[] = {{26, 4, 4, 0, 0x2211}, {26, 4, 2, 1, 0x0}, {26, 4, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData55_SOBEL_XY_3X3_08U[] = {{28, 4, 4, 0, 0x2211}, {28, 4, 2, 1, 0x0}, {28, 4, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData56_SOBEL_XY_3X3_08U[] = {{30, 4, 4, 0, 0x2211}, {30, 4, 2, 1, 0x0}, {30, 4, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData57_SOBEL_XY_3X3_08U[] = {{32, 4, 4, 0, 0x2211}, {32, 4, 2, 1, 0x0}, {32, 4, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData58_SOBEL_XY_3X3_08U[] = {{48, 4, 4, 0, 0x2211}, {48, 4, 2, 1, 0x0}, {48, 4, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData59_SOBEL_XY_3X3_08U[] = {{64, 4, 4, 0, 0x2211}, {64, 4, 2, 1, 0x0}, {64, 4, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData60_SOBEL_XY_3X3_08U[] = {{96, 4, 4, 0, 0x2211}, {96, 4, 2, 1, 0x0}, {96, 4, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData61_SOBEL_XY_3X3_08U[] = {{2, 6, 4, 0, 0x2211}, {2, 6, 2, 1, 0x0}, {2, 6, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData62_SOBEL_XY_3X3_08U[] = {{4, 6, 4, 0, 0x2211}, {4, 6, 2, 1, 0x0}, {4, 6, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData63_SOBEL_XY_3X3_08U[] = {{6, 6, 4, 0, 0x2211}, {6, 6, 2, 1, 0x0}, {6, 6, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData64_SOBEL_XY_3X3_08U[] = {{8, 6, 4, 0, 0x2211}, {8, 6, 2, 1, 0x0}, {8, 6, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData65_SOBEL_XY_3X3_08U[] = {{10, 6, 4, 0, 0x2211}, {10, 6, 2, 1, 0x0}, {10, 6, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData66_SOBEL_XY_3X3_08U[] = {{12, 6, 4, 0, 0x2211}, {12, 6, 2, 1, 0x0}, {12, 6, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData67_SOBEL_XY_3X3_08U[] = {{14, 6, 4, 0, 0x2211}, {14, 6, 2, 1, 0x0}, {14, 6, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData68_SOBEL_XY_3X3_08U[] = {{16, 6, 4, 0, 0x2211}, {16, 6, 2, 1, 0x0}, {16, 6, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData69_SOBEL_XY_3X3_08U[] = {{18, 6, 4, 0, 0x2211}, {18, 6, 2, 1, 0x0}, {18, 6, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData70_SOBEL_XY_3X3_08U[] = {{20, 6, 4, 0, 0x2211}, {20, 6, 2, 1, 0x0}, {20, 6, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData71_SOBEL_XY_3X3_08U[] = {{22, 6, 4, 0, 0x2211}, {22, 6, 2, 1, 0x0}, {22, 6, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData72_SOBEL_XY_3X3_08U[] = {{24, 6, 4, 0, 0x2211}, {24, 6, 2, 1, 0x0}, {24, 6, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData73_SOBEL_XY_3X3_08U[] = {{26, 6, 4, 0, 0x2211}, {26, 6, 2, 1, 0x0}, {26, 6, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData74_SOBEL_XY_3X3_08U[] = {{28, 6, 4, 0, 0x2211}, {28, 6, 2, 1, 0x0}, {28, 6, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData75_SOBEL_XY_3X3_08U[] = {{30, 6, 4, 0, 0x2211}, {30, 6, 2, 1, 0x0}, {30, 6, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData76_SOBEL_XY_3X3_08U[] = {{32, 6, 4, 0, 0x2211}, {32, 6, 2, 1, 0x0}, {32, 6, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData77_SOBEL_XY_3X3_08U[] = {{48, 6, 4, 0, 0x2211}, {48, 6, 2, 1, 0x0}, {48, 6, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData78_SOBEL_XY_3X3_08U[] = {{64, 6, 4, 0, 0x2211}, {64, 6, 2, 1, 0x0}, {64, 6, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData79_SOBEL_XY_3X3_08U[] = {{2, 8, 4, 0, 0x2211}, {2, 8, 2, 1, 0x0}, {2, 8, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData80_SOBEL_XY_3X3_08U[] = {{4, 8, 4, 0, 0x2211}, {4, 8, 2, 1, 0x0}, {4, 8, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData81_SOBEL_XY_3X3_08U[] = {{6, 8, 4, 0, 0x2211}, {6, 8, 2, 1, 0x0}, {6, 8, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData82_SOBEL_XY_3X3_08U[] = {{8, 8, 4, 0, 0x2211}, {8, 8, 2, 1, 0x0}, {8, 8, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData83_SOBEL_XY_3X3_08U[] = {{10, 8, 4, 0, 0x2211}, {10, 8, 2, 1, 0x0}, {10, 8, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData84_SOBEL_XY_3X3_08U[] = {{12, 8, 4, 0, 0x2211}, {12, 8, 2, 1, 0x0}, {12, 8, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData85_SOBEL_XY_3X3_08U[] = {{14, 8, 4, 0, 0x2211}, {14, 8, 2, 1, 0x0}, {14, 8, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData86_SOBEL_XY_3X3_08U[] = {{16, 8, 4, 0, 0x2211}, {16, 8, 2, 1, 0x0}, {16, 8, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData87_SOBEL_XY_3X3_08U[] = {{18, 8, 4, 0, 0x2211}, {18, 8, 2, 1, 0x0}, {18, 8, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData88_SOBEL_XY_3X3_08U[] = {{20, 8, 4, 0, 0x2211}, {20, 8, 2, 1, 0x0}, {20, 8, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData89_SOBEL_XY_3X3_08U[] = {{22, 8, 4, 0, 0x2211}, {22, 8, 2, 1, 0x0}, {22, 8, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData90_SOBEL_XY_3X3_08U[] = {{24, 8, 4, 0, 0x2211}, {24, 8, 2, 1, 0x0}, {24, 8, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData91_SOBEL_XY_3X3_08U[] = {{26, 8, 4, 0, 0x2211}, {26, 8, 2, 1, 0x0}, {26, 8, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData92_SOBEL_XY_3X3_08U[] = {{28, 8, 4, 0, 0x2211}, {28, 8, 2, 1, 0x0}, {28, 8, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData93_SOBEL_XY_3X3_08U[] = {{30, 8, 4, 0, 0x2211}, {30, 8, 2, 1, 0x0}, {30, 8, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData94_SOBEL_XY_3X3_08U[] = {{32, 8, 4, 0, 0x2211}, {32, 8, 2, 1, 0x0}, {32, 8, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData95_SOBEL_XY_3X3_08U[] = {{48, 8, 4, 0, 0x2211}, {48, 8, 2, 1, 0x0}, {48, 8, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData96_SOBEL_XY_3X3_08U[] = {{2, 10, 4, 0, 0x2211}, {2, 10, 2, 1, 0x0}, {2, 10, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData97_SOBEL_XY_3X3_08U[] = {{4, 10, 4, 0, 0x2211}, {4, 10, 2, 1, 0x0}, {4, 10, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData98_SOBEL_XY_3X3_08U[] = {{6, 10, 4, 0, 0x2211}, {6, 10, 2, 1, 0x0}, {6, 10, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData99_SOBEL_XY_3X3_08U[] = {{8, 10, 4, 0, 0x2211}, {8, 10, 2, 1, 0x0}, {8, 10, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData100_SOBEL_XY_3X3_08U[] = {{10, 10, 4, 0, 0x2211}, {10, 10, 2, 1, 0x0}, {10, 10, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData101_SOBEL_XY_3X3_08U[] = {{12, 10, 4, 0, 0x2211}, {12, 10, 2, 1, 0x0}, {12, 10, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData102_SOBEL_XY_3X3_08U[] = {{14, 10, 4, 0, 0x2211}, {14, 10, 2, 1, 0x0}, {14, 10, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData103_SOBEL_XY_3X3_08U[] = {{16, 10, 4, 0, 0x2211}, {16, 10, 2, 1, 0x0}, {16, 10, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData104_SOBEL_XY_3X3_08U[] = {{18, 10, 4, 0, 0x2211}, {18, 10, 2, 1, 0x0}, {18, 10, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData105_SOBEL_XY_3X3_08U[] = {{20, 10, 4, 0, 0x2211}, {20, 10, 2, 1, 0x0}, {20, 10, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData106_SOBEL_XY_3X3_08U[] = {{22, 10, 4, 0, 0x2211}, {22, 10, 2, 1, 0x0}, {22, 10, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData107_SOBEL_XY_3X3_08U[] = {{24, 10, 4, 0, 0x2211}, {24, 10, 2, 1, 0x0}, {24, 10, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData108_SOBEL_XY_3X3_08U[] = {{26, 10, 4, 0, 0x2211}, {26, 10, 2, 1, 0x0}, {26, 10, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData109_SOBEL_XY_3X3_08U[] = {{28, 10, 4, 0, 0x2211}, {28, 10, 2, 1, 0x0}, {28, 10, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData110_SOBEL_XY_3X3_08U[] = {{30, 10, 4, 0, 0x2211}, {30, 10, 2, 1, 0x0}, {30, 10, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData111_SOBEL_XY_3X3_08U[] = {{32, 10, 4, 0, 0x2211}, {32, 10, 2, 1, 0x0}, {32, 10, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData112_SOBEL_XY_3X3_08U[] = {{2, 12, 4, 0, 0x2211}, {2, 12, 2, 1, 0x0}, {2, 12, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData113_SOBEL_XY_3X3_08U[] = {{4, 12, 4, 0, 0x2211}, {4, 12, 2, 1, 0x0}, {4, 12, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData114_SOBEL_XY_3X3_08U[] = {{6, 12, 4, 0, 0x2211}, {6, 12, 2, 1, 0x0}, {6, 12, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData115_SOBEL_XY_3X3_08U[] = {{8, 12, 4, 0, 0x2211}, {8, 12, 2, 1, 0x0}, {8, 12, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData116_SOBEL_XY_3X3_08U[] = {{10, 12, 4, 0, 0x2211}, {10, 12, 2, 1, 0x0}, {10, 12, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData117_SOBEL_XY_3X3_08U[] = {{12, 12, 4, 0, 0x2211}, {12, 12, 2, 1, 0x0}, {12, 12, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData118_SOBEL_XY_3X3_08U[] = {{14, 12, 4, 0, 0x2211}, {14, 12, 2, 1, 0x0}, {14, 12, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData119_SOBEL_XY_3X3_08U[] = {{16, 12, 4, 0, 0x2211}, {16, 12, 2, 1, 0x0}, {16, 12, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData120_SOBEL_XY_3X3_08U[] = {{18, 12, 4, 0, 0x2211}, {18, 12, 2, 1, 0x0}, {18, 12, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData121_SOBEL_XY_3X3_08U[] = {{20, 12, 4, 0, 0x2211}, {20, 12, 2, 1, 0x0}, {20, 12, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData122_SOBEL_XY_3X3_08U[] = {{22, 12, 4, 0, 0x2211}, {22, 12, 2, 1, 0x0}, {22, 12, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData123_SOBEL_XY_3X3_08U[] = {{24, 12, 4, 0, 0x2211}, {24, 12, 2, 1, 0x0}, {24, 12, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData124_SOBEL_XY_3X3_08U[] = {{26, 12, 4, 0, 0x2211}, {26, 12, 2, 1, 0x0}, {26, 12, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData125_SOBEL_XY_3X3_08U[] = {{28, 12, 4, 0, 0x2211}, {28, 12, 2, 1, 0x0}, {28, 12, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData126_SOBEL_XY_3X3_08U[] = {{30, 12, 4, 0, 0x2211}, {30, 12, 2, 1, 0x0}, {30, 12, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData127_SOBEL_XY_3X3_08U[] = {{32, 12, 4, 0, 0x2211}, {32, 12, 2, 1, 0x0}, {32, 12, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData128_SOBEL_XY_3X3_08U[] = {{2, 14, 4, 0, 0x2211}, {2, 14, 2, 1, 0x0}, {2, 14, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData129_SOBEL_XY_3X3_08U[] = {{4, 14, 4, 0, 0x2211}, {4, 14, 2, 1, 0x0}, {4, 14, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData130_SOBEL_XY_3X3_08U[] = {{6, 14, 4, 0, 0x2211}, {6, 14, 2, 1, 0x0}, {6, 14, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData131_SOBEL_XY_3X3_08U[] = {{8, 14, 4, 0, 0x2211}, {8, 14, 2, 1, 0x0}, {8, 14, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData132_SOBEL_XY_3X3_08U[] = {{10, 14, 4, 0, 0x2211}, {10, 14, 2, 1, 0x0}, {10, 14, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData133_SOBEL_XY_3X3_08U[] = {{12, 14, 4, 0, 0x2211}, {12, 14, 2, 1, 0x0}, {12, 14, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData134_SOBEL_XY_3X3_08U[] = {{14, 14, 4, 0, 0x2211}, {14, 14, 2, 1, 0x0}, {14, 14, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData135_SOBEL_XY_3X3_08U[] = {{16, 14, 4, 0, 0x2211}, {16, 14, 2, 1, 0x0}, {16, 14, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData136_SOBEL_XY_3X3_08U[] = {{18, 14, 4, 0, 0x2211}, {18, 14, 2, 1, 0x0}, {18, 14, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData137_SOBEL_XY_3X3_08U[] = {{20, 14, 4, 0, 0x2211}, {20, 14, 2, 1, 0x0}, {20, 14, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData138_SOBEL_XY_3X3_08U[] = {{22, 14, 4, 0, 0x2211}, {22, 14, 2, 1, 0x0}, {22, 14, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData139_SOBEL_XY_3X3_08U[] = {{24, 14, 4, 0, 0x2211}, {24, 14, 2, 1, 0x0}, {24, 14, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData140_SOBEL_XY_3X3_08U[] = {{26, 14, 4, 0, 0x2211}, {26, 14, 2, 1, 0x0}, {26, 14, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData141_SOBEL_XY_3X3_08U[] = {{28, 14, 4, 0, 0x2211}, {28, 14, 2, 1, 0x0}, {28, 14, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData142_SOBEL_XY_3X3_08U[] = {{30, 14, 4, 0, 0x2211}, {30, 14, 2, 1, 0x0}, {30, 14, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData143_SOBEL_XY_3X3_08U[] = {{2, 16, 4, 0, 0x2211}, {2, 16, 2, 1, 0x0}, {2, 16, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData144_SOBEL_XY_3X3_08U[] = {{4, 16, 4, 0, 0x2211}, {4, 16, 2, 1, 0x0}, {4, 16, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData145_SOBEL_XY_3X3_08U[] = {{6, 16, 4, 0, 0x2211}, {6, 16, 2, 1, 0x0}, {6, 16, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData146_SOBEL_XY_3X3_08U[] = {{8, 16, 4, 0, 0x2211}, {8, 16, 2, 1, 0x0}, {8, 16, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData147_SOBEL_XY_3X3_08U[] = {{10, 16, 4, 0, 0x2211}, {10, 16, 2, 1, 0x0}, {10, 16, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData148_SOBEL_XY_3X3_08U[] = {{12, 16, 4, 0, 0x2211}, {12, 16, 2, 1, 0x0}, {12, 16, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData149_SOBEL_XY_3X3_08U[] = {{14, 16, 4, 0, 0x2211}, {14, 16, 2, 1, 0x0}, {14, 16, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData150_SOBEL_XY_3X3_08U[] = {{16, 16, 4, 0, 0x2211}, {16, 16, 2, 1, 0x0}, {16, 16, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData151_SOBEL_XY_3X3_08U[] = {{18, 16, 4, 0, 0x2211}, {18, 16, 2, 1, 0x0}, {18, 16, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData152_SOBEL_XY_3X3_08U[] = {{20, 16, 4, 0, 0x2211}, {20, 16, 2, 1, 0x0}, {20, 16, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData153_SOBEL_XY_3X3_08U[] = {{22, 16, 4, 0, 0x2211}, {22, 16, 2, 1, 0x0}, {22, 16, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData154_SOBEL_XY_3X3_08U[] = {{24, 16, 4, 0, 0x2211}, {24, 16, 2, 1, 0x0}, {24, 16, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData155_SOBEL_XY_3X3_08U[] = {{26, 16, 4, 0, 0x2211}, {26, 16, 2, 1, 0x0}, {26, 16, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData156_SOBEL_XY_3X3_08U[] = {{2, 18, 4, 0, 0x2211}, {2, 18, 2, 1, 0x0}, {2, 18, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData157_SOBEL_XY_3X3_08U[] = {{4, 18, 4, 0, 0x2211}, {4, 18, 2, 1, 0x0}, {4, 18, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData158_SOBEL_XY_3X3_08U[] = {{6, 18, 4, 0, 0x2211}, {6, 18, 2, 1, 0x0}, {6, 18, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData159_SOBEL_XY_3X3_08U[] = {{8, 18, 4, 0, 0x2211}, {8, 18, 2, 1, 0x0}, {8, 18, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData160_SOBEL_XY_3X3_08U[] = {{10, 18, 4, 0, 0x2211}, {10, 18, 2, 1, 0x0}, {10, 18, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData161_SOBEL_XY_3X3_08U[] = {{12, 18, 4, 0, 0x2211}, {12, 18, 2, 1, 0x0}, {12, 18, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData162_SOBEL_XY_3X3_08U[] = {{14, 18, 4, 0, 0x2211}, {14, 18, 2, 1, 0x0}, {14, 18, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData163_SOBEL_XY_3X3_08U[] = {{16, 18, 4, 0, 0x2211}, {16, 18, 2, 1, 0x0}, {16, 18, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData164_SOBEL_XY_3X3_08U[] = {{18, 18, 4, 0, 0x2211}, {18, 18, 2, 1, 0x0}, {18, 18, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData165_SOBEL_XY_3X3_08U[] = {{20, 18, 4, 0, 0x2211}, {20, 18, 2, 1, 0x0}, {20, 18, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData166_SOBEL_XY_3X3_08U[] = {{22, 18, 4, 0, 0x2211}, {22, 18, 2, 1, 0x0}, {22, 18, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData167_SOBEL_XY_3X3_08U[] = {{24, 18, 4, 0, 0x2211}, {24, 18, 2, 1, 0x0}, {24, 18, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData168_SOBEL_XY_3X3_08U[] = {{2, 20, 4, 0, 0x2211}, {2, 20, 2, 1, 0x0}, {2, 20, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData169_SOBEL_XY_3X3_08U[] = {{4, 20, 4, 0, 0x2211}, {4, 20, 2, 1, 0x0}, {4, 20, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData170_SOBEL_XY_3X3_08U[] = {{6, 20, 4, 0, 0x2211}, {6, 20, 2, 1, 0x0}, {6, 20, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData171_SOBEL_XY_3X3_08U[] = {{8, 20, 4, 0, 0x2211}, {8, 20, 2, 1, 0x0}, {8, 20, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData172_SOBEL_XY_3X3_08U[] = {{10, 20, 4, 0, 0x2211}, {10, 20, 2, 1, 0x0}, {10, 20, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData173_SOBEL_XY_3X3_08U[] = {{12, 20, 4, 0, 0x2211}, {12, 20, 2, 1, 0x0}, {12, 20, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData174_SOBEL_XY_3X3_08U[] = {{14, 20, 4, 0, 0x2211}, {14, 20, 2, 1, 0x0}, {14, 20, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData175_SOBEL_XY_3X3_08U[] = {{16, 20, 4, 0, 0x2211}, {16, 20, 2, 1, 0x0}, {16, 20, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData176_SOBEL_XY_3X3_08U[] = {{18, 20, 4, 0, 0x2211}, {18, 20, 2, 1, 0x0}, {18, 20, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData177_SOBEL_XY_3X3_08U[] = {{20, 20, 4, 0, 0x2211}, {20, 20, 2, 1, 0x0}, {20, 20, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData178_SOBEL_XY_3X3_08U[] = {{2, 22, 4, 0, 0x2211}, {2, 22, 2, 1, 0x0}, {2, 22, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData179_SOBEL_XY_3X3_08U[] = {{4, 22, 4, 0, 0x2211}, {4, 22, 2, 1, 0x0}, {4, 22, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData180_SOBEL_XY_3X3_08U[] = {{6, 22, 4, 0, 0x2211}, {6, 22, 2, 1, 0x0}, {6, 22, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData181_SOBEL_XY_3X3_08U[] = {{8, 22, 4, 0, 0x2211}, {8, 22, 2, 1, 0x0}, {8, 22, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData182_SOBEL_XY_3X3_08U[] = {{10, 22, 4, 0, 0x2211}, {10, 22, 2, 1, 0x0}, {10, 22, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData183_SOBEL_XY_3X3_08U[] = {{12, 22, 4, 0, 0x2211}, {12, 22, 2, 1, 0x0}, {12, 22, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData184_SOBEL_XY_3X3_08U[] = {{14, 22, 4, 0, 0x2211}, {14, 22, 2, 1, 0x0}, {14, 22, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData185_SOBEL_XY_3X3_08U[] = {{16, 22, 4, 0, 0x2211}, {16, 22, 2, 1, 0x0}, {16, 22, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData186_SOBEL_XY_3X3_08U[] = {{18, 22, 4, 0, 0x2211}, {18, 22, 2, 1, 0x0}, {18, 22, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData187_SOBEL_XY_3X3_08U[] = {{2, 24, 4, 0, 0x2211}, {2, 24, 2, 1, 0x0}, {2, 24, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData188_SOBEL_XY_3X3_08U[] = {{4, 24, 4, 0, 0x2211}, {4, 24, 2, 1, 0x0}, {4, 24, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData189_SOBEL_XY_3X3_08U[] = {{6, 24, 4, 0, 0x2211}, {6, 24, 2, 1, 0x0}, {6, 24, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData190_SOBEL_XY_3X3_08U[] = {{8, 24, 4, 0, 0x2211}, {8, 24, 2, 1, 0x0}, {8, 24, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData191_SOBEL_XY_3X3_08U[] = {{10, 24, 4, 0, 0x2211}, {10, 24, 2, 1, 0x0}, {10, 24, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData192_SOBEL_XY_3X3_08U[] = {{12, 24, 4, 0, 0x2211}, {12, 24, 2, 1, 0x0}, {12, 24, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData193_SOBEL_XY_3X3_08U[] = {{14, 24, 4, 0, 0x2211}, {14, 24, 2, 1, 0x0}, {14, 24, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData194_SOBEL_XY_3X3_08U[] = {{16, 24, 4, 0, 0x2211}, {16, 24, 2, 1, 0x0}, {16, 24, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData195_SOBEL_XY_3X3_08U[] = {{2, 26, 4, 0, 0x2211}, {2, 26, 2, 1, 0x0}, {2, 26, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData196_SOBEL_XY_3X3_08U[] = {{4, 26, 4, 0, 0x2211}, {4, 26, 2, 1, 0x0}, {4, 26, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData197_SOBEL_XY_3X3_08U[] = {{6, 26, 4, 0, 0x2211}, {6, 26, 2, 1, 0x0}, {6, 26, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData198_SOBEL_XY_3X3_08U[] = {{8, 26, 4, 0, 0x2211}, {8, 26, 2, 1, 0x0}, {8, 26, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData199_SOBEL_XY_3X3_08U[] = {{10, 26, 4, 0, 0x2211}, {10, 26, 2, 1, 0x0}, {10, 26, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData200_SOBEL_XY_3X3_08U[] = {{12, 26, 4, 0, 0x2211}, {12, 26, 2, 1, 0x0}, {12, 26, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData201_SOBEL_XY_3X3_08U[] = {{14, 26, 4, 0, 0x2211}, {14, 26, 2, 1, 0x0}, {14, 26, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData202_SOBEL_XY_3X3_08U[] = {{16, 26, 4, 0, 0x2211}, {16, 26, 2, 1, 0x0}, {16, 26, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData203_SOBEL_XY_3X3_08U[] = {{2, 28, 4, 0, 0x2211}, {2, 28, 2, 1, 0x0}, {2, 28, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData204_SOBEL_XY_3X3_08U[] = {{4, 28, 4, 0, 0x2211}, {4, 28, 2, 1, 0x0}, {4, 28, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData205_SOBEL_XY_3X3_08U[] = {{6, 28, 4, 0, 0x2211}, {6, 28, 2, 1, 0x0}, {6, 28, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData206_SOBEL_XY_3X3_08U[] = {{8, 28, 4, 0, 0x2211}, {8, 28, 2, 1, 0x0}, {8, 28, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData207_SOBEL_XY_3X3_08U[] = {{10, 28, 4, 0, 0x2211}, {10, 28, 2, 1, 0x0}, {10, 28, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData208_SOBEL_XY_3X3_08U[] = {{12, 28, 4, 0, 0x2211}, {12, 28, 2, 1, 0x0}, {12, 28, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData209_SOBEL_XY_3X3_08U[] = {{14, 28, 4, 0, 0x2211}, {14, 28, 2, 1, 0x0}, {14, 28, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData210_SOBEL_XY_3X3_08U[] = {{2, 30, 4, 0, 0x2211}, {2, 30, 2, 1, 0x0}, {2, 30, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData211_SOBEL_XY_3X3_08U[] = {{4, 30, 4, 0, 0x2211}, {4, 30, 2, 1, 0x0}, {4, 30, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData212_SOBEL_XY_3X3_08U[] = {{6, 30, 4, 0, 0x2211}, {6, 30, 2, 1, 0x0}, {6, 30, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData213_SOBEL_XY_3X3_08U[] = {{8, 30, 4, 0, 0x2211}, {8, 30, 2, 1, 0x0}, {8, 30, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData214_SOBEL_XY_3X3_08U[] = {{10, 30, 4, 0, 0x2211}, {10, 30, 2, 1, 0x0}, {10, 30, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData215_SOBEL_XY_3X3_08U[] = {{12, 30, 4, 0, 0x2211}, {12, 30, 2, 1, 0x0}, {12, 30, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData216_SOBEL_XY_3X3_08U[] = {{2, 32, 4, 0, 0x2211}, {2, 32, 2, 1, 0x0}, {2, 32, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData217_SOBEL_XY_3X3_08U[] = {{4, 32, 4, 0, 0x2211}, {4, 32, 2, 1, 0x0}, {4, 32, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData218_SOBEL_XY_3X3_08U[] = {{6, 32, 4, 0, 0x2211}, {6, 32, 2, 1, 0x0}, {6, 32, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData219_SOBEL_XY_3X3_08U[] = {{8, 32, 4, 0, 0x2211}, {8, 32, 2, 1, 0x0}, {8, 32, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData220_SOBEL_XY_3X3_08U[] = {{10, 32, 4, 0, 0x2211}, {10, 32, 2, 1, 0x0}, {10, 32, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData221_SOBEL_XY_3X3_08U[] = {{12, 32, 4, 0, 0x2211}, {12, 32, 2, 1, 0x0}, {12, 32, 2, 1, 0x0}};

static acf_scenario_kernel_data gScenarioKernelData0_SOBEL_XY_3X3_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData1_SOBEL_XY_3X3_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData2_SOBEL_XY_3X3_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData3_SOBEL_XY_3X3_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData4_SOBEL_XY_3X3_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData5_SOBEL_XY_3X3_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData6_SOBEL_XY_3X3_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData7_SOBEL_XY_3X3_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData8_SOBEL_XY_3X3_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData9_SOBEL_XY_3X3_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData10_SOBEL_XY_3X3_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData11_SOBEL_XY_3X3_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData12_SOBEL_XY_3X3_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData13_SOBEL_XY_3X3_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData14_SOBEL_XY_3X3_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData15_SOBEL_XY_3X3_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData16_SOBEL_XY_3X3_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData17_SOBEL_XY_3X3_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData18_SOBEL_XY_3X3_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData19_SOBEL_XY_3X3_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData20_SOBEL_XY_3X3_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData21_SOBEL_XY_3X3_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData22_SOBEL_XY_3X3_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData23_SOBEL_XY_3X3_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData24_SOBEL_XY_3X3_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData25_SOBEL_XY_3X3_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData26_SOBEL_XY_3X3_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData27_SOBEL_XY_3X3_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData28_SOBEL_XY_3X3_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData29_SOBEL_XY_3X3_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData30_SOBEL_XY_3X3_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData31_SOBEL_XY_3X3_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData32_SOBEL_XY_3X3_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData33_SOBEL_XY_3X3_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData34_SOBEL_XY_3X3_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData35_SOBEL_XY_3X3_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData36_SOBEL_XY_3X3_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData37_SOBEL_XY_3X3_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData38_SOBEL_XY_3X3_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData39_SOBEL_XY_3X3_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData40_SOBEL_XY_3X3_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData41_SOBEL_XY_3X3_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData42_SOBEL_XY_3X3_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData43_SOBEL_XY_3X3_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData44_SOBEL_XY_3X3_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData45_SOBEL_XY_3X3_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData46_SOBEL_XY_3X3_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData47_SOBEL_XY_3X3_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData48_SOBEL_XY_3X3_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData49_SOBEL_XY_3X3_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData50_SOBEL_XY_3X3_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData51_SOBEL_XY_3X3_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData52_SOBEL_XY_3X3_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData53_SOBEL_XY_3X3_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData54_SOBEL_XY_3X3_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData55_SOBEL_XY_3X3_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData56_SOBEL_XY_3X3_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData57_SOBEL_XY_3X3_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData58_SOBEL_XY_3X3_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData59_SOBEL_XY_3X3_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData60_SOBEL_XY_3X3_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData61_SOBEL_XY_3X3_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData62_SOBEL_XY_3X3_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData63_SOBEL_XY_3X3_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData64_SOBEL_XY_3X3_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData65_SOBEL_XY_3X3_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData66_SOBEL_XY_3X3_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData67_SOBEL_XY_3X3_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData68_SOBEL_XY_3X3_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData69_SOBEL_XY_3X3_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData70_SOBEL_XY_3X3_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData71_SOBEL_XY_3X3_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData72_SOBEL_XY_3X3_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData73_SOBEL_XY_3X3_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData74_SOBEL_XY_3X3_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData75_SOBEL_XY_3X3_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData76_SOBEL_XY_3X3_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData77_SOBEL_XY_3X3_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData78_SOBEL_XY_3X3_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData79_SOBEL_XY_3X3_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData80_SOBEL_XY_3X3_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData81_SOBEL_XY_3X3_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData82_SOBEL_XY_3X3_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData83_SOBEL_XY_3X3_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData84_SOBEL_XY_3X3_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData85_SOBEL_XY_3X3_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData86_SOBEL_XY_3X3_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData87_SOBEL_XY_3X3_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData88_SOBEL_XY_3X3_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData89_SOBEL_XY_3X3_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData90_SOBEL_XY_3X3_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData91_SOBEL_XY_3X3_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData92_SOBEL_XY_3X3_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData93_SOBEL_XY_3X3_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData94_SOBEL_XY_3X3_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData95_SOBEL_XY_3X3_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData96_SOBEL_XY_3X3_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData97_SOBEL_XY_3X3_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData98_SOBEL_XY_3X3_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData99_SOBEL_XY_3X3_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData100_SOBEL_XY_3X3_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData101_SOBEL_XY_3X3_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData102_SOBEL_XY_3X3_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData103_SOBEL_XY_3X3_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData104_SOBEL_XY_3X3_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData105_SOBEL_XY_3X3_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData106_SOBEL_XY_3X3_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData107_SOBEL_XY_3X3_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData108_SOBEL_XY_3X3_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData109_SOBEL_XY_3X3_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData110_SOBEL_XY_3X3_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData111_SOBEL_XY_3X3_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData112_SOBEL_XY_3X3_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData113_SOBEL_XY_3X3_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData114_SOBEL_XY_3X3_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData115_SOBEL_XY_3X3_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData116_SOBEL_XY_3X3_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData117_SOBEL_XY_3X3_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData118_SOBEL_XY_3X3_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData119_SOBEL_XY_3X3_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData120_SOBEL_XY_3X3_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData121_SOBEL_XY_3X3_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData122_SOBEL_XY_3X3_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData123_SOBEL_XY_3X3_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData124_SOBEL_XY_3X3_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData125_SOBEL_XY_3X3_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData126_SOBEL_XY_3X3_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData127_SOBEL_XY_3X3_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData128_SOBEL_XY_3X3_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData129_SOBEL_XY_3X3_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData130_SOBEL_XY_3X3_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData131_SOBEL_XY_3X3_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData132_SOBEL_XY_3X3_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData133_SOBEL_XY_3X3_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData134_SOBEL_XY_3X3_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData135_SOBEL_XY_3X3_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData136_SOBEL_XY_3X3_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData137_SOBEL_XY_3X3_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData138_SOBEL_XY_3X3_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData139_SOBEL_XY_3X3_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData140_SOBEL_XY_3X3_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData141_SOBEL_XY_3X3_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData142_SOBEL_XY_3X3_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData143_SOBEL_XY_3X3_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData144_SOBEL_XY_3X3_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData145_SOBEL_XY_3X3_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData146_SOBEL_XY_3X3_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData147_SOBEL_XY_3X3_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData148_SOBEL_XY_3X3_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData149_SOBEL_XY_3X3_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData150_SOBEL_XY_3X3_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData151_SOBEL_XY_3X3_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData152_SOBEL_XY_3X3_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData153_SOBEL_XY_3X3_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData154_SOBEL_XY_3X3_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData155_SOBEL_XY_3X3_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData156_SOBEL_XY_3X3_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData157_SOBEL_XY_3X3_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData158_SOBEL_XY_3X3_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData159_SOBEL_XY_3X3_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData160_SOBEL_XY_3X3_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData161_SOBEL_XY_3X3_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData162_SOBEL_XY_3X3_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData163_SOBEL_XY_3X3_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData164_SOBEL_XY_3X3_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData165_SOBEL_XY_3X3_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData166_SOBEL_XY_3X3_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData167_SOBEL_XY_3X3_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData168_SOBEL_XY_3X3_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData169_SOBEL_XY_3X3_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData170_SOBEL_XY_3X3_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData171_SOBEL_XY_3X3_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData172_SOBEL_XY_3X3_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData173_SOBEL_XY_3X3_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData174_SOBEL_XY_3X3_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData175_SOBEL_XY_3X3_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData176_SOBEL_XY_3X3_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData177_SOBEL_XY_3X3_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData178_SOBEL_XY_3X3_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData179_SOBEL_XY_3X3_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData180_SOBEL_XY_3X3_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData181_SOBEL_XY_3X3_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData182_SOBEL_XY_3X3_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData183_SOBEL_XY_3X3_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData184_SOBEL_XY_3X3_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData185_SOBEL_XY_3X3_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData186_SOBEL_XY_3X3_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData187_SOBEL_XY_3X3_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData188_SOBEL_XY_3X3_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData189_SOBEL_XY_3X3_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData190_SOBEL_XY_3X3_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData191_SOBEL_XY_3X3_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData192_SOBEL_XY_3X3_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData193_SOBEL_XY_3X3_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData194_SOBEL_XY_3X3_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData195_SOBEL_XY_3X3_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData196_SOBEL_XY_3X3_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData197_SOBEL_XY_3X3_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData198_SOBEL_XY_3X3_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData199_SOBEL_XY_3X3_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData200_SOBEL_XY_3X3_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData201_SOBEL_XY_3X3_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData202_SOBEL_XY_3X3_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData203_SOBEL_XY_3X3_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData204_SOBEL_XY_3X3_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData205_SOBEL_XY_3X3_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData206_SOBEL_XY_3X3_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData207_SOBEL_XY_3X3_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData208_SOBEL_XY_3X3_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData209_SOBEL_XY_3X3_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData210_SOBEL_XY_3X3_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData211_SOBEL_XY_3X3_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData212_SOBEL_XY_3X3_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData213_SOBEL_XY_3X3_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData214_SOBEL_XY_3X3_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData215_SOBEL_XY_3X3_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData216_SOBEL_XY_3X3_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData217_SOBEL_XY_3X3_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData218_SOBEL_XY_3X3_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData219_SOBEL_XY_3X3_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData220_SOBEL_XY_3X3_08U[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData221_SOBEL_XY_3X3_08U[] = {{1}};

static acf_scenario gScenarioArray_SOBEL_XY_3X3_08U[] = {
{2, 1, 44, 0, 1, gScenarioBufferData0_SOBEL_XY_3X3_08U, 30, gScenarioKernelData0_SOBEL_XY_3X3_08U, 2},
{4, 1, 64, 0, 1, gScenarioBufferData1_SOBEL_XY_3X3_08U, 30, gScenarioKernelData1_SOBEL_XY_3X3_08U, 2},
{6, 1, 84, 0, 1, gScenarioBufferData2_SOBEL_XY_3X3_08U, 30, gScenarioKernelData2_SOBEL_XY_3X3_08U, 2},
{8, 1, 104, 0, 1, gScenarioBufferData3_SOBEL_XY_3X3_08U, 30, gScenarioKernelData3_SOBEL_XY_3X3_08U, 2},
{10, 1, 124, 0, 1, gScenarioBufferData4_SOBEL_XY_3X3_08U, 30, gScenarioKernelData4_SOBEL_XY_3X3_08U, 2},
{12, 1, 144, 0, 1, gScenarioBufferData5_SOBEL_XY_3X3_08U, 30, gScenarioKernelData5_SOBEL_XY_3X3_08U, 2},
{14, 1, 164, 0, 1, gScenarioBufferData6_SOBEL_XY_3X3_08U, 30, gScenarioKernelData6_SOBEL_XY_3X3_08U, 2},
{16, 1, 184, 0, 1, gScenarioBufferData7_SOBEL_XY_3X3_08U, 30, gScenarioKernelData7_SOBEL_XY_3X3_08U, 2},
{18, 1, 204, 0, 1, gScenarioBufferData8_SOBEL_XY_3X3_08U, 30, gScenarioKernelData8_SOBEL_XY_3X3_08U, 2},
{20, 1, 224, 0, 1, gScenarioBufferData9_SOBEL_XY_3X3_08U, 30, gScenarioKernelData9_SOBEL_XY_3X3_08U, 2},
{22, 1, 244, 0, 1, gScenarioBufferData10_SOBEL_XY_3X3_08U, 30, gScenarioKernelData10_SOBEL_XY_3X3_08U, 2},
{24, 1, 264, 0, 1, gScenarioBufferData11_SOBEL_XY_3X3_08U, 30, gScenarioKernelData11_SOBEL_XY_3X3_08U, 2},
{26, 1, 284, 0, 1, gScenarioBufferData12_SOBEL_XY_3X3_08U, 30, gScenarioKernelData12_SOBEL_XY_3X3_08U, 2},
{28, 1, 304, 0, 1, gScenarioBufferData13_SOBEL_XY_3X3_08U, 30, gScenarioKernelData13_SOBEL_XY_3X3_08U, 2},
{30, 1, 324, 0, 1, gScenarioBufferData14_SOBEL_XY_3X3_08U, 30, gScenarioKernelData14_SOBEL_XY_3X3_08U, 2},
{32, 1, 344, 0, 1, gScenarioBufferData15_SOBEL_XY_3X3_08U, 30, gScenarioKernelData15_SOBEL_XY_3X3_08U, 2},
{48, 1, 504, 0, 1, gScenarioBufferData16_SOBEL_XY_3X3_08U, 30, gScenarioKernelData16_SOBEL_XY_3X3_08U, 2},
{64, 1, 664, 0, 1, gScenarioBufferData17_SOBEL_XY_3X3_08U, 30, gScenarioKernelData17_SOBEL_XY_3X3_08U, 2},
{96, 1, 984, 0, 1, gScenarioBufferData18_SOBEL_XY_3X3_08U, 30, gScenarioKernelData18_SOBEL_XY_3X3_08U, 2},
{112, 1, 1144, 0, 1, gScenarioBufferData19_SOBEL_XY_3X3_08U, 30, gScenarioKernelData19_SOBEL_XY_3X3_08U, 2},
{128, 1, 1304, 0, 1, gScenarioBufferData20_SOBEL_XY_3X3_08U, 30, gScenarioKernelData20_SOBEL_XY_3X3_08U, 2},
{2, 2, 76, 0, 1, gScenarioBufferData21_SOBEL_XY_3X3_08U, 30, gScenarioKernelData21_SOBEL_XY_3X3_08U, 2},
{4, 2, 112, 0, 1, gScenarioBufferData22_SOBEL_XY_3X3_08U, 30, gScenarioKernelData22_SOBEL_XY_3X3_08U, 2},
{6, 2, 148, 0, 1, gScenarioBufferData23_SOBEL_XY_3X3_08U, 30, gScenarioKernelData23_SOBEL_XY_3X3_08U, 2},
{8, 2, 184, 0, 1, gScenarioBufferData24_SOBEL_XY_3X3_08U, 30, gScenarioKernelData24_SOBEL_XY_3X3_08U, 2},
{10, 2, 220, 0, 1, gScenarioBufferData25_SOBEL_XY_3X3_08U, 30, gScenarioKernelData25_SOBEL_XY_3X3_08U, 2},
{12, 2, 256, 0, 1, gScenarioBufferData26_SOBEL_XY_3X3_08U, 30, gScenarioKernelData26_SOBEL_XY_3X3_08U, 2},
{14, 2, 292, 0, 1, gScenarioBufferData27_SOBEL_XY_3X3_08U, 30, gScenarioKernelData27_SOBEL_XY_3X3_08U, 2},
{16, 2, 328, 0, 1, gScenarioBufferData28_SOBEL_XY_3X3_08U, 30, gScenarioKernelData28_SOBEL_XY_3X3_08U, 2},
{18, 2, 364, 0, 1, gScenarioBufferData29_SOBEL_XY_3X3_08U, 30, gScenarioKernelData29_SOBEL_XY_3X3_08U, 2},
{20, 2, 400, 0, 1, gScenarioBufferData30_SOBEL_XY_3X3_08U, 30, gScenarioKernelData30_SOBEL_XY_3X3_08U, 2},
{22, 2, 436, 0, 1, gScenarioBufferData31_SOBEL_XY_3X3_08U, 30, gScenarioKernelData31_SOBEL_XY_3X3_08U, 2},
{24, 2, 472, 0, 1, gScenarioBufferData32_SOBEL_XY_3X3_08U, 30, gScenarioKernelData32_SOBEL_XY_3X3_08U, 2},
{26, 2, 508, 0, 1, gScenarioBufferData33_SOBEL_XY_3X3_08U, 30, gScenarioKernelData33_SOBEL_XY_3X3_08U, 2},
{28, 2, 544, 0, 1, gScenarioBufferData34_SOBEL_XY_3X3_08U, 30, gScenarioKernelData34_SOBEL_XY_3X3_08U, 2},
{30, 2, 580, 0, 1, gScenarioBufferData35_SOBEL_XY_3X3_08U, 30, gScenarioKernelData35_SOBEL_XY_3X3_08U, 2},
{32, 2, 616, 0, 1, gScenarioBufferData36_SOBEL_XY_3X3_08U, 30, gScenarioKernelData36_SOBEL_XY_3X3_08U, 2},
{48, 2, 904, 0, 1, gScenarioBufferData37_SOBEL_XY_3X3_08U, 30, gScenarioKernelData37_SOBEL_XY_3X3_08U, 2},
{64, 2, 1192, 0, 1, gScenarioBufferData38_SOBEL_XY_3X3_08U, 30, gScenarioKernelData38_SOBEL_XY_3X3_08U, 2},
{96, 2, 1768, 0, 1, gScenarioBufferData39_SOBEL_XY_3X3_08U, 30, gScenarioKernelData39_SOBEL_XY_3X3_08U, 2},
{112, 2, 2056, 0, 1, gScenarioBufferData40_SOBEL_XY_3X3_08U, 30, gScenarioKernelData40_SOBEL_XY_3X3_08U, 2},
{128, 2, 2344, 0, 1, gScenarioBufferData41_SOBEL_XY_3X3_08U, 30, gScenarioKernelData41_SOBEL_XY_3X3_08U, 2},
{2, 4, 140, 0, 1, gScenarioBufferData42_SOBEL_XY_3X3_08U, 30, gScenarioKernelData42_SOBEL_XY_3X3_08U, 2},
{4, 4, 208, 0, 1, gScenarioBufferData43_SOBEL_XY_3X3_08U, 30, gScenarioKernelData43_SOBEL_XY_3X3_08U, 2},
{6, 4, 276, 0, 1, gScenarioBufferData44_SOBEL_XY_3X3_08U, 30, gScenarioKernelData44_SOBEL_XY_3X3_08U, 2},
{8, 4, 344, 0, 1, gScenarioBufferData45_SOBEL_XY_3X3_08U, 30, gScenarioKernelData45_SOBEL_XY_3X3_08U, 2},
{10, 4, 412, 0, 1, gScenarioBufferData46_SOBEL_XY_3X3_08U, 30, gScenarioKernelData46_SOBEL_XY_3X3_08U, 2},
{12, 4, 480, 0, 1, gScenarioBufferData47_SOBEL_XY_3X3_08U, 30, gScenarioKernelData47_SOBEL_XY_3X3_08U, 2},
{14, 4, 548, 0, 1, gScenarioBufferData48_SOBEL_XY_3X3_08U, 30, gScenarioKernelData48_SOBEL_XY_3X3_08U, 2},
{16, 4, 616, 0, 1, gScenarioBufferData49_SOBEL_XY_3X3_08U, 30, gScenarioKernelData49_SOBEL_XY_3X3_08U, 2},
{18, 4, 684, 0, 1, gScenarioBufferData50_SOBEL_XY_3X3_08U, 30, gScenarioKernelData50_SOBEL_XY_3X3_08U, 2},
{20, 4, 752, 0, 1, gScenarioBufferData51_SOBEL_XY_3X3_08U, 30, gScenarioKernelData51_SOBEL_XY_3X3_08U, 2},
{22, 4, 820, 0, 1, gScenarioBufferData52_SOBEL_XY_3X3_08U, 30, gScenarioKernelData52_SOBEL_XY_3X3_08U, 2},
{24, 4, 888, 0, 1, gScenarioBufferData53_SOBEL_XY_3X3_08U, 30, gScenarioKernelData53_SOBEL_XY_3X3_08U, 2},
{26, 4, 956, 0, 1, gScenarioBufferData54_SOBEL_XY_3X3_08U, 30, gScenarioKernelData54_SOBEL_XY_3X3_08U, 2},
{28, 4, 1024, 0, 1, gScenarioBufferData55_SOBEL_XY_3X3_08U, 30, gScenarioKernelData55_SOBEL_XY_3X3_08U, 2},
{30, 4, 1092, 0, 1, gScenarioBufferData56_SOBEL_XY_3X3_08U, 30, gScenarioKernelData56_SOBEL_XY_3X3_08U, 2},
{32, 4, 1160, 0, 1, gScenarioBufferData57_SOBEL_XY_3X3_08U, 30, gScenarioKernelData57_SOBEL_XY_3X3_08U, 2},
{48, 4, 1704, 0, 1, gScenarioBufferData58_SOBEL_XY_3X3_08U, 30, gScenarioKernelData58_SOBEL_XY_3X3_08U, 2},
{64, 4, 2248, 0, 1, gScenarioBufferData59_SOBEL_XY_3X3_08U, 30, gScenarioKernelData59_SOBEL_XY_3X3_08U, 2},
{96, 4, 3336, 0, 1, gScenarioBufferData60_SOBEL_XY_3X3_08U, 30, gScenarioKernelData60_SOBEL_XY_3X3_08U, 2},
{2, 6, 204, 0, 1, gScenarioBufferData61_SOBEL_XY_3X3_08U, 30, gScenarioKernelData61_SOBEL_XY_3X3_08U, 2},
{4, 6, 304, 0, 1, gScenarioBufferData62_SOBEL_XY_3X3_08U, 30, gScenarioKernelData62_SOBEL_XY_3X3_08U, 2},
{6, 6, 404, 0, 1, gScenarioBufferData63_SOBEL_XY_3X3_08U, 30, gScenarioKernelData63_SOBEL_XY_3X3_08U, 2},
{8, 6, 504, 0, 1, gScenarioBufferData64_SOBEL_XY_3X3_08U, 30, gScenarioKernelData64_SOBEL_XY_3X3_08U, 2},
{10, 6, 604, 0, 1, gScenarioBufferData65_SOBEL_XY_3X3_08U, 30, gScenarioKernelData65_SOBEL_XY_3X3_08U, 2},
{12, 6, 704, 0, 1, gScenarioBufferData66_SOBEL_XY_3X3_08U, 30, gScenarioKernelData66_SOBEL_XY_3X3_08U, 2},
{14, 6, 804, 0, 1, gScenarioBufferData67_SOBEL_XY_3X3_08U, 30, gScenarioKernelData67_SOBEL_XY_3X3_08U, 2},
{16, 6, 904, 0, 1, gScenarioBufferData68_SOBEL_XY_3X3_08U, 30, gScenarioKernelData68_SOBEL_XY_3X3_08U, 2},
{18, 6, 1004, 0, 1, gScenarioBufferData69_SOBEL_XY_3X3_08U, 30, gScenarioKernelData69_SOBEL_XY_3X3_08U, 2},
{20, 6, 1104, 0, 1, gScenarioBufferData70_SOBEL_XY_3X3_08U, 30, gScenarioKernelData70_SOBEL_XY_3X3_08U, 2},
{22, 6, 1204, 0, 1, gScenarioBufferData71_SOBEL_XY_3X3_08U, 30, gScenarioKernelData71_SOBEL_XY_3X3_08U, 2},
{24, 6, 1304, 0, 1, gScenarioBufferData72_SOBEL_XY_3X3_08U, 30, gScenarioKernelData72_SOBEL_XY_3X3_08U, 2},
{26, 6, 1404, 0, 1, gScenarioBufferData73_SOBEL_XY_3X3_08U, 30, gScenarioKernelData73_SOBEL_XY_3X3_08U, 2},
{28, 6, 1504, 0, 1, gScenarioBufferData74_SOBEL_XY_3X3_08U, 30, gScenarioKernelData74_SOBEL_XY_3X3_08U, 2},
{30, 6, 1604, 0, 1, gScenarioBufferData75_SOBEL_XY_3X3_08U, 30, gScenarioKernelData75_SOBEL_XY_3X3_08U, 2},
{32, 6, 1704, 0, 1, gScenarioBufferData76_SOBEL_XY_3X3_08U, 30, gScenarioKernelData76_SOBEL_XY_3X3_08U, 2},
{48, 6, 2504, 0, 1, gScenarioBufferData77_SOBEL_XY_3X3_08U, 30, gScenarioKernelData77_SOBEL_XY_3X3_08U, 2},
{64, 6, 3304, 0, 1, gScenarioBufferData78_SOBEL_XY_3X3_08U, 30, gScenarioKernelData78_SOBEL_XY_3X3_08U, 2},
{2, 8, 268, 0, 1, gScenarioBufferData79_SOBEL_XY_3X3_08U, 30, gScenarioKernelData79_SOBEL_XY_3X3_08U, 2},
{4, 8, 400, 0, 1, gScenarioBufferData80_SOBEL_XY_3X3_08U, 30, gScenarioKernelData80_SOBEL_XY_3X3_08U, 2},
{6, 8, 532, 0, 1, gScenarioBufferData81_SOBEL_XY_3X3_08U, 30, gScenarioKernelData81_SOBEL_XY_3X3_08U, 2},
{8, 8, 664, 0, 1, gScenarioBufferData82_SOBEL_XY_3X3_08U, 30, gScenarioKernelData82_SOBEL_XY_3X3_08U, 2},
{10, 8, 796, 0, 1, gScenarioBufferData83_SOBEL_XY_3X3_08U, 30, gScenarioKernelData83_SOBEL_XY_3X3_08U, 2},
{12, 8, 928, 0, 1, gScenarioBufferData84_SOBEL_XY_3X3_08U, 30, gScenarioKernelData84_SOBEL_XY_3X3_08U, 2},
{14, 8, 1060, 0, 1, gScenarioBufferData85_SOBEL_XY_3X3_08U, 30, gScenarioKernelData85_SOBEL_XY_3X3_08U, 2},
{16, 8, 1192, 0, 1, gScenarioBufferData86_SOBEL_XY_3X3_08U, 30, gScenarioKernelData86_SOBEL_XY_3X3_08U, 2},
{18, 8, 1324, 0, 1, gScenarioBufferData87_SOBEL_XY_3X3_08U, 30, gScenarioKernelData87_SOBEL_XY_3X3_08U, 2},
{20, 8, 1456, 0, 1, gScenarioBufferData88_SOBEL_XY_3X3_08U, 30, gScenarioKernelData88_SOBEL_XY_3X3_08U, 2},
{22, 8, 1588, 0, 1, gScenarioBufferData89_SOBEL_XY_3X3_08U, 30, gScenarioKernelData89_SOBEL_XY_3X3_08U, 2},
{24, 8, 1720, 0, 1, gScenarioBufferData90_SOBEL_XY_3X3_08U, 30, gScenarioKernelData90_SOBEL_XY_3X3_08U, 2},
{26, 8, 1852, 0, 1, gScenarioBufferData91_SOBEL_XY_3X3_08U, 30, gScenarioKernelData91_SOBEL_XY_3X3_08U, 2},
{28, 8, 1984, 0, 1, gScenarioBufferData92_SOBEL_XY_3X3_08U, 30, gScenarioKernelData92_SOBEL_XY_3X3_08U, 2},
{30, 8, 2116, 0, 1, gScenarioBufferData93_SOBEL_XY_3X3_08U, 30, gScenarioKernelData93_SOBEL_XY_3X3_08U, 2},
{32, 8, 2248, 0, 1, gScenarioBufferData94_SOBEL_XY_3X3_08U, 30, gScenarioKernelData94_SOBEL_XY_3X3_08U, 2},
{48, 8, 3304, 0, 1, gScenarioBufferData95_SOBEL_XY_3X3_08U, 30, gScenarioKernelData95_SOBEL_XY_3X3_08U, 2},
{2, 10, 332, 0, 1, gScenarioBufferData96_SOBEL_XY_3X3_08U, 30, gScenarioKernelData96_SOBEL_XY_3X3_08U, 2},
{4, 10, 496, 0, 1, gScenarioBufferData97_SOBEL_XY_3X3_08U, 30, gScenarioKernelData97_SOBEL_XY_3X3_08U, 2},
{6, 10, 660, 0, 1, gScenarioBufferData98_SOBEL_XY_3X3_08U, 30, gScenarioKernelData98_SOBEL_XY_3X3_08U, 2},
{8, 10, 824, 0, 1, gScenarioBufferData99_SOBEL_XY_3X3_08U, 30, gScenarioKernelData99_SOBEL_XY_3X3_08U, 2},
{10, 10, 988, 0, 1, gScenarioBufferData100_SOBEL_XY_3X3_08U, 30, gScenarioKernelData100_SOBEL_XY_3X3_08U, 2},
{12, 10, 1152, 0, 1, gScenarioBufferData101_SOBEL_XY_3X3_08U, 30, gScenarioKernelData101_SOBEL_XY_3X3_08U, 2},
{14, 10, 1316, 0, 1, gScenarioBufferData102_SOBEL_XY_3X3_08U, 30, gScenarioKernelData102_SOBEL_XY_3X3_08U, 2},
{16, 10, 1480, 0, 1, gScenarioBufferData103_SOBEL_XY_3X3_08U, 30, gScenarioKernelData103_SOBEL_XY_3X3_08U, 2},
{18, 10, 1644, 0, 1, gScenarioBufferData104_SOBEL_XY_3X3_08U, 30, gScenarioKernelData104_SOBEL_XY_3X3_08U, 2},
{20, 10, 1808, 0, 1, gScenarioBufferData105_SOBEL_XY_3X3_08U, 30, gScenarioKernelData105_SOBEL_XY_3X3_08U, 2},
{22, 10, 1972, 0, 1, gScenarioBufferData106_SOBEL_XY_3X3_08U, 30, gScenarioKernelData106_SOBEL_XY_3X3_08U, 2},
{24, 10, 2136, 0, 1, gScenarioBufferData107_SOBEL_XY_3X3_08U, 30, gScenarioKernelData107_SOBEL_XY_3X3_08U, 2},
{26, 10, 2300, 0, 1, gScenarioBufferData108_SOBEL_XY_3X3_08U, 30, gScenarioKernelData108_SOBEL_XY_3X3_08U, 2},
{28, 10, 2464, 0, 1, gScenarioBufferData109_SOBEL_XY_3X3_08U, 30, gScenarioKernelData109_SOBEL_XY_3X3_08U, 2},
{30, 10, 2628, 0, 1, gScenarioBufferData110_SOBEL_XY_3X3_08U, 30, gScenarioKernelData110_SOBEL_XY_3X3_08U, 2},
{32, 10, 2792, 0, 1, gScenarioBufferData111_SOBEL_XY_3X3_08U, 30, gScenarioKernelData111_SOBEL_XY_3X3_08U, 2},
{2, 12, 396, 0, 1, gScenarioBufferData112_SOBEL_XY_3X3_08U, 30, gScenarioKernelData112_SOBEL_XY_3X3_08U, 2},
{4, 12, 592, 0, 1, gScenarioBufferData113_SOBEL_XY_3X3_08U, 30, gScenarioKernelData113_SOBEL_XY_3X3_08U, 2},
{6, 12, 788, 0, 1, gScenarioBufferData114_SOBEL_XY_3X3_08U, 30, gScenarioKernelData114_SOBEL_XY_3X3_08U, 2},
{8, 12, 984, 0, 1, gScenarioBufferData115_SOBEL_XY_3X3_08U, 30, gScenarioKernelData115_SOBEL_XY_3X3_08U, 2},
{10, 12, 1180, 0, 1, gScenarioBufferData116_SOBEL_XY_3X3_08U, 30, gScenarioKernelData116_SOBEL_XY_3X3_08U, 2},
{12, 12, 1376, 0, 1, gScenarioBufferData117_SOBEL_XY_3X3_08U, 30, gScenarioKernelData117_SOBEL_XY_3X3_08U, 2},
{14, 12, 1572, 0, 1, gScenarioBufferData118_SOBEL_XY_3X3_08U, 30, gScenarioKernelData118_SOBEL_XY_3X3_08U, 2},
{16, 12, 1768, 0, 1, gScenarioBufferData119_SOBEL_XY_3X3_08U, 30, gScenarioKernelData119_SOBEL_XY_3X3_08U, 2},
{18, 12, 1964, 0, 1, gScenarioBufferData120_SOBEL_XY_3X3_08U, 30, gScenarioKernelData120_SOBEL_XY_3X3_08U, 2},
{20, 12, 2160, 0, 1, gScenarioBufferData121_SOBEL_XY_3X3_08U, 30, gScenarioKernelData121_SOBEL_XY_3X3_08U, 2},
{22, 12, 2356, 0, 1, gScenarioBufferData122_SOBEL_XY_3X3_08U, 30, gScenarioKernelData122_SOBEL_XY_3X3_08U, 2},
{24, 12, 2552, 0, 1, gScenarioBufferData123_SOBEL_XY_3X3_08U, 30, gScenarioKernelData123_SOBEL_XY_3X3_08U, 2},
{26, 12, 2748, 0, 1, gScenarioBufferData124_SOBEL_XY_3X3_08U, 30, gScenarioKernelData124_SOBEL_XY_3X3_08U, 2},
{28, 12, 2944, 0, 1, gScenarioBufferData125_SOBEL_XY_3X3_08U, 30, gScenarioKernelData125_SOBEL_XY_3X3_08U, 2},
{30, 12, 3140, 0, 1, gScenarioBufferData126_SOBEL_XY_3X3_08U, 30, gScenarioKernelData126_SOBEL_XY_3X3_08U, 2},
{32, 12, 3336, 0, 1, gScenarioBufferData127_SOBEL_XY_3X3_08U, 30, gScenarioKernelData127_SOBEL_XY_3X3_08U, 2},
{2, 14, 460, 0, 1, gScenarioBufferData128_SOBEL_XY_3X3_08U, 30, gScenarioKernelData128_SOBEL_XY_3X3_08U, 2},
{4, 14, 688, 0, 1, gScenarioBufferData129_SOBEL_XY_3X3_08U, 30, gScenarioKernelData129_SOBEL_XY_3X3_08U, 2},
{6, 14, 916, 0, 1, gScenarioBufferData130_SOBEL_XY_3X3_08U, 30, gScenarioKernelData130_SOBEL_XY_3X3_08U, 2},
{8, 14, 1144, 0, 1, gScenarioBufferData131_SOBEL_XY_3X3_08U, 30, gScenarioKernelData131_SOBEL_XY_3X3_08U, 2},
{10, 14, 1372, 0, 1, gScenarioBufferData132_SOBEL_XY_3X3_08U, 30, gScenarioKernelData132_SOBEL_XY_3X3_08U, 2},
{12, 14, 1600, 0, 1, gScenarioBufferData133_SOBEL_XY_3X3_08U, 30, gScenarioKernelData133_SOBEL_XY_3X3_08U, 2},
{14, 14, 1828, 0, 1, gScenarioBufferData134_SOBEL_XY_3X3_08U, 30, gScenarioKernelData134_SOBEL_XY_3X3_08U, 2},
{16, 14, 2056, 0, 1, gScenarioBufferData135_SOBEL_XY_3X3_08U, 30, gScenarioKernelData135_SOBEL_XY_3X3_08U, 2},
{18, 14, 2284, 0, 1, gScenarioBufferData136_SOBEL_XY_3X3_08U, 30, gScenarioKernelData136_SOBEL_XY_3X3_08U, 2},
{20, 14, 2512, 0, 1, gScenarioBufferData137_SOBEL_XY_3X3_08U, 30, gScenarioKernelData137_SOBEL_XY_3X3_08U, 2},
{22, 14, 2740, 0, 1, gScenarioBufferData138_SOBEL_XY_3X3_08U, 30, gScenarioKernelData138_SOBEL_XY_3X3_08U, 2},
{24, 14, 2968, 0, 1, gScenarioBufferData139_SOBEL_XY_3X3_08U, 30, gScenarioKernelData139_SOBEL_XY_3X3_08U, 2},
{26, 14, 3196, 0, 1, gScenarioBufferData140_SOBEL_XY_3X3_08U, 30, gScenarioKernelData140_SOBEL_XY_3X3_08U, 2},
{28, 14, 3424, 0, 1, gScenarioBufferData141_SOBEL_XY_3X3_08U, 30, gScenarioKernelData141_SOBEL_XY_3X3_08U, 2},
{30, 14, 3652, 0, 1, gScenarioBufferData142_SOBEL_XY_3X3_08U, 30, gScenarioKernelData142_SOBEL_XY_3X3_08U, 2},
{2, 16, 524, 0, 1, gScenarioBufferData143_SOBEL_XY_3X3_08U, 30, gScenarioKernelData143_SOBEL_XY_3X3_08U, 2},
{4, 16, 784, 0, 1, gScenarioBufferData144_SOBEL_XY_3X3_08U, 30, gScenarioKernelData144_SOBEL_XY_3X3_08U, 2},
{6, 16, 1044, 0, 1, gScenarioBufferData145_SOBEL_XY_3X3_08U, 30, gScenarioKernelData145_SOBEL_XY_3X3_08U, 2},
{8, 16, 1304, 0, 1, gScenarioBufferData146_SOBEL_XY_3X3_08U, 30, gScenarioKernelData146_SOBEL_XY_3X3_08U, 2},
{10, 16, 1564, 0, 1, gScenarioBufferData147_SOBEL_XY_3X3_08U, 30, gScenarioKernelData147_SOBEL_XY_3X3_08U, 2},
{12, 16, 1824, 0, 1, gScenarioBufferData148_SOBEL_XY_3X3_08U, 30, gScenarioKernelData148_SOBEL_XY_3X3_08U, 2},
{14, 16, 2084, 0, 1, gScenarioBufferData149_SOBEL_XY_3X3_08U, 30, gScenarioKernelData149_SOBEL_XY_3X3_08U, 2},
{16, 16, 2344, 0, 1, gScenarioBufferData150_SOBEL_XY_3X3_08U, 30, gScenarioKernelData150_SOBEL_XY_3X3_08U, 2},
{18, 16, 2604, 0, 1, gScenarioBufferData151_SOBEL_XY_3X3_08U, 30, gScenarioKernelData151_SOBEL_XY_3X3_08U, 2},
{20, 16, 2864, 0, 1, gScenarioBufferData152_SOBEL_XY_3X3_08U, 30, gScenarioKernelData152_SOBEL_XY_3X3_08U, 2},
{22, 16, 3124, 0, 1, gScenarioBufferData153_SOBEL_XY_3X3_08U, 30, gScenarioKernelData153_SOBEL_XY_3X3_08U, 2},
{24, 16, 3384, 0, 1, gScenarioBufferData154_SOBEL_XY_3X3_08U, 30, gScenarioKernelData154_SOBEL_XY_3X3_08U, 2},
{26, 16, 3644, 0, 1, gScenarioBufferData155_SOBEL_XY_3X3_08U, 30, gScenarioKernelData155_SOBEL_XY_3X3_08U, 2},
{2, 18, 588, 0, 1, gScenarioBufferData156_SOBEL_XY_3X3_08U, 30, gScenarioKernelData156_SOBEL_XY_3X3_08U, 2},
{4, 18, 880, 0, 1, gScenarioBufferData157_SOBEL_XY_3X3_08U, 30, gScenarioKernelData157_SOBEL_XY_3X3_08U, 2},
{6, 18, 1172, 0, 1, gScenarioBufferData158_SOBEL_XY_3X3_08U, 30, gScenarioKernelData158_SOBEL_XY_3X3_08U, 2},
{8, 18, 1464, 0, 1, gScenarioBufferData159_SOBEL_XY_3X3_08U, 30, gScenarioKernelData159_SOBEL_XY_3X3_08U, 2},
{10, 18, 1756, 0, 1, gScenarioBufferData160_SOBEL_XY_3X3_08U, 30, gScenarioKernelData160_SOBEL_XY_3X3_08U, 2},
{12, 18, 2048, 0, 1, gScenarioBufferData161_SOBEL_XY_3X3_08U, 30, gScenarioKernelData161_SOBEL_XY_3X3_08U, 2},
{14, 18, 2340, 0, 1, gScenarioBufferData162_SOBEL_XY_3X3_08U, 30, gScenarioKernelData162_SOBEL_XY_3X3_08U, 2},
{16, 18, 2632, 0, 1, gScenarioBufferData163_SOBEL_XY_3X3_08U, 30, gScenarioKernelData163_SOBEL_XY_3X3_08U, 2},
{18, 18, 2924, 0, 1, gScenarioBufferData164_SOBEL_XY_3X3_08U, 30, gScenarioKernelData164_SOBEL_XY_3X3_08U, 2},
{20, 18, 3216, 0, 1, gScenarioBufferData165_SOBEL_XY_3X3_08U, 30, gScenarioKernelData165_SOBEL_XY_3X3_08U, 2},
{22, 18, 3508, 0, 1, gScenarioBufferData166_SOBEL_XY_3X3_08U, 30, gScenarioKernelData166_SOBEL_XY_3X3_08U, 2},
{24, 18, 3800, 0, 1, gScenarioBufferData167_SOBEL_XY_3X3_08U, 30, gScenarioKernelData167_SOBEL_XY_3X3_08U, 2},
{2, 20, 652, 0, 1, gScenarioBufferData168_SOBEL_XY_3X3_08U, 30, gScenarioKernelData168_SOBEL_XY_3X3_08U, 2},
{4, 20, 976, 0, 1, gScenarioBufferData169_SOBEL_XY_3X3_08U, 30, gScenarioKernelData169_SOBEL_XY_3X3_08U, 2},
{6, 20, 1300, 0, 1, gScenarioBufferData170_SOBEL_XY_3X3_08U, 30, gScenarioKernelData170_SOBEL_XY_3X3_08U, 2},
{8, 20, 1624, 0, 1, gScenarioBufferData171_SOBEL_XY_3X3_08U, 30, gScenarioKernelData171_SOBEL_XY_3X3_08U, 2},
{10, 20, 1948, 0, 1, gScenarioBufferData172_SOBEL_XY_3X3_08U, 30, gScenarioKernelData172_SOBEL_XY_3X3_08U, 2},
{12, 20, 2272, 0, 1, gScenarioBufferData173_SOBEL_XY_3X3_08U, 30, gScenarioKernelData173_SOBEL_XY_3X3_08U, 2},
{14, 20, 2596, 0, 1, gScenarioBufferData174_SOBEL_XY_3X3_08U, 30, gScenarioKernelData174_SOBEL_XY_3X3_08U, 2},
{16, 20, 2920, 0, 1, gScenarioBufferData175_SOBEL_XY_3X3_08U, 30, gScenarioKernelData175_SOBEL_XY_3X3_08U, 2},
{18, 20, 3244, 0, 1, gScenarioBufferData176_SOBEL_XY_3X3_08U, 30, gScenarioKernelData176_SOBEL_XY_3X3_08U, 2},
{20, 20, 3568, 0, 1, gScenarioBufferData177_SOBEL_XY_3X3_08U, 30, gScenarioKernelData177_SOBEL_XY_3X3_08U, 2},
{2, 22, 716, 0, 1, gScenarioBufferData178_SOBEL_XY_3X3_08U, 30, gScenarioKernelData178_SOBEL_XY_3X3_08U, 2},
{4, 22, 1072, 0, 1, gScenarioBufferData179_SOBEL_XY_3X3_08U, 30, gScenarioKernelData179_SOBEL_XY_3X3_08U, 2},
{6, 22, 1428, 0, 1, gScenarioBufferData180_SOBEL_XY_3X3_08U, 30, gScenarioKernelData180_SOBEL_XY_3X3_08U, 2},
{8, 22, 1784, 0, 1, gScenarioBufferData181_SOBEL_XY_3X3_08U, 30, gScenarioKernelData181_SOBEL_XY_3X3_08U, 2},
{10, 22, 2140, 0, 1, gScenarioBufferData182_SOBEL_XY_3X3_08U, 30, gScenarioKernelData182_SOBEL_XY_3X3_08U, 2},
{12, 22, 2496, 0, 1, gScenarioBufferData183_SOBEL_XY_3X3_08U, 30, gScenarioKernelData183_SOBEL_XY_3X3_08U, 2},
{14, 22, 2852, 0, 1, gScenarioBufferData184_SOBEL_XY_3X3_08U, 30, gScenarioKernelData184_SOBEL_XY_3X3_08U, 2},
{16, 22, 3208, 0, 1, gScenarioBufferData185_SOBEL_XY_3X3_08U, 30, gScenarioKernelData185_SOBEL_XY_3X3_08U, 2},
{18, 22, 3564, 0, 1, gScenarioBufferData186_SOBEL_XY_3X3_08U, 30, gScenarioKernelData186_SOBEL_XY_3X3_08U, 2},
{2, 24, 780, 0, 1, gScenarioBufferData187_SOBEL_XY_3X3_08U, 30, gScenarioKernelData187_SOBEL_XY_3X3_08U, 2},
{4, 24, 1168, 0, 1, gScenarioBufferData188_SOBEL_XY_3X3_08U, 30, gScenarioKernelData188_SOBEL_XY_3X3_08U, 2},
{6, 24, 1556, 0, 1, gScenarioBufferData189_SOBEL_XY_3X3_08U, 30, gScenarioKernelData189_SOBEL_XY_3X3_08U, 2},
{8, 24, 1944, 0, 1, gScenarioBufferData190_SOBEL_XY_3X3_08U, 30, gScenarioKernelData190_SOBEL_XY_3X3_08U, 2},
{10, 24, 2332, 0, 1, gScenarioBufferData191_SOBEL_XY_3X3_08U, 30, gScenarioKernelData191_SOBEL_XY_3X3_08U, 2},
{12, 24, 2720, 0, 1, gScenarioBufferData192_SOBEL_XY_3X3_08U, 30, gScenarioKernelData192_SOBEL_XY_3X3_08U, 2},
{14, 24, 3108, 0, 1, gScenarioBufferData193_SOBEL_XY_3X3_08U, 30, gScenarioKernelData193_SOBEL_XY_3X3_08U, 2},
{16, 24, 3496, 0, 1, gScenarioBufferData194_SOBEL_XY_3X3_08U, 30, gScenarioKernelData194_SOBEL_XY_3X3_08U, 2},
{2, 26, 844, 0, 1, gScenarioBufferData195_SOBEL_XY_3X3_08U, 30, gScenarioKernelData195_SOBEL_XY_3X3_08U, 2},
{4, 26, 1264, 0, 1, gScenarioBufferData196_SOBEL_XY_3X3_08U, 30, gScenarioKernelData196_SOBEL_XY_3X3_08U, 2},
{6, 26, 1684, 0, 1, gScenarioBufferData197_SOBEL_XY_3X3_08U, 30, gScenarioKernelData197_SOBEL_XY_3X3_08U, 2},
{8, 26, 2104, 0, 1, gScenarioBufferData198_SOBEL_XY_3X3_08U, 30, gScenarioKernelData198_SOBEL_XY_3X3_08U, 2},
{10, 26, 2524, 0, 1, gScenarioBufferData199_SOBEL_XY_3X3_08U, 30, gScenarioKernelData199_SOBEL_XY_3X3_08U, 2},
{12, 26, 2944, 0, 1, gScenarioBufferData200_SOBEL_XY_3X3_08U, 30, gScenarioKernelData200_SOBEL_XY_3X3_08U, 2},
{14, 26, 3364, 0, 1, gScenarioBufferData201_SOBEL_XY_3X3_08U, 30, gScenarioKernelData201_SOBEL_XY_3X3_08U, 2},
{16, 26, 3784, 0, 1, gScenarioBufferData202_SOBEL_XY_3X3_08U, 30, gScenarioKernelData202_SOBEL_XY_3X3_08U, 2},
{2, 28, 908, 0, 1, gScenarioBufferData203_SOBEL_XY_3X3_08U, 30, gScenarioKernelData203_SOBEL_XY_3X3_08U, 2},
{4, 28, 1360, 0, 1, gScenarioBufferData204_SOBEL_XY_3X3_08U, 30, gScenarioKernelData204_SOBEL_XY_3X3_08U, 2},
{6, 28, 1812, 0, 1, gScenarioBufferData205_SOBEL_XY_3X3_08U, 30, gScenarioKernelData205_SOBEL_XY_3X3_08U, 2},
{8, 28, 2264, 0, 1, gScenarioBufferData206_SOBEL_XY_3X3_08U, 30, gScenarioKernelData206_SOBEL_XY_3X3_08U, 2},
{10, 28, 2716, 0, 1, gScenarioBufferData207_SOBEL_XY_3X3_08U, 30, gScenarioKernelData207_SOBEL_XY_3X3_08U, 2},
{12, 28, 3168, 0, 1, gScenarioBufferData208_SOBEL_XY_3X3_08U, 30, gScenarioKernelData208_SOBEL_XY_3X3_08U, 2},
{14, 28, 3620, 0, 1, gScenarioBufferData209_SOBEL_XY_3X3_08U, 30, gScenarioKernelData209_SOBEL_XY_3X3_08U, 2},
{2, 30, 972, 0, 1, gScenarioBufferData210_SOBEL_XY_3X3_08U, 30, gScenarioKernelData210_SOBEL_XY_3X3_08U, 2},
{4, 30, 1456, 0, 1, gScenarioBufferData211_SOBEL_XY_3X3_08U, 30, gScenarioKernelData211_SOBEL_XY_3X3_08U, 2},
{6, 30, 1940, 0, 1, gScenarioBufferData212_SOBEL_XY_3X3_08U, 30, gScenarioKernelData212_SOBEL_XY_3X3_08U, 2},
{8, 30, 2424, 0, 1, gScenarioBufferData213_SOBEL_XY_3X3_08U, 30, gScenarioKernelData213_SOBEL_XY_3X3_08U, 2},
{10, 30, 2908, 0, 1, gScenarioBufferData214_SOBEL_XY_3X3_08U, 30, gScenarioKernelData214_SOBEL_XY_3X3_08U, 2},
{12, 30, 3392, 0, 1, gScenarioBufferData215_SOBEL_XY_3X3_08U, 30, gScenarioKernelData215_SOBEL_XY_3X3_08U, 2},
{2, 32, 1036, 0, 1, gScenarioBufferData216_SOBEL_XY_3X3_08U, 30, gScenarioKernelData216_SOBEL_XY_3X3_08U, 2},
{4, 32, 1552, 0, 1, gScenarioBufferData217_SOBEL_XY_3X3_08U, 30, gScenarioKernelData217_SOBEL_XY_3X3_08U, 2},
{6, 32, 2068, 0, 1, gScenarioBufferData218_SOBEL_XY_3X3_08U, 30, gScenarioKernelData218_SOBEL_XY_3X3_08U, 2},
{8, 32, 2584, 0, 1, gScenarioBufferData219_SOBEL_XY_3X3_08U, 30, gScenarioKernelData219_SOBEL_XY_3X3_08U, 2},
{10, 32, 3100, 0, 1, gScenarioBufferData220_SOBEL_XY_3X3_08U, 30, gScenarioKernelData220_SOBEL_XY_3X3_08U, 2},
{12, 32, 3616, 0, 1, gScenarioBufferData221_SOBEL_XY_3X3_08U, 30, gScenarioKernelData221_SOBEL_XY_3X3_08U, 2}
};

static acf_scenario_list gScenarioList_SOBEL_XY_3X3_08U = {
222, //number of scenarios
gScenarioArray_SOBEL_XY_3X3_08U};
//**************************************************************

class SOBEL_XY_3X3_08U : public ACF_Process_APU
{
public:
   SOBEL_XY_3X3_08U(int32_t apex_id = 0) : ACF_Process_APU(apex_id)
   {} 

   int32_t Initialize()
   {
      int32_t lRetVal = 0;

      if (!Initialized()) //initialization steps that only need to occur once
      {
         SetProcessIdentifier("SOBEL_XY_3X3_08U");
         SetApuLoadInfo(SOBEL_XY_3X3_08U_LOAD_SEGMENTS,
                        SOBEL_XY_3X3_08U_LOAD_PMEM, SOBEL_XY_3X3_08U_LOAD_PMEM_SIZE,
                        SOBEL_XY_3X3_08U_LOAD_DMEM, SOBEL_XY_3X3_08U_LOAD_DMEM_SIZE,
                        0, 0); //assuming _LOAD_CMEM does not exist
         FlagSpatialDep();

         //***NOTE: the order in which the following ports are added is meaningful; do not change!

         AddPort("INPUT_0", ICP_DATATYPE_08U, 1, 1, 2, 1, 0, 0, 0, 0, 0, 0, 0, 0x1010101);
         AddPort("OUTPUT_0", ICP_DATATYPE_08U, 1, 1, 2, 1, 1, 0, 0, 0, 0, 0, 1);
         AddPort("OUTPUT_1", ICP_DATATYPE_08U, 1, 1, 2, 1, 1, 0, 0, 0, 0, 0, 2);

         CfgScenarios(&gScenarioList_SOBEL_XY_3X3_08U);

         FlagAsInitialized();
      }

      lRetVal = SelectApuConfiguration(mApuCfg, mApexId); //by default mApuCfg = ACF_APU_CFG__APEX0_DEFAULT and mApexId = 0

      return lRetVal;
   }
};

#endif //_ACF_PROCESS_APU_SOBEL_XY_3X3_08U
