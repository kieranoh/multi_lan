#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void print_rand_num_plus_offset(int offset) {
    if (offset < 0) {
        return; // offset이 음수인 경우 아무것도 출력하지 않음
    }

    // 랜덤 숫자 생성
    srand(time(NULL)); // 시드 초기화
    int rand_num = rand() % 100; // 0에서 99 사이의 랜덤 숫자 생성

    // 오프셋을 더한 값 출력
    printf("%d\n", rand_num + offset);
}