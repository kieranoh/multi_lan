#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *read_file_from_dir(const char *filename, const char *dir_path) {
    // Vytvoření cesty k souboru
    char *full_path;
    size_t path_length = strlen(dir_path) + strlen(filename) + 2; // +2 pro '/' a '\0'
    full_path = (char *)malloc(path_length);
    if (!full_path) {
        return ""; // Vrátíme prázdný řetězec, pokud došlo k chybě při alokaci paměti
    }
    snprintf(full_path, path_length, "%s/%s", dir_path, filename);

    // Otevření souboru
    FILE *file = fopen(full_path, "r");
    free(full_path); // Uvolníme proměnnou pro cestu k souboru, již ji nepotřebujeme
    if (!file) {
        return ""; // Vrátíme prázdný řetězec, pokud se soubor nepodařilo otevřít
    }

    // Zjistíme velikost souboru
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);
    
    // Alokujeme paměť pro čtení obsahu souboru
    char *content = (char *)malloc(file_size + 1); // +1 pro '\0'
    if (!content) {
        fclose(file);
        return ""; // Vrátíme prázdný řetězec, pokud došlo k chybě při alokaci paměti
    }

    // Čtení obsahu souboru
    fread(content, 1, file_size, file);
    content[file_size] = '\0'; // Přidání koncového znaku

    // Uzavření souboru
    fclose(file);
    return content; // Vrátíme obsah souboru
}