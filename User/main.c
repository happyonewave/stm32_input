#include <string.h>
#include <stdlib.h>
#include "stm32f10x.h"
#include "bsp_usart.h"
#include "bsp_ili9341_lcd.h"
#include "bsp_led.h"
#include "bsp_exti.h"
#include "bsp_key.h"


static void Delay(__IO uint32_t nCount);

static uint8_t *pBuffer;
static uint64_t *pBuffer_start;

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
    LED_GPIO_Config();

    /* 初始化EXTI中断，按下按键会触发中断，
  *  触发中断会进入stm32f4xx_it.c文件中的函数
	*  KEY1_IRQHandler和KEY2_IRQHandler，处理中断，反转LED灯。
	*/
    //EXTI_Key_Config();
    //EXTIX_Init();

    //指定显示模式
    ILI9341_GramScan(3);

    LCD_SetFont(&Font8x16);
    LCD_SetColors(RED, BLACK);

    ILI9341_Clear(0, 0, LCD_X_LENGTH, LCD_Y_LENGTH);    /* 清屏，显示全黑 */

    //ILI9341_DispStringLine_EN_CH(LINE(7),0,"||");
    //scanf("%d",&time);
    while (1) {
        key = Key_Scan();
        if (key != -1) {
           pBuffer =  keyHandler(key, pBuffer, pBuffer_start);
    while (Key_Scan() == key) {}
        }
        key2 = Key_Scan2();
        if (key2 != -1) {
           pBuffer =  keyHandler(key2, pBuffer, pBuffer_start);
    while (Key_Scan2() == key2) {}
        }
        Delay(500000);
        showCursor();
    }
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

