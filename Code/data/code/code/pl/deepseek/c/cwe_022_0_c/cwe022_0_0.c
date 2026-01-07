#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <errno.h>

char *read_file_from_dir(const char *filename, const char *dir_path) {
    // Sprawdzenie poprawności parametrów wejściowych
    if (filename == NULL || dir_path == NULL) {
        return strdup("");
    }
    
    // Otwarcie katalogu
    DIR *dir = opendir(dir_path);
    if (dir == NULL) {
        return strdup("");
    }
    
    // Przeszukanie katalogu w poszukiwaniu pliku
    struct dirent *entry;
    int found = 0;
    
    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, filename) == 0) {
            found = 1;
            break;
        }
    }
    
    // Jeśli plik nie został znaleziony, zamknij katalog i zwróć pusty ciąg
    if (!found) {
        closedir(dir);
        return strdup("");
    }
    
    // Zamknij katalog, ponieważ już znaleźliśmy plik
    closedir(dir);
    
    // Zbuduj pełną ścieżkę do pliku
    size_t path_len = strlen(dir_path) + strlen(filename) + 2; // +2 dla '/' i '\0'
    char *full_path = malloc(path_len);
    if (full_path == NULL) {
        return strdup("");
    }
    
    snprintf(full_path, path_len, "%s/%s", dir_path, filename);
    
    // Otwórz plik do odczytu
    FILE *file = fopen(full_path, "rb");
    free(full_path);
    
    if (file == NULL) {
        return strdup("");
    }
    
    // Przejdź na koniec pliku, aby określić jego rozmiar
    if (fseek(file, 0, SEEK_END) != 0) {
        fclose(file);
        return strdup("");
    }
    
    long file_size = ftell(file);
    if (file_size < 0) {
        fclose(file);
        return strdup("");
    }
    
    // Wróć na początek pliku
    rewind(file);
    
    // Przydziel pamięć na zawartość pliku (+1 dla znaku null)
    char *content = malloc(file_size + 1);
    if (content == NULL) {
        fclose(file);
        return strdup("");
    }
    
    // Odczytaj całą zawartość pliku
    size_t bytes_read = fread(content, 1, file_size, file);
    fclose(file);
    
    // Sprawdź, czy odczytano cały plik
    if (bytes_read != (size_t)file_size) {
        free(content);
        return strdup("");
    }
    
    // Zakończ ciąg znakiem null
    content[file_size] = '\0';
    
    return content;
}