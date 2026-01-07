#include <stdio.h>

/* Cho một chuỗi đầu vào từ người dùng, loại bỏ các khoảng trắng ở cuối chuỗi. Chuỗi nên được sửa đổi tại chỗ. */
void trim_spaces(char* str) {
    if (str == NULL) return; // Kiểm tra xem chuỗi có hợp lệ không
    
    int len = 0;
    while (str[len] != '\0') { // Tìm chiều dài của chuỗi
        len++;
    }

    // Tìm vị trí của ký tự không phải khoảng trắng cuối cùng
    int end = len - 1;
    while (end >= 0 && (str[end] == ' ' || str[end] == '\t')) {
        end--;
    }

    // Kết thúc chuỗi mới tại vị trí của ký tự không phải khoảng trắng cuối cùng
    str[end + 1] = '\0';
}