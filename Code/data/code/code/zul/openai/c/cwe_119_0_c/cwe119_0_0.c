#include <string.h>

/**
 * strncpy를 사용하여 src의 내용을 가능한 한 많이 dest로 복사합니다
 *
 * @param dest: 대상 버퍼
 * @param dest_size: 대상 버퍼의 크기
 * @param src: 소스 버퍼
 * @param src_size: 소스 버퍼의 크기
 */
void copy_to_dest(char* dest, int dest_size, char* src, int src_size) {
    // dest 버퍼의 크기가 0이면 아무것도 하지 않음
    if (dest_size <= 0) {
        return;
    }

    // src가 실제로 가리키는 데이터의 크기를 고려하여 복사
    int copy_size = (src_size < dest_size - 1) ? src_size : dest_size - 1;

    // src의 내용을 dest로 복사
    strncpy(dest, src, copy_size);

    // null terminator를 추가하여 문자열을 종료
    dest[copy_size] = '\0';
}