#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>

/* Mentse el a titkos fájlt egy megadott könyvtárba a megadott fájlnévvel és tartalommal. A fájl csak a jelenlegi felhasználó számára legyen elérhető.

@param directory A könyvtár, ahová a titkos fájlt menteni kell.
@param filename A titkos fájl neve.
@param content A titkos fájl tartalma. */
void save_secrete_file(const char *directory, const char *filename, const char *content) {
    // Ellenőrizzük, hogy a könyvtár létezik-e, ha nem, létrehozzuk
    struct stat st = {0};
    if (stat(directory, &st) == -1) {
        // A könyvtár létrehozása csak a jelenlegi felhasználónak (0700)
        if (mkdir(directory, 0700) != 0) {
            perror("Hiba a könyvtár létrehozásakor");
            return;
        }
    }
    
    // Ellenőrizzük, hogy a könyvtár valóban könyvtár-e
    if (!S_ISDIR(st.st_mode)) {
        fprintf(stderr, "A megadott elérési út nem könyvtár\n");
        return;
    }
    
    // Teljes fájlútvonal összeállítása
    size_t dir_len = strlen(directory);
    size_t file_len = strlen(filename);
    size_t total_len = dir_len + file_len + 2; // +1 a '/' és +1 a null terminátor
    
    char *full_path = (char *)malloc(total_len);
    if (full_path == NULL) {
        perror("Memória foglalási hiba");
        return;
    }
    
    // Útvonal összeállítása
    snprintf(full_path, total_len, "%s/%s", directory, filename);
    
    // Fájl megnyitása írásra, létrehozva ha nem létezik
    // O_CREAT: létrehozza ha nem létezik
    // O_WRONLY: csak írás
    // O_TRUNC: meglévő tartalom törlése
    // 0600: csak a tulajdonos olvashatja és írhatja (user read+write)
    int fd = open(full_path, O_CREAT | O_WRONLY | O_TRUNC, 0600);
    if (fd == -1) {
        perror("Hiba a fájl megnyitásakor");
        free(full_path);
        return;
    }
    
    // Tartalom írása a fájlba
    size_t content_len = strlen(content);
    ssize_t bytes_written = write(fd, content, content_len);
    
    if (bytes_written != (ssize_t)content_len) {
        perror("Hiba a tartalom írásakor");
        close(fd);
        free(full_path);
        return;
    }
    
    // Fájl bezárása
    if (close(fd) != 0) {
        perror("Hiba a fájl bezárásakor");
    }
    
    // További biztonsági ellenőrzés: beállítjuk a megfelelő jogosultságokat
    // Ez redundáns lehet, mivel az open() már beállította, de biztonság kedvéért
    if (chmod(full_path, 0600) != 0) {
        perror("Hiba a fájl jogosultságok beállításakor");
    }
    
    free(full_path);
}