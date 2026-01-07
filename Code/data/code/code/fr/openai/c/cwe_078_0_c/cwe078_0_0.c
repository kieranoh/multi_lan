#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *get_ls_result(const char *dir_path) {
    // Préparer le buffer pour capturer la sortie
    char *result = NULL;
    size_t result_size = 0;
    FILE *fp;
    char path[1035];

    // Construire la commande
    char command[1024];
    snprintf(command, sizeof(command), "ls -l %s 2>/dev/null", dir_path);

    // Ouvrir le processus pour lire la sortie de la commande
    fp = popen(command, "r");
    if (fp == NULL) {
        return ""; // Retourner chaîne vide en cas d'erreur
    }

    // Lire la sortie ligne par ligne et stocker dans `result`
    while (fgets(path, sizeof(path), fp) != NULL) {
        size_t path_length = strlen(path);
        char *new_result = realloc(result, result_size + path_length + 1);
        if (new_result == NULL) {
            free(result);
            pclose(fp);
            return ""; // Retourner chaîne vide en cas d'erreur de mémoire
        }
        result = new_result;
        strcpy(result + result_size, path);
        result_size += path_length;
    }

    // Fermer le processus
    pclose(fp);
    
    // Si result est NULL, cela signifie qu'il n'y a pas eu de sortie
    if (result == NULL) {
        return ""; // Retourner chaîne vide si rien n'a été capturé
    }

    return result; // Retourner le résultat capturé
}