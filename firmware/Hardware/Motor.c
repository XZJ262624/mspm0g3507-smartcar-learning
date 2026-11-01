/**
  ****************************************************************************
  * @file    Motor.c
  * @author  XZJxsdss
  * @date    2025_7_30
  * @brief   电机测速及PID控制
  * 2025_8_2update_stm32_STM_PID_1(2025_7_25)移植定时中断测速部分
  ****************************************************************************
**/

/**
  ****************************************************************************
  * @date    2025_8_12
  * @brief   四驱方案：由“//注释分组一”开始取消注释，至注释部分下方最近有效代码行
  ****************************************************************************
**/

#include "ti_msp_dl_config.h"
#include "Encoder.h"
#include "Motor.h"
#include "PWM.h"
#include "Clock.h"
#include "Key.h"

float FR_Speed;
float FL_Speed;
float BR_Speed;
float BL_Speed;

float BLSp_Target,BLSp_Actual,BLSp_Out;
float BLSp_Err0,BLSp_Err1,BLSp_ErrInt;

float BRSp_Target,BRSp_Actual,BRSp_Out;
float BRSp_Err0,BRSp_Err1,BRSp_ErrInt;

float FLSp_Target,FLSp_Actual,FLSp_Out;
float FLSp_Err0,FLSp_Err1,FLSp_ErrInt;

float FRSp_Target,FRSp_Actual,FRSp_Out;
float FRSp_Err0,FRSp_Err1,FRSp_ErrInt;


float SpKp = 0.005;
float SpKi = 0.0018;
float SpKd = 0.00234;
uint8_t MS;
// float SpKp = 0.0045;
// float SpKi = 0.0016;
// float SpKd = 0.00254;

//
//简介：电机测速定时中断，中断时间间隔T为10ms
//使用说明：需要添加想测速的车轮直接令其等于对应Encoder_GetXX_Speed()即可
//
void TIMER_G0_INST_IRQHandler(void)
{
    switch(DL_TimerG_getPendingInterrupt(TIMER_G0_INST))
    {
        case DL_TIMER_IIDX_ZERO:
            if(Key_GetNum() == 2)
            {if(MS == 0){MS = 1;}
            else{MS = 0;}}

            BL_Speed = Encoder_GetBL_Speed();
            BLSp_Actual = BL_Speed;
            BLSp_Err0 = BLSp_Err1;
            BLSp_Err1 = BLSp_Target - BLSp_Actual;
            BLSp_ErrInt += BLSp_Err0;
            if(BLSp_ErrInt > 45000){BLSp_ErrInt = 45000;}
            if(BLSp_ErrInt < -45000){BLSp_ErrInt = -45000;}
            BLSp_Out = SpKp*BLSp_Err0 + SpKi*BLSp_ErrInt + SpKd*(BLSp_Err0 - BLSp_Err1);
            if(BLSp_Out > 100)
            {BLSp_Out = 100;}
            if(BLSp_Out < -100)
            {BLSp_Out = -100;}

            BR_Speed = Encoder_GetBR_Speed();
            BRSp_Actual = BR_Speed;
            BRSp_Err0 = BRSp_Err1;
            BRSp_Err1 = BRSp_Target - BRSp_Actual;
            BRSp_ErrInt += BRSp_Err0;
            if(BRSp_ErrInt > 45000){BRSp_ErrInt = 45000;}
            if(BRSp_ErrInt < -45000){BRSp_ErrInt = -45000;}
            BRSp_Out = SpKp*BRSp_Err0 + SpKi*BRSp_ErrInt + SpKd*(BRSp_Err0 - BRSp_Err1);
            if(BRSp_Out > 100)
            {BRSp_Out = 100;}
            if(BRSp_Out < -100)
            {BRSp_Out = -100;}

            // //注释分组一
            // FL_Speed = Encoder_GetFL_Speed();
            // FLSp_Actual = FL_Speed;
            // FLSp_Err0 = FLSp_Err1;
            // FLSp_Err1 = FLSp_Target - FLSp_Actual;
            // FLSp_ErrInt += FLSp_Err0;
            // if(FLSp_ErrInt > 45000){FLSp_ErrInt = 45000;}
            // if(FLSp_ErrInt < -45000){FLSp_ErrInt = -45000;}
            // FLSp_Out = SpKp*FLSp_Err0 + SpKi*FLSp_ErrInt + SpKd*(FLSp_Err0 - FLSp_Err1);
            // if(FLSp_Out > 100)
            // {FLSp_Out = 100;}
            // if(FLSp_Out < -100)
            // {FLSp_Out = -100;}

            // FR_Speed = Encoder_GetFR_Speed();
            // FRSp_Actual = FR_Speed;
            // FRSp_Err0 = FRSp_Err1;
            // FRSp_Err1 = FRSp_Target - FRSp_Actual;
            // FRSp_ErrInt += FRSp_Err0;
            // if(FRSp_ErrInt > 45000){FRSp_ErrInt = 45000;}
            // if(FRSp_ErrInt < -45000){FRSp_ErrInt = -45000;}
            // FRSp_Out = SpKp*FRSp_Err0 + SpKi*FRSp_ErrInt + SpKd*(FRSp_Err0 - FRSp_Err1);
            // if(FRSp_Out > 100)
            // {FRSp_Out = 100;}
            // if(FRSp_Out < -100)
            // {FRSp_Out = -100;}

            SetMotorBR_PWM(BRSp_Out);
            SetMotorBL_PWM(BLSp_Out);
            // //注释分组一
            // SetMotorFL_PWM(FLSp_Out);
            // SetMotorFR_PWM(FRSp_Out);
            break;
        default:
            break;
    }
}

