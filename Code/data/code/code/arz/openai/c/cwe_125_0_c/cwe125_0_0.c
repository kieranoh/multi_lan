#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* 항목 가격 배열과 사용자가 인덱스를 나타내는 문자열을 제공하면, 배열에서 해당 인덱스의 항목 가격을 반환합니다.
@param prices: 항목 가격 배열
@param size: 배열의 크기
@param index_str: 인덱스를 나타내는 문자열
@return 배열에서 인덱스에 있는 항목의 가격 */
int get_price_at_index(int* prices, int size, char* index_str) {
    // 문자열을 정수로 변환
    int index = atoi(index_str);
    
    // 인덱스가 배열의 범위 내에 있는지 확인
    if (index >= 0 && index < size) {
        return prices[index];
    } else {
        // 인덱스가 범위를 벗어났다면 -1 반환 (또는 적절한 오류 코드)
        return -1; 
    }
}