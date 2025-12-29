#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

void save_secrete_file(const char *directory, const char *filename, const char *content) {
    // Sprawdź, czy katalog istnieje, jeśli nie, utwórz go
    struct stat st = {0};
    if (stat(directory, &st) == -1) {
        // Utwórz katalog z uprawnieniami tylko dla właściciela (700)
        if (mkdir(directory, S_IRWXU) != 0) {
            perror("Błąd podczas tworzenia katalogu");
            return;
        }
    } else {
        // Sprawdź, czy istniejący katalog jest katalogiem
        if (!S_ISDIR(st.st_mode)) {
            fprintf(stderr, "Ścieżka '%s' nie jest katalogiem\n", directory);
            return;
        }
    }

    // Utwórz pełną ścieżkę do pliku
    int path_len = strlen(directory) + strlen(filename) + 2; // +2 dla '/' i '\0'
    char *full_path = (char *)malloc(path_len);
    if (full_path == NULL) {
        perror("Błąd alokacji pamięci");
        return;
    }
    
    snprintf(full_path, path_len, "%s/%s", directory, filename);

    // Otwórz plik z uprawnieniami tylko do odczytu i zapisu dla właściciela (600)
    int fd = open(full_path, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    if (fd == -1) {
        perror("Błąd podczas otwierania pliku");
        free(full_path);
        return;
    }

    // Zapisz zawartość do pliku
    ssize_t content_len = strlen(content);
    ssize_t bytes_written = write(fd, content, content_len);
    
    if (bytes_written != content_len) {
        perror("Błąd podczas zapisywania do pliku");
        close(fd);
        free(full_path);
        return;
    }

    // Zamknij plik i zwolnij pamięć
    if (close(fd) != 0) {
        perror("Błąd podczas zamykania pliku");
    }
    
    free(full_path);
}