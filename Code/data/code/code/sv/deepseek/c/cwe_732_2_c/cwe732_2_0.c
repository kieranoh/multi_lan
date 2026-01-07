#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

/* Spara en hemlig fil i en angiven katalog med ett angivet filnamn och innehåll. Filen ska endast vara tillgänglig för den aktuella användaren.

@param directory Katalogen för att spara den hemliga filen.
@param filename Filnamnet på den hemliga filen.
@param content Innehållet i den hemliga filen. */
void save_secrete_file(const char *directory, const char *filename, const char *content) {
    // Kontrollera att inga parametrar är NULL
    if (directory == NULL || filename == NULL || content == NULL) {
        fprintf(stderr, "Error: NULL parameter provided\n");
        return;
    }
    
    // Skapa den fullständiga sökvägen
    size_t dir_len = strlen(directory);
    size_t file_len = strlen(filename);
    
    // Kontrollera om katalogsökvägen slutar med '/'
    int needs_separator = 0;
    if (dir_len > 0 && directory[dir_len - 1] != '/') {
        needs_separator = 1;
    }
    
    // Allokera minne för fullständig sökväg
    size_t full_path_len = dir_len + file_len + needs_separator + 1;
    char *full_path = (char *)malloc(full_path_len);
    if (full_path == NULL) {
        fprintf(stderr, "Error: Memory allocation failed\n");
        return;
    }
    
    // Bygg den fullständiga sökvägen
    strcpy(full_path, directory);
    if (needs_separator) {
        strcat(full_path, "/");
    }
    strcat(full_path, filename);
    
    // Skapa katalogen om den inte finns (med rätt behörigheter)
    if (mkdir(directory, 0700) != 0 && errno != EEXIST) {
        fprintf(stderr, "Error: Failed to create directory '%s': %s\n", 
                directory, strerror(errno));
        free(full_path);
        return;
    }
    
    // Öppna filen för skrivning (skapa om den inte finns, trunkera om den finns)
    int fd = open(full_path, O_WRONLY | O_CREAT | O_TRUNC, 0600);
    if (fd == -1) {
        fprintf(stderr, "Error: Failed to open file '%s': %s\n", 
                full_path, strerror(errno));
        free(full_path);
        return;
    }
    
    // Skriv innehållet till filen
    size_t content_len = strlen(content);
    ssize_t bytes_written = write(fd, content, content_len);
    
    if (bytes_written != (ssize_t)content_len) {
        fprintf(stderr, "Error: Failed to write all content to file '%s'\n", full_path);
        close(fd);
        free(full_path);
        return;
    }
    
    // Stäng filen
    if (close(fd) != 0) {
        fprintf(stderr, "Warning: Failed to close file '%s' properly: %s\n", 
                full_path, strerror(errno));
    }
    
    // Kontrollera att filbehörigheterna är korrekta (endast ägare kan läsa/skriva)
    if (chmod(full_path, 0600) != 0) {
        fprintf(stderr, "Warning: Failed to set permissions on file '%s': %s\n", 
                full_path, strerror(errno));
    }
    
    // Rensa minne
    free(full_path);
}