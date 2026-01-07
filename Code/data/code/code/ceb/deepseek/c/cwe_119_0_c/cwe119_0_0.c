#include <string.h>

void copy_to_dest(char* dest, int dest_size, char* src, int src_size) {
    if (dest == NULL || src == NULL || dest_size <= 0) {
        return;
    }
    
    // Ensure we don't copy more than dest can hold (leaving space for null terminator)
    int copy_size = dest_size - 1;
    
    // If src_size is valid and smaller than available space, use src_size
    if (src_size > 0 && src_size < copy_size) {
        copy_size = src_size;
    }
    
    // Use strncpy to copy the content
    strncpy(dest, src, copy_size);
    
    // Ensure null termination
    dest[copy_size] = '\0';
}