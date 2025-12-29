#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *read_file_from_dir(const char *filename, const char *dir_path) {
    // Создаем полный путь к файлу
    size_t path_length = strlen(dir_path) + strlen(filename) + 2; // +2 для '/' и '\0'
    char *full_path = (char *)malloc(path_length);
    if (full_path == NULL) {
        return ""; // Ошибка при выделении памяти
    }
    
    // Формируем путь
    snprintf(full_path, path_length, "%s/%s", dir_path, filename);

    // Открываем файл
    FILE *file = fopen(full_path, "r");
    free(full_path); // Освобождаем память после использования
    if (file == NULL) {
        return ""; // Не удалось открыть файл
    }

    // Определяем размер файла
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);
    
    // Выделяем память для чтения содержимого файла
    char *buffer = (char *)malloc(file_size + 1); // +1 для '\0'
    if (buffer == NULL) {
        fclose(file);
        return ""; // Ошибка при выделении памяти
    }

    // Читаем содержимое файла
    fread(buffer, 1, file_size, file);
    buffer[file_size] = '\0'; // Добавляем завершающий ноль

    fclose(file); // Закрываем файл
    return buffer; // Возвращаем содержимое файла
}