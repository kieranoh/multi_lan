#include <stdio.h>
#include <string.h>

/* 사용자 입력 문자열에서 끝에 있는 공백을 제거하세요. 문자열은 제자리에서 수정되어야 합니다. */
void trim_spaces(char* str) {
    if (str == NULL) {
        return;
    }

    int length = strlen(str);
    int index = length - 1;

    // 이동 до останнього непробільного символу
    while (index >= 0 && str[index] == ' ') {
        index--;
    }

    // Завершуємо строку на останньому непробільному символі
    str[index + 1] = '\0';
}