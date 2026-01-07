#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char* write_results(const char* results) {
    // Tworzenie nazwy tymczasowego pliku
    char* temp_filename = tmpnam(NULL);
    if (temp_filename == NULL) {
        return NULL; // Błąd w tworzeniu nazwy pliku
    }

    // Otwieranie pliku do zapisu
    FILE* file = fopen(temp_filename, "w");
    if (file == NULL) {
        return NULL; // Błąd w otwieraniu pliku
    }

    // Zapis wyników do pliku
    fprintf(file, "%s", results);
    fclose(file);

    // Dynamiczna alokacja pamięci dla nazwy pliku
    char* result = (char*)malloc(strlen(temp_filename) + 1);
    if (result == NULL) {
        return NULL; // Błąd w alokacji pamięci
    }

    // Kopiowanie nazwy pliku do alokowanej pamięci
    strcpy(result, temp_filename);
    return result; // Zwracamy nazwę tymczasowego pliku
}