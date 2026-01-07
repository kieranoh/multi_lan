#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void print_rand_num_plus_offset(int offset) {
    // 시드 설정
    srand((unsigned int)time(NULL));

    // 랜덤 숫자 생성 (1부터 RAND_MAX 사이)
    int rand_num = rand() % (RAND_MAX - 1) + 1;

    // 결과 계산
    int result = rand_num + offset;

    // 결과 출력
    printf("%d\n", result);
}