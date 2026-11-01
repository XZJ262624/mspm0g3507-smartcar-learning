/**
  ****************************************************************************
  * @file    Clock.c
  * @author  移植自bilibili_Torris_Yin
  * @date    2025_8_7
  * @brief   为M0G3507配置系统内置的嘀嗒定时器
  * @version unknown
  ****************************************************************************
**/
#include "ti_msp_dl_config.h"
#include "Clock.h"

volatile unsigned long tick_ms;
volatile uint32_t start_time;

int mspm0_delay_ms(unsigned long num_ms)
{
    start_time = tick_ms;
    while (tick_ms - start_time < num_ms);
    return 0;
}

int mspm0_get_clock_ms(unsigned long *count)
{
    if (!count)
        return 1;
    count[0] = tick_ms;
    return 0;
}

void SysTick_Init(void)
{
    DL_SYSTICK_config(CPUCLK_FREQ/1000);
    NVIC_SetPriority(SysTick_IRQn, 0);
}

void SysTick_Handler(void)
{
    tick_ms++;
}
