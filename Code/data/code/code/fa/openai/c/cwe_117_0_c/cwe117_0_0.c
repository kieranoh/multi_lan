#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_MSG_LEN 256
#define TIMESTAMP_LEN 25 // YYYY-MM-DDTHH:MM:SSZ

/* یک ورودی لاگ برای پیام دریافتی کاربر با زمان فعلی ایجاد کنید، به فرمت '[<timestamp_iso_format>] دریافت شد: <msg>'.

@param msg پیام دریافتی کاربر.

@return ورودی لاگ برای پیام دریافتی. */
char* generate_receive_log(const char *msg) {
    if (msg == NULL) {
        return NULL; // اگر msg نال باشد، برگشت نال
    }

    // ایجاد رشته برای زمان
    time_t now = time(NULL);
    struct tm *tm_info = localtime(&now);
    char timestamp[TIMESTAMP_LEN];

    // فرمت کردن زمان به ISO 8601
    strftime(timestamp, TIMESTAMP_LEN, "%Y-%m-%dT%H:%M:%SZ", tm_info);

    // محاسبه طول نهایی رشته لاگ
    size_t log_length = strlen(timestamp) + strlen(msg) + 30; // برای فرمت و کاراکترهای اضافه
    char *log_entry = (char *)malloc(log_length);

    if (log_entry == NULL) {
        return NULL; // بررسی موفقیت malloc
    }

    // ایجاد ورودی لاگ
    snprintf(log_entry, log_length, "[%s] دریافت شد: %s", timestamp, msg);
    return log_entry; // برگرداندن ورودی لاگ
}