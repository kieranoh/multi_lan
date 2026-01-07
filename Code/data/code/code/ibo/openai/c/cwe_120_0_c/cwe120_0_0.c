#include <stdio.h>
#include <string.h>

void congratulate_user(char* buffer, int buffer_size, const char *userName, int userName_size)
{
    // Ensure the buffer has enough space for the message and null terminator
    const char* message_template = "축하합니다, %s!";
    int required_size = snprintf(NULL, 0, message_template, userName) + 1; // +1 for null terminator

    if (required_size <= buffer_size) {
        snprintf(buffer, buffer_size, message_template, userName);
    } else {
        // If the buffer is not large enough, truncate the message
        snprintf(buffer, buffer_size, "축하합니다, %.*s!", userName_size, userName);
    }
}