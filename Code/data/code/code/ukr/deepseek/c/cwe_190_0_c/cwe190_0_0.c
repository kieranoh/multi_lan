#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void print_rand_num_plus_offset(int offset) {
    // 난수 생성기 초기화 (한 번만)
    static int initialized = 0;
    if (!initialized) {
        srand(time(NULL));
        initialized = 1;
    }
    
    // 양의 난수 생성 (1부터 RAND_MAX까지)
    int random_num = rand() % RAND_MAX + 1;
    
    // 오프셋을 더한 값 계산
    int result = random_num + offset;
    
    // 결과 출력
    printf("%d\n", result);
}