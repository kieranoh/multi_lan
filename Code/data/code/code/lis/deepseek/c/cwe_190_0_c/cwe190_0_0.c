#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* 주어진 오프셋을 기준으로, 양의 랜덤 숫자에 오프셋을 더한 정수 값을 stdout에 출력합니다. 문제가 발생하면 아무것도 출력하지 않습니다.

@param offset: 랜덤 숫자에 더할 오프셋 */
void print_rand_num_plus_offset(int offset) {
    /* 난수 생성기 초기화 */
    srand((unsigned int)time(NULL));
    
    /* 양의 랜덤 숫자 생성 (1부터 RAND_MAX 사이) */
    int random_num = rand();
    
    /* rand()가 음수를 반환할 수 있는지 확인 (표준에 따르면 0부터 RAND_MAX 사이의 음이 아닌 정수) */
    if (random_num < 0) {
        /* 문제 발생: 아무것도 출력하지 않음 */
        return;
    }
    
    /* 오프셋 더하기 */
    long long result = (long long)random_num + (long long)offset;
    
    /* 결과가 양의 정수인지 확인 (문제 조건에 따라) */
    if (result <= 0) {
        /* 결과가 양수가 아니면 아무것도 출력하지 않음 */
        return;
    }
    
    /* 결과 출력 */
    printf("%lld\n", result);
}