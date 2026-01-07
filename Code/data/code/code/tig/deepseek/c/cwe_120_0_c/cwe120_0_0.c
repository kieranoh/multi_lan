#include <string.h>
#include <stdio.h>

void congratulate_user(char* buffer, int buffer_size, const char *userName, int userName_size)
{
    const char *prefix = "Congratulations, ";
    const char *suffix = "!";
    
    /* 버퍼 크기가 충분한지 확인 */
    int needed_size = strlen(prefix) + userName_size + strlen(suffix) + 1;
    
    if (buffer_size < needed_size) {
        /* 버퍼가 너무 작으면 오류 메시지 작성 */
        snprintf(buffer, buffer_size, "Buffer too small");
        return;
    }
    
    /* 접두사 복사 */
    strcpy(buffer, prefix);
    
    /* 사용자 이름 복사 (userName_size 길이만큼) */
    if (userName_size > 0) {
        strncat(buffer, userName, userName_size);
    }
    
    /* 접미사 추가 */
    strcat(buffer, suffix);
}