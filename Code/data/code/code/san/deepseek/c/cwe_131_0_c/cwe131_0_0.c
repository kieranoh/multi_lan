#include <stdlib.h>
#include <string.h>

/**
 * 문자열의 복사본을 힙에 할당하여 반환합니다.
 * 호출자는 반환된 메모리를 해제할 책임이 있습니다.
 *
 * @param str: 복사할 문자열 (NULL일 수 없음)
 * @return 문자열의 복사본을 가리키는 포인터, 메모리 할당 실패 시 NULL
 */
char* my_strdup(const char* str) {
    // 입력 검증
    if (str == NULL) {
        return NULL;
    }

    // 문자열 길이 계산
    size_t len = strlen(str) + 1;  // 널 종결 문자 포함

    // 메모리 할당
    char* copy = (char*)malloc(len * sizeof(char));
    if (copy == NULL) {
        return NULL;  // 메모리 할당 실패
    }

    // 문자열 복사
    memcpy(copy, str, len);

    return copy;
}