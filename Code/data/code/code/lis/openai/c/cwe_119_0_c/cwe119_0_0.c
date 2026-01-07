#include <string.h>

/* strncpy를 사용하여 src의 내용을 dest로 최대한 복사합니다

@param dest: 대상 버퍼
@param dest_size: 대상 버퍼의 크기
@param src: 소스 버퍼
@param src_size: 소스 버퍼의 크기 */
void copy_to_dest(char* dest, int dest_size, char* src, int src_size) {
    if (dest == NULL || src == NULL || dest_size <= 0 || src_size <= 0) {
        return;
    }
    
    // src의 내용을 dest에 복사, dest_size - 1을 사용하는 이유는 null 문자 공간 확보
    strncpy(dest, src, dest_size - 1);
    
    // dest의 끝에 null 문자 추가
    dest[dest_size - 1] = '\0';
}