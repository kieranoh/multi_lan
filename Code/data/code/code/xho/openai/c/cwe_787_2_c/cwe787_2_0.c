#include <stdio.h>
#include <string.h>

/* 사용자 입력 문자열에서 끝에 있는 공백을 제거하세요. 문자열은 제자리에서 수정되어야 합니다. */
void trim_spaces(char* str) {
    if (str == NULL) return; // 문자열이 NULL인지 확인

    int len = strlen(str);
    int end = len - 1;

    // 문자열 끝에서부터 공백을 찾음
    while (end >= 0 && str[end] == ' ') {
        end--;
    }

    // 공백 다음의 마지막 문자 다음에 널 문자 추가
    str[end + 1] = '\0';
}

int main() {
    char str[] = "Hello, World!    "; // 예시 문자열
    printf("Before trim: '%s'\n", str);
    trim_spaces(str);
    printf("After trim: '%s'\n", str);
    return 0;
}