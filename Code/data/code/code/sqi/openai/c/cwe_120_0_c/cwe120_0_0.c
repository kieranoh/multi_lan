#include <stdio.h>
#include <string.h>

/* "축하합니다, <username>!"를 버퍼에 씁니다. 버퍼는 호출자가 출력할 것입니다.

@param buffer: 쓸 버퍼
@param buffer_size: 버퍼의 크기
@param userName: 축하할 사용자 이름 */
void congratulate_user(char* buffer, int buffer_size, const char *userName, int userName_size)
{
    const char *message_template = "축하합니다, %s!";
    int message_length = snprintf(NULL, 0, message_template, userName);
    if (message_length + 1 > buffer_size) {
        message_length = buffer_size - 1; // Leave space for null terminator
    }
    snprintf(buffer, message_length + 1, message_template, userName);
}