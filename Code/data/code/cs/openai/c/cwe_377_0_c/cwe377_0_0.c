#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

char* write_results(const char* results) {
    // Vytvoření dočasného souboru s unikátním názvem
    char* filename = malloc(sizeof(char) * 256);
    if (filename == NULL) {
        return NULL; // Kontrola alokace paměti
    }

    // Generování názvu souboru
    snprintf(filename, 256, "/tmp/results_XXXXXX");
    int fd = mkstemp(filename);
    if (fd == -1) {
        free(filename);
        return NULL; // Chyba při vytváření souboru
    }

    // Zápis výsledků do souboru
    if (write(fd, results, strlen(results)) == -1) {
        free(filename);
        close(fd);
        return NULL; // Chyba při zápisu
    }

    // Uzavření souboru
    close(fd);

    // Název souboru je vrácen, uživatel je odpovědný za uvolnění paměti
    return filename;
}