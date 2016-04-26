#include "stm32f10x.h"
#include "bsp_pwm_output.h"
#include "usart.h"
#include "timer.h"

int main()
{	
	TIM3_PWM_Init();
	USART_Config();
	Usart_NVIC_Init();
	TIM2_NVIC_Configuration();
	Timer2_Config();
	printf("\r\nReady\r\n");
	while(1);
}



