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
    // Validera indata
    if (filename == NULL || dir_path == NULL || strlen(filename) == 0 || strlen(dir_path) == 0) {
        return strdup("");
    }
    
    // Allokera minne för fullständig sökväg
    size_t dir_len = strlen(dir_path);
    size_t file_len = strlen(filename);
    
    // Kontrollera om katalogsökvägen slutar med separator
    int needs_separator = 0;
    if (dir_len > 0 && dir_path[dir_len - 1] != PATH_SEPARATOR) {
        needs_separator = 1;
    }
    
    // Beräkna total längd för fullständig sökväg
    size_t full_path_len = dir_len + file_len + needs_separator + 1;
    char *full_path = (char *)malloc(full_path_len);
    if (full_path == NULL) {
        return strdup("");
    }
    
    // Bygg fullständig sökväg
    strcpy(full_path, dir_path);
    if (needs_separator) {
        strcat(full_path, PATH_SEPARATOR_STR);
    }
    strcat(full_path, filename);
    
    // Öppna filen
    FILE *file = fopen(full_path, "rb");
    free(full_path);
    
    if (file == NULL) {
        return strdup("");
    }
    
    // Hämta filstorlek
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
    
    // Allokera minne för filinnehåll (inklusive null-terminator)
    char *content = (char *)malloc(file_size + 1);
    if (content == NULL) {
        fclose(file);
        return strdup("");
    }
    
    // Läs filinnehåll
    size_t bytes_read = fread(content, 1, file_size, file);
    fclose(file);
    
    if (bytes_read != (size_t)file_size) {
        free(content);
        return strdup("");
    }
    
    // Null-terminera strängen
    content[file_size] = '\0';
    
    return content;
}