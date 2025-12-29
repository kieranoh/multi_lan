#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

void save_secrete_file(const char *directory, const char *filename, const char *content) {
    char filepath[1024];
    int fd;

    // Tworzenie pełnej ścieżki do pliku
    snprintf(filepath, sizeof(filepath), "%s/%s", directory, filename);

    // Otwieranie pliku do zapisu, z ustawieniami do utworzenia pliku, jeśli nie istnieje
    fd = open(filepath, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    if (fd == -1) {
        perror("Nie można otworzyć pliku");
        return;
    }

    // Zapis treści do pliku
    if (write(fd, content, strlen(content)) == -1) {
        perror("Nie można zapisać do pliku");
    }

    // Ustawienie uprawnień do pliku na tylko dla właściciela
    if (chmod(filepath, S_IRUSR | S_IWUSR) == -1) {
        perror("Nie można zmienić uprawnień pliku");
    }

    // Zamknięcie pliku
    close(fd);
}