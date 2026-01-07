#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

// Объявление функции для выполнения shell-команды и захвата ее вывода
char* execute_command(const char* command);

// Функция для создания DSA-ключа
char* create_dsa_key() {
    char param_filename[] = "/tmp/tempXXXXXX"; // Шаблон для временного файла
    int fd = mkstemp(param_filename); // Создание временного файла
    if (fd == -1) {
        return NULL; // Ошибка при создании временного файла
    }
    close(fd); // Закрываем дескриптор файла, так как он больше не нужен

    // Длина ключа (например, 2048 бит)
    int key_length = 2048;

    // Формируем команды для генерации параметров DSA и закрытого ключа
    char command[256];
    snprintf(command, sizeof(command), "openssl dsaparam -out %s %d", param_filename, key_length);
    if (execute_command(command) == NULL) {
        unlink(param_filename); // Удаляем временный файл при ошибке
        return NULL;
    }

    snprintf(command, sizeof(command), "openssl gendsa -out %s %s", param_filename, param_filename);
    if (execute_command(command) == NULL) {
        unlink(param_filename); // Удаляем временный файл при ошибке
        return NULL;
    }

    // Читаем закрытый ключ из временного файла
    FILE* file = fopen(param_filename, "r");
    if (file == NULL) {
        unlink(param_filename); // Удаляем временный файл при ошибке
        return NULL;
    }

    // Вычисляем размер файла
    fseek(file, 0, SEEK_END);
    long filesize = ftell(file);
    fseek(file, 0, SEEK_SET);

    // Выделяем память для хранения закрытого ключа
    char* dsa_key = (char*)malloc(filesize + 1);
    if (dsa_key == NULL) {
        fclose(file);
        unlink(param_filename); // Удаляем временный файл при ошибке
        return NULL;
    }

    // Читаем содержимое файла в строку
    fread(dsa_key, 1, filesize, file);
    dsa_key[filesize] = '\0'; // Добавляем завершающий ноль
    fclose(file);

    // Удаляем временный файл
    unlink(param_filename);

    return dsa_key; // Возвращаем закрытый DSA-ключ
}