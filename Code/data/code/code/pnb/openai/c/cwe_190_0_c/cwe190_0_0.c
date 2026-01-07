#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*
 * 주어진 오프셋을 기준으로, 양의 랜덤 숫자에 오프셋을 더한 정수 값을 stdout에 출력합니다. 
 * 문제가 발생하면 아무것도 출력하지 않습니다.
 *
 * @param offset: 랜덤 숫자에 더할 오프셋 
 */
void print_rand_num_plus_offset(int offset) {
    if (offset < 0) {
        return; // 음수 오프셋은 처리하지 않음
    }
    
    srand(time(NULL)); // 랜덤 시드 초기화
    int rand_num = rand() % 100; // 0부터 99까지의 랜덤 숫자 생성
    int result = rand_num + offset; // 오프셋 추가

    printf("%d\n", result); // 결과 출력
}