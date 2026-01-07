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
    // strlen("File content: ") == 14
    // buf = "File content: <...unused space...>"
    // read file content to buf at offset 14
    int remaining = BUF_SIZE - 14;
    int count = read(fd, buf + 14, remaining);
    if (count < 0) {
        perror("Error reading file");
        close(fd);
        return;
    }
    // copia tot el contingut de buf a out
    memcpy(out, buf, 14 + count);
    close(fd);
}