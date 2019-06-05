/**
  ******************************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2013-xx-xx
  * @brief   液晶显示汉字实验（字模文件在SD卡）
  ******************************************************************************
  * @attention
  *
  * 实验平台:野火 F103-MINI STM32 开发板 
  * 论坛    :http://www.firebbs.cn
  * 淘宝    :https://fire-stm32.taobao.com
  *
  ******************************************************************************
  */

#include <string.h>
#include <stdlib.h>
#include "stm32f10x.h"
#include "bsp_usart.h"
#include "bsp_ili9341_lcd.h"
#include "bsp_led.h"
#include "bsp_exti.h"
#include "bsp_key.h"

static void LCD_Test(void);

static void Delay(__IO uint32_t nCount);

uint8_t *pBuffer;
uint64_t *pBuffer_start;
//char dispBuff[100];
int key;
int key2;

int main(void) {
    //为buffer分配内存空间
    pBuffer = (uint8_t *) malloc(8);
    //记录起始地址
    pBuffer_start = (uint64_t *) pBuffer;
    //LCD 初始化
    ILI9341_Init();

    /* USART config */
    USART_Config();
    KEY_Init();
    printf("GPIOA->IDR:0x%x\n", GPIOA->IDR);
    printf("GPIOB->IDR:0x%x\n", GPIOB->IDR);
    printf("GPIOB->IDR:0x%x\n", GPIOB->IDR);
    printf("GPIOC->IDR:0x%x\n", GPIOC->IDR);
    printf("GPIOC->IDR:0x%x\n", GPIOC->IDR);
    printf("buffer 0x%x\n", *pBuffer);

    /* LED 端口初始化 */
    //LED_GPIO_Config();

    /* 初始化EXTI中断，按下按键会触发中断，
  *  触发中断会进入stm32f4xx_it.c文件中的函数
	*  KEY1_IRQHandler和KEY2_IRQHandler，处理中断，反转LED灯。
	*/
    //EXTI_Key_Config();
    //EXTIX_Init();

    //指定显示模式
    ILI9341_GramScan(3);

    //Printf_Charater();

    LCD_SetFont(&Font8x16);
    LCD_SetColors(RED, BLACK);

    ILI9341_Clear(0, 0, LCD_X_LENGTH, LCD_Y_LENGTH);    /* 清屏，显示全黑 */

    while (1) {
        key = Key_Scan();
        if (key != -1) {
             keyHandler(key, pBuffer, pBuffer_start);
    while (Key_Scan() == key) {}
        }
        key2 = Key_Scan2();
        if (key2 != -1) {
             keyHandler(key2, pBuffer, pBuffer_start);
    while (Key_Scan2() == key2) {}
        }

        //while ( 1 )
        //{
        //LCD_Test();
        //}


    }
}


/*用于测试各种液晶的函数*/
void LCD_Test(void) {
    /*演示显示变量*/
    static uint8_t bufferCount = 0;
    char dispBuff[100];

    bufferCount++;

    LCD_SetFont(&Font8x16);
    LCD_SetColors(RED, BLACK);

    ILI9341_Clear(0, 0, LCD_X_LENGTH, LCD_Y_LENGTH);    /* 清屏，显示全黑 */
    /********显示字符串示例*******/
    //ILI9341_DispStringLine_EN_CH(LINE(0),L"daz");
    //ILI9341_DispStringLine_EN_CH(LINE(1),L"-=./,");
    //sILI9341_DispStringLine_EN_CH(LINE(2),L"对");
    //ILI9341_DispStringLine_EN_CH(LINE(0),"野火3.2_2.8寸LCD参数：");
    //ILI9341_DispStringLine_EN_CH(LINE(1),"分辨率：240x320 px");
    //ILI9341_DispStringLine_EN_CH(LINE(2),"ILI9341液晶驱动");
    //ILI9341_DispStringLine_EN_CH(LINE(3),"XPT2046触摸屏驱动");

    /********显示变量示例*******/
    LCD_SetTextColor(GREEN);

    /*使用c标准库把变量转化成字符串*/
    //sprintf(dispBuff,"显示变量： %d ",bufferCount);
    LCD_ClearLine(LINE(5));    /* 清除单行文字 */

    /*然后显示该字符串即可，其它变量也是这样处理*/
    //ILI9341_DispStringLine_EN_CH(LINE(5),dispBuff);

    /*******显示图形示例******/
    /* 画直线 */

    LCD_ClearLine(LINE(7));/* 清除单行文字 */
    LCD_SetTextColor(BLUE);

    //ILI9341_DispStringLine_EN_CH(LINE(7),L"画直线：");

    LCD_SetTextColor(RED);
    ILI9341_DrawLine(50, 170, 210, 230);
    ILI9341_DrawLine(50, 200, 210, 240);

    LCD_SetTextColor(GREEN);
    ILI9341_DrawLine(100, 170, 200, 230);
    ILI9341_DrawLine(200, 200, 220, 240);

    LCD_SetTextColor(BLUE);
    ILI9341_DrawLine(110, 170, 110, 230);
    ILI9341_DrawLine(130, 200, 220, 240);

    Delay(0xFFFFFF);

    ILI9341_Clear(0, 16 * 8, LCD_X_LENGTH, LCD_Y_LENGTH - 16 * 8);    /* 清屏，显示全黑 */


    /*画矩形*/

    LCD_ClearLine(LINE(7));    /* 清除单行文字 */
    LCD_SetTextColor(BLUE);

    //ILI9341_DispStringLine_EN_CH(LINE(7),L"画矩形：");

    LCD_SetTextColor(RED);
    ILI9341_DrawRectangle(50, 200, 100, 30, 1);

    LCD_SetTextColor(GREEN);
    ILI9341_DrawRectangle(160, 200, 20, 40, 0);

    LCD_SetTextColor(BLUE);
    ILI9341_DrawRectangle(170, 200, 50, 20, 1);

    Delay(0xFFFFFF);

    ILI9341_Clear(0, 16 * 8, LCD_X_LENGTH, LCD_Y_LENGTH - 16 * 8);    /* 清屏，显示全黑 */

    /* 画圆 */
    LCD_ClearLine(LINE(7));    /* 清除单行文字 */
    LCD_SetTextColor(BLUE);

    //ILI9341_DispStringLine_EN_CH(LINE(7),L"画圆");

    LCD_SetTextColor(RED);
    ILI9341_DrawCircle(100, 200, 20, 0);

    LCD_SetTextColor(GREEN);
    ILI9341_DrawCircle(100, 200, 10, 1);

    LCD_SetTextColor(BLUE);
    ILI9341_DrawCircle(140, 200, 20, 0);

    Delay(0xFFFFFF);

    ILI9341_Clear(0, 16 * 8, LCD_X_LENGTH, LCD_Y_LENGTH - 16 * 8);    /* 清屏，显示全黑 */

}


/**
  * @brief  简单延时函数
  * @param  nCount ：延时计数值
  * @retval 无
  */
static void Delay(__IO uint32_t nCount) {
    for (; nCount != 0; nCount--);

}


/*"当"字符的字模16x16 */
unsigned char charater_matrix[] =
        { /*"当",0*/
                0x01, 0x00, 0x21, 0x08, 0x11, 0x08, 0x09, 0x10, 0x09, 0x20, 0x01, 0x00, 0x7F, 0xF8, 0x00, 0x08,
                0x00, 0x08, 0x00, 0x08, 0x3F, 0xF8, 0x00, 0x08, 0x00, 0x08, 0x00, 0x08, 0x7F, 0xF8, 0x00, 0x08,

        };




/* ------------------------------------------end of file---------------------------------------- */

