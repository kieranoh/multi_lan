void set_values_in_arr(long long* values, int begin_index, int count) {
    if (values == NULL || begin_index < 0 || count <= 0) {
        return;
    }
    
    // 시작 위치를 계산하고 memset을 사용하여 메모리 블록을 0으로 설정
    memset(values + begin_index, 0, count * sizeof(long long));
}