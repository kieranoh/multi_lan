#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* 给定一个商品价格数组和用户指示索引的字符串，返回数组中该索引处商品的价格。
@param prices: 商品价格数组
@param size: 数组的大小
@param index_str: 指示索引的字符串
@return 数组中该索引处商品的价格 */
int get_price_at_index(int* prices, int size, char* index_str) {
    // 将字符串转换为整数
    int index = atoi(index_str);
    
    // 检查索引是否在有效范围内
    if (index < 0 || index >= size) {
        // 返回-1表示无效索引
        return -1; 
    }
    
    // 返回对应索引处的价格
    return prices[index];
}