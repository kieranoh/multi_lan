#include <string.h>

void congratulate_user(char* buffer, int buffer_size, const char *userName, int userName_size)
{
    const char *prefix = "축하합니다, ";
    const char *suffix = "!";
    
    /* 접두사 길이 계산 */
    int prefix_len = strlen(prefix);
    
    /* 접미사 길이 계산 */
    int suffix_len = strlen(suffix);
    
    /* 전체 필요한 길이 계산 */
    int total_needed = prefix_len + userName_size + suffix_len + 1; /* +1 for null terminator */
    
    /* 버퍼 크기 확인 */
    if (buffer_size < total_needed) {
        /* 버퍼가 충분하지 않으면 가능한 만큼만 복사 */
        int copy_len = buffer_size - 1; /* null terminator 공간 확보 */
        
        if (copy_len > 0) {
            /* 접두사 복사 */
            int prefix_copy = (copy_len < prefix_len) ? copy_len : prefix_len;
            strncpy(buffer, prefix, prefix_copy);
            copy_len -= prefix_copy;
            
            /* 사용자 이름 복사 */
            if (copy_len > 0) {
                int name_copy = (copy_len < userName_size) ? copy_len : userName_size;
                strncpy(buffer + prefix_copy, userName, name_copy);
                copy_len -= name_copy;
                
                /* 접미사 복사 */
                if (copy_len > 0) {
                    int suffix_copy = (copy_len < suffix_len) ? copy_len : suffix_len;
                    strncpy(buffer + prefix_copy + name_copy, suffix, suffix_copy);
                    copy_len -= suffix_copy;
                }
            }
            
            /* null terminator 추가 */
            buffer[buffer_size - 1] = '\0';
        } else {
            /* 버퍼가 너무 작아 아무것도 복사할 수 없는 경우 */
            if (buffer_size > 0) {
                buffer[0] = '\0';
            }
        }
    } else {
        /* 버퍼가 충분한 경우 전체 문자열 생성 */
        char *ptr = buffer;
        
        /* 접두사 복사 */
        strcpy(ptr, prefix);
        ptr += prefix_len;
        
        /* 사용자 이름 복사 */
        strncpy(ptr, userName, userName_size);
        ptr += userName_size;
        
        /* 접미사 복사 */
        strcpy(ptr, suffix);
    }
}