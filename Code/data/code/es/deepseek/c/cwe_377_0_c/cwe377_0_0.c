#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char* write_results(const char* results) {
    // Verificar que results no sea NULL
    if (results == NULL) {
        return NULL;
    }
    
    // Crear una plantilla para el archivo temporal
    char template[] = "/tmp/results_XXXXXX";
    
    // Crear el archivo temporal usando mkstemp
    int fd = mkstemp(template);
    if (fd == -1) {
        return NULL;
    }
    
    // Escribir los resultados en el archivo
    size_t len = strlen(results);
    ssize_t written = write(fd, results, len);
    
    if (written != (ssize_t)len) {
        // Error al escribir, cerrar y eliminar el archivo
        close(fd);
        unlink(template);
        return NULL;
    }
    
    // Cerrar el archivo
    close(fd);
    
    // Asignar memoria para el nombre del archivo
    char* filename = malloc(strlen(template) + 1);
    if (filename == NULL) {
        // No pudimos asignar memoria, eliminar el archivo
        unlink(template);
        return NULL;
    }
    
    // Copiar el nombre del archivo
    strcpy(filename, template);
    
    return filename;
}