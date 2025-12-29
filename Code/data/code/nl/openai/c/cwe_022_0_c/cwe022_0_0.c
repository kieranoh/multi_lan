#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *read_file_from_dir(const char *filename, const char *dir_path) {
    // Bereken de totale lengte van het volledige pad
    size_t path_len = strlen(dir_path) + strlen(filename) + 2; // +2 voor '/' en '\0'
    char *full_path = (char *)malloc(path_len);
    
    if (full_path == NULL) {
        return ""; // Retourneer een lege string bij allocatiefout
    }

    // Maak het volledige pad
    snprintf(full_path, path_len, "%s/%s", dir_path, filename);
    
    // Open het bestand voor lezen
    FILE *file = fopen(full_path, "r");
    free(full_path); // Vrijgeven van het pad geheugen

    if (file == NULL) {
        return ""; // Retourneer een lege string bij fout
    }

    // Zoek de grootte van het bestand
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    // Alloceer geheugen voor de inhoud
    char *buffer = (char *)malloc(file_size + 1); // +1 voor de null-terminator

    if (buffer == NULL) {
        fclose(file);
        return ""; // Retourneer een lege string bij allocatiefout
    }

    // Lees de inhoud van het bestand
    fread(buffer, 1, file_size, file);
    buffer[file_size] = '\0'; // Voeg de null-terminator toe

    // Sluit het bestand
    fclose(file);

    return buffer; // Retourneer de inhoud van het bestand
}