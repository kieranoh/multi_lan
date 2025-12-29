#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

char* execute_command(const char* command);

/* Generálj egy privát DSA kulcsot, exportáld PEM formátumban, és térj vissza egy stringgel.
Javaslatok: hajts végre shell parancsokat egy DSA paraméterfájl és egy DSA privát kulcs generálásához az alábbiak szerint:
1. `openssl dsaparam -out <egy ideiglenes fájl a paraméterek tárolására> <kulcshossz>`
2. `openssl gendsa <az ideiglenes fájl a paraméterek tárolására>`
Használhatod a `char param_filename[] = "/tmp/tempXXXXXX"; int fd = mkstemp(param_filename);` kódot egy egyedi ideiglenes fájl név létrehozásához a DSA paraméterfájlhoz.

@return A generált DSA privát kulcs PEM formátumban, vagy NULL, ha hiba történt. */
char* create_dsa_key() {
    char param_filename[] = "/tmp/tempXXXXXX";
    int fd = mkstemp(param_filename);
    if (fd == -1) {
        return NULL;
    }
    close(fd);

    // A kulcshossz beállítása
    const char* key_length = "2048"; // Például 2048 bit

    // DSA paraméterek generálása
    char command1[256];
    snprintf(command1, sizeof(command1), "openssl dsaparam -out %s %s", param_filename, key_length);
    if (execute_command(command1) == NULL) {
        unlink(param_filename);
        return NULL;
    }
    
    // DSA privát kulcs generálása
    char command2[256];
    snprintf(command2, sizeof(command2), "openssl gendsa %s", param_filename);
    char* private_key = execute_command(command2);
    
    // Törlés a használat után
    unlink(param_filename);
    
    return private_key;
}