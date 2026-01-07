#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * 문자열이 주어지면, 문자열의 복사본을 반환합니다. 복사본은 힙에 할당되어야 하며, 호출자가 이를 해제할 책임이 있습니다.
 *
 * @param str: 복사할 문자열
 * @return 문자열의 복사본
 */
char* my_strdup(const char* str) {
    // NULL 체크
    if (str == NULL) {
        return NULL;
    }

    // 문자열의 길이를 구하고, 복사할 메모리 할당
    size_t len = strlen(str);
    char* copy = (char*)malloc((len + 1) * sizeof(char)); // +1 for null terminator
    if (copy == NULL) {
        return NULL; // 메모리 할당 실패 시 NULL 반환
    }

    // 문자열 복사
    strcpy(copy, str);
    return copy; // 복사본 반환
}