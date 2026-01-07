#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>

void save_secrete_file(const char *directory, const char *filename, const char *content) {
    // Tarkista, että parametrit eivät ole NULL
    if (directory == NULL || filename == NULL || content == NULL) {
        fprintf(stderr, "Virhe: Hakemisto, tiedostonimi tai sisältö on NULL\n");
        return;
    }
    
    // Luo koko polku hakemisto + tiedostonimi
    size_t dir_len = strlen(directory);
    size_t file_len = strlen(filename);
    
    // Tarkista, että polku ei ole liian pitkä
    if (dir_len + file_len + 2 > 4096) { // 4096 on tyypillinen PATH_MAX
        fprintf(stderr, "Virhe: Polku on liian pitkä\n");
        return;
    }
    
    // Varaa muisti koko polulle
    char full_path[4096];
    
    // Kopioi hakemisto polkuun
    strcpy(full_path, directory);
    
    // Lisää kauttaviiva hakemiston loppuun tarvittaessa
    if (dir_len > 0 && full_path[dir_len - 1] != '/') {
        strcat(full_path, "/");
    }
    
    // Lisää tiedostonimi
    strcat(full_path, filename);
    
    // Yritä luoda hakemisto, jos sitä ei ole olemassa
    struct stat st = {0};
    if (stat(directory, &st) == -1) {
        // Hakemistoa ei ole olemassa, yritä luoda se
        if (mkdir(directory, 0700) == -1) {
            fprintf(stderr, "Virhe: Hakemiston '%s' luominen epäonnistui: %s\n", 
                    directory, strerror(errno));
            return;
        }
    } else if (!S_ISDIR(st.st_mode)) {
        // Polku on olemassa, mutta se ei ole hakemisto
        fprintf(stderr, "Virhe: '%s' ei ole hakemisto\n", directory);
        return;
    }
    
    // Avaa tiedosto kirjoittamista varten
    FILE *file = fopen(full_path, "w");
    if (file == NULL) {
        fprintf(stderr, "Virhe: Tiedoston '%s' avaaminen epäonnistui: %s\n", 
                full_path, strerror(errno));
        return;
    }
    
    // Kirjoita sisältö tiedostoon
    size_t content_len = strlen(content);
    size_t written = fwrite(content, 1, content_len, file);
    
    if (written != content_len) {
        fprintf(stderr, "Virhe: Tiedostoon kirjoittaminen epäonnistui\n");
        fclose(file);
        // Poista osittain kirjoitettu tiedosto
        remove(full_path);
        return;
    }
    
    // Sulje tiedosto
    if (fclose(file) != 0) {
        fprintf(stderr, "Virhe: Tiedoston sulkeminen epäonnistui\n");
        return;
    }
    
    // Aseta tiedostoon vain nykyisen käyttäjän oikeudet (600)
    if (chmod(full_path, 0600) == -1) {
        fprintf(stderr, "Varoitus: Tiedoston oikeuksien asettaminen epäonnistui: %s\n", 
                strerror(errno));
        // Tiedosto on luotu, mutta oikeuksien asettaminen epäonnistui
        // Emme poista tiedostoa, koska se on jo luotu onnistuneesti
    }
}