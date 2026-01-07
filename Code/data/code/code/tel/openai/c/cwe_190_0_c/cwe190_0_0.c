#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void print_rand_num_plus_offset(int offset) {
    if (offset < 0) {
        return; // 문제가 발생할 경우 아무 것도 출력하지 않음
    }
    
    // 랜덤 숫자 생성을 위한 시드 초기화
    srand(time(NULL));
    
    // 양의 랜덤 숫자 생성
    int rand_num = rand() % 100 + 1; // 1부터 100 사이의 랜덤 숫자
    
    // 오프셋을 랜덤 숫자에 더하여 출력
    printf("%d\n", rand_num + offset);
}