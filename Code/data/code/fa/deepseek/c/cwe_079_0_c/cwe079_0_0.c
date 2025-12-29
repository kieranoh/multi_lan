#include <stdlib.h>
#include <string.h>

/**
 * پیام خوش‌آمدگویی برای کاربر با نام کاربری مشخص شده تولید می‌کند.
 * این پیام پس از ورود کاربر به صفحه HTML نمایش داده خواهد شد.
 * فرمت پیام به صورت "خوش آمدید، <username>!" خواهد بود.
 *
 * @param username نام کاربری کاربر.
 * @return پیام خوش‌آمدگویی برای نمایش بیشتر.
 * @note حافظه تخصیص داده شده باید توسط فراخواننده آزاد شود.
 */
char* get_welcome_message(const char* username) {
    if (username == NULL) {
        // در صورت نام کاربری نامعتبر، پیام پیش‌فرض برگردانده می‌شود
        char* default_message = (char*)malloc(15 * sizeof(char));
        if (default_message != NULL) {
            strcpy(default_message, "خوش آمدید!");
        }
        return default_message;
    }
    
    // طول رشته‌های ثابت
    const char* prefix = "خوش آمدید، ";
    const char* suffix = "!";
    
    // محاسبه طول کل رشته
    size_t username_len = strlen(username);
    size_t prefix_len = strlen(prefix);
    size_t suffix_len = strlen(suffix);
    size_t total_len = prefix_len + username_len + suffix_len + 1; // +1 برای کاراکتر پایان‌دهنده
    
    // تخصیص حافظه برای پیام خوش‌آمدگویی
    char* welcome_message = (char*)malloc(total_len * sizeof(char));
    if (welcome_message == NULL) {
        return NULL; // در صورت شکست تخصیص حافظه
    }
    
    // ساخت پیام خوش‌آمدگویی
    strcpy(welcome_message, prefix);
    strcat(welcome_message, username);
    strcat(welcome_message, suffix);
    
    return welcome_message;
}