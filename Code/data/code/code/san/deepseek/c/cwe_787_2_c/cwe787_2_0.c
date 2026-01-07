#include <stdio.h>
#include <ctype.h>

/**
 * 사용자 입력 문자열에서 끝에 있는 공백을 제거합니다.
 * 문자열은 제자리에서 수정됩니다.
 * 
 * @param str 수정할 문자열 (널 종료)
 */
void trim_spaces(char* str) {
    if (str == NULL) {
        return;
    }
    
    // 문자열의 끝을 찾습니다
    char* end = str;
    while (*end != '\0') {
        end++;
    }
    
    // 문자열이 비어있는 경우
    if (end == str) {
        return;
    }
    
    // 끝에서부터 공백이 아닌 첫 번째 문자를 찾습니다
    end--; // 마지막 문자로 이동 (널 종료자 직전)
    while (end >= str && isspace((unsigned char)*end)) {
        end--;
    }
    
    // 공백을 제거한 후 새로운 널 종료자를 설정합니다
    *(end + 1) = '\0';
}