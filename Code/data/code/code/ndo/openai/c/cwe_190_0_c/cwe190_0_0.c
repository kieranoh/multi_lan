#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void print_rand_num_plus_offset(int offset) {
    if (offset < 0) {
        return; // 오프셋이 음수인 경우 아무것도 출력하지 않음
    }

    // 랜덤 숫자 생성을 위한 시드 초기화
    srand(time(NULL));
    
    // 양의 랜덤 숫자 생성
    int rand_num = rand() % (RAND_MAX / 2); // RAND_MAX의 절반 이하의 랜덤 수
    int result = rand_num + offset;

    // 결과 출력
    printf("%d\n", result);
}