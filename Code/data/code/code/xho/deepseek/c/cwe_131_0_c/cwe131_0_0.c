#include <stdlib.h>
#include <string.h>

char* my_strdup(const char* str) {
    /* 입력 문자열이 NULL인 경우 NULL 반환 */
    if (str == NULL) {
        return NULL;
    }
    
    /* 문자열 길이 계산 */
    size_t len = strlen(str);
    
    /* 힙에 메모리 할당 (널 종결 문자 포함) */
    char* copy = (char*)malloc(len + 1);
    
    /* 메모리 할당 실패 시 NULL 반환 */
    if (copy == NULL) {
        return NULL;
    }
    
    /* 문자열 복사 */
    strcpy(copy, str);
    
    /* 복사된 문자열 반환 */
    return copy;
}