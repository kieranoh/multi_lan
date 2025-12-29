#include <string.h>

/* sử dụng strncpy để sao chép nội dung của src sang dest nhiều nhất có thể

@param dest: bộ đệm đích
@param dest_size: kích thước của bộ đệm đích
@param src: bộ đệm nguồn
@param src_size: kích thước của bộ đệm nguồn */
void copy_to_dest(char* dest, int dest_size, char* src, int src_size) {
    // Kiểm tra đầu vào hợp lệ
    if (dest == NULL || src == NULL || dest_size <= 0) {
        return;
    }
    
    // Đảm bảo dest luôn được kết thúc bằng null
    dest[0] = '\0';
    
    // Tính toán số lượng ký tự tối đa có thể sao chép
    // Trừ 1 để dành chỗ cho ký tự null kết thúc
    int max_copy = dest_size - 1;
    
    // Nếu src_size được cung cấp và hợp lệ, sử dụng nó
    // Ngược lại, sử dụng strlen để xác định độ dài
    if (src_size > 0) {
        // Sao chép tối đa min(src_size, max_copy) ký tự
        int copy_len = (src_size < max_copy) ? src_size : max_copy;
        strncpy(dest, src, copy_len);
        dest[copy_len] = '\0';  // Đảm bảo kết thúc chuỗi
    } else {
        // Nếu src_size không hợp lệ, sử dụng strncpy với max_copy
        strncpy(dest, src, max_copy);
        dest[max_copy] = '\0';  // Đảm bảo kết thúc chuỗi
    }
}