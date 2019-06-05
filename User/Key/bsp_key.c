//
// Created by qin on 2019/6/5.
//

#include "bsp_key.h"
#include "bsp_ili9341_lcd.h"
/*********************************************************************
*按键用的PA8-PA11,PB12-PB15
*PA8-PA11为推挽输出
*PB12-PB15为下拉输入
*********************************************************************/
void KEY_Init(void)//按键初始化
{
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE);    //使能A端口时钟
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;         //推挽输出
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//速度50MHz
    GPIO_Init(GPIOB, &GPIO_InitStructure);    //初始化GPIOB8-11

    //RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);    //使能B端口时钟
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;        //下拉输入/逐行扫描
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//速度50MHz
    GPIO_Init(GPIOB, &GPIO_InitStructure);    //初始化GPIOB12-15

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC | RCC_APB2Periph_AFIO, ENABLE);    //使能A端口时钟
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;         //推挽输出
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//速度50MHz
    GPIO_Init(GPIOC, &GPIO_InitStructure);    //初始化GPIOB8-11

    //RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);    //使能B端口时钟
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;        //下拉输入/逐行扫描
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//速度50MHz
    GPIO_Init(GPIOC, &GPIO_InitStructure);    //初始化GPIOB12-15
}

/*********************************************************************
*函数说明： 按键扫描
*返回值  :  按键值
*参数    ：  void
**********************************************************************/
int Key_Scan(void) {
    int keyValue = 0;//按键值
    u16 WriteVal = 0;//给PA口写入的数据
    __IO uint32_t nCount = 1000;
    GPIO_Write(GPIOB, ((GPIOB->ODR & 0x00ff) | 0x0f00));//让PA8-11输出高电平

    //printf("GPIOB->IDR:0x%x\n",GPIOB->IDR);
    if ((GPIOB->IDR & 0xf000) == 0x0000)//若PB12-PB15全为0，则没有按键按下
        return -1;
    else {
        //Delay(1000);//延时消抖
        for (; nCount != 0; nCount--){};
        if ((GPIOB->IDR & 0xf000) == 0x0000)//若PB12-PB15全为0，则刚刚是抖动产生
            return -1;

    }
    GPIO_Write(GPIOB, (GPIOB->ODR & 0xf0ff) | 0x0100);//让PA8-11输出0001，检测第四行
    switch (GPIOB->IDR & 0xf000) {
        case 0x1000 :
            keyValue = 0x59;
            break;//13 Y
        case 0x2000 :
            keyValue = 0x47;
            break;//14 G
        case 0x4000 :
            keyValue = 0x42;
            break;//15 B
        case 0x8000 :
            keyValue = 0x0D;
            break;//16 Enter
    }

    GPIO_Write(GPIOB, (GPIOB->ODR & 0xf0ff) | 0x0200);//让PA8-11输出0010，检测第三行
    switch (GPIOB->IDR & 0xf000) {
        case 0x1000 :
            keyValue = 0x55;
            break;//9 U
        case 0x2000 :
            keyValue = 0x48;
            break;//10 H
        case 0x4000 :
            keyValue = 0x4E;
            break;//11 N
        case 0x8000 :
            keyValue = 12;
            break;  //12
    }

    GPIO_Write(GPIOB, (GPIOB->ODR & 0xf0ff) | 0x0400);//让PA8-11输出0100，检测第二行
    switch (GPIOB->IDR & 0xf000) {
        case 0x1000 :
            keyValue = 0x49;
            break;//5 I
        case 0x2000 :
            keyValue = 0x4A;
            break;//6 J
        case 0x4000 :
            keyValue = 0x4D;
            break;//7 M
        case 0x8000 :
            keyValue = 0x08;
            break;//8 backspace
    }
    GPIO_Write(GPIOB, (GPIOB->ODR & 0xf0ff) | 0x0800);//让PA8-11输出1000，检测第一行
    switch (GPIOB->IDR & 0xf000) {
        case 0x1000 :
            keyValue = 0x4F;
            break;//1 O
        case 0x2000 :
            keyValue = 0x4B;
            break;//2 K
        case 0x4000 :
            keyValue = 0x4C;
            break;//3 L
        case 0x8000 :
            keyValue = 0x50;
            break;//4 P
    }

    return keyValue;
}

