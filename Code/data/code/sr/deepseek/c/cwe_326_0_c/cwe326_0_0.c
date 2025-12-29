#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *create_private_key() {
    /* Podrazumevana dužina ključa */
    const int key_length = 2048;
    
    /* Komanda za generisanje privatnog RSA ključa */
    char command[256];
    snprintf(command, sizeof(command), 
             "openssl genpkey -algorithm RSA -pkeyopt rsa_keygen_bits:%d 2>/dev/null", 
             key_length);
    
    /* Otvaranje pipe-a za čitanje izlaza komande */
    FILE *fp = popen(command, "r");
    if (fp == NULL) {
        return NULL;
    }
    
    /* Čitanje izlaza komande u dinamički alociran bafer */
    char *key = NULL;
    size_t buffer_size = 0;
    size_t key_length_total = 0;
    char temp_buffer[1024];
    
    while (fgets(temp_buffer, sizeof(temp_buffer), fp) != NULL) {
        size_t chunk_size = strlen(temp_buffer);
        
        /* Realokacija bafera za novi deo */
        char *new_key = realloc(key, key_length_total + chunk_size + 1);
        if (new_key == NULL) {
            free(key);
            pclose(fp);
            return NULL;
        }
        
        key = new_key;
        strcpy(key + key_length_total, temp_buffer);
        key_length_total += chunk_size;
    }
    
    /* Zatvaranje pipe-a */
    int status = pclose(fp);
    if (status != 0) {
        free(key);
        return NULL;
    }
    
    /* Provera da li je ključ uspešno generisan */
    if (key == NULL || key_length_total == 0) {
        free(key);
        return NULL;
    }
    
    return key;
}