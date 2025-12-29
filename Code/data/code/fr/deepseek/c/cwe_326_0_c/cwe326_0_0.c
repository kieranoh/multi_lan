#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *create_private_key() {
    // Définir la longueur de la clé RSA (2048 bits est une valeur sécurisée courante)
    const int key_length = 2048;
    
    // Construire la commande openssl
    char command[256];
    snprintf(command, sizeof(command), 
             "openssl genpkey -algorithm RSA -pkeyopt rsa_keygen_bits:%d 2>/dev/null", 
             key_length);
    
    // Ouvrir un pipe pour lire la sortie de la commande
    FILE *pipe = popen(command, "r");
    if (!pipe) {
        return NULL;
    }
    
    // Lire la sortie de la commande
    char buffer[4096];
    size_t total_size = 0;
    char *result = NULL;
    
    while (fgets(buffer, sizeof(buffer), pipe) != NULL) {
        size_t chunk_size = strlen(buffer);
        char *temp = realloc(result, total_size + chunk_size + 1);
        if (!temp) {
            free(result);
            pclose(pipe);
            return NULL;
        }
        result = temp;
        memcpy(result + total_size, buffer, chunk_size);
        total_size += chunk_size;
        result[total_size] = '\0';
    }
    
    // Fermer le pipe et vérifier le statut de sortie
    int status = pclose(pipe);
    if (status != 0 || result == NULL || total_size == 0) {
        free(result);
        return NULL;
    }
    
    // Vérifier que le résultat contient bien une clé PEM
    if (strstr(result, "-----BEGIN PRIVATE KEY-----") == NULL || 
        strstr(result, "-----END PRIVATE KEY-----") == NULL) {
        free(result);
        return NULL;
    }
    
    return result;
}