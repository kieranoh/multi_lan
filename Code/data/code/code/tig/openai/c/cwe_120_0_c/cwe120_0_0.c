#include <stdio.h>
#include <string.h>

/* "축하합니다, <username>!"를 버퍼에 작성합니다. 버퍼는 호출자가 출력할 것입니다.

@param buffer: 작성할 버퍼
@param buffer_size: 버퍼의 크기
@param userName: 축하할 사용자 이름 */
void congratulate_user(char* buffer, int buffer_size, const char *userName, int userName_size)
{
    const char *template = "축하합니다, ";
    const char *suffix = "!";
    
    // Check if the buffer is large enough
    int required_size = strlen(template) + userName_size + strlen(suffix) + 1; // +1 for the null terminator
    if (required_size > buffer_size) {
        return; // Not enough space in buffer
    }
    
    // Construct the message
    snprintf(buffer, buffer_size, "%s%s%s", template, userName, suffix);
}