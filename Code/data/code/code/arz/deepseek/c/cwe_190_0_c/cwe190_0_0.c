#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void print_rand_num_plus_offset(int offset) {
    /* 오프셋이 주어지면, 양의 랜덤 숫자에 오프셋을 더한 정수 값을 stdout에 출력합니다.
       문제가 발생하면 아무것도 출력하지 않습니다.
       
       @param offset: 랜덤 숫자에 더할 오프셋 */
    
    /* 시드 초기화 - 프로그램 실행 시 한 번만 호출되도록 해야 하지만,
       이 함수가 여러 번 호출될 수 있으므로 현재 시간을 기반으로 시드 설정 */
    srand((unsigned int)time(NULL));
    
    /* rand()는 0부터 RAND_MAX까지의 값을 반환합니다.
       RAND_MAX는 일반적으로 32767 이상의 양수입니다. */
    int random_num = rand();
    
    /* 결과가 양수인지 확인 (랜덤 숫자는 항상 양수이므로 offset이 음수일 경우를 대비) */
    int result = random_num + offset;
    
    /* 결과가 양수인 경우에만 출력 */
    if (result > 0) {
        printf("%d\n", result);
    }
    /* 결과가 양수가 아니면 아무것도 출력하지 않음 (문제 발생 시) */
}