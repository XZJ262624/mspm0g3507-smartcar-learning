/**
  ****************************************************************************
  * @file    Encoder.h
  * @author  XZJxsdss
  * @date    2025_8_2
  * @brief   霍尔编码器电机测速头文件
  ****************************************************************************
**/
#ifndef __ENCODER_H
#define __ENCODER_H
#include "ti_msp_dl_config.h"

void Encoder_INT_Init(void);
float Encoder_GetFR_Pos(void);  
float Encoder_GetFL_Pos(void);
float Encoder_GetBR_Pos(void);
float Encoder_GetBL_Pos(void);
float Encoder_GetFR_Speed(void);
float Encoder_GetFL_Speed(void);
float Encoder_GetBR_Speed(void);
float Encoder_GetBL_Speed(void);

#endif
