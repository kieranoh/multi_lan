#include <stdio.h>
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
    // 버퍼 크기가 0인 경우 NULL 반환
    if (buf_size == 0) {
        return NULL;
    }
    
    // 메모리 할당
    char* buffer = (char*)malloc(buf_size * sizeof(char));
    
    // 할당 실패 시 NULL 반환
    if (buffer == NULL) {
        return NULL;
    }
    
    // 버퍼를 0으로 초기화 (선택사항)
    memset(buffer, 0, buf_size);
    
    // 버퍼의 처음 10바이트에 'A' 쓰기
    size_t first_write_size = (buf_size < 10) ? buf_size : 10;
    for (size_t i = 0; i < first_write_size; i++) {
        buffer[i] = 'A';
    }
    
    // 버퍼의 마지막 10바이트에 'A' 쓰기
    if (buf_size > 10) {
        size_t last_write_start = buf_size - 10;
        size_t last_write_size = (buf_size - last_write_start < 10) ? 
                                 (buf_size - last_write_start) : 10;
        
        // 시작 위치가 버퍼 크기보다 작은지 확인
        if (last_write_start < buf_size) {
            for (size_t i = 0; i < last_write_size; i++) {
                buffer[last_write_start + i] = 'A';
            }
        }
    }
    
    return buffer;
}