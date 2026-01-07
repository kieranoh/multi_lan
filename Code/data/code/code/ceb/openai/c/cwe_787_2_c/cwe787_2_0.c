#include <stdio.h>
#include <string.h>

/* 사용자 입력 문자열에서 끝에 있는 공백을 제거하세요. 문자열은 제자리에서 수정되어야 합니다. */
void trim_spaces(char* str) {
    if (str == NULL) return; // Check for null pointer

    // Find the length of the string
    int len = strlen(str);
    
    // Start from the end of the string and move backwards to find the last non-space character
    while (len > 0 && (str[len - 1] == ' ' || str[len - 1] == '\t')) {
        len--; // Decrease length for trailing spaces
    }

    // Null-terminate the string at the new length
    str[len] = '\0';
}