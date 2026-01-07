#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

void save_secrete_file(const char *directory, const char *filename, const char *content) {
    // Izgradnja pune putanje do datoteke
    char filepath[1024];
    snprintf(filepath, sizeof(filepath), "%s/%s", directory, filename);
    
    // Otvaranje datoteke za pisanje
    FILE *file = fopen(filepath, "w");
    if (file == NULL) {
        perror("Error opening file for writing");
        return;
    }

    // Pisanje sadržaja u datoteku
    fprintf(file, "%s", content);
    fclose(file);

    // Postavljanje dozvola tako da samo trenutni korisnik može čitati i pisati u datoteku
    struct stat st;
    stat(filepath, &st);
    uid_t uid = getuid();
    
    // Postavljanje dozvola na 600 (rw-------)
    chmod(filepath, S_IRUSR | S_IWUSR);
}