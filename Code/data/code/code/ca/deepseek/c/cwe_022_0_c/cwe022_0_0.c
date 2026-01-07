#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <errno.h>

#ifdef _WIN32
    #include <windows.h>
    #define PATH_SEPARATOR '\\'
#else
    #include <unistd.h>
    #include <limits.h>
    #define PATH_SEPARATOR '/'
#endif

char *read_file_from_dir(const char *filename, const char *dir_path) {
    // Validar entrades
    if (filename == NULL || dir_path == NULL || strlen(filename) == 0) {
        return strdup("");
    }
    
    // Construir el camí complet del fitxer
    size_t dir_len = strlen(dir_path);
    size_t filename_len = strlen(filename);
    
    // Comprovar si el directori ja té una barra al final
    int needs_separator = 0;
    if (dir_len > 0 && dir_path[dir_len - 1] != PATH_SEPARATOR) {
        needs_separator = 1;
    }
    
    // Calcular la mida necessària per al camí complet
    size_t full_path_len = dir_len + needs_separator + filename_len + 1;
    char *full_path = (char *)malloc(full_path_len);
    if (full_path == NULL) {
        return strdup("");
    }
    
    // Construir el camí complet
    strcpy(full_path, dir_path);
    if (needs_separator) {
        strcat(full_path, (char[]){PATH_SEPARATOR, '\0'});
    }
    strcat(full_path, filename);
    
    // Verificar que el camí complet no surti del directori donat (seguretat bàsica)
    #ifndef _WIN32
    char resolved_path[PATH_MAX];
    if (realpath(full_path, resolved_path) == NULL) {
        free(full_path);
        return strdup("");
    }
    
    // Comprovar que el camí resolt comenci amb el directori donat
    size_t resolved_dir_len = strlen(dir_path);
    char *resolved_dir = realpath(dir_path, NULL);
    if (resolved_dir == NULL) {
        free(full_path);
        return strdup("");
    }
    
    if (strncmp(resolved_path, resolved_dir, strlen(resolved_dir)) != 0) {
        free(resolved_dir);
        free(full_path);
        return strdup("");
    }
    free(resolved_dir);
    #endif
    
    // Obrir el fitxer
    FILE *file = fopen(full_path, "rb");
    if (file == NULL) {
        free(full_path);
        return strdup("");
    }
    
    // Obtenir la mida del fitxer
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
    
    if (fseek(file, 0, SEEK_SET) != 0) {
        fclose(file);
        free(full_path);
        return strdup("");
    }
    
    // Assignar memòria per al contingut (incloent el byte nul)
    char *content = (char *)malloc(file_size + 1);
    if (content == NULL) {
        fclose(file);
        free(full_path);
        return strdup("");
    }
    
    // Llegir el contingut del fitxer
    size_t bytes_read = fread(content, 1, file_size, file);
    if (bytes_read != (size_t)file_size) {
        free(content);
        fclose(file);
        free(full_path);
        return strdup("");
    }
    
    // Tancar el fitxer i alliberar el camí
    fclose(file);
    free(full_path);
    
    // Afegir el terminador nul
    content[file_size] = '\0';
    
    return content;
}