#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

/* shell agindua exekutatzeko eta bere irteera harrapatzeko funtzioa; deitzaileak memoria askatzeaz arduratu behar du; EZ da funtzio hau inplementatu behar, emanda dago baina lehenik deklaratu behar da erabilitzeko. */
char* execute_command(const char* command);

/* DSA gako pribatu bat sortu, PEM formatuan esportatu, eta string gisa itzuli.
Hints: DSA paramfile bat eta DSA gako pribatu bat sortzeko shell aginduak exekutatu:
1. `openssl dsaparam -out <parametarako gorde beharreko fitxategi temporala> <gako_luzera>`
2. `openssl gendsa <parametarako gorde beharreko fitxategi temporala>`
DSA parametro fitxategirako izen temporala sortzeko `char param_filename[] = "/tmp/tempXXXXXX"; int fd = mkstemp(param_filename);` erabil dezakezu.

@return Sortutako DSA gako pribatua PEM formatuan, edo NULL errore bat gertatu bada. */
char* create_dsa_key() {
    char param_filename[] = "/tmp/tempXXXXXX";
    int fd = mkstemp(param_filename);
    if (fd == -1) {
        return NULL;  // Errorea fitxategia sortzerakoan
    }
    close(fd); // Fitxategi desblokeatu

    // DSA parametroak sortu
    char command1[256];
    snprintf(command1, sizeof(command1), "openssl dsaparam -out %s 2048", param_filename);
    if (execute_command(command1) == NULL) {
        unlink(param_filename); // Fitxategia ezabatu errore bat gertatuz
        return NULL;
    }

    // DSA gako pribatua sortu
    char command2[256];
    snprintf(command2, sizeof(command2), "openssl gendsa -outform PEM -out private_key.pem %s", param_filename);
    if (execute_command(command2) == NULL) {
        unlink(param_filename); // Fitxategia ezabatu errore bat gertatuz
        return NULL;
    }

    // Parametro fitxategia ezabatu
    unlink(param_filename);
    
    // Pribatua irakurri eta itzuli
    FILE *file = fopen("private_key.pem", "r");
    if (file == NULL) {
        return NULL; // Errorea fitxategia irakurtzerakoan
    }

    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *key = malloc(length + 1);
    if (key == NULL) {
        fclose(file);
        return NULL; // Memoria ez da eskuratu
    }

    fread(key, 1, length, file);
    key[length] = '\0'; // Null terminatzailea gehitu
    fclose(file);

    // Pribatua eskuratu ondoren, fitxategia ezabatu
    unlink("private_key.pem");
    
    return key;
}