#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char* write_results(const char* results) {
    if (results == NULL) {
        return NULL;
    }
    
    // Создаем шаблон для временного файла
    char template[] = "/tmp/results_XXXXXX";
    
    // Создаем временный файл с уникальным именем
    int fd = mkstemp(template);
    if (fd == -1) {
        return NULL;
    }
    
    // Записываем содержимое в файл
    size_t len = strlen(results);
    ssize_t written = write(fd, results, len);
    
    if (written != (ssize_t)len) {
        close(fd);
        unlink(template);
        return NULL;
    }
    
    // Закрываем файл
    close(fd);
    
    // Выделяем память для имени файла
    char* filename = (char*)malloc(strlen(template) + 1);
    if (filename == NULL) {
        unlink(template);
        return NULL;
    }
    
    // Копируем имя файла в выделенную память
    strcpy(filename, template);
    
    return filename;
}