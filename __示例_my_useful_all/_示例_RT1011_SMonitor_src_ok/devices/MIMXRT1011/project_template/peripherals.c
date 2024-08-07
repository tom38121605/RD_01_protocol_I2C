/*
 * Copyright 2019 NXP.
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/***********************************************************************************************************************
 * This file was generated by the MCUXpresso Config Tools. Any manual edits made to this file
 * will be overwritten if the respective MCUXpresso Config Tools is used to update this file.
 **********************************************************************************************************************/

/* clang-format off */
/* TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
!!GlobalInfo
product: Peripherals v6.0
processor: MIMXRT1011xxxxx
mcu_data: ksdk2_0
processor_version: 0.0.8
functionalGroups:
- name: BOARD_InitPeripherals
  called_from_default_init: true
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS **********/

/* TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
component:
- type: 'system'
- type_id: 'system_54b53072540eeeb8f8e9343e71f28176'
- global_system_definitions: []
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS **********/
/* clang-format on */

/***********************************************************************************************************************
 * Included files
 **********************************************************************************************************************/
#include "peripherals.h"


const gpt_config_t DEMO_GPT_config = {         //--add
  .clockSource = kGPT_ClockSource_LowFreq,
  //.clockSource = kGPT_ClockSource_Periph,
  .divider = 1,
  .enableFreeRun = false,
  .enableRunInWait = true,
  .enableRunInStop = true,
  .enableRunInDoze = true,
  .enableRunInDbg = false,
  .enableMode = true
};


void DEMO_GPT_init(void) {           //--add
  /* GPT device and channels initialization */
  GPT_Init(DEMO_GPT_PERIPHERAL, &DEMO_GPT_config);
  GPT_SetOscClockDivider(DEMO_GPT_PERIPHERAL, 1);
  /* Enable GPT interrupt sources */
  GPT_EnableInterrupts(DEMO_GPT_PERIPHERAL, 0);
}


/***********************************************************************************************************************
 * Initialization functions
 **********************************************************************************************************************/
void BOARD_InitPeripherals(void)
{
      
  DEMO_GPT_init();  //--add
}

/***********************************************************************************************************************
 * BOARD_InitBootPeripherals function
 **********************************************************************************************************************/
void BOARD_InitBootPeripherals(void)
{
    BOARD_InitPeripherals();
}
