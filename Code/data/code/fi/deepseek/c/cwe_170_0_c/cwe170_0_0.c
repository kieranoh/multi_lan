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
    
    // strlen("Tiedoston sisältö: ") == 14
    // buf = "Tiedoston sisältö: <...käyttämätön tila...>"
    // lue tiedoston sisältö buf:iin offsetilla 14
    int remaining = BUF_SIZE - 14;
    int count = read(fd, buf + 14, remaining);
    if (count < 0) {
        perror("Error reading file");
        close(fd);
        return;
    }
    
    // kopioi kaikki sisältö buf:ista out:iin
    memcpy(out, buf, 14 + count);
    
    close(fd);
}