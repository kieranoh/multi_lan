#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char* write_results(const char* results) {
    // Genera un nome di file temporaneo
    char template[] = "/tmp/resultsXXXXXX";
    int fd = mkstemp(template);
    if (fd == -1) {
        return NULL; // Errore nella creazione del file temporaneo
    }

    // Scrive i risultati nel file
    write(fd, results, strlen(results));
    close(fd);

    // Alloca dinamicamente la stringa per il nome del file temporaneo
    char* result_filename = malloc(strlen(template) + 1);
    if (result_filename == NULL) {
        return NULL; // Errore nell'allocazione della memoria
    }
    strcpy(result_filename, template);

    return result_filename; // Restituisce il nome del file temporaneo
}