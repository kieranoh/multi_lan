#include <stdlib.h>
#include <string.h>

char* get_welcome_message(const char* username) {
    const char* prefix = "Добро пожаловать, ";
    const char* suffix = "!";
    
    // Вычисляем длину результирующей строки
    size_t prefix_len = strlen(prefix);
    size_t username_len = strlen(username);
    size_t suffix_len = strlen(suffix);
    size_t total_len = prefix_len + username_len + suffix_len + 1; // +1 для нулевого терминатора
    
    // Выделяем память для результирующей строки
    char* message = (char*)malloc(total_len * sizeof(char));
    if (message == NULL) {
        return NULL; // Возвращаем NULL в случае ошибки выделения памяти
    }
    
    // Формируем строку
    strcpy(message, prefix);
    strcat(message, username);
    strcat(message, suffix);
    
    return message;
}