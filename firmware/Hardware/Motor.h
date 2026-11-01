/**
  ****************************************************************************
  * @file    Motor.h
  * @author  XZJxsdss
  * @date    2025_7_30
  * @brief   电机测速及控制
  ****************************************************************************
**/
#include "ti_msp_dl_config.h"
#ifndef __MOTOR_H
#define __MOTOR_H

#define On      1;
#define Off     0;

void SetMotorBL_Speed(int16_t Speed);
void SetMotorBR_Speed(int16_t Speed);
void SetMotorFL_Speed(int16_t Speed);
void SetMotorFR_Speed(int16_t Speed);

void SetMotorBL_PWM(int8_t Speed);
void SetMotorFL_PWM(int8_t Speed);
void SetMotorFR_PWM(int8_t Speed);
void SetMotorBR_PWM(int8_t Speed);
void PIDControlTest(void);

#endif
