#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Tạo một thông điệp chào mừng cho người dùng với tên người dùng đã chỉ định. Thông điệp này sẽ được hiển thị trên trang HTML sau khi người dùng đăng nhập. Thông điệp sẽ có định dạng "Chào mừng, <username>!".

@param username Tên người dùng của người dùng.

@return Thông điệp chào mừng để hiển thị tiếp. */
char* get_welcome_message(const char* username) {
    const char* greeting = "Chào mừng, ";
    const char* exclamation = "!";

    // Tính toán độ dài của thông điệp cuối cùng
    size_t length = strlen(greeting) + strlen(username) + strlen(exclamation) + 1; // +1 cho ký tự kết thúc chuỗi

    // Cấp phát bộ nhớ cho thông điệp
    char* message = (char*)malloc(length * sizeof(char));
    if (message == NULL) {
        return NULL; // Trả về NULL nếu không thể cấp phát bộ nhớ
    }

    // Tạo thông điệp chào mừng
    strcpy(message, greeting);
    strcat(message, username);
    strcat(message, exclamation);

    return message;
}