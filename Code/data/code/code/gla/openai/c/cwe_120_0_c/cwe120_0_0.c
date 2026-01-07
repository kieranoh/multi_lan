#include <stdio.h>
#include <string.h>

/* "축하합니다, <username>!"를 버퍼에 씁니다. 버퍼는 호출자가 출력할 것입니다.

@param buffer: 쓸 버퍼
@param buffer_size: 버퍼의 크기
@param userName: 축하할 사용자 이름 */
void congratulate_user(char* buffer, int buffer_size, const char *userName, int userName_size)
{
    const char* message_prefix = "축하합니다, ";
    const char* message_suffix = "!";
    int required_size = strlen(message_prefix) + userName_size + strlen(message_suffix) + 1; // +1 for null terminator

    if (required_size <= buffer_size) {
        snprintf(buffer, buffer_size, "%s%s%s", message_prefix, userName, message_suffix);
    } else {
        // If there's not enough space, we can write a truncated message
        snprintf(buffer, buffer_size, "%s%s", message_prefix, userName_size > buffer_size - strlen(message_prefix) - 1 ? "..." : userName);
    }
}