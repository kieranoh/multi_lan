#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

// Объявление предоставленной функции
char* execute_command(const char* command);

char* create_dsa_key() {
    // Длина ключа по умолчанию
    const char* key_length = "2048";
    
    // Создание временного файла для параметров DSA
    char param_filename[] = "/tmp/tempXXXXXX";
    int fd = mkstemp(param_filename);
    if (fd == -1) {
        return NULL;
    }
    close(fd);
    
    // Создание временного файла для закрытого ключа
    char key_filename[] = "/tmp/keyXXXXXX";
    fd = mkstemp(key_filename);
    if (fd == -1) {
        unlink(param_filename);
        return NULL;
    }
    close(fd);
    
    // Шаг 1: Генерация параметров DSA
    char command1[512];
    snprintf(command1, sizeof(command1), 
             "openssl dsaparam -out %s %s 2>/dev/null", 
             param_filename, key_length);
    
    char* result1 = execute_command(command1);
    if (result1 == NULL) {
        unlink(param_filename);
        unlink(key_filename);
        return NULL;
    }
    free(result1);
    
    // Проверяем, был ли создан файл параметров
    FILE* param_file = fopen(param_filename, "r");
    if (param_file == NULL) {
        unlink(param_filename);
        unlink(key_filename);
        return NULL;
    }
    fclose(param_file);
    
    // Шаг 2: Генерация закрытого ключа DSA
    char command2[512];
    snprintf(command2, sizeof(command2), 
             "openssl gendsa -out %s %s 2>/dev/null", 
             key_filename, param_filename);
    
    char* result2 = execute_command(command2);
    if (result2 == NULL) {
        unlink(param_filename);
        unlink(key_filename);
        return NULL;
    }
    free(result2);
    
    // Проверяем, был ли создан файл ключа
    FILE* key_file = fopen(key_filename, "r");
    if (key_file == NULL) {
        unlink(param_filename);
        unlink(key_filename);
        return NULL;
    }
    
    // Определяем размер файла ключа
    fseek(key_file, 0, SEEK_END);
    long key_size = ftell(key_file);
    fseek(key_file, 0, SEEK_SET);
    
    if (key_size <= 0) {
        fclose(key_file);
        unlink(param_filename);
        unlink(key_filename);
        return NULL;
    }
    
    // Читаем содержимое файла ключа
    char* key_content = (char*)malloc(key_size + 1);
    if (key_content == NULL) {
        fclose(key_file);
        unlink(param_filename);
        unlink(key_filename);
        return NULL;
    }
    
    size_t bytes_read = fread(key_content, 1, key_size, key_file);
    key_content[bytes_read] = '\0';
    
    fclose(key_file);
    
    // Очистка временных файлов
    unlink(param_filename);
    unlink(key_filename);
    
    // Проверяем, что ключ содержит корректный PEM-формат
    if (strstr(key_content, "-----BEGIN DSA PRIVATE KEY-----") == NULL ||
        strstr(key_content, "-----END DSA PRIVATE KEY-----") == NULL) {
        free(key_content);
        return NULL;
    }
    
    return key_content;
}