/*********************************************************************
*函数说明： 按键扫描
*返回值  :  按键值
*参数    ：  void
**********************************************************************/
int Key_Scan2(void) {
    int keyValue = 67;//按键值
    u16 WriteVal = 0;//给PA口写入的数据
    __IO uint32_t nCount = 1000;
    //printf("GPIOC->IDR1:0x%x\n",GPIOC->IDR);
    GPIO_Write(GPIOC, ((GPIOC->ODR & 0xf00f) | 0x00f0));//让PA4-7输出高电平
    //GPIO_WriteBit(GPIOC,GPIO_Pin_4 , 0);
    //printf("GPIOC->IDR2:0x%x\n",GPIOC->IDR);
    if ((GPIOC->IDR & 0x0f00) == 0x0000)//若PB8-PB12全为0，则没有按键按下
        return -1;
    else {
        //Delay(1000);//延时消抖
        for (; nCount != 0; nCount--){};
        if ((GPIOC->IDR & 0x0f00) == 0x0000)//若PB8-PB12全为0，则刚刚是抖动产生
            return -1;

    }
    GPIO_Write(GPIOC, (GPIOC->ODR & 0xff0f) | 0x0010);//让PA4-7输出0001，检测第四行

    switch (GPIOC->IDR & 0x0f00) {
        case 0x0100 :
            keyValue = 0x57;
            break;//13 W
        case 0x0200 :
            keyValue = 0x41;
            break;//14 A
        case 0x0400 :
            keyValue = 0x5A;
            break;//15 Z
        case 0x0800 :
            keyValue = 0x51;
            break;//16 Q
    }

    GPIO_Write(GPIOC, (GPIOC->ODR & 0xff0f) | 0x0020);//让PA4-7输出0010，检测第三行
    switch (GPIOC->IDR & 0x0f00) {
        case 0x0100 :
            keyValue = 0x45;
            break;//9 E
        case 0x0200 :
            keyValue = 0x53;
            break;//10 S
        case 0x0400 :
            keyValue = 0x58;
            break;//11 X
        case 0x0800 :
            keyValue = 0x10;
            break;//12 shift
    }

    GPIO_Write(GPIOC, (GPIOC->ODR & 0xff0f) | 0x0040);//让PA4-7输出0100，检测第二行
    switch (GPIOC->IDR & 0x0f00) {
        case 0x0100 :
            keyValue = 0x52;
            break;//5 R
        case 0x0200 :
            keyValue = 0x44;
            break;//6 D
        case 0x0400 :
            keyValue = 0x43;
            break;//7 C
        case 0x0800 :
            keyValue = 8;
            break;   //8
    }
    GPIO_Write(GPIOC, (GPIOC->ODR & 0xff0f) | 0x0080);//让PA4-7输出1000，检测第一行
    switch (GPIOC->IDR & 0x0f00) {
        case 0x0100 :
            keyValue = 0x54;
            break;//1 T
        case 0x0200 :
            keyValue = 0x46;
            break;//2 F
        case 0x0400 :
            keyValue = 0x56;
            break;//3 V
        case 0x0800 :
            keyValue = 0x20;
            break;//4  space
    }

    return keyValue;
}

void keyHandler(uint8_t key,uint8_t *pBuffer,uint64_t *pBuffer_start) {
    int out = key;
    printf("\n\npBuffer_start 0=%#llX\n\n", *pBuffer_start);
    printf("key:0x%x\n", key);
    //退格
    if (key == 0x08) {
        if (bufferCount > 0)
            bufferCount--;
        ILI9341_Clear(bufferCount % (LCD_Y_LENGTH / WIDTH_CH_CHAR), 0, WIDTH_CH_CHAR, WIDTH_CH_CHAR);    /* 清屏*/
        *pBuffer = 0x0;
        if ((pBuffer - (uint8_t *) pBuffer_start) > 0)
            pBuffer--;
    }
    //切换shift
    if (key == 0x10) {
        shift = !shift;
    }
    //上屏
    if (key == 0x0D) {
        printf("\n\n print pBuffer_start =%#llX\n\n", *pBuffer_start);
        ILI9341_DisplayStringEx(bufferCount % (LCD_Y_LENGTH / WIDTH_CH_CHAR),(bufferCount) / (LCD_Y_LENGTH / WIDTH_CH_CHAR) + 2, WIDTH_CH_CHAR, WIDTH_CH_CHAR,  getValueByKey((uint32_t) * toBigEndian(*pBuffer_start), CODES,
                                             "N"), 0);
        bufferCount++;
    }
    printf("buffer1 0x%x\n", *pBuffer);
    //编码上屏
    if ((key >= 0x41) || key == 0x20) {
        if (!shift && key != 0x20) {
            out += 0x20;
        }
        if ((pBuffer - (uint8_t *) pBuffer_start) < 8) {
            *pBuffer = out;
            printf("pBuffer_start 0x%x\n", *pBuffer);
            ILI9341_DisplayStringEx(bufferCount % (LCD_Y_LENGTH / WIDTH_CH_CHAR), 0, WIDTH_CH_CHAR, WIDTH_CH_CHAR,(char *) &out, 0);
            pBuffer++;
            bufferCount++;
        }
    }
}