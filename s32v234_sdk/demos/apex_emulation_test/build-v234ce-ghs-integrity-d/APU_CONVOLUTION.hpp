#ifndef _ACF_PROCESS_APU_APU_CONVOLUTION
#define _ACF_PROCESS_APU_APU_CONVOLUTION

#include <acf_process_apu.h>
#include <APU_CONVOLUTION_APU_LOAD.h> //APU load associated with this process
#include <stdint.h>


//SCENARIO LIST*************************************************
static acf_scenario_buffer_data gScenarioBufferData0_APU_CONVOLUTION[] = {{8, 4, 4, 0, 0x2211}, {8, 4, 2, 1, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}, {1, 1, 1, 0, 0x0}};

static acf_scenario_kernel_data gScenarioKernelData0_APU_CONVOLUTION[] = {{1}};

static acf_scenario gScenarioArray_APU_CONVOLUTION[] = {
{0, 0, 344, 40, 1, gScenarioBufferData0_APU_CONVOLUTION, 50, gScenarioKernelData0_APU_CONVOLUTION, 2}
};

static acf_scenario_list gScenarioList_APU_CONVOLUTION = {
1, //number of scenarios
gScenarioArray_APU_CONVOLUTION};
//**************************************************************

class APU_CONVOLUTION : public ACF_Process_APU
{
public:
   APU_CONVOLUTION(int32_t apex_id = 0) : ACF_Process_APU(apex_id)
   {} 

   int32_t Initialize()
   {
      int32_t lRetVal = 0;

      if (!Initialized()) //initialization steps that only need to occur once
      {
         SetProcessIdentifier("APU_CONVOLUTION");
         SetApuLoadInfo(APU_CONVOLUTION_LOAD_SEGMENTS,
                        APU_CONVOLUTION_LOAD_PMEM, APU_CONVOLUTION_LOAD_PMEM_SIZE,
                        APU_CONVOLUTION_LOAD_DMEM, APU_CONVOLUTION_LOAD_DMEM_SIZE,
                        0, 0); //assuming _LOAD_CMEM does not exist
         FlagSpatialDep();

         //***NOTE: the order in which the following ports are added is meaningful; do not change!

         AddPort("ConvGraph_Input", ICP_DATATYPE_08U, 1, 1, 8, 4, 0, 0, 0, 0, 0, 0, 0, 0x1010101);
         AddPort("ConvGraph_In_Filt", ICP_DATATYPE_16S, 3, 3, 1, 1, 0, 1, 1, 0, 1, 0, 2);
         AddPort("ConvGraph_FiltScale", ICP_DATATYPE_16S, 1, 1, 1, 1, 0, 1, 1, 0, 1, 0, 3);
         AddPort("ConvGraph_FiltSymmFlag", ICP_DATATYPE_16U, 1, 1, 1, 1, 0, 1, 1, 0, 1, 0, 4);
         AddPort("ConvGraph_Output", ICP_DATATYPE_16S, 1, 1, 8, 4, 1, 0, 0, 0, 0, 0, 1);

         CfgScenarios(&gScenarioList_APU_CONVOLUTION);

         FlagAsInitialized();
      }

      lRetVal = SelectApuConfiguration(mApuCfg, mApexId); //by default mApuCfg = ACF_APU_CFG__APEX0_DEFAULT and mApexId = 0

      return lRetVal;
   }
};

#endif //_ACF_PROCESS_APU_APU_CONVOLUTION
