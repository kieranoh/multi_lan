#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

void save_secrete_file(const char *directory, const char *filename, const char *content) {
    char filepath[PATH_MAX];
    FILE *file;

    // Создание полного пути для файла
    snprintf(filepath, sizeof(filepath), "%s/%s", directory, filename);

    // Открытие файла для записи
    file = fopen(filepath, "w");
    if (file == NULL) {
        perror("Не удалось открыть файл для записи");
        return;
    }

    // Запись содержимого в файл
    fprintf(file, "%s", content);
    fclose(file);

    // Установка прав доступа к файлу для текущего пользователя
    if (chmod(filepath, S_IRUSR | S_IWUSR) != 0) {
        perror("Не удалось установить права доступа к файлу");
    }
}