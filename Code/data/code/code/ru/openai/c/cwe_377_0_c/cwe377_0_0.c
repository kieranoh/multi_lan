#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char* write_results(const char* results) {
    // Создаем временный файл
    char temp_filename[] = "/tmp/resultsXXXXXX"; // Шаблон для временного файла
    int fd = mkstemp(temp_filename);
    
    if (fd == -1) {
        return NULL; // Ошибка создания файла
    }

    // Записываем данные в файл
    if (write(fd, results, strlen(results)) == -1) {
        close(fd);
        unlink(temp_filename); // Удаляем файл в случае ошибки записи
        return NULL;
    }

    // Закрываем дескриптор файла
    close(fd);

    // Выделяем память для возвращаемого имени файла
    char* result_filename = malloc(strlen(temp_filename) + 1);
    if (result_filename == NULL) {
        unlink(temp_filename); // Удаляем файл в случае ошибки выделения памяти
        return NULL;
    }

    // Копируем имя временного файла в выделенную память
    strcpy(result_filename, temp_filename);

    return result_filename; // Возвращаем имя временного файла
}