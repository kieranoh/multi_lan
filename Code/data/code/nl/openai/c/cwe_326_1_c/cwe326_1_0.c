#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

char* execute_command(const char* command);

/* Genereer een privé DSA-sleutel, exporteer deze met het PEM-formaat en retourneer deze als een string. */
char* create_dsa_key() {
    char param_filename[] = "/tmp/tempXXXXXX";
    int fd = mkstemp(param_filename);
    if (fd == -1) {
        return NULL; // Fout bij het maken van een tijdelijke bestandsnaam
    }
    
    // We sluiten de file descriptor omdat we deze niet meer nodig hebben
    close(fd);

    // Definieer de sleutel lengte
    const int key_length = 2048; // of andere lengte indien nodig

    // Commando's om DSA-parameters en DSA-sleutel te genereren
    char command[256];

    // Genereer DSA-parameters
    snprintf(command, sizeof(command), "openssl dsaparam -out %s %d", param_filename, key_length);
    if (execute_command(command) == NULL) {
        unlink(param_filename); // Verwijder het tijdelijke bestand bij fout
        return NULL;
    }

    // Genereer DSA-sleutel
    snprintf(command, sizeof(command), "openssl gendsa -outform PEM -out /dev/stdout %s", param_filename);
    char* private_key = execute_command(command);
    
    // Verwijder het tijdelijke bestand
    unlink(param_filename);

    return private_key; // Retourneer de DSA-prive sleutel in PEM-formaat
}