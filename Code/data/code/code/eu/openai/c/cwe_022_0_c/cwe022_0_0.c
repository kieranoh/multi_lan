#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *read_file_from_dir(const char *filename, const char *dir_path) {
    // Fitxategiaren bidea osatu
    size_t path_len = strlen(dir_path) + strlen(filename) + 2; // +2: '/' eta '\0' 
    char *full_path = (char *)malloc(path_len);
    if (full_path == NULL) {
        return NULL; // Memoria eskatu ezinik
    }
    snprintf(full_path, path_len, "%s/%s", dir_path, filename);

    // Fitxategia ireki
    FILE *file = fopen(full_path, "r");
    free(full_path); // full_path erabiltzen ez bada, askatu

    if (file == NULL) {
        return ""; // Fitxategia ezin da irakurri
    }

    // Fitxategiaren edukia irakurri
    fseek(file, 0, SEEK_END);
    long filesize = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *content = (char *)malloc(filesize + 1);
    if (content == NULL) {
        fclose(file);
        return NULL; // Memoria eskatu ezinik
    }

    fread(content, 1, filesize, file);
    content[filesize] = '\0'; // String amaiera

    fclose(file);
    return content; // Edukia itzuli
}