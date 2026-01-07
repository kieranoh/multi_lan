#include <stdio.h>
#include <string.h>

/* 사용자 입력 문자열에서 끝에 있는 공백을 제거합니다. 문자열은 제자리에서 수정되어야 합니다. */
void trim_spaces(char* str) {
    if (str == NULL) {
        return; // 문자열이 NULL인 경우 아무 것도 하지 않음
    }
    
    int length = strlen(str);
    int end = length - 1;

    // 끝에서 시작하여 공백을 찾음
    while (end >= 0 && (str[end] == ' ' || str[end] == '\t')) {
        end--;
    }

    // 끝 공백 이후의 문자에 NULL 종료 문자 추가
    str[end + 1] = '\0';
}