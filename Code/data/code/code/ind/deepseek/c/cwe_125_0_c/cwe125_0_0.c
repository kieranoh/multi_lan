#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int get_price_at_index(int* prices, int size, char* index_str) {
    if (prices == NULL || index_str == NULL || size <= 0) {
        return -1;
    }

    /* 문자열이 유효한 정수인지 확인 */
    for (int i = 0; index_str[i] != '\0'; i++) {
        if (i == 0 && index_str[i] == '-') {
            continue; /* 음수 인덱스 허용 */
        }
        if (!isdigit((unsigned char)index_str[i])) {
            return -1;
        }
    }

    /* 문자열을 정수로 변환 */
    char *endptr;
    long index = strtol(index_str, &endptr, 10);
    
    /* 변환 실패 또는 추가 문자가 있는지 확인 */
    if (endptr == index_str || *endptr != '\0') {
        return -1;
    }

    /* 인덱스가 배열 범위 내에 있는지 확인 */
    if (index < 0 || index >= size) {
        return -1;
    }

    return prices[index];
}