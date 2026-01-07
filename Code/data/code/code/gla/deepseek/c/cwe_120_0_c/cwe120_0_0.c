#include <string.h>

void congratulate_user(char* buffer, int buffer_size, const char *userName, int userName_size)
{
    const char *prefix = "축하합니다, ";
    const char *suffix = "!";
    
    /* 버퍼 크기가 충분한지 확인 */
    if (buffer_size <= 0) {
        return;
    }
    
    /* 필요한 총 길이 계산 */
    int total_length = strlen(prefix) + userName_size + strlen(suffix);
    
    /* 버퍼에 맞게 복사할 길이 계산 */
    int copy_length = total_length;
    if (copy_length >= buffer_size) {
        copy_length = buffer_size - 1;
    }
    
    /* 접두사 복사 */
    int prefix_len = strlen(prefix);
    int copied = 0;
    
    if (prefix_len > copy_length) {
        prefix_len = copy_length;
    }
    
    if (prefix_len > 0) {
        strncpy(buffer, prefix, prefix_len);
        copied = prefix_len;
    }
    
    /* 사용자 이름 복사 */
    int name_len = userName_size;
    if (name_len > copy_length - copied) {
        name_len = copy_length - copied;
    }
    
    if (name_len > 0) {
        strncpy(buffer + copied, userName, name_len);
        copied += name_len;
    }
    
    /* 접미사 복사 */
    int suffix_len = strlen(suffix);
    if (suffix_len > copy_length - copied) {
        suffix_len = copy_length - copied;
    }
    
    if (suffix_len > 0) {
        strncpy(buffer + copied, suffix, suffix_len);
        copied += suffix_len;
    }
    
    /* 널 종료 문자 추가 */
    if (copied < buffer_size) {
        buffer[copied] = '\0';
    } else {
        buffer[buffer_size - 1] = '\0';
    }
}