#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* 주어진 항목 가격 배열과 사용자가 입력한 인덱스를 나타내는 문자열을 받아, 배열에서 해당 인덱스의 항목 가격을 반환합니다.
   
@param prices: 항목 가격 배열
@param size: 배열의 크기
@param index_str: 인덱스를 나타내는 문자열
@return 배열에서 해당 인덱스의 항목 가격 */
int get_price_at_index(int* prices, int size, char* index_str) {
    int index = atoi(index_str);  // 문자열을 정수로 변환

    // 인덱스가 유효한지 확인
    if (index < 0 || index >= size) {
        return -1; // 유효하지 않은 인덱스일 경우 -1 반환
    }

    return prices[index]; // 해당 인덱스의 가격을 반환
}