#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

/* Étant donné un tampon déjà rempli avec un préfixe, lire le contenu d'un fichier et l'ajouter au tampon. Ensuite, copier tout le tampon dans un autre tampon (out).

@param filename: le nom du fichier à lire
@param out: le tampon dans lequel copier le contenu
@param buf: le tampon dans lequel lire le contenu du fichier
@param BUF_SIZE: la taille du tampon */
void copy_file_content(const char *filename, char* out, char* buf, const int BUF_SIZE) {
    int fd = open(filename, O_RDONLY);
    if (fd < 0) {
        perror("Error opening file");
        return;
    }
    
    // strlen("Contenu du fichier: ") == 14
    // buf = "Contenu du fichier: <...espace inutilisé...>"
    // lire le contenu du fichier dans buf à l'offset 14
    
    // Copier le préfixe dans le buffer
    strcpy(buf, "Contenu du fichier: ");
    
    int remaining = BUF_SIZE - 14;
    int count = read(fd, buf + 14, remaining);
    if (count < 0) {
        perror("Error reading file");
        close(fd);
        return;
    }
    
    // Assurer la terminaison nulle si possible
    int total_length = 14 + count;
    if (total_length < BUF_SIZE) {
        buf[total_length] = '\0';
    } else if (BUF_SIZE > 0) {
        buf[BUF_SIZE - 1] = '\0';
    }
    
    // copier tout le contenu de buf dans out
    strncpy(out, buf, BUF_SIZE);
    if (BUF_SIZE > 0) {
        out[BUF_SIZE - 1] = '\0';
    }
    
    close(fd);
}