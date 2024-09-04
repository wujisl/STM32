#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Timer.h"

uint16_t Num;

int	main()
{	
	OLED_Init();
	Timer_Init();
	
	OLED_ShowString(1,1,"Ciallo~");
	OLED_ShowString(2,1,"Num:");
	
	
	while(1)
	{
		OLED_ShowNum(2, 5, Num, 5);
		OLED_ShowNum(3, 5, TIM_GetCounter(TIM2), 5);
	}
}


void TIM2_IRQHandler(void)
{
	//检查是否进入对应中断
	if(TIM_GetITStatus(TIM2, TIM_IT_Update) == SET)
	{
		Num ++;
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
	}
}