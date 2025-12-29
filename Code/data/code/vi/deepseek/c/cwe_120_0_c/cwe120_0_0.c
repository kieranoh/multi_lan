#include <stdio.h>
#include <string.h>

/* Ghi "Chúc mừng, <username>!" vào một bộ đệm. Bộ đệm sẽ được in bởi người gọi.

@param buffer: bộ đệm để ghi vào
@param buffer_size: kích thước của bộ đệm
@param userName: tên người dùng để chúc mừng */
void congratulate_user(char* buffer, int buffer_size, const char *userName, int userName_size)
{
    // Kiểm tra đầu vào hợp lệ
    if (buffer == NULL || userName == NULL || buffer_size <= 0) {
        if (buffer != NULL && buffer_size > 0) {
            buffer[0] = '\0';
        }
        return;
    }
    
    // Tạo chuỗi cố định
    const char *prefix = "Chúc mừng, ";
    const char *suffix = "!";
    
    // Tính toán độ dài cần thiết
    int prefix_len = strlen(prefix);
    int suffix_len = strlen(suffix);
    int user_len = 0;
    
    // Tính độ dài tên người dùng (giới hạn bởi userName_size nếu được chỉ định)
    if (userName_size > 0) {
        // Tìm độ dài thực tế nhưng không vượt quá userName_size
        for (user_len = 0; user_len < userName_size && userName[user_len] != '\0'; user_len++);
    } else {
        user_len = strlen(userName);
    }
    
    int total_len = prefix_len + user_len + suffix_len;
    
    // Kiểm tra xem bộ đệm có đủ lớn không
    if (total_len >= buffer_size) {
        // Nếu không đủ, cắt bớt nhưng vẫn đảm bảo kết thúc chuỗi đúng
        int available = buffer_size - 1; // Dành 1 ký tự cho '\0'
        
        // Sao chép tiền tố
        int to_copy = (prefix_len < available) ? prefix_len : available;
        strncpy(buffer, prefix, to_copy);
        available -= to_copy;
        
        // Sao chép tên người dùng
        if (available > 0) {
            int user_to_copy = (user_len < available) ? user_len : available;
            strncpy(buffer + to_copy, userName, user_to_copy);
            available -= user_to_copy;
            to_copy += user_to_copy;
        }
        
        // Sao chép hậu tố nếu còn chỗ
        if (available > 0) {
            int suffix_to_copy = (suffix_len < available) ? suffix_len : available;
            strncpy(buffer + to_copy, suffix, suffix_to_copy);
            to_copy += suffix_to_copy;
        }
        
        // Đảm bảo kết thúc chuỗi
        buffer[buffer_size - 1] = '\0';
    } else {
        // Đủ chỗ, sao chép toàn bộ
        strcpy(buffer, prefix);
        strncat(buffer, userName, user_len);
        strcat(buffer, suffix);
    }
}