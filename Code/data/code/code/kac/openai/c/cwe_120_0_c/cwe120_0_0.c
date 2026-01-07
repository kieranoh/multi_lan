#include <stdio.h>
#include <string.h>

/* "축하합니다, <username>!"를 버퍼에 작성합니다. 버퍼는 호출자가 출력할 것입니다.

@param buffer: 작성할 버퍼
@param buffer_size: 버퍼의 크기
@param userName: 축하할 사용자 이름 */
void congratulate_user(char* buffer, int buffer_size, const char *userName, int userName_size)
{
    const char *message_prefix = "축하합니다, ";
    const char *message_suffix = "!";
    
    int prefix_length = strlen(message_prefix);
    int suffix_length = strlen(message_suffix);
    int total_length = prefix_length + userName_size + suffix_length;

    if (total_length < buffer_size) {
        snprintf(buffer, buffer_size, "%s%s%s", message_prefix, userName, message_suffix);
    } else {
        // If the buffer is not large enough, we can truncate the message
        snprintf(buffer, buffer_size, "%s%s!", message_prefix, userName);
    }
}