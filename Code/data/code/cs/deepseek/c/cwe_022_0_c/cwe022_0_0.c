#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <errno.h>

#ifdef _WIN32
    #include <direct.h>
    #define PATH_SEPARATOR "\\"
    #define PATH_SEPARATOR_CHAR '\\'
#else
    #include <unistd.h>
    #define PATH_SEPARATOR "/"
    #define PATH_SEPARATOR_CHAR '/'
#endif

char *read_file_from_dir(const char *filename, const char *dir_path) {
    // Kontrola vstupních parametrů
    if (filename == NULL || dir_path == NULL) {
        return strdup("");
    }
    
    // Kontrola, zda je název souboru prázdný
    if (strlen(filename) == 0) {
        return strdup("");
    }
    
    // Vytvoření úplné cesty k souboru
    size_t dir_len = strlen(dir_path);
    size_t filename_len = strlen(filename);
    
    // Kontrola, zda cesta končí separátorem
    int needs_separator = 0;
    if (dir_len > 0 && dir_path[dir_len - 1] != PATH_SEPARATOR_CHAR) {
        needs_separator = 1;
    }
    
    // Alokace paměti pro úplnou cestu
    size_t full_path_len = dir_len + needs_separator + filename_len + 1;
    char *full_path = (char *)malloc(full_path_len);
    if (full_path == NULL) {
        return strdup("");
    }
    
    // Sestavení úplné cesty
    strcpy(full_path, dir_path);
    if (needs_separator) {
        strcat(full_path, PATH_SEPARATOR);
    }
    strcat(full_path, filename);
    
    // Otevření souboru
    FILE *file = fopen(full_path, "rb");  // "rb" pro binární režim, aby správně fungovalo na všech platformách
    free(full_path);  // Uvolnění cesty, už ji nepotřebujeme
    
    if (file == NULL) {
        return strdup("");
    }
    
    // Získání velikosti souboru
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
    
    // Alokace paměti pro obsah souboru (plus null terminator)
    char *content = (char *)malloc(file_size + 1);
    if (content == NULL) {
        fclose(file);
        return strdup("");
    }
    
    // Čtení obsahu souboru
    size_t bytes_read = fread(content, 1, file_size, file);
    fclose(file);
    
    if (bytes_read != (size_t)file_size) {
        free(content);
        return strdup("");
    }
    
    // Přidání null terminatoru
    content[file_size] = '\0';
    
    return content;
}