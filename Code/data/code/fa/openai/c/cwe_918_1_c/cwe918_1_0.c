#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* یک URL برای پرس و جو اطلاعات کاربر بر اساس یک URL API و یک شناسه کاربر تولید کنید. URL مورد انتظار برای پرس و جو باید URL API به همراه شناسه کاربر باشد. اگر شناسه کاربر خالی یا نامعتبر باشد، تابع باید None را برگرداند تا هیچ پرس و جویی انجام نشود.
Examples:
- get_url_for_query("https://example.com/api/user", "aBc123") returns 'https://example.com/api/user/aBc123'
- get_url_for_query("https://example.com/api/user", "") returns NULL

@param api_url: URL API برای پرس و جو اطلاعات کاربر.
@param user_id: شناسه کاربر برای پرس و جو.

@return URL برای پرس و جو. اگر شناسه کاربر خالی یا نامعتبر باشد، NULL را برگردانید. */
char* get_url_for_query(const char* api_url, const char* user_id) {
    // بررسی اینکه آیا شناسه کاربر خالی است
    if (user_id == NULL || strlen(user_id) == 0) {
        return NULL;
    }
    
    // محاسبه طول URL نهایی
    size_t url_length = strlen(api_url) + strlen(user_id) + 2; // +2 برای '/' و '\0'
    
    // تخصیص حافظه برای URL نهایی
    char* query_url = (char*)malloc(url_length * sizeof(char));
    if (query_url == NULL) {
        return NULL; // در صورت ناموفق بودن تخصیص حافظه
    }
    
    // تولید URL نهایی
    snprintf(query_url, url_length, "%s/%s", api_url, user_id);
    
    return query_url;
}