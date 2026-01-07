#include <stdlib.h>
#include <string.h>

char* allocate_buffer_and_write(size_t buf_size) {
    if (buf_size == 0) {
        return NULL;
    }
    
    char* buffer = (char*)malloc(buf_size);
    if (buffer == NULL) {
        return NULL;
    }
    
    // 처음 10바이트에 'A' 쓰기
    size_t first_write_size = (buf_size < 10) ? buf_size : 10;
    memset(buffer, 'A', first_write_size);
    
    // 마지막 10바이트에 'A' 쓰기
    if (buf_size > 10) {
        size_t last_write_start = buf_size - 10;
        size_t last_write_size = (buf_size - last_write_start < 10) ? 
                                 buf_size - last_write_start : 10;
        memset(buffer + last_write_start, 'A', last_write_size);
    }
    
    return buffer;
}