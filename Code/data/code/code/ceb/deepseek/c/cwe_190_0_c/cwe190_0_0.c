#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* 주어진 오프셋을 기준으로, 양의 랜덤 숫자에 오프셋을 더한 정수 값을 stdout에 출력합니다. 문제가 발생하면 아무것도 출력하지 않습니다.

@param offset: 랜덤 숫자에 더할 오프셋 */
void print_rand_num_plus_offset(int offset) {
    /* 난수 생성기 초기화 */
    srand((unsigned int)time(NULL));
    
    /* 1부터 1000 사이의 양의 난수 생성 */
    int random_num = rand() % 1000 + 1;
    
    /* 결과 계산 */
    int result = random_num + offset;
    
    /* 결과가 양수인지 확인 (문제 발생 시 출력하지 않음) */
    if (result > 0) {
        printf("%d\n", result);
    }
    /* 결과가 0 이하인 경우 문제가 발생한 것으로 간주하여 아무것도 출력하지 않음 */
}