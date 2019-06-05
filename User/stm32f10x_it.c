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

#include <stdio.h>
#include "stm32f10x_it.h"
#include "bsp_led.h"
#include "bsp_exti.h"
#include "bsp_ili9341_lcd.h"
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



void KEY1_IRQHandler(void)
{
  //确保是否产生了EXTI Line中断
	if(EXTI_GetITStatus(KEY1_INT_EXTI_LINE) != RESET) 
	{
		printf("key1");
		// LED1 取反		
		LED1_TOGGLE;
    //清除中断标志位
		EXTI_ClearITPendingBit(KEY1_INT_EXTI_LINE);     
	}  
}

void KEY2_IRQHandler(void)
{
	
  //确保是否产生了EXTI Line中断
	if(EXTI_GetITStatus(KEY2_INT_EXTI_LINE) != RESET) 
	{
		
		printf("key2");
		// LED2 取反		
		LED2_TOGGLE;
    //清除中断标志位
		EXTI_ClearITPendingBit(KEY2_INT_EXTI_LINE);     
	}  
}

//FUNCTION：键盘中断服务函数
//AUTHOR：BiggerPast
void EXTI15_10_IRQHandler(void)
{
	
	   // int keyValue=0;//按键值
    //u16 WriteVal=0;//给PA口写入的数据
		//printf("EXTI15_10_IRQHandler\n");
      //确保是否产生了EXTI Line中断
	if(EXTI_GetITStatus(KEY2_INT_EXTI_LINE) != RESET) 
	{
	static uint8_t count = 0;	
		printf("keyb");
		// LED2 取反		
		LED2_TOGGLE;
			count++;
			ILI9341_DisplayStringEx(count%(320/16),(count)/(320/16)+1,16,16,"钦",0);
    //清除中断标志位
		EXTI_ClearITPendingBit(KEY2_INT_EXTI_LINE);     
	} 
	
//	if(EXTI_GetITStatus(EXTI_Line12) != RESET||EXTI_GetITStatus(EXTI_Line13) != RESET||EXTI_GetITStatus(EXTI_Line14) != RESET||EXTI_GetITStatus(EXTI_Line15) != RESET) 
	//{
	//	
 //   GPIO_Write(GPIOB,((GPIOB->ODR & 0x00ff )| 0x0f00));//让PA8-11输出高电平
//        Delay(500);//延时消抖
 //       if((GPIOB->IDR & 0xf000)==0x0000)//若PB12-PB15全为0，则刚刚是抖动产生
//        return ;
 //   
 //   GPIO_Write(GPIOB,(GPIOB->ODR & 0xf0ff )| 0x0100);//让PA8-11输出0001，检测第四行
//      switch(GPIOB->IDR & 0xf000)
//        {
//            case 0x1000 : keyValue=13;break;
//            case 0x2000 : keyValue=14;break;
//            case 0x4000 : keyValue=15;break;
//            case 0x8000 : keyValue=16;break;    
//        }
//    
//    GPIO_Write(GPIOB,(GPIOB->ODR & 0xf0ff )| 0x0200);//让PA8-11输出0010，检测第三行
//     switch(GPIOB->IDR & 0xf000)
//       {
//            case 0x1000 : keyValue=9;break;
//            case 0x2000 : keyValue=10;break;
//            case 0x4000 : keyValue=11;break;
//            case 0x8000 : keyValue=12;break; 
//        }
//    
//    GPIO_Write(GPIOB,(GPIOB->ODR & 0xf0ff )| 0x0400);//让PA8-11输出0100，检测第二行
//      switch(GPIOB->IDR & 0xf000)
//        {
//            case 0x1000 : keyValue=5;break;
//            case 0x2000 : keyValue=6;break;
//            case 0x4000 : keyValue=7;break;
//           case 0x8000 : keyValue=8;break; 
//        }
//    GPIO_Write(GPIOB,(GPIOB->ODR & 0xf0ff )| 0x0800);//让PA8-11输出1000，检测第一行
//      switch(GPIOB->IDR & 0xf000)
//        {
//            case 0x1000 : keyValue=1;break;
//            case 0x2000 : keyValue=2;break;
//            case 0x4000 : keyValue=3;break;
//            case 0x8000 : keyValue=4;break; 
//      }
//   
//		printf("keyValue=%d",keyValue);
//	EXTI_ClearITPendingBit(EXTI_Line12|EXTI_Line13|EXTI_Line14|EXTI_Line15);//清除Line上的中断标志位
//			}
//	u8 i;
//	INTX_DISABLE();//关闭总中断
//	delay_ms(10);
//	for(i=8;i<12;i++)
//	{
//		GPIO_SetBits(GPIOB,GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11);//置为高电平
//		PAout(i)=0;
//		if(PBin(8)==0)
//	{
//			switch(i)
//			{
//				case(8):printf("i:%d,case(8)\n",i); break;
//				case(9):printf("i:%d,case(9)\n",i); break;
//				case(10):printf("i:%d,case(10)\n",i); break;
//				case(11): printf("i:%d,case(11)\n",i);break; 
//			}
//		}else if(PBin(9)==0)
//		{
//			switch(i)
//			{
//				case(8):printf("i:%d,case(8)\n",i); break;
//				case(9):printf("i:%d,case(9)\n",i); break;
//				case(10):printf("i:%d,case(10)\n",i); break;
//				case(11): printf("i:%d,case(11)\n",i);break; 
//			}
//		}else if(PBin(10)==0)
//		{
//			switch(i)
//			{
//				case(8):printf("i:%d,case(8)\n",i); break;
//				case(9):printf("i:%d,case(9)\n",i); break;
//				case(10):printf("i:%d,case(10)\n",i); break;
//				case(11): printf("i:%d,case(11)\n",i);break; 
//			}
//		}else if(PBin(11)==0)
//		{
//			switch(i)
//			{
//				case(8):printf("i:%d,case(8)\n",i); break;
//				case(9):printf("i:%d,case(9)\n",i); break;
//				case(10):printf("i:%d,case(10)\n",i); break;
//				case(11): printf("i:%d,case(11)\n",i);break; 
//			}
//		}
//	}
//	GPIO_ResetBits(GPIOB,GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11);//置为低电平
	//INTX_ENABLE();//开启总中断
	//EXTI_ClearITPendingBit(EXTI_Line8|EXTI_Line9|EXTI_Line10|GPIO_Pin_11|KEY2_INT_EXTI_LINE);//清除Line上的中断标志位
}


/**
  * @brief  简单延时函数
  * @param  nCount ：延时计数值
  * @retval 无
  */	
static void Delay ( __IO uint32_t nCount )
{
  for ( ; nCount != 0; nCount -- );
	
}
/******************************************************************************/
/*                 STM32F10x Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f10x_xx.s).                                            */
/******************************************************************************/

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
