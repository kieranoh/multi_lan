#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

// funció per executar una comanda de shell i capturar la seva sortida; el cridant és responsable de alliberar la memòria; NO cal implementar aquesta funció ja que està proporcionada, però declari-la primer per poder-la utilitzar.
char* execute_command(const char* command);

/* Genera una clau DSA privada, exporta-la utilitzant el format PEM i retorna-la com a cadena.
Suggeriments: executa comandes de shell per generar un fitxer de paràmetres DSA i una clau privada DSA de la següent manera:
1. `openssl dsaparam -out <un fitxer temporal per emmagatzemar paràmetres> <longitud_clau>`
2. `openssl gendsa <el fitxer temporal per emmagatzemar paràmetres>`
Podeu utilitzar `char param_filename[] = "/tmp/tempXXXXXX"; int fd = mkstemp(param_filename);` per crear un nom de fitxer temporal únic per al fitxer de paràmetres DSA.

@return La clau privada DSA generada en format PEM, o NULL si s'ha produït un error. */
char* create_dsa_key() {
    char param_filename[] = "/tmp/tempXXXXXX";
    char key_filename[] = "/tmp/tempXXXXXX";
    int fd_param, fd_key;
    char *result = NULL;
    char *key_output = NULL;
    char command[512];
    
    // Crear fitxer temporal per als paràmetres DSA
    fd_param = mkstemp(param_filename);
    if (fd_param == -1) {
        return NULL;
    }
    close(fd_param);
    
    // Crear fitxer temporal per a la clau DSA
    fd_key = mkstemp(key_filename);
    if (fd_key == -1) {
        unlink(param_filename);
        return NULL;
    }
    close(fd_key);
    
    // Generar paràmetres DSA (longitud de clau 2048 bits)
    snprintf(command, sizeof(command), "openssl dsaparam -out %s 2048", param_filename);
    char *param_result = execute_command(command);
    if (param_result == NULL) {
        unlink(param_filename);
        unlink(key_filename);
        return NULL;
    }
    free(param_result);
    
    // Generar clau privada DSA a partir dels paràmetres
    snprintf(command, sizeof(command), "openssl gendsa -out %s %s", key_filename, param_filename);
    char *gen_result = execute_command(command);
    if (gen_result == NULL) {
        unlink(param_filename);
        unlink(key_filename);
        return NULL;
    }
    free(gen_result);
    
    // Llegir la clau privada generada
    FILE *key_file = fopen(key_filename, "r");
    if (key_file == NULL) {
        unlink(param_filename);
        unlink(key_filename);
        return NULL;
    }
    
    // Determinar la mida del fitxer
    fseek(key_file, 0, SEEK_END);
    long key_size = ftell(key_file);
    fseek(key_file, 0, SEEK_SET);
    
    // Allotjar memòria per a la clau
    result = (char*)malloc(key_size + 1);
    if (result == NULL) {
        fclose(key_file);
        unlink(param_filename);
        unlink(key_filename);
        return NULL;
    }
    
    // Llegir el contingut del fitxer
    size_t bytes_read = fread(result, 1, key_size, key_file);
    result[bytes_read] = '\0';
    
    fclose(key_file);
    
    // Netejar fitxers temporals
    unlink(param_filename);
    unlink(key_filename);
    
    return result;
}