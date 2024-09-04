#include "stm32f10x.h"                  // Device header
#include "PWM.h"

void Servo_Init()
{
	PWM_Init();
}

//���ýǶȺ���
void Servo_SetAngle(float Angle)
{
	PWM_SetCompare2(Angle / 180 * 2000 + 500);
}