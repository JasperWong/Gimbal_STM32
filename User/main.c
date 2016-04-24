#include "stm32f10x.h"
#include "bsp_pwm_output.h"
#include "usart.h"
#include "timer.h"

#define RECEIVE_BUF_SIZE 32
static uint8_t isDone=0;

int main()
{	
	TIM3_PWM_Init();
	USART_Config();
	Usart_NVIC_Init();
	TIM2_NVIC_Configuration();
	Timer2_Config();
	printf("\r\nReady\r\n");
	while(1);
	return 0;
}

void OnRecieve(int16_t data)
{
	static int8_t roll_buffer[10];
	static int8_t yaw_buffer[10];
	static uint8_t buffer_bit=0;
	static uint8_t bit=0;
	int16_t roll;
	int16_t yaw;
	uint8_t read_bit;
	int16_t roll_final=0;
	int16_t yaw_final=0;
	int16_t data_buff[RECEIVE_BUF_SIZE];
	
	if(!isDone)
	{
		if (data=='X')   bit=0;
		if (data=='\n')  isDone=1;
		data_buff[bit]=data;
		bit++;
	}

	if (isDone)
	{
		uint8_t isMinus_roll=0;
		uint8_t isMinus_yaw=0;
		
		roll=0;
		yaw=0;
		isMinus_roll=0;
		isMinus_yaw=0;
		read_bit=2;
			
		/**getRoll**/
		while (data_buff[read_bit]!=' ')
		{
			if (data_buff[read_bit]=='-')
			{
				isMinus_roll=1;
				read_bit++;
				continue;
			}
			roll=roll*10+(data_buff[read_bit]-'0');
			read_bit++;
		}
		read_bit+=3;
				
		/**getyaw**/
		while (data_buff[read_bit]!=' ')
		{
			if (data_buff[read_bit]=='-')
			{
				isMinus_yaw=1;
				read_bit++;
				continue;
			}
			yaw=yaw*10+(data_buff[read_bit]-'0');
			read_bit++;
		}

		if (isMinus_roll)
		{
			roll=-roll;
			isMinus_roll=0;
		}
		if (isMinus_yaw)
		{
			yaw=-yaw;
			isMinus_yaw=0;
		}
		roll+=90;

		roll_buffer[buffer_bit]=roll;
		yaw_buffer[buffer_bit]=yaw;
				buffer_bit++;
				if(buffer_bit>=11) buffer_bit=0;
				
				for(int i=0;i<10;i++)
				{
					roll_final+=roll_buffer[i];
					yaw_final+=yaw_buffer[i];
				}
				
				roll_final/=10;
				yaw_final/=10;
				
		printf("%c%c",roll_final,yaw_final);
		Roll(roll);
		YawToAngle(yaw);
				
		if (roll==0) Reset();
		isDone=0;
	}

}

