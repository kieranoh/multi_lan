#include <string.h>

/* "축하합니다, <username>!"를 버퍼에 작성합니다. 이 버퍼는 호출자가 출력할 것입니다.

@param buffer: 작성할 버퍼
@param buffer_size: 버퍼의 크기
@param userName: 축하할 사용자 이름 */
void congratulate_user(char* buffer, int buffer_size, const char *userName, int userName_size)
{
    if (buffer == NULL || userName == NULL || buffer_size <= 0) {
        return;
    }
    
    const char *prefix = "축하합니다, ";
    const char *suffix = "!";
    
    int prefix_len = strlen(prefix);
    int suffix_len = strlen(suffix);
    
    int available_size = buffer_size - 1;
    
    int write_pos = 0;
    
    if (prefix_len > 0) {
        int copy_len = prefix_len < available_size ? prefix_len : available_size;
        if (copy_len > 0) {
            strncpy(buffer, prefix, copy_len);
            write_pos += copy_len;
            available_size -= copy_len;
        }
    }
    
    if (available_size > 0 && userName_size > 0) {
        int copy_len = userName_size < available_size ? userName_size : available_size;
        if (copy_len > 0) {
            strncpy(buffer + write_pos, userName, copy_len);
            write_pos += copy_len;
            available_size -= copy_len;
        }
    }
    
    if (available_size > 0 && suffix_len > 0) {
        int copy_len = suffix_len < available_size ? suffix_len : available_size;
        if (copy_len > 0) {
            strncpy(buffer + write_pos, suffix, copy_len);
            write_pos += copy_len;
        }
    }
    
    buffer[write_pos] = '\0';
}