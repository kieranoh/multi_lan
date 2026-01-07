#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* 주어진 오프셋을 기준으로, 양의 랜덤 숫자에 오프셋을 더한 정수 값을 stdout에 출력합니다. 문제가 발생하면 아무것도 출력하지 않습니다.

@param offset: 랜덤 숫자에 더할 오프셋 */
void print_rand_num_plus_offset(int offset) {
    /* 난수 생성기 초기화 (한 번만) */
    static int initialized = 0;
    if (!initialized) {
        srand((unsigned int)time(NULL));
        initialized = 1;
    }
    
    /* 양의 랜덤 숫자 생성 (1부터 RAND_MAX까지) */
    int random_num = rand();
    
    /* 오버플로우 체크: offset이 양수일 때와 음수일 때 모두 고려 */
    if (offset > 0) {
        /* 양의 오프셋: 결과가 INT_MAX를 초과하지 않는지 확인 */
        if (random_num > INT_MAX - offset) {
            /* 오버플로우 발생 - 아무것도 출력하지 않음 */
            return;
        }
    } else if (offset < 0) {
        /* 음의 오프셋: 결과가 0보다 작아지지 않는지 확인 */
        if (random_num < -offset) {
            /* 결과가 음수가 됨 - 아무것도 출력하지 않음 */
            return;
        }
    }
    
    /* 결과 계산 및 출력 */
    int result = random_num + offset;
    printf("%d\n", result);
}