//
//简介：设定电机目标速度
//
void SetMotorBL_Speed(int16_t Speed)
{
    BLSp_Target = Speed;
}
void SetMotorBR_Speed(int16_t Speed)
{
    BRSp_Target = Speed;
}
void SetMotorFL_Speed(int16_t Speed)
{
    FLSp_Target = Speed;
}
void SetMotorFR_Speed(int16_t Speed)
{
    FRSp_Target = Speed;
}

//
//简介：设置电机正反转及其对应PWM
//
void SetMotorBL_PWM(int8_t Speed)
{
    if(Speed >= 0)
    {
      DL_GPIO_setPins(MOTOR_BL_IN2_PORT,MOTOR_BL_IN2_PIN);
      DL_GPIO_clearPins(MOTOR_BL_IN1_PORT,MOTOR_BL_IN1_PIN);
      SetPWM_TG12_CH0(Speed);
    }
    else
    {
      DL_GPIO_setPins(MOTOR_BL_IN1_PORT,MOTOR_BL_IN1_PIN);
      DL_GPIO_clearPins(MOTOR_BL_IN2_PORT,MOTOR_BL_IN2_PIN);
      SetPWM_TG12_CH0(-Speed);
    }
}

void SetMotorBR_PWM(int8_t Speed)
{
    if(Speed >= 0)
    {
      DL_GPIO_setPins(MOTOR_BR_IN2_PORT,MOTOR_BR_IN2_PIN);
      DL_GPIO_clearPins(MOTOR_BR_IN1_PORT,MOTOR_BR_IN1_PIN);
      SetPWM_TG6_CH0(Speed);
    }
    else
    {
      DL_GPIO_setPins(MOTOR_BR_IN1_PORT,MOTOR_BR_IN1_PIN);
      DL_GPIO_clearPins(MOTOR_BR_IN2_PORT,MOTOR_BR_IN2_PIN);
      SetPWM_TG6_CH0(-Speed);
    }
}

void SetMotorFL_PWM(int8_t Speed)
{
    if(Speed >= 0)
    {
      DL_GPIO_setPins(MOTOR_FL_IN1_PORT,MOTOR_FL_IN1_PIN);
      DL_GPIO_clearPins(MOTOR_FL_IN2_PORT,MOTOR_FL_IN2_PIN);
      SetPWM_TG12_CH1(Speed);
    }
    else
    {
      DL_GPIO_setPins(MOTOR_FL_IN2_PORT,MOTOR_FL_IN2_PIN);
      DL_GPIO_clearPins(MOTOR_FL_IN1_PORT,MOTOR_FL_IN1_PIN);
      SetPWM_TG12_CH1(-Speed);
    }
}

void SetMotorFR_PWM(int8_t Speed)
{
    if(Speed >= 0)
    {
      DL_GPIO_setPins(MOTOR_FR_IN1_PORT,MOTOR_FR_IN1_PIN);
      DL_GPIO_clearPins(MOTOR_FR_IN2_PORT,MOTOR_FR_IN2_PIN);
      SetPWM_TG6_CH1(Speed);
    }
    else
    {
      DL_GPIO_setPins(MOTOR_FR_IN2_PORT,MOTOR_FR_IN2_PIN);
      DL_GPIO_clearPins(MOTOR_FR_IN1_PORT,MOTOR_FR_IN1_PIN);
      SetPWM_TG6_CH1(-Speed);
    }
}

//测试用
void PIDControlTest(void)
{
    SetMotorBL_Speed(500);
    SetMotorBR_Speed(500);
    // //注释分组一
    // SetMotorFL_Speed(-500);
    // SetMotorFR_Speed(-500);
    mspm0_delay_ms(2000);

    SetMotorBL_Speed(-500);
    SetMotorBR_Speed(-500);
    // //注释分组一
    // SetMotorFL_Speed(500);
    // SetMotorFR_Speed(500);
    mspm0_delay_ms(2000);
}
