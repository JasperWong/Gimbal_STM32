#include "usart.h"
#include "bsp_pwm_output.h"
#include "parser.h"

#define RECEIVE_BUF_SIZE 32
static uint8_t isDone=0;

void USART_Config()
{
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART1_InitStructure;
    
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_APB2Periph_GPIOA,ENABLE);
       
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
    GPIO_Init(GPIOA,&GPIO_InitStructure);
    
    GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;
    GPIO_InitStructure.GPIO_Pin=GPIO_Pin_10;
    GPIO_Init(GPIOA,&GPIO_InitStructure);

    USART1_InitStructure.USART_BaudRate=9600;
    USART1_InitStructure.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
    USART1_InitStructure.USART_Mode=USART_Mode_Rx|USART_Mode_Tx;
    USART1_InitStructure.USART_Parity=USART_Parity_No;
    USART1_InitStructure.USART_StopBits=USART_StopBits_1;
    USART1_InitStructure.USART_WordLength=USART_WordLength_8b;
    USART_Init(USART1,&USART1_InitStructure);
    
    USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);
    
    USART_Cmd(USART1,ENABLE);
 
}

void Usart_NVIC_Init()
{
    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
    NVIC_InitStructure.NVIC_IRQChannel=USART1_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority=1;
    NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}

COMMAND_PARSER parser;

void OnRecieve(int32_t data)
{
	static int8_t roll_buffer[10];
	static int8_t yaw_buffer[10];
	PARSER_RunPaser(&parser,data);
	
}

	
	
//	static int8_t roll_buffer[10];
//	static int8_t yaw_buffer[10];
//	static uint8_t buffer_read_bit=0;
//	static uint8_t bit=0;
//	int16_t roll;
//	int16_t yaw;
//	uint8_t read_bit;
//	int16_t roll_final=0;
//	int16_t yaw_final=0;
//	int16_t data_buff[RECEIVE_BUF_SIZE];
//	
//	if(!isDone)
//	{
//		if (data=='X')   bit=0;
//		if (data=='\n')  isDone=1;
//		data_buff[bit]=data;
//		bit++;
//	}

//	if (isDone)
//	{
//		uint8_t isMinus_roll=0;
//		uint8_t isMinus_yaw=0;
//		roll=0;
//		yaw=0;
//		isMinus_roll=0;
//		isMinus_yaw=0;
//		read_bit=2;
//		/**getRoll**/
//		while (data_buff[read_bit]!=' ')
//		{
//			if (data_buff[read_bit]=='-')
//			{
//				isMinus_roll=1;
//				read_bit++;
//				continue;
//			}
//			roll=roll*10+(data_buff[read_bit]-'0');
//			read_bit++;
//		}
//						
//		/**getyaw**/
//		do{
//			read_bit++;
//		}
//		while(data_buff[read_bit]!=':');
//		
//		read_bit++;
//		
//		while (data_buff[read_bit]!=' ')
//		{
//			if (data_buff[read_bit]=='-')
//			{
//				isMinus_yaw=1;
//				read_bit++;
//				continue;
//			}
//			yaw=yaw*10+(data_buff[read_bit]-'0');
//			read_bit++;
//		}

//		if (isMinus_roll)
//		{
//			roll=-roll;
//			isMinus_roll=0;
//		}
//		if (isMinus_yaw)
//		{
//			yaw=-yaw;
//			isMinus_yaw=0;
//		}
//		
//		roll+=90;								//VR's angle to Gimbal's angle
//		
//		roll_buffer[buffer_read_bit]=roll;
//		yaw_buffer[buffer_read_bit]=yaw;
//				buffer_read_bit++;
//				if(buffer_read_bit>10) buffer_read_bit=0;
//				for(int i=0;i<10;i++)
//				{
//					roll_final+=roll_buffer[i];
//					yaw_final+=yaw_buffer[i];
//				}
//				roll_final/=10;
//				yaw_final/=10;
//				
//		printf("%c%c",roll_final,yaw_final);
//		Roll(roll);
//		YawToAngle(yaw);
//				
//		isDone=0;
//	}

//}



/// 重定向c库函数printf到USART1
int fputc(int ch, FILE *f)
{
		/* 发送一个字节数据到USART1 */
		USART_SendData(USART1, (uint8_t) ch);
		
		/* 等待发送完毕 */
		while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);		
	
		return (ch);
}

/// 重定向c库函数scanf到USART1
int fgetc(FILE *f)
{
		/* 等待串口1输入数据 */
		while (USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == RESET);
    
		return (int)USART_ReceiveData(USART1);
}


