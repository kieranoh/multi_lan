#include <string.h>

/* sử dụng strncpy để sao chép nội dung của src sang dest nhiều nhất có thể

@param dest: bộ đệm đích
@param dest_size: kích thước của bộ đệm đích
@param src: bộ đệm nguồn
@param src_size: kích thước của bộ đệm nguồn */
void copy_to_dest(char* dest, int dest_size, char* src, int src_size) {
    if (dest == NULL || src == NULL || dest_size <= 0 || src_size <= 0) {
        return; // không làm gì nếu đầu vào không hợp lệ
    }
    
    // Sao chép nội dung của src sang dest
    strncpy(dest, src, dest_size - 1);
    
    // Đảm bảo chuỗi dest được kết thúc bằng ký tự null
    dest[dest_size - 1] = '\0';
}