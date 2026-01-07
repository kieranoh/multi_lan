#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>

void save_secrete_file(const char *directory, const char *filename, const char *content) {
    // Проверка входных параметров
    if (directory == NULL || filename == NULL || content == NULL) {
        return;
    }
    
    // Создание полного пути к файлу
    size_t dir_len = strlen(directory);
    size_t file_len = strlen(filename);
    size_t total_len = dir_len + file_len + 2; // +2 для '/' и нулевого символа
    
    char *full_path = (char *)malloc(total_len);
    if (full_path == NULL) {
        return;
    }
    
    // Формирование пути
    snprintf(full_path, total_len, "%s/%s", directory, filename);
    
    // Создание директории, если она не существует
    // Создаем с правами 0700 (только для владельца)
    if (mkdir(directory, 0700) != 0) {
        // Если директория уже существует, это нормально
        // Проверяем, что это действительно ошибка "существует"
        if (errno != EEXIST) {
            free(full_path);
            return;
        }
    }
    
    // Открытие файла для записи
    // O_CREAT | O_WRONLY | O_TRUNC: создать файл, открыть для записи, очистить если существует
    // 0600: права доступа - только владелец может читать и писать
    int fd = open(full_path, O_CREAT | O_WRONLY | O_TRUNC, 0600);
    if (fd == -1) {
        free(full_path);
        return;
    }
    
    // Запись содержимого в файл
    size_t content_len = strlen(content);
    ssize_t bytes_written = write(fd, content, content_len);
    
    // Закрытие файла
    close(fd);
    
    // Освобождение памяти
    free(full_path);
    
    // Если запись не удалась, удаляем файл
    if (bytes_written != (ssize_t)content_len) {
        unlink(full_path);
    }
}