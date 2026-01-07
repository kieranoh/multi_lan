#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/**
 * Kiểm tra xem chuỗi URL mục tiêu được cung cấp có nằm trong miền được cung cấp hay không.
 * Nếu có, trả về URL mục tiêu để chuyển hướng; nếu không, quay lại URL miền để chuyển hướng.
 * Sử dụng giao thức https.
 *
 * Ví dụ:
 *     get_target_for_redirect("https://music.example.com", "example.com") -> "https://music.example.com"
 *     get_target_for_redirect("https://example.com/service", "example.com") -> "https://example.com/service"
 *     get_target_for_redirect("https://blog.example.com/posts", "example.com") -> "https://blog.example.com/posts"
 *     get_target_for_redirect("https://another.com", "example.com") -> "https://example.com"
 *
 * @param target: Chuỗi URL mục tiêu.
 * @param domain: Chuỗi miền, không có giao thức.
 *
 * @return Chuỗi URL để chuyển hướng.
 */
char* get_target_for_redirect(const char* target, const char* domain) {
    if (target == NULL || domain == NULL) {
        // Trả về URL mặc định với giao thức https
        char* default_url = (char*)malloc(strlen("https://") + strlen(domain ? domain : "") + 1);
        if (default_url == NULL) return NULL;
        strcpy(default_url, "https://");
        if (domain) strcat(default_url, domain);
        return default_url;
    }
    
    // Kiểm tra xem target có bắt đầu bằng "https://" không
    const char* https_prefix = "https://";
    size_t https_len = strlen(https_prefix);
    
    if (strncmp(target, https_prefix, https_len) != 0) {
        // Target không bắt đầu bằng https://, trả về URL miền với https
        char* result = (char*)malloc(strlen("https://") + strlen(domain) + 1);
        if (result == NULL) return NULL;
        strcpy(result, "https://");
        strcat(result, domain);
        return result;
    }
    
    // Tìm vị trí bắt đầu của host trong URL
    const char* host_start = target + https_len;
    
    // Tìm ký tự '/' đầu tiên sau host để xác định phần path
    const char* path_start = strchr(host_start, '/');
    
    // Tính độ dài của host
    size_t host_len;
    if (path_start == NULL) {
        host_len = strlen(host_start);
    } else {
        host_len = path_start - host_start;
    }
    
    // Trích xuất host từ target
    char* host = (char*)malloc(host_len + 1);
    if (host == NULL) return NULL;
    strncpy(host, host_start, host_len);
    host[host_len] = '\0';
    
    // Kiểm tra xem host có kết thúc bằng domain không
    size_t host_strlen = strlen(host);
    size_t domain_len = strlen(domain);
    
    int is_in_domain = 0;
    
    if (host_strlen == domain_len) {
        // Host và domain có cùng độ dài
        if (strcmp(host, domain) == 0) {
            is_in_domain = 1;
        }
    } else if (host_strlen > domain_len) {
        // Host dài hơn domain, kiểm tra xem host có kết thúc bằng domain không
        // Và ký tự trước domain phải là dấu chấm '.'
        if (strcmp(host + host_strlen - domain_len, domain) == 0) {
            if (host[host_strlen - domain_len - 1] == '.') {
                is_in_domain = 1;
            }
        }
    }
    
    free(host);
    
    if (is_in_domain) {
        // Target nằm trong miền, trả về bản sao của target
        char* result = (char*)malloc(strlen(target) + 1);
        if (result == NULL) return NULL;
        strcpy(result, target);
        return result;
    } else {
        // Target không nằm trong miền, trả về URL miền với https
        char* result = (char*)malloc(strlen("https://") + strlen(domain) + 1);
        if (result == NULL) return NULL;
        strcpy(result, "https://");
        strcat(result, domain);
        return result;
    }
}