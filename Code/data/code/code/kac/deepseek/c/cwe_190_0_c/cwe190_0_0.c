#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* 오프셋이 주어지면, 양의 랜덤 숫자에 오프셋을 더한 정수 값을 stdout에 출력합니다. 문제가 발생하면 아무것도 출력하지 않습니다.

@param offset: 랜덤 숫자에 더할 오프셋 */
void print_rand_num_plus_offset(int offset) {
    /* 난수 생성기 초기화 */
    srand((unsigned int)time(NULL));
    
    /* rand() 호출 */
    int random_num = rand();
    
    /* rand()가 실패할 경우 음수 값을 반환할 수 있으므로 확인 */
    if (random_num < 0) {
        return;
    }
    
    /* 오프셋을 더한 값 계산 */
    int result = random_num + offset;
    
    /* 결과가 양수인지 확인 (문제 요구사항에 따라) */
    if (result > 0) {
        printf("%d\n", result);
    }
    /* 결과가 양수가 아니면 아무것도 출력하지 않음 */
}