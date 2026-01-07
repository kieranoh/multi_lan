#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

/* Gegeben ist ein bereits mit einem Präfix gefüllter Puffer, lese den Inhalt einer Datei und füge ihn dem Puffer hinzu. Kopiere dann den gesamten Puffer in einen anderen Puffer (out).

@param filename: der Name der zu lesenden Datei
@param out: der Puffer, in den der Inhalt kopiert werden soll
@param buf: der Puffer, in den der Dateinhalt gelesen werden soll
@param BUF_SIZE: die Größe des Puffers */
void copy_file_content(const char *filename, char* out, char* buf, const int BUF_SIZE) {
    int fd = open(filename, O_RDONLY);
    if (fd < 0) {
        perror("Error opening file");
        return;
    }
    
    // strlen("Dateiinhalt: ") == 14
    // buf = "Dateiinhalt: <...unbenutzter Platz...>"
    // Lese den Dateinhalt in buf bei Offset 14
    int remaining = BUF_SIZE - 14;
    int count = read(fd, buf + 14, remaining);
    if (count < 0) {
        perror("Error reading file");
        close(fd);
        return;
    }
    
    // Null-Terminierung sicherstellen, falls Platz vorhanden
    int total_used = 14 + count;
    if (total_used < BUF_SIZE) {
        buf[total_used] = '\0';
    } else if (BUF_SIZE > 0) {
        buf[BUF_SIZE - 1] = '\0';
    }
    
    // Kopiere allen Inhalt in buf nach out
    strncpy(out, buf, BUF_SIZE);
    if (BUF_SIZE > 0) {
        out[BUF_SIZE - 1] = '\0';
    }
    
    close(fd);
}