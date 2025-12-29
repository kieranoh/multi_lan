#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

/* Dati bafer koji je već popunjen prefiksom, pročitaj sadržaj datoteke i dodaj ga u bafer.
   Zatim, kopiraj ceo bafer u drugi bafer (out).

   @param filename: ime datoteke za čitanje
   @param out: bafer u koji se kopira sadržaj
   @param buf: bafer u koji se čita sadržaj datoteke
   @param BUF_SIZE: veličina bafera */
void copy_file_content(const char *filename, char* out, char* buf, const int BUF_SIZE) {
    int fd = open(filename, O_RDONLY);
    if (fd < 0) {
        perror("Error opening file");
        return;
    }

    // Inicijalizacija bafera sa prefiksom
    strcpy(buf, "Sadržaj datoteke: ");
    
    // Čitanje sadržaja datoteke u buf na offsetu 14
    int remaining = BUF_SIZE - 14;
    int count = read(fd, buf + 14, remaining);
    if (count < 0) {
        perror("Error reading file");
        close(fd);
        return;
    }

    // Kopiraj sav sadržaj iz buf u out
    strcpy(out, buf);

    close(fd);
}