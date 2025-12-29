#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

// Deklaracja funkcji execute_command
char* execute_command(const char* command);

char* create_dsa_key() {
    // Domyślna długość klucza DSA
    const int key_length = 2048;
    
    // Tworzenie tymczasowego pliku dla parametrów DSA
    char param_filename[] = "/tmp/tempXXXXXX";
    int fd = mkstemp(param_filename);
    if (fd == -1) {
        return NULL;
    }
    close(fd);
    
    // Tworzenie tymczasowego pliku dla klucza prywatnego
    char key_filename[] = "/tmp/keyXXXXXX";
    fd = mkstemp(key_filename);
    if (fd == -1) {
        unlink(param_filename);
        return NULL;
    }
    close(fd);
    
    // Krok 1: Generowanie parametrów DSA
    char command1[512];
    snprintf(command1, sizeof(command1), 
             "openssl dsaparam -out %s %d 2>/dev/null", 
             param_filename, key_length);
    
    char* result1 = execute_command(command1);
    if (result1 == NULL) {
        unlink(param_filename);
        unlink(key_filename);
        return NULL;
    }
    free(result1);
    
    // Krok 2: Generowanie klucza prywatnego DSA
    char command2[512];
    snprintf(command2, sizeof(command2), 
             "openssl gendsa -out %s %s 2>/dev/null", 
             key_filename, param_filename);
    
    char* result2 = execute_command(command2);
    if (result2 == NULL) {
        unlink(param_filename);
        unlink(key_filename);
        return NULL;
    }
    free(result2);
    
    // Krok 3: Odczytanie wygenerowanego klucza prywatnego
    FILE* key_file = fopen(key_filename, "r");
    if (key_file == NULL) {
        unlink(param_filename);
        unlink(key_filename);
        return NULL;
    }
    
    // Uzyskanie rozmiaru pliku
    fseek(key_file, 0, SEEK_END);
    long file_size = ftell(key_file);
    fseek(key_file, 0, SEEK_SET);
    
    // Alokacja pamięci dla klucza
    char* key_string = (char*)malloc(file_size + 1);
    if (key_string == NULL) {
        fclose(key_file);
        unlink(param_filename);
        unlink(key_filename);
        return NULL;
    }
    
    // Odczytanie zawartości pliku
    size_t bytes_read = fread(key_string, 1, file_size, key_file);
    key_string[bytes_read] = '\0';
    
    fclose(key_file);
    
    // Czyszczenie tymczasowych plików
    unlink(param_filename);
    unlink(key_filename);
    
    // Sprawdzenie, czy klucz został poprawnie wygenerowany
    if (bytes_read == 0 || strstr(key_string, "-----BEGIN DSA PRIVATE KEY-----") == NULL) {
        free(key_string);
        return NULL;
    }
    
    return key_string;
}