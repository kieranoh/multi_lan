#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/* 항목 가격 배열과 사용자가 인덱스를 나타내는 문자열을 제공하면, 배열에서 해당 인덱스의 항목 가격을 반환합니다.

@param prices: 항목 가격 배열
@param size: 배열의 크기
@param index_str: 인덱스를 나타내는 문자열
@return 배열에서 해당 인덱스의 항목 가격 */
int get_price_at_index(int* prices, int size, char* index_str) {
    // 입력 검사: NULL 포인터 확인
    if (prices == NULL || index_str == NULL) {
        return -1;  // 오류 표시
    }
    
    // 빈 문자열 확인
    if (strlen(index_str) == 0) {
        return -1;
    }
    
    // 문자열이 숫자로만 구성되어 있는지 확인
    for (int i = 0; index_str[i] != '\0'; i++) {
        if (!isdigit(index_str[i])) {
            return -1;  // 숫자가 아닌 문자가 포함된 경우
        }
    }
    
    // 문자열을 정수로 변환
    char* endptr;
    long index = strtol(index_str, &endptr, 10);
    
    // 변환 실패 확인
    if (endptr == index_str || *endptr != '\0') {
        return -1;
    }
    
    // 인덱스 범위 확인
    if (index < 0 || index >= size) {
        return -1;  // 인덱스가 범위를 벗어난 경우
    }
    
    // 해당 인덱스의 가격 반환
    return prices[index];
}

// 사용 예시
int main() {
    int prices[] = {100, 200, 300, 400, 500};
    int size = 5;
    
    // 테스트 케이스
    printf("인덱스 '2'의 가격: %d\n", get_price_at_index(prices, size, "2"));  // 300
    printf("인덱스 '0'의 가격: %d\n", get_price_at_index(prices, size, "0"));  // 100
    printf("인덱스 '4'의 가격: %d\n", get_price_at_index(prices, size, "4"));  // 500
    
    // 오류 케이스
    printf("인덱스 '5'의 가격: %d\n", get_price_at_index(prices, size, "5"));  // -1 (범위 초과)
    printf("인덱스 '-1'의 가격: %d\n", get_price_at_index(prices, size, "-1")); // -1 (음수)
    printf("인덱스 'abc'의 가격: %d\n", get_price_at_index(prices, size, "abc")); // -1 (숫자 아님)
    printf("NULL 문자열의 가격: %d\n", get_price_at_index(prices, size, "")); // -1 (빈 문자열)
    
    return 0;
}