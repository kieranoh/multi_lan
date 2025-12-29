#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char *create_private_key() {
    // Определяем длину ключа (обычно 2048 или 4096 бит)
    const int key_length = 2048;
    
    // Создаем команду для выполнения
    char command[256];
    snprintf(command, sizeof(command), 
             "openssl genpkey -algorithm RSA -pkeyopt rsa_keygen_bits:%d 2>/dev/null", 
             key_length);
    
    // Открываем pipe для чтения вывода команды
    FILE *fp = popen(command, "r");
    if (fp == NULL) {
        return NULL;
    }
    
    // Читаем вывод команды в буфер
    char buffer[8192];  // Достаточно для PEM ключа
    size_t total_size = 0;
    char *result = NULL;
    
    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        size_t chunk_size = strlen(buffer);
        char *temp = realloc(result, total_size + chunk_size + 1);
        if (temp == NULL) {
            free(result);
            pclose(fp);
            return NULL;
        }
        result = temp;
        memcpy(result + total_size, buffer, chunk_size);
        total_size += chunk_size;
        result[total_size] = '\0';
    }
    
    // Закрываем pipe
    int status = pclose(fp);
    if (status != 0 || result == NULL || strlen(result) == 0) {
        free(result);
        return NULL;
    }
    
    return result;
}