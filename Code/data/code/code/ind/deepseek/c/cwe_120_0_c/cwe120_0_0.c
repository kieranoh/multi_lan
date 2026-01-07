#include <string.h>
#include <stdio.h>

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
    
    int actual_userName_size = userName_size;
    if (userName_size < 0) {
        actual_userName_size = (int)strlen(userName);
    }
    
    int total_length = prefix_len + actual_userName_size + suffix_len;
    
    if (total_length >= buffer_size) {
        int copy_len = buffer_size - 1;
        int prefix_copy_len = (prefix_len < copy_len) ? prefix_len : copy_len;
        
        strncpy(buffer, prefix, prefix_copy_len);
        buffer[prefix_copy_len] = '\0';
        
        if (prefix_copy_len < copy_len) {
            int remaining = copy_len - prefix_copy_len;
            int userName_copy_len = (actual_userName_size < remaining) ? actual_userName_size : remaining;
            
            strncat(buffer, userName, userName_copy_len);
            buffer[prefix_copy_len + userName_copy_len] = '\0';
            
            if (prefix_copy_len + userName_copy_len < copy_len) {
                int suffix_remaining = copy_len - (prefix_copy_len + userName_copy_len);
                int suffix_copy_len = (suffix_len < suffix_remaining) ? suffix_len : suffix_remaining;
                
                strncat(buffer, suffix, suffix_copy_len);
                buffer[prefix_copy_len + userName_copy_len + suffix_copy_len] = '\0';
            }
        }
        return;
    }
    
    strcpy(buffer, prefix);
    strncat(buffer, userName, actual_userName_size);
    strcat(buffer, suffix);
}