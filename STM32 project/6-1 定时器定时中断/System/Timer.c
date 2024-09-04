#include "stm32f10x.h"                  // Device header

void Timer_Init(void)
{
	//�򿪶�ʱ��ʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	
	
	//��TIM2����Ϊ�ڲ�ʱ��ģʽ
	TIM_InternalClockConfig(TIM2);
	
	
	//����ʱ����Ԫ �����ֵ = CK_PSC/(PSC + 1)/(ARR + 1), ��ʱCK_PSC���ڲ�ʱ��72MHz��
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStructure.TIM_Period = 10000 - 1;			//ARR�Զ���װ��������
	TIM_TimeBaseInitStructure.TIM_Prescaler = 7200 - 1;			//PSCԤ��Ƶ��������
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
	
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStructure);
		
		/*����Ԥ��Ƶ���Ļ���Ĵ����Ĵ��ڣ�ϵͳ�ճ�ʼ����ͻ����һ���ж�
		  ����ϵͳ��ʼ��1����������������ڿ����ж�֮ǰ�����ʶλ*/
	
		TIM_ClearFlag(TIM2, TIM_IT_Update);
	//ʹ���ж�
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
	
	//����NVIC���ж���أ�
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&NVIC_InitStructure);
	
	//��TIM��ʱ��
	TIM_Cmd(TIM2, ENABLE);

}


//�жϺ���ģ��
/*
void TIM2_IRQHandler(void)
{
	//����Ƿ�����Ӧ�ж�
	if(TIM_GetITStatus(TIM2, TIM_IT_Update) == SET)
	{
		
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
	}
}
*/