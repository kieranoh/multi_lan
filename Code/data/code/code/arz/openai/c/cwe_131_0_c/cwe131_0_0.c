#include <stdlib.h>
#include <string.h>

/* 문자열이 주어지면, 문자열의 복사본을 반환합니다. 복사본은 힙에 할당되어야 하며, 호출자가 이를 해제할 책임이 있습니다.

@param str: 복사할 문자열
@return 문자열의 복사본 */
char* my_strdup(const char* str) {
    if (str == NULL) {
        return NULL; // NULL 체크
    }

    size_t len = strlen(str); // 문자열 길이 계산
    char* copy = (char*)malloc(len + 1); // 힙에 메모리 할당 (+1 for null terminator)

    if (copy == NULL) {
        return NULL; // 메모리 할당 실패 체크
    }

    strcpy(copy, str); // 문자열 복사
    return copy; // 복사본 반환
}