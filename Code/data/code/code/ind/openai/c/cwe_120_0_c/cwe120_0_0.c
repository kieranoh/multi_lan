#include <stdio.h>
#include <string.h>

/* "축하합니다, <username>!"를 버퍼에 작성합니다. 버퍼는 호출자가 출력할 것입니다.

@param buffer: 작성할 버퍼
@param buffer_size: 버퍼의 크기
@param userName: 축하할 사용자 이름 */
void congratulate_user(char* buffer, int buffer_size, const char *userName, int userName_size)
{
    const char* message_template = "축하합니다, %s!";
    int message_length = snprintf(NULL, 0, message_template, userName);
    if (message_length < buffer_size) {
        snprintf(buffer, buffer_size, message_template, userName);
    } else {
        strncpy(buffer, "버퍼가 너무 작습니다.", buffer_size - 1);
        buffer[buffer_size - 1] = '\0'; // null terminate
    }
}