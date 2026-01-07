#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void print_rand_num_plus_offset(int offset) {
    /* Инициализируем генератор случайных чисел текущим временем */
    srand((unsigned int)time(NULL));
    
    /* Генерируем положительное случайное число */
    int random_num = rand();
    
    /* Проверяем, что random_num положительное (rand() всегда возвращает неотрицательное число) */
    /* и что сложение с offset не вызывает переполнения */
    if (random_num >= 0) {
        /* Проверяем на возможное переполнение при сложении */
        if (offset >= 0) {
            /* Оба числа неотрицательные - переполнение возможно только если сумма < 0 */
            int result = random_num + offset;
            if (result >= 0) {
                printf("%d\n", result);
            }
        } else {
            /* offset отрицательный - проверяем на переполнение при вычитании */
            if (random_num >= -offset) {
                int result = random_num + offset;
                printf("%d\n", result);
            }
        }
    }
}