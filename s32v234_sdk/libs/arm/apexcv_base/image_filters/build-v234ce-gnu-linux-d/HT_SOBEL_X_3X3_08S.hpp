#ifndef _ACF_PROCESS_APU_HT_SOBEL_X_3X3_08S
#define _ACF_PROCESS_APU_HT_SOBEL_X_3X3_08S

#include <acf_process_apu.h>
#include <HT_SOBEL_X_3X3_08S_APU_LOAD.h> //APU load associated with this process
#include <stdint.h>


//SCENARIO LIST*************************************************
static acf_scenario_buffer_data gScenarioBufferData0_HT_SOBEL_X_3X3_08S[] = {{4, 1, 4, 0, 0x2211}, {4, 1, 2, 1, 0x0}, {4, 1, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData1_HT_SOBEL_X_3X3_08S[] = {{8, 1, 4, 0, 0x2211}, {8, 1, 2, 1, 0x0}, {8, 1, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData2_HT_SOBEL_X_3X3_08S[] = {{12, 1, 4, 0, 0x2211}, {12, 1, 2, 1, 0x0}, {12, 1, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData3_HT_SOBEL_X_3X3_08S[] = {{16, 1, 4, 0, 0x2211}, {16, 1, 2, 1, 0x0}, {16, 1, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData4_HT_SOBEL_X_3X3_08S[] = {{20, 1, 4, 0, 0x2211}, {20, 1, 2, 1, 0x0}, {20, 1, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData5_HT_SOBEL_X_3X3_08S[] = {{24, 1, 4, 0, 0x2211}, {24, 1, 2, 1, 0x0}, {24, 1, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData6_HT_SOBEL_X_3X3_08S[] = {{28, 1, 4, 0, 0x2211}, {28, 1, 2, 1, 0x0}, {28, 1, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData7_HT_SOBEL_X_3X3_08S[] = {{32, 1, 4, 0, 0x2211}, {32, 1, 2, 1, 0x0}, {32, 1, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData8_HT_SOBEL_X_3X3_08S[] = {{40, 1, 4, 0, 0x2211}, {40, 1, 2, 1, 0x0}, {40, 1, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData9_HT_SOBEL_X_3X3_08S[] = {{48, 1, 4, 0, 0x2211}, {48, 1, 2, 1, 0x0}, {48, 1, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData10_HT_SOBEL_X_3X3_08S[] = {{56, 1, 4, 0, 0x2211}, {56, 1, 2, 1, 0x0}, {56, 1, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData11_HT_SOBEL_X_3X3_08S[] = {{64, 1, 4, 0, 0x2211}, {64, 1, 2, 1, 0x0}, {64, 1, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData12_HT_SOBEL_X_3X3_08S[] = {{4, 2, 4, 0, 0x2211}, {4, 2, 2, 1, 0x0}, {4, 2, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData13_HT_SOBEL_X_3X3_08S[] = {{8, 2, 4, 0, 0x2211}, {8, 2, 2, 1, 0x0}, {8, 2, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData14_HT_SOBEL_X_3X3_08S[] = {{12, 2, 4, 0, 0x2211}, {12, 2, 2, 1, 0x0}, {12, 2, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData15_HT_SOBEL_X_3X3_08S[] = {{16, 2, 4, 0, 0x2211}, {16, 2, 2, 1, 0x0}, {16, 2, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData16_HT_SOBEL_X_3X3_08S[] = {{20, 2, 4, 0, 0x2211}, {20, 2, 2, 1, 0x0}, {20, 2, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData17_HT_SOBEL_X_3X3_08S[] = {{24, 2, 4, 0, 0x2211}, {24, 2, 2, 1, 0x0}, {24, 2, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData18_HT_SOBEL_X_3X3_08S[] = {{28, 2, 4, 0, 0x2211}, {28, 2, 2, 1, 0x0}, {28, 2, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData19_HT_SOBEL_X_3X3_08S[] = {{32, 2, 4, 0, 0x2211}, {32, 2, 2, 1, 0x0}, {32, 2, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData20_HT_SOBEL_X_3X3_08S[] = {{40, 2, 4, 0, 0x2211}, {40, 2, 2, 1, 0x0}, {40, 2, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData21_HT_SOBEL_X_3X3_08S[] = {{48, 2, 4, 0, 0x2211}, {48, 2, 2, 1, 0x0}, {48, 2, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData22_HT_SOBEL_X_3X3_08S[] = {{56, 2, 4, 0, 0x2211}, {56, 2, 2, 1, 0x0}, {56, 2, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData23_HT_SOBEL_X_3X3_08S[] = {{64, 2, 4, 0, 0x2211}, {64, 2, 2, 1, 0x0}, {64, 2, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData24_HT_SOBEL_X_3X3_08S[] = {{4, 4, 4, 0, 0x2211}, {4, 4, 2, 1, 0x0}, {4, 4, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData25_HT_SOBEL_X_3X3_08S[] = {{8, 4, 4, 0, 0x2211}, {8, 4, 2, 1, 0x0}, {8, 4, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData26_HT_SOBEL_X_3X3_08S[] = {{12, 4, 4, 0, 0x2211}, {12, 4, 2, 1, 0x0}, {12, 4, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData27_HT_SOBEL_X_3X3_08S[] = {{16, 4, 4, 0, 0x2211}, {16, 4, 2, 1, 0x0}, {16, 4, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData28_HT_SOBEL_X_3X3_08S[] = {{20, 4, 4, 0, 0x2211}, {20, 4, 2, 1, 0x0}, {20, 4, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData29_HT_SOBEL_X_3X3_08S[] = {{24, 4, 4, 0, 0x2211}, {24, 4, 2, 1, 0x0}, {24, 4, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData30_HT_SOBEL_X_3X3_08S[] = {{28, 4, 4, 0, 0x2211}, {28, 4, 2, 1, 0x0}, {28, 4, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData31_HT_SOBEL_X_3X3_08S[] = {{32, 4, 4, 0, 0x2211}, {32, 4, 2, 1, 0x0}, {32, 4, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData32_HT_SOBEL_X_3X3_08S[] = {{40, 4, 4, 0, 0x2211}, {40, 4, 2, 1, 0x0}, {40, 4, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData33_HT_SOBEL_X_3X3_08S[] = {{48, 4, 4, 0, 0x2211}, {48, 4, 2, 1, 0x0}, {48, 4, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData34_HT_SOBEL_X_3X3_08S[] = {{56, 4, 4, 0, 0x2211}, {56, 4, 2, 1, 0x0}, {56, 4, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData35_HT_SOBEL_X_3X3_08S[] = {{64, 4, 4, 0, 0x2211}, {64, 4, 2, 1, 0x0}, {64, 4, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData36_HT_SOBEL_X_3X3_08S[] = {{4, 6, 4, 0, 0x2211}, {4, 6, 2, 1, 0x0}, {4, 6, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData37_HT_SOBEL_X_3X3_08S[] = {{8, 6, 4, 0, 0x2211}, {8, 6, 2, 1, 0x0}, {8, 6, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData38_HT_SOBEL_X_3X3_08S[] = {{12, 6, 4, 0, 0x2211}, {12, 6, 2, 1, 0x0}, {12, 6, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData39_HT_SOBEL_X_3X3_08S[] = {{16, 6, 4, 0, 0x2211}, {16, 6, 2, 1, 0x0}, {16, 6, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData40_HT_SOBEL_X_3X3_08S[] = {{20, 6, 4, 0, 0x2211}, {20, 6, 2, 1, 0x0}, {20, 6, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData41_HT_SOBEL_X_3X3_08S[] = {{24, 6, 4, 0, 0x2211}, {24, 6, 2, 1, 0x0}, {24, 6, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData42_HT_SOBEL_X_3X3_08S[] = {{28, 6, 4, 0, 0x2211}, {28, 6, 2, 1, 0x0}, {28, 6, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData43_HT_SOBEL_X_3X3_08S[] = {{32, 6, 4, 0, 0x2211}, {32, 6, 2, 1, 0x0}, {32, 6, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData44_HT_SOBEL_X_3X3_08S[] = {{40, 6, 4, 0, 0x2211}, {40, 6, 2, 1, 0x0}, {40, 6, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData45_HT_SOBEL_X_3X3_08S[] = {{48, 6, 4, 0, 0x2211}, {48, 6, 2, 1, 0x0}, {48, 6, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData46_HT_SOBEL_X_3X3_08S[] = {{56, 6, 4, 0, 0x2211}, {56, 6, 2, 1, 0x0}, {56, 6, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData47_HT_SOBEL_X_3X3_08S[] = {{4, 8, 4, 0, 0x2211}, {4, 8, 2, 1, 0x0}, {4, 8, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData48_HT_SOBEL_X_3X3_08S[] = {{8, 8, 4, 0, 0x2211}, {8, 8, 2, 1, 0x0}, {8, 8, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData49_HT_SOBEL_X_3X3_08S[] = {{12, 8, 4, 0, 0x2211}, {12, 8, 2, 1, 0x0}, {12, 8, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData50_HT_SOBEL_X_3X3_08S[] = {{16, 8, 4, 0, 0x2211}, {16, 8, 2, 1, 0x0}, {16, 8, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData51_HT_SOBEL_X_3X3_08S[] = {{20, 8, 4, 0, 0x2211}, {20, 8, 2, 1, 0x0}, {20, 8, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData52_HT_SOBEL_X_3X3_08S[] = {{24, 8, 4, 0, 0x2211}, {24, 8, 2, 1, 0x0}, {24, 8, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData53_HT_SOBEL_X_3X3_08S[] = {{28, 8, 4, 0, 0x2211}, {28, 8, 2, 1, 0x0}, {28, 8, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData54_HT_SOBEL_X_3X3_08S[] = {{32, 8, 4, 0, 0x2211}, {32, 8, 2, 1, 0x0}, {32, 8, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData55_HT_SOBEL_X_3X3_08S[] = {{40, 8, 4, 0, 0x2211}, {40, 8, 2, 1, 0x0}, {40, 8, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData56_HT_SOBEL_X_3X3_08S[] = {{4, 10, 4, 0, 0x2211}, {4, 10, 2, 1, 0x0}, {4, 10, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData57_HT_SOBEL_X_3X3_08S[] = {{8, 10, 4, 0, 0x2211}, {8, 10, 2, 1, 0x0}, {8, 10, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData58_HT_SOBEL_X_3X3_08S[] = {{12, 10, 4, 0, 0x2211}, {12, 10, 2, 1, 0x0}, {12, 10, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData59_HT_SOBEL_X_3X3_08S[] = {{16, 10, 4, 0, 0x2211}, {16, 10, 2, 1, 0x0}, {16, 10, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData60_HT_SOBEL_X_3X3_08S[] = {{20, 10, 4, 0, 0x2211}, {20, 10, 2, 1, 0x0}, {20, 10, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData61_HT_SOBEL_X_3X3_08S[] = {{24, 10, 4, 0, 0x2211}, {24, 10, 2, 1, 0x0}, {24, 10, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData62_HT_SOBEL_X_3X3_08S[] = {{28, 10, 4, 0, 0x2211}, {28, 10, 2, 1, 0x0}, {28, 10, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData63_HT_SOBEL_X_3X3_08S[] = {{32, 10, 4, 0, 0x2211}, {32, 10, 2, 1, 0x0}, {32, 10, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData64_HT_SOBEL_X_3X3_08S[] = {{4, 12, 4, 0, 0x2211}, {4, 12, 2, 1, 0x0}, {4, 12, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData65_HT_SOBEL_X_3X3_08S[] = {{8, 12, 4, 0, 0x2211}, {8, 12, 2, 1, 0x0}, {8, 12, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData66_HT_SOBEL_X_3X3_08S[] = {{12, 12, 4, 0, 0x2211}, {12, 12, 2, 1, 0x0}, {12, 12, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData67_HT_SOBEL_X_3X3_08S[] = {{16, 12, 4, 0, 0x2211}, {16, 12, 2, 1, 0x0}, {16, 12, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData68_HT_SOBEL_X_3X3_08S[] = {{20, 12, 4, 0, 0x2211}, {20, 12, 2, 1, 0x0}, {20, 12, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData69_HT_SOBEL_X_3X3_08S[] = {{24, 12, 4, 0, 0x2211}, {24, 12, 2, 1, 0x0}, {24, 12, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData70_HT_SOBEL_X_3X3_08S[] = {{28, 12, 4, 0, 0x2211}, {28, 12, 2, 1, 0x0}, {28, 12, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData71_HT_SOBEL_X_3X3_08S[] = {{4, 14, 4, 0, 0x2211}, {4, 14, 2, 1, 0x0}, {4, 14, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData72_HT_SOBEL_X_3X3_08S[] = {{8, 14, 4, 0, 0x2211}, {8, 14, 2, 1, 0x0}, {8, 14, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData73_HT_SOBEL_X_3X3_08S[] = {{12, 14, 4, 0, 0x2211}, {12, 14, 2, 1, 0x0}, {12, 14, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData74_HT_SOBEL_X_3X3_08S[] = {{16, 14, 4, 0, 0x2211}, {16, 14, 2, 1, 0x0}, {16, 14, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData75_HT_SOBEL_X_3X3_08S[] = {{20, 14, 4, 0, 0x2211}, {20, 14, 2, 1, 0x0}, {20, 14, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData76_HT_SOBEL_X_3X3_08S[] = {{24, 14, 4, 0, 0x2211}, {24, 14, 2, 1, 0x0}, {24, 14, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData77_HT_SOBEL_X_3X3_08S[] = {{4, 16, 4, 0, 0x2211}, {4, 16, 2, 1, 0x0}, {4, 16, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData78_HT_SOBEL_X_3X3_08S[] = {{8, 16, 4, 0, 0x2211}, {8, 16, 2, 1, 0x0}, {8, 16, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData79_HT_SOBEL_X_3X3_08S[] = {{12, 16, 4, 0, 0x2211}, {12, 16, 2, 1, 0x0}, {12, 16, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData80_HT_SOBEL_X_3X3_08S[] = {{16, 16, 4, 0, 0x2211}, {16, 16, 2, 1, 0x0}, {16, 16, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData81_HT_SOBEL_X_3X3_08S[] = {{20, 16, 4, 0, 0x2211}, {20, 16, 2, 1, 0x0}, {20, 16, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData82_HT_SOBEL_X_3X3_08S[] = {{4, 18, 4, 0, 0x2211}, {4, 18, 2, 1, 0x0}, {4, 18, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData83_HT_SOBEL_X_3X3_08S[] = {{8, 18, 4, 0, 0x2211}, {8, 18, 2, 1, 0x0}, {8, 18, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData84_HT_SOBEL_X_3X3_08S[] = {{12, 18, 4, 0, 0x2211}, {12, 18, 2, 1, 0x0}, {12, 18, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData85_HT_SOBEL_X_3X3_08S[] = {{16, 18, 4, 0, 0x2211}, {16, 18, 2, 1, 0x0}, {16, 18, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData86_HT_SOBEL_X_3X3_08S[] = {{4, 20, 4, 0, 0x2211}, {4, 20, 2, 1, 0x0}, {4, 20, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData87_HT_SOBEL_X_3X3_08S[] = {{8, 20, 4, 0, 0x2211}, {8, 20, 2, 1, 0x0}, {8, 20, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData88_HT_SOBEL_X_3X3_08S[] = {{12, 20, 4, 0, 0x2211}, {12, 20, 2, 1, 0x0}, {12, 20, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData89_HT_SOBEL_X_3X3_08S[] = {{16, 20, 4, 0, 0x2211}, {16, 20, 2, 1, 0x0}, {16, 20, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData90_HT_SOBEL_X_3X3_08S[] = {{4, 22, 4, 0, 0x2211}, {4, 22, 2, 1, 0x0}, {4, 22, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData91_HT_SOBEL_X_3X3_08S[] = {{8, 22, 4, 0, 0x2211}, {8, 22, 2, 1, 0x0}, {8, 22, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData92_HT_SOBEL_X_3X3_08S[] = {{12, 22, 4, 0, 0x2211}, {12, 22, 2, 1, 0x0}, {12, 22, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData93_HT_SOBEL_X_3X3_08S[] = {{4, 24, 4, 0, 0x2211}, {4, 24, 2, 1, 0x0}, {4, 24, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData94_HT_SOBEL_X_3X3_08S[] = {{8, 24, 4, 0, 0x2211}, {8, 24, 2, 1, 0x0}, {8, 24, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData95_HT_SOBEL_X_3X3_08S[] = {{12, 24, 4, 0, 0x2211}, {12, 24, 2, 1, 0x0}, {12, 24, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData96_HT_SOBEL_X_3X3_08S[] = {{4, 26, 4, 0, 0x2211}, {4, 26, 2, 1, 0x0}, {4, 26, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData97_HT_SOBEL_X_3X3_08S[] = {{8, 26, 4, 0, 0x2211}, {8, 26, 2, 1, 0x0}, {8, 26, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData98_HT_SOBEL_X_3X3_08S[] = {{12, 26, 4, 0, 0x2211}, {12, 26, 2, 1, 0x0}, {12, 26, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData99_HT_SOBEL_X_3X3_08S[] = {{4, 28, 4, 0, 0x2211}, {4, 28, 2, 1, 0x0}, {4, 28, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData100_HT_SOBEL_X_3X3_08S[] = {{8, 28, 4, 0, 0x2211}, {8, 28, 2, 1, 0x0}, {8, 28, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData101_HT_SOBEL_X_3X3_08S[] = {{12, 28, 4, 0, 0x2211}, {12, 28, 2, 1, 0x0}, {12, 28, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData102_HT_SOBEL_X_3X3_08S[] = {{4, 30, 4, 0, 0x2211}, {4, 30, 2, 1, 0x0}, {4, 30, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData103_HT_SOBEL_X_3X3_08S[] = {{8, 30, 4, 0, 0x2211}, {8, 30, 2, 1, 0x0}, {8, 30, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData104_HT_SOBEL_X_3X3_08S[] = {{4, 32, 4, 0, 0x2211}, {4, 32, 2, 1, 0x0}, {4, 32, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData105_HT_SOBEL_X_3X3_08S[] = {{8, 32, 4, 0, 0x2211}, {8, 32, 2, 1, 0x0}, {8, 32, 2, 1, 0x0}};

static acf_scenario_kernel_data gScenarioKernelData0_HT_SOBEL_X_3X3_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData1_HT_SOBEL_X_3X3_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData2_HT_SOBEL_X_3X3_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData3_HT_SOBEL_X_3X3_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData4_HT_SOBEL_X_3X3_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData5_HT_SOBEL_X_3X3_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData6_HT_SOBEL_X_3X3_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData7_HT_SOBEL_X_3X3_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData8_HT_SOBEL_X_3X3_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData9_HT_SOBEL_X_3X3_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData10_HT_SOBEL_X_3X3_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData11_HT_SOBEL_X_3X3_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData12_HT_SOBEL_X_3X3_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData13_HT_SOBEL_X_3X3_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData14_HT_SOBEL_X_3X3_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData15_HT_SOBEL_X_3X3_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData16_HT_SOBEL_X_3X3_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData17_HT_SOBEL_X_3X3_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData18_HT_SOBEL_X_3X3_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData19_HT_SOBEL_X_3X3_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData20_HT_SOBEL_X_3X3_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData21_HT_SOBEL_X_3X3_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData22_HT_SOBEL_X_3X3_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData23_HT_SOBEL_X_3X3_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData24_HT_SOBEL_X_3X3_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData25_HT_SOBEL_X_3X3_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData26_HT_SOBEL_X_3X3_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData27_HT_SOBEL_X_3X3_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData28_HT_SOBEL_X_3X3_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData29_HT_SOBEL_X_3X3_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData30_HT_SOBEL_X_3X3_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData31_HT_SOBEL_X_3X3_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData32_HT_SOBEL_X_3X3_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData33_HT_SOBEL_X_3X3_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData34_HT_SOBEL_X_3X3_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData35_HT_SOBEL_X_3X3_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData36_HT_SOBEL_X_3X3_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData37_HT_SOBEL_X_3X3_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData38_HT_SOBEL_X_3X3_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData39_HT_SOBEL_X_3X3_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData40_HT_SOBEL_X_3X3_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData41_HT_SOBEL_X_3X3_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData42_HT_SOBEL_X_3X3_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData43_HT_SOBEL_X_3X3_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData44_HT_SOBEL_X_3X3_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData45_HT_SOBEL_X_3X3_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData46_HT_SOBEL_X_3X3_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData47_HT_SOBEL_X_3X3_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData48_HT_SOBEL_X_3X3_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData49_HT_SOBEL_X_3X3_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData50_HT_SOBEL_X_3X3_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData51_HT_SOBEL_X_3X3_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData52_HT_SOBEL_X_3X3_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData53_HT_SOBEL_X_3X3_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData54_HT_SOBEL_X_3X3_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData55_HT_SOBEL_X_3X3_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData56_HT_SOBEL_X_3X3_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData57_HT_SOBEL_X_3X3_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData58_HT_SOBEL_X_3X3_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData59_HT_SOBEL_X_3X3_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData60_HT_SOBEL_X_3X3_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData61_HT_SOBEL_X_3X3_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData62_HT_SOBEL_X_3X3_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData63_HT_SOBEL_X_3X3_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData64_HT_SOBEL_X_3X3_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData65_HT_SOBEL_X_3X3_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData66_HT_SOBEL_X_3X3_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData67_HT_SOBEL_X_3X3_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData68_HT_SOBEL_X_3X3_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData69_HT_SOBEL_X_3X3_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData70_HT_SOBEL_X_3X3_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData71_HT_SOBEL_X_3X3_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData72_HT_SOBEL_X_3X3_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData73_HT_SOBEL_X_3X3_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData74_HT_SOBEL_X_3X3_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData75_HT_SOBEL_X_3X3_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData76_HT_SOBEL_X_3X3_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData77_HT_SOBEL_X_3X3_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData78_HT_SOBEL_X_3X3_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData79_HT_SOBEL_X_3X3_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData80_HT_SOBEL_X_3X3_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData81_HT_SOBEL_X_3X3_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData82_HT_SOBEL_X_3X3_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData83_HT_SOBEL_X_3X3_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData84_HT_SOBEL_X_3X3_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData85_HT_SOBEL_X_3X3_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData86_HT_SOBEL_X_3X3_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData87_HT_SOBEL_X_3X3_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData88_HT_SOBEL_X_3X3_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData89_HT_SOBEL_X_3X3_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData90_HT_SOBEL_X_3X3_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData91_HT_SOBEL_X_3X3_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData92_HT_SOBEL_X_3X3_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData93_HT_SOBEL_X_3X3_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData94_HT_SOBEL_X_3X3_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData95_HT_SOBEL_X_3X3_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData96_HT_SOBEL_X_3X3_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData97_HT_SOBEL_X_3X3_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData98_HT_SOBEL_X_3X3_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData99_HT_SOBEL_X_3X3_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData100_HT_SOBEL_X_3X3_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData101_HT_SOBEL_X_3X3_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData102_HT_SOBEL_X_3X3_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData103_HT_SOBEL_X_3X3_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData104_HT_SOBEL_X_3X3_08S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData105_HT_SOBEL_X_3X3_08S[] = {{1}};

static acf_scenario gScenarioArray_HT_SOBEL_X_3X3_08S[] = {
{1, 1, 72, 0, 1, gScenarioBufferData0_HT_SOBEL_X_3X3_08S, 30, gScenarioKernelData0_HT_SOBEL_X_3X3_08S, 2},
{2, 1, 120, 0, 1, gScenarioBufferData1_HT_SOBEL_X_3X3_08S, 30, gScenarioKernelData1_HT_SOBEL_X_3X3_08S, 2},
{3, 1, 168, 0, 1, gScenarioBufferData2_HT_SOBEL_X_3X3_08S, 30, gScenarioKernelData2_HT_SOBEL_X_3X3_08S, 2},
{4, 1, 216, 0, 1, gScenarioBufferData3_HT_SOBEL_X_3X3_08S, 30, gScenarioKernelData3_HT_SOBEL_X_3X3_08S, 2},
{5, 1, 264, 0, 1, gScenarioBufferData4_HT_SOBEL_X_3X3_08S, 30, gScenarioKernelData4_HT_SOBEL_X_3X3_08S, 2},
{6, 1, 312, 0, 1, gScenarioBufferData5_HT_SOBEL_X_3X3_08S, 30, gScenarioKernelData5_HT_SOBEL_X_3X3_08S, 2},
{7, 1, 360, 0, 1, gScenarioBufferData6_HT_SOBEL_X_3X3_08S, 30, gScenarioKernelData6_HT_SOBEL_X_3X3_08S, 2},
{8, 1, 408, 0, 1, gScenarioBufferData7_HT_SOBEL_X_3X3_08S, 30, gScenarioKernelData7_HT_SOBEL_X_3X3_08S, 2},
{10, 1, 504, 0, 1, gScenarioBufferData8_HT_SOBEL_X_3X3_08S, 30, gScenarioKernelData8_HT_SOBEL_X_3X3_08S, 2},
{12, 1, 600, 0, 1, gScenarioBufferData9_HT_SOBEL_X_3X3_08S, 30, gScenarioKernelData9_HT_SOBEL_X_3X3_08S, 2},
{14, 1, 696, 0, 1, gScenarioBufferData10_HT_SOBEL_X_3X3_08S, 30, gScenarioKernelData10_HT_SOBEL_X_3X3_08S, 2},
{16, 1, 792, 0, 1, gScenarioBufferData11_HT_SOBEL_X_3X3_08S, 30, gScenarioKernelData11_HT_SOBEL_X_3X3_08S, 2},
{1, 2, 128, 0, 1, gScenarioBufferData12_HT_SOBEL_X_3X3_08S, 30, gScenarioKernelData12_HT_SOBEL_X_3X3_08S, 2},
{2, 2, 216, 0, 1, gScenarioBufferData13_HT_SOBEL_X_3X3_08S, 30, gScenarioKernelData13_HT_SOBEL_X_3X3_08S, 2},
{3, 2, 304, 0, 1, gScenarioBufferData14_HT_SOBEL_X_3X3_08S, 30, gScenarioKernelData14_HT_SOBEL_X_3X3_08S, 2},
{4, 2, 392, 0, 1, gScenarioBufferData15_HT_SOBEL_X_3X3_08S, 30, gScenarioKernelData15_HT_SOBEL_X_3X3_08S, 2},
{5, 2, 480, 0, 1, gScenarioBufferData16_HT_SOBEL_X_3X3_08S, 30, gScenarioKernelData16_HT_SOBEL_X_3X3_08S, 2},
{6, 2, 568, 0, 1, gScenarioBufferData17_HT_SOBEL_X_3X3_08S, 30, gScenarioKernelData17_HT_SOBEL_X_3X3_08S, 2},
{7, 2, 656, 0, 1, gScenarioBufferData18_HT_SOBEL_X_3X3_08S, 30, gScenarioKernelData18_HT_SOBEL_X_3X3_08S, 2},
{8, 2, 744, 0, 1, gScenarioBufferData19_HT_SOBEL_X_3X3_08S, 30, gScenarioKernelData19_HT_SOBEL_X_3X3_08S, 2},
{10, 2, 920, 0, 1, gScenarioBufferData20_HT_SOBEL_X_3X3_08S, 30, gScenarioKernelData20_HT_SOBEL_X_3X3_08S, 2},
{12, 2, 1096, 0, 1, gScenarioBufferData21_HT_SOBEL_X_3X3_08S, 30, gScenarioKernelData21_HT_SOBEL_X_3X3_08S, 2},
{14, 2, 1272, 0, 1, gScenarioBufferData22_HT_SOBEL_X_3X3_08S, 30, gScenarioKernelData22_HT_SOBEL_X_3X3_08S, 2},
{16, 2, 1448, 0, 1, gScenarioBufferData23_HT_SOBEL_X_3X3_08S, 30, gScenarioKernelData23_HT_SOBEL_X_3X3_08S, 2},
{1, 4, 240, 0, 1, gScenarioBufferData24_HT_SOBEL_X_3X3_08S, 30, gScenarioKernelData24_HT_SOBEL_X_3X3_08S, 2},
{2, 4, 408, 0, 1, gScenarioBufferData25_HT_SOBEL_X_3X3_08S, 30, gScenarioKernelData25_HT_SOBEL_X_3X3_08S, 2},
{3, 4, 576, 0, 1, gScenarioBufferData26_HT_SOBEL_X_3X3_08S, 30, gScenarioKernelData26_HT_SOBEL_X_3X3_08S, 2},
{4, 4, 744, 0, 1, gScenarioBufferData27_HT_SOBEL_X_3X3_08S, 30, gScenarioKernelData27_HT_SOBEL_X_3X3_08S, 2},
{5, 4, 912, 0, 1, gScenarioBufferData28_HT_SOBEL_X_3X3_08S, 30, gScenarioKernelData28_HT_SOBEL_X_3X3_08S, 2},
{6, 4, 1080, 0, 1, gScenarioBufferData29_HT_SOBEL_X_3X3_08S, 30, gScenarioKernelData29_HT_SOBEL_X_3X3_08S, 2},
{7, 4, 1248, 0, 1, gScenarioBufferData30_HT_SOBEL_X_3X3_08S, 30, gScenarioKernelData30_HT_SOBEL_X_3X3_08S, 2},
{8, 4, 1416, 0, 1, gScenarioBufferData31_HT_SOBEL_X_3X3_08S, 30, gScenarioKernelData31_HT_SOBEL_X_3X3_08S, 2},
{10, 4, 1752, 0, 1, gScenarioBufferData32_HT_SOBEL_X_3X3_08S, 30, gScenarioKernelData32_HT_SOBEL_X_3X3_08S, 2},
{12, 4, 2088, 0, 1, gScenarioBufferData33_HT_SOBEL_X_3X3_08S, 30, gScenarioKernelData33_HT_SOBEL_X_3X3_08S, 2},
{14, 4, 2424, 0, 1, gScenarioBufferData34_HT_SOBEL_X_3X3_08S, 30, gScenarioKernelData34_HT_SOBEL_X_3X3_08S, 2},
{16, 4, 2760, 0, 1, gScenarioBufferData35_HT_SOBEL_X_3X3_08S, 30, gScenarioKernelData35_HT_SOBEL_X_3X3_08S, 2},
{1, 6, 352, 0, 1, gScenarioBufferData36_HT_SOBEL_X_3X3_08S, 30, gScenarioKernelData36_HT_SOBEL_X_3X3_08S, 2},
{2, 6, 600, 0, 1, gScenarioBufferData37_HT_SOBEL_X_3X3_08S, 30, gScenarioKernelData37_HT_SOBEL_X_3X3_08S, 2},
{3, 6, 848, 0, 1, gScenarioBufferData38_HT_SOBEL_X_3X3_08S, 30, gScenarioKernelData38_HT_SOBEL_X_3X3_08S, 2},
{4, 6, 1096, 0, 1, gScenarioBufferData39_HT_SOBEL_X_3X3_08S, 30, gScenarioKernelData39_HT_SOBEL_X_3X3_08S, 2},
{5, 6, 1344, 0, 1, gScenarioBufferData40_HT_SOBEL_X_3X3_08S, 30, gScenarioKernelData40_HT_SOBEL_X_3X3_08S, 2},
{6, 6, 1592, 0, 1, gScenarioBufferData41_HT_SOBEL_X_3X3_08S, 30, gScenarioKernelData41_HT_SOBEL_X_3X3_08S, 2},
{7, 6, 1840, 0, 1, gScenarioBufferData42_HT_SOBEL_X_3X3_08S, 30, gScenarioKernelData42_HT_SOBEL_X_3X3_08S, 2},
{8, 6, 2088, 0, 1, gScenarioBufferData43_HT_SOBEL_X_3X3_08S, 30, gScenarioKernelData43_HT_SOBEL_X_3X3_08S, 2},
{10, 6, 2584, 0, 1, gScenarioBufferData44_HT_SOBEL_X_3X3_08S, 30, gScenarioKernelData44_HT_SOBEL_X_3X3_08S, 2},
{12, 6, 3080, 0, 1, gScenarioBufferData45_HT_SOBEL_X_3X3_08S, 30, gScenarioKernelData45_HT_SOBEL_X_3X3_08S, 2},
{14, 6, 3576, 0, 1, gScenarioBufferData46_HT_SOBEL_X_3X3_08S, 30, gScenarioKernelData46_HT_SOBEL_X_3X3_08S, 2},
{1, 8, 464, 0, 1, gScenarioBufferData47_HT_SOBEL_X_3X3_08S, 30, gScenarioKernelData47_HT_SOBEL_X_3X3_08S, 2},
{2, 8, 792, 0, 1, gScenarioBufferData48_HT_SOBEL_X_3X3_08S, 30, gScenarioKernelData48_HT_SOBEL_X_3X3_08S, 2},
{3, 8, 1120, 0, 1, gScenarioBufferData49_HT_SOBEL_X_3X3_08S, 30, gScenarioKernelData49_HT_SOBEL_X_3X3_08S, 2},
{4, 8, 1448, 0, 1, gScenarioBufferData50_HT_SOBEL_X_3X3_08S, 30, gScenarioKernelData50_HT_SOBEL_X_3X3_08S, 2},
{5, 8, 1776, 0, 1, gScenarioBufferData51_HT_SOBEL_X_3X3_08S, 30, gScenarioKernelData51_HT_SOBEL_X_3X3_08S, 2},
{6, 8, 2104, 0, 1, gScenarioBufferData52_HT_SOBEL_X_3X3_08S, 30, gScenarioKernelData52_HT_SOBEL_X_3X3_08S, 2},
{7, 8, 2432, 0, 1, gScenarioBufferData53_HT_SOBEL_X_3X3_08S, 30, gScenarioKernelData53_HT_SOBEL_X_3X3_08S, 2},
{8, 8, 2760, 0, 1, gScenarioBufferData54_HT_SOBEL_X_3X3_08S, 30, gScenarioKernelData54_HT_SOBEL_X_3X3_08S, 2},
{10, 8, 3416, 0, 1, gScenarioBufferData55_HT_SOBEL_X_3X3_08S, 30, gScenarioKernelData55_HT_SOBEL_X_3X3_08S, 2},
{1, 10, 576, 0, 1, gScenarioBufferData56_HT_SOBEL_X_3X3_08S, 30, gScenarioKernelData56_HT_SOBEL_X_3X3_08S, 2},
{2, 10, 984, 0, 1, gScenarioBufferData57_HT_SOBEL_X_3X3_08S, 30, gScenarioKernelData57_HT_SOBEL_X_3X3_08S, 2},
{3, 10, 1392, 0, 1, gScenarioBufferData58_HT_SOBEL_X_3X3_08S, 30, gScenarioKernelData58_HT_SOBEL_X_3X3_08S, 2},
{4, 10, 1800, 0, 1, gScenarioBufferData59_HT_SOBEL_X_3X3_08S, 30, gScenarioKernelData59_HT_SOBEL_X_3X3_08S, 2},
{5, 10, 2208, 0, 1, gScenarioBufferData60_HT_SOBEL_X_3X3_08S, 30, gScenarioKernelData60_HT_SOBEL_X_3X3_08S, 2},
{6, 10, 2616, 0, 1, gScenarioBufferData61_HT_SOBEL_X_3X3_08S, 30, gScenarioKernelData61_HT_SOBEL_X_3X3_08S, 2},
{7, 10, 3024, 0, 1, gScenarioBufferData62_HT_SOBEL_X_3X3_08S, 30, gScenarioKernelData62_HT_SOBEL_X_3X3_08S, 2},
{8, 10, 3432, 0, 1, gScenarioBufferData63_HT_SOBEL_X_3X3_08S, 30, gScenarioKernelData63_HT_SOBEL_X_3X3_08S, 2},
{1, 12, 688, 0, 1, gScenarioBufferData64_HT_SOBEL_X_3X3_08S, 30, gScenarioKernelData64_HT_SOBEL_X_3X3_08S, 2},
{2, 12, 1176, 0, 1, gScenarioBufferData65_HT_SOBEL_X_3X3_08S, 30, gScenarioKernelData65_HT_SOBEL_X_3X3_08S, 2},
{3, 12, 1664, 0, 1, gScenarioBufferData66_HT_SOBEL_X_3X3_08S, 30, gScenarioKernelData66_HT_SOBEL_X_3X3_08S, 2},
{4, 12, 2152, 0, 1, gScenarioBufferData67_HT_SOBEL_X_3X3_08S, 30, gScenarioKernelData67_HT_SOBEL_X_3X3_08S, 2},
{5, 12, 2640, 0, 1, gScenarioBufferData68_HT_SOBEL_X_3X3_08S, 30, gScenarioKernelData68_HT_SOBEL_X_3X3_08S, 2},
{6, 12, 3128, 0, 1, gScenarioBufferData69_HT_SOBEL_X_3X3_08S, 30, gScenarioKernelData69_HT_SOBEL_X_3X3_08S, 2},
{7, 12, 3616, 0, 1, gScenarioBufferData70_HT_SOBEL_X_3X3_08S, 30, gScenarioKernelData70_HT_SOBEL_X_3X3_08S, 2},
{1, 14, 800, 0, 1, gScenarioBufferData71_HT_SOBEL_X_3X3_08S, 30, gScenarioKernelData71_HT_SOBEL_X_3X3_08S, 2},
{2, 14, 1368, 0, 1, gScenarioBufferData72_HT_SOBEL_X_3X3_08S, 30, gScenarioKernelData72_HT_SOBEL_X_3X3_08S, 2},
{3, 14, 1936, 0, 1, gScenarioBufferData73_HT_SOBEL_X_3X3_08S, 30, gScenarioKernelData73_HT_SOBEL_X_3X3_08S, 2},
{4, 14, 2504, 0, 1, gScenarioBufferData74_HT_SOBEL_X_3X3_08S, 30, gScenarioKernelData74_HT_SOBEL_X_3X3_08S, 2},
{5, 14, 3072, 0, 1, gScenarioBufferData75_HT_SOBEL_X_3X3_08S, 30, gScenarioKernelData75_HT_SOBEL_X_3X3_08S, 2},
{6, 14, 3640, 0, 1, gScenarioBufferData76_HT_SOBEL_X_3X3_08S, 30, gScenarioKernelData76_HT_SOBEL_X_3X3_08S, 2},
{1, 16, 912, 0, 1, gScenarioBufferData77_HT_SOBEL_X_3X3_08S, 30, gScenarioKernelData77_HT_SOBEL_X_3X3_08S, 2},
{2, 16, 1560, 0, 1, gScenarioBufferData78_HT_SOBEL_X_3X3_08S, 30, gScenarioKernelData78_HT_SOBEL_X_3X3_08S, 2},
{3, 16, 2208, 0, 1, gScenarioBufferData79_HT_SOBEL_X_3X3_08S, 30, gScenarioKernelData79_HT_SOBEL_X_3X3_08S, 2},
{4, 16, 2856, 0, 1, gScenarioBufferData80_HT_SOBEL_X_3X3_08S, 30, gScenarioKernelData80_HT_SOBEL_X_3X3_08S, 2},
{5, 16, 3504, 0, 1, gScenarioBufferData81_HT_SOBEL_X_3X3_08S, 30, gScenarioKernelData81_HT_SOBEL_X_3X3_08S, 2},
{1, 18, 1024, 0, 1, gScenarioBufferData82_HT_SOBEL_X_3X3_08S, 30, gScenarioKernelData82_HT_SOBEL_X_3X3_08S, 2},
{2, 18, 1752, 0, 1, gScenarioBufferData83_HT_SOBEL_X_3X3_08S, 30, gScenarioKernelData83_HT_SOBEL_X_3X3_08S, 2},
{3, 18, 2480, 0, 1, gScenarioBufferData84_HT_SOBEL_X_3X3_08S, 30, gScenarioKernelData84_HT_SOBEL_X_3X3_08S, 2},
{4, 18, 3208, 0, 1, gScenarioBufferData85_HT_SOBEL_X_3X3_08S, 30, gScenarioKernelData85_HT_SOBEL_X_3X3_08S, 2},
{1, 20, 1136, 0, 1, gScenarioBufferData86_HT_SOBEL_X_3X3_08S, 30, gScenarioKernelData86_HT_SOBEL_X_3X3_08S, 2},
{2, 20, 1944, 0, 1, gScenarioBufferData87_HT_SOBEL_X_3X3_08S, 30, gScenarioKernelData87_HT_SOBEL_X_3X3_08S, 2},
{3, 20, 2752, 0, 1, gScenarioBufferData88_HT_SOBEL_X_3X3_08S, 30, gScenarioKernelData88_HT_SOBEL_X_3X3_08S, 2},
{4, 20, 3560, 0, 1, gScenarioBufferData89_HT_SOBEL_X_3X3_08S, 30, gScenarioKernelData89_HT_SOBEL_X_3X3_08S, 2},
{1, 22, 1248, 0, 1, gScenarioBufferData90_HT_SOBEL_X_3X3_08S, 30, gScenarioKernelData90_HT_SOBEL_X_3X3_08S, 2},
{2, 22, 2136, 0, 1, gScenarioBufferData91_HT_SOBEL_X_3X3_08S, 30, gScenarioKernelData91_HT_SOBEL_X_3X3_08S, 2},
{3, 22, 3024, 0, 1, gScenarioBufferData92_HT_SOBEL_X_3X3_08S, 30, gScenarioKernelData92_HT_SOBEL_X_3X3_08S, 2},
{1, 24, 1360, 0, 1, gScenarioBufferData93_HT_SOBEL_X_3X3_08S, 30, gScenarioKernelData93_HT_SOBEL_X_3X3_08S, 2},
{2, 24, 2328, 0, 1, gScenarioBufferData94_HT_SOBEL_X_3X3_08S, 30, gScenarioKernelData94_HT_SOBEL_X_3X3_08S, 2},
{3, 24, 3296, 0, 1, gScenarioBufferData95_HT_SOBEL_X_3X3_08S, 30, gScenarioKernelData95_HT_SOBEL_X_3X3_08S, 2},
{1, 26, 1472, 0, 1, gScenarioBufferData96_HT_SOBEL_X_3X3_08S, 30, gScenarioKernelData96_HT_SOBEL_X_3X3_08S, 2},
{2, 26, 2520, 0, 1, gScenarioBufferData97_HT_SOBEL_X_3X3_08S, 30, gScenarioKernelData97_HT_SOBEL_X_3X3_08S, 2},
{3, 26, 3568, 0, 1, gScenarioBufferData98_HT_SOBEL_X_3X3_08S, 30, gScenarioKernelData98_HT_SOBEL_X_3X3_08S, 2},
{1, 28, 1584, 0, 1, gScenarioBufferData99_HT_SOBEL_X_3X3_08S, 30, gScenarioKernelData99_HT_SOBEL_X_3X3_08S, 2},
{2, 28, 2712, 0, 1, gScenarioBufferData100_HT_SOBEL_X_3X3_08S, 30, gScenarioKernelData100_HT_SOBEL_X_3X3_08S, 2},
{3, 28, 3840, 0, 1, gScenarioBufferData101_HT_SOBEL_X_3X3_08S, 30, gScenarioKernelData101_HT_SOBEL_X_3X3_08S, 2},
{1, 30, 1696, 0, 1, gScenarioBufferData102_HT_SOBEL_X_3X3_08S, 30, gScenarioKernelData102_HT_SOBEL_X_3X3_08S, 2},
{2, 30, 2904, 0, 1, gScenarioBufferData103_HT_SOBEL_X_3X3_08S, 30, gScenarioKernelData103_HT_SOBEL_X_3X3_08S, 2},
{1, 32, 1808, 0, 1, gScenarioBufferData104_HT_SOBEL_X_3X3_08S, 30, gScenarioKernelData104_HT_SOBEL_X_3X3_08S, 2},
{2, 32, 3096, 0, 1, gScenarioBufferData105_HT_SOBEL_X_3X3_08S, 30, gScenarioKernelData105_HT_SOBEL_X_3X3_08S, 2}
};

static acf_scenario_list gScenarioList_HT_SOBEL_X_3X3_08S = {
106, //number of scenarios
gScenarioArray_HT_SOBEL_X_3X3_08S};
//**************************************************************

class HT_SOBEL_X_3X3_08S : public ACF_Process_APU
{
public:
   HT_SOBEL_X_3X3_08S(int32_t apex_id = 0) : ACF_Process_APU(apex_id)
   {} 

   int32_t Initialize()
   {
      int32_t lRetVal = 0;

      if (!Initialized()) //initialization steps that only need to occur once
      {
         SetProcessIdentifier("HT_SOBEL_X_3X3_08S");
         SetApuLoadInfo(HT_SOBEL_X_3X3_08S_LOAD_SEGMENTS,
                        HT_SOBEL_X_3X3_08S_LOAD_PMEM, HT_SOBEL_X_3X3_08S_LOAD_PMEM_SIZE,
                        HT_SOBEL_X_3X3_08S_LOAD_DMEM, HT_SOBEL_X_3X3_08S_LOAD_DMEM_SIZE,
                        0, 0); //assuming _LOAD_CMEM does not exist
         FlagSpatialDep();

         //***NOTE: the order in which the following ports are added is meaningful; do not change!

         AddPort("INPUT_0", ICP_DATATYPE_08U, 1, 1, 4, 1, 0, 0, 0, 0, 0, 0, 0, 0x1010202);
         AddPort("BUFFER_0", ICP_DATATYPE_16S, 1, 1, 4, 1, 1, 0, 0, 0, 0, 0, 1);
         AddPort("OUTPUT_0", ICP_DATATYPE_08S, 1, 1, 4, 1, 1, 0, 0, 0, 0, 0, 2);

         CfgScenarios(&gScenarioList_HT_SOBEL_X_3X3_08S);

         FlagAsInitialized();
      }

      lRetVal = SelectApuConfiguration(mApuCfg, mApexId); //by default mApuCfg = ACF_APU_CFG__APEX0_DEFAULT and mApexId = 0

      return lRetVal;
   }
};

#endif //_ACF_PROCESS_APU_HT_SOBEL_X_3X3_08S
