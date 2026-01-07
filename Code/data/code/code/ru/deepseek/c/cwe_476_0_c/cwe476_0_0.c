#include <stdlib.h>
#include <string.h>

char* allocate_buffer_and_write(size_t buf_size) {
    // Проверяем, что запрошенный размер достаточно велик для записи в первые и последние 10 байт
    if (buf_size < 20) {
        // Если размер меньше 20, выделяем минимальный буфер размером 20
        // чтобы можно было записать в первые и последние 10 байт
        buf_size = 20;
    }
    
    // Выделяем буфер запрошенного размера
    char* buffer = (char*)malloc(buf_size);
    if (buffer == NULL) {
        return NULL; // Возвращаем NULL в случае ошибки выделения памяти
    }
    
    // Записываем 'A' в первые 10 байт
    memset(buffer, 'A', 10);
    
    // Записываем 'A' в последние 10 байт
    memset(buffer + buf_size - 10, 'A', 10);
    
    return buffer;
}