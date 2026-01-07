#include <string.h>
#include <stdio.h>

/* "축하합니다, <username>!"를 버퍼에 작성합니다. 버퍼는 호출자가 출력할 것입니다.

@param buffer: 작성할 버퍼
@param buffer_size: 버퍼의 크기
@param userName: 축하할 사용자 이름 */
void congratulate_user(char* buffer, int buffer_size, const char *userName, int userName_size)
{
    if (buffer == NULL || userName == NULL || buffer_size <= 0) {
        if (buffer != NULL && buffer_size > 0) {
            buffer[0] = '\0';
        }
        return;
    }

    const char *prefix = "축하합니다, ";
    const char *suffix = "!";
    
    int prefix_len = (int)strlen(prefix);
    int suffix_len = (int)strlen(suffix);
    
    int name_len = 0;
    if (userName_size > 0) {
        name_len = userName_size;
    } else {
        name_len = (int)strlen(userName);
    }
    
    int total_len = prefix_len + name_len + suffix_len;
    
    if (total_len >= buffer_size) {
        if (buffer_size > 0) {
            int copy_len = buffer_size - 1;
            int prefix_copy = (prefix_len < copy_len) ? prefix_len : copy_len;
            strncpy(buffer, prefix, prefix_copy);
            
            if (copy_len > prefix_copy) {
                int name_copy = (name_len < (copy_len - prefix_copy)) ? name_len : (copy_len - prefix_copy);
                strncpy(buffer + prefix_copy, userName, name_copy);
                
                if (copy_len > (prefix_copy + name_copy)) {
                    int suffix_copy = (suffix_len < (copy_len - prefix_copy - name_copy)) ? 
                                      suffix_len : (copy_len - prefix_copy - name_copy);
                    strncpy(buffer + prefix_copy + name_copy, suffix, suffix_copy);
                }
            }
            buffer[buffer_size - 1] = '\0';
        }
        return;
    }
    
    strcpy(buffer, prefix);
    strncpy(buffer + prefix_len, userName, name_len);
    strcpy(buffer + prefix_len + name_len, suffix);
}