#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

void save_secrete_file(const char *directory, const char *filename, const char *content) {
    char path[1024];
    struct stat st;

    // Ellenőrizzük, hogy a megadott könyvtár létezik-e
    if (stat(directory, &st) != 0 || !S_ISDIR(st.st_mode)) {
        fprintf(stderr, "A megadott könyvtár nem létezik.\n");
        return;
    }

    // Készítsük el a fájl teljes elérési útját
    snprintf(path, sizeof(path), "%s/%s", directory, filename);

    // Nyissuk meg a fájlt írásra
    FILE *file = fopen(path, "w");
    if (file == NULL) {
        perror("A fájl megnyitása nem sikerült");
        return;
    }

    // Írjuk bele a tartalmat a fájlba
    fprintf(file, "%s", content);

    // Zárjuk be a fájlt
    fclose(file);

    // A fájl jogosultságainak beállítása, hogy csak a tulajdonos férhessen hozzá
    chmod(path, S_IRUSR | S_IWUSR);
}