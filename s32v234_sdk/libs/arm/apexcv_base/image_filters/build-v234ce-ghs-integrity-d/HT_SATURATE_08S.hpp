#ifndef _ACF_PROCESS_APU_HT_SATURATE_08S
#define _ACF_PROCESS_APU_HT_SATURATE_08S

#include <acf_process_apu.h>
#include <HT_SATURATE_08S_APU_LOAD.h> //APU load associated with this process
#include <stdint.h>


//SCENARIO LIST*************************************************
static acf_scenario_buffer_data gScenarioBufferData0_HT_SATURATE_08S[] = {{2, 1, 2, 0, 0x0}, {2, 1, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData1_HT_SATURATE_08S[] = {{4, 1, 2, 0, 0x0}, {4, 1, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData2_HT_SATURATE_08S[] = {{6, 1, 2, 0, 0x0}, {6, 1, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData3_HT_SATURATE_08S[] = {{8, 1, 2, 0, 0x0}, {8, 1, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData4_HT_SATURATE_08S[] = {{10, 1, 2, 0, 0x0}, {10, 1, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData5_HT_SATURATE_08S[] = {{12, 1, 2, 0, 0x0}, {12, 1, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData6_HT_SATURATE_08S[] = {{14, 1, 2, 0, 0x0}, {14, 1, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData7_HT_SATURATE_08S[] = {{16, 1, 2, 0, 0x0}, {16, 1, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData8_HT_SATURATE_08S[] = {{20, 1, 2, 0, 0x0}, {20, 1, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData9_HT_SATURATE_08S[] = {{24, 1, 2, 0, 0x0}, {24, 1, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData10_HT_SATURATE_08S[] = {{28, 1, 2, 0, 0x0}, {28, 1, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData11_HT_SATURATE_08S[] = {{32, 1, 2, 0, 0x0}, {32, 1, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData12_HT_SATURATE_08S[] = {{36, 1, 2, 0, 0x0}, {36, 1, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData13_HT_SATURATE_08S[] = {{40, 1, 2, 0, 0x0}, {40, 1, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData14_HT_SATURATE_08S[] = {{44, 1, 2, 0, 0x0}, {44, 1, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData15_HT_SATURATE_08S[] = {{48, 1, 2, 0, 0x0}, {48, 1, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData16_HT_SATURATE_08S[] = {{52, 1, 2, 0, 0x0}, {52, 1, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData17_HT_SATURATE_08S[] = {{56, 1, 2, 0, 0x0}, {56, 1, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData18_HT_SATURATE_08S[] = {{60, 1, 2, 0, 0x0}, {60, 1, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData19_HT_SATURATE_08S[] = {{64, 1, 2, 0, 0x0}, {64, 1, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData20_HT_SATURATE_08S[] = {{2, 2, 2, 0, 0x0}, {2, 2, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData21_HT_SATURATE_08S[] = {{4, 2, 2, 0, 0x0}, {4, 2, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData22_HT_SATURATE_08S[] = {{6, 2, 2, 0, 0x0}, {6, 2, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData23_HT_SATURATE_08S[] = {{8, 2, 2, 0, 0x0}, {8, 2, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData24_HT_SATURATE_08S[] = {{10, 2, 2, 0, 0x0}, {10, 2, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData25_HT_SATURATE_08S[] = {{12, 2, 2, 0, 0x0}, {12, 2, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData26_HT_SATURATE_08S[] = {{14, 2, 2, 0, 0x0}, {14, 2, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData27_HT_SATURATE_08S[] = {{16, 2, 2, 0, 0x0}, {16, 2, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData28_HT_SATURATE_08S[] = {{20, 2, 2, 0, 0x0}, {20, 2, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData29_HT_SATURATE_08S[] = {{24, 2, 2, 0, 0x0}, {24, 2, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData30_HT_SATURATE_08S[] = {{28, 2, 2, 0, 0x0}, {28, 2, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData31_HT_SATURATE_08S[] = {{32, 2, 2, 0, 0x0}, {32, 2, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData32_HT_SATURATE_08S[] = {{36, 2, 2, 0, 0x0}, {36, 2, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData33_HT_SATURATE_08S[] = {{40, 2, 2, 0, 0x0}, {40, 2, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData34_HT_SATURATE_08S[] = {{44, 2, 2, 0, 0x0}, {44, 2, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData35_HT_SATURATE_08S[] = {{48, 2, 2, 0, 0x0}, {48, 2, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData36_HT_SATURATE_08S[] = {{52, 2, 2, 0, 0x0}, {52, 2, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData37_HT_SATURATE_08S[] = {{56, 2, 2, 0, 0x0}, {56, 2, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData38_HT_SATURATE_08S[] = {{60, 2, 2, 0, 0x0}, {60, 2, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData39_HT_SATURATE_08S[] = {{64, 2, 2, 0, 0x0}, {64, 2, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData40_HT_SATURATE_08S[] = {{2, 4, 2, 0, 0x0}, {2, 4, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData41_HT_SATURATE_08S[] = {{4, 4, 2, 0, 0x0}, {4, 4, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData42_HT_SATURATE_08S[] = {{6, 4, 2, 0, 0x0}, {6, 4, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData43_HT_SATURATE_08S[] = {{8, 4, 2, 0, 0x0}, {8, 4, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData44_HT_SATURATE_08S[] = {{10, 4, 2, 0, 0x0}, {10, 4, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData45_HT_SATURATE_08S[] = {{12, 4, 2, 0, 0x0}, {12, 4, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData46_HT_SATURATE_08S[] = {{14, 4, 2, 0, 0x0}, {14, 4, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData47_HT_SATURATE_08S[] = {{16, 4, 2, 0, 0x0}, {16, 4, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData48_HT_SATURATE_08S[] = {{20, 4, 2, 0, 0x0}, {20, 4, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData49_HT_SATURATE_08S[] = {{24, 4, 2, 0, 0x0}, {24, 4, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData50_HT_SATURATE_08S[] = {{28, 4, 2, 0, 0x0}, {28, 4, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData51_HT_SATURATE_08S[] = {{32, 4, 2, 0, 0x0}, {32, 4, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData52_HT_SATURATE_08S[] = {{36, 4, 2, 0, 0x0}, {36, 4, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData53_HT_SATURATE_08S[] = {{40, 4, 2, 0, 0x0}, {40, 4, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData54_HT_SATURATE_08S[] = {{44, 4, 2, 0, 0x0}, {44, 4, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData55_HT_SATURATE_08S[] = {{48, 4, 2, 0, 0x0}, {48, 4, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData56_HT_SATURATE_08S[] = {{52, 4, 2, 0, 0x0}, {52, 4, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData57_HT_SATURATE_08S[] = {{56, 4, 2, 0, 0x0}, {56, 4, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData58_HT_SATURATE_08S[] = {{60, 4, 2, 0, 0x0}, {60, 4, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData59_HT_SATURATE_08S[] = {{64, 4, 2, 0, 0x0}, {64, 4, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData60_HT_SATURATE_08S[] = {{2, 6, 2, 0, 0x0}, {2, 6, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData61_HT_SATURATE_08S[] = {{4, 6, 2, 0, 0x0}, {4, 6, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData62_HT_SATURATE_08S[] = {{6, 6, 2, 0, 0x0}, {6, 6, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData63_HT_SATURATE_08S[] = {{8, 6, 2, 0, 0x0}, {8, 6, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData64_HT_SATURATE_08S[] = {{10, 6, 2, 0, 0x0}, {10, 6, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData65_HT_SATURATE_08S[] = {{12, 6, 2, 0, 0x0}, {12, 6, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData66_HT_SATURATE_08S[] = {{14, 6, 2, 0, 0x0}, {14, 6, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData67_HT_SATURATE_08S[] = {{16, 6, 2, 0, 0x0}, {16, 6, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData68_HT_SATURATE_08S[] = {{20, 6, 2, 0, 0x0}, {20, 6, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData69_HT_SATURATE_08S[] = {{24, 6, 2, 0, 0x0}, {24, 6, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData70_HT_SATURATE_08S[] = {{28, 6, 2, 0, 0x0}, {28, 6, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData71_HT_SATURATE_08S[] = {{32, 6, 2, 0, 0x0}, {32, 6, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData72_HT_SATURATE_08S[] = {{36, 6, 2, 0, 0x0}, {36, 6, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData73_HT_SATURATE_08S[] = {{40, 6, 2, 0, 0x0}, {40, 6, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData74_HT_SATURATE_08S[] = {{44, 6, 2, 0, 0x0}, {44, 6, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData75_HT_SATURATE_08S[] = {{48, 6, 2, 0, 0x0}, {48, 6, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData76_HT_SATURATE_08S[] = {{52, 6, 2, 0, 0x0}, {52, 6, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData77_HT_SATURATE_08S[] = {{56, 6, 2, 0, 0x0}, {56, 6, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData78_HT_SATURATE_08S[] = {{60, 6, 2, 0, 0x0}, {60, 6, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData79_HT_SATURATE_08S[] = {{64, 6, 2, 0, 0x0}, {64, 6, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData80_HT_SATURATE_08S[] = {{2, 8, 2, 0, 0x0}, {2, 8, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData81_HT_SATURATE_08S[] = {{4, 8, 2, 0, 0x0}, {4, 8, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData82_HT_SATURATE_08S[] = {{6, 8, 2, 0, 0x0}, {6, 8, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData83_HT_SATURATE_08S[] = {{8, 8, 2, 0, 0x0}, {8, 8, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData84_HT_SATURATE_08S[] = {{10, 8, 2, 0, 0x0}, {10, 8, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData85_HT_SATURATE_08S[] = {{12, 8, 2, 0, 0x0}, {12, 8, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData86_HT_SATURATE_08S[] = {{14, 8, 2, 0, 0x0}, {14, 8, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData87_HT_SATURATE_08S[] = {{16, 8, 2, 0, 0x0}, {16, 8, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData88_HT_SATURATE_08S[] = {{20, 8, 2, 0, 0x0}, {20, 8, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData89_HT_SATURATE_08S[] = {{24, 8, 2, 0, 0x0}, {24, 8, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData90_HT_SATURATE_08S[] = {{28, 8, 2, 0, 0x0}, {28, 8, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData91_HT_SATURATE_08S[] = {{32, 8, 2, 0, 0x0}, {32, 8, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData92_HT_SATURATE_08S[] = {{36, 8, 2, 0, 0x0}, {36, 8, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData93_HT_SATURATE_08S[] = {{40, 8, 2, 0, 0x0}, {40, 8, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData94_HT_SATURATE_08S[] = {{44, 8, 2, 0, 0x0}, {44, 8, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData95_HT_SATURATE_08S[] = {{48, 8, 2, 0, 0x0}, {48, 8, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData96_HT_SATURATE_08S[] = {{52, 8, 2, 0, 0x0}, {52, 8, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData97_HT_SATURATE_08S[] = {{56, 8, 2, 0, 0x0}, {56, 8, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData98_HT_SATURATE_08S[] = {{60, 8, 2, 0, 0x0}, {60, 8, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData99_HT_SATURATE_08S[] = {{64, 8, 2, 0, 0x0}, {64, 8, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData100_HT_SATURATE_08S[] = {{2, 10, 2, 0, 0x0}, {2, 10, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData101_HT_SATURATE_08S[] = {{4, 10, 2, 0, 0x0}, {4, 10, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData102_HT_SATURATE_08S[] = {{6, 10, 2, 0, 0x0}, {6, 10, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData103_HT_SATURATE_08S[] = {{8, 10, 2, 0, 0x0}, {8, 10, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData104_HT_SATURATE_08S[] = {{10, 10, 2, 0, 0x0}, {10, 10, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData105_HT_SATURATE_08S[] = {{12, 10, 2, 0, 0x0}, {12, 10, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData106_HT_SATURATE_08S[] = {{14, 10, 2, 0, 0x0}, {14, 10, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData107_HT_SATURATE_08S[] = {{16, 10, 2, 0, 0x0}, {16, 10, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData108_HT_SATURATE_08S[] = {{20, 10, 2, 0, 0x0}, {20, 10, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData109_HT_SATURATE_08S[] = {{24, 10, 2, 0, 0x0}, {24, 10, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData110_HT_SATURATE_08S[] = {{28, 10, 2, 0, 0x0}, {28, 10, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData111_HT_SATURATE_08S[] = {{32, 10, 2, 0, 0x0}, {32, 10, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData112_HT_SATURATE_08S[] = {{36, 10, 2, 0, 0x0}, {36, 10, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData113_HT_SATURATE_08S[] = {{40, 10, 2, 0, 0x0}, {40, 10, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData114_HT_SATURATE_08S[] = {{44, 10, 2, 0, 0x0}, {44, 10, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData115_HT_SATURATE_08S[] = {{48, 10, 2, 0, 0x0}, {48, 10, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData116_HT_SATURATE_08S[] = {{52, 10, 2, 0, 0x0}, {52, 10, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData117_HT_SATURATE_08S[] = {{56, 10, 2, 0, 0x0}, {56, 10, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData118_HT_SATURATE_08S[] = {{60, 10, 2, 0, 0x0}, {60, 10, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData119_HT_SATURATE_08S[] = {{64, 10, 2, 0, 0x0}, {64, 10, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData120_HT_SATURATE_08S[] = {{2, 12, 2, 0, 0x0}, {2, 12, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData121_HT_SATURATE_08S[] = {{4, 12, 2, 0, 0x0}, {4, 12, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData122_HT_SATURATE_08S[] = {{6, 12, 2, 0, 0x0}, {6, 12, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData123_HT_SATURATE_08S[] = {{8, 12, 2, 0, 0x0}, {8, 12, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData124_HT_SATURATE_08S[] = {{10, 12, 2, 0, 0x0}, {10, 12, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData125_HT_SATURATE_08S[] = {{12, 12, 2, 0, 0x0}, {12, 12, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData126_HT_SATURATE_08S[] = {{14, 12, 2, 0, 0x0}, {14, 12, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData127_HT_SATURATE_08S[] = {{16, 12, 2, 0, 0x0}, {16, 12, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData128_HT_SATURATE_08S[] = {{20, 12, 2, 0, 0x0}, {20, 12, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData129_HT_SATURATE_08S[] = {{24, 12, 2, 0, 0x0}, {24, 12, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData130_HT_SATURATE_08S[] = {{28, 12, 2, 0, 0x0}, {28, 12, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData131_HT_SATURATE_08S[] = {{32, 12, 2, 0, 0x0}, {32, 12, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData132_HT_SATURATE_08S[] = {{36, 12, 2, 0, 0x0}, {36, 12, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData133_HT_SATURATE_08S[] = {{40, 12, 2, 0, 0x0}, {40, 12, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData134_HT_SATURATE_08S[] = {{44, 12, 2, 0, 0x0}, {44, 12, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData135_HT_SATURATE_08S[] = {{48, 12, 2, 0, 0x0}, {48, 12, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData136_HT_SATURATE_08S[] = {{52, 12, 2, 0, 0x0}, {52, 12, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData137_HT_SATURATE_08S[] = {{2, 14, 2, 0, 0x0}, {2, 14, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData138_HT_SATURATE_08S[] = {{4, 14, 2, 0, 0x0}, {4, 14, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData139_HT_SATURATE_08S[] = {{6, 14, 2, 0, 0x0}, {6, 14, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData140_HT_SATURATE_08S[] = {{8, 14, 2, 0, 0x0}, {8, 14, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData141_HT_SATURATE_08S[] = {{10, 14, 2, 0, 0x0}, {10, 14, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData142_HT_SATURATE_08S[] = {{12, 14, 2, 0, 0x0}, {12, 14, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData143_HT_SATURATE_08S[] = {{14, 14, 2, 0, 0x0}, {14, 14, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData144_HT_SATURATE_08S[] = {{16, 14, 2, 0, 0x0}, {16, 14, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData145_HT_SATURATE_08S[] = {{20, 14, 2, 0, 0x0}, {20, 14, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData146_HT_SATURATE_08S[] = {{24, 14, 2, 0, 0x0}, {24, 14, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData147_HT_SATURATE_08S[] = {{28, 14, 2, 0, 0x0}, {28, 14, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData148_HT_SATURATE_08S[] = {{32, 14, 2, 0, 0x0}, {32, 14, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData149_HT_SATURATE_08S[] = {{36, 14, 2, 0, 0x0}, {36, 14, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData150_HT_SATURATE_08S[] = {{40, 14, 2, 0, 0x0}, {40, 14, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData151_HT_SATURATE_08S[] = {{44, 14, 2, 0, 0x0}, {44, 14, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData152_HT_SATURATE_08S[] = {{2, 16, 2, 0, 0x0}, {2, 16, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData153_HT_SATURATE_08S[] = {{4, 16, 2, 0, 0x0}, {4, 16, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData154_HT_SATURATE_08S[] = {{6, 16, 2, 0, 0x0}, {6, 16, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData155_HT_SATURATE_08S[] = {{8, 16, 2, 0, 0x0}, {8, 16, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData156_HT_SATURATE_08S[] = {{10, 16, 2, 0, 0x0}, {10, 16, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData157_HT_SATURATE_08S[] = {{12, 16, 2, 0, 0x0}, {12, 16, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData158_HT_SATURATE_08S[] = {{14, 16, 2, 0, 0x0}, {14, 16, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData159_HT_SATURATE_08S[] = {{16, 16, 2, 0, 0x0}, {16, 16, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData160_HT_SATURATE_08S[] = {{20, 16, 2, 0, 0x0}, {20, 16, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData161_HT_SATURATE_08S[] = {{24, 16, 2, 0, 0x0}, {24, 16, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData162_HT_SATURATE_08S[] = {{28, 16, 2, 0, 0x0}, {28, 16, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData163_HT_SATURATE_08S[] = {{32, 16, 2, 0, 0x0}, {32, 16, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData164_HT_SATURATE_08S[] = {{36, 16, 2, 0, 0x0}, {36, 16, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData165_HT_SATURATE_08S[] = {{40, 16, 2, 0, 0x0}, {40, 16, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData166_HT_SATURATE_08S[] = {{2, 18, 2, 0, 0x0}, {2, 18, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData167_HT_SATURATE_08S[] = {{4, 18, 2, 0, 0x0}, {4, 18, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData168_HT_SATURATE_08S[] = {{6, 18, 2, 0, 0x0}, {6, 18, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData169_HT_SATURATE_08S[] = {{8, 18, 2, 0, 0x0}, {8, 18, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData170_HT_SATURATE_08S[] = {{10, 18, 2, 0, 0x0}, {10, 18, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData171_HT_SATURATE_08S[] = {{12, 18, 2, 0, 0x0}, {12, 18, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData172_HT_SATURATE_08S[] = {{14, 18, 2, 0, 0x0}, {14, 18, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData173_HT_SATURATE_08S[] = {{16, 18, 2, 0, 0x0}, {16, 18, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData174_HT_SATURATE_08S[] = {{20, 18, 2, 0, 0x0}, {20, 18, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData175_HT_SATURATE_08S[] = {{24, 18, 2, 0, 0x0}, {24, 18, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData176_HT_SATURATE_08S[] = {{28, 18, 2, 0, 0x0}, {28, 18, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData177_HT_SATURATE_08S[] = {{32, 18, 2, 0, 0x0}, {32, 18, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData178_HT_SATURATE_08S[] = {{2, 20, 2, 0, 0x0}, {2, 20, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData179_HT_SATURATE_08S[] = {{4, 20, 2, 0, 0x0}, {4, 20, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData180_HT_SATURATE_08S[] = {{6, 20, 2, 0, 0x0}, {6, 20, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData181_HT_SATURATE_08S[] = {{8, 20, 2, 0, 0x0}, {8, 20, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData182_HT_SATURATE_08S[] = {{10, 20, 2, 0, 0x0}, {10, 20, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData183_HT_SATURATE_08S[] = {{12, 20, 2, 0, 0x0}, {12, 20, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData184_HT_SATURATE_08S[] = {{14, 20, 2, 0, 0x0}, {14, 20, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData185_HT_SATURATE_08S[] = {{16, 20, 2, 0, 0x0}, {16, 20, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData186_HT_SATURATE_08S[] = {{20, 20, 2, 0, 0x0}, {20, 20, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData187_HT_SATURATE_08S[] = {{24, 20, 2, 0, 0x0}, {24, 20, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData188_HT_SATURATE_08S[] = {{28, 20, 2, 0, 0x0}, {28, 20, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData189_HT_SATURATE_08S[] = {{32, 20, 2, 0, 0x0}, {32, 20, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData190_HT_SATURATE_08S[] = {{2, 22, 2, 0, 0x0}, {2, 22, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData191_HT_SATURATE_08S[] = {{4, 22, 2, 0, 0x0}, {4, 22, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData192_HT_SATURATE_08S[] = {{6, 22, 2, 0, 0x0}, {6, 22, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData193_HT_SATURATE_08S[] = {{8, 22, 2, 0, 0x0}, {8, 22, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData194_HT_SATURATE_08S[] = {{10, 22, 2, 0, 0x0}, {10, 22, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData195_HT_SATURATE_08S[] = {{12, 22, 2, 0, 0x0}, {12, 22, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData196_HT_SATURATE_08S[] = {{14, 22, 2, 0, 0x0}, {14, 22, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData197_HT_SATURATE_08S[] = {{16, 22, 2, 0, 0x0}, {16, 22, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData198_HT_SATURATE_08S[] = {{20, 22, 2, 0, 0x0}, {20, 22, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData199_HT_SATURATE_08S[] = {{24, 22, 2, 0, 0x0}, {24, 22, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData200_HT_SATURATE_08S[] = {{28, 22, 2, 0, 0x0}, {28, 22, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData201_HT_SATURATE_08S[] = {{2, 24, 2, 0, 0x0}, {2, 24, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData202_HT_SATURATE_08S[] = {{4, 24, 2, 0, 0x0}, {4, 24, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData203_HT_SATURATE_08S[] = {{6, 24, 2, 0, 0x0}, {6, 24, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData204_HT_SATURATE_08S[] = {{8, 24, 2, 0, 0x0}, {8, 24, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData205_HT_SATURATE_08S[] = {{10, 24, 2, 0, 0x0}, {10, 24, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData206_HT_SATURATE_08S[] = {{12, 24, 2, 0, 0x0}, {12, 24, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData207_HT_SATURATE_08S[] = {{14, 24, 2, 0, 0x0}, {14, 24, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData208_HT_SATURATE_08S[] = {{16, 24, 2, 0, 0x0}, {16, 24, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData209_HT_SATURATE_08S[] = {{20, 24, 2, 0, 0x0}, {20, 24, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData210_HT_SATURATE_08S[] = {{24, 24, 2, 0, 0x0}, {24, 24, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData211_HT_SATURATE_08S[] = {{2, 26, 2, 0, 0x0}, {2, 26, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData212_HT_SATURATE_08S[] = {{4, 26, 2, 0, 0x0}, {4, 26, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData213_HT_SATURATE_08S[] = {{6, 26, 2, 0, 0x0}, {6, 26, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData214_HT_SATURATE_08S[] = {{8, 26, 2, 0, 0x0}, {8, 26, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData215_HT_SATURATE_08S[] = {{10, 26, 2, 0, 0x0}, {10, 26, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData216_HT_SATURATE_08S[] = {{12, 26, 2, 0, 0x0}, {12, 26, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData217_HT_SATURATE_08S[] = {{14, 26, 2, 0, 0x0}, {14, 26, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData218_HT_SATURATE_08S[] = {{16, 26, 2, 0, 0x0}, {16, 26, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData219_HT_SATURATE_08S[] = {{20, 26, 2, 0, 0x0}, {20, 26, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData220_HT_SATURATE_08S[] = {{24, 26, 2, 0, 0x0}, {24, 26, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData221_HT_SATURATE_08S[] = {{2, 28, 2, 0, 0x0}, {2, 28, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData222_HT_SATURATE_08S[] = {{4, 28, 2, 0, 0x0}, {4, 28, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData223_HT_SATURATE_08S[] = {{6, 28, 2, 0, 0x0}, {6, 28, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData224_HT_SATURATE_08S[] = {{8, 28, 2, 0, 0x0}, {8, 28, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData225_HT_SATURATE_08S[] = {{10, 28, 2, 0, 0x0}, {10, 28, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData226_HT_SATURATE_08S[] = {{12, 28, 2, 0, 0x0}, {12, 28, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData227_HT_SATURATE_08S[] = {{14, 28, 2, 0, 0x0}, {14, 28, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData228_HT_SATURATE_08S[] = {{16, 28, 2, 0, 0x0}, {16, 28, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData229_HT_SATURATE_08S[] = {{20, 28, 2, 0, 0x0}, {20, 28, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData230_HT_SATURATE_08S[] = {{2, 30, 2, 0, 0x0}, {2, 30, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData231_HT_SATURATE_08S[] = {{4, 30, 2, 0, 0x0}, {4, 30, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData232_HT_SATURATE_08S[] = {{6, 30, 2, 0, 0x0}, {6, 30, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData233_HT_SATURATE_08S[] = {{8, 30, 2, 0, 0x0}, {8, 30, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData234_HT_SATURATE_08S[] = {{10, 30, 2, 0, 0x0}, {10, 30, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData235_HT_SATURATE_08S[] = {{12, 30, 2, 0, 0x0}, {12, 30, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData236_HT_SATURATE_08S[] = {{14, 30, 2, 0, 0x0}, {14, 30, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData237_HT_SATURATE_08S[] = {{16, 30, 2, 0, 0x0}, {16, 30, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData238_HT_SATURATE_08S[] = {{20, 30, 2, 0, 0x0}, {20, 30, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData239_HT_SATURATE_08S[] = {{2, 32, 2, 0, 0x0}, {2, 32, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData240_HT_SATURATE_08S[] = {{4, 32, 2, 0, 0x0}, {4, 32, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData241_HT_SATURATE_08S[] = {{6, 32, 2, 0, 0x0}, {6, 32, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData242_HT_SATURATE_08S[] = {{8, 32, 2, 0, 0x0}, {8, 32, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData243_HT_SATURATE_08S[] = {{10, 32, 2, 0, 0x0}, {10, 32, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData244_HT_SATURATE_08S[] = {{12, 32, 2, 0, 0x0}, {12, 32, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData245_HT_SATURATE_08S[] = {{14, 32, 2, 0, 0x0}, {14, 32, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData246_HT_SATURATE_08S[] = {{16, 32, 2, 0, 0x0}, {16, 32, 2, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData247_HT_SATURATE_08S[] = {{20, 32, 2, 0, 0x0}, {20, 32, 2, 0, 0x0}};

static acf_scenario_kernel_data gScenarioKernelData0_HT_SATURATE_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData1_HT_SATURATE_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData2_HT_SATURATE_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData3_HT_SATURATE_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData4_HT_SATURATE_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData5_HT_SATURATE_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData6_HT_SATURATE_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData7_HT_SATURATE_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData8_HT_SATURATE_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData9_HT_SATURATE_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData10_HT_SATURATE_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData11_HT_SATURATE_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData12_HT_SATURATE_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData13_HT_SATURATE_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData14_HT_SATURATE_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData15_HT_SATURATE_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData16_HT_SATURATE_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData17_HT_SATURATE_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData18_HT_SATURATE_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData19_HT_SATURATE_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData20_HT_SATURATE_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData21_HT_SATURATE_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData22_HT_SATURATE_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData23_HT_SATURATE_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData24_HT_SATURATE_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData25_HT_SATURATE_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData26_HT_SATURATE_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData27_HT_SATURATE_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData28_HT_SATURATE_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData29_HT_SATURATE_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData30_HT_SATURATE_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData31_HT_SATURATE_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData32_HT_SATURATE_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData33_HT_SATURATE_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData34_HT_SATURATE_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData35_HT_SATURATE_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData36_HT_SATURATE_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData37_HT_SATURATE_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData38_HT_SATURATE_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData39_HT_SATURATE_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData40_HT_SATURATE_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData41_HT_SATURATE_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData42_HT_SATURATE_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData43_HT_SATURATE_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData44_HT_SATURATE_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData45_HT_SATURATE_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData46_HT_SATURATE_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData47_HT_SATURATE_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData48_HT_SATURATE_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData49_HT_SATURATE_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData50_HT_SATURATE_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData51_HT_SATURATE_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData52_HT_SATURATE_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData53_HT_SATURATE_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData54_HT_SATURATE_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData55_HT_SATURATE_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData56_HT_SATURATE_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData57_HT_SATURATE_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData58_HT_SATURATE_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData59_HT_SATURATE_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData60_HT_SATURATE_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData61_HT_SATURATE_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData62_HT_SATURATE_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData63_HT_SATURATE_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData64_HT_SATURATE_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData65_HT_SATURATE_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData66_HT_SATURATE_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData67_HT_SATURATE_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData68_HT_SATURATE_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData69_HT_SATURATE_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData70_HT_SATURATE_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData71_HT_SATURATE_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData72_HT_SATURATE_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData73_HT_SATURATE_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData74_HT_SATURATE_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData75_HT_SATURATE_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData76_HT_SATURATE_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData77_HT_SATURATE_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData78_HT_SATURATE_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData79_HT_SATURATE_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData80_HT_SATURATE_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData81_HT_SATURATE_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData82_HT_SATURATE_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData83_HT_SATURATE_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData84_HT_SATURATE_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData85_HT_SATURATE_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData86_HT_SATURATE_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData87_HT_SATURATE_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData88_HT_SATURATE_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData89_HT_SATURATE_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData90_HT_SATURATE_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData91_HT_SATURATE_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData92_HT_SATURATE_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData93_HT_SATURATE_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData94_HT_SATURATE_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData95_HT_SATURATE_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData96_HT_SATURATE_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData97_HT_SATURATE_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData98_HT_SATURATE_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData99_HT_SATURATE_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData100_HT_SATURATE_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData101_HT_SATURATE_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData102_HT_SATURATE_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData103_HT_SATURATE_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData104_HT_SATURATE_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData105_HT_SATURATE_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData106_HT_SATURATE_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData107_HT_SATURATE_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData108_HT_SATURATE_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData109_HT_SATURATE_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData110_HT_SATURATE_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData111_HT_SATURATE_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData112_HT_SATURATE_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData113_HT_SATURATE_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData114_HT_SATURATE_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData115_HT_SATURATE_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData116_HT_SATURATE_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData117_HT_SATURATE_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData118_HT_SATURATE_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData119_HT_SATURATE_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData120_HT_SATURATE_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData121_HT_SATURATE_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData122_HT_SATURATE_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData123_HT_SATURATE_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData124_HT_SATURATE_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData125_HT_SATURATE_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData126_HT_SATURATE_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData127_HT_SATURATE_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData128_HT_SATURATE_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData129_HT_SATURATE_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData130_HT_SATURATE_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData131_HT_SATURATE_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData132_HT_SATURATE_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData133_HT_SATURATE_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData134_HT_SATURATE_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData135_HT_SATURATE_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData136_HT_SATURATE_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData137_HT_SATURATE_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData138_HT_SATURATE_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData139_HT_SATURATE_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData140_HT_SATURATE_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData141_HT_SATURATE_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData142_HT_SATURATE_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData143_HT_SATURATE_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData144_HT_SATURATE_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData145_HT_SATURATE_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData146_HT_SATURATE_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData147_HT_SATURATE_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData148_HT_SATURATE_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData149_HT_SATURATE_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData150_HT_SATURATE_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData151_HT_SATURATE_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData152_HT_SATURATE_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData153_HT_SATURATE_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData154_HT_SATURATE_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData155_HT_SATURATE_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData156_HT_SATURATE_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData157_HT_SATURATE_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData158_HT_SATURATE_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData159_HT_SATURATE_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData160_HT_SATURATE_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData161_HT_SATURATE_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData162_HT_SATURATE_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData163_HT_SATURATE_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData164_HT_SATURATE_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData165_HT_SATURATE_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData166_HT_SATURATE_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData167_HT_SATURATE_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData168_HT_SATURATE_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData169_HT_SATURATE_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData170_HT_SATURATE_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData171_HT_SATURATE_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData172_HT_SATURATE_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData173_HT_SATURATE_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData174_HT_SATURATE_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData175_HT_SATURATE_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData176_HT_SATURATE_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData177_HT_SATURATE_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData178_HT_SATURATE_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData179_HT_SATURATE_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData180_HT_SATURATE_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData181_HT_SATURATE_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData182_HT_SATURATE_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData183_HT_SATURATE_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData184_HT_SATURATE_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData185_HT_SATURATE_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData186_HT_SATURATE_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData187_HT_SATURATE_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData188_HT_SATURATE_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData189_HT_SATURATE_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData190_HT_SATURATE_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData191_HT_SATURATE_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData192_HT_SATURATE_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData193_HT_SATURATE_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData194_HT_SATURATE_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData195_HT_SATURATE_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData196_HT_SATURATE_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData197_HT_SATURATE_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData198_HT_SATURATE_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData199_HT_SATURATE_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData200_HT_SATURATE_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData201_HT_SATURATE_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData202_HT_SATURATE_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData203_HT_SATURATE_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData204_HT_SATURATE_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData205_HT_SATURATE_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData206_HT_SATURATE_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData207_HT_SATURATE_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData208_HT_SATURATE_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData209_HT_SATURATE_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData210_HT_SATURATE_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData211_HT_SATURATE_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData212_HT_SATURATE_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData213_HT_SATURATE_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData214_HT_SATURATE_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData215_HT_SATURATE_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData216_HT_SATURATE_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData217_HT_SATURATE_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData218_HT_SATURATE_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData219_HT_SATURATE_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData220_HT_SATURATE_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData221_HT_SATURATE_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData222_HT_SATURATE_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData223_HT_SATURATE_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData224_HT_SATURATE_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData225_HT_SATURATE_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData226_HT_SATURATE_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData227_HT_SATURATE_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData228_HT_SATURATE_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData229_HT_SATURATE_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData230_HT_SATURATE_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData231_HT_SATURATE_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData232_HT_SATURATE_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData233_HT_SATURATE_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData234_HT_SATURATE_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData235_HT_SATURATE_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData236_HT_SATURATE_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData237_HT_SATURATE_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData238_HT_SATURATE_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData239_HT_SATURATE_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData240_HT_SATURATE_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData241_HT_SATURATE_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData242_HT_SATURATE_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData243_HT_SATURATE_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData244_HT_SATURATE_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData245_HT_SATURATE_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData246_HT_SATURATE_08S[] = {{0}};
static acf_scenario_kernel_data gScenarioKernelData247_HT_SATURATE_08S[] = {{0}};

static acf_scenario gScenarioArray_HT_SATURATE_08S[] = {
{1, 1, 12, 0, 0, gScenarioBufferData0_HT_SATURATE_08S, 20, gScenarioKernelData0_HT_SATURATE_08S, 2},
{2, 1, 24, 0, 0, gScenarioBufferData1_HT_SATURATE_08S, 20, gScenarioKernelData1_HT_SATURATE_08S, 2},
{3, 1, 36, 0, 0, gScenarioBufferData2_HT_SATURATE_08S, 20, gScenarioKernelData2_HT_SATURATE_08S, 2},
{4, 1, 48, 0, 0, gScenarioBufferData3_HT_SATURATE_08S, 20, gScenarioKernelData3_HT_SATURATE_08S, 2},
{5, 1, 60, 0, 0, gScenarioBufferData4_HT_SATURATE_08S, 20, gScenarioKernelData4_HT_SATURATE_08S, 2},
{6, 1, 72, 0, 0, gScenarioBufferData5_HT_SATURATE_08S, 20, gScenarioKernelData5_HT_SATURATE_08S, 2},
{7, 1, 84, 0, 0, gScenarioBufferData6_HT_SATURATE_08S, 20, gScenarioKernelData6_HT_SATURATE_08S, 2},
{8, 1, 96, 0, 0, gScenarioBufferData7_HT_SATURATE_08S, 20, gScenarioKernelData7_HT_SATURATE_08S, 2},
{10, 1, 120, 0, 0, gScenarioBufferData8_HT_SATURATE_08S, 20, gScenarioKernelData8_HT_SATURATE_08S, 2},
{12, 1, 144, 0, 0, gScenarioBufferData9_HT_SATURATE_08S, 20, gScenarioKernelData9_HT_SATURATE_08S, 2},
{14, 1, 168, 0, 0, gScenarioBufferData10_HT_SATURATE_08S, 20, gScenarioKernelData10_HT_SATURATE_08S, 2},
{16, 1, 192, 0, 0, gScenarioBufferData11_HT_SATURATE_08S, 20, gScenarioKernelData11_HT_SATURATE_08S, 2},
{18, 1, 216, 0, 0, gScenarioBufferData12_HT_SATURATE_08S, 20, gScenarioKernelData12_HT_SATURATE_08S, 2},
{20, 1, 240, 0, 0, gScenarioBufferData13_HT_SATURATE_08S, 20, gScenarioKernelData13_HT_SATURATE_08S, 2},
{22, 1, 264, 0, 0, gScenarioBufferData14_HT_SATURATE_08S, 20, gScenarioKernelData14_HT_SATURATE_08S, 2},
{24, 1, 288, 0, 0, gScenarioBufferData15_HT_SATURATE_08S, 20, gScenarioKernelData15_HT_SATURATE_08S, 2},
{26, 1, 312, 0, 0, gScenarioBufferData16_HT_SATURATE_08S, 20, gScenarioKernelData16_HT_SATURATE_08S, 2},
{28, 1, 336, 0, 0, gScenarioBufferData17_HT_SATURATE_08S, 20, gScenarioKernelData17_HT_SATURATE_08S, 2},
{30, 1, 360, 0, 0, gScenarioBufferData18_HT_SATURATE_08S, 20, gScenarioKernelData18_HT_SATURATE_08S, 2},
{32, 1, 384, 0, 0, gScenarioBufferData19_HT_SATURATE_08S, 20, gScenarioKernelData19_HT_SATURATE_08S, 2},
{1, 2, 24, 0, 0, gScenarioBufferData20_HT_SATURATE_08S, 20, gScenarioKernelData20_HT_SATURATE_08S, 2},
{2, 2, 48, 0, 0, gScenarioBufferData21_HT_SATURATE_08S, 20, gScenarioKernelData21_HT_SATURATE_08S, 2},
{3, 2, 72, 0, 0, gScenarioBufferData22_HT_SATURATE_08S, 20, gScenarioKernelData22_HT_SATURATE_08S, 2},
{4, 2, 96, 0, 0, gScenarioBufferData23_HT_SATURATE_08S, 20, gScenarioKernelData23_HT_SATURATE_08S, 2},
{5, 2, 120, 0, 0, gScenarioBufferData24_HT_SATURATE_08S, 20, gScenarioKernelData24_HT_SATURATE_08S, 2},
{6, 2, 144, 0, 0, gScenarioBufferData25_HT_SATURATE_08S, 20, gScenarioKernelData25_HT_SATURATE_08S, 2},
{7, 2, 168, 0, 0, gScenarioBufferData26_HT_SATURATE_08S, 20, gScenarioKernelData26_HT_SATURATE_08S, 2},
{8, 2, 192, 0, 0, gScenarioBufferData27_HT_SATURATE_08S, 20, gScenarioKernelData27_HT_SATURATE_08S, 2},
{10, 2, 240, 0, 0, gScenarioBufferData28_HT_SATURATE_08S, 20, gScenarioKernelData28_HT_SATURATE_08S, 2},
{12, 2, 288, 0, 0, gScenarioBufferData29_HT_SATURATE_08S, 20, gScenarioKernelData29_HT_SATURATE_08S, 2},
{14, 2, 336, 0, 0, gScenarioBufferData30_HT_SATURATE_08S, 20, gScenarioKernelData30_HT_SATURATE_08S, 2},
{16, 2, 384, 0, 0, gScenarioBufferData31_HT_SATURATE_08S, 20, gScenarioKernelData31_HT_SATURATE_08S, 2},
{18, 2, 432, 0, 0, gScenarioBufferData32_HT_SATURATE_08S, 20, gScenarioKernelData32_HT_SATURATE_08S, 2},
{20, 2, 480, 0, 0, gScenarioBufferData33_HT_SATURATE_08S, 20, gScenarioKernelData33_HT_SATURATE_08S, 2},
{22, 2, 528, 0, 0, gScenarioBufferData34_HT_SATURATE_08S, 20, gScenarioKernelData34_HT_SATURATE_08S, 2},
{24, 2, 576, 0, 0, gScenarioBufferData35_HT_SATURATE_08S, 20, gScenarioKernelData35_HT_SATURATE_08S, 2},
{26, 2, 624, 0, 0, gScenarioBufferData36_HT_SATURATE_08S, 20, gScenarioKernelData36_HT_SATURATE_08S, 2},
{28, 2, 672, 0, 0, gScenarioBufferData37_HT_SATURATE_08S, 20, gScenarioKernelData37_HT_SATURATE_08S, 2},
{30, 2, 720, 0, 0, gScenarioBufferData38_HT_SATURATE_08S, 20, gScenarioKernelData38_HT_SATURATE_08S, 2},
{32, 2, 768, 0, 0, gScenarioBufferData39_HT_SATURATE_08S, 20, gScenarioKernelData39_HT_SATURATE_08S, 2},
{1, 4, 48, 0, 0, gScenarioBufferData40_HT_SATURATE_08S, 20, gScenarioKernelData40_HT_SATURATE_08S, 2},
{2, 4, 96, 0, 0, gScenarioBufferData41_HT_SATURATE_08S, 20, gScenarioKernelData41_HT_SATURATE_08S, 2},
{3, 4, 144, 0, 0, gScenarioBufferData42_HT_SATURATE_08S, 20, gScenarioKernelData42_HT_SATURATE_08S, 2},
{4, 4, 192, 0, 0, gScenarioBufferData43_HT_SATURATE_08S, 20, gScenarioKernelData43_HT_SATURATE_08S, 2},
{5, 4, 240, 0, 0, gScenarioBufferData44_HT_SATURATE_08S, 20, gScenarioKernelData44_HT_SATURATE_08S, 2},
{6, 4, 288, 0, 0, gScenarioBufferData45_HT_SATURATE_08S, 20, gScenarioKernelData45_HT_SATURATE_08S, 2},
{7, 4, 336, 0, 0, gScenarioBufferData46_HT_SATURATE_08S, 20, gScenarioKernelData46_HT_SATURATE_08S, 2},
{8, 4, 384, 0, 0, gScenarioBufferData47_HT_SATURATE_08S, 20, gScenarioKernelData47_HT_SATURATE_08S, 2},
{10, 4, 480, 0, 0, gScenarioBufferData48_HT_SATURATE_08S, 20, gScenarioKernelData48_HT_SATURATE_08S, 2},
{12, 4, 576, 0, 0, gScenarioBufferData49_HT_SATURATE_08S, 20, gScenarioKernelData49_HT_SATURATE_08S, 2},
{14, 4, 672, 0, 0, gScenarioBufferData50_HT_SATURATE_08S, 20, gScenarioKernelData50_HT_SATURATE_08S, 2},
{16, 4, 768, 0, 0, gScenarioBufferData51_HT_SATURATE_08S, 20, gScenarioKernelData51_HT_SATURATE_08S, 2},
{18, 4, 864, 0, 0, gScenarioBufferData52_HT_SATURATE_08S, 20, gScenarioKernelData52_HT_SATURATE_08S, 2},
{20, 4, 960, 0, 0, gScenarioBufferData53_HT_SATURATE_08S, 20, gScenarioKernelData53_HT_SATURATE_08S, 2},
{22, 4, 1056, 0, 0, gScenarioBufferData54_HT_SATURATE_08S, 20, gScenarioKernelData54_HT_SATURATE_08S, 2},
{24, 4, 1152, 0, 0, gScenarioBufferData55_HT_SATURATE_08S, 20, gScenarioKernelData55_HT_SATURATE_08S, 2},
{26, 4, 1248, 0, 0, gScenarioBufferData56_HT_SATURATE_08S, 20, gScenarioKernelData56_HT_SATURATE_08S, 2},
{28, 4, 1344, 0, 0, gScenarioBufferData57_HT_SATURATE_08S, 20, gScenarioKernelData57_HT_SATURATE_08S, 2},
{30, 4, 1440, 0, 0, gScenarioBufferData58_HT_SATURATE_08S, 20, gScenarioKernelData58_HT_SATURATE_08S, 2},
{32, 4, 1536, 0, 0, gScenarioBufferData59_HT_SATURATE_08S, 20, gScenarioKernelData59_HT_SATURATE_08S, 2},
{1, 6, 72, 0, 0, gScenarioBufferData60_HT_SATURATE_08S, 20, gScenarioKernelData60_HT_SATURATE_08S, 2},
{2, 6, 144, 0, 0, gScenarioBufferData61_HT_SATURATE_08S, 20, gScenarioKernelData61_HT_SATURATE_08S, 2},
{3, 6, 216, 0, 0, gScenarioBufferData62_HT_SATURATE_08S, 20, gScenarioKernelData62_HT_SATURATE_08S, 2},
{4, 6, 288, 0, 0, gScenarioBufferData63_HT_SATURATE_08S, 20, gScenarioKernelData63_HT_SATURATE_08S, 2},
{5, 6, 360, 0, 0, gScenarioBufferData64_HT_SATURATE_08S, 20, gScenarioKernelData64_HT_SATURATE_08S, 2},
{6, 6, 432, 0, 0, gScenarioBufferData65_HT_SATURATE_08S, 20, gScenarioKernelData65_HT_SATURATE_08S, 2},
{7, 6, 504, 0, 0, gScenarioBufferData66_HT_SATURATE_08S, 20, gScenarioKernelData66_HT_SATURATE_08S, 2},
{8, 6, 576, 0, 0, gScenarioBufferData67_HT_SATURATE_08S, 20, gScenarioKernelData67_HT_SATURATE_08S, 2},
{10, 6, 720, 0, 0, gScenarioBufferData68_HT_SATURATE_08S, 20, gScenarioKernelData68_HT_SATURATE_08S, 2},
{12, 6, 864, 0, 0, gScenarioBufferData69_HT_SATURATE_08S, 20, gScenarioKernelData69_HT_SATURATE_08S, 2},
{14, 6, 1008, 0, 0, gScenarioBufferData70_HT_SATURATE_08S, 20, gScenarioKernelData70_HT_SATURATE_08S, 2},
{16, 6, 1152, 0, 0, gScenarioBufferData71_HT_SATURATE_08S, 20, gScenarioKernelData71_HT_SATURATE_08S, 2},
{18, 6, 1296, 0, 0, gScenarioBufferData72_HT_SATURATE_08S, 20, gScenarioKernelData72_HT_SATURATE_08S, 2},
{20, 6, 1440, 0, 0, gScenarioBufferData73_HT_SATURATE_08S, 20, gScenarioKernelData73_HT_SATURATE_08S, 2},
{22, 6, 1584, 0, 0, gScenarioBufferData74_HT_SATURATE_08S, 20, gScenarioKernelData74_HT_SATURATE_08S, 2},
{24, 6, 1728, 0, 0, gScenarioBufferData75_HT_SATURATE_08S, 20, gScenarioKernelData75_HT_SATURATE_08S, 2},
{26, 6, 1872, 0, 0, gScenarioBufferData76_HT_SATURATE_08S, 20, gScenarioKernelData76_HT_SATURATE_08S, 2},
{28, 6, 2016, 0, 0, gScenarioBufferData77_HT_SATURATE_08S, 20, gScenarioKernelData77_HT_SATURATE_08S, 2},
{30, 6, 2160, 0, 0, gScenarioBufferData78_HT_SATURATE_08S, 20, gScenarioKernelData78_HT_SATURATE_08S, 2},
{32, 6, 2304, 0, 0, gScenarioBufferData79_HT_SATURATE_08S, 20, gScenarioKernelData79_HT_SATURATE_08S, 2},
{1, 8, 96, 0, 0, gScenarioBufferData80_HT_SATURATE_08S, 20, gScenarioKernelData80_HT_SATURATE_08S, 2},
{2, 8, 192, 0, 0, gScenarioBufferData81_HT_SATURATE_08S, 20, gScenarioKernelData81_HT_SATURATE_08S, 2},
{3, 8, 288, 0, 0, gScenarioBufferData82_HT_SATURATE_08S, 20, gScenarioKernelData82_HT_SATURATE_08S, 2},
{4, 8, 384, 0, 0, gScenarioBufferData83_HT_SATURATE_08S, 20, gScenarioKernelData83_HT_SATURATE_08S, 2},
{5, 8, 480, 0, 0, gScenarioBufferData84_HT_SATURATE_08S, 20, gScenarioKernelData84_HT_SATURATE_08S, 2},
{6, 8, 576, 0, 0, gScenarioBufferData85_HT_SATURATE_08S, 20, gScenarioKernelData85_HT_SATURATE_08S, 2},
{7, 8, 672, 0, 0, gScenarioBufferData86_HT_SATURATE_08S, 20, gScenarioKernelData86_HT_SATURATE_08S, 2},
{8, 8, 768, 0, 0, gScenarioBufferData87_HT_SATURATE_08S, 20, gScenarioKernelData87_HT_SATURATE_08S, 2},
{10, 8, 960, 0, 0, gScenarioBufferData88_HT_SATURATE_08S, 20, gScenarioKernelData88_HT_SATURATE_08S, 2},
{12, 8, 1152, 0, 0, gScenarioBufferData89_HT_SATURATE_08S, 20, gScenarioKernelData89_HT_SATURATE_08S, 2},
{14, 8, 1344, 0, 0, gScenarioBufferData90_HT_SATURATE_08S, 20, gScenarioKernelData90_HT_SATURATE_08S, 2},
{16, 8, 1536, 0, 0, gScenarioBufferData91_HT_SATURATE_08S, 20, gScenarioKernelData91_HT_SATURATE_08S, 2},
{18, 8, 1728, 0, 0, gScenarioBufferData92_HT_SATURATE_08S, 20, gScenarioKernelData92_HT_SATURATE_08S, 2},
{20, 8, 1920, 0, 0, gScenarioBufferData93_HT_SATURATE_08S, 20, gScenarioKernelData93_HT_SATURATE_08S, 2},
{22, 8, 2112, 0, 0, gScenarioBufferData94_HT_SATURATE_08S, 20, gScenarioKernelData94_HT_SATURATE_08S, 2},
{24, 8, 2304, 0, 0, gScenarioBufferData95_HT_SATURATE_08S, 20, gScenarioKernelData95_HT_SATURATE_08S, 2},
{26, 8, 2496, 0, 0, gScenarioBufferData96_HT_SATURATE_08S, 20, gScenarioKernelData96_HT_SATURATE_08S, 2},
{28, 8, 2688, 0, 0, gScenarioBufferData97_HT_SATURATE_08S, 20, gScenarioKernelData97_HT_SATURATE_08S, 2},
{30, 8, 2880, 0, 0, gScenarioBufferData98_HT_SATURATE_08S, 20, gScenarioKernelData98_HT_SATURATE_08S, 2},
{32, 8, 3072, 0, 0, gScenarioBufferData99_HT_SATURATE_08S, 20, gScenarioKernelData99_HT_SATURATE_08S, 2},
{1, 10, 120, 0, 0, gScenarioBufferData100_HT_SATURATE_08S, 20, gScenarioKernelData100_HT_SATURATE_08S, 2},
{2, 10, 240, 0, 0, gScenarioBufferData101_HT_SATURATE_08S, 20, gScenarioKernelData101_HT_SATURATE_08S, 2},
{3, 10, 360, 0, 0, gScenarioBufferData102_HT_SATURATE_08S, 20, gScenarioKernelData102_HT_SATURATE_08S, 2},
{4, 10, 480, 0, 0, gScenarioBufferData103_HT_SATURATE_08S, 20, gScenarioKernelData103_HT_SATURATE_08S, 2},
{5, 10, 600, 0, 0, gScenarioBufferData104_HT_SATURATE_08S, 20, gScenarioKernelData104_HT_SATURATE_08S, 2},
{6, 10, 720, 0, 0, gScenarioBufferData105_HT_SATURATE_08S, 20, gScenarioKernelData105_HT_SATURATE_08S, 2},
{7, 10, 840, 0, 0, gScenarioBufferData106_HT_SATURATE_08S, 20, gScenarioKernelData106_HT_SATURATE_08S, 2},
{8, 10, 960, 0, 0, gScenarioBufferData107_HT_SATURATE_08S, 20, gScenarioKernelData107_HT_SATURATE_08S, 2},
{10, 10, 1200, 0, 0, gScenarioBufferData108_HT_SATURATE_08S, 20, gScenarioKernelData108_HT_SATURATE_08S, 2},
{12, 10, 1440, 0, 0, gScenarioBufferData109_HT_SATURATE_08S, 20, gScenarioKernelData109_HT_SATURATE_08S, 2},
{14, 10, 1680, 0, 0, gScenarioBufferData110_HT_SATURATE_08S, 20, gScenarioKernelData110_HT_SATURATE_08S, 2},
{16, 10, 1920, 0, 0, gScenarioBufferData111_HT_SATURATE_08S, 20, gScenarioKernelData111_HT_SATURATE_08S, 2},
{18, 10, 2160, 0, 0, gScenarioBufferData112_HT_SATURATE_08S, 20, gScenarioKernelData112_HT_SATURATE_08S, 2},
{20, 10, 2400, 0, 0, gScenarioBufferData113_HT_SATURATE_08S, 20, gScenarioKernelData113_HT_SATURATE_08S, 2},
{22, 10, 2640, 0, 0, gScenarioBufferData114_HT_SATURATE_08S, 20, gScenarioKernelData114_HT_SATURATE_08S, 2},
{24, 10, 2880, 0, 0, gScenarioBufferData115_HT_SATURATE_08S, 20, gScenarioKernelData115_HT_SATURATE_08S, 2},
{26, 10, 3120, 0, 0, gScenarioBufferData116_HT_SATURATE_08S, 20, gScenarioKernelData116_HT_SATURATE_08S, 2},
{28, 10, 3360, 0, 0, gScenarioBufferData117_HT_SATURATE_08S, 20, gScenarioKernelData117_HT_SATURATE_08S, 2},
{30, 10, 3600, 0, 0, gScenarioBufferData118_HT_SATURATE_08S, 20, gScenarioKernelData118_HT_SATURATE_08S, 2},
{32, 10, 3840, 0, 0, gScenarioBufferData119_HT_SATURATE_08S, 20, gScenarioKernelData119_HT_SATURATE_08S, 2},
{1, 12, 144, 0, 0, gScenarioBufferData120_HT_SATURATE_08S, 20, gScenarioKernelData120_HT_SATURATE_08S, 2},
{2, 12, 288, 0, 0, gScenarioBufferData121_HT_SATURATE_08S, 20, gScenarioKernelData121_HT_SATURATE_08S, 2},
{3, 12, 432, 0, 0, gScenarioBufferData122_HT_SATURATE_08S, 20, gScenarioKernelData122_HT_SATURATE_08S, 2},
{4, 12, 576, 0, 0, gScenarioBufferData123_HT_SATURATE_08S, 20, gScenarioKernelData123_HT_SATURATE_08S, 2},
{5, 12, 720, 0, 0, gScenarioBufferData124_HT_SATURATE_08S, 20, gScenarioKernelData124_HT_SATURATE_08S, 2},
{6, 12, 864, 0, 0, gScenarioBufferData125_HT_SATURATE_08S, 20, gScenarioKernelData125_HT_SATURATE_08S, 2},
{7, 12, 1008, 0, 0, gScenarioBufferData126_HT_SATURATE_08S, 20, gScenarioKernelData126_HT_SATURATE_08S, 2},
{8, 12, 1152, 0, 0, gScenarioBufferData127_HT_SATURATE_08S, 20, gScenarioKernelData127_HT_SATURATE_08S, 2},
{10, 12, 1440, 0, 0, gScenarioBufferData128_HT_SATURATE_08S, 20, gScenarioKernelData128_HT_SATURATE_08S, 2},
{12, 12, 1728, 0, 0, gScenarioBufferData129_HT_SATURATE_08S, 20, gScenarioKernelData129_HT_SATURATE_08S, 2},
{14, 12, 2016, 0, 0, gScenarioBufferData130_HT_SATURATE_08S, 20, gScenarioKernelData130_HT_SATURATE_08S, 2},
{16, 12, 2304, 0, 0, gScenarioBufferData131_HT_SATURATE_08S, 20, gScenarioKernelData131_HT_SATURATE_08S, 2},
{18, 12, 2592, 0, 0, gScenarioBufferData132_HT_SATURATE_08S, 20, gScenarioKernelData132_HT_SATURATE_08S, 2},
{20, 12, 2880, 0, 0, gScenarioBufferData133_HT_SATURATE_08S, 20, gScenarioKernelData133_HT_SATURATE_08S, 2},
{22, 12, 3168, 0, 0, gScenarioBufferData134_HT_SATURATE_08S, 20, gScenarioKernelData134_HT_SATURATE_08S, 2},
{24, 12, 3456, 0, 0, gScenarioBufferData135_HT_SATURATE_08S, 20, gScenarioKernelData135_HT_SATURATE_08S, 2},
{26, 12, 3744, 0, 0, gScenarioBufferData136_HT_SATURATE_08S, 20, gScenarioKernelData136_HT_SATURATE_08S, 2},
{1, 14, 168, 0, 0, gScenarioBufferData137_HT_SATURATE_08S, 20, gScenarioKernelData137_HT_SATURATE_08S, 2},
{2, 14, 336, 0, 0, gScenarioBufferData138_HT_SATURATE_08S, 20, gScenarioKernelData138_HT_SATURATE_08S, 2},
{3, 14, 504, 0, 0, gScenarioBufferData139_HT_SATURATE_08S, 20, gScenarioKernelData139_HT_SATURATE_08S, 2},
{4, 14, 672, 0, 0, gScenarioBufferData140_HT_SATURATE_08S, 20, gScenarioKernelData140_HT_SATURATE_08S, 2},
{5, 14, 840, 0, 0, gScenarioBufferData141_HT_SATURATE_08S, 20, gScenarioKernelData141_HT_SATURATE_08S, 2},
{6, 14, 1008, 0, 0, gScenarioBufferData142_HT_SATURATE_08S, 20, gScenarioKernelData142_HT_SATURATE_08S, 2},
{7, 14, 1176, 0, 0, gScenarioBufferData143_HT_SATURATE_08S, 20, gScenarioKernelData143_HT_SATURATE_08S, 2},
{8, 14, 1344, 0, 0, gScenarioBufferData144_HT_SATURATE_08S, 20, gScenarioKernelData144_HT_SATURATE_08S, 2},
{10, 14, 1680, 0, 0, gScenarioBufferData145_HT_SATURATE_08S, 20, gScenarioKernelData145_HT_SATURATE_08S, 2},
{12, 14, 2016, 0, 0, gScenarioBufferData146_HT_SATURATE_08S, 20, gScenarioKernelData146_HT_SATURATE_08S, 2},
{14, 14, 2352, 0, 0, gScenarioBufferData147_HT_SATURATE_08S, 20, gScenarioKernelData147_HT_SATURATE_08S, 2},
{16, 14, 2688, 0, 0, gScenarioBufferData148_HT_SATURATE_08S, 20, gScenarioKernelData148_HT_SATURATE_08S, 2},
{18, 14, 3024, 0, 0, gScenarioBufferData149_HT_SATURATE_08S, 20, gScenarioKernelData149_HT_SATURATE_08S, 2},
{20, 14, 3360, 0, 0, gScenarioBufferData150_HT_SATURATE_08S, 20, gScenarioKernelData150_HT_SATURATE_08S, 2},
{22, 14, 3696, 0, 0, gScenarioBufferData151_HT_SATURATE_08S, 20, gScenarioKernelData151_HT_SATURATE_08S, 2},
{1, 16, 192, 0, 0, gScenarioBufferData152_HT_SATURATE_08S, 20, gScenarioKernelData152_HT_SATURATE_08S, 2},
{2, 16, 384, 0, 0, gScenarioBufferData153_HT_SATURATE_08S, 20, gScenarioKernelData153_HT_SATURATE_08S, 2},
{3, 16, 576, 0, 0, gScenarioBufferData154_HT_SATURATE_08S, 20, gScenarioKernelData154_HT_SATURATE_08S, 2},
{4, 16, 768, 0, 0, gScenarioBufferData155_HT_SATURATE_08S, 20, gScenarioKernelData155_HT_SATURATE_08S, 2},
{5, 16, 960, 0, 0, gScenarioBufferData156_HT_SATURATE_08S, 20, gScenarioKernelData156_HT_SATURATE_08S, 2},
{6, 16, 1152, 0, 0, gScenarioBufferData157_HT_SATURATE_08S, 20, gScenarioKernelData157_HT_SATURATE_08S, 2},
{7, 16, 1344, 0, 0, gScenarioBufferData158_HT_SATURATE_08S, 20, gScenarioKernelData158_HT_SATURATE_08S, 2},
{8, 16, 1536, 0, 0, gScenarioBufferData159_HT_SATURATE_08S, 20, gScenarioKernelData159_HT_SATURATE_08S, 2},
{10, 16, 1920, 0, 0, gScenarioBufferData160_HT_SATURATE_08S, 20, gScenarioKernelData160_HT_SATURATE_08S, 2},
{12, 16, 2304, 0, 0, gScenarioBufferData161_HT_SATURATE_08S, 20, gScenarioKernelData161_HT_SATURATE_08S, 2},
{14, 16, 2688, 0, 0, gScenarioBufferData162_HT_SATURATE_08S, 20, gScenarioKernelData162_HT_SATURATE_08S, 2},
{16, 16, 3072, 0, 0, gScenarioBufferData163_HT_SATURATE_08S, 20, gScenarioKernelData163_HT_SATURATE_08S, 2},
{18, 16, 3456, 0, 0, gScenarioBufferData164_HT_SATURATE_08S, 20, gScenarioKernelData164_HT_SATURATE_08S, 2},
{20, 16, 3840, 0, 0, gScenarioBufferData165_HT_SATURATE_08S, 20, gScenarioKernelData165_HT_SATURATE_08S, 2},
{1, 18, 216, 0, 0, gScenarioBufferData166_HT_SATURATE_08S, 20, gScenarioKernelData166_HT_SATURATE_08S, 2},
{2, 18, 432, 0, 0, gScenarioBufferData167_HT_SATURATE_08S, 20, gScenarioKernelData167_HT_SATURATE_08S, 2},
{3, 18, 648, 0, 0, gScenarioBufferData168_HT_SATURATE_08S, 20, gScenarioKernelData168_HT_SATURATE_08S, 2},
{4, 18, 864, 0, 0, gScenarioBufferData169_HT_SATURATE_08S, 20, gScenarioKernelData169_HT_SATURATE_08S, 2},
{5, 18, 1080, 0, 0, gScenarioBufferData170_HT_SATURATE_08S, 20, gScenarioKernelData170_HT_SATURATE_08S, 2},
{6, 18, 1296, 0, 0, gScenarioBufferData171_HT_SATURATE_08S, 20, gScenarioKernelData171_HT_SATURATE_08S, 2},
{7, 18, 1512, 0, 0, gScenarioBufferData172_HT_SATURATE_08S, 20, gScenarioKernelData172_HT_SATURATE_08S, 2},
{8, 18, 1728, 0, 0, gScenarioBufferData173_HT_SATURATE_08S, 20, gScenarioKernelData173_HT_SATURATE_08S, 2},
{10, 18, 2160, 0, 0, gScenarioBufferData174_HT_SATURATE_08S, 20, gScenarioKernelData174_HT_SATURATE_08S, 2},
{12, 18, 2592, 0, 0, gScenarioBufferData175_HT_SATURATE_08S, 20, gScenarioKernelData175_HT_SATURATE_08S, 2},
{14, 18, 3024, 0, 0, gScenarioBufferData176_HT_SATURATE_08S, 20, gScenarioKernelData176_HT_SATURATE_08S, 2},
{16, 18, 3456, 0, 0, gScenarioBufferData177_HT_SATURATE_08S, 20, gScenarioKernelData177_HT_SATURATE_08S, 2},
{1, 20, 240, 0, 0, gScenarioBufferData178_HT_SATURATE_08S, 20, gScenarioKernelData178_HT_SATURATE_08S, 2},
{2, 20, 480, 0, 0, gScenarioBufferData179_HT_SATURATE_08S, 20, gScenarioKernelData179_HT_SATURATE_08S, 2},
{3, 20, 720, 0, 0, gScenarioBufferData180_HT_SATURATE_08S, 20, gScenarioKernelData180_HT_SATURATE_08S, 2},
{4, 20, 960, 0, 0, gScenarioBufferData181_HT_SATURATE_08S, 20, gScenarioKernelData181_HT_SATURATE_08S, 2},
{5, 20, 1200, 0, 0, gScenarioBufferData182_HT_SATURATE_08S, 20, gScenarioKernelData182_HT_SATURATE_08S, 2},
{6, 20, 1440, 0, 0, gScenarioBufferData183_HT_SATURATE_08S, 20, gScenarioKernelData183_HT_SATURATE_08S, 2},
{7, 20, 1680, 0, 0, gScenarioBufferData184_HT_SATURATE_08S, 20, gScenarioKernelData184_HT_SATURATE_08S, 2},
{8, 20, 1920, 0, 0, gScenarioBufferData185_HT_SATURATE_08S, 20, gScenarioKernelData185_HT_SATURATE_08S, 2},
{10, 20, 2400, 0, 0, gScenarioBufferData186_HT_SATURATE_08S, 20, gScenarioKernelData186_HT_SATURATE_08S, 2},
{12, 20, 2880, 0, 0, gScenarioBufferData187_HT_SATURATE_08S, 20, gScenarioKernelData187_HT_SATURATE_08S, 2},
{14, 20, 3360, 0, 0, gScenarioBufferData188_HT_SATURATE_08S, 20, gScenarioKernelData188_HT_SATURATE_08S, 2},
{16, 20, 3840, 0, 0, gScenarioBufferData189_HT_SATURATE_08S, 20, gScenarioKernelData189_HT_SATURATE_08S, 2},
{1, 22, 264, 0, 0, gScenarioBufferData190_HT_SATURATE_08S, 20, gScenarioKernelData190_HT_SATURATE_08S, 2},
{2, 22, 528, 0, 0, gScenarioBufferData191_HT_SATURATE_08S, 20, gScenarioKernelData191_HT_SATURATE_08S, 2},
{3, 22, 792, 0, 0, gScenarioBufferData192_HT_SATURATE_08S, 20, gScenarioKernelData192_HT_SATURATE_08S, 2},
{4, 22, 1056, 0, 0, gScenarioBufferData193_HT_SATURATE_08S, 20, gScenarioKernelData193_HT_SATURATE_08S, 2},
{5, 22, 1320, 0, 0, gScenarioBufferData194_HT_SATURATE_08S, 20, gScenarioKernelData194_HT_SATURATE_08S, 2},
{6, 22, 1584, 0, 0, gScenarioBufferData195_HT_SATURATE_08S, 20, gScenarioKernelData195_HT_SATURATE_08S, 2},
{7, 22, 1848, 0, 0, gScenarioBufferData196_HT_SATURATE_08S, 20, gScenarioKernelData196_HT_SATURATE_08S, 2},
{8, 22, 2112, 0, 0, gScenarioBufferData197_HT_SATURATE_08S, 20, gScenarioKernelData197_HT_SATURATE_08S, 2},
{10, 22, 2640, 0, 0, gScenarioBufferData198_HT_SATURATE_08S, 20, gScenarioKernelData198_HT_SATURATE_08S, 2},
{12, 22, 3168, 0, 0, gScenarioBufferData199_HT_SATURATE_08S, 20, gScenarioKernelData199_HT_SATURATE_08S, 2},
{14, 22, 3696, 0, 0, gScenarioBufferData200_HT_SATURATE_08S, 20, gScenarioKernelData200_HT_SATURATE_08S, 2},
{1, 24, 288, 0, 0, gScenarioBufferData201_HT_SATURATE_08S, 20, gScenarioKernelData201_HT_SATURATE_08S, 2},
{2, 24, 576, 0, 0, gScenarioBufferData202_HT_SATURATE_08S, 20, gScenarioKernelData202_HT_SATURATE_08S, 2},
{3, 24, 864, 0, 0, gScenarioBufferData203_HT_SATURATE_08S, 20, gScenarioKernelData203_HT_SATURATE_08S, 2},
{4, 24, 1152, 0, 0, gScenarioBufferData204_HT_SATURATE_08S, 20, gScenarioKernelData204_HT_SATURATE_08S, 2},
{5, 24, 1440, 0, 0, gScenarioBufferData205_HT_SATURATE_08S, 20, gScenarioKernelData205_HT_SATURATE_08S, 2},
{6, 24, 1728, 0, 0, gScenarioBufferData206_HT_SATURATE_08S, 20, gScenarioKernelData206_HT_SATURATE_08S, 2},
{7, 24, 2016, 0, 0, gScenarioBufferData207_HT_SATURATE_08S, 20, gScenarioKernelData207_HT_SATURATE_08S, 2},
{8, 24, 2304, 0, 0, gScenarioBufferData208_HT_SATURATE_08S, 20, gScenarioKernelData208_HT_SATURATE_08S, 2},
{10, 24, 2880, 0, 0, gScenarioBufferData209_HT_SATURATE_08S, 20, gScenarioKernelData209_HT_SATURATE_08S, 2},
{12, 24, 3456, 0, 0, gScenarioBufferData210_HT_SATURATE_08S, 20, gScenarioKernelData210_HT_SATURATE_08S, 2},
{1, 26, 312, 0, 0, gScenarioBufferData211_HT_SATURATE_08S, 20, gScenarioKernelData211_HT_SATURATE_08S, 2},
{2, 26, 624, 0, 0, gScenarioBufferData212_HT_SATURATE_08S, 20, gScenarioKernelData212_HT_SATURATE_08S, 2},
{3, 26, 936, 0, 0, gScenarioBufferData213_HT_SATURATE_08S, 20, gScenarioKernelData213_HT_SATURATE_08S, 2},
{4, 26, 1248, 0, 0, gScenarioBufferData214_HT_SATURATE_08S, 20, gScenarioKernelData214_HT_SATURATE_08S, 2},
{5, 26, 1560, 0, 0, gScenarioBufferData215_HT_SATURATE_08S, 20, gScenarioKernelData215_HT_SATURATE_08S, 2},
{6, 26, 1872, 0, 0, gScenarioBufferData216_HT_SATURATE_08S, 20, gScenarioKernelData216_HT_SATURATE_08S, 2},
{7, 26, 2184, 0, 0, gScenarioBufferData217_HT_SATURATE_08S, 20, gScenarioKernelData217_HT_SATURATE_08S, 2},
{8, 26, 2496, 0, 0, gScenarioBufferData218_HT_SATURATE_08S, 20, gScenarioKernelData218_HT_SATURATE_08S, 2},
{10, 26, 3120, 0, 0, gScenarioBufferData219_HT_SATURATE_08S, 20, gScenarioKernelData219_HT_SATURATE_08S, 2},
{12, 26, 3744, 0, 0, gScenarioBufferData220_HT_SATURATE_08S, 20, gScenarioKernelData220_HT_SATURATE_08S, 2},
{1, 28, 336, 0, 0, gScenarioBufferData221_HT_SATURATE_08S, 20, gScenarioKernelData221_HT_SATURATE_08S, 2},
{2, 28, 672, 0, 0, gScenarioBufferData222_HT_SATURATE_08S, 20, gScenarioKernelData222_HT_SATURATE_08S, 2},
{3, 28, 1008, 0, 0, gScenarioBufferData223_HT_SATURATE_08S, 20, gScenarioKernelData223_HT_SATURATE_08S, 2},
{4, 28, 1344, 0, 0, gScenarioBufferData224_HT_SATURATE_08S, 20, gScenarioKernelData224_HT_SATURATE_08S, 2},
{5, 28, 1680, 0, 0, gScenarioBufferData225_HT_SATURATE_08S, 20, gScenarioKernelData225_HT_SATURATE_08S, 2},
{6, 28, 2016, 0, 0, gScenarioBufferData226_HT_SATURATE_08S, 20, gScenarioKernelData226_HT_SATURATE_08S, 2},
{7, 28, 2352, 0, 0, gScenarioBufferData227_HT_SATURATE_08S, 20, gScenarioKernelData227_HT_SATURATE_08S, 2},
{8, 28, 2688, 0, 0, gScenarioBufferData228_HT_SATURATE_08S, 20, gScenarioKernelData228_HT_SATURATE_08S, 2},
{10, 28, 3360, 0, 0, gScenarioBufferData229_HT_SATURATE_08S, 20, gScenarioKernelData229_HT_SATURATE_08S, 2},
{1, 30, 360, 0, 0, gScenarioBufferData230_HT_SATURATE_08S, 20, gScenarioKernelData230_HT_SATURATE_08S, 2},
{2, 30, 720, 0, 0, gScenarioBufferData231_HT_SATURATE_08S, 20, gScenarioKernelData231_HT_SATURATE_08S, 2},
{3, 30, 1080, 0, 0, gScenarioBufferData232_HT_SATURATE_08S, 20, gScenarioKernelData232_HT_SATURATE_08S, 2},
{4, 30, 1440, 0, 0, gScenarioBufferData233_HT_SATURATE_08S, 20, gScenarioKernelData233_HT_SATURATE_08S, 2},
{5, 30, 1800, 0, 0, gScenarioBufferData234_HT_SATURATE_08S, 20, gScenarioKernelData234_HT_SATURATE_08S, 2},
{6, 30, 2160, 0, 0, gScenarioBufferData235_HT_SATURATE_08S, 20, gScenarioKernelData235_HT_SATURATE_08S, 2},
{7, 30, 2520, 0, 0, gScenarioBufferData236_HT_SATURATE_08S, 20, gScenarioKernelData236_HT_SATURATE_08S, 2},
{8, 30, 2880, 0, 0, gScenarioBufferData237_HT_SATURATE_08S, 20, gScenarioKernelData237_HT_SATURATE_08S, 2},
{10, 30, 3600, 0, 0, gScenarioBufferData238_HT_SATURATE_08S, 20, gScenarioKernelData238_HT_SATURATE_08S, 2},
{1, 32, 384, 0, 0, gScenarioBufferData239_HT_SATURATE_08S, 20, gScenarioKernelData239_HT_SATURATE_08S, 2},
{2, 32, 768, 0, 0, gScenarioBufferData240_HT_SATURATE_08S, 20, gScenarioKernelData240_HT_SATURATE_08S, 2},
{3, 32, 1152, 0, 0, gScenarioBufferData241_HT_SATURATE_08S, 20, gScenarioKernelData241_HT_SATURATE_08S, 2},
{4, 32, 1536, 0, 0, gScenarioBufferData242_HT_SATURATE_08S, 20, gScenarioKernelData242_HT_SATURATE_08S, 2},
{5, 32, 1920, 0, 0, gScenarioBufferData243_HT_SATURATE_08S, 20, gScenarioKernelData243_HT_SATURATE_08S, 2},
{6, 32, 2304, 0, 0, gScenarioBufferData244_HT_SATURATE_08S, 20, gScenarioKernelData244_HT_SATURATE_08S, 2},
{7, 32, 2688, 0, 0, gScenarioBufferData245_HT_SATURATE_08S, 20, gScenarioKernelData245_HT_SATURATE_08S, 2},
{8, 32, 3072, 0, 0, gScenarioBufferData246_HT_SATURATE_08S, 20, gScenarioKernelData246_HT_SATURATE_08S, 2},
{10, 32, 3840, 0, 0, gScenarioBufferData247_HT_SATURATE_08S, 20, gScenarioKernelData247_HT_SATURATE_08S, 2}
};

static acf_scenario_list gScenarioList_HT_SATURATE_08S = {
248, //number of scenarios
gScenarioArray_HT_SATURATE_08S};
//**************************************************************

class HT_SATURATE_08S : public ACF_Process_APU
{
public:
   HT_SATURATE_08S(int32_t apex_id = 0) : ACF_Process_APU(apex_id)
   {} 

   int32_t Initialize()
   {
      int32_t lRetVal = 0;

      if (!Initialized()) //initialization steps that only need to occur once
      {
         SetProcessIdentifier("HT_SATURATE_08S");
         SetApuLoadInfo(HT_SATURATE_08S_LOAD_SEGMENTS,
                        HT_SATURATE_08S_LOAD_PMEM, HT_SATURATE_08S_LOAD_PMEM_SIZE,
                        HT_SATURATE_08S_LOAD_DMEM, HT_SATURATE_08S_LOAD_DMEM_SIZE,
                        0, 0); //assuming _LOAD_CMEM does not exist

         //***NOTE: the order in which the following ports are added is meaningful; do not change!

         AddPort("INPUT_0", ICP_DATATYPE_16S, 1, 1, 2, 1, 0, 0, 0, 0, 0, 0, 0, 0x0);
         AddPort("OUTPUT_0", ICP_DATATYPE_08S, 1, 1, 2, 1, 1, 0, 0, 0, 0, 0, 1);

         CfgScenarios(&gScenarioList_HT_SATURATE_08S);

         FlagAsInitialized();
      }

      lRetVal = SelectApuConfiguration(mApuCfg, mApexId); //by default mApuCfg = ACF_APU_CFG__APEX0_DEFAULT and mApexId = 0

      return lRetVal;
   }
};

#endif //_ACF_PROCESS_APU_HT_SATURATE_08S
