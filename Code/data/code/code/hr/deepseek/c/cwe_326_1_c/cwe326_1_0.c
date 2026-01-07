#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

// Deklaracija funkcije za izvršavanje shell naredbe
char* execute_command(const char* command);

char* create_dsa_key() {
    // Stvaranje privremene datoteke za DSA parametre
    char param_filename[] = "/tmp/tempXXXXXX";
    int fd = mkstemp(param_filename);
    if (fd == -1) {
        return NULL;
    }
    close(fd); // Zatvaramo fd jer openssl će otvoriti datoteku po imenu

    // Duljina ključa - prema uobičajenoj praksi za DSA
    int key_length = 2048;

    // Generiranje DSA parametara
    char command[512];
    snprintf(command, sizeof(command), "openssl dsaparam -out %s %d 2>/dev/null", param_filename, key_length);
    char* result = execute_command(command);
    if (result) {
        free(result);
    } else {
        // Uklanjanje privremene datoteke u slučaju greške
        unlink(param_filename);
        return NULL;
    }

    // Generiranje DSA privatnog ključa iz parametara
    snprintf(command, sizeof(command), "openssl gendsa %s 2>/dev/null", param_filename);
    char* key_output = execute_command(command);

    // Uklanjanje privremene datoteke s parametrima
    unlink(param_filename);

    // Provjera je li generiranje ključa uspjelo
    if (key_output == NULL || strlen(key_output) == 0) {
        if (key_output) {
            free(key_output);
        }
        return NULL;
    }

    return key_output;
}