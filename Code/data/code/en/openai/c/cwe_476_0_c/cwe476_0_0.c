#include <stdlib.h>
#include <string.h>

/**
Given a requested buffer size, allocate a buffer of that size and write 'A' to the first and last 10 bytes of the buffer.

@param buf_size: the size of the buffer to allocate
@return the allocated buffer
*/
char* allocate_buffer_and_write(size_t buf_size) {
    // Validate the buffer size
    if (buf_size == 0) {
        return NULL; // Return NULL if size is zero
    }

    // Allocate the buffer
    char* buffer = (char*)malloc(buf_size);
    if (buffer == NULL) {
        return NULL; // Return NULL if allocation fails
    }

    // Initialize the buffer to zero
    memset(buffer, 0, buf_size);

    // Write 'A' to the first 10 bytes
    size_t first_limit = buf_size < 10 ? buf_size : 10;
    memset(buffer, 'A', first_limit);

    // Write 'A' to the last 10 bytes
    size_t last_limit = buf_size < 10 ? buf_size : 10;
    if (buf_size > 10) {
        memset(buffer + (buf_size - last_limit), 'A', last_limit);
    }

    return buffer;
}