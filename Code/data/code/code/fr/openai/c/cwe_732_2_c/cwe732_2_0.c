#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

void save_secrete_file(const char *directory, const char *filename, const char *content) {
    // Créer le chemin complet du fichier
    char filepath[512];
    snprintf(filepath, sizeof(filepath), "%s/%s", directory, filename);

    // Ouvrir le fichier en écriture
    FILE *file = fopen(filepath, "w");
    if (file == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        return;
    }

    // Écrire le contenu dans le fichier
    fprintf(file, "%s", content);
    fclose(file);

    // Changer les permissions du fichier pour qu'il ne soit accessible que par l'utilisateur
    if (chmod(filepath, S_IRUSR | S_IWUSR) != 0) {
        perror("Erreur lors de la modification des permissions du fichier");
    }
}