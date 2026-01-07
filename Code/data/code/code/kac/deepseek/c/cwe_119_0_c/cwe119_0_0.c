#include <string.h>

/* strncpy를 사용하여 src의 내용을 가능한 한 많이 dest로 복사합니다

@param dest: 대상 버퍼
@param dest_size: 대상 버퍼의 크기
@param src: 소스 버퍼
@param src_size: 소스 버퍼의 크기 */
void copy_to_dest(char* dest, int dest_size, char* src, int src_size) {
    if (dest == NULL || src == NULL || dest_size <= 0) {
        return;
    }
    
    /* 복사할 최대 바이트 수 계산: dest_size-1 (널 종결자를 위한 공간)과 src_size 중 작은 값 */
    int copy_size = (dest_size - 1) < src_size ? (dest_size - 1) : src_size;
    
    if (copy_size > 0) {
        strncpy(dest, src, copy_size);
        dest[copy_size] = '\0';  /* 널 종결자 보장 */
    } else {
        dest[0] = '\0';  /* 복사할 수 없는 경우 빈 문자열로 설정 */
    }
}