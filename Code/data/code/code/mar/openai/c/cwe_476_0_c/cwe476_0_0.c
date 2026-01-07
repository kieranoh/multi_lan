#include <stdlib.h>
#include <string.h>

/* 요청된 버퍼 크기를 기준으로 해당 크기의 버퍼를 할당하고, 버퍼의 처음과 마지막 10바이트에 'A'를 씁니다.

@param buf_size: 할당할 버퍼의 크기
@return 할당된 버퍼 */
char* allocate_buffer_and_write(size_t buf_size) {
    // 버퍼 크기가 0보다 작거나 같으면 NULL 반환
    if (buf_size <= 0) {
        return NULL;
    }

    // 요청된 크기의 버퍼 할당
    char* buffer = (char*)malloc(buf_size);
    if (buffer == NULL) {
        return NULL; // 메모리 할당 실패 시 NULL 반환
    }

    // 버퍼 초기화
    memset(buffer, 0, buf_size);

    // 처음 10바이트에 'A' 쓰기
    size_t first_chunk_size = (buf_size < 10) ? buf_size : 10;
    memset(buffer, 'A', first_chunk_size);

    // 마지막 10바이트에 'A' 쓰기
    if (buf_size > 10) {
        memset(buffer + buf_size - 10, 'A', 10);
    }

    return buffer;
}