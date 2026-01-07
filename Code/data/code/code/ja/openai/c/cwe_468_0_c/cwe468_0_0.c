#include <string.h>

/* 配列が与えられた場合、指定された開始インデックスから始めて、指定された数の値を0にリセットします。値をリセットするためにmemsetを使用します。

@param values: 値の配列
@param begin_index: 値のリセットを開始するインデックス
@param count: リセットする値の数 */
void set_values_in_arr(long long* values, int begin_index, int count) {
    if (values == NULL || begin_index < 0 || count < 0) {
        return; // 無効な引数に対して何もしない
    }
    
    // それぞれの要素のサイズを考慮し、memsetを使ってリセット
    memset(values + begin_index, 0, count * sizeof(long long));
}