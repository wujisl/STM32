#include "stm32f10x.h"                  // Device header

void PWM_Init(void)
{
	//�򿪶�ʱ��ʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	//��������GPIO�ڣ�GPIO������Ĭ�ϸ��ù��ܵģ�ע��ʹ��TIMx��ͨ����Ӧ�ĸ�GPIO
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; 		//�ǵ��Ǹ����������
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	//��TIM2����Ϊ�ڲ�ʱ��ģʽ
	TIM_InternalClockConfig(TIM2);
	
	
	//����ʱ����Ԫ �����ֵ = CK_PSC/(PSC + 1)/(ARR + 1), ��ʱCK_PSC���ڲ�ʱ��72MHz��
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStructure.TIM_Period = 20000 - 1;			//ARR�Զ���װ��������
	TIM_TimeBaseInitStructure.TIM_Prescaler = 72 - 1;			//PSCԤ��Ƶ��������
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
	//Ƶ��50Hz
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStructure);
	
	//��ʼ������Ƚϵ�Ԫ
	TIM_OCInitTypeDef TIM_OCInitStructure;
	//���ṹ�帳��ʼֵ������
	TIM_OCStructInit(&TIM_OCInitStructure);
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse = 0;			//Pulseֱ�롰���塱��ָCCR��ֵ
	/*
		���㹫ʽ��
		Ƶ�� = CK_PSC /��PSC + 1��/ ��ARR + 1��
		PWMռ�ձ� = CCR /��ARR + 1��
		�ֱ��� = 1 / ��ARR + 1��
	*/
	//��ʱCCRȡֵ��Χ500 ~ 2500 ��Ӧ 0.5ms ~ 2.5ms
	
	TIM_OC2Init(TIM2, &TIM_OCInitStructure);
	
	
	//��TIM��ʱ��
	TIM_Cmd(TIM2, ENABLE);
	
}

//�����Ǹı�CCR����ʱ��ARRֵ���㼴ռ�ձȣ��ĺ���
void PWM_SetCompare2(uint16_t Compare)
{
	TIM_SetCompare2(TIM2, Compare);
}