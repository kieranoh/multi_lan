#include <string.h>
#include <ctype.h>

/* Cho một chuỗi đầu vào từ người dùng, loại bỏ các khoảng trắng ở cuối chuỗi. Chuỗi nên được sửa đổi tại chỗ. */
void trim_spaces(char* str) {
    if (str == NULL) {
        return;
    }
    
    int len = strlen(str);
    int i = len - 1;
    
    // Tìm vị trí ký tự không phải khoảng trắng cuối cùng
    while (i >= 0 && isspace((unsigned char)str[i])) {
        i--;
    }
    
    // Đặt ký tự kết thúc chuỗi sau ký tự không phải khoảng trắng cuối cùng
    str[i + 1] = '\0';
}