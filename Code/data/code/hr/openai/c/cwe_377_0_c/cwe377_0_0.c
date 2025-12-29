#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char* write_results(const char* results) {
    // Generišemo ime privremene datoteke
    char* temp_filename = malloc(256);
    if (temp_filename == NULL) {
        return NULL; // Neuspjeh alokacije memorije
    }

    // Kreiramo privremenu datoteku koristeći mkstemp
    snprintf(temp_filename, 256, "/tmp/resultsXXXXXX");
    int fd = mkstemp(temp_filename);
    if (fd == -1) {
        free(temp_filename);
        return NULL; // Neuspjeh kreiranja datoteke
    }

    // Upišemo rezultate u privremenu datoteku
    FILE* file = fdopen(fd, "w");
    if (file == NULL) {
        free(temp_filename);
        close(fd);
        return NULL; // Neuspjeh otvaranja datoteke
    }

    fprintf(file, "%s", results);
    fclose(file);

    return temp_filename; // Vraćamo naziv privremene datoteke
}