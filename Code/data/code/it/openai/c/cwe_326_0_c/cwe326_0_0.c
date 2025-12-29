#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *create_private_key() {
    const int key_length = 2048; // Lunghezza della chiave RSA
    char command[256];
    FILE *fp;
    char *private_key = NULL;
    long length;

    // Comando per generare la chiave RSA
    snprintf(command, sizeof(command), "openssl genpkey -algorithm RSA -pkeyopt rsa_keygen_bits:%d 2>/dev/null", key_length);
    
    // Esecuzione del comando
    fp = popen(command, "r");
    if (fp == NULL) {
        return NULL; // errore nell'esecuzione del comando
    }

    // Calcola la lunghezza della chiave generata
    fseek(fp, 0, SEEK_END);
    length = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    // Alloca memoria per la chiave privata
    private_key = (char *)malloc(length + 1);
    if (private_key == NULL) {
        pclose(fp);
        return NULL; // errore di allocazione memoria
    }

    // Legge la chiave privata dal comando
    fread(private_key, 1, length, fp);
    private_key[length] = '\0'; // termina la stringa

    // Chiude il pipe
    pclose(fp);
    
    return private_key; // restituisce la chiave privata in formato PEM
}