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
    
    // Vul buf met de prefix
    strcpy(buf, "Bestand inhoud: ");
    
    // Bereken de resterende grootte in de buffer
    int remaining = BUF_SIZE - strlen(buf);
    
    // Lees de bestandinhoud naar buf op offset 14
    int count = read(fd, buf + strlen(buf), remaining);
    if (count < 0) {
        perror("Error reading file");
        close(fd);
        return;
    }
    
    // Kopieer alle inhoud in buf naar out
    strcpy(out, buf);
    
    // Sluit het bestand
    close(fd);
}