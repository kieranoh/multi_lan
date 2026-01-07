#include <string.h>

/* strncpy를 사용하여 src의 내용을 dest에 최대한 복사합니다

@param dest: 대상 버퍼
@param dest_size: 대상 버퍼의 크기
@param src: 소스 버퍼
@param src_size: 소스 버퍼의 크기 */
void copy_to_dest(char* dest, int dest_size, char* src, int src_size) {
    if (dest == NULL || src == NULL || dest_size <= 0) {
        return;
    }
    
    /* dest_size가 1이면 널 종료 문자만 저장 가능 */
    if (dest_size == 1) {
        dest[0] = '\0';
        return;
    }
    
    /* 복사할 최대 바이트 수 계산: dest_size-1 또는 src_size 중 작은 값 */
    int copy_size = (src_size < dest_size - 1) ? src_size : dest_size - 1;
    
    /* strncpy를 사용하여 복사 */
    strncpy(dest, src, copy_size);
    
    /* strncpy는 널 종료를 보장하지 않으므로 수동으로 널 종료 */
    dest[copy_size] = '\0';
}