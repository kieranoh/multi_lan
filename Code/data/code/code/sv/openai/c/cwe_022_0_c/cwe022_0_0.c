#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *read_file_from_dir(const char *filename, const char *dir_path) {
    // Skapa den fullständiga sökvägen till filen
    size_t path_length = strlen(dir_path) + strlen(filename) + 2; // +2 för '/' och '\0'
    char *full_path = (char *)malloc(path_length);
    if (full_path == NULL) {
        return NULL; // Returnera NULL om minnesallokering misslyckas
    }
    snprintf(full_path, path_length, "%s/%s", dir_path, filename);

    // Öppna filen för läsning
    FILE *file = fopen(full_path, "r");
    free(full_path); // Frigör full_path efter att ha använt den
    if (file == NULL) {
        return strdup(""); // Returnera en tom sträng om filen inte kan öppnas
    }

    // Hitta filens storlek
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    // Allokera minne för att läsa filens innehåll
    char *content = (char *)malloc(file_size + 1); // +1 för null-terminering
    if (content == NULL) {
        fclose(file);
        return NULL; // Returnera NULL om minnesallokering misslyckas
    }

    // Läs filens innehåll
    fread(content, 1, file_size, file);
    content[file_size] = '\0'; // Null-terminera strängen

    fclose(file); // Stäng filen
    return content; // Returnera innehållet i filen
}