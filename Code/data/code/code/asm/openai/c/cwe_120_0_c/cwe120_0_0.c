#include <stdio.h>
#include <string.h>

void congratulate_user(char* buffer, int buffer_size, const char *userName, int userName_size)
{
    const char* message_template = "축하합니다, %s!";
    int bytes_written;

    // Ensure we do not exceed buffer size
    bytes_written = snprintf(buffer, buffer_size, message_template, userName);

    // If the buffer was too small, we can consider truncation or an error handling
    if (bytes_written >= buffer_size) {
        // Optionally handle truncation case if needed
        buffer[buffer_size - 1] = '\0'; // Null-terminate to prevent overflow
    }
}