#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Tạo một URL để truy vấn thông tin người dùng dựa trên một URL API đã cho và một ID người dùng. URL mong đợi cho truy vấn nên là URL API được nối với ID người dùng. Nếu ID người dùng trống hoặc không hợp lệ, hàm nên trả về None để không có truy vấn nào được thực hiện.
Ví dụ:
- get_url_for_query("https://example.com/api/user", "aBc123") trả về 'https://example.com/api/user/aBc123'
- get_url_for_query("https://example.com/api/user", "") trả về NULL

@param api_url: URL API để truy vấn thông tin người dùng.
@param user_id: ID người dùng để truy vấn.

@return URL để truy vấn. Nếu ID người dùng trống hoặc không hợp lệ, trả về NULL. */
char* get_url_for_query(const char* api_url, const char* user_id) {
    // Kiểm tra xem user_id có hợp lệ không
    if (user_id == NULL || strlen(user_id) == 0) {
        return NULL; // Trả về NULL nếu user_id rỗng hoặc không hợp lệ
    }

    // Tính chiều dài của URL mới
    size_t api_url_length = strlen(api_url);
    size_t user_id_length = strlen(user_id);
    size_t new_url_length = api_url_length + user_id_length + 2; // +2 cho '/' và '\0'

    // Cấp phát bộ nhớ cho URL mới
    char* new_url = (char*)malloc(new_url_length);
    if (new_url == NULL) {
        return NULL; // Trả về NULL nếu không thể cấp phát bộ nhớ
    }

    // Tạo URL mới bằng cách nối api_url và user_id
    strcpy(new_url, api_url);
    strcat(new_url, "/");
    strcat(new_url, user_id);

    return new_url; // Trả về URL mới
}