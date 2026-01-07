#include <string.h>

void congratulate_user(char* buffer, int buffer_size, const char *userName, int userName_size)
{
    const char *prefix = "恭喜，";
    const char *suffix = "！";
    
    // 计算前缀和后缀的长度
    int prefix_len = strlen(prefix);
    int suffix_len = strlen(suffix);
    
    // 计算总长度（包括空终止符）
    int total_len = prefix_len + userName_size + suffix_len;
    
    // 确保不会溢出缓冲区
    if (total_len >= buffer_size) {
        // 如果缓冲区太小，尽可能多地复制并确保以空字符结尾
        int copy_len = buffer_size - 1;
        
        // 复制前缀
        int prefix_copy = (prefix_len < copy_len) ? prefix_len : copy_len;
        strncpy(buffer, prefix, prefix_copy);
        copy_len -= prefix_copy;
        
        // 复制用户名
        if (copy_len > 0) {
            int name_copy = (userName_size < copy_len) ? userName_size : copy_len;
            strncpy(buffer + prefix_copy, userName, name_copy);
            copy_len -= name_copy;
            
            // 复制后缀
            if (copy_len > 0) {
                int suffix_copy = (suffix_len < copy_len) ? suffix_len : copy_len;
                strncpy(buffer + prefix_copy + name_copy, suffix, suffix_copy);
            }
        }
        
        // 确保以空字符结尾
        buffer[buffer_size - 1] = '\0';
    } else {
        // 缓冲区足够大，安全地复制所有内容
        strcpy(buffer, prefix);
        strncpy(buffer + prefix_len, userName, userName_size);
        strcpy(buffer + prefix_len + userName_size, suffix);
    }
}