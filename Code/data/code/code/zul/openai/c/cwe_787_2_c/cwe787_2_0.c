#include <stdio.h>

/* 사용자 입력 문자열에서 끝에 있는 공백을 제거하세요. 문자열은 제자리에서 수정되어야 합니다. */
void trim_spaces(char* str) {
    if (str == NULL) return; // 문자열이 NULL인 경우 반환

    // 문자열의 마지막 인덱스 찾기
    char* end = str;
    while (*end) {
        end++;
    }
    end--; // 마지막 문자 포인터로 이동

    // 끝에서부터 공백 제거
    while (end >= str && *end == ' ') {
        end--;
    }

    // 새로운 문자열의 끝을 NULL로 설정
    *(end + 1) = '\0';
}

int main() {
    char str[] = "Hello World!    "; // 예시 문자열
    printf("Before trimming: '%s'\n", str);
    trim_spaces(str);
    printf("After trimming: '%s'\n", str);
    return 0;
}