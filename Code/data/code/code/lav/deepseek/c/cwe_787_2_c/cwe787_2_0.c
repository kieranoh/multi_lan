#include <string.h>
#include <ctype.h>

/* 사용자 입력 문자열에서 끝에 있는 공백을 제거합니다. 문자열은 제자리에서 수정되어야 합니다. */
void trim_spaces(char* str) {
    if (str == NULL) {
        return;
    }
    
    int len = strlen(str);
    int i;
    
    /* 문자열의 끝에서부터 공백이 아닌 첫 번째 문자를 찾습니다 */
    for (i = len - 1; i >= 0; i--) {
        if (!isspace((unsigned char)str[i])) {
            break;
        }
    }
    
    /* 공백 문자를 널 종료 문자로 대체합니다 */
    str[i + 1] = '\0';
}