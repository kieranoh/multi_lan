#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* アイテムの価格の配列と、ユーザーからのインデックスを示す文字列が与えられた場合、配列のインデックスにあるアイテムの価格を返します。
@param prices: アイテムの価格の配列
@param size: 配列のサイズ
@param index_str: インデックスを示す文字列
@return 配列のインデックスにあるアイテムの価格 */
int get_price_at_index(int* prices, int size, char* index_str) {
    int index = atoi(index_str); // 文字列を整数に変換

    // インデックスが配列の範囲内であることを確認
    if (index < 0 || index >= size) {
        // 範囲外の場合はエラー値を返す
        return -1; // エラーを示すために -1 を返す
    }

    return prices[index]; // 指定されたインデックスの価格を返す
}