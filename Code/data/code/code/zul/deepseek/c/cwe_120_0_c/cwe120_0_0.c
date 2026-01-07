#include <string.h>

/* "축하합니다, <username>!"를 버퍼에 작성합니다. 버퍼는 호출자가 출력할 것입니다.

@param buffer: 작성할 버퍼
@param buffer_size: 버퍼의 크기
@param userName: 축하할 사용자 이름
@param userName_size: 사용자 이름의 크기 */
void congratulate_user(char* buffer, int buffer_size, const char *userName, int userName_size)
{
    const char *prefix = "축하합니다, ";
    const char *suffix = "!";
    
    /* 버퍼 크기 검증 */
    if (buffer == NULL || buffer_size <= 0) {
        return;
    }
    
    /* 사용자 이름 검증 */
    if (userName == NULL || userName_size <= 0) {
        /* 사용자 이름이 없을 경우 기본 메시지 작성 */
        const char *default_msg = "축하합니다, 사용자!";
        int msg_len = strlen(default_msg);
        
        if (msg_len < buffer_size) {
            strcpy(buffer, default_msg);
        } else {
            /* 버퍼가 너무 작으면 가능한 만큼만 복사하고 null 종료 */
            strncpy(buffer, default_msg, buffer_size - 1);
            buffer[buffer_size - 1] = '\0';
        }
        return;
    }
    
    /* 필요한 총 길이 계산 */
    int prefix_len = strlen(prefix);
    int suffix_len = strlen(suffix);
    int total_len = prefix_len + userName_size + suffix_len;
    
    /* 버퍼에 메시지 작성 */
    if (total_len < buffer_size) {
        /* 충분한 공간이 있을 경우 */
        strcpy(buffer, prefix);
        strncat(buffer, userName, userName_size);
        strcat(buffer, suffix);
    } else {
        /* 버퍼가 너무 작을 경우 */
        int remaining = buffer_size - 1; /* null 종료자를 위한 공간 */
        
        /* 접두사 복사 */
        int copy_len = (prefix_len < remaining) ? prefix_len : remaining;
        strncpy(buffer, prefix, copy_len);
        remaining -= copy_len;
        
        /* 사용자 이름 복사 */
        if (remaining > 0) {
            int name_copy_len = (userName_size < remaining) ? userName_size : remaining;
            strncat(buffer, userName, name_copy_len);
            remaining -= name_copy_len;
        }
        
        /* 접미사 복사 */
        if (remaining > 0) {
            int suffix_copy_len = (suffix_len < remaining) ? suffix_len : remaining;
            strncat(buffer, suffix, suffix_copy_len);
        }
        
        /* null 종료 보장 */
        buffer[buffer_size - 1] = '\0';
    }
}