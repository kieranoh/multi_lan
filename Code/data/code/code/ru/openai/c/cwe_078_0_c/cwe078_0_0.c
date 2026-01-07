#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *get_ls_result(const char *dir_path) {
    // Создаем команду для выполнения
    char command[256];
    snprintf(command, sizeof(command), "ls -l %s", dir_path);

    // Создаем временный файл для хранения вывода
    FILE *fp;
    char *result = NULL;
    size_t size = 0;

    // Открываем процесс с помощью popen
    fp = popen(command, "r");
    if (fp == NULL) {
        return ""; // Возвращаем пустую строку в случае ошибки
    }

    // Читаем вывод команды
    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        size_t len = strlen(buffer);
        char *new_result = realloc(result, size + len + 1);
        if (new_result == NULL) {
            free(result);
            pclose(fp);
            return ""; // Возвращаем пустую строку в случае ошибки
        }
        result = new_result;
        strcpy(result + size, buffer);
        size += len;
    }

    // Закрываем процесс
    if (pclose(fp) == -1) {
        free(result);
        return ""; // Возвращаем пустую строку в случае ошибки
    }

    return result; // Возвращаем результат
}