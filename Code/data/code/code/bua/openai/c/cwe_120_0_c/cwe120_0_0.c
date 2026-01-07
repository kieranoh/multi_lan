#include <stdio.h>
#include <string.h>

void congratulate_user(char* buffer, int buffer_size, const char *userName, int userName_size)
{
    const char* message_format = "축하합니다, %s!";
    int message_length = snprintf(NULL, 0, message_format, userName); // Calculate the length of the message
    if (message_length + 1 <= buffer_size) { // Check if the buffer is large enough
        snprintf(buffer, buffer_size, message_format, userName); // Write the message to buffer
    } else {
        // If buffer is too small, we can choose to handle this case, e.g., truncate or leave it empty
        snprintf(buffer, buffer_size, "버퍼가 너무 작습니다."); // Example of an error message
    }
}