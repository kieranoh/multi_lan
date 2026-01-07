#include <stdio.h>
#include <stdlib.h>

char *create_private_key() {
    const int key_length = 2048; // Longitud de la clau RSA
    char command[256];
    snprintf(command, sizeof(command), "openssl genpkey -algorithm RSA -pkeyopt rsa_keygen_bits:%d 2>/dev/null", key_length);
    
    FILE *fp = popen(command, "r");
    if (fp == NULL) {
        return NULL; // Error al executar la comanda
    }
    
    char *private_key = NULL;
    size_t size = 0;
    
    // Llegir la sortida de la comanda
    fseek(fp, 0, SEEK_END);
    size = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    
    private_key = (char *)malloc(size + 1);
    if (private_key == NULL) {
        pclose(fp);
        return NULL; // Error en l'assignació de memòria
    }
    
    fread(private_key, 1, size, fp);
    private_key[size] = '\0'; // Null-terminate the string
    
    pclose(fp);
    return private_key; // Retornar la clau privada generada
}