#include <string.h>

/*
 * strncpy를 사용하여 src의 내용을 가능한 한 많이 dest로 복사합니다
 *
 * @param dest: 대상 버퍼
 * @param dest_size: 대상 버퍼의 크기
 * @param src: 소스 버퍼
 * @param src_size: 소스 버퍼의 크기
 */
void copy_to_dest(char* dest, int dest_size, char* src, int src_size) {
    if (dest == NULL || src == NULL || dest_size <= 0 || src_size <= 0) {
        return; // 잘못된 입력에 대해 조용히 반환합니다.
    }
    
    // src의 실제 복사할 크기를 계산합니다.
    int copy_size = (src_size < dest_size - 1) ? src_size : dest_size - 1;

    // src의 내용을 dest로 복사합니다.
    strncpy(dest, src, copy_size);

    // 문자열 종료 문자를 추가합니다.
    dest[copy_size] = '\0';
}