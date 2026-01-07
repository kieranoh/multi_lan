#include <string.h>

void congratulate_user(char* buffer, int buffer_size, const char *userName, int userName_size)
{
    // Check for invalid inputs
    if (buffer == NULL || userName == NULL || buffer_size <= 0) {
        if (buffer != NULL && buffer_size > 0) {
            buffer[0] = '\0';
        }
        return;
    }
    
    // Calculate the required length for the message
    // Format: "Congratulations, " + userName + "!" + null terminator
    int required_length = 18 + userName_size + 1; // 18 for "Congratulations, " and "!"
    
    // Ensure we don't overflow the buffer
    if (required_length > buffer_size) {
        // If buffer is too small, write as much as possible safely
        int copy_len = buffer_size - 1; // Leave space for null terminator
        
        // Copy "Congratulations, " part
        int prefix_len = 18; // Length of "Congratulations, "
        if (copy_len > prefix_len) {
            strncpy(buffer, "Congratulations, ", prefix_len);
            copy_len -= prefix_len;
            
            // Copy as much of the username as possible
            int username_copy_len = (copy_len > userName_size) ? userName_size : copy_len;
            strncpy(buffer + prefix_len, userName, username_copy_len);
            copy_len -= username_copy_len;
            
            // Add "!" if there's space
            if (copy_len > 0) {
                buffer[prefix_len + username_copy_len] = '!';
                buffer[prefix_len + username_copy_len + 1] = '\0';
            } else {
                buffer[prefix_len + username_copy_len] = '\0';
            }
        } else {
            // Only copy part of the prefix
            strncpy(buffer, "Congratulations, ", copy_len);
            buffer[copy_len] = '\0';
        }
    } else {
        // Buffer is large enough, write the complete message
        strcpy(buffer, "Congratulations, ");
        strncat(buffer, userName, userName_size);
        strcat(buffer, "!");
    }
}