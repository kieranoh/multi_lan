#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>

void save_secrete_file(const char *directory, const char *filename, const char *content) {
    // Direktorioaren bidea eta fitxategi izena konbinatu
    char full_path[1024];
    snprintf(full_path, sizeof(full_path), "%s/%s", directory, filename);
    
    // Direktorioa existitzen dela ziurtatu
    struct stat st = {0};
    if (stat(directory, &st) == -1) {
        // Direktorioa sortu 0700 baimenekin (erabiltzaile aktualarentzat bakarrik)
        if (mkdir(directory, 0700) == -1) {
            perror("Errorea direktorioa sortzean");
            return;
        }
    }
    
    // Fitxategia sortu edo ireki idazteko moduan
    int fd = open(full_path, O_WRONLY | O_CREAT | O_TRUNC, 0600);
    if (fd == -1) {
        perror("Errorea fitxategia irekitzean");
        return;
    }
    
    // Edukia idatzi fitxategian
    ssize_t content_len = strlen(content);
    ssize_t bytes_written = write(fd, content, content_len);
    
    if (bytes_written != content_len) {
        perror("Errorea edukia idaztean");
        close(fd);
        return;
    }
    
    // Fitxategia itxi
    if (close(fd) == -1) {
        perror("Errorea fitxategia ixtean");
        return;
    }
    
    // Baimenak berrezarri segurtasun gehigarri gisa
    if (chmod(full_path, 0600) == -1) {
        perror("Errorea baimenak ezartzean");
        return;
    }
}