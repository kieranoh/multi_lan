#include <stdlib.h>
#include <string.h>

char* my_strdup(const char* str) {
    /* 입력 검증: NULL 포인터가 전달되면 NULL 반환 */
    if (str == NULL) {
        return NULL;
    }
    
    /* 문자열 길이 계산 */
    size_t len = strlen(str);
    
    /* 메모리 할당: 문자열 길이 + 널 종료 문자 */
    char* copy = (char*)malloc(len + 1);
    
    /* 메모리 할당 실패 검증 */
    if (copy == NULL) {
        return NULL;
    }
    
    /* 문자열 복사 */
    strcpy(copy, str);
    
    /* 복사된 문자열 반환 */
    return copy;
}