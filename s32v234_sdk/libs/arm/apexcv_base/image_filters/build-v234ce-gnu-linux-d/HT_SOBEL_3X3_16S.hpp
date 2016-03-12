#ifndef _ACF_PROCESS_APU_HT_SOBEL_3X3_16S
#define _ACF_PROCESS_APU_HT_SOBEL_3X3_16S

#include <acf_process_apu.h>
#include <HT_SOBEL_3X3_16S_APU_LOAD.h> //APU load associated with this process
#include <stdint.h>


//SCENARIO LIST*************************************************
static acf_scenario_buffer_data gScenarioBufferData0_HT_SOBEL_3X3_16S[] = {{4, 1, 7, 0, 0x2222}, {4, 1, 2, 2, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData1_HT_SOBEL_3X3_16S[] = {{8, 1, 7, 0, 0x2222}, {8, 1, 2, 2, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData2_HT_SOBEL_3X3_16S[] = {{12, 1, 7, 0, 0x2222}, {12, 1, 2, 2, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData3_HT_SOBEL_3X3_16S[] = {{16, 1, 7, 0, 0x2222}, {16, 1, 2, 2, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData4_HT_SOBEL_3X3_16S[] = {{20, 1, 7, 0, 0x2222}, {20, 1, 2, 2, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData5_HT_SOBEL_3X3_16S[] = {{24, 1, 7, 0, 0x2222}, {24, 1, 2, 2, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData6_HT_SOBEL_3X3_16S[] = {{28, 1, 7, 0, 0x2222}, {28, 1, 2, 2, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData7_HT_SOBEL_3X3_16S[] = {{32, 1, 7, 0, 0x2222}, {32, 1, 2, 2, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData8_HT_SOBEL_3X3_16S[] = {{40, 1, 7, 0, 0x2222}, {40, 1, 2, 2, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData9_HT_SOBEL_3X3_16S[] = {{48, 1, 7, 0, 0x2222}, {48, 1, 2, 2, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData10_HT_SOBEL_3X3_16S[] = {{56, 1, 7, 0, 0x2222}, {56, 1, 2, 2, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData11_HT_SOBEL_3X3_16S[] = {{64, 1, 7, 0, 0x2222}, {64, 1, 2, 2, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData12_HT_SOBEL_3X3_16S[] = {{4, 2, 4, 0, 0x2222}, {4, 2, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData13_HT_SOBEL_3X3_16S[] = {{8, 2, 4, 0, 0x2222}, {8, 2, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData14_HT_SOBEL_3X3_16S[] = {{12, 2, 4, 0, 0x2222}, {12, 2, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData15_HT_SOBEL_3X3_16S[] = {{16, 2, 4, 0, 0x2222}, {16, 2, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData16_HT_SOBEL_3X3_16S[] = {{20, 2, 4, 0, 0x2222}, {20, 2, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData17_HT_SOBEL_3X3_16S[] = {{24, 2, 4, 0, 0x2222}, {24, 2, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData18_HT_SOBEL_3X3_16S[] = {{28, 2, 4, 0, 0x2222}, {28, 2, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData19_HT_SOBEL_3X3_16S[] = {{32, 2, 4, 0, 0x2222}, {32, 2, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData20_HT_SOBEL_3X3_16S[] = {{40, 2, 4, 0, 0x2222}, {40, 2, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData21_HT_SOBEL_3X3_16S[] = {{48, 2, 4, 0, 0x2222}, {48, 2, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData22_HT_SOBEL_3X3_16S[] = {{56, 2, 4, 0, 0x2222}, {56, 2, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData23_HT_SOBEL_3X3_16S[] = {{64, 2, 4, 0, 0x2222}, {64, 2, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData24_HT_SOBEL_3X3_16S[] = {{4, 4, 4, 0, 0x2222}, {4, 4, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData25_HT_SOBEL_3X3_16S[] = {{8, 4, 4, 0, 0x2222}, {8, 4, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData26_HT_SOBEL_3X3_16S[] = {{12, 4, 4, 0, 0x2222}, {12, 4, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData27_HT_SOBEL_3X3_16S[] = {{16, 4, 4, 0, 0x2222}, {16, 4, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData28_HT_SOBEL_3X3_16S[] = {{20, 4, 4, 0, 0x2222}, {20, 4, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData29_HT_SOBEL_3X3_16S[] = {{24, 4, 4, 0, 0x2222}, {24, 4, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData30_HT_SOBEL_3X3_16S[] = {{28, 4, 4, 0, 0x2222}, {28, 4, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData31_HT_SOBEL_3X3_16S[] = {{32, 4, 4, 0, 0x2222}, {32, 4, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData32_HT_SOBEL_3X3_16S[] = {{40, 4, 4, 0, 0x2222}, {40, 4, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData33_HT_SOBEL_3X3_16S[] = {{48, 4, 4, 0, 0x2222}, {48, 4, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData34_HT_SOBEL_3X3_16S[] = {{56, 4, 4, 0, 0x2222}, {56, 4, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData35_HT_SOBEL_3X3_16S[] = {{64, 4, 4, 0, 0x2222}, {64, 4, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData36_HT_SOBEL_3X3_16S[] = {{4, 6, 4, 0, 0x2222}, {4, 6, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData37_HT_SOBEL_3X3_16S[] = {{8, 6, 4, 0, 0x2222}, {8, 6, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData38_HT_SOBEL_3X3_16S[] = {{12, 6, 4, 0, 0x2222}, {12, 6, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData39_HT_SOBEL_3X3_16S[] = {{16, 6, 4, 0, 0x2222}, {16, 6, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData40_HT_SOBEL_3X3_16S[] = {{20, 6, 4, 0, 0x2222}, {20, 6, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData41_HT_SOBEL_3X3_16S[] = {{24, 6, 4, 0, 0x2222}, {24, 6, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData42_HT_SOBEL_3X3_16S[] = {{28, 6, 4, 0, 0x2222}, {28, 6, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData43_HT_SOBEL_3X3_16S[] = {{32, 6, 4, 0, 0x2222}, {32, 6, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData44_HT_SOBEL_3X3_16S[] = {{40, 6, 4, 0, 0x2222}, {40, 6, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData45_HT_SOBEL_3X3_16S[] = {{48, 6, 4, 0, 0x2222}, {48, 6, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData46_HT_SOBEL_3X3_16S[] = {{56, 6, 4, 0, 0x2222}, {56, 6, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData47_HT_SOBEL_3X3_16S[] = {{64, 6, 4, 0, 0x2222}, {64, 6, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData48_HT_SOBEL_3X3_16S[] = {{4, 8, 4, 0, 0x2222}, {4, 8, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData49_HT_SOBEL_3X3_16S[] = {{8, 8, 4, 0, 0x2222}, {8, 8, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData50_HT_SOBEL_3X3_16S[] = {{12, 8, 4, 0, 0x2222}, {12, 8, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData51_HT_SOBEL_3X3_16S[] = {{16, 8, 4, 0, 0x2222}, {16, 8, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData52_HT_SOBEL_3X3_16S[] = {{20, 8, 4, 0, 0x2222}, {20, 8, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData53_HT_SOBEL_3X3_16S[] = {{24, 8, 4, 0, 0x2222}, {24, 8, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData54_HT_SOBEL_3X3_16S[] = {{28, 8, 4, 0, 0x2222}, {28, 8, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData55_HT_SOBEL_3X3_16S[] = {{32, 8, 4, 0, 0x2222}, {32, 8, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData56_HT_SOBEL_3X3_16S[] = {{40, 8, 4, 0, 0x2222}, {40, 8, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData57_HT_SOBEL_3X3_16S[] = {{48, 8, 4, 0, 0x2222}, {48, 8, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData58_HT_SOBEL_3X3_16S[] = {{4, 10, 4, 0, 0x2222}, {4, 10, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData59_HT_SOBEL_3X3_16S[] = {{8, 10, 4, 0, 0x2222}, {8, 10, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData60_HT_SOBEL_3X3_16S[] = {{12, 10, 4, 0, 0x2222}, {12, 10, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData61_HT_SOBEL_3X3_16S[] = {{16, 10, 4, 0, 0x2222}, {16, 10, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData62_HT_SOBEL_3X3_16S[] = {{20, 10, 4, 0, 0x2222}, {20, 10, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData63_HT_SOBEL_3X3_16S[] = {{24, 10, 4, 0, 0x2222}, {24, 10, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData64_HT_SOBEL_3X3_16S[] = {{28, 10, 4, 0, 0x2222}, {28, 10, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData65_HT_SOBEL_3X3_16S[] = {{32, 10, 4, 0, 0x2222}, {32, 10, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData66_HT_SOBEL_3X3_16S[] = {{40, 10, 4, 0, 0x2222}, {40, 10, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData67_HT_SOBEL_3X3_16S[] = {{4, 12, 4, 0, 0x2222}, {4, 12, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData68_HT_SOBEL_3X3_16S[] = {{8, 12, 4, 0, 0x2222}, {8, 12, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData69_HT_SOBEL_3X3_16S[] = {{12, 12, 4, 0, 0x2222}, {12, 12, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData70_HT_SOBEL_3X3_16S[] = {{16, 12, 4, 0, 0x2222}, {16, 12, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData71_HT_SOBEL_3X3_16S[] = {{20, 12, 4, 0, 0x2222}, {20, 12, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData72_HT_SOBEL_3X3_16S[] = {{24, 12, 4, 0, 0x2222}, {24, 12, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData73_HT_SOBEL_3X3_16S[] = {{28, 12, 4, 0, 0x2222}, {28, 12, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData74_HT_SOBEL_3X3_16S[] = {{32, 12, 4, 0, 0x2222}, {32, 12, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData75_HT_SOBEL_3X3_16S[] = {{4, 14, 4, 0, 0x2222}, {4, 14, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData76_HT_SOBEL_3X3_16S[] = {{8, 14, 4, 0, 0x2222}, {8, 14, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData77_HT_SOBEL_3X3_16S[] = {{12, 14, 4, 0, 0x2222}, {12, 14, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData78_HT_SOBEL_3X3_16S[] = {{16, 14, 4, 0, 0x2222}, {16, 14, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData79_HT_SOBEL_3X3_16S[] = {{20, 14, 4, 0, 0x2222}, {20, 14, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData80_HT_SOBEL_3X3_16S[] = {{24, 14, 4, 0, 0x2222}, {24, 14, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData81_HT_SOBEL_3X3_16S[] = {{28, 14, 4, 0, 0x2222}, {28, 14, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData82_HT_SOBEL_3X3_16S[] = {{4, 16, 4, 0, 0x2222}, {4, 16, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData83_HT_SOBEL_3X3_16S[] = {{8, 16, 4, 0, 0x2222}, {8, 16, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData84_HT_SOBEL_3X3_16S[] = {{12, 16, 4, 0, 0x2222}, {12, 16, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData85_HT_SOBEL_3X3_16S[] = {{16, 16, 4, 0, 0x2222}, {16, 16, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData86_HT_SOBEL_3X3_16S[] = {{20, 16, 4, 0, 0x2222}, {20, 16, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData87_HT_SOBEL_3X3_16S[] = {{24, 16, 4, 0, 0x2222}, {24, 16, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData88_HT_SOBEL_3X3_16S[] = {{4, 18, 4, 0, 0x2222}, {4, 18, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData89_HT_SOBEL_3X3_16S[] = {{8, 18, 4, 0, 0x2222}, {8, 18, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData90_HT_SOBEL_3X3_16S[] = {{12, 18, 4, 0, 0x2222}, {12, 18, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData91_HT_SOBEL_3X3_16S[] = {{16, 18, 4, 0, 0x2222}, {16, 18, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData92_HT_SOBEL_3X3_16S[] = {{20, 18, 4, 0, 0x2222}, {20, 18, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData93_HT_SOBEL_3X3_16S[] = {{4, 20, 4, 0, 0x2222}, {4, 20, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData94_HT_SOBEL_3X3_16S[] = {{8, 20, 4, 0, 0x2222}, {8, 20, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData95_HT_SOBEL_3X3_16S[] = {{12, 20, 4, 0, 0x2222}, {12, 20, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData96_HT_SOBEL_3X3_16S[] = {{16, 20, 4, 0, 0x2222}, {16, 20, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData97_HT_SOBEL_3X3_16S[] = {{20, 20, 4, 0, 0x2222}, {20, 20, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData98_HT_SOBEL_3X3_16S[] = {{4, 22, 4, 0, 0x2222}, {4, 22, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData99_HT_SOBEL_3X3_16S[] = {{8, 22, 4, 0, 0x2222}, {8, 22, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData100_HT_SOBEL_3X3_16S[] = {{12, 22, 4, 0, 0x2222}, {12, 22, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData101_HT_SOBEL_3X3_16S[] = {{16, 22, 4, 0, 0x2222}, {16, 22, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData102_HT_SOBEL_3X3_16S[] = {{4, 24, 4, 0, 0x2222}, {4, 24, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData103_HT_SOBEL_3X3_16S[] = {{8, 24, 4, 0, 0x2222}, {8, 24, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData104_HT_SOBEL_3X3_16S[] = {{12, 24, 4, 0, 0x2222}, {12, 24, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData105_HT_SOBEL_3X3_16S[] = {{16, 24, 4, 0, 0x2222}, {16, 24, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData106_HT_SOBEL_3X3_16S[] = {{4, 26, 4, 0, 0x2222}, {4, 26, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData107_HT_SOBEL_3X3_16S[] = {{8, 26, 4, 0, 0x2222}, {8, 26, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData108_HT_SOBEL_3X3_16S[] = {{12, 26, 4, 0, 0x2222}, {12, 26, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData109_HT_SOBEL_3X3_16S[] = {{16, 26, 4, 0, 0x2222}, {16, 26, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData110_HT_SOBEL_3X3_16S[] = {{4, 28, 4, 0, 0x2222}, {4, 28, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData111_HT_SOBEL_3X3_16S[] = {{8, 28, 4, 0, 0x2222}, {8, 28, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData112_HT_SOBEL_3X3_16S[] = {{12, 28, 4, 0, 0x2222}, {12, 28, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData113_HT_SOBEL_3X3_16S[] = {{4, 30, 4, 0, 0x2222}, {4, 30, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData114_HT_SOBEL_3X3_16S[] = {{8, 30, 4, 0, 0x2222}, {8, 30, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData115_HT_SOBEL_3X3_16S[] = {{12, 30, 4, 0, 0x2222}, {12, 30, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData116_HT_SOBEL_3X3_16S[] = {{4, 32, 4, 0, 0x2222}, {4, 32, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData117_HT_SOBEL_3X3_16S[] = {{8, 32, 4, 0, 0x2222}, {8, 32, 2, 1, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData118_HT_SOBEL_3X3_16S[] = {{12, 32, 4, 0, 0x2222}, {12, 32, 2, 1, 0x0}};

static acf_scenario_kernel_data gScenarioKernelData0_HT_SOBEL_3X3_16S[] = {{2}};
static acf_scenario_kernel_data gScenarioKernelData1_HT_SOBEL_3X3_16S[] = {{2}};
static acf_scenario_kernel_data gScenarioKernelData2_HT_SOBEL_3X3_16S[] = {{2}};
static acf_scenario_kernel_data gScenarioKernelData3_HT_SOBEL_3X3_16S[] = {{2}};
static acf_scenario_kernel_data gScenarioKernelData4_HT_SOBEL_3X3_16S[] = {{2}};
static acf_scenario_kernel_data gScenarioKernelData5_HT_SOBEL_3X3_16S[] = {{2}};
static acf_scenario_kernel_data gScenarioKernelData6_HT_SOBEL_3X3_16S[] = {{2}};
static acf_scenario_kernel_data gScenarioKernelData7_HT_SOBEL_3X3_16S[] = {{2}};
static acf_scenario_kernel_data gScenarioKernelData8_HT_SOBEL_3X3_16S[] = {{2}};
static acf_scenario_kernel_data gScenarioKernelData9_HT_SOBEL_3X3_16S[] = {{2}};
static acf_scenario_kernel_data gScenarioKernelData10_HT_SOBEL_3X3_16S[] = {{2}};
static acf_scenario_kernel_data gScenarioKernelData11_HT_SOBEL_3X3_16S[] = {{2}};
static acf_scenario_kernel_data gScenarioKernelData12_HT_SOBEL_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData13_HT_SOBEL_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData14_HT_SOBEL_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData15_HT_SOBEL_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData16_HT_SOBEL_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData17_HT_SOBEL_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData18_HT_SOBEL_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData19_HT_SOBEL_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData20_HT_SOBEL_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData21_HT_SOBEL_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData22_HT_SOBEL_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData23_HT_SOBEL_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData24_HT_SOBEL_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData25_HT_SOBEL_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData26_HT_SOBEL_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData27_HT_SOBEL_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData28_HT_SOBEL_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData29_HT_SOBEL_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData30_HT_SOBEL_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData31_HT_SOBEL_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData32_HT_SOBEL_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData33_HT_SOBEL_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData34_HT_SOBEL_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData35_HT_SOBEL_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData36_HT_SOBEL_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData37_HT_SOBEL_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData38_HT_SOBEL_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData39_HT_SOBEL_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData40_HT_SOBEL_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData41_HT_SOBEL_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData42_HT_SOBEL_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData43_HT_SOBEL_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData44_HT_SOBEL_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData45_HT_SOBEL_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData46_HT_SOBEL_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData47_HT_SOBEL_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData48_HT_SOBEL_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData49_HT_SOBEL_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData50_HT_SOBEL_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData51_HT_SOBEL_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData52_HT_SOBEL_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData53_HT_SOBEL_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData54_HT_SOBEL_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData55_HT_SOBEL_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData56_HT_SOBEL_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData57_HT_SOBEL_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData58_HT_SOBEL_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData59_HT_SOBEL_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData60_HT_SOBEL_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData61_HT_SOBEL_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData62_HT_SOBEL_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData63_HT_SOBEL_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData64_HT_SOBEL_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData65_HT_SOBEL_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData66_HT_SOBEL_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData67_HT_SOBEL_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData68_HT_SOBEL_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData69_HT_SOBEL_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData70_HT_SOBEL_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData71_HT_SOBEL_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData72_HT_SOBEL_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData73_HT_SOBEL_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData74_HT_SOBEL_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData75_HT_SOBEL_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData76_HT_SOBEL_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData77_HT_SOBEL_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData78_HT_SOBEL_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData79_HT_SOBEL_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData80_HT_SOBEL_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData81_HT_SOBEL_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData82_HT_SOBEL_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData83_HT_SOBEL_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData84_HT_SOBEL_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData85_HT_SOBEL_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData86_HT_SOBEL_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData87_HT_SOBEL_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData88_HT_SOBEL_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData89_HT_SOBEL_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData90_HT_SOBEL_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData91_HT_SOBEL_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData92_HT_SOBEL_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData93_HT_SOBEL_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData94_HT_SOBEL_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData95_HT_SOBEL_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData96_HT_SOBEL_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData97_HT_SOBEL_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData98_HT_SOBEL_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData99_HT_SOBEL_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData100_HT_SOBEL_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData101_HT_SOBEL_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData102_HT_SOBEL_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData103_HT_SOBEL_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData104_HT_SOBEL_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData105_HT_SOBEL_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData106_HT_SOBEL_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData107_HT_SOBEL_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData108_HT_SOBEL_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData109_HT_SOBEL_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData110_HT_SOBEL_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData111_HT_SOBEL_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData112_HT_SOBEL_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData113_HT_SOBEL_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData114_HT_SOBEL_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData115_HT_SOBEL_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData116_HT_SOBEL_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData117_HT_SOBEL_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData118_HT_SOBEL_3X3_16S[] = {{1}};

static acf_scenario gScenarioArray_HT_SOBEL_3X3_16S[] = {
{1, 1, 104, 0, 2, gScenarioBufferData0_HT_SOBEL_3X3_16S, 20, gScenarioKernelData0_HT_SOBEL_3X3_16S, 2},
{2, 1, 164, 0, 2, gScenarioBufferData1_HT_SOBEL_3X3_16S, 20, gScenarioKernelData1_HT_SOBEL_3X3_16S, 2},
{3, 1, 224, 0, 2, gScenarioBufferData2_HT_SOBEL_3X3_16S, 20, gScenarioKernelData2_HT_SOBEL_3X3_16S, 2},
{4, 1, 284, 0, 2, gScenarioBufferData3_HT_SOBEL_3X3_16S, 20, gScenarioKernelData3_HT_SOBEL_3X3_16S, 2},
{5, 1, 344, 0, 2, gScenarioBufferData4_HT_SOBEL_3X3_16S, 20, gScenarioKernelData4_HT_SOBEL_3X3_16S, 2},
{6, 1, 404, 0, 2, gScenarioBufferData5_HT_SOBEL_3X3_16S, 20, gScenarioKernelData5_HT_SOBEL_3X3_16S, 2},
{7, 1, 464, 0, 2, gScenarioBufferData6_HT_SOBEL_3X3_16S, 20, gScenarioKernelData6_HT_SOBEL_3X3_16S, 2},
{8, 1, 524, 0, 2, gScenarioBufferData7_HT_SOBEL_3X3_16S, 20, gScenarioKernelData7_HT_SOBEL_3X3_16S, 2},
{10, 1, 644, 0, 2, gScenarioBufferData8_HT_SOBEL_3X3_16S, 20, gScenarioKernelData8_HT_SOBEL_3X3_16S, 2},
{12, 1, 764, 0, 2, gScenarioBufferData9_HT_SOBEL_3X3_16S, 20, gScenarioKernelData9_HT_SOBEL_3X3_16S, 2},
{14, 1, 884, 0, 2, gScenarioBufferData10_HT_SOBEL_3X3_16S, 20, gScenarioKernelData10_HT_SOBEL_3X3_16S, 2},
{16, 1, 1004, 0, 2, gScenarioBufferData11_HT_SOBEL_3X3_16S, 20, gScenarioKernelData11_HT_SOBEL_3X3_16S, 2},
{1, 2, 128, 0, 1, gScenarioBufferData12_HT_SOBEL_3X3_16S, 20, gScenarioKernelData12_HT_SOBEL_3X3_16S, 2},
{2, 2, 208, 0, 1, gScenarioBufferData13_HT_SOBEL_3X3_16S, 20, gScenarioKernelData13_HT_SOBEL_3X3_16S, 2},
{3, 2, 288, 0, 1, gScenarioBufferData14_HT_SOBEL_3X3_16S, 20, gScenarioKernelData14_HT_SOBEL_3X3_16S, 2},
{4, 2, 368, 0, 1, gScenarioBufferData15_HT_SOBEL_3X3_16S, 20, gScenarioKernelData15_HT_SOBEL_3X3_16S, 2},
{5, 2, 448, 0, 1, gScenarioBufferData16_HT_SOBEL_3X3_16S, 20, gScenarioKernelData16_HT_SOBEL_3X3_16S, 2},
{6, 2, 528, 0, 1, gScenarioBufferData17_HT_SOBEL_3X3_16S, 20, gScenarioKernelData17_HT_SOBEL_3X3_16S, 2},
{7, 2, 608, 0, 1, gScenarioBufferData18_HT_SOBEL_3X3_16S, 20, gScenarioKernelData18_HT_SOBEL_3X3_16S, 2},
{8, 2, 688, 0, 1, gScenarioBufferData19_HT_SOBEL_3X3_16S, 20, gScenarioKernelData19_HT_SOBEL_3X3_16S, 2},
{10, 2, 848, 0, 1, gScenarioBufferData20_HT_SOBEL_3X3_16S, 20, gScenarioKernelData20_HT_SOBEL_3X3_16S, 2},
{12, 2, 1008, 0, 1, gScenarioBufferData21_HT_SOBEL_3X3_16S, 20, gScenarioKernelData21_HT_SOBEL_3X3_16S, 2},
{14, 2, 1168, 0, 1, gScenarioBufferData22_HT_SOBEL_3X3_16S, 20, gScenarioKernelData22_HT_SOBEL_3X3_16S, 2},
{16, 2, 1328, 0, 1, gScenarioBufferData23_HT_SOBEL_3X3_16S, 20, gScenarioKernelData23_HT_SOBEL_3X3_16S, 2},
{1, 4, 224, 0, 1, gScenarioBufferData24_HT_SOBEL_3X3_16S, 20, gScenarioKernelData24_HT_SOBEL_3X3_16S, 2},
{2, 4, 368, 0, 1, gScenarioBufferData25_HT_SOBEL_3X3_16S, 20, gScenarioKernelData25_HT_SOBEL_3X3_16S, 2},
{3, 4, 512, 0, 1, gScenarioBufferData26_HT_SOBEL_3X3_16S, 20, gScenarioKernelData26_HT_SOBEL_3X3_16S, 2},
{4, 4, 656, 0, 1, gScenarioBufferData27_HT_SOBEL_3X3_16S, 20, gScenarioKernelData27_HT_SOBEL_3X3_16S, 2},
{5, 4, 800, 0, 1, gScenarioBufferData28_HT_SOBEL_3X3_16S, 20, gScenarioKernelData28_HT_SOBEL_3X3_16S, 2},
{6, 4, 944, 0, 1, gScenarioBufferData29_HT_SOBEL_3X3_16S, 20, gScenarioKernelData29_HT_SOBEL_3X3_16S, 2},
{7, 4, 1088, 0, 1, gScenarioBufferData30_HT_SOBEL_3X3_16S, 20, gScenarioKernelData30_HT_SOBEL_3X3_16S, 2},
{8, 4, 1232, 0, 1, gScenarioBufferData31_HT_SOBEL_3X3_16S, 20, gScenarioKernelData31_HT_SOBEL_3X3_16S, 2},
{10, 4, 1520, 0, 1, gScenarioBufferData32_HT_SOBEL_3X3_16S, 20, gScenarioKernelData32_HT_SOBEL_3X3_16S, 2},
{12, 4, 1808, 0, 1, gScenarioBufferData33_HT_SOBEL_3X3_16S, 20, gScenarioKernelData33_HT_SOBEL_3X3_16S, 2},
{14, 4, 2096, 0, 1, gScenarioBufferData34_HT_SOBEL_3X3_16S, 20, gScenarioKernelData34_HT_SOBEL_3X3_16S, 2},
{16, 4, 2384, 0, 1, gScenarioBufferData35_HT_SOBEL_3X3_16S, 20, gScenarioKernelData35_HT_SOBEL_3X3_16S, 2},
{1, 6, 320, 0, 1, gScenarioBufferData36_HT_SOBEL_3X3_16S, 20, gScenarioKernelData36_HT_SOBEL_3X3_16S, 2},
{2, 6, 528, 0, 1, gScenarioBufferData37_HT_SOBEL_3X3_16S, 20, gScenarioKernelData37_HT_SOBEL_3X3_16S, 2},
{3, 6, 736, 0, 1, gScenarioBufferData38_HT_SOBEL_3X3_16S, 20, gScenarioKernelData38_HT_SOBEL_3X3_16S, 2},
{4, 6, 944, 0, 1, gScenarioBufferData39_HT_SOBEL_3X3_16S, 20, gScenarioKernelData39_HT_SOBEL_3X3_16S, 2},
{5, 6, 1152, 0, 1, gScenarioBufferData40_HT_SOBEL_3X3_16S, 20, gScenarioKernelData40_HT_SOBEL_3X3_16S, 2},
{6, 6, 1360, 0, 1, gScenarioBufferData41_HT_SOBEL_3X3_16S, 20, gScenarioKernelData41_HT_SOBEL_3X3_16S, 2},
{7, 6, 1568, 0, 1, gScenarioBufferData42_HT_SOBEL_3X3_16S, 20, gScenarioKernelData42_HT_SOBEL_3X3_16S, 2},
{8, 6, 1776, 0, 1, gScenarioBufferData43_HT_SOBEL_3X3_16S, 20, gScenarioKernelData43_HT_SOBEL_3X3_16S, 2},
{10, 6, 2192, 0, 1, gScenarioBufferData44_HT_SOBEL_3X3_16S, 20, gScenarioKernelData44_HT_SOBEL_3X3_16S, 2},
{12, 6, 2608, 0, 1, gScenarioBufferData45_HT_SOBEL_3X3_16S, 20, gScenarioKernelData45_HT_SOBEL_3X3_16S, 2},
{14, 6, 3024, 0, 1, gScenarioBufferData46_HT_SOBEL_3X3_16S, 20, gScenarioKernelData46_HT_SOBEL_3X3_16S, 2},
{16, 6, 3440, 0, 1, gScenarioBufferData47_HT_SOBEL_3X3_16S, 20, gScenarioKernelData47_HT_SOBEL_3X3_16S, 2},
{1, 8, 416, 0, 1, gScenarioBufferData48_HT_SOBEL_3X3_16S, 20, gScenarioKernelData48_HT_SOBEL_3X3_16S, 2},
{2, 8, 688, 0, 1, gScenarioBufferData49_HT_SOBEL_3X3_16S, 20, gScenarioKernelData49_HT_SOBEL_3X3_16S, 2},
{3, 8, 960, 0, 1, gScenarioBufferData50_HT_SOBEL_3X3_16S, 20, gScenarioKernelData50_HT_SOBEL_3X3_16S, 2},
{4, 8, 1232, 0, 1, gScenarioBufferData51_HT_SOBEL_3X3_16S, 20, gScenarioKernelData51_HT_SOBEL_3X3_16S, 2},
{5, 8, 1504, 0, 1, gScenarioBufferData52_HT_SOBEL_3X3_16S, 20, gScenarioKernelData52_HT_SOBEL_3X3_16S, 2},
{6, 8, 1776, 0, 1, gScenarioBufferData53_HT_SOBEL_3X3_16S, 20, gScenarioKernelData53_HT_SOBEL_3X3_16S, 2},
{7, 8, 2048, 0, 1, gScenarioBufferData54_HT_SOBEL_3X3_16S, 20, gScenarioKernelData54_HT_SOBEL_3X3_16S, 2},
{8, 8, 2320, 0, 1, gScenarioBufferData55_HT_SOBEL_3X3_16S, 20, gScenarioKernelData55_HT_SOBEL_3X3_16S, 2},
{10, 8, 2864, 0, 1, gScenarioBufferData56_HT_SOBEL_3X3_16S, 20, gScenarioKernelData56_HT_SOBEL_3X3_16S, 2},
{12, 8, 3408, 0, 1, gScenarioBufferData57_HT_SOBEL_3X3_16S, 20, gScenarioKernelData57_HT_SOBEL_3X3_16S, 2},
{1, 10, 512, 0, 1, gScenarioBufferData58_HT_SOBEL_3X3_16S, 20, gScenarioKernelData58_HT_SOBEL_3X3_16S, 2},
{2, 10, 848, 0, 1, gScenarioBufferData59_HT_SOBEL_3X3_16S, 20, gScenarioKernelData59_HT_SOBEL_3X3_16S, 2},
{3, 10, 1184, 0, 1, gScenarioBufferData60_HT_SOBEL_3X3_16S, 20, gScenarioKernelData60_HT_SOBEL_3X3_16S, 2},
{4, 10, 1520, 0, 1, gScenarioBufferData61_HT_SOBEL_3X3_16S, 20, gScenarioKernelData61_HT_SOBEL_3X3_16S, 2},
{5, 10, 1856, 0, 1, gScenarioBufferData62_HT_SOBEL_3X3_16S, 20, gScenarioKernelData62_HT_SOBEL_3X3_16S, 2},
{6, 10, 2192, 0, 1, gScenarioBufferData63_HT_SOBEL_3X3_16S, 20, gScenarioKernelData63_HT_SOBEL_3X3_16S, 2},
{7, 10, 2528, 0, 1, gScenarioBufferData64_HT_SOBEL_3X3_16S, 20, gScenarioKernelData64_HT_SOBEL_3X3_16S, 2},
{8, 10, 2864, 0, 1, gScenarioBufferData65_HT_SOBEL_3X3_16S, 20, gScenarioKernelData65_HT_SOBEL_3X3_16S, 2},
{10, 10, 3536, 0, 1, gScenarioBufferData66_HT_SOBEL_3X3_16S, 20, gScenarioKernelData66_HT_SOBEL_3X3_16S, 2},
{1, 12, 608, 0, 1, gScenarioBufferData67_HT_SOBEL_3X3_16S, 20, gScenarioKernelData67_HT_SOBEL_3X3_16S, 2},
{2, 12, 1008, 0, 1, gScenarioBufferData68_HT_SOBEL_3X3_16S, 20, gScenarioKernelData68_HT_SOBEL_3X3_16S, 2},
{3, 12, 1408, 0, 1, gScenarioBufferData69_HT_SOBEL_3X3_16S, 20, gScenarioKernelData69_HT_SOBEL_3X3_16S, 2},
{4, 12, 1808, 0, 1, gScenarioBufferData70_HT_SOBEL_3X3_16S, 20, gScenarioKernelData70_HT_SOBEL_3X3_16S, 2},
{5, 12, 2208, 0, 1, gScenarioBufferData71_HT_SOBEL_3X3_16S, 20, gScenarioKernelData71_HT_SOBEL_3X3_16S, 2},
{6, 12, 2608, 0, 1, gScenarioBufferData72_HT_SOBEL_3X3_16S, 20, gScenarioKernelData72_HT_SOBEL_3X3_16S, 2},
{7, 12, 3008, 0, 1, gScenarioBufferData73_HT_SOBEL_3X3_16S, 20, gScenarioKernelData73_HT_SOBEL_3X3_16S, 2},
{8, 12, 3408, 0, 1, gScenarioBufferData74_HT_SOBEL_3X3_16S, 20, gScenarioKernelData74_HT_SOBEL_3X3_16S, 2},
{1, 14, 704, 0, 1, gScenarioBufferData75_HT_SOBEL_3X3_16S, 20, gScenarioKernelData75_HT_SOBEL_3X3_16S, 2},
{2, 14, 1168, 0, 1, gScenarioBufferData76_HT_SOBEL_3X3_16S, 20, gScenarioKernelData76_HT_SOBEL_3X3_16S, 2},
{3, 14, 1632, 0, 1, gScenarioBufferData77_HT_SOBEL_3X3_16S, 20, gScenarioKernelData77_HT_SOBEL_3X3_16S, 2},
{4, 14, 2096, 0, 1, gScenarioBufferData78_HT_SOBEL_3X3_16S, 20, gScenarioKernelData78_HT_SOBEL_3X3_16S, 2},
{5, 14, 2560, 0, 1, gScenarioBufferData79_HT_SOBEL_3X3_16S, 20, gScenarioKernelData79_HT_SOBEL_3X3_16S, 2},
{6, 14, 3024, 0, 1, gScenarioBufferData80_HT_SOBEL_3X3_16S, 20, gScenarioKernelData80_HT_SOBEL_3X3_16S, 2},
{7, 14, 3488, 0, 1, gScenarioBufferData81_HT_SOBEL_3X3_16S, 20, gScenarioKernelData81_HT_SOBEL_3X3_16S, 2},
{1, 16, 800, 0, 1, gScenarioBufferData82_HT_SOBEL_3X3_16S, 20, gScenarioKernelData82_HT_SOBEL_3X3_16S, 2},
{2, 16, 1328, 0, 1, gScenarioBufferData83_HT_SOBEL_3X3_16S, 20, gScenarioKernelData83_HT_SOBEL_3X3_16S, 2},
{3, 16, 1856, 0, 1, gScenarioBufferData84_HT_SOBEL_3X3_16S, 20, gScenarioKernelData84_HT_SOBEL_3X3_16S, 2},
{4, 16, 2384, 0, 1, gScenarioBufferData85_HT_SOBEL_3X3_16S, 20, gScenarioKernelData85_HT_SOBEL_3X3_16S, 2},
{5, 16, 2912, 0, 1, gScenarioBufferData86_HT_SOBEL_3X3_16S, 20, gScenarioKernelData86_HT_SOBEL_3X3_16S, 2},
{6, 16, 3440, 0, 1, gScenarioBufferData87_HT_SOBEL_3X3_16S, 20, gScenarioKernelData87_HT_SOBEL_3X3_16S, 2},
{1, 18, 896, 0, 1, gScenarioBufferData88_HT_SOBEL_3X3_16S, 20, gScenarioKernelData88_HT_SOBEL_3X3_16S, 2},
{2, 18, 1488, 0, 1, gScenarioBufferData89_HT_SOBEL_3X3_16S, 20, gScenarioKernelData89_HT_SOBEL_3X3_16S, 2},
{3, 18, 2080, 0, 1, gScenarioBufferData90_HT_SOBEL_3X3_16S, 20, gScenarioKernelData90_HT_SOBEL_3X3_16S, 2},
{4, 18, 2672, 0, 1, gScenarioBufferData91_HT_SOBEL_3X3_16S, 20, gScenarioKernelData91_HT_SOBEL_3X3_16S, 2},
{5, 18, 3264, 0, 1, gScenarioBufferData92_HT_SOBEL_3X3_16S, 20, gScenarioKernelData92_HT_SOBEL_3X3_16S, 2},
{1, 20, 992, 0, 1, gScenarioBufferData93_HT_SOBEL_3X3_16S, 20, gScenarioKernelData93_HT_SOBEL_3X3_16S, 2},
{2, 20, 1648, 0, 1, gScenarioBufferData94_HT_SOBEL_3X3_16S, 20, gScenarioKernelData94_HT_SOBEL_3X3_16S, 2},
{3, 20, 2304, 0, 1, gScenarioBufferData95_HT_SOBEL_3X3_16S, 20, gScenarioKernelData95_HT_SOBEL_3X3_16S, 2},
{4, 20, 2960, 0, 1, gScenarioBufferData96_HT_SOBEL_3X3_16S, 20, gScenarioKernelData96_HT_SOBEL_3X3_16S, 2},
{5, 20, 3616, 0, 1, gScenarioBufferData97_HT_SOBEL_3X3_16S, 20, gScenarioKernelData97_HT_SOBEL_3X3_16S, 2},
{1, 22, 1088, 0, 1, gScenarioBufferData98_HT_SOBEL_3X3_16S, 20, gScenarioKernelData98_HT_SOBEL_3X3_16S, 2},
{2, 22, 1808, 0, 1, gScenarioBufferData99_HT_SOBEL_3X3_16S, 20, gScenarioKernelData99_HT_SOBEL_3X3_16S, 2},
{3, 22, 2528, 0, 1, gScenarioBufferData100_HT_SOBEL_3X3_16S, 20, gScenarioKernelData100_HT_SOBEL_3X3_16S, 2},
{4, 22, 3248, 0, 1, gScenarioBufferData101_HT_SOBEL_3X3_16S, 20, gScenarioKernelData101_HT_SOBEL_3X3_16S, 2},
{1, 24, 1184, 0, 1, gScenarioBufferData102_HT_SOBEL_3X3_16S, 20, gScenarioKernelData102_HT_SOBEL_3X3_16S, 2},
{2, 24, 1968, 0, 1, gScenarioBufferData103_HT_SOBEL_3X3_16S, 20, gScenarioKernelData103_HT_SOBEL_3X3_16S, 2},
{3, 24, 2752, 0, 1, gScenarioBufferData104_HT_SOBEL_3X3_16S, 20, gScenarioKernelData104_HT_SOBEL_3X3_16S, 2},
{4, 24, 3536, 0, 1, gScenarioBufferData105_HT_SOBEL_3X3_16S, 20, gScenarioKernelData105_HT_SOBEL_3X3_16S, 2},
{1, 26, 1280, 0, 1, gScenarioBufferData106_HT_SOBEL_3X3_16S, 20, gScenarioKernelData106_HT_SOBEL_3X3_16S, 2},
{2, 26, 2128, 0, 1, gScenarioBufferData107_HT_SOBEL_3X3_16S, 20, gScenarioKernelData107_HT_SOBEL_3X3_16S, 2},
{3, 26, 2976, 0, 1, gScenarioBufferData108_HT_SOBEL_3X3_16S, 20, gScenarioKernelData108_HT_SOBEL_3X3_16S, 2},
{4, 26, 3824, 0, 1, gScenarioBufferData109_HT_SOBEL_3X3_16S, 20, gScenarioKernelData109_HT_SOBEL_3X3_16S, 2},
{1, 28, 1376, 0, 1, gScenarioBufferData110_HT_SOBEL_3X3_16S, 20, gScenarioKernelData110_HT_SOBEL_3X3_16S, 2},
{2, 28, 2288, 0, 1, gScenarioBufferData111_HT_SOBEL_3X3_16S, 20, gScenarioKernelData111_HT_SOBEL_3X3_16S, 2},
{3, 28, 3200, 0, 1, gScenarioBufferData112_HT_SOBEL_3X3_16S, 20, gScenarioKernelData112_HT_SOBEL_3X3_16S, 2},
{1, 30, 1472, 0, 1, gScenarioBufferData113_HT_SOBEL_3X3_16S, 20, gScenarioKernelData113_HT_SOBEL_3X3_16S, 2},
{2, 30, 2448, 0, 1, gScenarioBufferData114_HT_SOBEL_3X3_16S, 20, gScenarioKernelData114_HT_SOBEL_3X3_16S, 2},
{3, 30, 3424, 0, 1, gScenarioBufferData115_HT_SOBEL_3X3_16S, 20, gScenarioKernelData115_HT_SOBEL_3X3_16S, 2},
{1, 32, 1568, 0, 1, gScenarioBufferData116_HT_SOBEL_3X3_16S, 20, gScenarioKernelData116_HT_SOBEL_3X3_16S, 2},
{2, 32, 2608, 0, 1, gScenarioBufferData117_HT_SOBEL_3X3_16S, 20, gScenarioKernelData117_HT_SOBEL_3X3_16S, 2},
{3, 32, 3648, 0, 1, gScenarioBufferData118_HT_SOBEL_3X3_16S, 20, gScenarioKernelData118_HT_SOBEL_3X3_16S, 2}
};

static acf_scenario_list gScenarioList_HT_SOBEL_3X3_16S = {
119, //number of scenarios
gScenarioArray_HT_SOBEL_3X3_16S};
//**************************************************************

class HT_SOBEL_3X3_16S : public ACF_Process_APU
{
public:
   HT_SOBEL_3X3_16S(int32_t apex_id = 0) : ACF_Process_APU(apex_id)
   {} 

   int32_t Initialize()
   {
      int32_t lRetVal = 0;

      if (!Initialized()) //initialization steps that only need to occur once
      {
         SetProcessIdentifier("HT_SOBEL_3X3_16S");
         SetApuLoadInfo(HT_SOBEL_3X3_16S_LOAD_SEGMENTS,
                        HT_SOBEL_3X3_16S_LOAD_PMEM, HT_SOBEL_3X3_16S_LOAD_PMEM_SIZE,
                        HT_SOBEL_3X3_16S_LOAD_DMEM, HT_SOBEL_3X3_16S_LOAD_DMEM_SIZE,
                        0, 0); //assuming _LOAD_CMEM does not exist
         FlagSpatialDep();

         //***NOTE: the order in which the following ports are added is meaningful; do not change!

         AddPort("INPUT_0", ICP_DATATYPE_08U, 1, 1, 4, 1, 0, 0, 0, 0, 0, 0, 0, 0x2020202);
         AddPort("OUTPUT_0", ICP_DATATYPE_16S, 1, 1, 4, 1, 1, 0, 0, 0, 0, 0, 1);

         CfgScenarios(&gScenarioList_HT_SOBEL_3X3_16S);

         FlagAsInitialized();
      }

      lRetVal = SelectApuConfiguration(mApuCfg, mApexId); //by default mApuCfg = ACF_APU_CFG__APEX0_DEFAULT and mApexId = 0

      return lRetVal;
   }
};

#endif //_ACF_PROCESS_APU_HT_SOBEL_3X3_16S
