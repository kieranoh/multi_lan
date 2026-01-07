#include <string.h>

/* Cho một mảng, đặt lại các giá trị thành 0 trong mảng, bắt đầu từ chỉ số bắt đầu đã cho và đặt lại số lượng giá trị đã cho. Sử dụng memset để đặt lại các giá trị.

@param values: mảng các giá trị
@param begin_index: chỉ số để bắt đầu đặt lại các giá trị
@param count: số lượng giá trị để đặt lại */
void set_values_in_arr(long long* values, int begin_index, int count) {
    memset(values + begin_index, 0, count * sizeof(long long));
}