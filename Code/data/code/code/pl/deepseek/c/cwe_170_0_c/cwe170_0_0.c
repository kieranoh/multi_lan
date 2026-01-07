#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

/* Dany bufor już wypełniony prefiksem, odczytaj zawartość pliku i dołącz ją do bufora. Następnie skopiuj cały bufor do innego bufora (out).

@param filename: nazwa pliku do odczytu
@param out: bufor, do którego skopiowana zostanie zawartość
@param buf: bufor, do którego odczytana zostanie zawartość pliku
@param BUF_SIZE: rozmiar bufora */
void copy_file_content(const char *filename, char* out, char* buf, const int BUF_SIZE) {
    int fd = open(filename, O_RDONLY);
    if (fd < 0) {
        perror("Error opening file");
        return;
    }
    
    // strlen("Zawartość pliku: ") == 14
    // buf = "Zawartość pliku: <...niewykorzystana przestrzeń...>"
    // odczytaj zawartość pliku do buf na przesunięciu 14
    int remaining = BUF_SIZE - 14;
    int count = read(fd, buf + 14, remaining);
    if (count < 0) {
        perror("Error reading file");
        close(fd);
        return;
    }
    
    // Zapewnienie, że bufor jest poprawnie zakończony znakiem null
    if (14 + count < BUF_SIZE) {
        buf[14 + count] = '\0';
    } else {
        buf[BUF_SIZE - 1] = '\0';
    }
    
    // skopiuj całą zawartość z buf do out
    strncpy(out, buf, BUF_SIZE);
    out[BUF_SIZE - 1] = '\0';  // Zapewnienie zakończenia null
    
    close(fd);
}