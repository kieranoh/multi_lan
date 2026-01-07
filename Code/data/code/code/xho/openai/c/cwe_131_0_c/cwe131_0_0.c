#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* 문자열이 주어지면, 문자열의 복사본을 반환합니다. 복사본은 힙에 할당되어야 하며, 호출자가 이를 해제할 책임이 있습니다.

@param str: 복사할 문자열
@return 문자열의 복사본 */
char* my_strdup(const char* str) {
    // 입력 문자열이 NULL인 경우 NULL을 반환
    if (str == NULL) {
        return NULL;
    }
    
    // 문자열의 길이를 계산
    size_t length = strlen(str);
    
    // 힙에 메모리 할당 (길이 + 1(널 종료 문자))
    char* copy = (char*)malloc((length + 1) * sizeof(char));
    
    // 메모리 할당 실패 확인
    if (copy == NULL) {
        return NULL;
    }
    
    // 문자열을 복사
    strcpy(copy, str);
    
    // 복사본 반환
    return copy;
}