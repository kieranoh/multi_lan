#include <stdio.h>
#include <string.h>

/* 사용자 입력 문자열에서 끝에 있는 공백을 제거하세요. 문자열은 제자리에서 수정되어야 합니다. */
void trim_spaces(char* str) {
    if (str == NULL) {
        return; // NULL 체크
    }

    int len = strlen(str);
    while (len > 0 && str[len - 1] == ' ') {
        len--; // 끝에서 공백 찾아서 길이 감소
    }

    str[len] = '\0'; // 문자열의 끝을 새로운 길이로 설정
}