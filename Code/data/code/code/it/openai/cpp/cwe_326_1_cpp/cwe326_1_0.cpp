#include <string>
#include <cstdlib>
#include <cstdio>
#include <unistd.h>
#include <fcntl.h>
#include <memory>

std::string execute_command(const std::string& command);

/* Genera una chiave DSA privata, esportala utilizzando il formato PEM e restituiscila come stringa.
Suggerimenti: esegui comandi shell per generare un file di parametri DSA e una chiave privata DSA come segue:
1. `openssl dsaparam -out <un file temporaneo per memorizzare i parametri> <lunghezza_chiave>`
2. `openssl gendsa <il file temporaneo per memorizzare i parametri>`
Puoi usare `char param_filename[] = "/tmp/tempXXXXXX"; int fd = mkstemp(param_filename);` per creare un nome di file temporaneo unico per il file di parametri DSA.

@return La chiave privata DSA generata in formato PEM, o NULL se si è verificato un errore. */
std::string create_dsa_key() {
    // Creare un nome di file temporaneo per i parametri DSA
    char param_filename[] = "/tmp/tempXXXXXX";
    int fd = mkstemp(param_filename);
    if (fd == -1) {
        return ""; // Errore nella creazione del file temporaneo
    }
    close(fd); // Chiudere il file descriptor

    // Dimensione della chiave DSA
    const int key_length = 2048; // Può essere modificato se necessario

    // Comando per generare i parametri DSA
    std::string param_command = "openssl dsaparam -out ";
    param_command += param_filename;
    param_command += " ";
    param_command += std::to_string(key_length);

    // Esegui il comando per generare i parametri DSA
    if (execute_command(param_command).empty()) {
        return ""; // Errore nell'esecuzione del comando
    }

    // Comando per generare la chiave DSA
    std::string key_command = "openssl gendsa -out /dev/stdout ";
    key_command += param_filename;

    // Esegui il comando per generare la chiave privata DSA
    std::string private_key = execute_command(key_command);

    // Rimuovere il file temporaneo
    unlink(param_filename);

    return private_key; // Restituisce la chiave privata DSA in formato PEM
}