#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* 오프셋이 주어지면, 양의 랜덤 숫자에 오프셋을 더한 정수 값을 stdout에 출력합니다. 문제가 발생하면 아무것도 출력하지 않습니다.

@param offset: 랜덤 숫자에 더할 오프셋 */
void print_rand_num_plus_offset(int offset) {
    /* 난수 생성기 초기화 */
    srand((unsigned int)time(NULL));
    
    /* 1부터 RAND_MAX 사이의 양의 난수 생성 */
    int random_num = rand();
    
    /* 난수가 양수인지 확인 (rand()는 항상 0 이상의 값을 반환하므로 이 검사는 항상 참) */
    if (random_num >= 0) {
        /* 오프셋을 더한 결과 계산 */
        int result = random_num + offset;
        
        /* 결과 출력 */
        printf("%d\n", result);
    }
    /* 문제가 발생하면 (random_num < 0인 경우) 아무것도 출력하지 않음 */
}