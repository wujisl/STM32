#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"


uint8_t KeyNum;

int	main()
{	
	OLED_Init();
	
	OLED_ShowChar(1,1,'A');
	OLED_ShowString(2,3,"Ciallo~");
	OLED_ShowNum(3,2,12345,6);
	
	
	while(1)
	{
	
		
	}
}
