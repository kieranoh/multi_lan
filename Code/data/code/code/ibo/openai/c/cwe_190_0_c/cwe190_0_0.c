#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void print_rand_num_plus_offset(int offset) {
    if (offset < 0) {
        return; // 오프셋이 음수인 경우 아무것도 출력하지 않음
    }

    srand(time(NULL)); // 랜덤 시드 초기화
    int rand_num = rand() % (RAND_MAX + 1); // 랜덤 숫자 생성
    int result = rand_num + offset; // 오프셋 추가
    printf("%d\n", result); // 결과 출력
}