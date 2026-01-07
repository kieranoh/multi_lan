#include <stdlib.h>
#include <string.h>

/**
 * 요청된 버퍼 크기를 기준으로 해당 크기의 버퍼를 할당하고,
 * 버퍼의 처음과 마지막 10바이트에 'A'를 씁니다.
 * 
 * @param buf_size: 할당할 버퍼의 크기
 * @return 할당된 버퍼 (할당 실패 시 NULL 반환)
 */
char* allocate_buffer_and_write(size_t buf_size) {
    // 버퍼 할당
    char* buffer = (char*)malloc(buf_size);
    if (buffer == NULL) {
        return NULL;  // 메모리 할당 실패
    }
    
    // 버퍼를 0으로 초기화 (선택사항)
    memset(buffer, 0, buf_size);
    
    // 처음 10바이트에 'A' 쓰기
    size_t first_write_size = (buf_size < 10) ? buf_size : 10;
    for (size_t i = 0; i < first_write_size; i++) {
        buffer[i] = 'A';
    }
    
    // 마지막 10바이트에 'A' 쓰기
    if (buf_size >= 10) {
        size_t last_start = buf_size - 10;
        for (size_t i = last_start; i < buf_size; i++) {
            buffer[i] = 'A';
        }
    }
    
    return buffer;
}