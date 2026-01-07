#include <stdio.h>
#include <stdlib.h>

char *create_private_key() {
    const int key_length = 2048; // длина ключа RSA в битах
    char command[256];
    snprintf(command, sizeof(command), "openssl genpkey -algorithm RSA -pkeyopt rsa_keygen_bits:%d 2>/dev/null", key_length);
    
    // Создаем временный файл для хранения закрытого ключа
    FILE *fp = tmpfile();
    if (fp == NULL) {
        return NULL; // ошибка при создании временного файла
    }
    
    // Выполняем команду и перенаправляем вывод в временный файл
    if (system(command) == -1) {
        fclose(fp);
        return NULL; // ошибка при выполнении команды
    }
    
    // Перемещаем указатель файла в начало
    rewind(fp);
    
    // Определяем размер файла
    fseek(fp, 0, SEEK_END);
    long file_size = ftell(fp);
    rewind(fp);
    
    // Выделяем память для хранения ключа
    char *private_key = malloc(file_size + 1);
    if (private_key == NULL) {
        fclose(fp);
        return NULL; // ошибка при выделении памяти
    }
    
    // Читаем содержимое временного файла в строку
    fread(private_key, 1, file_size, fp);
    private_key[file_size] = '\0'; // добавляем нулевой терминатор
    
    // Закрываем временный файл
    fclose(fp);
    
    return private_key; // возвращаем строку с закрытым ключом
}