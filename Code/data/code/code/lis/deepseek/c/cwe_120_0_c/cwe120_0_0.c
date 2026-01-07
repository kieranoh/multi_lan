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
    int name_len = userName_size;
    
    int total_len = prefix_len + name_len + suffix_len;
    
    if (total_len >= buffer_size) {
        int copy_len = buffer_size - 1;
        int prefix_copy_len = (prefix_len < copy_len) ? prefix_len : copy_len;
        
        if (prefix_copy_len > 0) {
            strncpy(buffer, prefix, prefix_copy_len);
            buffer[prefix_copy_len] = '\0';
        }
        
        if (prefix_copy_len < copy_len) {
            int name_copy_len = copy_len - prefix_copy_len;
            int actual_name_copy = (name_len < name_copy_len) ? name_len : name_copy_len;
            
            if (actual_name_copy > 0) {
                strncat(buffer, userName, actual_name_copy);
            }
        }
        
        if (prefix_copy_len + name_len < copy_len) {
            int suffix_copy_len = copy_len - (prefix_copy_len + name_len);
            int actual_suffix_copy = (suffix_len < suffix_copy_len) ? suffix_len : suffix_copy_len;
            
            if (actual_suffix_copy > 0) {
                strncat(buffer, suffix, actual_suffix_copy);
            }
        }
    } else {
        strcpy(buffer, prefix);
        strncat(buffer, userName, name_len);
        strcat(buffer, suffix);
    }
}