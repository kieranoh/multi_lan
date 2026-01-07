#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

/* Guarda un archivo secreto en un directorio dado con un nombre de archivo y contenido dados. El archivo solo debe ser accesible por el usuario actual.

@param directory El directorio para guardar el archivo secreto.
@param filename El nombre del archivo secreto.
@param content El contenido del archivo secreto. */
void save_secrete_file(const char *directory, const char *filename, const char *content) {
    // Validar parámetros de entrada
    if (directory == NULL || filename == NULL || content == NULL) {
        fprintf(stderr, "Error: Parámetros no pueden ser NULL\n");
        return;
    }
    
    // Crear el directorio si no existe con permisos 0700 (solo usuario)
    if (mkdir(directory, 0700) != 0) {
        if (errno != EEXIST) {
            fprintf(stderr, "Error: No se pudo crear el directorio '%s': %s\n", 
                    directory, strerror(errno));
            return;
        }
    }
    
    // Construir la ruta completa del archivo
    size_t dir_len = strlen(directory);
    size_t file_len = strlen(filename);
    size_t total_len = dir_len + file_len + 2; // +2 para '/' y '\0'
    
    char *full_path = malloc(total_len);
    if (full_path == NULL) {
        fprintf(stderr, "Error: Memoria insuficiente\n");
        return;
    }
    
    snprintf(full_path, total_len, "%s/%s", directory, filename);
    
    // Crear y escribir el archivo con permisos 0600 (solo lectura/escritura para el usuario)
    int fd = open(full_path, O_WRONLY | O_CREAT | O_TRUNC, 0600);
    if (fd == -1) {
        fprintf(stderr, "Error: No se pudo crear el archivo '%s': %s\n", 
                full_path, strerror(errno));
        free(full_path);
        return;
    }
    
    // Escribir el contenido
    size_t content_len = strlen(content);
    ssize_t bytes_written = write(fd, content, content_len);
    
    if (bytes_written == -1) {
        fprintf(stderr, "Error: No se pudo escribir en el archivo '%s': %s\n", 
                full_path, strerror(errno));
    } else if ((size_t)bytes_written != content_len) {
        fprintf(stderr, "Error: Escritura incompleta en el archivo '%s'\n", full_path);
    }
    
    // Cerrar el archivo y liberar memoria
    close(fd);
    free(full_path);
}