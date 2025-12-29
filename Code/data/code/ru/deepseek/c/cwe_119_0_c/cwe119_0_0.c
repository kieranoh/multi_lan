#include <string.h>

void copy_to_dest(char* dest, int dest_size, char* src, int src_size) {
    if (dest == NULL || src == NULL || dest_size <= 0) {
        return;
    }
    
    // Определяем количество символов для копирования
    // Берем минимум из dest_size-1 (для нуль-терминатора) и src_size
    int copy_size = (dest_size - 1) < src_size ? (dest_size - 1) : src_size;
    
    // Копируем данные с помощью strncpy
    strncpy(dest, src, copy_size);
    
    // Гарантируем нуль-терминацию строки
    dest[copy_size] = '\0';
}