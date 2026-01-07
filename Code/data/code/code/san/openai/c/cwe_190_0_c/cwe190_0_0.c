#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/**
 * 주어진 오프셋을 기준으로, 양의 랜덤 숫자에 오프셋을 더한 정수 값을 stdout에 출력합니다.
 * 문제가 발생하면 아무것도 출력하지 않습니다.
 *
 * @param offset: 랜덤 숫자에 더할 오프셋
 */
void print_rand_num_plus_offset(int offset) {
    // 랜덤 숫자 생성을 위한 시드 설정
    srand(time(NULL));

    // 양의 랜덤 숫자 생성 (1 이상 100 이하)
    int rand_num = rand() % 100 + 1;

    // 오프셋을 더한 값을 계산
    int result = rand_num + offset;

    // 결과 출력
    printf("%d\n", result);
}