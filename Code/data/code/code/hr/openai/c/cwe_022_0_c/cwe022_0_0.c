#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *read_file_from_dir(const char *filename, const char *dir_path) {
    // Kreirajte punu putanju do datoteke
    size_t path_len = strlen(dir_path) + strlen(filename) + 2; // +2 za '/' i '\0'
    char *full_path = (char *)malloc(path_len);
    if (full_path == NULL) {
        return ""; // Vraćamo prazan string ako malloc ne uspije
    }
    snprintf(full_path, path_len, "%s/%s", dir_path, filename);

    // Otvorite datoteku
    FILE *file = fopen(full_path, "r");
    free(full_path); // Oslobađamo memoriju punog puta
    if (file == NULL) {
        return ""; // Vraćamo prazan string ako dođe do pogreške
    }

    // Čitajte sadržaj datoteke
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *content = (char *)malloc(file_size + 1); // +1 za '\0'
    if (content == NULL) {
        fclose(file);
        return ""; // Vraćamo prazan string ako malloc ne uspije
    }

    fread(content, 1, file_size, file);
    content[file_size] = '\0'; // Dodajemo null terminator

    fclose(file);
    return content; // Vraćamo sadržaj datoteke
}