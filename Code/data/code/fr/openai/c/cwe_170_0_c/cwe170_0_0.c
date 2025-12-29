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

    // Préfixe à ajouter dans le tampon
    const char* prefix = "Contenu du fichier: ";
    strcpy(buf, prefix);  // Copier le préfixe dans buf
    int offset = strlen(prefix);
    
    // Lire le contenu du fichier dans buf à l'offset approprié
    int remaining = BUF_SIZE - offset;
    int count = read(fd, buf + offset, remaining);
    if (count < 0) {
        perror("Error reading file");
        close(fd);
        return;
    }
    
    // Copier tout le contenu de buf dans out
    strcpy(out, buf);
    
    close(fd);
}