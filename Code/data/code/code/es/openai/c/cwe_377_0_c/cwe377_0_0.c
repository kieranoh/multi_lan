#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char* write_results(const char* results) {
    // Crear un archivo temporal
    char* filename = malloc(L_tmpnam);
    if (filename == NULL) {
        return NULL; // Manejo de error: no se pudo asignar memoria
    }
    
    // Generar un nombre de archivo temporal
    tmpnam(filename);
    
    // Abrir el archivo temporal para escritura
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        free(filename); // Liberar memoria en caso de error
        return NULL; // Manejo de error: no se pudo abrir el archivo
    }
    
    // Escribir el contenido proporcionado en el archivo
    fprintf(file, "%s", results);
    
    // Cerrar el archivo
    fclose(file);
    
    // Devolver el nombre del archivo
    return filename;
}