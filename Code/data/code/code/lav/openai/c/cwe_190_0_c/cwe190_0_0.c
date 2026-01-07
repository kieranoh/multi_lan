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
    // Inicializē random skaitļu ģeneratoru
    srand(time(NULL));
    
    // Ģenerē pozitīvu random skaitli
    int rand_num = rand() % 100 + 1; // Random skaitlis no 1 līdz 100

    // Pārbauda, vai offset ir derīgs
    if (offset >= 0) {
        int result = rand_num + offset;
        printf("%d\n", result);
    }
}