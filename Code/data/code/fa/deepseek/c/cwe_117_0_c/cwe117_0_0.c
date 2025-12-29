#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

#define MAX_MSG_LEN 256

/* یک ورودی لاگ برای پیام دریافتی کاربر با زمان فعلی ایجاد کنید، به فرمت '[<timestamp_iso_format>] دریافت شد: <msg>'.

@param msg پیام دریافتی کاربر.

@return ورودی لاگ برای پیام دریافتی. */
char* generate_receive_log(const char *msg) {
    // دریافت زمان فعلی
    time_t current_time = time(NULL);
    if (current_time == -1) {
        return NULL;
    }
    
    // تبدیل زمان به ساختار tm
    struct tm *time_info = localtime(&current_time);
    if (time_info == NULL) {
        return NULL;
    }
    
    // فرمت‌دهی زمان به صورت ISO 8601 (YYYY-MM-DD HH:MM:SS)
    char timestamp[20];
    strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", time_info);
    
    // محاسبه طول رشته نهایی
    // طول = طول timestamp + طول متن ثابت + طول پیام + 1 برای کاراکتر پایان‌دهنده
    int fixed_text_len = strlen("[] دریافت شد: ");
    int msg_len = strlen(msg);
    int total_len = strlen(timestamp) + fixed_text_len + msg_len + 1;
    
    // بررسی محدودیت طول پیام
    if (msg_len > MAX_MSG_LEN) {
        return NULL;
    }
    
    // تخصیص حافظه برای رشته خروجی
    char *log_entry = (char *)malloc(total_len * sizeof(char));
    if (log_entry == NULL) {
        return NULL;
    }
    
    // ساخت رشته نهایی
    snprintf(log_entry, total_len, "[%s] دریافت شد: %s", timestamp, msg);
    
    return log_entry;
}