#include <ctype.h>
#include <string.h>

/* 사용자 입력 문자열에서 끝에 있는 공백을 제거하세요. 문자열은 제자리에서 수정되어야 합니다. */
void trim_spaces(char* str) {
    if (str == NULL) {
        return;
    }
    
    int len = strlen(str);
    int i = len - 1;
    
    // 끝에서부터 공백 문자(스페이스, 탭, 개행 등)를 찾아 제거
    while (i >= 0 && isspace((unsigned char)str[i])) {
        i--;
    }
    
    // 널 종료 문자를 공백이 아닌 마지막 문자 다음 위치에 설정
    str[i + 1] = '\0';
}