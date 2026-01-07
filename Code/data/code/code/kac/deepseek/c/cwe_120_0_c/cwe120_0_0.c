#include <string.h>

void congratulate_user(char* buffer, int buffer_size, const char *userName, int userName_size)
{
    const char *prefix = "Congratulations, ";
    const char *suffix = "!";
    
    /* 버퍼 크기가 충분한지 확인 */
    int needed_size = strlen(prefix) + userName_size + strlen(suffix) + 1;
    
    if (buffer_size < needed_size) {
        /* 버퍼가 너무 작으면 가능한 만큼만 복사하고 null 종료 */
        strncpy(buffer, prefix, buffer_size - 1);
        buffer[buffer_size - 1] = '\0';
        return;
    }
    
    /* prefix 복사 */
    strcpy(buffer, prefix);
    
    /* 사용자 이름 복사 (userName_size 길이만큼) */
    strncat(buffer, userName, userName_size);
    
    /* suffix 추가 */
    strcat(buffer, suffix);
}