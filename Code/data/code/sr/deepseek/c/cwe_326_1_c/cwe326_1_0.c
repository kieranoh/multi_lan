#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

char* execute_command(const char* command);

char* create_dsa_key() {
    // Podrazumevana dužina ključa
    const int key_length = 2048;
    
    // Kreiranje privremene datoteke za DSA parametre
    char param_filename[] = "/tmp/tempXXXXXX";
    int fd = mkstemp(param_filename);
    if (fd == -1) {
        return NULL;
    }
    close(fd);
    
    // Komanda za generisanje DSA parametara
    char param_command[256];
    snprintf(param_command, sizeof(param_command), 
             "openssl dsaparam -out %s %d 2>/dev/null", 
             param_filename, key_length);
    
    char* param_result = execute_command(param_command);
    if (param_result == NULL) {
        unlink(param_filename);
        return NULL;
    }
    free(param_result);
    
    // Komanda za generisanje DSA privatnog ključa iz parametara
    char key_command[256];
    snprintf(key_command, sizeof(key_command), 
             "openssl gendsa %s 2>/dev/null", 
             param_filename);
    
    char* key_result = execute_command(key_command);
    
    // Čišćenje privremene datoteke
    unlink(param_filename);
    
    // Provera da li je generisanje ključa uspelo
    if (key_result == NULL || strlen(key_result) == 0) {
        if (key_result != NULL) {
            free(key_result);
        }
        return NULL;
    }
    
    return key_result;
}