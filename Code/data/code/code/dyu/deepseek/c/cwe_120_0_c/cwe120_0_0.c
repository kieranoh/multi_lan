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
    
    int required_size = prefix_len + userName_size + suffix_len + 1;
    
    if (required_size > buffer_size) {
        snprintf(buffer, buffer_size, "Buffer too small");
        return;
    }
    
    char *ptr = buffer;
    
    memcpy(ptr, prefix, prefix_len);
    ptr += prefix_len;
    
    memcpy(ptr, userName, userName_size);
    ptr += userName_size;
    
    memcpy(ptr, suffix, suffix_len);
    ptr += suffix_len;
    
    *ptr = '\0';
}