#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <errno.h>

char *read_file_from_dir(const char *filename, const char *dir_path) {
    // Validar parámetros de entrada
    if (filename == NULL || dir_path == NULL) {
        return strdup("");
    }
    
    // Construir la ruta completa del archivo
    size_t dir_len = strlen(dir_path);
    size_t filename_len = strlen(filename);
    
    // Verificar si la ruta del directorio termina con '/'
    int needs_separator = (dir_len > 0 && dir_path[dir_len - 1] != '/');
    
    // Calcular longitud total de la ruta
    size_t full_path_len = dir_len + filename_len + (needs_separator ? 1 : 0) + 1;
    char *full_path = (char *)malloc(full_path_len);
    
    if (full_path == NULL) {
        return strdup("");
    }
    
    // Construir la ruta completa
    if (needs_separator) {
        snprintf(full_path, full_path_len, "%s/%s", dir_path, filename);
    } else {
        snprintf(full_path, full_path_len, "%s%s", dir_path, filename);
    }
    
    // Verificar si el archivo existe y es accesible
    struct stat file_stat;
    if (stat(full_path, &file_stat) != 0) {
        free(full_path);
        return strdup("");
    }
    
    // Verificar que sea un archivo regular
    if (!S_ISREG(file_stat.st_mode)) {
        free(full_path);
        return strdup("");
    }
    
    // Abrir el archivo en modo lectura binaria
    FILE *file = fopen(full_path, "rb");
    free(full_path);
    
    if (file == NULL) {
        return strdup("");
    }
    
    // Obtener el tamaño del archivo
    if (fseek(file, 0, SEEK_END) != 0) {
        fclose(file);
        return strdup("");
    }
    
    long file_size = ftell(file);
    if (file_size < 0) {
        fclose(file);
        return strdup("");
    }
    
    if (fseek(file, 0, SEEK_SET) != 0) {
        fclose(file);
        return strdup("");
    }
    
    // Asignar memoria para el contenido del archivo + terminador nulo
    char *content = (char *)malloc(file_size + 1);
    if (content == NULL) {
        fclose(file);
        return strdup("");
    }
    
    // Leer el contenido del archivo
    size_t bytes_read = fread(content, 1, file_size, file);
    fclose(file);
    
    if (bytes_read != (size_t)file_size) {
        free(content);
        return strdup("");
    }
    
    // Añadir terminador nulo
    content[file_size] = '\0';
    
    return content;
}