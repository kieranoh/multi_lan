#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#ifdef _WIN32
    #include <windows.h>
    #include <direct.h>
    #define PATH_SEPARATOR '\\'
    #define PATH_SEPARATOR_STR "\\"
#else
    #include <unistd.h>
    #include <sys/stat.h>
    #define PATH_SEPARATOR '/'
    #define PATH_SEPARATOR_STR "/"
#endif

char *read_file_from_dir(const char *filename, const char *dir_path) {
    // Ellenőrizzük a bemeneti paramétereket
    if (filename == NULL || dir_path == NULL) {
        return strdup("");
    }
    
    // Ellenőrizzük, hogy a könyvtárútvonal és a fájlnév nem üres
    if (strlen(filename) == 0 || strlen(dir_path) == 0) {
        return strdup("");
    }
    
    // Összeállítjuk a teljes elérési utat
    size_t dir_len = strlen(dir_path);
    size_t filename_len = strlen(filename);
    
    // Ellenőrizzük, hogy a könyvtárútvonal végén van-e elválasztó
    int needs_separator = 0;
    if (dir_len > 0 && dir_path[dir_len - 1] != PATH_SEPARATOR) {
        needs_separator = 1;
    }
    
    // Számoljuk ki a szükséges méretet
    size_t full_path_len = dir_len + filename_len + (needs_separator ? 1 : 0) + 1;
    char *full_path = (char *)malloc(full_path_len);
    
    if (full_path == NULL) {
        return strdup("");
    }
    
    // Összeállítjuk a teljes elérési utat
    strcpy(full_path, dir_path);
    if (needs_separator) {
        strcat(full_path, PATH_SEPARATOR_STR);
    }
    strcat(full_path, filename);
    
    // Megpróbáljuk megnyitni a fájlt
    FILE *file = fopen(full_path, "rb");
    free(full_path);
    
    if (file == NULL) {
        return strdup("");
    }
    
    // Pozicionálás a fájl végére a méret meghatározásához
    if (fseek(file, 0, SEEK_END) != 0) {
        fclose(file);
        return strdup("");
    }
    
    long file_size = ftell(file);
    if (file_size < 0) {
        fclose(file);
        return strdup("");
    }
    
    // Vissza a fájl elejére
    rewind(file);
    
    // Foglalunk memóriát a tartalomnak (plusz egy nullterminátor)
    char *content = (char *)malloc(file_size + 1);
    if (content == NULL) {
        fclose(file);
        return strdup("");
    }
    
    // Beolvassuk a fájl tartalmát
    size_t bytes_read = fread(content, 1, file_size, file);
    
    // Nulltermináljuk a stringet
    content[bytes_read] = '\0';
    
    // Bezárjuk a fájlt
    fclose(file);
    
    // Ellenőrizzük, hogy minden bájtot beolvastunk-e
    if (bytes_read != (size_t)file_size) {
        free(content);
        return strdup("");
    }
    
    return content;
}