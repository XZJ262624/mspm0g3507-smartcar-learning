#include "ti_msp_dl_config.h"

uint8_t Key_Num;

uint8_t Key_GetState(void)
{
	if(DL_GPIO_readPins(BUTTON_PORT,BUTTON_SW2_PIN) == 0)
	{
		return 2;
	}
    else
	return 0;
}

uint8_t Key_GetNum(void)
{

	uint8_t Temp;
	if(Key_Num)
	{
		Temp = Key_Num;
		Key_Num = 0;
		return Temp;
	}
	return 0;
}

void Key_Tick(void)
{
	static uint8_t Count;
	static uint8_t CurrState, PrevState;
	
	Count++;
	
	if(Count >= 4)
	{
		Count = 0;
		PrevState = CurrState;
		CurrState = Key_GetState();
		
		if(CurrState == 0 && PrevState != 0)
		{
			Key_Num = PrevState;
		}
	}
}

void TIMER_G7_INST_IRQHandler(void)
{
    switch(DL_TimerG_getPendingInterrupt(TIMER_G7_INST))
    {
        case DL_TIMER_IIDX_ZERO:
            Key_Tick();            
            break;
        default:
            break;
    }
}
