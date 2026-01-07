#include <stdio.h>
#include <string.h>

void trim_spaces(char* str) {
    if (str == NULL) return;

    size_t len = strlen(str);
    
    // 오른쪽에서부터 공백을 찾습니다.
    while (len > 0 && str[len - 1] == ' ') {
        len--;
    }
    
    // 문자열 끝을 Null 문자로 설정하여 공백을 제거합니다.
    str[len] = '\0';
}