//
// Created by qin on 2019/6/5.
//

#include <stdlib.h>
#include "code.h"
char *getValueByKey(uint32_t key, const kv *array, char *def) {
    int i = 0;
    printf(" getValueByKey key:%#X\n", key);
    while (array[i].value != NULL && array[i].key != key) {
//printf(" array[i].id:%#X\n",array[i].id);
        i++;
    }

    printf(" array[i].value:%#X\n", *((uint32_t *)(array[i].value)));
    if (array[i].value == NULL)
        return def;
    return array[i].value;
}

uint32_t utf_to_unicode(unsigned long utf) {
    int size = 0;
    unsigned char unicode[9];
    uint32_t result = 0;
    int i = 0;
    int j = 0;
    if (utf <= 0x7F) {
        *(unicode + size++) = utf & 0x7F;
    } else if (utf >= 0xC080 && utf <= 0xCFBF) {
        *(unicode + size++) = ((utf >> 10) & 0x07);
        *(unicode + size++) = (utf & 0x3F) | (((utf >> 8) & 0x03) << 6);
    } else if (utf >= 0xE08080 && utf <= 0xEFBFBF) {
        *(unicode + size++) = ((utf >> 10) & 0x0F) | ((utf >> 16) & 0x0F) << 4;
        *(unicode + size++) = (utf & 0x3F) | (((utf >> 8) & 0x03) << 6);
    } else if (utf >= 0xF0808080 && utf <= 0xF7BFBFBF) {
        *(unicode + size++) = ((utf >> 20) & 0x03) | (((utf >> 24) & 0x07) << 2);
        *(unicode + size++) = ((utf >> 10) & 0x0F) | (((utf >> 16) & 0x0F) << 4);
        *(unicode + size++) = (utf & 0x3F) | ((utf >> 8) & 0x03) << 6;
    } else if (utf >= 0xF880808080 && utf <= 0xFBBFBFBFBF) {
        *(unicode + size++) = (utf >> 32) & 0x03;
        *(unicode + size++) = ((utf >> 20) & 0x03) | (((utf >> 24) & 0x3F) << 2);
        *(unicode + size++) = ((utf >> 10) & 0x0F) | (((utf >> 16) & 0x0F) << 4);
        *(unicode + size++) = (utf & 0x3F) | (((utf >> 8) & 0x03) << 6);
    } else if (utf >= 0xFC8080808080 && utf <= 0xFDBFBFBFBFBF) {
        *(unicode + size++) = ((utf >> 32) & 0x3F) | (((utf >> 40) & 0x01) << 6);
        *(unicode + size++) = ((utf >> 20) & 0x03) | (((utf >> 24) & 0x3F) << 2);
        *(unicode + size++) = ((utf >> 10) & 0x0F) | (((utf >> 16) & 0x0F) << 4);
        *(unicode + size++) = (utf & 0x3F) | (((utf >> 8) & 0x03) << 6);
    } else {
        printf("Error : unknow scope\n");
        return -1;
    }
    *(unicode + size) = '\0';
    if (size == -1) {
        printf("Error : unknow scope\n");
        return 0;
    }
    for (; i < size; i++) {
        result = result << (j * 2 * 4);
        result += *(unicode + i);
        j++;
    }
		
    printf("utf_to_unicode result:%#X\n", result);
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