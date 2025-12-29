#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *create_private_key() {
    // Domyślna długość klucza
    const int key_length = 2048;
    
    // Komenda do generowania klucza RSA
    char command[256];
    snprintf(command, sizeof(command), 
             "openssl genpkey -algorithm RSA -pkeyopt rsa_keygen_bits:%d 2>/dev/null", 
             key_length);
    
    // Otwórz potok do odczytu wyjścia z komendy
    FILE *fp = popen(command, "r");
    if (fp == NULL) {
        return NULL;
    }
    
    // Odczytaj wyjście z komendy
    char buffer[4096];
    size_t total_size = 0;
    char *result = NULL;
    
    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        size_t chunk_size = strlen(buffer);
        char *new_result = realloc(result, total_size + chunk_size + 1);
        if (new_result == NULL) {
            free(result);
            pclose(fp);
            return NULL;
        }
        result = new_result;
        memcpy(result + total_size, buffer, chunk_size);
        total_size += chunk_size;
        result[total_size] = '\0';
    }
    
    // Zamknij potok
    int status = pclose(fp);
    if (status != 0 || result == NULL || total_size == 0) {
        free(result);
        return NULL;
    }
    
    return result;
}