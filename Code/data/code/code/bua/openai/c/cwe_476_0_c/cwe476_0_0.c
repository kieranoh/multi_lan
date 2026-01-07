#include <stdlib.h>
#include <string.h>

char* allocate_buffer_and_write(size_t buf_size) {
    // 요청된 버퍼 크기보다 작은 경우 NULL 반환
    if (buf_size < 20) {
        return NULL;
    }

    // 메모리 할당
    char* buffer = (char*)malloc(buf_size);
    if (buffer == NULL) {
        return NULL; // 메모리 할당 실패 시 NULL 반환
    }

    // 버퍼 초기화
    memset(buffer, 0, buf_size);

    // 처음 10바이트에 'A' 쓰기
    memset(buffer, 'A', 10);

    // 마지막 10바이트에 'A' 쓰기
    memset(buffer + buf_size - 10, 'A', 10);

    return buffer; // 할당된 버퍼 반환
}