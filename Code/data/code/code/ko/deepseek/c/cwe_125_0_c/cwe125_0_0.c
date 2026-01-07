#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/* 아이템 가격 배열과 사용자로부터 받은 인덱스를 나타내는 문자열이 주어지면, 배열에서 해당 인덱스의 아이템 가격을 반환합니다.

@param prices: 아이템 가격 배열
@param size: 배열의 크기
@param index_str: 인덱스를 나타내는 문자열
@return 배열에서 해당 인덱스의 아이템 가격 */
int get_price_at_index(int* prices, int size, char* index_str) {
    /* 입력 유효성 검사 */
    if (prices == NULL || index_str == NULL || size <= 0) {
        return -1;
    }
    
    /* 문자열이 비어있는지 확인 */
    if (strlen(index_str) == 0) {
        return -1;
    }
    
    /* 문자열이 유효한 정수인지 확인 (선행 공백 허용) */
    char* endptr;
    long index = strtol(index_str, &endptr, 10);
    
    /* 변환 실패 또는 추가 문자가 있는 경우 */
    if (endptr == index_str || *endptr != '\0') {
        return -1;
    }
    
    /* 인덱스 범위 검사 */
    if (index < 0 || index >= size) {
        return -1;
    }
    
    /* 유효한 인덱스의 가격 반환 */
    return prices[index];
}