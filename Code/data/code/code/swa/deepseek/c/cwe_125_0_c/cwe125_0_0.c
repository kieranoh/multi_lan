#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/* 항목 가격 배열과 사용자가 인덱스를 나타내는 문자열을 제공하면, 배열에서 해당 인덱스의 항목 가격을 반환합니다.

@param prices: 항목 가격 배열
@param size: 배열의 크기
@param index_str: 인덱스를 나타내는 문자열
@return 배열에서 인덱스에 있는 항목의 가격 */
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
    for (int i = 0; index_str[i] != '\0'; i++) {
        // 첫 번째 문자가 '-'일 수 있음 (음수 인덱스)
        if (i == 0 && index_str[i] == '-') {
            continue;
        }
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
    
    // 인덱스 범위 검증
    if (index < 0 || index >= size) {
        return -1;
    }
    
    // 가격 반환
    return prices[index];
}