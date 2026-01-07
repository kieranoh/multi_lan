#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* write_results(const char* results) {
    // Fitxategi izena sortu (adibidez, "results.txt")
    const char* filename = "results.txt";
    
    // Fitxategia ireki idazteko moduan
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        return NULL; // Fitxategia irekitzean errore bat izanez gero, NULL itzuli
    }

    // Emaitzak fitxategira idatzi
    fprintf(file, "%s", results);
    
    // Fitxategia itxi
    fclose(file);

    // Fitxategi izena kopia dinamikoa sortu
    char* result_filename = malloc(strlen(filename) + 1);
    if (result_filename != NULL) {
        strcpy(result_filename, filename);
    }

    // Fitxategi izena itzuli
    return result_filename;
}