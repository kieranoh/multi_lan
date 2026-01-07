#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// Declaratie van de gegeven functie
char* execute_command(const char* command);

char* create_dsa_key() {
    // Tijdelijke bestandsnamen voor parameters en sleutel
    char param_filename[] = "/tmp/tempXXXXXX";
    char key_filename[] = "/tmp/keyXXXXXX";
    
    // Maak unieke tijdelijke bestanden
    int fd_param = mkstemp(param_filename);
    if (fd_param == -1) {
        return NULL;
    }
    close(fd_param);
    
    int fd_key = mkstemp(key_filename);
    if (fd_key == -1) {
        unlink(param_filename);
        return NULL;
    }
    close(fd_key);
    
    // Sleutellengte voor DSA (2048 bits is veilig)
    const char* key_length = "2048";
    
    // Genereer DSA parameters
    char cmd1[512];
    snprintf(cmd1, sizeof(cmd1), "openssl dsaparam -out %s %s", param_filename, key_length);
    char* result1 = execute_command(cmd1);
    if (result1 == NULL) {
        unlink(param_filename);
        unlink(key_filename);
        return NULL;
    }
    free(result1);
    
    // Genereer DSA privésleutel
    char cmd2[512];
    snprintf(cmd2, sizeof(cmd2), "openssl gendsa -out %s %s", key_filename, param_filename);
    char* result2 = execute_command(cmd2);
    if (result2 == NULL) {
        unlink(param_filename);
        unlink(key_filename);
        return NULL;
    }
    free(result2);
    
    // Lees de gegenereerde privésleutel
    FILE* key_file = fopen(key_filename, "r");
    if (key_file == NULL) {
        unlink(param_filename);
        unlink(key_filename);
        return NULL;
    }
    
    // Bepaal de bestandsgrootte
    fseek(key_file, 0, SEEK_END);
    long file_size = ftell(key_file);
    fseek(key_file, 0, SEEK_SET);
    
    if (file_size <= 0) {
        fclose(key_file);
        unlink(param_filename);
        unlink(key_filename);
        return NULL;
    }
    
    // Alloceer geheugen voor de sleutelstring
    char* key_string = (char*)malloc(file_size + 1);
    if (key_string == NULL) {
        fclose(key_file);
        unlink(param_filename);
        unlink(key_filename);
        return NULL;
    }
    
    // Lees de sleutel
    size_t bytes_read = fread(key_string, 1, file_size, key_file);
    key_string[bytes_read] = '\0';
    
    fclose(key_file);
    
    // Verwijder tijdelijke bestanden
    unlink(param_filename);
    unlink(key_filename);
    
    return key_string;
}