#include <stdio.h>
#include <string.h>

/* Ghi "Chúc mừng, <username>!" vào một bộ đệm. Bộ đệm sẽ được in bởi người gọi.

@param buffer: bộ đệm để ghi vào
@param buffer_size: kích thước của bộ đệm
@param userName: tên người dùng để chúc mừng */
void congratulate_user(char* buffer, int buffer_size, const char *userName, int userName_size)
{
    if (buffer == NULL || userName == NULL || buffer_size <= 0 || userName_size <= 0) {
        return;
    }

    const char* message_template = "Chúc mừng, %s!";
    int required_size = snprintf(NULL, 0, message_template, userName) + 1; // Calculate required size

    if (required_size > buffer_size) {
        // If buffer is not large enough, truncate the message to fit
        snprintf(buffer, buffer_size, "Chúc mừng, %.*s!", userName_size - 1, userName);
    } else {
        snprintf(buffer, buffer_size, message_template, userName);
    }
}