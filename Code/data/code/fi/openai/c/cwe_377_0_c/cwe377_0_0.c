#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char* write_results(const char* results) {
    // Luo väliaikaisen tiedoston nimi
    char* filename = (char*)malloc(256 * sizeof(char));
    if (filename == NULL) {
        return NULL; // Tarkista muistiallokointi
    }
    
    // Generoi väliaikaisen tiedoston nimi
    snprintf(filename, 256, "tempfile_XXXXXX");
    int fd = mkstemp(filename);
    if (fd == -1) {
        free(filename);
        return NULL; // Tarkista tiedoston luonti
    }

    // Kirjoita tulokset tiedostoon
    if (results != NULL) {
        write(fd, results, strlen(results));
    }
    
    // Sulje tiedosto
    close(fd);
    
    return filename; // Palauta dynaamisesti allokoitu tiedoston nimi
}