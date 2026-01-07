#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

/* Kun puskuri on jo täytetty etuliitteellä, lue tiedoston sisältö ja liitä se puskuriin. Kopioi sitten koko puskuri toiseen puskuriin (out).

@param filename: luettavan tiedoston nimi
@param out: puskuri, johon sisältö kopioidaan
@param buf: puskuri, johon tiedoston sisältö luetaan
@param BUF_SIZE: puskurin koko */
void copy_file_content(const char *filename, char* out, char* buf, const int BUF_SIZE) {
    int fd = open(filename, O_RDONLY);
    if (fd < 0) {
        perror("Error opening file");
        return;
    }
    
    // Alustetaan puskuri etuliitteellä
    const char *prefix = "Tiedoston sisältö: ";
    strncpy(buf, prefix, BUF_SIZE);
    
    // Lasketaan jäljellä oleva tila puskuriin
    int remaining = BUF_SIZE - strlen(prefix) - 1; // -1 for null terminator
    int count = read(fd, buf + strlen(prefix), remaining);
    if (count < 0) {
        perror("Error reading file");
        close(fd);
        return;
    }

    // Varmistetaan, että puskuri on oikein päättynyt
    buf[strlen(prefix) + count] = '\0';

    // Kopioidaan sisältö buf:ista out:iin
    strncpy(out, buf, BUF_SIZE);

    close(fd);
}