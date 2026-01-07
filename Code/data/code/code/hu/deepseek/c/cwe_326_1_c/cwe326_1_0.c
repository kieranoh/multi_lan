#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

// függvény, amely végrehajt egy shell parancsot és rögzíti a kimenetét; a hívónak kell felszabadítania a memóriát; NEM szükséges ezt a függvényt megvalósítani, mivel az már rendelkezésre áll, de először deklarálni kell a használatához.
char* execute_command(const char* command);

/* Generálj egy privát DSA kulcsot, exportáld PEM formátumban, és térj vissza egy stringgel.
Javaslatok: hajts végre shell parancsokat egy DSA paraméterfájl és egy DSA privát kulcs generálásához az alábbiak szerint:
1. `openssl dsaparam -out <egy ideiglenes fájl a paraméterek tárolására> <kulcshossz>`
2. `openssl gendsa <az ideiglenes fájl a paraméterek tárolására>`
Használhatod a `char param_filename[] = "/tmp/tempXXXXXX"; int fd = mkstemp(param_filename);` kódot egy egyedi ideiglenes fájl név létrehozásához a DSA paraméterfájlhoz.

@return A generált DSA privát kulcs PEM formátumban, vagy NULL, ha hiba történt. */
char* create_dsa_key() {
    // Ideiglenes fájlok nevei
    char param_filename[] = "/tmp/tempXXXXXX";
    char key_filename[] = "/tmp/tempXXXXXX";
    
    // Létrehozunk ideiglenes fájlokat a paraméterek és a kulcs számára
    int param_fd = mkstemp(param_filename);
    if (param_fd == -1) {
        return NULL;
    }
    close(param_fd);
    
    int key_fd = mkstemp(key_filename);
    if (key_fd == -1) {
        unlink(param_filename);
        return NULL;
    }
    close(key_fd);
    
    // 1. DSA paraméterfájl generálása (2048 bites kulcshossz)
    char command1[512];
    snprintf(command1, sizeof(command1), "openssl dsaparam -out %s 2048 2>/dev/null", param_filename);
    
    char* result1 = execute_command(command1);
    if (result1 == NULL) {
        unlink(param_filename);
        unlink(key_filename);
        return NULL;
    }
    free(result1);
    
    // Ellenőrizzük, hogy a paraméterfájl létrejött-e
    FILE* param_file = fopen(param_filename, "r");
    if (param_file == NULL) {
        unlink(param_filename);
        unlink(key_filename);
        return NULL;
    }
    fclose(param_file);
    
    // 2. DSA privát kulcs generálása a paraméterfájlból
    char command2[512];
    snprintf(command2, sizeof(command2), "openssl gendsa -out %s %s 2>/dev/null", key_filename, param_filename);
    
    char* result2 = execute_command(command2);
    if (result2 == NULL) {
        unlink(param_filename);
        unlink(key_filename);
        return NULL;
    }
    free(result2);
    
    // Ellenőrizzük, hogy a kulcsfájl létrejött-e
    FILE* key_file = fopen(key_filename, "r");
    if (key_file == NULL) {
        unlink(param_filename);
        unlink(key_filename);
        return NULL;
    }
    fclose(key_file);
    
    // 3. A kulcs PEM formátumban történő kiolvasása
    char command3[512];
    snprintf(command3, sizeof(command3), "openssl dsa -in %s -outform PEM 2>/dev/null", key_filename);
    
    char* pem_key = execute_command(command3);
    
    // 4. Ideiglenes fájlok törlése
    unlink(param_filename);
    unlink(key_filename);
    
    return pem_key;
}