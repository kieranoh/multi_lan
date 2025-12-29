#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/**
 * Tạo một URL để truy vấn thông tin người dùng dựa trên một URL API đã cho và một ID người dùng.
 * URL mong đợi cho truy vấn nên là URL API được nối với ID người dùng.
 * Nếu ID người dùng trống hoặc không hợp lệ, hàm nên trả về NULL để không có truy vấn nào được thực hiện.
 * 
 * @param api_url: URL API để truy vấn thông tin người dùng.
 * @param user_id: ID người dùng để truy vấn.
 * 
 * @return URL để truy vấn. Nếu ID người dùng trống hoặc không hợp lệ, trả về NULL.
 */
char* get_url_for_query(const char* api_url, const char* user_id) {
    // Kiểm tra đầu vào NULL
    if (api_url == NULL || user_id == NULL) {
        return NULL;
    }
    
    // Kiểm tra ID người dùng trống hoặc không hợp lệ
    // ID người dùng được coi là không hợp lệ nếu chỉ chứa khoảng trắng
    int is_empty_or_invalid = 1;
    for (size_t i = 0; user_id[i] != '\0'; i++) {
        if (!isspace((unsigned char)user_id[i])) {
            is_empty_or_invalid = 0;
            break;
        }
    }
    
    if (is_empty_or_invalid) {
        return NULL;
    }
    
    // Tính độ dài cần thiết cho chuỗi kết quả
    // api_url + '/' + user_id + '\0'
    size_t api_url_len = strlen(api_url);
    size_t user_id_len = strlen(user_id);
    size_t total_len = api_url_len + 1 + user_id_len + 1;
    
    // Cấp phát bộ nhớ cho chuỗi kết quả
    char* result_url = (char*)malloc(total_len * sizeof(char));
    if (result_url == NULL) {
        return NULL; // Không thể cấp phát bộ nhớ
    }
    
    // Xây dựng URL kết quả
    strcpy(result_url, api_url);
    strcat(result_url, "/");
    strcat(result_url, user_id);
    
    return result_url;
}