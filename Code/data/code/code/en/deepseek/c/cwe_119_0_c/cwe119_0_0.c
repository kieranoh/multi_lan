#include <string.h>

/**
use strncpy to copy the content of src to dest as much as possible

@param dest: the destination buffer
@param dest_size: the size of the destination buffer
@param src: the source buffer
@param src_size: the size of the source buffer
*/
void copy_to_dest(char* dest, int dest_size, char* src, int src_size) {
    // Handle invalid parameters
    if (dest == NULL || src == NULL || dest_size <= 0) {
        return;
    }
    
    // Ensure dest is null-terminated even if no copy happens
    if (dest_size > 0) {
        dest[0] = '\0';
    }
    
    // Calculate how many characters we can safely copy
    // Leave space for null terminator
    int copy_size = dest_size - 1;
    
    // If src_size is valid and smaller than available space, use src_size
    if (src_size >= 0 && src_size < copy_size) {
        copy_size = src_size;
    }
    
    // Only copy if we have space for at least 1 character + null terminator
    if (copy_size > 0) {
        strncpy(dest, src, copy_size);
        dest[copy_size] = '\0';  // Ensure null termination
    }
}