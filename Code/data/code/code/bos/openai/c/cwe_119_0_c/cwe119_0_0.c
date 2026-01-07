#include <string.h>

/* strncpy를 사용하여 src의 내용을 dest에 최대한 복사합니다
@param dest: 대상 버퍼
@param dest_size: 대상 버퍼의 크기
@param src: 소스 버퍼
@param src_size: 소스 버퍼의 크기 */
void copy_to_dest(char* dest, int dest_size, char* src, int src_size) {
    // dest 버퍼의 크기가 0이거나 src가 NULL인 경우, 아무 것도 하지 않음
    if (dest_size <= 0 || src == NULL) {
        return;
    }

    // src의 내용을 dest로 복사하되, dest의 크기에 맞춰 최대 dest_size - 1 바이트를 복사하고, 마지막에 null 문자 추가
    strncpy(dest, src, dest_size - 1);
    dest[dest_size - 1] = '\0'; // 항상 null로 종료
}