#include <stdio.h>
#include <string.h>

/* 사용자 입력 문자열에서 끝에 있는 공백을 제거합니다. 문자열은 제자리에서 수정되어야 합니다. */
void trim_spaces(char* str) {
    if (str == NULL) return; // Null check

    size_t len = strlen(str);
    while (len > 0 && str[len - 1] == ' ') {
        str[len - 1] = '\0'; // Replace space with null terminator
        len--; // Decrease the length
    }
}