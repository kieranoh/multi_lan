#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

void save_secrete_file(const char *directory, const char *filename, const char *content) {
    // Combineer directory en filename om het volledige pad te maken
    char filepath[1024];
    snprintf(filepath, sizeof(filepath), "%s/%s", directory, filename);

    // Open het bestand voor schrijven
    FILE *file = fopen(filepath, "w");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    // Schrijf de inhoud naar het bestand
    fprintf(file, "%s", content);
    fclose(file);

    // Stel de bestandspermissies in, zodat alleen de eigenaar toegang heeft
    if (chmod(filepath, S_IRUSR | S_IWUSR) < 0) {
        perror("Error changing file permissions");
        return;
    }
}