#include <string.h>
#include <stdio.h>

/* "축하합니다, <username>!"를 버퍼에 작성합니다. 버퍼는 호출자가 출력할 것입니다.

@param buffer: 작성할 버퍼
@param buffer_size: 버퍼의 크기
@param userName: 축하할 사용자 이름 */
void congratulate_user(char* buffer, int buffer_size, const char *userName, int userName_size)
{
    if (buffer == NULL || userName == NULL || buffer_size <= 0) {
        return;
    }
    
    // 버퍼에 안전하게 문자열 작성
    int written = snprintf(buffer, buffer_size, "축하합니다, %.*s!", userName_size, userName);
    
    // 버퍼가 충분하지 않은 경우 null 종료 문자 보장
    if (written >= buffer_size) {
        buffer[buffer_size - 1] = '\0';
    }
}