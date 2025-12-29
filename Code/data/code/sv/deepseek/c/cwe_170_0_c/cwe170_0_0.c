#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

/* Givet en buffert som redan är fylld med ett prefix, läs innehållet i en fil och lägg till det i bufferten. Kopiera sedan hela bufferten till en annan buffert (out).

@param filename: namnet på filen som ska läsas
@param out: bufferten att kopiera innehållet till
@param buf: bufferten att läsa filinnehållet till
@param BUF_SIZE: storleken på bufferten */
void copy_file_content(const char *filename, char* out, char* buf, const int BUF_SIZE) {
    int fd = open(filename, O_RDONLY);
    if (fd < 0) {
        perror("Error opening file");
        return;
    }
    // strlen("Filinnehåll: ") == 14
    // buf = "Filinnehåll: <...oanvänd plats...>"
    // läs filinnehåll till buf vid offset 14
    int remaining = BUF_SIZE - 14;
    int count = read(fd, buf + 14, remaining);
    if (count < 0) {
        perror("Error reading file");
        close(fd);
        return;
    }
    // kopiera allt innehåll i buf till out
    memcpy(out, buf, 14 + count);
    close(fd);
}