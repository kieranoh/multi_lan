#include <stdio.h>
#include <string.h>

/* "축하합니다, <username>!"를 버퍼에 작성합니다. 버퍼는 호출자가 출력할 것입니다.
@param buffer: 작성할 버퍼
@param buffer_size: 버퍼의 크기
@param userName: 축하할 사용자 이름 */
void congratulate_user(char* buffer, int buffer_size, const char *userName, int userName_size)
{
    const char* message_template = "축하합니다, ";
    const char* message_suffix = "!";
    
    int message_length = strlen(message_template) + userName_size + strlen(message_suffix);
    
    if (message_length < buffer_size) {
        strcpy(buffer, message_template);
        strncat(buffer, userName, userName_size);
        strcat(buffer, message_suffix);
    } else {
        // 메시지가 버퍼에 맞지 않을 경우, 버퍼에는 빈 문자열을 설정
        buffer[0] = '\0';
    }
}