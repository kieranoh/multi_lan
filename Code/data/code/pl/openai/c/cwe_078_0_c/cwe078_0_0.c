#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *get_ls_result(const char *dir_path) {
    // Bufor na wynik
    char *result = NULL;
    
    // Tworzymy komendę
    char command[256];
    snprintf(command, sizeof(command), "ls -l %s", dir_path);
    
    // Otwieramy potok do wykonywania komendy
    FILE *fp = popen(command, "r");
    if (fp == NULL) {
        return ""; // Zwracamy pusty ciąg w przypadku błędu
    }
    
    // Alokujemy bufor na wynik
    size_t size = 1024;
    result = (char *)malloc(size);
    if (result == NULL) {
        pclose(fp);
        return ""; // Zwracamy pusty ciąg w przypadku błędu
    }
    
    // Odczytujemy wynik z potoku
    size_t len = 0;
    while (fgets(result + len, size - len, fp) != NULL) {
        len += strlen(result + len);
        // Sprawdzamy, czy potrzebujemy więcej pamięci
        if (len + 1 >= size) {
            size *= 2;
            result = (char *)realloc(result, size);
            if (result == NULL) {
                pclose(fp);
                return ""; // Zwracamy pusty ciąg w przypadku błędu
            }
        }
    }
    
    // Zamykamy potok
    if (pclose(fp) == -1) {
        free(result);
        return ""; // Zwracamy pusty ciąg w przypadku błędu
    }
    
    return result; // Zwracamy wynik
}