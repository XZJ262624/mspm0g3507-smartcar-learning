/**
****************************************************************************
* @file    main.c
* @author  XZJxsdss
* @date    2025_7_31
* @brief   LP_M0G3507_OLED
****************************************************************************
**/
#include "ti_msp_dl_config.h"
#include "main.h"

// int8_t Text;
extern float Trk_Actual;
extern float Trk_Target;
extern float Trk_Out;
extern float BL_Speed;
extern float BR_Speed;
extern float Curr_COORD;
extern float MS;

int main(void)
{
    SYSCFG_DL_init();
    SysTick_Init();

    Timer_Init();
    
    while (1) 
    {

    }
}

