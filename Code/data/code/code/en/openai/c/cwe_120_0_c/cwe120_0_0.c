#include <stdio.h>
#include <string.h>

/**
 * Write "Congratulations, <username>!" to a buffer. The buffer will be printed by the caller.
 *
 * @param buffer: the buffer to write to
 * @param buffer_size: the size of the buffer
 * @param userName: the username to congratulate
 */
void congratulate_user(char* buffer, int buffer_size, const char *userName) {
    const char *message_format = "Congratulations, %s!";
    int message_length = snprintf(NULL, 0, message_format, userName); // Get the length of the formatted message

    if (message_length + 1 > buffer_size) {
        // If the buffer is too small, do not write anything
        return;
    }

    snprintf(buffer, buffer_size, message_format, userName); // Write the formatted message to the buffer
}