#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char* write_results(const char* results) {
    // Crear un fitxer temporal
    char* filename_template = "/tmp/resultsXXXXXX";
    char* temp_filename = (char*)malloc(strlen(filename_template) + 1);
    if (!temp_filename) {
        return NULL; // Error en la reserva de memòria
    }
    strcpy(temp_filename, filename_template);
    
    int fd = mkstemp(temp_filename);
    if (fd == -1) {
        free(temp_filename);
        return NULL; // Error en la creació del fitxer temporal
    }

    // Escriure els resultats al fitxer temporal
    write(fd, results, strlen(results));
    
    // Tancar el fitxer
    close(fd);
    
    // Retornar el nom del fitxer temporal
    return temp_filename;
}