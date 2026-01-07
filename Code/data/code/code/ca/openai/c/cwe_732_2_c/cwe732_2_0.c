#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

void save_secrete_file(const char *directory, const char *filename, const char *content) {
    // Crear el camí complet del fitxer
    char filepath[1024];
    snprintf(filepath, sizeof(filepath), "%s/%s", directory, filename);

    // Obtenir un descriptor de fitxer per obrir o crear el fitxer
    FILE *file = fopen(filepath, "w");
    if (file == NULL) {
        perror("No es pot obrir el fitxer");
        return;
    }

    // Escriure el contingut al fitxer
    fprintf(file, "%s", content);
    fclose(file);

    // Canviar els permisos del fitxer per fer-lo accessible només pel usuari actual
    if (chmod(filepath, S_IRUSR | S_IWUSR) < 0) {
        perror("No es poden canviar els permisos del fitxer");
    }
}