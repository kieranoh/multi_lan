#include <string.h>

/* strncpy를 사용하여 src의 내용을 dest로 최대한 복사합니다

@param dest: 대상 버퍼
@param dest_size: 대상 버퍼의 크기
@param src: 소스 버퍼
@param src_size: 소스 버퍼의 크기 */
void copy_to_dest(char* dest, int dest_size, char* src, int src_size) {
    if (dest == NULL || src == NULL || dest_size <= 0) {
        return; // 유효성 검사
    }

    // src의 내용을 dest로 최대한 복사
    strncpy(dest, src, dest_size - 1);
    dest[dest_size - 1] = '\0'; // null 종료
}