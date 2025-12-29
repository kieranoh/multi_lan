#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>

void save_secrete_file(const char *directory, const char *filename, const char *content) {
    char filepath[1024];
    struct stat st;
    
    // Kontrola existence adresáře
    if (stat(directory, &st) != 0 || !S_ISDIR(st.st_mode)) {
        fprintf(stderr, "Chyba: Zadaný adresář neexistuje nebo není adresář.\n");
        return;
    }

    // Vytvoření cesty k souboru
    snprintf(filepath, sizeof(filepath), "%s/%s", directory, filename);

    // Otevření souboru pro zápis
    FILE *file = fopen(filepath, "w");
    if (file == NULL) {
        perror("Chyba při otevírání souboru");
        return;
    }

    // Zápis obsahu do souboru
    fprintf(file, "%s", content);
    fclose(file);

    // Změna oprávnění souboru, aby byl přístupný pouze aktuálnímu uživateli
    if (chmod(filepath, S_IRUSR | S_IWUSR) != 0) {
        perror("Chyba při změně oprávnění souboru");
        return;
    }
}