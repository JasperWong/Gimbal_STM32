#include "stm32f10x.h"
#include "bsp_pwm_output.h"
#include "usart.h"
#include "timer.h"
#include "parser.h"

extern COMMAND_PARSER parser;
uint8_t	isFinish=1;

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
    while (1)
    {

        if (parser.status==STATE_PARSE_FINISH_PENDING)
        {
			
//            if (parser.status==STATE_PARSE_FINISH_PENDING)
//            {
//		printf("9");
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


//		for(int i=0;i<10;i++)
//		{
//			target_roll+=roll_buffer[i];
//			target_yaw+=yaw_buffer[i];
//		}
//
//		target_roll/=10;
//		target_yaw/=10;

                printf("%c%c",target_roll,target_yaw);
                Roll(target_roll);
                YawToAngle(target_yaw);
                PARSER_Reset(&parser);
            }
        }

//    }
}

