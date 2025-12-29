#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

int get_price_at_index(int* prices, int size, char* index_str) {
    // Переменная для хранения индекса
    long index;
    
    // Преобразуем строку в число
    errno = 0; // Сбрасываем errno перед вызовом strtol
    char *endptr;
    index = strtol(index_str, &endptr, 10);
    
    // Проверяем на ошибки преобразования
    if (errno != 0 || *endptr != '\0' || endptr == index_str) {
        return -1; // Ошибка преобразования
    }
    
    // Проверяем, находится ли индекс в диапазоне
    if (index < 0 || index >= size) {
        return -1; // Индекс вне диапазона
    }
    
    // Возвращаем цену по индексу
    return prices[index];
}