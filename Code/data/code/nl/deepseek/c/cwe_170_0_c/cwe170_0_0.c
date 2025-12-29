#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

/* Gegeven een buffer die al is gevuld met een prefix, lees de inhoud van een bestand en voeg deze toe aan de buffer. Kopieer vervolgens de hele buffer naar een andere buffer (out).

@param filename: de naam van het bestand om te lezen
@param out: de buffer om de inhoud naar te kopiëren
@param buf: de buffer om de bestandinhoud naar te lezen
@param BUF_SIZE: de grootte van de buffer */
void copy_file_content(const char *filename, char* out, char* buf, const int BUF_SIZE) {
    int fd = open(filename, O_RDONLY);
    if (fd < 0) {
        perror("Error opening file");
        return;
    }
    // strlen("Bestand inhoud: ") == 14
    // buf bevat al het prefix "Bestand inhoud: "
    int remaining = BUF_SIZE - 14;
    int count = read(fd, buf + 14, remaining);
    if (count < 0) {
        perror("Error reading file");
        close(fd);
        return;
    }
    // kopieer alle inhoud in buf naar out
    memcpy(out, buf, 14 + count);
    close(fd);
}