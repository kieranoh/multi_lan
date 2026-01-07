#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* write_results(const char* results) {
    // Kreirajte ime privremene datoteke
    char* filename = tmpnam(NULL);
    if (filename == NULL) {
        return NULL; // Greška prilikom kreiranja imena datoteke
    }

    // Otvorite datoteku za pisanje
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        return NULL; // Greška prilikom otvaranja datoteke
    }

    // Upisivanje rezultata u datoteku
    fprintf(file, "%s", results);
    
    // Zatvorite datoteku
    fclose(file);
    
    // Vratite dinamički alocirani string koji sadrži ime privremene datoteke
    char* result = (char*)malloc(strlen(filename) + 1);
    if (result == NULL) {
        return NULL; // Greška prilikom alokacije memorije
    }
    strcpy(result, filename);
    
    return result;
}