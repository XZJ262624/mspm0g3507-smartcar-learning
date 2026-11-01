/**
  ****************************************************************************
  * @file    pwm.h
  * @author  XZJxsdss
  * @date    2025_7_30
  * @brief   PWM输出
  ****************************************************************************
**/
#include "ti_msp_dl_config.h"
#ifndef PWM_H
#define PWM_H

void SetPWM_TG12_CH0(uint16_t Duty);
void SetPWM_TG12_CH1(uint16_t Duty);
void SetPWM_TG6_CH0(uint16_t Duty);
void SetPWM_TG6_CH1(uint16_t Duty);

#endif
