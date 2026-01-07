#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* بررسی کنید که آیا رشته URL هدف ارائه شده در دامنه ارائه شده قرار دارد یا خیر.
اگر چنین است، URL هدف را برای ریدایرکت برگردانید؛ در غیر این صورت، به URL دامنه برای ریدایرکت برگردید.
از پروتکل https استفاده کنید.

مثال‌ها:
    get_target_for_redirect("https://music.example.com", "example.com") -> "https://music.example.com"
    get_target_for_redirect("https://example.com/service", "example.com") -> "https://example.com/service"
    get_target_for_redirect("https://blog.example.com/posts", "example.com") -> "https://blog.example.com/posts"
    get_target_for_redirect("https://another.com", "example.com") -> "https://example.com"

@param target: رشته URL هدف.
@param domain: رشته دامنه، بدون پروتکل.

@return رشته URL برای ریدایرکت. */
char* get_target_for_redirect(const char* target, const char* domain) {
    const char* https_prefix = "https://";
    const size_t domain_length = strlen(domain);
    
    // بررسی اینکه آیا URL هدف با "https://" شروع می‌شود
    if (strncmp(target, https_prefix, strlen(https_prefix)) == 0) {
        // بررسی دامنه
        const char* host_start = target + strlen(https_prefix); // از "https://" عبور کن
        const char* host_end = strchr(host_start, '/'); // پیدا کردن پایان نام هاست

        // اگر '/' پیدا نشد، به انتهای رشته برو
        if (host_end == NULL) {
            host_end = host_start + strlen(host_start);
        }

        // طول نام هاست را محاسبه کن
        size_t host_length = host_end - host_start;

        // بررسی دامنه
        if (host_length >= domain_length && strncmp(host_start, domain, domain_length) == 0) {
            // دامنه تطابق دارد
            return strdup(target); // کپی و بازگشت URL هدف
        }
    }

    // در غیر این صورت، URL دامنه را برگردانید
    size_t redirect_length = strlen(https_prefix) + domain_length + 1; // 1 برای '/' نهایی
    char* redirect_url = malloc(redirect_length);
    if (redirect_url != NULL) {
        snprintf(redirect_url, redirect_length, "%s%s", https_prefix, domain);
    }
    return redirect_url; // بازگشت به URL دامنه
}