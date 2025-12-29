#include <string.h>

/* 가능한 한 src의 내용을 dest로 복사하려면 strncpy를 사용하세요.

@param dest: 목적지 버퍼
@param dest_size: 목적지 버퍼의 크기
@param src: 원본 버퍼
@param src_size: 원본 버퍼의 크기 */
void copy_to_dest(char* dest, int dest_size, char* src, int src_size) {
    if (dest == NULL || src == NULL || dest_size <= 0) {
        return;
    }
    
    /* dest_size가 1인 경우, 널 종료 문자만 저장할 수 있습니다 */
    if (dest_size == 1) {
        dest[0] = '\0';
        return;
    }
    
    /* 복사할 실제 바이트 수를 계산합니다: dest_size-1과 src_size 중 작은 값 */
    int copy_size = (src_size < dest_size - 1) ? src_size : dest_size - 1;
    
    /* strncpy를 사용하여 복사합니다 */
    strncpy(dest, src, copy_size);
    
    /* strncpy는 널 종료를 보장하지 않으므로, 항상 dest를 널 종료합니다 */
    dest[copy_size] = '\0';
}