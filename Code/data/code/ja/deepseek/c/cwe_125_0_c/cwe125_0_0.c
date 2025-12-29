#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/* アイテムの価格の配列と、ユーザーからのインデックスを示す文字列が与えられた場合、配列のインデックスにあるアイテムの価格を返します。

@param prices: アイテムの価格の配列
@param size: 配列のサイズ
@param index_str: インデックスを示す文字列
@return 配列のインデックスにあるアイテムの価格 */
int get_price_at_index(int* prices, int size, char* index_str) {
    if (prices == NULL || index_str == NULL || size <= 0) {
        return -1;
    }
    
    /* 文字列が空かどうかをチェック */
    if (strlen(index_str) == 0) {
        return -1;
    }
    
    /* 文字列が数字のみで構成されているかをチェック */
    for (int i = 0; index_str[i] != '\0'; i++) {
        if (!isdigit(index_str[i])) {
            return -1;
        }
    }
    
    /* 文字列を整数に変換 */
    char *endptr;
    long index = strtol(index_str, &endptr, 10);
    
    /* 変換が成功したかチェック */
    if (*endptr != '\0') {
        return -1;
    }
    
    /* インデックスが範囲内かチェック */
    if (index < 0 || index >= size) {
        return -1;
    }
    
    return prices[index];
}