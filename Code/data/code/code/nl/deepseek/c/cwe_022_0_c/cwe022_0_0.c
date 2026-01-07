#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <errno.h>

#ifdef _WIN32
    #include <windows.h>
    #include <direct.h>
    #define PATH_SEPARATOR "\\"
    #define PATH_SEPARATOR_CHAR '\\'
#else
    #include <unistd.h>
    #include <limits.h>
    #define PATH_SEPARATOR "/"
    #define PATH_SEPARATOR_CHAR '/'
#endif

char *read_file_from_dir(const char *filename, const char *dir_path) {
    // Controleer op NULL pointers
    if (filename == NULL || dir_path == NULL) {
        return strdup("");
    }
    
    // Bouw het volledige pad
    size_t dir_len = strlen(dir_path);
    size_t filename_len = strlen(filename);
    
    // Controleer of het directorypad eindigt met een separator
    int needs_separator = 0;
    if (dir_len > 0 && dir_path[dir_len - 1] != PATH_SEPARATOR_CHAR) {
        needs_separator = 1;
    }
    
    // Bereken de totale lengte van het volledige pad
    size_t full_path_len = dir_len + filename_len + needs_separator + 1;
    char *full_path = (char *)malloc(full_path_len);
    if (full_path == NULL) {
        return strdup("");
    }
    
    // Construeer het volledige pad
    strcpy(full_path, dir_path);
    if (needs_separator) {
        strcat(full_path, PATH_SEPARATOR);
    }
    strcat(full_path, filename);
    
    // Open het bestand
    FILE *file = fopen(full_path, "rb"); // Open in binary mode voor consistente leesoperatie
    free(full_path); // We hebben het pad niet meer nodig na het openen
    
    if (file == NULL) {
        return strdup("");
    }
    
    // Bepaal de grootte van het bestand
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
    
    // Alloceer geheugen voor de inhoud (plus null-terminator)
    char *content = (char *)malloc(file_size + 1);
    if (content == NULL) {
        fclose(file);
        return strdup("");
    }
    
    // Lees de inhoud
    size_t bytes_read = fread(content, 1, file_size, file);
    fclose(file);
    
    if (bytes_read != (size_t)file_size) {
        free(content);
        return strdup("");
    }
    
    // Null-terminate de string
    content[bytes_read] = '\0';
    
    return content;
}