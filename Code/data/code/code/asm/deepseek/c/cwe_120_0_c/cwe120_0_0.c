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
    
    int user_len = userName_size;
    if (userName_size < 0) {
        user_len = (int)strlen(userName);
    }
    
    int total_len = prefix_len + user_len + suffix_len;
    
    if (total_len >= buffer_size) {
        int available = buffer_size - 1;
        int prefix_copy = (prefix_len < available) ? prefix_len : available;
        if (prefix_copy > 0) {
            strncpy(buffer, prefix, prefix_copy);
            buffer[prefix_copy] = '\0';
        }
        
        if (prefix_copy < available) {
            int user_copy = available - prefix_copy;
            if (user_copy > user_len) user_copy = user_len;
            strncat(buffer, userName, user_copy);
        }
        
        if (prefix_len + user_len < available) {
            int suffix_copy = available - (prefix_len + user_len);
            if (suffix_copy > suffix_len) suffix_copy = suffix_len;
            strncat(buffer, suffix, suffix_copy);
        }
        return;
    }
    
    strcpy(buffer, prefix);
    strncat(buffer, userName, user_len);
    strcat(buffer, suffix);
}