#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

void save_secrete_file(const char *directory, const char *filename, const char *content) {
    // Kontrola vstupních parametrů
    if (directory == NULL || filename == NULL || content == NULL) {
        fprintf(stderr, "Chyba: Vstupní parametry nesmí být NULL\n");
        return;
    }
    
    // Vytvoření úplné cesty k souboru
    size_t dir_len = strlen(directory);
    size_t file_len = strlen(filename);
    size_t total_len = dir_len + file_len + 2; // +2 pro '/' a '\0'
    
    char *full_path = malloc(total_len);
    if (full_path == NULL) {
        fprintf(stderr, "Chyba: Nelze alokovat paměť pro cestu\n");
        return;
    }
    
    // Sestavení cesty
    snprintf(full_path, total_len, "%s/%s", directory, filename);
    
    // Zajištění existence adresáře
    if (mkdir(directory, 0700) != 0) {
        if (errno != EEXIST) {
            fprintf(stderr, "Chyba: Nelze vytvořit adresář '%s': %s\n", 
                    directory, strerror(errno));
            free(full_path);
            return;
        }
    }
    
    // Otevření souboru s přísnými oprávněními
    int fd = open(full_path, O_WRONLY | O_CREAT | O_TRUNC, 0600);
    if (fd == -1) {
        fprintf(stderr, "Chyba: Nelze vytvořit soubor '%s': %s\n", 
                full_path, strerror(errno));
        free(full_path);
        return;
    }
    
    // Zápis obsahu do souboru
    size_t content_len = strlen(content);
    ssize_t bytes_written = write(fd, content, content_len);
    
    if (bytes_written != (ssize_t)content_len) {
        fprintf(stderr, "Chyba: Nelze zapsat celý obsah do souboru '%s'\n", full_path);
        close(fd);
        free(full_path);
        return;
    }
    
    // Uzavření souboru a uvolnění paměti
    if (close(fd) != 0) {
        fprintf(stderr, "Varování: Chyba při uzavírání souboru '%s': %s\n", 
                full_path, strerror(errno));
    }
    
    free(full_path);
}