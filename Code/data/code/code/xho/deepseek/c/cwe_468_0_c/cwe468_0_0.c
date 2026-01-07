/* 주어진 배열에서, 주어진 시작 인덱스부터 주어진 개수만큼의 값을 0으로 재설정합니다. memset을 사용하여 값을 재설정하세요.

@param values: 값의 배열
@param begin_index: 값을 재설정할 시작 인덱스
@param count: 재설정할 값의 개수 */
void set_values_in_arr(long long* values, int begin_index, int count) {
    // 시작 인덱스가 음수이거나 count가 0 이하인 경우 아무 작업도 하지 않음
    if (begin_index < 0 || count <= 0) {
        return;
    }
    
    // memset을 사용하여 시작 위치부터 count 개수만큼의 long long 요소를 0으로 설정
    // 각 요소의 크기는 sizeof(long long)이므로, 총 바이트 수는 count * sizeof(long long)
    // 시작 주소는 values 배열의 begin_index 위치
    memset(values + begin_index, 0, count * sizeof(long long));
}