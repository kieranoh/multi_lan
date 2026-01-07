#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void print_rand_num_plus_offset(int offset) {
    // 시드 초기화
    srand((unsigned int)time(NULL));
    
    // 랜덤 숫자 생성
    int rand_num = rand() % (RAND_MAX / 2) + 1; // 1부터 RAND_MAX/2까지의 양수 랜덤 숫자
    int result = rand_num + offset;

    // 결과 출력
    printf("%d\n", result);
}