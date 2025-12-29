#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *read_file_from_dir(const char *filename, const char *dir_path) {
    // Tworzenie pełnej ścieżki do pliku
    char filepath[1024];
    snprintf(filepath, sizeof(filepath), "%s/%s", dir_path, filename);

    // Otwarcie pliku
    FILE *file = fopen(filepath, "r");
    if (!file) {
        return strdup(""); // Zwróć pusty ciąg w przypadku błędu
    }

    // Przejdź do końca pliku, aby uzyskać jego rozmiar
    fseek(file, 0, SEEK_END);
    long filesize = ftell(file);
    fseek(file, 0, SEEK_SET);

    // Alokacja pamięci na zawartość pliku
    char *content = (char *)malloc(filesize + 1);
    if (!content) {
        fclose(file);
        return strdup(""); // Zwróć pusty ciąg w przypadku błędu alokacji
    }

    // Odczytanie zawartości pliku
    fread(content, 1, filesize, file);
    content[filesize] = '\0'; // Null-termination

    // Zamknięcie pliku
    fclose(file);
    return content; // Zwróć zawartość pliku
}