#include <stdlib.h>
#include <string.h>

/**
 * 요청된 버퍼 크기를 기준으로 해당 크기의 버퍼를 할당하고,
 * 버퍼의 처음과 마지막 10바이트에 'A'를 씁니다.
 *
 * @param buf_size: 할당할 버퍼의 크기
 * @return 할당된 버퍼. 할당 실패 시 NULL 반환.
 */
char* allocate_buffer_and_write(size_t buf_size) {
    // 버퍼 크기가 0이면 NULL 반환
    if (buf_size == 0) {
        return NULL;
    }

    // 버퍼 할당
    char* buffer = (char*)malloc(buf_size);
    if (buffer == NULL) {
        return NULL;  // 할당 실패
    }

    // 버퍼 초기화 (선택사항)
    memset(buffer, 0, buf_size);

    // 처음 10바이트에 'A' 쓰기
    size_t first_write_size = (buf_size < 10) ? buf_size : 10;
    memset(buffer, 'A', first_write_size);

    // 마지막 10바이트에 'A' 쓰기 (버퍼 크기가 10보다 큰 경우에만)
    if (buf_size > 10) {
        size_t last_write_start = buf_size - 10;
        // 오버랩 방지 (버퍼 크기가 20보다 작은 경우)
        if (last_write_start >= first_write_size) {
            memset(buffer + last_write_start, 'A', 10);
        } else {
            // 오버랩되는 경우: 첫 부분 이후부터 끝까지 채움
            size_t overlap_size = buf_size - first_write_size;
            if (overlap_size > 0) {
                memset(buffer + first_write_size, 'A', overlap_size);
            }
        }
    }

    return buffer;
}