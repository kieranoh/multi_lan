#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *read_file_from_dir(const char *filename, const char *dir_path) {
    // Construir la ruta completa del archivo
    size_t path_length = strlen(dir_path) + strlen(filename) + 2; // 1 para '/' y 1 para '\0'
    char *full_path = malloc(path_length);
    if (!full_path) {
        return NULL; // Error en la asignación de memoria
    }
    
    snprintf(full_path, path_length, "%s/%s", dir_path, filename);

    // Abrir el archivo para lectura
    FILE *file = fopen(full_path, "r");
    free(full_path); // Liberar la ruta completa, ya no la necesitamos
    
    if (!file) {
        return strdup(""); // Error al abrir el archivo, devolver cadena vacía
    }

    // Leer el contenido del archivo
    fseek(file, 0, SEEK_END); // Ir al final del archivo
    long length = ftell(file); // Obtener el tamaño del archivo
    fseek(file, 0, SEEK_SET); // Volver al principio del archivo

    // Asignar memoria para el contenido del archivo
    char *content = malloc(length + 1); // +1 para el terminador nulo
    if (!content) {
        fclose(file);
        return NULL; // Error en la asignación de memoria
    }

    // Leer el contenido del archivo
    fread(content, 1, length, file);
    content[length] = '\0'; // Asegurarse de que esté terminada en nulo
    fclose(file); // Cerrar el archivo

    return content; // Devolver el contenido leído
}