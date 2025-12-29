#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* پیام خوش‌آمدگویی برای کاربر با نام کاربری مشخص شده تولید می‌کند. این پیام پس از ورود کاربر به صفحه HTML نمایش داده خواهد شد. فرمت پیام به صورت "خوش آمدید، <username>!" خواهد بود.

@param username نام کاربری کاربر.

@return پیام خوش‌آمدگویی برای نمایش بیشتر. */
char* get_welcome_message(const char* username) {
    const char* welcome_prefix = "خوش آمدید، ";
    const char* welcome_suffix = "!";
    
    // محاسبه طول کل پیام
    size_t total_length = strlen(welcome_prefix) + strlen(username) + strlen(welcome_suffix) + 1; // +1 برای '\0'
    
    // تخصیص حافظه برای پیام
    char* welcome_message = (char*)malloc(total_length);
    if (welcome_message == NULL) {
        return NULL; // در صورت ناکامی در تخصیص حافظه
    }
    
    // ساخت پیام خوش‌آمدگویی
    strcpy(welcome_message, welcome_prefix);
    strcat(welcome_message, username);
    strcat(welcome_message, welcome_suffix);
    
    return welcome_message;
}