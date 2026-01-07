#include <string.h>

/* strncpy를 사용하여 src의 내용을 가능한 한 많이 dest로 복사합니다
@param dest: 대상 버퍼
@param dest_size: 대상 버퍼의 크기
@param src: 소스 버퍼
@param src_size: 소스 버퍼의 크기 */
void copy_to_dest(char* dest, int dest_size, char* src, int src_size) {
    if (dest == NULL || src == NULL || dest_size <= 0 || src_size <= 0) {
        return; // 잘못된 입력 처리
    }

    // src의 내용을 dest로 복사
    strncpy(dest, src, dest_size - 1); // dest_size - 1은 null 문자 공간을 남겨두기 위함
    dest[dest_size - 1] = '\0'; // null 문자 추가하여 문자열 종료
}