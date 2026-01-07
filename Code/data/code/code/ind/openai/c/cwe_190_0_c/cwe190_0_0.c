#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void print_rand_num_plus_offset(int offset) {
    if (offset < 0) {
        return; // offset이 음수인 경우 아무 것도 출력하지 않음
    }

    // 랜덤 숫자를 생성하기 위해 시드 설정
    srand(time(NULL));

    // 양의 랜덤 숫자 생성
    int rand_num = rand() % RAND_MAX; // RAND_MAX는 rand()가 반환할 수 있는 최대값
    int result = rand_num + offset;

    // 결과 출력
    printf("%d\n", result);
}