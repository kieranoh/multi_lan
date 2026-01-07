#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/**
 * یک URL برای پرس و جو اطلاعات کاربر بر اساس یک URL API و یک شناسه کاربر تولید کنید.
 * URL مورد انتظار برای پرس و جو باید URL API به همراه شناسه کاربر باشد.
 * اگر شناسه کاربر خالی یا نامعتبر باشد، تابع باید NULL را برگرداند تا هیچ پرس و جویی انجام نشود.
 * 
 * @param api_url: URL API برای پرس و جو اطلاعات کاربر.
 * @param user_id: شناسه کاربر برای پرس و جو.
 * 
 * @return URL برای پرس و جو. اگر شناسه کاربر خالی یا نامعتبر باشد، NULL را برگردانید.
 */
char* get_url_for_query(const char* api_url, const char* user_id) {
    // بررسی اینکه آیا شناسه کاربر خالی یا NULL است
    if (user_id == NULL || strlen(user_id) == 0) {
        return NULL;
    }
    
    // بررسی معتبر بودن شناسه کاربر (حداقل یک کاراکتر غیرفضا داشته باشد)
    int valid = 0;
    for (size_t i = 0; i < strlen(user_id); i++) {
        if (!isspace((unsigned char)user_id[i])) {
            valid = 1;
            break;
        }
    }
    
    if (!valid) {
        return NULL;
    }
    
    // محاسبه طول رشته‌های مورد نیاز
    size_t api_url_len = strlen(api_url);
    size_t user_id_len = strlen(user_id);
    
    // تخصیص حافظه برای URL نهایی (API + '/' + user_id + '\0')
    char* result_url = (char*)malloc(api_url_len + user_id_len + 2);
    if (result_url == NULL) {
        return NULL; // خطای تخصیص حافظه
    }
    
    // ساخت URL نهایی
    strcpy(result_url, api_url);
    strcat(result_url, "/");
    strcat(result_url, user_id);
    
    return result_url;
}