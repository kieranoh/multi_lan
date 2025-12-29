#include <stdio.h>
#include <string.h>

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
    const char* message_format = "تبریک، %s!";
    int message_length = snprintf(NULL, 0, message_format, userName);
    if (message_length + 1 <= buffer_size) {
        snprintf(buffer, buffer_size, message_format, userName);
    } else {
        // در صورتی که بافر برای ذخیره پیام کافی نباشد، پیام را به صورت ناقص می‌نویسیم
        snprintf(buffer, buffer_size, "تبریک، %.*s!", userName_size - 1, userName);
    }
}