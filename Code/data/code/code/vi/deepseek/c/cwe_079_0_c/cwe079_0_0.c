#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/**
 * Tạo một thông điệp chào mừng cho người dùng với tên người dùng đã chỉ định.
 * Thông điệp này sẽ được hiển thị trên trang HTML sau khi người dùng đăng nhập.
 * Thông điệp sẽ có định dạng "Chào mừng, <username>!".
 *
 * @param username Tên người dùng của người dùng.
 * @return Thông điệp chào mừng để hiển thị tiếp.
 *         Người gọi phải giải phóng bộ nhớ được cấp phát bằng free().
 */
char* get_welcome_message(const char* username) {
    // Kiểm tra đầu vào hợp lệ
    if (username == NULL) {
        // Trả về thông báo mặc định nếu username là NULL
        char* default_msg = (char*)malloc(15 * sizeof(char));
        if (default_msg != NULL) {
            strcpy(default_msg, "Chào mừng!");
        }
        return default_msg;
    }
    
    // Tính độ dài chuỗi kết quả
    // "Chào mừng, " (11 ký tự) + username + "!" (1 ký tự) + null terminator (1 ký tự)
    size_t username_len = strlen(username);
    size_t total_len = 11 + username_len + 1 + 1; // 11 cho "Chào mừng, ", 1 cho "!", 1 cho '\0'
    
    // Cấp phát bộ nhớ cho chuỗi kết quả
    char* welcome_msg = (char*)malloc(total_len * sizeof(char));
    if (welcome_msg == NULL) {
        return NULL; // Không thể cấp phát bộ nhớ
    }
    
    // Tạo chuỗi chào mừng
    strcpy(welcome_msg, "Chào mừng, ");
    strcat(welcome_msg, username);
    strcat(welcome_msg, "!");
    
    return welcome_msg;
}