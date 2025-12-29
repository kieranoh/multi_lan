#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *read_file_from_dir(const char *filename, const char *dir_path) {
    // Creiamo il percorso completo del file
    size_t path_len = strlen(dir_path) + strlen(filename) + 2; // +2 per '/' e '\0'
    char *full_path = (char *)malloc(path_len);
    if (full_path == NULL) {
        return NULL; // Errore di allocazione della memoria
    }
    snprintf(full_path, path_len, "%s/%s", dir_path, filename);

    // Apriamo il file
    FILE *file = fopen(full_path, "r");
    free(full_path); // Libera il percorso completo una volta che non ci serve più
    if (file == NULL) {
        return strdup(""); // Restituisci una stringa vuota in caso di errore
    }

    // Andiamo alla fine del file per determinare la dimensione
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    // Allochiamo memoria per il contenuto del file
    char *content = (char *)malloc(file_size + 1);
    if (content == NULL) {
        fclose(file);
        return NULL; // Errore di allocazione della memoria
    }
    
    // Leggiamo il contenuto del file
    fread(content, 1, file_size, file);
    content[file_size] = '\0'; // Aggiungiamo il terminatore di stringa

    // Chiudiamo il file e restituiamo il contenuto
    fclose(file);
    return content;
}