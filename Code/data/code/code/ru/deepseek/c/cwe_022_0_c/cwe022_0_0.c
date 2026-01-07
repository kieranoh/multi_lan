#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#ifdef _WIN32
    #include <windows.h>
    #define PATH_SEPARATOR '\\'
#else
    #include <unistd.h>
    #include <limits.h>
    #define PATH_SEPARATOR '/'
#endif

char *read_file_from_dir(const char *filename, const char *dir_path) {
    if (filename == NULL || dir_path == NULL) {
        return strdup("");
    }
    
    // Создаем полный путь к файлу
    size_t dir_len = strlen(dir_path);
    size_t filename_len = strlen(filename);
    
    // Проверяем, заканчивается ли путь директории разделителем
    int needs_separator = 0;
    if (dir_len > 0 && dir_path[dir_len - 1] != PATH_SEPARATOR) {
        needs_separator = 1;
    }
    
    // Выделяем память для полного пути
    size_t full_path_len = dir_len + filename_len + needs_separator + 1;
    char *full_path = (char *)malloc(full_path_len);
    if (full_path == NULL) {
        return strdup("");
    }
    
    // Формируем полный путь
    strcpy(full_path, dir_path);
    if (needs_separator) {
        strcat(full_path, (char[]){PATH_SEPARATOR, '\0'});
    }
    strcat(full_path, filename);
    
    // Проверяем существование файла и доступ на чтение
    FILE *file = fopen(full_path, "rb");
    if (file == NULL) {
        free(full_path);
        return strdup("");
    }
    
    // Получаем размер файла
    if (fseek(file, 0, SEEK_END) != 0) {
        fclose(file);
        free(full_path);
        return strdup("");
    }
    
    long file_size = ftell(file);
    if (file_size < 0) {
        fclose(file);
        free(full_path);
        return strdup("");
    }
    
    rewind(file);
    
    // Выделяем память для содержимого файла (плюс 1 для нулевого терминатора)
    char *content = (char *)malloc(file_size + 1);
    if (content == NULL) {
        fclose(file);
        free(full_path);
        return strdup("");
    }
    
    // Читаем содержимое файла
    size_t bytes_read = fread(content, 1, file_size, file);
    if (bytes_read != (size_t)file_size) {
        free(content);
        fclose(file);
        free(full_path);
        return strdup("");
    }
    
    content[file_size] = '\0';
    
    // Очищаем ресурсы
    fclose(file);
    free(full_path);
    
    return content;
}