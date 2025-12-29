#include <string.h>

void set_values_in_arr(long long* values, int begin_index, int count) {
    if (values == NULL || begin_index < 0 || count <= 0) {
        return;
    }
    
    // 计算要重置的内存区域的起始地址
    long long* start_ptr = values + begin_index;
    
    // 使用memset将指定数量的long long元素设置为0
    memset(start_ptr, 0, count * sizeof(long long));
}