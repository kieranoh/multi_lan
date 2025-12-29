#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <errno.h>

#ifdef _WIN32
    #include <windows.h>
    #include <direct.h>
    #define PATH_SEPARATOR '\\'
    #define PATH_SEPARATOR_STR "\\"
#else
    #include <unistd.h>
    #include <limits.h>
    #define PATH_SEPARATOR '/'
    #define PATH_SEPARATOR_STR "/"
#endif

char *read_file_from_dir(const char *filename, const char *dir_path) {
    // Controllo dei parametri di input
    if (filename == NULL || dir_path == NULL || filename[0] == '\0') {
        return strdup("");
    }
    
    // Costruzione del percorso completo del file
    size_t dir_len = strlen(dir_path);
    size_t filename_len = strlen(filename);
    
    // Controllo se il percorso della directory termina con separatore
    int needs_separator = 0;
    if (dir_len > 0 && dir_path[dir_len - 1] != PATH_SEPARATOR) {
        needs_separator = 1;
    }
    
    // Allocazione per il percorso completo
    size_t full_path_len = dir_len + needs_separator + filename_len + 1;
    char *full_path = (char *)malloc(full_path_len);
    if (full_path == NULL) {
        return strdup("");
    }
    
    // Costruzione del percorso completo
    strcpy(full_path, dir_path);
    if (needs_separator) {
        strcat(full_path, PATH_SEPARATOR_STR);
    }
    strcat(full_path, filename);
    
    // Apertura del file
    FILE *file = fopen(full_path, "rb");  // Modalità binaria per leggere correttamente tutti i file
    free(full_path);  // Libera il percorso completo dopo l'apertura
    
    if (file == NULL) {
        return strdup("");
    }
    
    // Determinazione della dimensione del file
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
    
    // Allocazione della memoria per il contenuto del file
    char *content = (char *)malloc(file_size + 1);
    if (content == NULL) {
        fclose(file);
        return strdup("");
    }
    
    // Lettura del contenuto del file
    size_t bytes_read = fread(content, 1, file_size, file);
    fclose(file);
    
    if (bytes_read != (size_t)file_size) {
        free(content);
        return strdup("");
    }
    
    // Aggiunta del terminatore di stringa
    content[file_size] = '\0';
    
    return content;
}