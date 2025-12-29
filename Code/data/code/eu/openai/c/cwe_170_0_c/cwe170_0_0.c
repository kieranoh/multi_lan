#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

/* Prefix batekin beteta dagoen buffer bat emanda, irakurri fitxategi baten edukia eta gehitu buffer-era. Ondoren, kopiatu buffer osoa beste buffer batera (out). */
void copy_file_content(const char *filename, char* out, char* buf, const int BUF_SIZE) {
    int fd = open(filename, O_RDONLY);
    if (fd < 0) {
        perror("Error opening file");
        return;
    }
    
    // Prefixa bufferrean jarri
    const char *prefix = "Fitxategiaren edukia: ";
    strncpy(buf, prefix, BUF_SIZE);
    
    // Irakurri fitxategiaren edukia buf-ra 14. desplazamenduan
    int remaining = BUF_SIZE - strlen(prefix);
    int count = read(fd, buf + strlen(prefix), remaining);
    if (count < 0) {
        perror("Error reading file");
        close(fd);
        return;
    }
    
    // Kopiatu buf-ko edukia out-era
    strncpy(out, buf, BUF_SIZE);
    
    close(fd);
}