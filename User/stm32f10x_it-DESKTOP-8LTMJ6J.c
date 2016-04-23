/**
  ******************************************************************************
  * @file    Project/STM32F10x_StdPeriph_Template/stm32f10x_it.c 
  * @author  MCD Application Team
  * @version V3.5.0
  * @date    08-April-2011
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and 
  *          peripherals interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTI
  
  AL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_it.h"
#include <stdio.h>
#include "bsp_pwm_output.h"
#include <math.h>

#define RECEIVE_BUF_SIZE 32

extern volatile u32 time;
extern uint32_t time_index;

/** @addtogroup STM32F10x_StdPeriph_Template
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M3 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{

}

 
/******************************************************************************/
/*                 STM32F10x Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f10x_xx.s).                                            */
/******************************************************************************/

void TIM2_IRQHandler(void)
{
	if(	TIM_GetITStatus(TIM2 , TIM_IT_Update) != RESET ) 
	{	
		time++;
		TIM_ClearITPendingBit(TIM2 , TIM_FLAG_Update);  
		if(time>=time_index)
		{
			time=0;
			Yaw(STOP);
			RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2 , DISABLE);
		}	
	}		 	
}

void USART1_IRQHandler(void)
{
    static uint8_t bit=0;
    static uint8_t isDone=0;
    int16_t roll;
    int16_t yaw;
    uint8_t read_bit;
//    int16_t angle_temp;
//    uint8_t read_counts;
		int8_t temp;
    int16_t data[RECEIVE_BUF_SIZE];
    uint8_t isMinus_roll=0;
    uint8_t isMinus_yaw=0;
	if((!isDone)&&(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET))
	{ 	
		temp= USART_ReceiveData(USART1);
        if(temp=='X')   bit=0;
        if(temp=='\n')  isDone=1;
//        if(temp=='Y')   Y_bit=bit+2;
        data[bit]=temp;
        bit++;
    }
    
    if(isDone)
    {
        roll=0;
        yaw=0;
        isMinus_roll=0;
        isMinus_yaw=0;
        read_bit=2;
        /**getRoll**/
        while(data[read_bit]!=' ')
        {   
            if(data[read_bit]=='-') 
            {
                isMinus_roll=1;
                read_bit++;
                continue;
            }
            roll=roll*10+(data[read_bit]-'0');
//            read_counts++;
            read_bit++;
        }  
        read_bit+=3;
      
//        read_counts=0;
        /**getyaw**/
        while(data[read_bit]!=' ')
        {
            if(data[read_bit]=='-') 
            {
                isMinus_yaw=1;
                read_bit++;
                continue;
            }
            yaw=yaw*10+(data[read_bit]-'0');
//            read_counts++;
            read_bit++;
        }
//        printf("%c%c\n",data[2],data[]);
        if(isMinus_roll) 
        {
            roll=-roll;
            isMinus_roll=0;  
        }
        if(isMinus_yaw)
        {
            yaw=-yaw;
            isMinus_yaw=0;
        }         
        roll+=90;
        printf("%c%c",roll,yaw);
        Roll(roll);
		YawToAngle(yaw);
		if(roll==0) Reset();
        isDone=0;
    }
    
}
/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/

/**
  * @}
  */ 


/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
