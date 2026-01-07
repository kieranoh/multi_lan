#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *read_file_from_dir(const char *filename, const char *dir_path) {
    // Luo täydellinen polku tiedostolle
    size_t path_length = strlen(dir_path) + strlen(filename) + 2; // +2 for '/' and NULL terminator
    char *full_path = (char *)malloc(path_length);
    if (full_path == NULL) {
        return ""; // Muistin varaus epäonnistui
    }

    snprintf(full_path, path_length, "%s/%s", dir_path, filename);

    // Avaa tiedosto lukemista varten
    FILE *file = fopen(full_path, "r");
    free(full_path); // Vapauta full_path muisti, koska emme tarvitse sitä enää

    if (file == NULL) {
        return ""; // Tiedoston avaus epäonnistui
    }

    // Siirry tiedoston loppuun saadaksesi sen pituuden
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET); // Siirry takaisin alkuun

    // Varaa muisti tiedoston sisällölle
    char *content = (char *)malloc(file_size + 1); // +1 NULL terminaattorille
    if (content == NULL) {
        fclose(file);
        return ""; // Muistin varaus epäonnistui
    }

    // Lue tiedoston sisältö
    fread(content, 1, file_size, file);
    content[file_size] = '\0'; // Lisää NULL terminaattori

    fclose(file); // Sulje tiedosto

    return content; // Palauta luettu sisältö
}