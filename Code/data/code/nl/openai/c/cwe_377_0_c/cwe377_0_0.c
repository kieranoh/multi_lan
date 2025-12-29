#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char* write_results(const char* results) {
    // Maak een pad voor het tijdelijke bestand
    char* temp_filename = tmpnam(NULL);
    if (temp_filename == NULL) {
        return NULL; // Fout bij het genereren van een tijdelijke bestandsnaam
    }

    // Open het tijdelijke bestand voor schrijven
    FILE* file = fopen(temp_filename, "w");
    if (file == NULL) {
        return NULL; // Fout bij het openen van het bestand
    }

    // Schrijf de resultaten naar het tijdelijke bestand
    size_t written = fwrite(results, sizeof(char), strlen(results), file);
    
    // Sluit het bestand
    fclose(file);

    // Controleer of een fout is opgetreden bij het schrijven
    if (written < strlen(results)) {
        return NULL; // Fout bij het schrijven naar het bestand
    }

    // Retourneer de naam van het tijdelijke bestand
    return temp_filename;
}