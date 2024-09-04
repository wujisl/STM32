#include "stm32f10x.h"                  // Device header

void PWM_Init(void)
{
	//打开定时器时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	//下面配置GPIO口，GPIO口是有默认复用功能的，注意使用TIMx的通道对应哪个GPIO
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; 		//记得是复用推挽输出
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	//将TIM2配置为内部时钟模式
	TIM_InternalClockConfig(TIM2);
	
	
	//配置时基单元 【溢出值 = CK_PSC/(PSC + 1)/(ARR + 1), 此时CK_PSC是内部时钟72MHz】
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStructure.TIM_Period = 100 - 1;			//ARR自动重装器的配置
	TIM_TimeBaseInitStructure.TIM_Prescaler = 36 - 1;			//PSC预分频器的配置
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
	
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStructure);
	
	//初始化输出比较单元
	TIM_OCInitTypeDef TIM_OCInitStructure;
	//给结构体赋初始值再配置
	TIM_OCStructInit(&TIM_OCInitStructure);
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse = 0;			//Pulse直译“脉冲”，指CCR的值
	/*
		计算公式：
		频率 = CK_PSC /（PSC + 1）/ （ARR + 1）
		PWM占空比 = CCR /（ARR + 1）
		分辨率 = 1 / （ARR + 1）
	*/
	
	TIM_OC3Init(TIM2, &TIM_OCInitStructure);
	
	
	//打开TIM定时器
	TIM_Cmd(TIM2, ENABLE);
	
}

//下面是改变CCR（此时按ARR值计算即占空比）的函数
void PWM_SetCompare3(uint16_t Compare)
{
	TIM_SetCompare3(TIM2, Compare);
}