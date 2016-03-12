#ifndef _ACF_PROCESS_APU_HT_CENTRALDY_3X3_16S
#define _ACF_PROCESS_APU_HT_CENTRALDY_3X3_16S

#include <acf_process_apu.h>
#include <HT_CENTRALDY_3X3_16S_APU_LOAD.h> //APU load associated with this process
#include <stdint.h>


//SCENARIO LIST*************************************************
static acf_scenario_buffer_data gScenarioBufferData0_HT_CENTRALDY_3X3_16S[] = {{4, 1, 4, 0, 0x2211}, {4, 1, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData1_HT_CENTRALDY_3X3_16S[] = {{8, 1, 4, 0, 0x2211}, {8, 1, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData2_HT_CENTRALDY_3X3_16S[] = {{12, 1, 4, 0, 0x2211}, {12, 1, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData3_HT_CENTRALDY_3X3_16S[] = {{16, 1, 4, 0, 0x2211}, {16, 1, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData4_HT_CENTRALDY_3X3_16S[] = {{20, 1, 4, 0, 0x2211}, {20, 1, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData5_HT_CENTRALDY_3X3_16S[] = {{24, 1, 4, 0, 0x2211}, {24, 1, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData6_HT_CENTRALDY_3X3_16S[] = {{28, 1, 4, 0, 0x2211}, {28, 1, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData7_HT_CENTRALDY_3X3_16S[] = {{32, 1, 4, 0, 0x2211}, {32, 1, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData8_HT_CENTRALDY_3X3_16S[] = {{40, 1, 4, 0, 0x2211}, {40, 1, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData9_HT_CENTRALDY_3X3_16S[] = {{48, 1, 4, 0, 0x2211}, {48, 1, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData10_HT_CENTRALDY_3X3_16S[] = {{56, 1, 4, 0, 0x2211}, {56, 1, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData11_HT_CENTRALDY_3X3_16S[] = {{64, 1, 4, 0, 0x2211}, {64, 1, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData12_HT_CENTRALDY_3X3_16S[] = {{4, 2, 4, 0, 0x2211}, {4, 2, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData13_HT_CENTRALDY_3X3_16S[] = {{8, 2, 4, 0, 0x2211}, {8, 2, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData14_HT_CENTRALDY_3X3_16S[] = {{12, 2, 4, 0, 0x2211}, {12, 2, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData15_HT_CENTRALDY_3X3_16S[] = {{16, 2, 4, 0, 0x2211}, {16, 2, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData16_HT_CENTRALDY_3X3_16S[] = {{20, 2, 4, 0, 0x2211}, {20, 2, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData17_HT_CENTRALDY_3X3_16S[] = {{24, 2, 4, 0, 0x2211}, {24, 2, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData18_HT_CENTRALDY_3X3_16S[] = {{28, 2, 4, 0, 0x2211}, {28, 2, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData19_HT_CENTRALDY_3X3_16S[] = {{32, 2, 4, 0, 0x2211}, {32, 2, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData20_HT_CENTRALDY_3X3_16S[] = {{40, 2, 4, 0, 0x2211}, {40, 2, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData21_HT_CENTRALDY_3X3_16S[] = {{48, 2, 4, 0, 0x2211}, {48, 2, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData22_HT_CENTRALDY_3X3_16S[] = {{56, 2, 4, 0, 0x2211}, {56, 2, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData23_HT_CENTRALDY_3X3_16S[] = {{64, 2, 4, 0, 0x2211}, {64, 2, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData24_HT_CENTRALDY_3X3_16S[] = {{4, 4, 4, 0, 0x2211}, {4, 4, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData25_HT_CENTRALDY_3X3_16S[] = {{8, 4, 4, 0, 0x2211}, {8, 4, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData26_HT_CENTRALDY_3X3_16S[] = {{12, 4, 4, 0, 0x2211}, {12, 4, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData27_HT_CENTRALDY_3X3_16S[] = {{16, 4, 4, 0, 0x2211}, {16, 4, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData28_HT_CENTRALDY_3X3_16S[] = {{20, 4, 4, 0, 0x2211}, {20, 4, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData29_HT_CENTRALDY_3X3_16S[] = {{24, 4, 4, 0, 0x2211}, {24, 4, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData30_HT_CENTRALDY_3X3_16S[] = {{28, 4, 4, 0, 0x2211}, {28, 4, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData31_HT_CENTRALDY_3X3_16S[] = {{32, 4, 4, 0, 0x2211}, {32, 4, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData32_HT_CENTRALDY_3X3_16S[] = {{40, 4, 4, 0, 0x2211}, {40, 4, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData33_HT_CENTRALDY_3X3_16S[] = {{48, 4, 4, 0, 0x2211}, {48, 4, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData34_HT_CENTRALDY_3X3_16S[] = {{56, 4, 4, 0, 0x2211}, {56, 4, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData35_HT_CENTRALDY_3X3_16S[] = {{64, 4, 4, 0, 0x2211}, {64, 4, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData36_HT_CENTRALDY_3X3_16S[] = {{4, 6, 4, 0, 0x2211}, {4, 6, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData37_HT_CENTRALDY_3X3_16S[] = {{8, 6, 4, 0, 0x2211}, {8, 6, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData38_HT_CENTRALDY_3X3_16S[] = {{12, 6, 4, 0, 0x2211}, {12, 6, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData39_HT_CENTRALDY_3X3_16S[] = {{16, 6, 4, 0, 0x2211}, {16, 6, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData40_HT_CENTRALDY_3X3_16S[] = {{20, 6, 4, 0, 0x2211}, {20, 6, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData41_HT_CENTRALDY_3X3_16S[] = {{24, 6, 4, 0, 0x2211}, {24, 6, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData42_HT_CENTRALDY_3X3_16S[] = {{28, 6, 4, 0, 0x2211}, {28, 6, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData43_HT_CENTRALDY_3X3_16S[] = {{32, 6, 4, 0, 0x2211}, {32, 6, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData44_HT_CENTRALDY_3X3_16S[] = {{40, 6, 4, 0, 0x2211}, {40, 6, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData45_HT_CENTRALDY_3X3_16S[] = {{48, 6, 4, 0, 0x2211}, {48, 6, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData46_HT_CENTRALDY_3X3_16S[] = {{56, 6, 4, 0, 0x2211}, {56, 6, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData47_HT_CENTRALDY_3X3_16S[] = {{64, 6, 4, 0, 0x2211}, {64, 6, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData48_HT_CENTRALDY_3X3_16S[] = {{4, 8, 4, 0, 0x2211}, {4, 8, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData49_HT_CENTRALDY_3X3_16S[] = {{8, 8, 4, 0, 0x2211}, {8, 8, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData50_HT_CENTRALDY_3X3_16S[] = {{12, 8, 4, 0, 0x2211}, {12, 8, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData51_HT_CENTRALDY_3X3_16S[] = {{16, 8, 4, 0, 0x2211}, {16, 8, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData52_HT_CENTRALDY_3X3_16S[] = {{20, 8, 4, 0, 0x2211}, {20, 8, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData53_HT_CENTRALDY_3X3_16S[] = {{24, 8, 4, 0, 0x2211}, {24, 8, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData54_HT_CENTRALDY_3X3_16S[] = {{28, 8, 4, 0, 0x2211}, {28, 8, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData55_HT_CENTRALDY_3X3_16S[] = {{32, 8, 4, 0, 0x2211}, {32, 8, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData56_HT_CENTRALDY_3X3_16S[] = {{40, 8, 4, 0, 0x2211}, {40, 8, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData57_HT_CENTRALDY_3X3_16S[] = {{48, 8, 4, 0, 0x2211}, {48, 8, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData58_HT_CENTRALDY_3X3_16S[] = {{56, 8, 4, 0, 0x2211}, {56, 8, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData59_HT_CENTRALDY_3X3_16S[] = {{4, 10, 4, 0, 0x2211}, {4, 10, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData60_HT_CENTRALDY_3X3_16S[] = {{8, 10, 4, 0, 0x2211}, {8, 10, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData61_HT_CENTRALDY_3X3_16S[] = {{12, 10, 4, 0, 0x2211}, {12, 10, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData62_HT_CENTRALDY_3X3_16S[] = {{16, 10, 4, 0, 0x2211}, {16, 10, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData63_HT_CENTRALDY_3X3_16S[] = {{20, 10, 4, 0, 0x2211}, {20, 10, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData64_HT_CENTRALDY_3X3_16S[] = {{24, 10, 4, 0, 0x2211}, {24, 10, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData65_HT_CENTRALDY_3X3_16S[] = {{28, 10, 4, 0, 0x2211}, {28, 10, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData66_HT_CENTRALDY_3X3_16S[] = {{32, 10, 4, 0, 0x2211}, {32, 10, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData67_HT_CENTRALDY_3X3_16S[] = {{40, 10, 4, 0, 0x2211}, {40, 10, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData68_HT_CENTRALDY_3X3_16S[] = {{4, 12, 4, 0, 0x2211}, {4, 12, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData69_HT_CENTRALDY_3X3_16S[] = {{8, 12, 4, 0, 0x2211}, {8, 12, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData70_HT_CENTRALDY_3X3_16S[] = {{12, 12, 4, 0, 0x2211}, {12, 12, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData71_HT_CENTRALDY_3X3_16S[] = {{16, 12, 4, 0, 0x2211}, {16, 12, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData72_HT_CENTRALDY_3X3_16S[] = {{20, 12, 4, 0, 0x2211}, {20, 12, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData73_HT_CENTRALDY_3X3_16S[] = {{24, 12, 4, 0, 0x2211}, {24, 12, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData74_HT_CENTRALDY_3X3_16S[] = {{28, 12, 4, 0, 0x2211}, {28, 12, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData75_HT_CENTRALDY_3X3_16S[] = {{32, 12, 4, 0, 0x2211}, {32, 12, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData76_HT_CENTRALDY_3X3_16S[] = {{4, 14, 4, 0, 0x2211}, {4, 14, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData77_HT_CENTRALDY_3X3_16S[] = {{8, 14, 4, 0, 0x2211}, {8, 14, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData78_HT_CENTRALDY_3X3_16S[] = {{12, 14, 4, 0, 0x2211}, {12, 14, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData79_HT_CENTRALDY_3X3_16S[] = {{16, 14, 4, 0, 0x2211}, {16, 14, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData80_HT_CENTRALDY_3X3_16S[] = {{20, 14, 4, 0, 0x2211}, {20, 14, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData81_HT_CENTRALDY_3X3_16S[] = {{24, 14, 4, 0, 0x2211}, {24, 14, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData82_HT_CENTRALDY_3X3_16S[] = {{28, 14, 4, 0, 0x2211}, {28, 14, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData83_HT_CENTRALDY_3X3_16S[] = {{4, 16, 4, 0, 0x2211}, {4, 16, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData84_HT_CENTRALDY_3X3_16S[] = {{8, 16, 4, 0, 0x2211}, {8, 16, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData85_HT_CENTRALDY_3X3_16S[] = {{12, 16, 4, 0, 0x2211}, {12, 16, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData86_HT_CENTRALDY_3X3_16S[] = {{16, 16, 4, 0, 0x2211}, {16, 16, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData87_HT_CENTRALDY_3X3_16S[] = {{20, 16, 4, 0, 0x2211}, {20, 16, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData88_HT_CENTRALDY_3X3_16S[] = {{24, 16, 4, 0, 0x2211}, {24, 16, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData89_HT_CENTRALDY_3X3_16S[] = {{4, 18, 4, 0, 0x2211}, {4, 18, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData90_HT_CENTRALDY_3X3_16S[] = {{8, 18, 4, 0, 0x2211}, {8, 18, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData91_HT_CENTRALDY_3X3_16S[] = {{12, 18, 4, 0, 0x2211}, {12, 18, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData92_HT_CENTRALDY_3X3_16S[] = {{16, 18, 4, 0, 0x2211}, {16, 18, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData93_HT_CENTRALDY_3X3_16S[] = {{20, 18, 4, 0, 0x2211}, {20, 18, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData94_HT_CENTRALDY_3X3_16S[] = {{24, 18, 4, 0, 0x2211}, {24, 18, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData95_HT_CENTRALDY_3X3_16S[] = {{4, 20, 4, 0, 0x2211}, {4, 20, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData96_HT_CENTRALDY_3X3_16S[] = {{8, 20, 4, 0, 0x2211}, {8, 20, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData97_HT_CENTRALDY_3X3_16S[] = {{12, 20, 4, 0, 0x2211}, {12, 20, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData98_HT_CENTRALDY_3X3_16S[] = {{16, 20, 4, 0, 0x2211}, {16, 20, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData99_HT_CENTRALDY_3X3_16S[] = {{20, 20, 4, 0, 0x2211}, {20, 20, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData100_HT_CENTRALDY_3X3_16S[] = {{4, 22, 4, 0, 0x2211}, {4, 22, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData101_HT_CENTRALDY_3X3_16S[] = {{8, 22, 4, 0, 0x2211}, {8, 22, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData102_HT_CENTRALDY_3X3_16S[] = {{12, 22, 4, 0, 0x2211}, {12, 22, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData103_HT_CENTRALDY_3X3_16S[] = {{16, 22, 4, 0, 0x2211}, {16, 22, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData104_HT_CENTRALDY_3X3_16S[] = {{4, 24, 4, 0, 0x2211}, {4, 24, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData105_HT_CENTRALDY_3X3_16S[] = {{8, 24, 4, 0, 0x2211}, {8, 24, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData106_HT_CENTRALDY_3X3_16S[] = {{12, 24, 4, 0, 0x2211}, {12, 24, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData107_HT_CENTRALDY_3X3_16S[] = {{16, 24, 4, 0, 0x2211}, {16, 24, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData108_HT_CENTRALDY_3X3_16S[] = {{4, 26, 4, 0, 0x2211}, {4, 26, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData109_HT_CENTRALDY_3X3_16S[] = {{8, 26, 4, 0, 0x2211}, {8, 26, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData110_HT_CENTRALDY_3X3_16S[] = {{12, 26, 4, 0, 0x2211}, {12, 26, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData111_HT_CENTRALDY_3X3_16S[] = {{16, 26, 4, 0, 0x2211}, {16, 26, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData112_HT_CENTRALDY_3X3_16S[] = {{4, 28, 4, 0, 0x2211}, {4, 28, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData113_HT_CENTRALDY_3X3_16S[] = {{8, 28, 4, 0, 0x2211}, {8, 28, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData114_HT_CENTRALDY_3X3_16S[] = {{12, 28, 4, 0, 0x2211}, {12, 28, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData115_HT_CENTRALDY_3X3_16S[] = {{4, 30, 4, 0, 0x2211}, {4, 30, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData116_HT_CENTRALDY_3X3_16S[] = {{8, 30, 4, 0, 0x2211}, {8, 30, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData117_HT_CENTRALDY_3X3_16S[] = {{12, 30, 4, 0, 0x2211}, {12, 30, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData118_HT_CENTRALDY_3X3_16S[] = {{4, 32, 4, 0, 0x2211}, {4, 32, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData119_HT_CENTRALDY_3X3_16S[] = {{8, 32, 4, 0, 0x2211}, {8, 32, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};
static acf_scenario_buffer_data gScenarioBufferData120_HT_CENTRALDY_3X3_16S[] = {{12, 32, 4, 0, 0x2211}, {12, 32, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};

static acf_scenario_kernel_data gScenarioKernelData0_HT_CENTRALDY_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData1_HT_CENTRALDY_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData2_HT_CENTRALDY_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData3_HT_CENTRALDY_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData4_HT_CENTRALDY_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData5_HT_CENTRALDY_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData6_HT_CENTRALDY_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData7_HT_CENTRALDY_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData8_HT_CENTRALDY_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData9_HT_CENTRALDY_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData10_HT_CENTRALDY_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData11_HT_CENTRALDY_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData12_HT_CENTRALDY_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData13_HT_CENTRALDY_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData14_HT_CENTRALDY_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData15_HT_CENTRALDY_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData16_HT_CENTRALDY_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData17_HT_CENTRALDY_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData18_HT_CENTRALDY_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData19_HT_CENTRALDY_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData20_HT_CENTRALDY_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData21_HT_CENTRALDY_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData22_HT_CENTRALDY_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData23_HT_CENTRALDY_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData24_HT_CENTRALDY_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData25_HT_CENTRALDY_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData26_HT_CENTRALDY_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData27_HT_CENTRALDY_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData28_HT_CENTRALDY_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData29_HT_CENTRALDY_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData30_HT_CENTRALDY_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData31_HT_CENTRALDY_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData32_HT_CENTRALDY_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData33_HT_CENTRALDY_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData34_HT_CENTRALDY_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData35_HT_CENTRALDY_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData36_HT_CENTRALDY_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData37_HT_CENTRALDY_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData38_HT_CENTRALDY_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData39_HT_CENTRALDY_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData40_HT_CENTRALDY_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData41_HT_CENTRALDY_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData42_HT_CENTRALDY_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData43_HT_CENTRALDY_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData44_HT_CENTRALDY_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData45_HT_CENTRALDY_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData46_HT_CENTRALDY_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData47_HT_CENTRALDY_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData48_HT_CENTRALDY_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData49_HT_CENTRALDY_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData50_HT_CENTRALDY_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData51_HT_CENTRALDY_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData52_HT_CENTRALDY_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData53_HT_CENTRALDY_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData54_HT_CENTRALDY_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData55_HT_CENTRALDY_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData56_HT_CENTRALDY_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData57_HT_CENTRALDY_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData58_HT_CENTRALDY_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData59_HT_CENTRALDY_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData60_HT_CENTRALDY_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData61_HT_CENTRALDY_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData62_HT_CENTRALDY_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData63_HT_CENTRALDY_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData64_HT_CENTRALDY_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData65_HT_CENTRALDY_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData66_HT_CENTRALDY_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData67_HT_CENTRALDY_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData68_HT_CENTRALDY_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData69_HT_CENTRALDY_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData70_HT_CENTRALDY_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData71_HT_CENTRALDY_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData72_HT_CENTRALDY_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData73_HT_CENTRALDY_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData74_HT_CENTRALDY_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData75_HT_CENTRALDY_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData76_HT_CENTRALDY_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData77_HT_CENTRALDY_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData78_HT_CENTRALDY_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData79_HT_CENTRALDY_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData80_HT_CENTRALDY_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData81_HT_CENTRALDY_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData82_HT_CENTRALDY_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData83_HT_CENTRALDY_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData84_HT_CENTRALDY_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData85_HT_CENTRALDY_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData86_HT_CENTRALDY_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData87_HT_CENTRALDY_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData88_HT_CENTRALDY_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData89_HT_CENTRALDY_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData90_HT_CENTRALDY_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData91_HT_CENTRALDY_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData92_HT_CENTRALDY_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData93_HT_CENTRALDY_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData94_HT_CENTRALDY_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData95_HT_CENTRALDY_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData96_HT_CENTRALDY_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData97_HT_CENTRALDY_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData98_HT_CENTRALDY_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData99_HT_CENTRALDY_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData100_HT_CENTRALDY_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData101_HT_CENTRALDY_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData102_HT_CENTRALDY_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData103_HT_CENTRALDY_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData104_HT_CENTRALDY_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData105_HT_CENTRALDY_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData106_HT_CENTRALDY_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData107_HT_CENTRALDY_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData108_HT_CENTRALDY_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData109_HT_CENTRALDY_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData110_HT_CENTRALDY_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData111_HT_CENTRALDY_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData112_HT_CENTRALDY_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData113_HT_CENTRALDY_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData114_HT_CENTRALDY_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData115_HT_CENTRALDY_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData116_HT_CENTRALDY_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData117_HT_CENTRALDY_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData118_HT_CENTRALDY_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData119_HT_CENTRALDY_3X3_16S[] = {{1}};
static acf_scenario_kernel_data gScenarioKernelData120_HT_CENTRALDY_3X3_16S[] = {{1}};

static acf_scenario gScenarioArray_HT_CENTRALDY_3X3_16S[] = {
{1, 1, 64, 24, 1, gScenarioBufferData0_HT_CENTRALDY_3X3_16S, 50, gScenarioKernelData0_HT_CENTRALDY_3X3_16S, 2},
{2, 1, 104, 24, 1, gScenarioBufferData1_HT_CENTRALDY_3X3_16S, 50, gScenarioKernelData1_HT_CENTRALDY_3X3_16S, 2},
{3, 1, 144, 24, 1, gScenarioBufferData2_HT_CENTRALDY_3X3_16S, 50, gScenarioKernelData2_HT_CENTRALDY_3X3_16S, 2},
{4, 1, 184, 24, 1, gScenarioBufferData3_HT_CENTRALDY_3X3_16S, 50, gScenarioKernelData3_HT_CENTRALDY_3X3_16S, 2},
{5, 1, 224, 24, 1, gScenarioBufferData4_HT_CENTRALDY_3X3_16S, 50, gScenarioKernelData4_HT_CENTRALDY_3X3_16S, 2},
{6, 1, 264, 24, 1, gScenarioBufferData5_HT_CENTRALDY_3X3_16S, 50, gScenarioKernelData5_HT_CENTRALDY_3X3_16S, 2},
{7, 1, 304, 24, 1, gScenarioBufferData6_HT_CENTRALDY_3X3_16S, 50, gScenarioKernelData6_HT_CENTRALDY_3X3_16S, 2},
{8, 1, 344, 24, 1, gScenarioBufferData7_HT_CENTRALDY_3X3_16S, 50, gScenarioKernelData7_HT_CENTRALDY_3X3_16S, 2},
{10, 1, 424, 24, 1, gScenarioBufferData8_HT_CENTRALDY_3X3_16S, 50, gScenarioKernelData8_HT_CENTRALDY_3X3_16S, 2},
{12, 1, 504, 24, 1, gScenarioBufferData9_HT_CENTRALDY_3X3_16S, 50, gScenarioKernelData9_HT_CENTRALDY_3X3_16S, 2},
{14, 1, 584, 24, 1, gScenarioBufferData10_HT_CENTRALDY_3X3_16S, 50, gScenarioKernelData10_HT_CENTRALDY_3X3_16S, 2},
{16, 1, 664, 24, 1, gScenarioBufferData11_HT_CENTRALDY_3X3_16S, 50, gScenarioKernelData11_HT_CENTRALDY_3X3_16S, 2},
{1, 2, 112, 24, 1, gScenarioBufferData12_HT_CENTRALDY_3X3_16S, 50, gScenarioKernelData12_HT_CENTRALDY_3X3_16S, 2},
{2, 2, 184, 24, 1, gScenarioBufferData13_HT_CENTRALDY_3X3_16S, 50, gScenarioKernelData13_HT_CENTRALDY_3X3_16S, 2},
{3, 2, 256, 24, 1, gScenarioBufferData14_HT_CENTRALDY_3X3_16S, 50, gScenarioKernelData14_HT_CENTRALDY_3X3_16S, 2},
{4, 2, 328, 24, 1, gScenarioBufferData15_HT_CENTRALDY_3X3_16S, 50, gScenarioKernelData15_HT_CENTRALDY_3X3_16S, 2},
{5, 2, 400, 24, 1, gScenarioBufferData16_HT_CENTRALDY_3X3_16S, 50, gScenarioKernelData16_HT_CENTRALDY_3X3_16S, 2},
{6, 2, 472, 24, 1, gScenarioBufferData17_HT_CENTRALDY_3X3_16S, 50, gScenarioKernelData17_HT_CENTRALDY_3X3_16S, 2},
{7, 2, 544, 24, 1, gScenarioBufferData18_HT_CENTRALDY_3X3_16S, 50, gScenarioKernelData18_HT_CENTRALDY_3X3_16S, 2},
{8, 2, 616, 24, 1, gScenarioBufferData19_HT_CENTRALDY_3X3_16S, 50, gScenarioKernelData19_HT_CENTRALDY_3X3_16S, 2},
{10, 2, 760, 24, 1, gScenarioBufferData20_HT_CENTRALDY_3X3_16S, 50, gScenarioKernelData20_HT_CENTRALDY_3X3_16S, 2},
{12, 2, 904, 24, 1, gScenarioBufferData21_HT_CENTRALDY_3X3_16S, 50, gScenarioKernelData21_HT_CENTRALDY_3X3_16S, 2},
{14, 2, 1048, 24, 1, gScenarioBufferData22_HT_CENTRALDY_3X3_16S, 50, gScenarioKernelData22_HT_CENTRALDY_3X3_16S, 2},
{16, 2, 1192, 24, 1, gScenarioBufferData23_HT_CENTRALDY_3X3_16S, 50, gScenarioKernelData23_HT_CENTRALDY_3X3_16S, 2},
{1, 4, 208, 24, 1, gScenarioBufferData24_HT_CENTRALDY_3X3_16S, 50, gScenarioKernelData24_HT_CENTRALDY_3X3_16S, 2},
{2, 4, 344, 24, 1, gScenarioBufferData25_HT_CENTRALDY_3X3_16S, 50, gScenarioKernelData25_HT_CENTRALDY_3X3_16S, 2},
{3, 4, 480, 24, 1, gScenarioBufferData26_HT_CENTRALDY_3X3_16S, 50, gScenarioKernelData26_HT_CENTRALDY_3X3_16S, 2},
{4, 4, 616, 24, 1, gScenarioBufferData27_HT_CENTRALDY_3X3_16S, 50, gScenarioKernelData27_HT_CENTRALDY_3X3_16S, 2},
{5, 4, 752, 24, 1, gScenarioBufferData28_HT_CENTRALDY_3X3_16S, 50, gScenarioKernelData28_HT_CENTRALDY_3X3_16S, 2},
{6, 4, 888, 24, 1, gScenarioBufferData29_HT_CENTRALDY_3X3_16S, 50, gScenarioKernelData29_HT_CENTRALDY_3X3_16S, 2},
{7, 4, 1024, 24, 1, gScenarioBufferData30_HT_CENTRALDY_3X3_16S, 50, gScenarioKernelData30_HT_CENTRALDY_3X3_16S, 2},
{8, 4, 1160, 24, 1, gScenarioBufferData31_HT_CENTRALDY_3X3_16S, 50, gScenarioKernelData31_HT_CENTRALDY_3X3_16S, 2},
{10, 4, 1432, 24, 1, gScenarioBufferData32_HT_CENTRALDY_3X3_16S, 50, gScenarioKernelData32_HT_CENTRALDY_3X3_16S, 2},
{12, 4, 1704, 24, 1, gScenarioBufferData33_HT_CENTRALDY_3X3_16S, 50, gScenarioKernelData33_HT_CENTRALDY_3X3_16S, 2},
{14, 4, 1976, 24, 1, gScenarioBufferData34_HT_CENTRALDY_3X3_16S, 50, gScenarioKernelData34_HT_CENTRALDY_3X3_16S, 2},
{16, 4, 2248, 24, 1, gScenarioBufferData35_HT_CENTRALDY_3X3_16S, 50, gScenarioKernelData35_HT_CENTRALDY_3X3_16S, 2},
{1, 6, 304, 24, 1, gScenarioBufferData36_HT_CENTRALDY_3X3_16S, 50, gScenarioKernelData36_HT_CENTRALDY_3X3_16S, 2},
{2, 6, 504, 24, 1, gScenarioBufferData37_HT_CENTRALDY_3X3_16S, 50, gScenarioKernelData37_HT_CENTRALDY_3X3_16S, 2},
{3, 6, 704, 24, 1, gScenarioBufferData38_HT_CENTRALDY_3X3_16S, 50, gScenarioKernelData38_HT_CENTRALDY_3X3_16S, 2},
{4, 6, 904, 24, 1, gScenarioBufferData39_HT_CENTRALDY_3X3_16S, 50, gScenarioKernelData39_HT_CENTRALDY_3X3_16S, 2},
{5, 6, 1104, 24, 1, gScenarioBufferData40_HT_CENTRALDY_3X3_16S, 50, gScenarioKernelData40_HT_CENTRALDY_3X3_16S, 2},
{6, 6, 1304, 24, 1, gScenarioBufferData41_HT_CENTRALDY_3X3_16S, 50, gScenarioKernelData41_HT_CENTRALDY_3X3_16S, 2},
{7, 6, 1504, 24, 1, gScenarioBufferData42_HT_CENTRALDY_3X3_16S, 50, gScenarioKernelData42_HT_CENTRALDY_3X3_16S, 2},
{8, 6, 1704, 24, 1, gScenarioBufferData43_HT_CENTRALDY_3X3_16S, 50, gScenarioKernelData43_HT_CENTRALDY_3X3_16S, 2},
{10, 6, 2104, 24, 1, gScenarioBufferData44_HT_CENTRALDY_3X3_16S, 50, gScenarioKernelData44_HT_CENTRALDY_3X3_16S, 2},
{12, 6, 2504, 24, 1, gScenarioBufferData45_HT_CENTRALDY_3X3_16S, 50, gScenarioKernelData45_HT_CENTRALDY_3X3_16S, 2},
{14, 6, 2904, 24, 1, gScenarioBufferData46_HT_CENTRALDY_3X3_16S, 50, gScenarioKernelData46_HT_CENTRALDY_3X3_16S, 2},
{16, 6, 3304, 24, 1, gScenarioBufferData47_HT_CENTRALDY_3X3_16S, 50, gScenarioKernelData47_HT_CENTRALDY_3X3_16S, 2},
{1, 8, 400, 24, 1, gScenarioBufferData48_HT_CENTRALDY_3X3_16S, 50, gScenarioKernelData48_HT_CENTRALDY_3X3_16S, 2},
{2, 8, 664, 24, 1, gScenarioBufferData49_HT_CENTRALDY_3X3_16S, 50, gScenarioKernelData49_HT_CENTRALDY_3X3_16S, 2},
{3, 8, 928, 24, 1, gScenarioBufferData50_HT_CENTRALDY_3X3_16S, 50, gScenarioKernelData50_HT_CENTRALDY_3X3_16S, 2},
{4, 8, 1192, 24, 1, gScenarioBufferData51_HT_CENTRALDY_3X3_16S, 50, gScenarioKernelData51_HT_CENTRALDY_3X3_16S, 2},
{5, 8, 1456, 24, 1, gScenarioBufferData52_HT_CENTRALDY_3X3_16S, 50, gScenarioKernelData52_HT_CENTRALDY_3X3_16S, 2},
{6, 8, 1720, 24, 1, gScenarioBufferData53_HT_CENTRALDY_3X3_16S, 50, gScenarioKernelData53_HT_CENTRALDY_3X3_16S, 2},
{7, 8, 1984, 24, 1, gScenarioBufferData54_HT_CENTRALDY_3X3_16S, 50, gScenarioKernelData54_HT_CENTRALDY_3X3_16S, 2},
{8, 8, 2248, 24, 1, gScenarioBufferData55_HT_CENTRALDY_3X3_16S, 50, gScenarioKernelData55_HT_CENTRALDY_3X3_16S, 2},
{10, 8, 2776, 24, 1, gScenarioBufferData56_HT_CENTRALDY_3X3_16S, 50, gScenarioKernelData56_HT_CENTRALDY_3X3_16S, 2},
{12, 8, 3304, 24, 1, gScenarioBufferData57_HT_CENTRALDY_3X3_16S, 50, gScenarioKernelData57_HT_CENTRALDY_3X3_16S, 2},
{14, 8, 3832, 24, 1, gScenarioBufferData58_HT_CENTRALDY_3X3_16S, 50, gScenarioKernelData58_HT_CENTRALDY_3X3_16S, 2},
{1, 10, 496, 24, 1, gScenarioBufferData59_HT_CENTRALDY_3X3_16S, 50, gScenarioKernelData59_HT_CENTRALDY_3X3_16S, 2},
{2, 10, 824, 24, 1, gScenarioBufferData60_HT_CENTRALDY_3X3_16S, 50, gScenarioKernelData60_HT_CENTRALDY_3X3_16S, 2},
{3, 10, 1152, 24, 1, gScenarioBufferData61_HT_CENTRALDY_3X3_16S, 50, gScenarioKernelData61_HT_CENTRALDY_3X3_16S, 2},
{4, 10, 1480, 24, 1, gScenarioBufferData62_HT_CENTRALDY_3X3_16S, 50, gScenarioKernelData62_HT_CENTRALDY_3X3_16S, 2},
{5, 10, 1808, 24, 1, gScenarioBufferData63_HT_CENTRALDY_3X3_16S, 50, gScenarioKernelData63_HT_CENTRALDY_3X3_16S, 2},
{6, 10, 2136, 24, 1, gScenarioBufferData64_HT_CENTRALDY_3X3_16S, 50, gScenarioKernelData64_HT_CENTRALDY_3X3_16S, 2},
{7, 10, 2464, 24, 1, gScenarioBufferData65_HT_CENTRALDY_3X3_16S, 50, gScenarioKernelData65_HT_CENTRALDY_3X3_16S, 2},
{8, 10, 2792, 24, 1, gScenarioBufferData66_HT_CENTRALDY_3X3_16S, 50, gScenarioKernelData66_HT_CENTRALDY_3X3_16S, 2},
{10, 10, 3448, 24, 1, gScenarioBufferData67_HT_CENTRALDY_3X3_16S, 50, gScenarioKernelData67_HT_CENTRALDY_3X3_16S, 2},
{1, 12, 592, 24, 1, gScenarioBufferData68_HT_CENTRALDY_3X3_16S, 50, gScenarioKernelData68_HT_CENTRALDY_3X3_16S, 2},
{2, 12, 984, 24, 1, gScenarioBufferData69_HT_CENTRALDY_3X3_16S, 50, gScenarioKernelData69_HT_CENTRALDY_3X3_16S, 2},
{3, 12, 1376, 24, 1, gScenarioBufferData70_HT_CENTRALDY_3X3_16S, 50, gScenarioKernelData70_HT_CENTRALDY_3X3_16S, 2},
{4, 12, 1768, 24, 1, gScenarioBufferData71_HT_CENTRALDY_3X3_16S, 50, gScenarioKernelData71_HT_CENTRALDY_3X3_16S, 2},
{5, 12, 2160, 24, 1, gScenarioBufferData72_HT_CENTRALDY_3X3_16S, 50, gScenarioKernelData72_HT_CENTRALDY_3X3_16S, 2},
{6, 12, 2552, 24, 1, gScenarioBufferData73_HT_CENTRALDY_3X3_16S, 50, gScenarioKernelData73_HT_CENTRALDY_3X3_16S, 2},
{7, 12, 2944, 24, 1, gScenarioBufferData74_HT_CENTRALDY_3X3_16S, 50, gScenarioKernelData74_HT_CENTRALDY_3X3_16S, 2},
{8, 12, 3336, 24, 1, gScenarioBufferData75_HT_CENTRALDY_3X3_16S, 50, gScenarioKernelData75_HT_CENTRALDY_3X3_16S, 2},
{1, 14, 688, 24, 1, gScenarioBufferData76_HT_CENTRALDY_3X3_16S, 50, gScenarioKernelData76_HT_CENTRALDY_3X3_16S, 2},
{2, 14, 1144, 24, 1, gScenarioBufferData77_HT_CENTRALDY_3X3_16S, 50, gScenarioKernelData77_HT_CENTRALDY_3X3_16S, 2},
{3, 14, 1600, 24, 1, gScenarioBufferData78_HT_CENTRALDY_3X3_16S, 50, gScenarioKernelData78_HT_CENTRALDY_3X3_16S, 2},
{4, 14, 2056, 24, 1, gScenarioBufferData79_HT_CENTRALDY_3X3_16S, 50, gScenarioKernelData79_HT_CENTRALDY_3X3_16S, 2},
{5, 14, 2512, 24, 1, gScenarioBufferData80_HT_CENTRALDY_3X3_16S, 50, gScenarioKernelData80_HT_CENTRALDY_3X3_16S, 2},
{6, 14, 2968, 24, 1, gScenarioBufferData81_HT_CENTRALDY_3X3_16S, 50, gScenarioKernelData81_HT_CENTRALDY_3X3_16S, 2},
{7, 14, 3424, 24, 1, gScenarioBufferData82_HT_CENTRALDY_3X3_16S, 50, gScenarioKernelData82_HT_CENTRALDY_3X3_16S, 2},
{1, 16, 784, 24, 1, gScenarioBufferData83_HT_CENTRALDY_3X3_16S, 50, gScenarioKernelData83_HT_CENTRALDY_3X3_16S, 2},
{2, 16, 1304, 24, 1, gScenarioBufferData84_HT_CENTRALDY_3X3_16S, 50, gScenarioKernelData84_HT_CENTRALDY_3X3_16S, 2},
{3, 16, 1824, 24, 1, gScenarioBufferData85_HT_CENTRALDY_3X3_16S, 50, gScenarioKernelData85_HT_CENTRALDY_3X3_16S, 2},
{4, 16, 2344, 24, 1, gScenarioBufferData86_HT_CENTRALDY_3X3_16S, 50, gScenarioKernelData86_HT_CENTRALDY_3X3_16S, 2},
{5, 16, 2864, 24, 1, gScenarioBufferData87_HT_CENTRALDY_3X3_16S, 50, gScenarioKernelData87_HT_CENTRALDY_3X3_16S, 2},
{6, 16, 3384, 24, 1, gScenarioBufferData88_HT_CENTRALDY_3X3_16S, 50, gScenarioKernelData88_HT_CENTRALDY_3X3_16S, 2},
{1, 18, 880, 24, 1, gScenarioBufferData89_HT_CENTRALDY_3X3_16S, 50, gScenarioKernelData89_HT_CENTRALDY_3X3_16S, 2},
{2, 18, 1464, 24, 1, gScenarioBufferData90_HT_CENTRALDY_3X3_16S, 50, gScenarioKernelData90_HT_CENTRALDY_3X3_16S, 2},
{3, 18, 2048, 24, 1, gScenarioBufferData91_HT_CENTRALDY_3X3_16S, 50, gScenarioKernelData91_HT_CENTRALDY_3X3_16S, 2},
{4, 18, 2632, 24, 1, gScenarioBufferData92_HT_CENTRALDY_3X3_16S, 50, gScenarioKernelData92_HT_CENTRALDY_3X3_16S, 2},
{5, 18, 3216, 24, 1, gScenarioBufferData93_HT_CENTRALDY_3X3_16S, 50, gScenarioKernelData93_HT_CENTRALDY_3X3_16S, 2},
{6, 18, 3800, 24, 1, gScenarioBufferData94_HT_CENTRALDY_3X3_16S, 50, gScenarioKernelData94_HT_CENTRALDY_3X3_16S, 2},
{1, 20, 976, 24, 1, gScenarioBufferData95_HT_CENTRALDY_3X3_16S, 50, gScenarioKernelData95_HT_CENTRALDY_3X3_16S, 2},
{2, 20, 1624, 24, 1, gScenarioBufferData96_HT_CENTRALDY_3X3_16S, 50, gScenarioKernelData96_HT_CENTRALDY_3X3_16S, 2},
{3, 20, 2272, 24, 1, gScenarioBufferData97_HT_CENTRALDY_3X3_16S, 50, gScenarioKernelData97_HT_CENTRALDY_3X3_16S, 2},
{4, 20, 2920, 24, 1, gScenarioBufferData98_HT_CENTRALDY_3X3_16S, 50, gScenarioKernelData98_HT_CENTRALDY_3X3_16S, 2},
{5, 20, 3568, 24, 1, gScenarioBufferData99_HT_CENTRALDY_3X3_16S, 50, gScenarioKernelData99_HT_CENTRALDY_3X3_16S, 2},
{1, 22, 1072, 24, 1, gScenarioBufferData100_HT_CENTRALDY_3X3_16S, 50, gScenarioKernelData100_HT_CENTRALDY_3X3_16S, 2},
{2, 22, 1784, 24, 1, gScenarioBufferData101_HT_CENTRALDY_3X3_16S, 50, gScenarioKernelData101_HT_CENTRALDY_3X3_16S, 2},
{3, 22, 2496, 24, 1, gScenarioBufferData102_HT_CENTRALDY_3X3_16S, 50, gScenarioKernelData102_HT_CENTRALDY_3X3_16S, 2},
{4, 22, 3208, 24, 1, gScenarioBufferData103_HT_CENTRALDY_3X3_16S, 50, gScenarioKernelData103_HT_CENTRALDY_3X3_16S, 2},
{1, 24, 1168, 24, 1, gScenarioBufferData104_HT_CENTRALDY_3X3_16S, 50, gScenarioKernelData104_HT_CENTRALDY_3X3_16S, 2},
{2, 24, 1944, 24, 1, gScenarioBufferData105_HT_CENTRALDY_3X3_16S, 50, gScenarioKernelData105_HT_CENTRALDY_3X3_16S, 2},
{3, 24, 2720, 24, 1, gScenarioBufferData106_HT_CENTRALDY_3X3_16S, 50, gScenarioKernelData106_HT_CENTRALDY_3X3_16S, 2},
{4, 24, 3496, 24, 1, gScenarioBufferData107_HT_CENTRALDY_3X3_16S, 50, gScenarioKernelData107_HT_CENTRALDY_3X3_16S, 2},
{1, 26, 1264, 24, 1, gScenarioBufferData108_HT_CENTRALDY_3X3_16S, 50, gScenarioKernelData108_HT_CENTRALDY_3X3_16S, 2},
{2, 26, 2104, 24, 1, gScenarioBufferData109_HT_CENTRALDY_3X3_16S, 50, gScenarioKernelData109_HT_CENTRALDY_3X3_16S, 2},
{3, 26, 2944, 24, 1, gScenarioBufferData110_HT_CENTRALDY_3X3_16S, 50, gScenarioKernelData110_HT_CENTRALDY_3X3_16S, 2},
{4, 26, 3784, 24, 1, gScenarioBufferData111_HT_CENTRALDY_3X3_16S, 50, gScenarioKernelData111_HT_CENTRALDY_3X3_16S, 2},
{1, 28, 1360, 24, 1, gScenarioBufferData112_HT_CENTRALDY_3X3_16S, 50, gScenarioKernelData112_HT_CENTRALDY_3X3_16S, 2},
{2, 28, 2264, 24, 1, gScenarioBufferData113_HT_CENTRALDY_3X3_16S, 50, gScenarioKernelData113_HT_CENTRALDY_3X3_16S, 2},
{3, 28, 3168, 24, 1, gScenarioBufferData114_HT_CENTRALDY_3X3_16S, 50, gScenarioKernelData114_HT_CENTRALDY_3X3_16S, 2},
{1, 30, 1456, 24, 1, gScenarioBufferData115_HT_CENTRALDY_3X3_16S, 50, gScenarioKernelData115_HT_CENTRALDY_3X3_16S, 2},
{2, 30, 2424, 24, 1, gScenarioBufferData116_HT_CENTRALDY_3X3_16S, 50, gScenarioKernelData116_HT_CENTRALDY_3X3_16S, 2},
{3, 30, 3392, 24, 1, gScenarioBufferData117_HT_CENTRALDY_3X3_16S, 50, gScenarioKernelData117_HT_CENTRALDY_3X3_16S, 2},
{1, 32, 1552, 24, 1, gScenarioBufferData118_HT_CENTRALDY_3X3_16S, 50, gScenarioKernelData118_HT_CENTRALDY_3X3_16S, 2},
{2, 32, 2584, 24, 1, gScenarioBufferData119_HT_CENTRALDY_3X3_16S, 50, gScenarioKernelData119_HT_CENTRALDY_3X3_16S, 2},
{3, 32, 3616, 24, 1, gScenarioBufferData120_HT_CENTRALDY_3X3_16S, 50, gScenarioKernelData120_HT_CENTRALDY_3X3_16S, 2}
};

static acf_scenario_list gScenarioList_HT_CENTRALDY_3X3_16S = {
121, //number of scenarios
gScenarioArray_HT_CENTRALDY_3X3_16S};
//**************************************************************

class HT_CENTRALDY_3X3_16S : public ACF_Process_APU
{
public:
   HT_CENTRALDY_3X3_16S(int32_t apex_id = 0) : ACF_Process_APU(apex_id)
   {} 

   int32_t Initialize()
   {
      int32_t lRetVal = 0;

      if (!Initialized()) //initialization steps that only need to occur once
      {
         SetProcessIdentifier("HT_CENTRALDY_3X3_16S");
         SetApuLoadInfo(HT_CENTRALDY_3X3_16S_LOAD_SEGMENTS,
                        HT_CENTRALDY_3X3_16S_LOAD_PMEM, HT_CENTRALDY_3X3_16S_LOAD_PMEM_SIZE,
                        HT_CENTRALDY_3X3_16S_LOAD_DMEM, HT_CENTRALDY_3X3_16S_LOAD_DMEM_SIZE,
                        0, 0); //assuming _LOAD_CMEM does not exist
         FlagSpatialDep();

         //***NOTE: the order in which the following ports are added is meaningful; do not change!

         AddPort("INPUT_0", ICP_DATATYPE_08U, 1, 1, 4, 1, 0, 0, 0, 0, 0, 0, 0, 0x1010101);
         AddPort("K_0", ICP_DATATYPE_08S, 1, 1, 1, 1, 0, 1, 1, 0, 1, 0, 2);
         AddPort("K_1", ICP_DATATYPE_08S, 1, 1, 1, 1, 0, 1, 1, 0, 1, 0, 3);
         AddPort("K_2", ICP_DATATYPE_08S, 1, 1, 1, 1, 0, 1, 1, 0, 1, 0, 4);
         AddPort("OUTPUT_0", ICP_DATATYPE_16S, 1, 1, 4, 1, 1, 0, 0, 0, 0, 0, 1);

         CfgScenarios(&gScenarioList_HT_CENTRALDY_3X3_16S);

         FlagAsInitialized();
      }

      lRetVal = SelectApuConfiguration(mApuCfg, mApexId); //by default mApuCfg = ACF_APU_CFG__APEX0_DEFAULT and mApexId = 0

      return lRetVal;
   }
};

#endif //_ACF_PROCESS_APU_HT_CENTRALDY_3X3_16S
