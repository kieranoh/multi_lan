#include <stdlib.h>
#include <string.h>

/*
 요청된 버퍼 크기를 기준으로 해당 크기의 버퍼를 할당하고, 
 버퍼의 처음과 마지막 10바이트에 'A'를 씁니다.

 @param buf_size: 할당할 버퍼의 크기
 @return 할당된 버퍼
 */
char* allocate_buffer_and_write(size_t buf_size) {
    // Allocate memory for the buffer
    char* buffer = (char*)malloc(buf_size);
    if (buffer == NULL) {
        return NULL; // Return NULL if allocation fails
    }

    // Initialize the buffer with zero
    memset(buffer, 0, buf_size);

    // Write 'A' to the first 10 bytes if buf_size is large enough
    if (buf_size >= 10) {
        memset(buffer, 'A', 10);
    }

    // Write 'A' to the last 10 bytes if buf_size is large enough
    if (buf_size >= 10) {
        memset(buffer + buf_size - 10, 'A', 10);
    }

    return buffer; // Return the allocated buffer
}