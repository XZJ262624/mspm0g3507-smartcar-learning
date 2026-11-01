/**
  ****************************************************************************
  * @file    Timer.c
  * @author  XZJxsdss
  * @date    2025_8_4
  * @brief   仪式感函数
  ****************************************************************************
**/
#include "ti_msp_dl_config.h"
#include "Timer.h"

void Timer_Init(void)
{
    TimerG0_Init();//负责：电机速度环pid,10ms一次中断
    TimerG6_Init();//电机PWM
    TimerG7_Init();//负责：按键消抖,5ms
    TimerG12_Init();//电机PWM
}

void TimerG0_Init(void)
{
    DL_TimerG_startCounter(TIMER_G0_INST);
    NVIC_EnableIRQ(TIMER_G0_INST_INT_IRQN);
}
void TimerG6_Init(void)
{    
    DL_TimerG_startCounter(PWM_G6_INST);
}
void TimerG7_Init(void)
{
    DL_TimerG_startCounter(TIMER_G7_INST);
    NVIC_EnableIRQ(TIMER_G7_INST_INT_IRQN);
}
void TimerG12_Init(void)
{
    DL_TimerG_startCounter(PWM_G12_INST);
}
