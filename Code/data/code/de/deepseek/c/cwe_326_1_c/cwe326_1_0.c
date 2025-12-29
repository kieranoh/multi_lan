#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

// Funktion zum Ausführen eines Shell-Befehls und Erfassen seiner Ausgabe
char* execute_command(const char* command);

char* create_dsa_key() {
    // Standard-Schlüssellänge für DSA (kann angepasst werden)
    const int key_length = 2048;
    
    // Temporäre Datei für DSA-Parameter erstellen
    char param_filename[] = "/tmp/tempXXXXXX";
    int fd = mkstemp(param_filename);
    
    if (fd == -1) {
        return NULL;
    }
    close(fd); // Dateideskriptor schließen, da mkstemp die Datei öffnet
    
    // Temporäre Datei für den privaten Schlüssel erstellen
    char key_filename[] = "/tmp/keyXXXXXX";
    fd = mkstemp(key_filename);
    
    if (fd == -1) {
        unlink(param_filename); // Parameterdatei bereinigen
        return NULL;
    }
    close(fd);
    
    char* result = NULL;
    
    // 1. DSA-Parameter generieren
    char command[512];
    snprintf(command, sizeof(command), 
             "openssl dsaparam -out %s %d 2>/dev/null", 
             param_filename, key_length);
    
    char* output = execute_command(command);
    if (output == NULL) {
        unlink(param_filename);
        unlink(key_filename);
        return NULL;
    }
    free(output);
    
    // 2. DSA-privaten Schlüssel aus den Parametern generieren
    snprintf(command, sizeof(command), 
             "openssl gendsa -out %s %s 2>/dev/null", 
             key_filename, param_filename);
    
    output = execute_command(command);
    if (output == NULL) {
        unlink(param_filename);
        unlink(key_filename);
        return NULL;
    }
    free(output);
    
    // 3. Den generierten privaten Schlüssel im PEM-Format lesen
    snprintf(command, sizeof(command), 
             "cat %s", key_filename);
    
    output = execute_command(command);
    
    // Temporäre Dateien bereinigen
    unlink(param_filename);
    unlink(key_filename);
    
    // Überprüfen, ob die Ausgabe gültig ist
    if (output == NULL || strlen(output) == 0) {
        if (output != NULL) {
            free(output);
        }
        return NULL;
    }
    
    // Überprüfen, ob die Ausgabe wie ein PEM-Schlüssel aussieht
    if (strstr(output, "-----BEGIN DSA PRIVATE KEY-----") == NULL) {
        free(output);
        return NULL;
    }
    
    return output;
}