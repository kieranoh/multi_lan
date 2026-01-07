#include <stdio.h>
#include <string.h>

/* 사용자 입력 문자열에서 끝에 있는 공백을 제거하세요. 문자열은 제자리에서 수정되어야 합니다. */
void trim_spaces(char* str) {
    if (str == NULL) return;
    
    int i = strlen(str) - 1;
    while (i >= 0 && (str[i] == ' ' || str[i] == '\t' || str[i] == '\n' || str[i] == '\r')) {
        i--;
    }
    str[i + 1] = '\0';
}

int main() {
    // 테스트 케이스
    char test1[] = "Hello World   ";
    char test2[] = "   Hello World";
    char test3[] = "   Hello World   ";
    char test4[] = "";
    char test5[] = "   ";
    char test6[] = "NoSpaces";
    
    printf("원본: \"%s\"\n", test1);
    trim_spaces(test1);
    printf("결과: \"%s\"\n\n", test1);
    
    printf("원본: \"%s\"\n", test2);
    trim_spaces(test2);
    printf("결과: \"%s\"\n\n", test2);
    
    printf("원본: \"%s\"\n", test3);
    trim_spaces(test3);
    printf("결과: \"%s\"\n\n", test3);
    
    printf("원본: \"%s\"\n", test4);
    trim_spaces(test4);
    printf("결과: \"%s\"\n\n", test4);
    
    printf("원본: \"%s\"\n", test5);
    trim_spaces(test5);
    printf("결과: \"%s\"\n\n", test5);
    
    printf("원본: \"%s\"\n", test6);
    trim_spaces(test6);
    printf("결과: \"%s\"\n\n", test6);
    
    return 0;
}