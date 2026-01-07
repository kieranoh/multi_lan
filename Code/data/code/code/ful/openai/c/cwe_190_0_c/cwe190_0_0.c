#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* 주어진 오프셋을 기준으로, 양의 랜덤 숫자에 오프셋을 더한 정수 값을 stdout에 출력합니다. 문제가 발생하면 아무것도 출력하지 않습니다.

@param offset: 랜덤 숫자에 더할 오프셋 */
void print_rand_num_plus_offset(int offset) {
    if (offset < 0) {
        return; // Offset should be non-negative
    }

    // Seed the random number generator
    srand(time(NULL));
    
    // Generate a random number between 1 and RAND_MAX
    int rand_num = rand() % (RAND_MAX - 1) + 1;

    // Calculate the result by adding the offset
    int result = rand_num + offset;

    // Print the result
    printf("%d\n", result);
}