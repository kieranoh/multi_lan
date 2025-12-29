#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#ifdef _WIN32
    #include <windows.h>
    #define PATH_SEPARATOR "\\"
    #define PATH_SEPARATOR_CHAR '\\'
#else
    #include <unistd.h>
    #include <sys/stat.h>
    #define PATH_SEPARATOR "/"
    #define PATH_SEPARATOR_CHAR '/'
#endif

char *read_file_from_dir(const char *filename, const char *dir_path) {
    // Tarkista että parametrit eivät ole NULL
    if (filename == NULL || dir_path == NULL) {
        return strdup("");
    }
    
    // Tarkista että tiedostonimi ei ole tyhjä
    if (strlen(filename) == 0) {
        return strdup("");
    }
    
    // Muodosta koko polku tiedostoon
    size_t dir_len = strlen(dir_path);
    size_t file_len = strlen(filename);
    
    // Tarkista että hakemistopolku ei ole liian pitkä
    if (dir_len > 4096 || file_len > 4096) {
        return strdup("");
    }
    
    // Varmista että hakemistopolku päättyy polkuerottimeen
    int needs_separator = 0;
    if (dir_len > 0 && dir_path[dir_len - 1] != PATH_SEPARATOR_CHAR) {
        needs_separator = 1;
    }
    
    // Varaa muisti koko polulle
    size_t full_path_len = dir_len + needs_separator + file_len + 1;
    char *full_path = (char *)malloc(full_path_len);
    if (full_path == NULL) {
        return strdup("");
    }
    
    // Muodosta koko polku
    strcpy(full_path, dir_path);
    if (needs_separator) {
        strcat(full_path, PATH_SEPARATOR);
    }
    strcat(full_path, filename);
    
    // Avaa tiedosto
    FILE *file = fopen(full_path, "rb");  // Avaa binääritilassa
    free(full_path);  // Ei tarvita enää
    
    if (file == NULL) {
        return strdup("");
    }
    
    // Siirry tiedoston loppuun saadaksesi koon
    if (fseek(file, 0, SEEK_END) != 0) {
        fclose(file);
        return strdup("");
    }
    
    long file_size = ftell(file);
    if (file_size < 0) {
        fclose(file);
        return strdup("");
    }
    
    // Siirry takaisin tiedoston alkuun
    rewind(file);
    
    // Varaa muisti tiedoston sisällölle (plus lopetusmerkki)
    char *content = (char *)malloc(file_size + 1);
    if (content == NULL) {
        fclose(file);
        return strdup("");
    }
    
    // Lue tiedoston sisältö
    size_t bytes_read = fread(content, 1, file_size, file);
    
    // Sulje tiedosto
    fclose(file);
    
    // Tarkista että luettiin kaikki data
    if (bytes_read != (size_t)file_size) {
        free(content);
        return strdup("");
    }
    
    // Lisää lopetusmerkki
    content[bytes_read] = '\0';
    
    return content;
}