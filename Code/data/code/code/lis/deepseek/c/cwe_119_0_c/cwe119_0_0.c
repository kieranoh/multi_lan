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
    
    /* dest_size가 1인 경우 널 종결자만 저장 */
    if (dest_size == 1) {
        dest[0] = '\0';
        return;
    }
    
    /* 실제로 복사할 수 있는 최대 바이트 수 계산 */
    int copy_size;
    if (src_size < 0) {
        /* src_size가 음수이면 src가 널 종결 문자열이라고 가정 */
        copy_size = dest_size - 1;
    } else {
        /* src_size와 dest_size-1 중 작은 값 선택 */
        copy_size = (src_size < dest_size - 1) ? src_size : dest_size - 1;
    }
    
    /* strncpy를 사용하여 복사 */
    strncpy(dest, src, copy_size);
    
    /* strncpy는 널 종결을 보장하지 않으므로 명시적으로 널 종결 */
    dest[copy_size] = '\0';
}