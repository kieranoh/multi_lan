#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *read_file_from_dir(const char *filename, const char *dir_path) {
    // Combinem el camí del directori amb el nom del fitxer
    size_t path_len = strlen(dir_path) + strlen(filename) + 2; // +2 per '/' i '\0'
    char *full_path = malloc(path_len);
    if (!full_path) {
        return ""; // Retornem cadena buida si no es pot al·locar memòria
    }
    snprintf(full_path, path_len, "%s/%s", dir_path, filename);
    
    // Obrim el fitxer per lectura
    FILE *file = fopen(full_path, "r");
    free(full_path); // Alliberem la memòria del camí complet

    if (!file) {
        return ""; // Retornem cadena buida si no s'ha pogut obrir el fitxer
    }

    // Anem a llegir el contingut del fitxer
    fseek(file, 0, SEEK_END); // Anem al final del fitxer
    long file_size = ftell(file); // Obtenim la mida del fitxer
    fseek(file, 0, SEEK_SET); // Tornem al principi del fitxer

    // Al·locar memòria per al contingut del fitxer
    char *content = malloc(file_size + 1); // +1 per '\0'
    if (!content) {
        fclose(file);
        return ""; // Retornem cadena buida si no es pot al·locar memòria
    }

    fread(content, 1, file_size, file); // Llegim el fitxer
    content[file_size] = '\0'; // Afegim el terminador de cadena

    fclose(file); // Tanquem el fitxer
    return content; // Retornem el contingut llegit
}