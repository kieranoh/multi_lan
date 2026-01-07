#include <string.h>
#include <ctype.h>

/* 사용자 입력 문자열에서 후행 공백을 제거합니다. 문자열은 제자리에서 수정되어야 합니다. */
void trim_spaces(char* str) {
    if (str == NULL) {
        return;
    }
    
    int length = strlen(str);
    int i = length - 1;
    
    /* 문자열 끝에서부터 공백이 아닌 문자를 찾을 때까지 이동 */
    while (i >= 0 && isspace((unsigned char)str[i])) {
        i--;
    }
    
    /* 공백 문자를 널 종료 문자로 대체 */
    str[i + 1] = '\0';
}