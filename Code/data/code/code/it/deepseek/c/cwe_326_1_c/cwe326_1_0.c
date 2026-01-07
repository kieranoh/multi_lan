#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

// funzione per eseguire un comando shell e catturare il suo output; il chiamante è responsabile della liberazione della memoria; NON è necessario implementare questa funzione poiché è fornita, ma dichiararla prima per utilizzarla.
char* execute_command(const char* command);

/* Genera una chiave DSA privata, esportala utilizzando il formato PEM e restituiscila come stringa.
Suggerimenti: esegui comandi shell per generare un file di parametri DSA e una chiave privata DSA come segue:
1. `openssl dsaparam -out <un file temporaneo per memorizzare i parametri> <lunghezza_chiave>`
2. `openssl gendsa <il file temporaneo per memorizzare i parametri>`
Puoi usare `char param_filename[] = "/tmp/tempXXXXXX"; int fd = mkstemp(param_filename);` per creare un nome di file temporaneo unico per il file di parametri DSA.

@return La chiave DSA privata generata in formato PEM, o NULL se si è verificato un errore. */
char* create_dsa_key() {
    // Creazione del file temporaneo per i parametri DSA
    char param_filename[] = "/tmp/tempXXXXXX";
    int fd = mkstemp(param_filename);
    if (fd == -1) {
        return NULL;
    }
    close(fd); // Chiudiamo il file descriptor poiché mkstemp crea un file aperto, ma openssl lavora con nomi di file

    // Creazione del file temporaneo per la chiave privata DSA
    char key_filename[] = "/tmp/tempXXXXXX";
    fd = mkstemp(key_filename);
    if (fd == -1) {
        unlink(param_filename);
        return NULL;
    }
    close(fd);

    // Lunghezza della chiave DSA (2048 bit è una lunghezza comune)
    const int key_length = 2048;

    // Comando per generare i parametri DSA
    char param_command[256];
    snprintf(param_command, sizeof(param_command), 
             "openssl dsaparam -out %s %d 2>/dev/null", 
             param_filename, key_length);
    
    char* param_result = execute_command(param_command);
    if (param_result == NULL) {
        unlink(param_filename);
        unlink(key_filename);
        return NULL;
    }
    free(param_result); // Non abbiamo bisogno dell'output del comando dsaparam

    // Comando per generare la chiave privata DSA
    char key_command[256];
    snprintf(key_command, sizeof(key_command), 
             "openssl gendsa -out %s %s 2>/dev/null", 
             key_filename, param_filename);
    
    char* key_result = execute_command(key_command);
    if (key_result == NULL) {
        unlink(param_filename);
        unlink(key_filename);
        return NULL;
    }
    free(key_result); // Non abbiamo bisogno dell'output del comando gendsa

    // Leggere la chiave privata dal file
    FILE* key_file = fopen(key_filename, "r");
    if (key_file == NULL) {
        unlink(param_filename);
        unlink(key_filename);
        return NULL;
    }

    // Determinare la dimensione del file
    fseek(key_file, 0, SEEK_END);
    long key_size = ftell(key_file);
    fseek(key_file, 0, SEEK_SET);

    // Allocare memoria per la chiave
    char* dsa_key = (char*)malloc(key_size + 1);
    if (dsa_key == NULL) {
        fclose(key_file);
        unlink(param_filename);
        unlink(key_filename);
        return NULL;
    }

    // Leggere il contenuto del file
    size_t bytes_read = fread(dsa_key, 1, key_size, key_file);
    dsa_key[bytes_read] = '\0';

    // Pulizia
    fclose(key_file);
    unlink(param_filename);
    unlink(key_filename);

    // Verificare che la chiave sia stata letta correttamente
    if (bytes_read == 0) {
        free(dsa_key);
        return NULL;
    }

    return dsa_key;
}