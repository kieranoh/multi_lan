#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

void save_secrete_file(const char *directory, const char *filename, const char *content) {
    // Crear la ruta completa para el archivo
    char filepath[512];
    snprintf(filepath, sizeof(filepath), "%s/%s", directory, filename);

    // Abrir el archivo en modo de escritura
    FILE *file = fopen(filepath, "w");
    if (file == NULL) {
        perror("Error al abrir el archivo");
        return;
    }

    // Escribir el contenido en el archivo
    fprintf(file, "%s", content);
    fclose(file);

    // Cambiar los permisos del archivo para que solo el usuario actual pueda acceder
    if (chmod(filepath, S_IRUSR | S_IWUSR) != 0) {
        perror("Error al cambiar los permisos del archivo");
    }
}