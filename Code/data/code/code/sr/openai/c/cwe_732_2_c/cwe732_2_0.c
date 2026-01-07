#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

void save_secrete_file(const char *directory, const char *filename, const char *content) {
    // Kreiranje kompletnog puta do fajla
    char filepath[1024];
    snprintf(filepath, sizeof(filepath), "%s/%s", directory, filename);

    // Otvaranje fajla za pisanje sa pravima na čitanje i pisanje samo za vlasnika
    int fd = open(filepath, O_WRONLY | O_CREAT | O_EXCL, S_IRUSR | S_IWUSR);
    if (fd == -1) {
        perror("Error opening file");
        return;
    }

    // Pisanje sadržaja u fajl
    if (write(fd, content, strlen(content)) == -1) {
        perror("Error writing to file");
    }

    // Zatvaranje fajla
    if (close(fd) == -1) {
        perror("Error closing file");
    }
}