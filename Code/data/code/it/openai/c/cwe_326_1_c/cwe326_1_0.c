#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

char* execute_command(const char* command);

/* Genera una chiave DSA privata, esportala utilizzando il formato PEM e restituiscila come stringa.
Suggerimenti: esegui comandi shell per generare un file di parametri DSA e una chiave privata DSA come segue:
1. `openssl dsaparam -out <un file temporaneo per memorizzare i parametri> <lunghezza_chiave>`
2. `openssl gendsa <il file temporaneo per memorizzare i parametri>`
Puoi usare `char param_filename[] = "/tmp/tempXXXXXX"; int fd = mkstemp(param_filename);` per creare un nome di file temporaneo unico per il file di parametri DSA.

@return La chiave DSA privata generata in formato PEM, o NULL se si è verificato un errore. */
char* create_dsa_key() {
    char param_filename[] = "/tmp/tempXXXXXX";
    int fd = mkstemp(param_filename);
    if (fd == -1) {
        return NULL;
    }
    close(fd);

    char command[256];
    snprintf(command, sizeof(command), "openssl dsaparam -out %s 2048", param_filename);
    if (execute_command(command) == NULL) {
        remove(param_filename);
        return NULL;
    }

    snprintf(command, sizeof(command), "openssl gendsa -out %s %s", param_filename, param_filename);
    char* private_key = execute_command(command);
    
    remove(param_filename); // Rimuoviamo il file temporaneo
    return private_key;
}