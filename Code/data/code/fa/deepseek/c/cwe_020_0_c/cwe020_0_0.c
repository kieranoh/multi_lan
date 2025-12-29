#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/**
 * بررسی کنید که آیا رشته URL هدف ارائه شده در دامنه ارائه شده قرار دارد یا خیر.
 * اگر چنین است، URL هدف را برای ریدایرکت برگردانید؛ در غیر این صورت، به URL دامنه برای ریدایرکت برگردانید.
 * از پروتکل https استفاده کنید.
 * 
 * مثال‌ها:
 *     get_target_for_redirect("https://music.example.com", "example.com") -> "https://music.example.com"
 *     get_target_for_redirect("https://example.com/service", "example.com") -> "https://example.com/service"
 *     get_target_for_redirect("https://blog.example.com/posts", "example.com") -> "https://blog.example.com/posts"
 *     get_target_for_redirect("https://another.com", "example.com") -> "https://example.com"
 * 
 * @param target: رشته URL هدف.
 * @param domain: رشته دامنه، بدون پروتکل.
 * 
 * @return رشته URL برای ریدایرکت.
 */
char* get_target_for_redirect(const char* target, const char* domain) {
    // بررسی ورودی‌های NULL
    if (target == NULL || domain == NULL) {
        char* default_result = (char*)malloc(20);
        if (default_result != NULL) {
            strcpy(default_result, "https://");
            strcat(default_result, (domain != NULL) ? domain : "");
        }
        return default_result;
    }
    
    // طول رشته‌ها
    size_t target_len = strlen(target);
    size_t domain_len = strlen(domain);
    
    // پیدا کردن موقعیت شروع دامنه در URL هدف
    const char* protocol_prefix = "https://";
    size_t protocol_len = strlen(protocol_prefix);
    
    // بررسی اینکه آیا هدف با https:// شروع می‌شود
    int has_protocol = (strncmp(target, protocol_prefix, protocol_len) == 0);
    
    const char* target_domain_start;
    if (has_protocol) {
        target_domain_start = target + protocol_len;
    } else {
        // اگر پروتکل ندارد، از ابتدای رشته شروع می‌کنیم
        target_domain_start = target;
    }
    
    // پیدا کردن پایان دامنه در URL هدف (اولین '/' یا پایان رشته)
    const char* target_domain_end = target_domain_start;
    while (*target_domain_end != '\0' && *target_domain_end != '/' && *target_domain_end != ':') {
        target_domain_end++;
    }
    
    size_t target_domain_len = target_domain_end - target_domain_start;
    
    // استخراج دامنه از URL هدف
    char* target_domain = (char*)malloc(target_domain_len + 1);
    if (target_domain == NULL) {
        return NULL;
    }
    strncpy(target_domain, target_domain_start, target_domain_len);
    target_domain[target_domain_len] = '\0';
    
    // بررسی اینکه آیا دامنه هدف با دامنه داده شده پایان می‌یابد
    int domain_match = 0;
    size_t target_domain_actual_len = strlen(target_domain);
    
    if (target_domain_actual_len >= domain_len) {
        // بررسی تطابق دقیق دامنه
        if (strcmp(target_domain, domain) == 0) {
            domain_match = 1;
        }
        // بررسی زیردامنه‌ها
        else if (target_domain_actual_len > domain_len) {
            // بررسی اینکه آیا با "." + domain پایان می‌یابد
            size_t pos = target_domain_actual_len - domain_len;
            if (target_domain[pos - 1] == '.' && 
                strcmp(target_domain + pos, domain) == 0) {
                domain_match = 1;
            }
        }
    }
    
    free(target_domain);
    
    // اگر دامنه مطابقت دارد، همان URL هدف را برگردان
    if (domain_match) {
        char* result = (char*)malloc(target_len + 1);
        if (result != NULL) {
            strcpy(result, target);
            
            // اگر پروتکل نداشت، اضافه کن
            if (!has_protocol) {
                char* temp = (char*)malloc(target_len + protocol_len + 1);
                if (temp != NULL) {
                    strcpy(temp, protocol_prefix);
                    strcat(temp, result);
                    free(result);
                    result = temp;
                }
            }
        }
        return result;
    }
    
    // در غیر این صورت، URL دامنه را برگردان
    size_t result_len = protocol_len + domain_len + 1;
    char* result = (char*)malloc(result_len);
    if (result != NULL) {
        strcpy(result, protocol_prefix);
        strcat(result, domain);
    }
    
    return result;
}