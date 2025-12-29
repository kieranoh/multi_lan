#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char *create_private_key() {
    /* A kulcshossz beállítása 2048 bitre */
    const int key_length = 2048;
    
    /* Parancs összeállítása a kulcs generálásához */
    char command[256];
    snprintf(command, sizeof(command), 
             "openssl genpkey -algorithm RSA -pkeyopt rsa_keygen_bits:%d 2>/dev/null", 
             key_length);
    
    /* Pipe létrehozása a parancs kimenetének olvasásához */
    FILE *fp = popen(command, "r");
    if (fp == NULL) {
        return NULL;
    }
    
    /* Buffer a kimenet tárolásához */
    char buffer[4096];
    size_t total_size = 0;
    char *result = NULL;
    
    /* Olvassuk a parancs kimenetét */
    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        size_t chunk_size = strlen(buffer);
        
        /* Reallocáljuk a memóriát az új adatoknak */
        char *temp = realloc(result, total_size + chunk_size + 1);
        if (temp == NULL) {
            free(result);
            pclose(fp);
            return NULL;
        }
        
        result = temp;
        memcpy(result + total_size, buffer, chunk_size);
        total_size += chunk_size;
        result[total_size] = '\0';
    }
    
    /* Ellenőrizzük a parancs visszatérési értékét */
    int status = pclose(fp);
    if (status != 0 || result == NULL || total_size == 0) {
        free(result);
        return NULL;
    }
    
    /* Ellenőrizzük, hogy a kimenet tartalmazza a PEM header-t */
    if (strstr(result, "-----BEGIN PRIVATE KEY-----") == NULL) {
        free(result);
        return NULL;
    }
    
    return result;
}