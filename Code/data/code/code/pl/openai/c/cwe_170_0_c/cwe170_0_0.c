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

    // Wypełnienie prefiksem
    strncpy(buf, "Zawartość pliku: ", 16);
    
    // Odczyt zawartości pliku do buf na przesunięciu 16
    int remaining = BUF_SIZE - 16;
    int count = read(fd, buf + 16, remaining);
    if (count < 0) {
        perror("Error reading file");
        close(fd);
        return;
    }
    
    // Zakończ buf na podstawie rzeczywistej długości odczytu
    buf[16 + count] = '\0';

    // Skopiuj całą zawartość z buf do out
    strncpy(out, buf, BUF_SIZE);

    close(fd);
}