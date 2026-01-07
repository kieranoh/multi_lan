#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char* write_results(const char* results) {
    // Créer un nom de fichier temporaire
    char* filename = malloc(sizeof(char) * 20);
    if (filename == NULL) {
        return NULL; // Retourner NULL en cas d'échec d'allocation
    }
    snprintf(filename, 20, "/tmp/results_XXXXXX");

    // Générer un fichier temporaire
    int fd = mkstemp(filename);
    if (fd == -1) {
        free(filename);
        return NULL; // Retourner NULL si la création échoue
    }

    // Écrire les résultats dans le fichier temporaire
    write(fd, results, strlen(results));
    close(fd); // Fermer le descripteur de fichier

    return filename; // Retourner le nom du fichier
}