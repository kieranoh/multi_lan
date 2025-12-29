#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

/* Donat un buffer ja omplert amb un prefix, llegeix el contingut d'un fitxer i afegeix-lo al buffer. A continuació, copia tot el buffer a un altre buffer (out).

@param filename: el nom del fitxer a llegir
@param out: el buffer on copiar el contingut
@param buf: el buffer on llegir el contingut del fitxer
@param BUF_SIZE: la mida del buffer */
void copy_file_content(const char *filename, char* out, char* buf, const int BUF_SIZE) {
    int fd = open(filename, O_RDONLY);
    if (fd < 0) {
        perror("Error opening file");
        return;
    }

    // Estableix el prefix en buf
    const char *prefix = "File content: ";
    strncpy(buf, prefix, BUF_SIZE);
    
    // Llegeix el contingut del fitxer al buf a partir de l'offset de la longitud del prefix
    int remaining = BUF_SIZE - strlen(prefix) - 1; // Espai per a la terminació nula
    int count = read(fd, buf + strlen(prefix), remaining);
    if (count < 0) {
        perror("Error reading file");
        close(fd);
        return;
    }

    // Assegura't que el buffer estigui ben terminat
    buf[strlen(prefix) + count] = '\0';

    // Copia tot el contingut de buf a out
    strncpy(out, buf, BUF_SIZE);

    close(fd);
}