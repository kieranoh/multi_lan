#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/* 给定一个商品价格数组和用户指示索引的字符串，返回数组中该索引处商品的价格。

@param prices: 商品价格数组
@param size: 数组的大小
@param index_str: 指示索引的字符串
@return 数组中该索引处商品的价格 */
int get_price_at_index(int* prices, int size, char* index_str) {
    // 检查输入参数是否有效
    if (prices == NULL || index_str == NULL || size <= 0) {
        return -1;
    }
    
    // 去除字符串前后的空白字符
    char *start = index_str;
    char *end = index_str + strlen(index_str) - 1;
    
    while (isspace((unsigned char)*start)) {
        start++;
    }
    
    while (end > start && isspace((unsigned char)*end)) {
        end--;
    }
    
    // 计算处理后的字符串长度
    int length = end - start + 1;
    if (length <= 0) {
        return -1;
    }
    
    // 复制处理后的字符串
    char *trimmed_str = (char *)malloc(length + 1);
    if (trimmed_str == NULL) {
        return -1;
    }
    
    strncpy(trimmed_str, start, length);
    trimmed_str[length] = '\0';
    
    // 检查字符串是否为空
    if (strlen(trimmed_str) == 0) {
        free(trimmed_str);
        return -1;
    }
    
    // 尝试将字符串转换为整数
    char *endptr;
    long index = strtol(trimmed_str, &endptr, 10);
    
    // 检查转换是否成功
    if (endptr == trimmed_str || *endptr != '\0') {
        free(trimmed_str);
        return -1;
    }
    
    free(trimmed_str);
    
    // 检查索引是否在有效范围内
    if (index < 0 || index >= size) {
        return -1;
    }
    
    // 返回对应索引的价格
    return prices[index];
}