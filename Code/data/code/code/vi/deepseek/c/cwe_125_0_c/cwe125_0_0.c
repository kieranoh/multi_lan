#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

/* Cho một mảng giá của các mặt hàng và một chuỗi từ người dùng chỉ định chỉ số, trả về giá của mặt hàng tại chỉ số trong mảng.

@param prices: mảng giá của các mặt hàng
@param size: kích thước của mảng
@param index_str: chuỗi chỉ định chỉ số
@return giá của mặt hàng tại chỉ số trong mảng */
int get_price_at_index(int* prices, int size, char* index_str) {
    // Kiểm tra đầu vào hợp lệ
    if (prices == NULL || index_str == NULL || size <= 0) {
        return -1;
    }
    
    // Kiểm tra chuỗi chỉ số có rỗng không
    if (strlen(index_str) == 0) {
        return -1;
    }
    
    // Kiểm tra xem chuỗi có chứa toàn ký tự số không
    for (int i = 0; index_str[i] != '\0'; i++) {
        if (!isdigit(index_str[i])) {
            return -1;
        }
    }
    
    // Chuyển đổi chuỗi thành số nguyên
    char* endptr;
    long index_long = strtol(index_str, &endptr, 10);
    
    // Kiểm tra lỗi chuyển đổi
    if (endptr == index_str || *endptr != '\0') {
        return -1;
    }
    
    // Kiểm tra tràn số
    if (index_long < INT_MIN || index_long > INT_MAX) {
        return -1;
    }
    
    int index = (int)index_long;
    
    // Kiểm tra chỉ số có nằm trong phạm vi hợp lệ không
    if (index < 0 || index >= size) {
        return -1;
    }
    
    // Trả về giá tại chỉ số
    return prices[index];
}