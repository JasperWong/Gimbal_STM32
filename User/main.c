#include "stm32f10x.h"
#include "bsp_pwm_output.h"
#include "usart.h"
#include "timer.h"
#include "parser.h"

extern COMMAND_PARSER parser;
uint8_t	isFinish=1;
static int16_t roll_buffer[10];
static int16_t yaw_buffer[10];

int main()
{
    TIM3_PWM_Init();
    USART_Config();
    Usart_NVIC_Init();
    TIM2_NVIC_Configuration();
    Timer2_Config();
    printf("\r\nReady\r\n");

    int32_t target_roll;
    int32_t target_yaw;
	int32_t final_roll=0;
	int32_t final_yaw=0;
	uint8_t buff_bit=0;
    while (1)
    {
        if (parser.status==STATE_PARSE_FINISH_PENDING)
        {

            target_roll=parser.data_roll;
            target_yaw=parser.data_yaw;
            if (parser.isMinus_Roll)
            {
                target_roll+=90;
            }
            else
            {
                target_roll=-target_roll+90;
            }

            if (parser.isMinus_Yaw)
            {
                target_yaw=-target_yaw;
            }

//		roll_buffer[buff_bit]=target_roll;
//		yaw_buffer[buff_bit]=target_yaw;
//		buff_bit++;

//			
//		for(int i=0;i<10;i++)
//		{
//			final_roll+=roll_buffer[i];
//			final_yaw+=yaw_buffer[i];
//		}

//		final_roll/=10;
//		final_yaw/=10;

		printf("%c%c",final_roll,final_yaw);
		Roll(target_roll);
		YawToAngle(target_yaw);
		
//		if(buff_bit>9) 
//		{
//			buff_bit=0;	
//			final_roll=0;
//			final_yaw=0;
//		}
		
		PARSER_Reset(&parser);
        }
    }

}


