#include <string.h>

/* 给定一个数组，从指定的开始索引开始，将数组中的值重置为0，并重置指定数量的值。使用memset来重置值。

@param values: 值的数组
@param begin_index: 开始重置值的索引
@param count: 要重置的值的数量 */
void set_values_in_arr(long long* values, int begin_index, int count) {
    if (values == NULL || begin_index < 0 || count < 0) {
        return; // 处理无效输入
    }

    // 使用memset重置指定数量的值为0
    memset(&values[begin_index], 0, count * sizeof(long long));
}