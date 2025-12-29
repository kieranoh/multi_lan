#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <errno.h>

char *read_file_from_dir(const char *filename, const char *dir_path) {
    // Proveri da li su ulazni parametri validni
    if (filename == NULL || dir_path == NULL || strlen(filename) == 0 || strlen(dir_path) == 0) {
        return strdup("");
    }
    
    // Konstruiši punu putanju do datoteke
    // Dodajemo +2 za '/' i za null terminator
    size_t path_len = strlen(dir_path) + strlen(filename) + 2;
    char *full_path = (char *)malloc(path_len);
    if (full_path == NULL) {
        return strdup("");
    }
    
    // Kreiraj punu putanju
    snprintf(full_path, path_len, "%s/%s", dir_path, filename);
    
    // Otvori datoteku za čitanje
    FILE *file = fopen(full_path, "rb");
    if (file == NULL) {
        free(full_path);
        return strdup("");
    }
    
    // Odredi veličinu datoteke
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
    
    // Vrati se na početak datoteke
    rewind(file);
    
    // Alociraj memoriju za sadržaj datoteke + null terminator
    char *content = (char *)malloc(file_size + 1);
    if (content == NULL) {
        fclose(file);
        free(full_path);
        return strdup("");
    }
    
    // Pročitaj celokupan sadržaj datoteke
    size_t bytes_read = fread(content, 1, file_size, file);
    if (bytes_read != (size_t)file_size) {
        free(content);
        fclose(file);
        free(full_path);
        return strdup("");
    }
    
    // Dodaj null terminator na kraj
    content[file_size] = '\0';
    
    // Očisti resurse
    fclose(file);
    free(full_path);
    
    return content;
}