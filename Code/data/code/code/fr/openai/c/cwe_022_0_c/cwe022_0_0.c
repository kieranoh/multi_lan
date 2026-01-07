#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *read_file_from_dir(const char *filename, const char *dir_path) {
    // Construction du chemin complet du fichier
    size_t path_length = strlen(dir_path) + strlen(filename) + 2; // +2 pour '/' et '\0'
    char *full_path = malloc(path_length);
    if (full_path == NULL) {
        return ""; // En cas d'échec d'allocation, retourner une chaîne vide
    }
    snprintf(full_path, path_length, "%s/%s", dir_path, filename);
    
    // Ouverture du fichier
    FILE *file = fopen(full_path, "r");
    free(full_path); // Libération de la mémoire utilisée pour full_path
    if (file == NULL) {
        return ""; // Retourner une chaîne vide en cas d'erreur d'ouverture
    }

    // Lecture du contenu du fichier
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);
    
    char *content = malloc(file_size + 1); // +1 pour le caractère nul de fin
    if (content == NULL) {
        fclose(file);
        return ""; // Retourner une chaîne vide en cas d'échec d'allocation
    }

    fread(content, 1, file_size, file);
    content[file_size] = '\0'; // Ajout du caractère nul à la fin
    fclose(file);

    return content; // Retourner le contenu du fichier
}