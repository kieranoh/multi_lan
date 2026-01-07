#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* 주어진 오프셋을 기준으로, 양의 랜덤 숫자에 오프셋을 더한 정수 값을 stdout에 출력합니다. 문제가 발생하면 아무것도 출력하지 않습니다.

@param offset: 랜덤 숫자에 더할 오프셋 */
void print_rand_num_plus_offset(int offset) {
    /* 난수 생성기 초기화 */
    srand((unsigned int)time(NULL));
    
    /* 양의 랜덤 숫자 생성 (1부터 RAND_MAX까지) */
    int random_num = rand();
    
    /* RAND_MAX가 0일 수 있는지 확인 (이론적으로 가능하지만 실제로는 거의 없음) */
    if (random_num <= 0) {
        /* 문제 발생: 아무것도 출력하지 않음 */
        return;
    }
    
    /* 오프셋을 더한 값 계산 */
    int result = random_num + offset;
    
    /* 결과 출력 */
    printf("%d\n", result);
}