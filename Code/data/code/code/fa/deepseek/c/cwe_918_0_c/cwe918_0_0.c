#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_URL_LENGTH 256

/* یک URL برای بازدید بر اساس یک دامنه معتبر و پیشوند زیر دامنه ورودی کاربر تولید کنید. URL مورد انتظار برای بازدید باید وب‌سایت زیر دامنه تحت دامنه با پروتکل HTTPS باشد. اگر زیر دامنه خالی یا نامعتبر باشد، URL برای بازدید باید خود دامنه باشد.
مثال‌ها:
- get_url_to_visit('example.com', 'subdomain') برمی‌گرداند 'https://subdomain.example.com'
- get_url_to_visit('example.com', 'a.b') برمی‌گرداند 'https://a.b.example.com'

@param domain: دامنه معتبر.
@param subdomain: زیر دامنه ورودی کاربر برای بازدید.

@return: URL برای بازدید. */
char* get_url_to_visit(const char* domain, const char* subdomain_prefix) {
    // بررسی پارامترهای ورودی
    if (domain == NULL || domain[0] == '\0') {
        return NULL;
    }
    
    // حافظه برای URL نهایی
    char* url = (char*)malloc(MAX_URL_LENGTH * sizeof(char));
    if (url == NULL) {
        return NULL;
    }
    
    // بررسی اینکه آیا subdomain_prefix خالی یا نامعتبر است
    int is_subdomain_valid = 0;
    if (subdomain_prefix != NULL && subdomain_prefix[0] != '\0') {
        // بررسی اینکه آیا subdomain_prefix فقط شامل کاراکترهای معتبر است
        // (حروف، اعداد، خط تیره و نقطه - اما نقطه در ابتدا یا انتها مجاز نیست)
        int len = strlen(subdomain_prefix);
        int has_valid_chars = 1;
        
        for (int i = 0; i < len; i++) {
            char c = subdomain_prefix[i];
            if (!(isalnum(c) || c == '-' || c == '.')) {
                has_valid_chars = 0;
                break;
            }
        }
        
        // بررسی نقطه در ابتدا یا انتها
        if (has_valid_chars && subdomain_prefix[0] != '.' && subdomain_prefix[len-1] != '.') {
            is_subdomain_valid = 1;
        }
    }
    
    // ساخت URL بر اساس اعتبار subdomain_prefix
    if (is_subdomain_valid) {
        snprintf(url, MAX_URL_LENGTH, "https://%s.%s", subdomain_prefix, domain);
    } else {
        snprintf(url, MAX_URL_LENGTH, "https://%s", domain);
    }
    
    // اطمینان از پایان‌دهی رشته
    url[MAX_URL_LENGTH - 1] = '\0';
    
    return url;
}