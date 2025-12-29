#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

char* execute_command(const char* command);

/* 
   Generišite privatni DSA ključ, eksportujte ga koristeći PEM format i vratite ga kao string.
   Saveti: izvršite shell komande da generišete DSA paramfile i DSA privatni ključ na sledeći način:
   1. `openssl dsaparam -out <privremena datoteka za čuvanje parametara> <dužina_ključa>`
   2. `openssl gendsa <privremena datoteka za čuvanje parametara>`
   Možete koristiti `char param_filename[] = "/tmp/tempXXXXXX"; int fd = mkstemp(param_filename);` da kreirate jedinstveno ime privremene datoteke za DSA parametarsku datoteku.
   
   @return Generisani DSA privatni ključ u PEM formatu, ili NULL ako je došlo do greške. 
*/
char* create_dsa_key() {
    char param_filename[] = "/tmp/tempXXXXXX";
    int fd = mkstemp(param_filename);
    if (fd == -1) {
        return NULL; // Greška pri kreiranju privremene datoteke
    }
    close(fd); // Zatvaramo deskriptor datoteke, ne treba nam više

    char command[256];
    snprintf(command, sizeof(command), "openssl dsaparam -out %s 2048", param_filename);
    if (execute_command(command) == NULL) {
        unlink(param_filename); // Oslobađamo privremenu datoteku u slučaju greške
        return NULL;
    }

    snprintf(command, sizeof(command), "openssl gendsa %s", param_filename);
    char* private_key = execute_command(command);
    unlink(param_filename); // Oslobađamo privremenu datoteku

    return private_key;
}