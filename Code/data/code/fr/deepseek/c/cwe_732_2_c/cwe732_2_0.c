#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

/* Enregistrez un fichier secret dans un répertoire donné avec un nom de fichier et un contenu spécifiés. Le fichier ne doit être accessible que par l'utilisateur actuel.

@param directory Le répertoire pour enregistrer le fichier secret.
@param filename Le nom du fichier secret.
@param content Le contenu du fichier secret. */
void save_secrete_file(const char *directory, const char *filename, const char *content) {
    // Vérification des paramètres d'entrée
    if (directory == NULL || filename == NULL || content == NULL) {
        fprintf(stderr, "Erreur : paramètres invalides (NULL)\n");
        return;
    }
    
    // Vérifier si le répertoire existe, sinon le créer
    struct stat st = {0};
    if (stat(directory, &st) == -1) {
        // Le répertoire n'existe pas, essayez de le créer
        if (mkdir(directory, 0700) == -1) {
            fprintf(stderr, "Erreur : impossible de créer le répertoire '%s' : %s\n", 
                    directory, strerror(errno));
            return;
        }
    } else {
        // Vérifier que c'est bien un répertoire
        if (!S_ISDIR(st.st_mode)) {
            fprintf(stderr, "Erreur : '%s' n'est pas un répertoire\n", directory);
            return;
        }
    }
    
    // Construire le chemin complet du fichier
    size_t dir_len = strlen(directory);
    size_t file_len = strlen(filename);
    
    // Vérifier si le répertoire se termine par un séparateur
    int needs_separator = 0;
    if (dir_len > 0 && directory[dir_len - 1] != '/') {
        needs_separator = 1;
    }
    
    // Allouer de la mémoire pour le chemin complet
    char *full_path = malloc(dir_len + file_len + needs_separator + 1);
    if (full_path == NULL) {
        fprintf(stderr, "Erreur : échec d'allocation mémoire\n");
        return;
    }
    
    // Construire le chemin complet
    strcpy(full_path, directory);
    if (needs_separator) {
        strcat(full_path, "/");
    }
    strcat(full_path, filename);
    
    // Ouvrir le fichier avec les permissions restrictives
    // O_CREAT | O_WRONLY | O_TRUNC : créer, écriture seule, écraser si existe
    // 0600 : permissions -rw------- (lecture/écriture uniquement pour le propriétaire)
    int fd = open(full_path, O_CREAT | O_WRONLY | O_TRUNC, 0600);
    if (fd == -1) {
        fprintf(stderr, "Erreur : impossible de créer le fichier '%s' : %s\n", 
                full_path, strerror(errno));
        free(full_path);
        return;
    }
    
    // Écrire le contenu dans le fichier
    size_t content_len = strlen(content);
    ssize_t bytes_written = write(fd, content, content_len);
    
    if (bytes_written == -1) {
        fprintf(stderr, "Erreur : échec d'écriture dans le fichier '%s' : %s\n", 
                full_path, strerror(errno));
        close(fd);
        free(full_path);
        return;
    }
    
    if ((size_t)bytes_written != content_len) {
        fprintf(stderr, "Avertissement : écriture incomplète dans le fichier '%s'\n", 
                full_path);
    }
    
    // Fermer le fichier
    if (close(fd) == -1) {
        fprintf(stderr, "Avertissement : erreur lors de la fermeture du fichier '%s' : %s\n", 
                full_path, strerror(errno));
    }
    
    // Nettoyer
    free(full_path);
}