#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *read_file_from_dir(const char *filename, const char *dir_path) {
    // Formiramo punu putanju do datoteke
    size_t path_length = strlen(dir_path) + strlen(filename) + 2; // +2 za '/' i '\0'
    char *full_path = (char *)malloc(path_length);

    if (full_path == NULL) {
        return ""; // greška u alokaciji
    }

    snprintf(full_path, path_length, "%s/%s", dir_path, filename);

    // Otvaramo datoteku za čitanje
    FILE *file = fopen(full_path, "r");
    free(full_path); // Oslobađamo memoriju za punu putanju

    if (file == NULL) {
        return ""; // greška prilikom otvaranja datoteke
    }

    // Pomera se na kraj datoteke da se dobije veličina datoteke
    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    fseek(file, 0, SEEK_SET); // Ponovo se postavlja pokazivač na početak

    // Alociramo memoriju za sadržaj datoteke
    char *content = (char *)malloc(length + 1); // +1 za '\0'
    if (content == NULL) {
        fclose(file);
        return ""; // greška u alokaciji
    }

    // Čitamo sadržaj datoteke
    fread(content, 1, length, file);
    content[length] = '\0'; // Dodajemo terminator na kraju

    fclose(file);
    return content; // Vraćamo sadržaj datoteke
}