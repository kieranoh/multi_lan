#include <string.h>

void congratulate_user(char* buffer, int buffer_size, const char *userName, int userName_size)
{
    const char *prefix = "축하합니다, ";
    const char *suffix = "!";
    
    /* 필요한 총 길이 계산: 접두사 + 사용자 이름 + 접미사 + 널 종결자 */
    int total_length = (int)strlen(prefix) + userName_size + (int)strlen(suffix) + 1;
    
    /* 버퍼 크기 확인 */
    if (buffer_size < total_length) {
        /* 버퍼가 너무 작으면 가능한 만큼만 복사하고 안전하게 종결 */
        int copy_len = buffer_size - 1;
        
        /* 접두사 복사 */
        int prefix_len = (int)strlen(prefix);
        int to_copy = (prefix_len < copy_len) ? prefix_len : copy_len;
        strncpy(buffer, prefix, to_copy);
        copy_len -= to_copy;
        
        /* 사용자 이름 복사 */
        if (copy_len > 0 && userName_size > 0) {
            int user_copy = (userName_size < copy_len) ? userName_size : copy_len;
            strncpy(buffer + to_copy, userName, user_copy);
            to_copy += user_copy;
            copy_len -= user_copy;
        }
        
        /* 접미사 복사 */
        if (copy_len > 0) {
            int suffix_len = (int)strlen(suffix);
            int suffix_copy = (suffix_len < copy_len) ? suffix_len : copy_len;
            strncpy(buffer + to_copy, suffix, suffix_copy);
            to_copy += suffix_copy;
        }
        
        /* 널 종결 */
        buffer[to_copy] = '\0';
    } else {
        /* 충분한 공간이 있으면 전체 문자열 작성 */
        char *ptr = buffer;
        
        /* 접두사 복사 */
        ptr = stpcpy(ptr, prefix);
        
        /* 사용자 이름 복사 */
        if (userName_size > 0) {
            strncpy(ptr, userName, userName_size);
            ptr += userName_size;
        }
        
        /* 접미사 복사 */
        ptr = stpcpy(ptr, suffix);
    }
}