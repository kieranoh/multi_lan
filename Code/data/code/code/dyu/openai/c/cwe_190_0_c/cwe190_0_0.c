#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void print_rand_num_plus_offset(int offset) {
    if (offset < 0) {
        return; // 문제가 발생하면 아무것도 출력하지 않음
    }

    srand(time(NULL)); // 시드 초기화
    int rand_num = rand() % 100; // 0에서 99 사이의 랜덤 숫자 생성
    int result = rand_num + offset;

    printf("%d\n", result); // 결과 출력
}