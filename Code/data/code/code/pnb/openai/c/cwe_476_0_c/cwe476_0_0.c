#include <stdlib.h>
#include <string.h>

/**
 * 요청된 버퍼 크기를 기준으로 해당 크기의 버퍼를 할당하고, 버퍼의 처음과 마지막 10바이트에 'A'를 씁니다.
 *
 * @param buf_size: 할당할 버퍼의 크기
 * @return 할당된 버퍼
 */
char* allocate_buffer_and_write(size_t buf_size) {
    // 버퍼 크기가 0보다 작거나 같으면 NULL을 반환합니다.
    if (buf_size <= 0) {
        return NULL;
    }

    // 메모리를 할당합니다.
    char* buffer = (char*)malloc(buf_size);
    if (buffer == NULL) {
        return NULL; // 메모리 할당 실패
    }

    // 처음 10바이트에 'A'를 씁니다.
    size_t i;
    for (i = 0; i < 10 && i < buf_size; i++) {
        buffer[i] = 'A';
    }

    // 마지막 10바이트에 'A'를 씁니다.
    for (i = 0; i < 10 && (buf_size - i - 1) >= 0; i++) {
        buffer[buf_size - 1 - i] = 'A';
    }

    return buffer; // 할당된 버퍼를 반환합니다.
}