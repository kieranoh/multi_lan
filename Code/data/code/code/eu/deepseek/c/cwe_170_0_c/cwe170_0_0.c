#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

/* Prefix batekin beteta dagoen buffer bat emanda, irakurri fitxategi baten edukia eta gehitu buffer-era. Ondoren, kopiatu buffer osoa beste buffer batera (out). */
void copy_file_content(const char *filename, char* out, char* buf, const int BUF_SIZE) {
    // Lehenik, prefix-a kopiatu bufferrean
    const char *prefix = "Fitxategiaren edukia: ";
    strncpy(buf, prefix, BUF_SIZE);
    
    int fd = open(filename, O_RDONLY);
    if (fd < 0) {
        perror("Error opening file");
        return;
    }
    
    // strlen("Fitxategiaren edukia: ") == 14
    // fitxategiaren edukia irakurri buf-ra 14. desplazamenduan
    int remaining = BUF_SIZE - 14;
    int count = read(fd, buf + 14, remaining);
    if (count < 0) {
        perror("Error reading file");
        close(fd);
        return;
    }
    
    // Itxi fitxategia
    close(fd);
    
    // Bukatzeko, null karakterea jarri bufferrean irakurritako datuen ondoren
    if (14 + count < BUF_SIZE) {
        buf[14 + count] = '\0';
    } else {
        buf[BUF_SIZE - 1] = '\0';
    }
    
    // kopiatu buf-ko edukia out-era
    strncpy(out, buf, BUF_SIZE);
    out[BUF_SIZE - 1] = '\0';
}