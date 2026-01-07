#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char* write_results(const char* results) {
    // Verificar que results no sea NULL
    if (results == NULL) {
        return NULL;
    }
    
    // Crear una plantilla para el nombre del archivo temporal
    char template[] = "/tmp/results_XXXXXX";
    
    // Crear un archivo temporal usando mkstemp
    int fd = mkstemp(template);
    if (fd == -1) {
        return NULL;
    }
    
    // Escribir el contenido en el archivo
    size_t len = strlen(results);
    ssize_t bytes_written = write(fd, results, len);
    
    // Cerrar el archivo
    close(fd);
    
    // Verificar si la escritura fue exitosa
    if (bytes_written != (ssize_t)len) {
        // Eliminar el archivo si la escritura falló
        unlink(template);
        return NULL;
    }
    
    // Asignar memoria para el nombre del archivo
    char* filename = malloc(strlen(template) + 1);
    if (filename == NULL) {
        // Liberar recursos en caso de error de asignación
        unlink(template);
        return NULL;
    }
    
    // Copiar el nombre del archivo
    strcpy(filename, template);
    
    return filename;
}