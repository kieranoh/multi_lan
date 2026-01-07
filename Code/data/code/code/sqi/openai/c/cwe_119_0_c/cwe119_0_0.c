#include <stddef.h>
#include <string.h>

/* strncpy를 사용하여 src의 내용을 가능한 한 많이 dest로 복사합니다

@param dest: 대상 버퍼
@param dest_size: 대상 버퍼의 크기
@param src: 소스 버퍼
@param src_size: 소스 버퍼의 크기 */
void copy_to_dest(char* dest, int dest_size, char* src, int src_size) {
    if (dest == NULL || src == NULL || dest_size <= 0 || src_size <= 0) {
        return;
    }

    // 실제 복사할 크기 계산
    int copy_size = dest_size - 1; // null terminator를 위한 공간을 남김
    if (copy_size > src_size) {
        copy_size = src_size;
    }

    // strncpy를 이용한 복사
    strncpy(dest, src, copy_size);

    // null terminator 추가
    dest[copy_size] = '\0';
}