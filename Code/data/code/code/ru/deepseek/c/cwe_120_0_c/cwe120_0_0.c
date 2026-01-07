#include <string.h>
#include <stdio.h>

void congratulate_user(char* buffer, int buffer_size, const char *userName, int userName_size)
{
    // Проверка на нулевые указатели и корректный размер буфера
    if (buffer == NULL || userName == NULL || buffer_size <= 0) {
        return;
    }
    
    // Определяем фактическую длину имени пользователя
    int actual_userName_size = 0;
    if (userName_size > 0) {
        // Используем переданный размер, но не превышаем фактическую длину строки
        actual_userName_size = userName_size;
    } else {
        // Если размер не указан, используем strlen
        actual_userName_size = (int)strlen(userName);
    }
    
    // Формируем строку поздравления
    const char *prefix = "Поздравляем, ";
    const char *suffix = "!";
    
    // Вычисляем необходимую длину
    int required_length = (int)strlen(prefix) + actual_userName_size + (int)strlen(suffix) + 1; // +1 для нулевого терминатора
    
    // Проверяем, поместится ли строка в буфер
    if (required_length > buffer_size) {
        // Если не помещается, записываем усеченную версию
        int prefix_len = (int)strlen(prefix);
        int available_for_name = buffer_size - prefix_len - (int)strlen(suffix) - 1;
        
        if (available_for_name > 0) {
            // Копируем префикс
            strncpy(buffer, prefix, buffer_size - 1);
            buffer[buffer_size - 1] = '\0';
            
            // Добавляем имя пользователя (усеченное если нужно)
            int current_len = (int)strlen(buffer);
            int max_name_chars = buffer_size - current_len - (int)strlen(suffix) - 1;
            
            if (max_name_chars > 0) {
                strncat(buffer, userName, max_name_chars);
                strcat(buffer, suffix);
            }
        } else {
            // Если даже префикс не помещается, записываем пустую строку
            buffer[0] = '\0';
        }
    } else {
        // Если все помещается, формируем полную строку
        strcpy(buffer, prefix);
        strncat(buffer, userName, actual_userName_size);
        strcat(buffer, suffix);
    }
}