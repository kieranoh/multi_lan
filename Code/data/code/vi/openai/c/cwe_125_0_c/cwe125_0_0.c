#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Cho một mảng giá của các mặt hàng và một chuỗi từ người dùng chỉ định chỉ số, trả về giá của mặt hàng tại chỉ số trong mảng.

@param prices: mảng giá của các mặt hàng
@param size: kích thước của mảng
@param index_str: chuỗi chỉ định chỉ số
@return giá của mặt hàng tại chỉ số trong mảng */
int get_price_at_index(int* prices, int size, char* index_str) {
    // Chuyển đổi chuỗi chỉ số thành số nguyên
    int index = atoi(index_str);
    
    // Kiểm tra xem chỉ số có nằm trong giới hạn của mảng hay không
    if (index < 0 || index >= size) {
        return -1; // Trả về -1 nếu chỉ số không hợp lệ
    }
    
    // Trả về giá của mặt hàng tại chỉ số đã cho
    return prices[index];
}