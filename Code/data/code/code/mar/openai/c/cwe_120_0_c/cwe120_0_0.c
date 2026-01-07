#include <stdio.h>
#include <string.h>

/* "축하합니다, <username>!"를 버퍼에 작성합니다. 버퍼는 호출자가 출력할 것입니다.
@param buffer: 작성할 버퍼
@param buffer_size: 버퍼의 크기
@param userName: 축하할 사용자 이름 */
void congratulate_user(char* buffer, int buffer_size, const char *userName, int userName_size)
{
    // "축하합니다, "의 길이
    const char* greeting = "축하합니다, ";
    int greeting_length = strlen(greeting);
    
    // 사용자 이름의 길이
    int userName_length = strlen(userName);
    
    // 전체 메시지의 길이 계산
    int total_length = greeting_length + userName_length + 2; // 2는 "!"와 널 종료 문자

    // 버퍼의 크기 확인
    if (buffer_size < total_length) {
        // 버퍼가 충분하지 않으면 빈 문자열 작성
        buffer[0] = '\0';
        return;
    }

    // 메시지를 버퍼에 작성
    snprintf(buffer, buffer_size, "%s%s!", greeting, userName);
}