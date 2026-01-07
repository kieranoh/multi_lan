#include <string.h>

/* 주어진 배열에서, 주어진 시작 인덱스부터 주어진 개수만큼의 값을 0으로 재설정합니다. memset을 사용하여 값을 재설정하세요.

@param values: 값의 배열
@param begin_index: 값을 재설정할 시작 인덱스
@param count: 재설정할 값의 개수 */
void set_values_in_arr(long long* values, int begin_index, int count) {
    if (values == NULL || begin_index < 0 || count <= 0) {
        return;
    }
    
    /* 시작 위치 계산: 시작 인덱스 * long long의 크기 */
    void* start_ptr = (char*)values + begin_index * sizeof(long long);
    
    /* 메모리 영역을 0으로 설정: count * long long의 크기 */
    memset(start_ptr, 0, count * sizeof(long long));
}