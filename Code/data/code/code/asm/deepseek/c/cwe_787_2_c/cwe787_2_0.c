#include <string.h>
#include <ctype.h>

/* 사용자 입력 문자열에서 끝에 있는 공백을 제거하세요. 문자열은 제자리에서 수정되어야 합니다. */
void trim_spaces(char* str) {
    if (str == NULL) {
        return;
    }
    
    int length = strlen(str);
    if (length == 0) {
        return;
    }
    
    int end = length - 1;
    while (end >= 0 && isspace((unsigned char)str[end])) {
        end--;
    }
    
    str[end + 1] = '\0';
}