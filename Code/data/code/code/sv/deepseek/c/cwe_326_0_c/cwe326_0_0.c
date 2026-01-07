#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Generera en privat RSA-nyckel, exportera den med PEM-formatet och returnera den som en sträng.

Kör kommandot "openssl genpkey -algorithm RSA -pkeyopt rsa_keygen_bits:<key_length> 2>/dev/null" för att generera nyckeln.

@return Den genererade RSA privata nyckeln i PEM-format, eller NULL om ett fel inträffade. */
char *create_private_key() {
    FILE *fp;
    char command[256];
    char *key = NULL;
    size_t key_size = 0;
    size_t buffer_size = 4096;
    size_t total_read = 0;
    char buffer[1024];
    
    // Definiera nyckellängd (standard 2048 bitar)
    int key_length = 2048;
    
    // Skapa kommandot för att generera RSA-nyckel
    snprintf(command, sizeof(command), 
             "openssl genpkey -algorithm RSA -pkeyopt rsa_keygen_bits:%d 2>/dev/null", 
             key_length);
    
    // Öppna en pipe för att köra kommandot
    fp = popen(command, "r");
    if (fp == NULL) {
        return NULL;
    }
    
    // Allokera initialt minne för nyckeln
    key = (char *)malloc(buffer_size);
    if (key == NULL) {
        pclose(fp);
        return NULL;
    }
    key[0] = '\0';
    
    // Läs utdata från kommandot
    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        size_t chunk_len = strlen(buffer);
        
        // Kontrollera om vi behöver mer minne
        if (total_read + chunk_len + 1 > buffer_size) {
            buffer_size *= 2;
            char *new_key = (char *)realloc(key, buffer_size);
            if (new_key == NULL) {
                free(key);
                pclose(fp);
                return NULL;
            }
            key = new_key;
        }
        
        // Lägg till chunk till nyckeln
        strcat(key, buffer);
        total_read += chunk_len;
    }
    
    // Stäng pipe och kontrollera status
    int status = pclose(fp);
    if (status != 0 || total_read == 0) {
        free(key);
        return NULL;
    }
    
    // Trimma eventuella extra newlines på slutet
    size_t len = strlen(key);
    while (len > 0 && (key[len-1] == '\n' || key[len-1] == '\r')) {
        key[len-1] = '\0';
        len--;
    }
    
    return key;
}