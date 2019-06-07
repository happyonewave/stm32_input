//
// Created by qin on 2019/6/5.
//

#include <stdlib.h>
#include "code.h"
#include "fonts.h"
#include "ff.h"

uint16_t getValueByKey(uint32_t key, const Kv *array, char *def) {
    int i = 0;
    printf(" getValueByKey key:%#X\n", key);
    while (array[i].value != NULL && array[i].key != key) {
//printf(" array[i].id:%#X\n",array[i].id);
        i++;
    }

    printf(" array[i].value:%#X\n", *((uint32_t * )(array[i].value)));
    if (array[i].value == NULL)
        return *def;
    return array[i].value;
}

uint16_t GetHangulCode_from_sd(uint32_t key,char *def) {
    static FIL fnew;
    static FATFS fs;
    static FRESULT res_sd;
    static UINT br;
    unsigned int pos;
    static uint8_t everRead = 0;
    const Kv kv[1];
    printf("GetHangulCode_from_sd key:0x%x\n", key);
    pos = 0;
    /*第一次使用，挂载文件系统，初始化sd*/
    if (everRead == 0) {
        res_sd = f_mount(&fs, "0:", 1);
        everRead = 1;

    }

    res_sd = f_open(&fnew, HANGULCODE_FILE_NAME, FA_OPEN_EXISTING | FA_READ);

    if (res_sd == FR_OK) {
        do {
            f_lseek(&fnew, pos);        //指针偏移
            res_sd = f_read(&fnew, (void *)kv, 6, &br);
            pos += 6;
           // printf("");
            //printf("key:%#X,value:%#X\n", (*kv).key, (*kv).value);
        } while ((*kv).value != NULL && (*kv).key != key);

        f_close(&fnew);
        printf(" return key:%#X,value:%#X\n", (*kv).key, (*kv).value);
        if ((*kv).value == NULL)
            return *def;
        return (*kv).value;
    }
    return *def;
}

uint32_t utf_to_unicode(uint32_t utf8) {
    uint32_t result;
    uint32_t one;
    uint32_t two;
    uint32_t three;
    uint32_t four;
    printf("utf8 %#X\n", utf8);
    if (utf8<=0x7f){
        result = utf8;
        printf(" one:%#X\n", result);
    }else if (utf8 >= 0xC080 && utf8<=0xdfbf){
        one = (utf8 & 0x1f00)>>2;
        two = utf8 & 0x3f;
        result = one +two;
        printf("one:%#X", one);
        printf(" two:%#X\n", two);
    }else if (utf8 >= 0xE08080 && utf8<=0xefbfbf){
        one = (utf8 & 0xf0000)>>4;
        two = (utf8 & 0x3f00)>>2;
        three = utf8 & 0x3f;
        result = one+two+three;
        printf("one:%#X", one);
        printf(" two:%#X", two);
        printf(" three:%#X\n", three);
    }else if (utf8 >= 0xF0808080 && utf8<=0xf7bfbfbf){
        one = (utf8 & 0x7000000)>>6;
        two = (utf8 & 0x3f0000)>>4;
        three = (utf8 & 0x3f00)>>2;
        four = utf8 & 0x3f;
        result = one+two+three+four;
        printf("one:%#X", one);
        printf(" two:%#X", two);
        printf(" three:%#X", three);
        printf(" four:%#X\n", four);
    }
    return result;
}
uint32_t UnicodeToUtf8(uint16_t unicode){
	uint32_t result = 0xe08080;
	// printf("unicode %#X\n", unicode);
  uint32_t one = (unicode &0xf000)<<4;
  uint32_t two = (unicode &0xfc0)<<2;
  uint32_t there = unicode &0x3f;
  result = result+one+two+there;

return result;
}
uint64_t *toBigEndian(uint64_t src) {
    uint64_t str1;
    uint64_t str2;
    uint64_t str3;
    uint64_t str4;
    uint64_t *result = (uint64_t *) malloc(8);
    printf("src:%#llX\n", src);
    if ((src) <= 0xff) {
        *result = src;
    } else if ((src) <= 0xffff) {
        str1 = ((src) & 0x00ff) << 2 * 4;
        str2 = ((src) & 0xff00) >> 2 * 4;
        printf("str1:%#llX\n", str1);
        printf("str2:%#llX\n", str2);
        *result = str1 + str2;
    } else if ((src) <= 0xffffff) {
        str1 = ((src) & 0x0000ff) << 4 * 4;
        str2 = (src) & 0x00ff00;
        str3 = ((src) & 0xff0000) >> 4 * 4;
        printf("str1:%#llX\n", str1);
        printf("str2:%#llX\n", str2);
        printf("str3:%#llX\n", str3);
        *result = str1 + str2 + str3;
    } else if ((src) <= 0xffffffff) {
        str1 = ((src) & 0x000000ff) << 6 * 4;
        str2 = ((src) & 0x0000ff00) << 2 * 4;
        str3 = ((src) & 0x00ff0000) >> 2 * 4;
        str4 = ((src) & 0xff000000) >> 6 * 4;
        printf("str1:%#llX\n", str1);
        printf("str2:%#llX\n", str2);
        printf("str3:%#llX\n", str3);
        printf("str4:%#llX\n", str4);
        *result = str1 + str2 + str3 + str4;
    }
    printf("result:%llX\n", *result);
    return result;

}