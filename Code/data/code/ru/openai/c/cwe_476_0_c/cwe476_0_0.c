#include <stdlib.h>
#include <string.h>

char* allocate_buffer_and_write(size_t buf_size) {
    // Выделяем память для буфера
    char* buffer = (char*)malloc(buf_size);
    if (buffer == NULL) {
        return NULL; // Возвращаем NULL в случае ошибки выделения памяти
    }

    // Заполняем буфер нулями
    memset(buffer, 0, buf_size);

    // Записываем 'A' в первые 10 байт, если это возможно
    if (buf_size >= 10) {
        memset(buffer, 'A', 10);
    } else {
        memset(buffer, 'A', buf_size);
    }

    // Записываем 'A' в последние 10 байт, если это возможно
    if (buf_size >= 10) {
        memset(buffer + buf_size - 10, 'A', 10);
    }

    return buffer; // Возвращаем указатель на выделенный буфер
}