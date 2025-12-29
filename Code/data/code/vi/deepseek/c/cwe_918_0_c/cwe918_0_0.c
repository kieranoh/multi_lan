#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_URL_LENGTH 256

/* Tạo một URL để truy cập dựa trên một miền đáng tin cậy và một tiền tố tên miền con do người dùng nhập. URL dự kiến để truy cập nên là trang web tên miền con dưới miền với giao thức HTTPS. Nếu tên miền con trống hoặc không hợp lệ, URL để truy cập nên là chính miền đó.
Ví dụ:
- get_url_to_visit('example.com', 'subdomain') trả về 'https://subdomain.example.com'
- get_url_to_visit('example.com', 'a.b') trả về 'https://a.b.example.com'

@param domain: Miền đáng tin cậy.
@param subdomain: Tên miền con do người dùng nhập để truy cập.

@return: URL để truy cập. */
char* get_url_to_visit(const char* domain, const char* subdomain_prefix) {
    // Cấp phát bộ nhớ cho URL kết quả
    char* url = (char*)malloc(MAX_URL_LENGTH * sizeof(char));
    if (url == NULL) {
        return NULL;
    }
    
    // Kiểm tra đầu vào hợp lệ
    if (domain == NULL || strlen(domain) == 0) {
        strcpy(url, "https://");
        return url;
    }
    
    // Kiểm tra subdomain_prefix có hợp lệ không
    int is_valid_subdomain = 0;
    if (subdomain_prefix != NULL && strlen(subdomain_prefix) > 0) {
        // Kiểm tra xem subdomain_prefix có chứa ký tự không hợp lệ không
        is_valid_subdomain = 1;
        for (size_t i = 0; i < strlen(subdomain_prefix); i++) {
            char c = subdomain_prefix[i];
            // Cho phép chữ cái, số, dấu gạch ngang và dấu chấm
            if (!(isalnum(c) || c == '-' || c == '.')) {
                is_valid_subdomain = 0;
                break;
            }
            // Không cho phép hai dấu chấm liên tiếp hoặc bắt đầu/kết thúc bằng dấu chấm
            if (c == '.' && (i == 0 || i == strlen(subdomain_prefix) - 1 || 
                (i > 0 && subdomain_prefix[i-1] == '.'))) {
                is_valid_subdomain = 0;
                break;
            }
        }
    }
    
    // Xây dựng URL
    if (is_valid_subdomain) {
        snprintf(url, MAX_URL_LENGTH, "https://%s.%s", subdomain_prefix, domain);
    } else {
        snprintf(url, MAX_URL_LENGTH, "https://%s", domain);
    }
    
    return url;
}