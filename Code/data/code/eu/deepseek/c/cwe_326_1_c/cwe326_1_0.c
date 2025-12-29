#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

/* shell agindua exekutatzeko eta bere irteera harrapatzeko funtzioa; deitzaileak memoria askatzeaz arduratu behar du; EZ da funtzio hau inplementatu behar, emanda dago baina lehenik deklaratu behar da erabilitzeko. */
char* execute_command(const char* command);

char* create_dsa_key() {
    char param_filename[] = "/tmp/tempXXXXXX";
    char key_filename[] = "/tmp/tempXXXXXX";
    char* key_result = NULL;
    char command[512];
    int fd_param, fd_key;
    
    // Sortu parametro fitxategi temporala
    fd_param = mkstemp(param_filename);
    if (fd_param == -1) {
        return NULL;
    }
    close(fd_param);
    
    // Sortu gako fitxategi temporala
    fd_key = mkstemp(key_filename);
    if (fd_key == -1) {
        unlink(param_filename);
        return NULL;
    }
    close(fd_key);
    
    // 1. Sortu DSA parametroak (1024 biteko luzera)
    snprintf(command, sizeof(command), "openssl dsaparam -out %s 1024", param_filename);
    char* param_result = execute_command(command);
    if (param_result == NULL) {
        unlink(param_filename);
        unlink(key_filename);
        return NULL;
    }
    free(param_result);
    
    // 2. Sortu DSA gako pribatua parametro fitxategitik
    snprintf(command, sizeof(command), "openssl gendsa %s", param_filename);
    char* gen_result = execute_command(command);
    if (gen_result == NULL) {
        unlink(param_filename);
        unlink(key_filename);
        return NULL;
    }
    free(gen_result);
    
    // 3. Irakurri sortutako gakoa (stdout-en dago)
    // Berriro exekutatu gakoa fitxategi batera gordetzeko
    snprintf(command, sizeof(command), "openssl gendsa %s 2>/dev/null", param_filename);
    key_result = execute_command(command);
    
    // 4. Garbitu fitxategi temporalak
    unlink(param_filename);
    unlink(key_filename);
    
    return key_result;
}