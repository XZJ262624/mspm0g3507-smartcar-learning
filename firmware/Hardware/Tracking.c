/**
  ****************************************************************************
  * @file    Motor.c
  * @author  XZJxsdss
  * @date    2025_8_12
  * @brief   获取灰度传感器读数及小车循迹环
  ****************************************************************************
**/
#include "ti_msp_dl_config.h"
#include "Motor.h"

//
float Trk_Target = 2.5,Trk_Actual,Trk_Out;
float Trk_Err0,Trk_Err1,Trk_ErrInt;
float TrkKp = 26.8;
float TrkKi = 0;
float TrkKd = 28;

uint8_t L4,L3,L2,L1;
uint8_t R4,R3,R2,R1;

float Curr_COORD,Last_COORD;
float Test;
extern uint8_t MS;

/**
****************************************************************************
*
* y
* A  L4 3 2 1 R1 2 3 4
* |   1 2 3 4  5 6 7 8
* |      ________(GrayScale)
* |      |      |
* |    (FL)    (FR)
* |      |      |
* |      |      |
* |     ——      ——
* |    |BL|    |BR|
* |     ———----———
* ————————————————————————————>x
*
****************************************************************************
**/

//
//简介：灰度传感器读取坐标，将结果传递到Curr_COORD
//
void Tracking_GetCoordinate(void)
{
    float ChannelNum = 0;
    // uint8_t L4 = 0,L3 = 0,L2 = 0,L1 = 0;
    // uint8_t R4 = 0,R3 = 0,R2 = 0,R1 = 0;

    if(DL_GPIO_readPins(GRAYSCALE_PIN_0_PORT,GRAYSCALE_PIN_0_PIN)){L4 = 1,ChannelNum++;}else{L4 = 0;}//PB27
    if(DL_GPIO_readPins(GRAYSCALE_PIN_1_PORT,GRAYSCALE_PIN_1_PIN)){L3 = 1,ChannelNum++;}else{L3 = 0;}//PB26
    if(DL_GPIO_readPins(GRAYSCALE_PIN_2_PORT,GRAYSCALE_PIN_2_PIN)){L2 = 1,ChannelNum++;}else{L2 = 0;}//PB22
    if(DL_GPIO_readPins(GRAYSCALE_PIN_3_PORT,GRAYSCALE_PIN_3_PIN)){L1 = 1,ChannelNum++;}else{L1 = 0;}//PB4
    if(DL_GPIO_readPins(GRAYSCALE_PIN_4_PORT,GRAYSCALE_PIN_4_PIN)){R1 = 1,ChannelNum++;}else{R1 = 0;}//PB5
    if(DL_GPIO_readPins(GRAYSCALE_PIN_5_PORT,GRAYSCALE_PIN_5_PIN)){R2 = 1,ChannelNum++;}else{R2 = 0;}//PB10
    if(DL_GPIO_readPins(GRAYSCALE_PIN_6_PORT,GRAYSCALE_PIN_6_PIN)){R3 = 1,ChannelNum++;}else{R3 = 0;}//PA14
    if(DL_GPIO_readPins(GRAYSCALE_PIN_7_PORT,GRAYSCALE_PIN_7_PIN)){R4 = 1,ChannelNum++;}else{R4 = 0;}//PA7

    if(ChannelNum == 0)//确保分母不为0
    {ChannelNum = 1;}

    if(ChannelNum < 3 && ChannelNum >= 1)
    {
        Curr_COORD = (L4*1 + L3*2 + L2*3 + L1*4 + R1*5 + R2*6 + R3*7 + R4*8)/ChannelNum;
        if(Curr_COORD != 0)
        {Last_COORD = Curr_COORD;}
        else if(Curr_COORD == 0)//未检测到黑线坐标时保持上一次的有效值
        {Curr_COORD = Last_COORD;}
    }
    // else if(ChannelNum >= 4)
    // {
    //     MS = 0;
    // }
    else if(ChannelNum > 2)
    {
        MS = 0;
    }
}

void Tracking_Cycle(void)
{
    Tracking_GetCoordinate();
    // Trk_Actual = Curr_COORD;
    // Trk_Err0 = Trk_Err1;
    // Trk_Err1 = Trk_Target - Trk_Actual;
    // Trk_ErrInt  += Trk_Err0;
    // if(Trk_ErrInt > 200){Trk_ErrInt = 200;}
    // if(Trk_ErrInt < -200){Trk_ErrInt = -200;}
    // Trk_Out = TrkKp*Trk_Err0 + TrkKi*Trk_ErrInt + TrkKd*(Trk_Err0 - Trk_Err1);
    // if(Trk_Out > 185)
    // {Trk_Out = 185;}
    // if(Trk_Out < -185)
    // {Trk_Out = -185;}

    // if(Trk_Err1 > 0)
    // {
    //     Trk_Out = 80;
    // }
    // else if(Trk_Err1 < 0)
    // {
    //     Trk_Out = -80;
    // }
    // else if(Trk_Err1 == 0)
    // {
    //     Trk_Out = 0;
    // }
     
     
    // if(Curr_COORD > 5.5 && Curr_COORD < 3.5)
    // {
        // if(Trk_Out > 25)
        // {Trk_Out = 25;}
        // if(Trk_Out < -25)
        // {Trk_Out = -25;}
        // SetMotorBL_Speed(MS*(540 + Trk_Out));
        // SetMotorBR_Speed(MS*(540 - Trk_Out));
    // }
    // else if(Curr_COORD < 5.5 || Curr_COORD > 3.5)
    // {
    //     if(Curr_COORD < 6.5 || Curr_COORD > 2.5)
    //     {
    //         SetMotorBL_Speed(MS*(400 + 3*Trk_Out));
    //         SetMotorBR_Speed(MS*(400 - 3*Trk_Out));
    //     }
    //     else if(Curr_COORD > 7 || Curr_COORD < 2)
    //     {
    //         SetMotorBL_Speed(MS*(400 + 6*Trk_Out));
    //         SetMotorBR_Speed(MS*(400 - 6*Trk_Out));
    //     }
    // }

    // SetMotorBL_Speed(MS*(300 - Trk_Out));
    // SetMotorBR_Speed(MS*(300 + Trk_Out));

    // SetMotorBL_Speed(MS*(300));
    // SetMotorBR_Speed(MS*(300));
}
