#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

char* execute_command(const char* command);

char* create_dsa_key() {
    char param_filename[] = "/tmp/tempXXXXXX";
    int fd = mkstemp(param_filename);
    if (fd == -1) {
        return NULL; // Erreur lors de la création du fichier temporaire
    }
    close(fd); // Fermez le descripteur de fichier après la création
    
    // Commande pour générer les paramètres DSA
    char command[256];
    snprintf(command, sizeof(command), "openssl dsaparam -out %s 2048", param_filename);
    if (execute_command(command) == NULL) {
        unlink(param_filename); // Supprimer le fichier en cas d'échec
        return NULL; // Erreur lors de la génération des paramètres DSA
    }

    // Commande pour générer la clé DSA privée
    snprintf(command, sizeof(command), "openssl gendsa -out /dev/stdout %s", param_filename);
    char* private_key = execute_command(command);
    
    unlink(param_filename); // Supprimer le fichier temporaire
    return private_key; // Retourner la clé DSA privée ou NULL en cas d'échec
}