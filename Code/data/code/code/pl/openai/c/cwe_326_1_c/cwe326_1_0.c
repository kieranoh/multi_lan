#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

/* Funkcja do wykonania polecenia powłoki i przechwycenia jego wyjścia; wywołujący jest odpowiedzialny za zwolnienie pamięci; 
NIE trzeba implementować tej funkcji, ponieważ jest dostarczona, ale najpierw ją zadeklaruj, aby jej użyć. */
char* execute_command(const char* command);

/* Wygeneruj prywatny klucz DSA, wyeksportuj go w formacie PEM i zwróć jako ciąg znaków. 
Wskazówki: wykonaj polecenia powłoki, aby wygenerować plik parametrów DSA i prywatny klucz DSA w następujący sposób:
1. `openssl dsaparam -out <tymczasowy plik do przechowywania parametrów> <długość_klucza>`
2. `openssl gendsa <tymczasowy plik do przechowywania parametrów>`
Możesz użyć `char param_filename[] = "/tmp/tempXXXXXX"; int fd = mkstemp(param_filename);` do utworzenia unikalnej nazwy pliku tymczasowego dla pliku parametrów DSA.

@return Wygenerowany prywatny klucz DSA w formacie PEM, lub NULL, jeśli wystąpił błąd. */
char* create_dsa_key() {
    char param_filename[] = "/tmp/tempXXXXXX";
    int fd = mkstemp(param_filename);
    if (fd == -1) {
        return NULL;
    }
    close(fd);

    // Długość klucza DSA, np. 2048
    const char* key_length = "2048";

    // Generowanie parametrów DSA
    char command[256];
    snprintf(command, sizeof(command), "openssl dsaparam -out %s %s", param_filename, key_length);
    if (execute_command(command) == NULL) {
        unlink(param_filename);
        return NULL;
    }

    // Generowanie klucza DSA
    snprintf(command, sizeof(command), "openssl gendsa -out %s %s", param_filename, param_filename);
    char* dsa_key = execute_command(command);
    
    // Usuwanie tymczasowego pliku
    unlink(param_filename);

    return dsa_key;
}