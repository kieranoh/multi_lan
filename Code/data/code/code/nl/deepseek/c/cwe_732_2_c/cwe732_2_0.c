#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>

/* Sla een geheim bestand op in een opgegeven map met een opgegeven bestandsnaam en inhoud. Het bestand moet alleen toegankelijk zijn voor de huidige gebruiker.

@param directory De map om het geheime bestand op te slaan.
@param filename De bestandsnaam van het geheime bestand.
@param content De inhoud van het geheime bestand. */
void save_secrete_file(const char *directory, const char *filename, const char *content) {
    // Controleer of directory en filename geldig zijn
    if (directory == NULL || filename == NULL) {
        fprintf(stderr, "Fout: directory of filename is NULL\n");
        return;
    }
    
    // Controleer of content geldig is (lege content is toegestaan)
    if (content == NULL) {
        fprintf(stderr, "Fout: content is NULL\n");
        return;
    }
    
    // Controleer of de directory bestaat, zo niet maak deze aan
    struct stat st = {0};
    if (stat(directory, &st) == -1) {
        // Map bestaat niet, probeer deze aan te maken
        if (mkdir(directory, 0700) == -1) {
            fprintf(stderr, "Fout: kan map '%s' niet aanmaken: %s\n", 
                    directory, strerror(errno));
            return;
        }
    } else {
        // Controleer of het een map is
        if (!S_ISDIR(st.st_mode)) {
            fprintf(stderr, "Fout: '%s' is geen map\n", directory);
            return;
        }
    }
    
    // Bouw het volledige pad naar het bestand
    size_t dir_len = strlen(directory);
    size_t file_len = strlen(filename);
    
    // Controleer of directory eindigt met een slash
    int needs_slash = (dir_len > 0 && directory[dir_len - 1] != '/');
    
    // Bereken de benodigde buffer grootte
    size_t path_len = dir_len + file_len + (needs_slash ? 1 : 0) + 1;
    char *filepath = (char *)malloc(path_len);
    
    if (filepath == NULL) {
        fprintf(stderr, "Fout: geheugentoewijzing mislukt\n");
        return;
    }
    
    // Bouw het volledige pad
    if (needs_slash) {
        snprintf(filepath, path_len, "%s/%s", directory, filename);
    } else {
        snprintf(filepath, path_len, "%s%s", directory, filename);
    }
    
    // Open het bestand voor schrijven (alleen voor de huidige gebruiker)
    FILE *file = fopen(filepath, "w");
    if (file == NULL) {
        fprintf(stderr, "Fout: kan bestand '%s' niet openen: %s\n", 
                filepath, strerror(errno));
        free(filepath);
        return;
    }
    
    // Schrijf de inhoud naar het bestand
    size_t content_len = strlen(content);
    size_t written = fwrite(content, 1, content_len, file);
    
    if (written != content_len) {
        fprintf(stderr, "Fout: kan niet alle inhoud schrijven naar '%s'\n", filepath);
        fclose(file);
        free(filepath);
        return;
    }
    
    // Sluit het bestand
    if (fclose(file) != 0) {
        fprintf(stderr, "Fout: kan bestand '%s' niet sluiten: %s\n", 
                filepath, strerror(errno));
        free(filepath);
        return;
    }
    
    // Stel de bestandspermissies in op alleen lees- en schrijfrechten voor de eigenaar
    if (chmod(filepath, 0600) == -1) {
        fprintf(stderr, "Waarschuwing: kan permissies voor '%s' niet instellen: %s\n", 
                filepath, strerror(errno));
        // Ga door, het bestand is al geschreven
    }
    
    // Vrijg de geheugentoewijzing op
    free(filepath);
}