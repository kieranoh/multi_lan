#include <string.h>
#include <stdio.h>

/**
 * پیام "تبریک، <username>!" را به یک بافر بنویسید. این بافر توسط فراخواننده چاپ خواهد شد.
 * 
 * @param buffer: بافری که باید به آن نوشته شود
 * @param buffer_size: اندازه بافر
 * @param userName: نام کاربری که باید تبریک گفته شود
 * @param userName_size: اندازه نام کاربری
 */
void congratulate_user(char* buffer, int buffer_size, const char *userName, int userName_size)
{
    // بررسی پارامترهای ورودی
    if (buffer == NULL || userName == NULL || buffer_size <= 0) {
        if (buffer != NULL && buffer_size > 0) {
            buffer[0] = '\0';
        }
        return;
    }
    
    // محاسبه طول پیام بدون نام کاربری
    const char *prefix = "تبریک، ";
    const char *suffix = "!";
    int prefix_len = (int)strlen(prefix);
    int suffix_len = (int)strlen(suffix);
    
    // محاسبه طول واقعی نام کاربری (استفاده از userName_size یا strlen)
    int actual_user_len;
    if (userName_size > 0) {
        // استفاده از اندازه ارائه شده، اما اطمینان از عدم تجاوز از طول رشته
        actual_user_len = userName_size;
        // اگر userName_size بزرگتر از طول واقعی رشته باشد، آن را محدود می‌کنیم
        int str_len = (int)strlen(userName);
        if (actual_user_len > str_len) {
            actual_user_len = str_len;
        }
    } else {
        // اگر userName_size نامعتبر است، از strlen استفاده می‌کنیم
        actual_user_len = (int)strlen(userName);
    }
    
    // محاسبه طول کل پیام
    int total_len = prefix_len + actual_user_len + suffix_len;
    
    // بررسی اینکه آیا بافر به اندازه کافی بزرگ است
    if (total_len >= buffer_size) {
        // اگر بافر بسیار کوچک است، حداقل یک رشته خالی برگردان
        if (buffer_size > 0) {
            buffer[0] = '\0';
        }
        return;
    }
    
    // ساخت پیام در بافر
    int pos = 0;
    
    // کپی پیشوند
    strcpy(buffer, prefix);
    pos += prefix_len;
    
    // کپی نام کاربری (با محدودیت طول)
    strncpy(buffer + pos, userName, actual_user_len);
    pos += actual_user_len;
    buffer[pos] = '\0'; // اطمینان از پایان رشته
    
    // کپی پسوند
    strcpy(buffer + pos, suffix);
}