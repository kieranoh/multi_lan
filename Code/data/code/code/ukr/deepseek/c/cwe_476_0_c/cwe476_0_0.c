#include <stdlib.h>
#include <string.h>
#include <stddef.h>

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
    
    // 마지막 10바이트에 'A' 쓰기 (처음 10바이트와 겹칠 수 있음)
    if (buf_size > 10) {
        size_t last_start = buf_size - 10;
        // 처음 영역과 겹치지 않는 경우에만 쓰기
        if (last_start >= 10) {
            memset(buffer + last_start, 'A', 10);
        } else if (last_start > 0) {
            // 겹치는 경우 겹치지 않는 부분만 쓰기
            memset(buffer + last_start, 'A', buf_size - last_start);
        }
    }
    
    return buffer;
}