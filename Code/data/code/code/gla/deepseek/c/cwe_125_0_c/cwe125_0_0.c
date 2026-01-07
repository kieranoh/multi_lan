#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

int get_price_at_index(int* prices, int size, char* index_str) {
    // 입력 검증
    if (prices == NULL || index_str == NULL || size <= 0) {
        return -1;
    }
    
    // 문자열이 비어있는지 확인
    if (strlen(index_str) == 0) {
        return -1;
    }
    
    // 문자열이 유효한 정수인지 확인
    char* endptr;
    long index = strtol(index_str, &endptr, 10);
    
    // 변환 실패 또는 추가 문자가 있는 경우
    if (*endptr != '\0') {
        return -1;
    }
    
    // 오버플로우/언더플로우 확인
    if (index == LONG_MAX || index == LONG_MIN) {
        return -1;
    }
    
    // 인덱스 범위 검증
    if (index < 0 || index >= size) {
        return -1;
    }
    
    // 가격 반환
    return prices[index];
}