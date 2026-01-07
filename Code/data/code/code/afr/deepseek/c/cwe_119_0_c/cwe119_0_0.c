#include <string.h>

/* strncpy를 사용하여 src의 내용을 dest로 최대한 복사합니다

@param dest: 대상 버퍼
@param dest_size: 대상 버퍼의 크기
@param src: 소스 버퍼
@param src_size: 소스 버퍼의 크기 */
void copy_to_dest(char* dest, int dest_size, char* src, int src_size) {
    if (dest == NULL || src == NULL || dest_size <= 0) {
        return;
    }
    
    /* dest_size가 1 이상인 경우, 항상 null 종료 문자를 위한 공간을 확보합니다 */
    if (src_size < 0) {
        src_size = 0;
    }
    
    /* 복사할 최대 문자 수 계산: dest_size-1 또는 src_size 중 작은 값 */
    int copy_len = dest_size - 1;
    if (src_size < copy_len) {
        copy_len = src_size;
    }
    
    /* strncpy를 사용하여 복사 수행 */
    strncpy(dest, src, copy_len);
    
    /* strncpy는 null 종료를 보장하지 않으므로 명시적으로 null 종료 */
    dest[copy_len] = '\0';
}