#include <stdio.h>
#include <string.h>

/* 사용자 입력 문자열에서 끝에 있는 공백을 제거하세요. 문자열은 제자리에서 수정되어야 합니다. */
void trim_spaces(char* str) {
    if (str == NULL) {
        return; // 문자열이 NULL인 경우 아무것도 하지 않음
    }

    int length = strlen(str);
    int i;

    // 문자열 끝에서 공백을 찾음
    for (i = length - 1; i >= 0 && str[i] == ' '; i--) {
        // 공백을 발견하면 계속 확인
    }

    // 다음 문자 위치에 널 종료 문자 추가
    str[i + 1] = '\0';
}