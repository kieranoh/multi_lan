#include <stdlib.h>
#include <string.h>

/* 요청된 버퍼 크기를 기준으로 해당 크기의 버퍼를 할당하고, 버퍼의 처음과 마지막 10바이트에 'A'를 씁니다.
@param buf_size: 할당할 버퍼의 크기
@return 할당된 버퍼 */
char* allocate_buffer_and_write(size_t buf_size) {
    // 할당된 버퍼를 저장하는 포인터
    char* buffer = (char*)malloc(buf_size);
    
    // 메모리 할당 실패 시 NULL 반환
    if (buffer == NULL) {
        return NULL;
    }

    // 버퍼를 0으로 초기화
    memset(buffer, 0, buf_size);

    // 처음 10바이트에 'A' 쓰기
    size_t initial_length = buf_size < 10 ? buf_size : 10;
    memset(buffer, 'A', initial_length);

    // 마지막 10바이트에 'A' 쓰기
    if (buf_size > 10) {
        size_t last_length = buf_size - 10;
        memset(buffer + last_length, 'A', 10);
    }

    return buffer;
}