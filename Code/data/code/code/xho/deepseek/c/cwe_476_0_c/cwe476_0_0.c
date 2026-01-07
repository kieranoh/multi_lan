#include <stdlib.h>
#include <string.h>

char* allocate_buffer_and_write(size_t buf_size) {
    /* 요청된 버퍼 크기를 기준으로 해당 크기의 버퍼를 할당하고, 버퍼의 처음과 마지막 10바이트에 'A'를 씁니다.
    
    @param buf_size: 할당할 버퍼의 크기
    @return 할당된 버퍼 */
    
    // 버퍼 크기가 0이면 NULL 반환
    if (buf_size == 0) {
        return NULL;
    }
    
    // 버퍼 할당
    char* buffer = (char*)malloc(buf_size);
    if (buffer == NULL) {
        return NULL;
    }
    
    // 버퍼를 0으로 초기화 (선택사항)
    memset(buffer, 0, buf_size);
    
    // 처음 10바이트에 'A' 쓰기
    size_t first_write_size = (buf_size < 10) ? buf_size : 10;
    memset(buffer, 'A', first_write_size);
    
    // 마지막 10바이트에 'A' 쓰기 (버퍼 크기가 10보다 클 경우만)
    if (buf_size > 10) {
        size_t last_write_start = buf_size - 10;
        // 마지막 10바이트와 처음 10바이트가 겹치지 않도록 처리
        if (last_write_start > first_write_size) {
            memset(buffer + last_write_start, 'A', 10);
        }
    }
    
    return buffer;
}