/**
  ****************************************************************************
  * @file    Encoder.c
  * @author  XZJxsdss
  * @date    2025_7_21
  * @brief   霍尔编码器电机测速
  * @version V 2.0
  * 更新于2025_8_1, 移植至M0G3507
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

static int64_t BL_Encoder;//左后电机编码器计数总值
static int64_t BR_Encoder;//右后电机编码器计数总值
static int64_t FL_Encoder;//左前电机编码器计数总值
static int64_t FR_Encoder;//右前电机编码器计数总值

//设置定时周期，T = SetCountNum * 进入中断时间 * 1000^-3
//当前T = 1 * 5ms * 1000^-3s
static int8_t SetCountNum = 1;
static float F = 100.0f;//中断周期T倒数, F = 1/T

//
//简介：传出位置数据,单位：°
//
//电机位置 = 外轮每圈360度*编码器读数 / （编码器每圈电信号*n相测速*减速比20.4)
//如：BL_Pos = (BL_Encoder * 360.0f) / (500.0f * 1.0f * 20.4f);
//其中28.346 = 500*20.409/360
float Encoder_GetBL_Pos(void)
{
	return BL_Encoder / 28.346f;
}
float Encoder_GetBR_Pos(void)
{
	return BR_Encoder / 28.346f;
}
float Encoder_GetFL_Pos(void)
{
	return FL_Encoder / 28.346f;
}
float Encoder_GetFR_Pos(void)
{
	return FR_Encoder / 28.346f;
}

//
//简介：传出速度数据,须在定时中断中读取
//需要根据进入定时中断频率调整参数F
//
float Encoder_GetBL_Speed(void)
{
	static uint8_t Count;
	static float Speed, PrevPos, CurrPos;
	
	Count++;
	
	if(Count >= SetCountNum)
	{
		PrevPos = CurrPos;
		CurrPos = Encoder_GetBL_Pos();
		Speed = (CurrPos - PrevPos)*F;
		Count = 0;
	}
	return Speed;
}
float Encoder_GetBR_Speed(void)
{
	static uint8_t Count;
	static float Speed, PrevPos, CurrPos;
	
	Count++;
	
	if(Count >= SetCountNum)
	{
		PrevPos = CurrPos;
		CurrPos = Encoder_GetBR_Pos();
		Speed = (CurrPos - PrevPos)*F;
		Count = 0;
	}
	return Speed;
}
float Encoder_GetFL_Speed(void)
{
	static uint8_t Count;
	static float Speed, PrevPos, CurrPos;
	
	Count++;
	
	if(Count >= SetCountNum)
	{
		PrevPos = CurrPos;
		CurrPos = Encoder_GetFL_Pos();
		Speed = (CurrPos - PrevPos)*F;
		Count = 0;
	}
	return Speed;
}
float Encoder_GetFR_Speed(void)
{
	static uint8_t Count;
	static float Speed, PrevPos, CurrPos;
	
	Count++;
	
	if(Count >= SetCountNum)
	{
		PrevPos = CurrPos;
		CurrPos = Encoder_GetFR_Pos();
		Speed = (CurrPos - PrevPos)*F;
		Count = 0;
	}
	return Speed;
}

//
//简介:G1中断响应函数,编码器A相上升沿触发
//
void GROUP1_IRQHandler(void)
{
    uint32_t gpioA = DL_GPIO_getEnabledInterruptStatus(GPIOA,ENCODER_BR_A_PIN|ENCODER_FR_A_PIN);
    uint32_t gpioB = DL_GPIO_getEnabledInterruptStatus(GPIOB,ENCODER_BL_A_PIN|ENCODER_FL_A_PIN);

    if(gpioB & ENCODER_BL_A_PIN)//对应左后编码器A相
    {
        if(!DL_GPIO_readPins(ENCODER_BL_B_PORT,ENCODER_BL_B_PIN))
            BL_Encoder++;
        else
            BL_Encoder--;
        DL_GPIO_clearInterruptStatus(GPIOB,ENCODER_BL_A_PIN);
    }

    if(gpioA & ENCODER_BR_A_PIN)//对应右后编码器A相
    {
        if(DL_GPIO_readPins(ENCODER_BR_B_PORT,ENCODER_BR_B_PIN))
            BR_Encoder++;
        else
            BR_Encoder--;
        DL_GPIO_clearInterruptStatus(GPIOA,ENCODER_BR_A_PIN);
    }

    // //注释分组一
    // if(gpioB & ENCODER_FL_A_PIN)//对应左前编码器A相
    // {
    //     if(!DL_GPIO_readPins(ENCODER_FL_B_PORT,ENCODER_FL_B_PIN))
    //         FL_Encoder++;
    //     else
    //         FL_Encoder--;
    //     DL_GPIO_clearInterruptStatus(GPIOB,ENCODER_FL_A_PIN);
    // }

    // if(gpioA & ENCODER_FR_A_PIN)//对应右前编码器A相
    // {
    //     if(DL_GPIO_readPins(ENCODER_FR_B_PORT,ENCODER_FR_B_PIN))
    //         FR_Encoder++;
    //     else
    //         FR_Encoder--;
    //     DL_GPIO_clearInterruptStatus(GPIOA,ENCODER_FR_A_PIN);
    // }
}

void Encoder_INT_Init(void)
{
    NVIC_EnableIRQ(ENCODER_GPIOA_INT_IRQN);
    NVIC_EnableIRQ(ENCODER_GPIOB_INT_IRQN);
}
