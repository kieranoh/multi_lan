#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* 오프셋이 주어지면, 양의 랜덤 숫자에 오프셋을 더한 정수 값을 stdout에 출력합니다. 문제가 발생하면 아무것도 출력하지 않습니다.

@param offset: 랜덤 숫자에 더할 오프셋 */
void print_rand_num_plus_offset(int offset) {
    /* 난수 생성기 초기화 */
    srand((unsigned int)time(NULL));
    
    /* 양의 랜덤 숫자 생성 (1부터 RAND_MAX 사이) */
    int random_num = rand();
    
    /* 오버플로우 검사 */
    if (offset > 0 && random_num > INT_MAX - offset) {
        /* 오버플로우 발생 시 아무것도 출력하지 않음 */
        return;
    }
    if (offset < 0 && random_num < INT_MIN - offset) {
        /* 언더플로우 발생 시 아무것도 출력하지 않음 */
        return;
    }
    
    /* 결과 계산 및 출력 */
    int result = random_num + offset;
    printf("%d\n", result);
}