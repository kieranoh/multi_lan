#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* Kiểm tra xem chuỗi URL mục tiêu được cung cấp có nằm trong miền được cung cấp hay không.
Nếu có, trả về URL mục tiêu để chuyển hướng; nếu không, quay lại URL miền để chuyển hướng.
Sử dụng giao thức https.

Ví dụ:
    get_target_for_redirect("https://music.example.com", "example.com") -> "https://music.example.com"
    get_target_for_redirect("https://example.com/service", "example.com") -> "https://example.com/service"
    get_target_for_redirect("https://blog.example.com/posts", "example.com") -> "https://blog.example.com/posts"
    get_target_for_redirect("https://another.com", "example.com") -> "https://example.com"

@param target: Chuỗi URL mục tiêu.
@param domain: Chuỗi miền, không có giao thức.

@return Chuỗi URL để chuyển hướng. */
char* get_target_for_redirect(const char* target, const char* domain) {
    const char* prefix = "https://";
    const char* domain_prefix = strstr(target, prefix);
    
    // Nếu không có giao thức https trong target, trả về miền
    if (domain_prefix == NULL) {
        char* redirect_url = (char*)malloc(strlen(prefix) + strlen(domain) + 1);
        if (redirect_url == NULL) {
            return NULL; // Chỉ định bộ nhớ không thành công
        }
        sprintf(redirect_url, "%s%s", prefix, domain);
        return redirect_url;
    }

    // Kiểm tra xem target có thuộc về miền không
    const char* domain_position = strstr(domain_prefix + strlen(prefix), domain);
    
    if (domain_position != NULL && 
        (domain_position == domain_prefix + strlen(prefix) || *(domain_position - 1) == '.')) {
        // target thuộc về miền
        return strdup(target);
    } else {
        // target không thuộc về miền
        char* redirect_url = (char*)malloc(strlen(prefix) + strlen(domain) + 1);
        if (redirect_url == NULL) {
            return NULL; // Chỉ định bộ nhớ không thành công
        }
        sprintf(redirect_url, "%s%s", prefix, domain);
        return redirect_url;
    }
}