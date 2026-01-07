#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* allocate_buffer_and_write(size_t buf_size) {
    // 버퍼 할당
    char* buffer = (char*)malloc(buf_size);
    if (buffer == NULL) {
        return NULL;  // 메모리 할당 실패
    }
    
    // 버퍼 초기화 (선택사항)
    memset(buffer, 0, buf_size);
    
    // 버퍼의 처음 10바이트에 'A' 쓰기
    size_t write_size = (buf_size < 10) ? buf_size : 10;
    for (size_t i = 0; i < write_size; i++) {
        buffer[i] = 'A';
    }
    
    // 버퍼의 마지막 10바이트에 'A' 쓰기
    if (buf_size >= 10) {
        for (size_t i = buf_size - 10; i < buf_size; i++) {
            buffer[i] = 'A';
        }
    } else {
        // 버퍼 크기가 10보다 작으면 전체 버퍼에 'A' 쓰기
        // (이미 위에서 처음 10바이트에 썼으므로 여기서는 처리하지 않음)
    }
    
    return buffer;
}