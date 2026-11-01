/**
  ****************************************************************************
  * @file    pwm.c
  * @author  XZJxsdss
  * @date    2025_7_30
  * @brief   PWM输出
  ****************************************************************************
**/
#include "ti_msp_dl_config.h"

uint16_t ARR = 100;//其实是ARR*100^-2，以便输入百分比数对应整形输入,syscfg修改后需在此处保持一致

void SetPWM_TG12_CH0(uint16_t Duty)
{
    DL_TimerG_setCaptureCompareValue(PWM_G12_INST,ARR*Duty,DL_TIMER_CC_0_INDEX);
}

void SetPWM_TG12_CH1(uint16_t Duty)
{
    DL_TimerG_setCaptureCompareValue(PWM_G12_INST,ARR*Duty,DL_TIMER_CC_1_INDEX);
}

void SetPWM_TG6_CH0(uint16_t Duty)
{
    DL_TimerG_setCaptureCompareValue(PWM_G6_INST,ARR*Duty,DL_TIMER_CC_0_INDEX);
}

void SetPWM_TG6_CH1(uint16_t Duty)
{
    DL_TimerG_setCaptureCompareValue(PWM_G6_INST,ARR*Duty,DL_TIMER_CC_1_INDEX);
}
