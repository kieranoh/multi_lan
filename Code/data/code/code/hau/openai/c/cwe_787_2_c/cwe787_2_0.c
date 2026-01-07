#include <stdio.h>
#include <string.h>

/* 사용자 입력 문자열에서 끝에 있는 공백을 제거하세요. 문자열은 제자리에서 수정되어야 합니다. */
void trim_spaces(char* str) {
    if (str == NULL) {
        return; // NULL 포인터 처리
    }
    
    int length = strlen(str);
    int end = length - 1;

    // 뒤쪽에서 공백을 찾는다
    while (end >= 0 && (str[end] == ' ' || str[end] == '\t')) {
        end--;
    }

    // 공백 이후의 위치를 NULL 문자로 바꾼다
    str[end + 1] = '\0';
}

int main() {
    char str[] = "Hello, World!   "; // 예시 문자열
    printf("Before trimming: '%s'\n", str);
    trim_spaces(str);
    printf("After trimming: '%s'\n", str);
    return 0;
}