#include <string.h>

/* используйте strncpy для копирования содержимого src в dest насколько это возможно

@param dest: буфер назначения
@param dest_size: размер буфера назначения
@param src: буфер источника
@param src_size: размер буфера источника */
void copy_to_dest(char* dest, int dest_size, char* src, int src_size) {
    // Проверяем, чтобы размер назначения был больше 0
    if (dest_size > 0) {
        // Определяем количество байтов, которые можно скопировать
        int bytes_to_copy = (src_size < dest_size - 1) ? src_size : dest_size - 1;
        // Копируем данные из src в dest
        strncpy(dest, src, bytes_to_copy);
        // Обеспечиваем нулевой терминатор в конце строки
        dest[bytes_to_copy] = '\0';
    }
}