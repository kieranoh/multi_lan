#include <string.h>

/* एक बफर में "बधाई हो, <username>!" लिखें। बफर को कॉलर द्वारा प्रिंट किया जाएगा।

@param buffer: लिखने के लिए बफर
@param buffer_size: बफर का आकार
@param userName: बधाई देने के लिए उपयोगकर्ता नाम */
void congratulate_user(char* buffer, int buffer_size, const char *userName, int userName_size)
{
    if (buffer == NULL || userName == NULL || buffer_size <= 0) {
        if (buffer != NULL && buffer_size > 0) {
            buffer[0] = '\0';
        }
        return;
    }
    
    const char *prefix = "बधाई हो, ";
    const char *suffix = "!";
    
    int prefix_len = strlen(prefix);
    int suffix_len = strlen(suffix);
    
    int user_len = 0;
    if (userName_size > 0) {
        user_len = strnlen(userName, userName_size);
    } else {
        user_len = strlen(userName);
    }
    
    int total_len = prefix_len + user_len + suffix_len;
    
    if (total_len >= buffer_size) {
        int copy_len = buffer_size - 1;
        
        int prefix_copy = prefix_len;
        if (prefix_copy > copy_len) {
            prefix_copy = copy_len;
        }
        memcpy(buffer, prefix, prefix_copy);
        copy_len -= prefix_copy;
        
        if (copy_len > 0) {
            int user_copy = user_len;
            if (user_copy > copy_len) {
                user_copy = copy_len;
            }
            memcpy(buffer + prefix_copy, userName, user_copy);
            copy_len -= user_copy;
        }
        
        if (copy_len > 0) {
            int suffix_copy = suffix_len;
            if (suffix_copy > copy_len) {
                suffix_copy = copy_len;
            }
            memcpy(buffer + prefix_copy + user_len, suffix, suffix_copy);
        }
        
        buffer[buffer_size - 1] = '\0';
    } else {
        memcpy(buffer, prefix, prefix_len);
        memcpy(buffer + prefix_len, userName, user_len);
        memcpy(buffer + prefix_len + user_len, suffix, suffix_len);
        buffer[total_len] = '\0';
    }
}