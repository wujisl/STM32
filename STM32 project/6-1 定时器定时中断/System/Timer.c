#include "stm32f10x.h"                  // Device header

void Timer_Init(void)
{
	//打开定时器时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	
	
	//将TIM2配置为内部时钟模式
	TIM_InternalClockConfig(TIM2);
	
	
	//配置时基单元 【溢出值 = CK_PSC/(PSC + 1)/(ARR + 1), 此时CK_PSC是内部时钟72MHz】
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStructure.TIM_Period = 10000 - 1;			//ARR自动重装器的配置
	TIM_TimeBaseInitStructure.TIM_Prescaler = 7200 - 1;			//PSC预分频器的配置
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
	
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStructure);
		
		/*对于预分频器的缓冲寄存器的存在，系统刚初始化完就会进入一次中断
		  导致系统开始从1计数。解决方案是在开启中断之前清除标识位*/
	
		TIM_ClearFlag(TIM2, TIM_IT_Update);
	//使能中断
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
	
	//配置NVIC（中断相关）
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&NVIC_InitStructure);
	
	//打开TIM定时器
	TIM_Cmd(TIM2, ENABLE);

}


//中断函数模板
/*
void TIM2_IRQHandler(void)
{
	//检查是否进入对应中断
	if(TIM_GetITStatus(TIM2, TIM_IT_Update) == SET)
	{
		
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
	}
}
*/