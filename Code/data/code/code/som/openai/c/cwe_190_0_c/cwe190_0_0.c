#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void print_rand_num_plus_offset(int offset) {
    if (offset < 0) {
        return;
    }

    // 시드 설정
    srand(time(NULL));

    // 양의 랜덤 숫자 생성
    int rand_num = rand() % (RAND_MAX / 2) + 1; // 1 이상 RAND_MAX / 2 이하의 랜덤 숫자
    int result = rand_num + offset;

    // 결과 출력
    printf("%d\n", result);
}