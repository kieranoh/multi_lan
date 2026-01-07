#include <string.h>

/**
 * 주어진 배열에서, 주어진 시작 인덱스부터 주어진 개수만큼의 값을 0으로 재설정합니다.
 * memset을 사용하여 값을 재설정하세요.
 * 
 * @param values: 값의 배열
 * @param begin_index: 값을 재설정할 시작 인덱스
 * @param count: 재설정할 값의 개수
 */
void set_values_in_arr(long long* values, int begin_index, int count) {
    // 유효성 검사: 배열 포인터가 NULL이거나, count가 0 이하이거나, 
    // 시작 인덱스가 음수인 경우 아무 작업도 수행하지 않음
    if (values == NULL || count <= 0 || begin_index < 0) {
        return;
    }
    
    // 시작 위치 계산: 배열의 시작 주소 + 시작 인덱스 * 요소 크기
    // long long 타입의 크기를 고려하여 바이트 단위로 오프셋 계산
    void* start_ptr = (char*)values + begin_index * sizeof(long long);
    
    // memset을 사용하여 count 개수만큼의 long long 요소를 0으로 설정
    // 총 바이트 수 = 요소 개수 * 요소 크기
    memset(start_ptr, 0, count * sizeof(long long));
}