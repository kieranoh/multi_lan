#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void print_rand_num_plus_offset(int offset) {
    if (offset < 0) {
        return; // 문제 발생 시 아무것도 출력하지 않음
    }
    
    // 랜덤 숫자 초기화
    srand(time(NULL));
    
    // 양의 랜덤 숫자 생성
    int rand_num = rand() % 100; // 0에서 99 사이의 숫자 생성
    int result = rand_num + offset;
    
    // 결과 출력
    printf("%d\n", result);
}