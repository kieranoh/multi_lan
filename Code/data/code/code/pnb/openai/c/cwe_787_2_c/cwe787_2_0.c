#include <stdio.h>
#include <string.h>

/* 사용자 입력 문자열에서 끝에 있는 공백을 제거하세요. 문자열은 제자리에서 수정되어야 합니다. */
void trim_spaces(char* str) {
    if (str == NULL) {
        return;
    }

    int len = strlen(str);
    int i;

    // Start from the end of the string and move backwards to find the last non-space character
    for (i = len - 1; i >= 0; i--) {
        if (str[i] != ' ') {
            break;
        }
    }

    // Null terminate the string after the last non-space character
    str[i + 1] = '\0';
}