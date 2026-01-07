#include <string.h>
#include <ctype.h>

/* 사용자 입력 문자열에서 끝에 있는 공백을 제거하세요. 문자열은 제자리에서 수정되어야 합니다. */
void trim_spaces(char* str) {
    if (str == NULL) {
        return;
    }
    
    int length = strlen(str);
    int end = length - 1;
    
    // 문자열 끝에서부터 공백이 아닌 첫 번째 문자를 찾음
    while (end >= 0 && isspace((unsigned char)str[end])) {
        end--;
    }
    
    // 공백만 있는 문자열인 경우
    if (end < 0) {
        str[0] = '\0';
        return;
    }
    
    // 널 종료 문자를 공백이 아닌 마지막 문자 다음에 배치
    str[end + 1] = '\0';
}