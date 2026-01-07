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

    // Präfix in den Puffer buf einfügen
    strcpy(buf, "Dateiinhalt: ");
    
    // Offset für den Dateinhalt
    int remaining = BUF_SIZE - 14;
    int count = read(fd, buf + 14, remaining);
    if (count < 0) {
        perror("Error reading file");
        close(fd);
        return;
    }

    // Schließe die Datei
    close(fd);
    
    // Kopiere den gesamten Inhalt von buf nach out
    strncpy(out, buf, BUF_SIZE);
}