#include <string.h>

void congratulate_user(char* buffer, int buffer_size, const char *userName, int userName_size)
{
    const char *prefix = "축하합니다, ";
    const char *suffix = "!";
    int prefix_len = strlen(prefix);
    int suffix_len = strlen(suffix);
    
    /* 버퍼 크기가 충분한지 확인 */
    if (buffer_size <= 0) {
        return;
    }
    
    /* 필요한 총 길이 계산 */
    int total_len = prefix_len + userName_size + suffix_len;
    
    /* 버퍼에 맞게 복사할 길이 결정 */
    int copy_len = total_len;
    if (copy_len >= buffer_size) {
        copy_len = buffer_size - 1; /* 널 종결자를 위한 공간 확보 */
    }
    
    /* 접두사 복사 */
    int copied = 0;
    if (prefix_len > 0 && copied < copy_len) {
        int to_copy = prefix_len;
        if (to_copy > copy_len - copied) {
            to_copy = copy_len - copied;
        }
        memcpy(buffer + copied, prefix, to_copy);
        copied += to_copy;
    }
    
    /* 사용자 이름 복사 */
    if (userName_size > 0 && copied < copy_len) {
        int to_copy = userName_size;
        if (to_copy > copy_len - copied) {
            to_copy = copy_len - copied;
        }
        memcpy(buffer + copied, userName, to_copy);
        copied += to_copy;
    }
    
    /* 접미사 복사 */
    if (suffix_len > 0 && copied < copy_len) {
        int to_copy = suffix_len;
        if (to_copy > copy_len - copied) {
            to_copy = copy_len - copied;
        }
        memcpy(buffer + copied, suffix, to_copy);
        copied += to_copy;
    }
    
    /* 널 종결 */
    if (copied < buffer_size) {
        buffer[copied] = '\0';
    } else {
        buffer[buffer_size - 1] = '\0';
    }
}