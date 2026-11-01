/**
  ****************************************************************************
  * @file    Clock.h
  * @author  移植自bilibili_Torris_Yin
  * @date    2025_8_7
  * @brief   为M0G3507配置系统内置的嘀嗒定时器
  * @version unknown
  ****************************************************************************
**/
#ifndef _CLOCK_H_
#define _CLOCK_H_

extern volatile unsigned long tick_ms;

int mspm0_delay_ms(unsigned long num_ms);
int mspm0_get_clock_ms(unsigned long *count);
void SysTick_Init(void);

#endif  /* #ifndef _CLOCK_H_ */