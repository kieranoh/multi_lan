#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

void save_secrete_file(const char *directory, const char *filename, const char *content) {
    // Luo täydellinen polku tiedostolle
    char *filepath = malloc(strlen(directory) + strlen(filename) + 2);
    if (filepath == NULL) {
        perror("malloc failed");
        return;
    }
    sprintf(filepath, "%s/%s", directory, filename);

    // Luo tiedosto kirjoitusta varten
    FILE *file = fopen(filepath, "w");
    if (file == NULL) {
        perror("fopen failed");
        free(filepath);
        return;
    }

    // Kirjoita sisältö tiedostoon
    fprintf(file, "%s", content);
    fclose(file);

    // Muuta tiedoston käyttöoikeuksia niin, että vain omistaja voi lukea ja kirjoittaa
    struct stat st;
    if (stat(filepath, &st) == 0) {
        // Aseta vain omistajalle luku- ja kirjoitusoikeus
        mode_t mode = st.st_mode & ~S_IRGRP & ~S_IWGRP & ~S_IROTH & ~S_IWOTH;
        chmod(filepath, mode);
    }

    free(filepath);
}