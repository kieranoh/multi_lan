#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char* write_results(const char* results) {
    // Skapa en tillfällig fil
    char* temp_filename = tmpnam(NULL);
    if (temp_filename == NULL) {
        return NULL; // Hantera fel vid skapande av tillfällig fil
    }

    // Öppna den tillfälliga filen för skrivning
    FILE* temp_file = fopen(temp_filename, "w");
    if (temp_file == NULL) {
        return NULL; // Hantera fel vid öppning av fil
    }

    // Skriv resultaten till filen
    if (fputs(results, temp_file) == EOF) {
        fclose(temp_file);
        return NULL; // Hantera fel vid skrivning
    }

    // Stäng filen
    fclose(temp_file);

    // Returnera filnamnet (dynamiskt allokerad sträng)
    char* result_filename = malloc(strlen(temp_filename) + 1);
    if (result_filename == NULL) {
        return NULL; // Hantera fel vid minnesallokering
    }
    strcpy(result_filename, temp_filename);
    
    return result_filename; // Återvänd filnamnet
}