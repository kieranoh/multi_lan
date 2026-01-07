#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* 오프셋이 주어지면, 양의 랜덤 숫자에 오프셋을 더한 정수 값을 stdout에 출력합니다. 문제가 발생하면 아무것도 출력하지 않습니다.
@param offset: 랜덤 숫자에 더할 오프셋 */
void print_rand_num_plus_offset(int offset) {
    if (offset < 0) {
        return; // Якщо офсет від'ємний, нічого не виводимо
    }
    
    // Ініціалізуємо генератор випадкових чисел
    srand(time(NULL));
    
    // Генеруємо позитивне випадкове число
    int random_number = rand() % (RAND_MAX / 2) + 1; // Додаємо 1 для забезпечення позитивності
    int result = random_number + offset;
    
    // Виводимо результат
    printf("%d\n", result);
}