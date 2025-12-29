#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char* write_results(const char* results) {
    // Verifica che l'input non sia NULL
    if (results == NULL) {
        return NULL;
    }

    // Crea un template per il file temporaneo
    char template[] = "/tmp/results_XXXXXX";
    
    // Crea il file temporaneo usando mkstemp
    int fd = mkstemp(template);
    if (fd == -1) {
        return NULL;
    }

    // Scrive i risultati nel file
    size_t len = strlen(results);
    ssize_t written = write(fd, results, len);
    
    // Chiude il file descriptor
    close(fd);

    // Verifica se la scrittura è avvenuta correttamente
    if (written != (ssize_t)len) {
        // Se la scrittura fallisce, rimuove il file e restituisce NULL
        unlink(template);
        return NULL;
    }

    // Alloca memoria per il nome del file
    char* filename = malloc(strlen(template) + 1);
    if (filename == NULL) {
        // Se l'allocazione fallisce, rimuove il file e restituisce NULL
        unlink(template);
        return NULL;
    }

    // Copia il nome del file nella memoria allocata
    strcpy(filename, template);
    
    return filename;
}