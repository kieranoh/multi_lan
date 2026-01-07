#include <string.h>
#include <stdio.h>

void congratulate_user(char* buffer, int buffer_size, const char *userName, int userName_size)
{
    if (buffer == NULL || userName == NULL || buffer_size <= 0) {
        return;
    }
    
    const char *prefix = "Congratulations, ";
    const char *suffix = "!";
    
    int prefix_len = (int)strlen(prefix);
    int suffix_len = (int)strlen(suffix);
    
    int available_user_len = buffer_size - prefix_len - suffix_len - 1;
    
    if (available_user_len <= 0) {
        return;
    }
    
    int actual_user_len = userName_size;
    if (actual_user_len > available_user_len) {
        actual_user_len = available_user_len;
    }
    
    char *ptr = buffer;
    
    memcpy(ptr, prefix, prefix_len);
    ptr += prefix_len;
    
    memcpy(ptr, userName, actual_user_len);
    ptr += actual_user_len;
    
    memcpy(ptr, suffix, suffix_len);
    ptr += suffix_len;
    
    *ptr = '\0';
}