#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void print_rand_num_plus_offset(int offset) {
    if (offset < 0) {
        return; // 오프셋이 음수인 경우 아무것도 출력하지 않음
    }
    
    // 랜덤 숫자 생성을 위한 시드 설정
    srand(time(NULL));
    
    // 1부터 RAND_MAX까지의 랜덤 숫자 생성
    int rand_num = rand() + 1; // 0이 아닌 양의 랜덤 숫자
    int result = rand_num + offset;
    
    // 결과 출력
    printf("%d\n", result);
}