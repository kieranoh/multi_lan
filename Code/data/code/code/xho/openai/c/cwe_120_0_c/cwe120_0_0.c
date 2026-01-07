#include <stdio.h>
#include <string.h>

/* "축하합니다, <username>!"를 버퍼에 작성합니다. 버퍼는 호출자가 출력할 것입니다.

@param buffer: 작성할 버퍼
@param buffer_size: 버퍼의 크기
@param userName: 축하할 사용자 이름 */
void congratulate_user(char* buffer, int buffer_size, const char *userName, int userName_size)
{
    const char* message_prefix = "축하합니다, ";
    const char* message_suffix = "!";
    int message_prefix_length = strlen(message_prefix);
    int message_suffix_length = strlen(message_suffix);
    int total_length = message_prefix_length + userName_size + message_suffix_length;

    // Check if the buffer is large enough to hold the message
    if (total_length < buffer_size) {
        // Copy the message to the buffer
        strcpy(buffer, message_prefix);
        strncat(buffer, userName, userName_size);
        strcat(buffer, message_suffix);
    } else {
        // Buffer is not large enough to hold the complete message
        snprintf(buffer, buffer_size, "%s%s%s", message_prefix, userName, message_suffix);
    }
}