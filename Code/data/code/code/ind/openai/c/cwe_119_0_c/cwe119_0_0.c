#include <string.h>

void copy_to_dest(char* dest, int dest_size, char* src, int src_size) {
    if (dest == NULL || src == NULL || dest_size <= 0 || src_size <= 0) {
        return;
    }
    
    // Calculate the number of bytes to copy
    int bytes_to_copy = (src_size < dest_size - 1) ? src_size : dest_size - 1;

    // Use strncpy to copy the contents
    strncpy(dest, src, bytes_to_copy);

    // Null terminate the destination string
    dest[bytes_to_copy] = '\0';
}