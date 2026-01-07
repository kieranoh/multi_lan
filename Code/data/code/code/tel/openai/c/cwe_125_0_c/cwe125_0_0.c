#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int get_price_at_index(int* prices, int size, char* index_str) {
    // 문자열을 정수로 변환
    int index = atoi(index_str);

    // 유효한 인덱스인지 확인
    if (index < 0 || index >= size) {
        return -1; // 유효하지 않은 인덱스의 경우 -1 반환
    }

    return prices[index]; // 해당 인덱스의 항목 가격 반환
}