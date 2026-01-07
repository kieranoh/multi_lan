#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

// funkce pro provedení shellového příkazu a zachycení jeho výstupu; volající je zodpovědný za uvolnění paměti
char* execute_command(const char* command);

char* create_dsa_key() {
    // Výchozí délka klíče (může být upravena podle potřeby)
    const int key_length = 2048;
    
    // Vytvoření dočasného souboru pro parametry DSA
    char param_filename[] = "/tmp/tempXXXXXX";
    int fd = mkstemp(param_filename);
    if (fd == -1) {
        fprintf(stderr, "Chyba při vytváření dočasného souboru: %s\n", strerror(errno));
        return NULL;
    }
    close(fd); // Soubor je vytvořen, zavřeme deskriptor
    
    // Vytvoření dočasného souboru pro soukromý klíč
    char key_filename[] = "/tmp/keyXXXXXX";
    int key_fd = mkstemp(key_filename);
    if (key_fd == -1) {
        fprintf(stderr, "Chyba při vytváření dočasného souboru pro klíč: %s\n", strerror(errno));
        unlink(param_filename);
        return NULL;
    }
    close(key_fd);
    
    char* result = NULL;
    char command[512];
    
    // 1. Generování DSA parametrů
    snprintf(command, sizeof(command), "openssl dsaparam -out %s %d 2>/dev/null", 
             param_filename, key_length);
    char* param_result = execute_command(command);
    if (param_result) {
        free(param_result);
        
        // 2. Generování soukromého DSA klíče z parametrů
        snprintf(command, sizeof(command), "openssl gendsa %s 2>/dev/null", param_filename);
        char* keygen_result = execute_command(command);
        if (keygen_result) {
            free(keygen_result);
            
            // 3. Export klíče do formátu PEM
            snprintf(command, sizeof(command), 
                     "openssl dsa -in %s -outform PEM 2>/dev/null", param_filename);
            result = execute_command(command);
        }
    }
    
    // Vyčištění dočasných souborů
    unlink(param_filename);
    unlink(key_filename);
    
    return result;
}