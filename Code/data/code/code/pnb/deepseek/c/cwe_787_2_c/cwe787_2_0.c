#include <string.h>
#include <ctype.h>

/* 사용자 입력 문자열에서 끝에 있는 공백을 제거하세요. 문자열은 제자리에서 수정되어야 합니다. */
void trim_spaces(char* str) {
    if (str == NULL) {
        return;
    }
    
    int len = strlen(str);
    int end = len - 1;
    
    // 끝에서부터 공백이 아닌 문자를 찾음
    while (end >= 0 && isspace((unsigned char)str[end])) {
        end--;
    }
    
    // 널 종료 문자를 설정하여 문자열 종료
    str[end + 1] = '\0';
}