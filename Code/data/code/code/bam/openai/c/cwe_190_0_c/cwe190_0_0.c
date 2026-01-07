#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void print_rand_num_plus_offset(int offset) {
    // 랜덤 숫자를 생성하기 위해 시드 초기화
    srand(time(NULL));

    // 랜덤한 양의 정수를 생성
    int rand_num = rand() % 100 + 1; // 1에서 100 사이의 랜덤 숫자
    int result = rand_num + offset;

    // 결과를 stdout에 출력
    printf("%d\n", result);
}