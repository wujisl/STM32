#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "PWM.h"

uint16_t cp;

int	main()
{	
	OLED_Init();
	PWM_Init();
	
	OLED_ShowString(1,1,"Ciallo~");
	
	while(1)
	{
		//ռ�ձ�������,�𽥱���
		for(cp = 0; cp <= 100; cp++)
		{
			PWM_SetCompare1(cp);
			Delay_ms(10);
		}
		
		//�𽥱䰵
		for(cp = 0; cp <= 100; cp++)
		{
			PWM_SetCompare1(100 - cp);
			Delay_ms(10);
		}
	}
}
