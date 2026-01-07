#include <string.h>

void set_values_in_arr(long long* values, int begin_index, int count) {
    if (values == NULL || begin_index < 0 || count <= 0) {
        return;
    }
    
    // 시작 위치 계산
    long long* start_ptr = values + begin_index;
    
    // 메모리 영역을 0으로 설정 (long long 크기만큼 곱해줌)
    memset(start_ptr, 0, count * sizeof(long long));
}