#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int get_price_at_index(int* prices, int size, char* index_str) {
    // 입력 검증
    if (prices == NULL || index_str == NULL || size <= 0) {
        return -1;
    }
    
    // 빈 문자열 검사
    if (strlen(index_str) == 0) {
        return -1;
    }
    
    // 문자열이 숫자로만 구성되어 있는지 확인
    for (int i = 0; index_str[i] != '\0'; i++) {
        if (!isdigit(index_str[i])) {
            return -1;
        }
    }
    
    // 문자열을 정수로 변환
    char* endptr;
    long index = strtol(index_str, &endptr, 10);
    
    // 변환 실패 확인
    if (endptr == index_str || *endptr != '\0') {
        return -1;
    }
    
    // 인덱스 범위 검사
    if (index < 0 || index >= size) {
        return -1;
    }
    
    // 가격 반환
    return prices[index];
}