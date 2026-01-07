#include <stdlib.h>
#include <string.h>

/**
Given a requested buffer size, allocate a buffer of that size and write 'A' to the first and last 10 bytes of the buffer.

@param buf_size: the size of the buffer to allocate
@return the allocated buffer
*/
char* allocate_buffer_and_write(size_t buf_size) {
    // Handle edge case: if buf_size is 0, return NULL
    if (buf_size == 0) {
        return NULL;
    }
    
    // Allocate buffer
    char* buffer = (char*)malloc(buf_size);
    if (buffer == NULL) {
        return NULL;
    }
    
    // Initialize buffer to zeros for safety
    memset(buffer, 0, buf_size);
    
    // Calculate how many bytes to write at the beginning
    size_t write_start = (buf_size < 10) ? buf_size : 10;
    
    // Write 'A' to first bytes
    for (size_t i = 0; i < write_start; i++) {
        buffer[i] = 'A';
    }
    
    // Calculate how many bytes to write at the end
    if (buf_size > 10) {
        size_t write_end = (buf_size < 20) ? buf_size - 10 : 10;
        size_t start_pos = buf_size - write_end;
        
        // Write 'A' to last bytes
        for (size_t i = start_pos; i < buf_size; i++) {
            buffer[i] = 'A';
        }
    }
    
    return buffer;
}