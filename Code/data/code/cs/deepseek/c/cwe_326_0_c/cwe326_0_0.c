#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char *create_private_key() {
    // Výchozí délka klíče - typická hodnota pro RSA
    const int key_length = 2048;
    
    // Příkaz pro generování klíče
    char command[256];
    snprintf(command, sizeof(command), 
             "openssl genpkey -algorithm RSA -pkeyopt rsa_keygen_bits:%d 2>/dev/null", 
             key_length);
    
    // Otevření roury pro čtení výstupu z příkazu
    FILE *pipe = popen(command, "r");
    if (!pipe) {
        return NULL;
    }
    
    // Čtení výstupu z příkazu
    char buffer[4096];
    size_t total_size = 0;
    char *result = NULL;
    size_t result_size = 0;
    
    while (fgets(buffer, sizeof(buffer), pipe) != NULL) {
        size_t chunk_size = strlen(buffer);
        
        // Realokace paměti pro výsledný řetězec
        char *new_result = realloc(result, result_size + chunk_size + 1);
        if (!new_result) {
            free(result);
            pclose(pipe);
            return NULL;
        }
        
        result = new_result;
        strcpy(result + result_size, buffer);
        result_size += chunk_size;
    }
    
    // Zavření roury
    int status = pclose(pipe);
    
    // Kontrola, zda příkaz proběhl úspěšně
    if (status != 0 || result == NULL || result_size == 0) {
        free(result);
        return NULL;
    }
    
    // Zajištění, že výsledek je správně ukončený řetězec
    result = realloc(result, result_size + 1);
    if (!result) {
        return NULL;
    }
    result[result_size] = '\0';
    
    return result;
}