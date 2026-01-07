#include <string.h>

void copy_to_dest(char* dest, int dest_size, char* src, int src_size) {
    // Ensure dest_size is not negative and is greater than 0
    if (dest_size <= 0) {
        return;
    }

    // Use strncpy to copy from src to dest
    strncpy(dest, src, dest_size - 1); // Leave space for null terminator
    dest[dest_size - 1] = '\0'; // Ensure dest is null-terminated

    // Note: strncpy does not null-terminate if src_size is greater than or equal to dest_size
    // The above line ensures that we always null-terminate dest.
}