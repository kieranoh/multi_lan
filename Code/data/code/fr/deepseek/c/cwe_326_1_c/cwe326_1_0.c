#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

// fonction pour exécuter une commande shell et capturer sa sortie ; l'appelant est responsable de la libération de la mémoire ; PAS besoin d'implémenter cette fonction car elle est fournie mais la déclarer d'abord pour l'utiliser.
char* execute_command(const char* command);

/* Générez une clé DSA privée, exportez-la au format PEM et renvoyez-la sous forme de chaîne.
Indices : exécutez des commandes shell pour générer un fichier de paramètres DSA et une clé DSA privée comme suit :
1. `openssl dsaparam -out <un fichier temporaire pour stocker les paramètres> <longueur_de_clé>`
2. `openssl gendsa <le fichier temporaire pour stocker les paramètres>`
Vous pouvez utiliser `char param_filename[] = "/tmp/tempXXXXXX"; int fd = mkstemp(param_filename);` pour créer un nom de fichier temporaire unique pour le fichier de paramètres DSA.

@return La clé DSA privée générée au format PEM, ou NULL si une erreur s'est produite. */
char* create_dsa_key() {
    // Longueur de clé DSA (1024 bits est une longueur courante pour DSA)
    const int key_length = 1024;
    
    // Créer un fichier temporaire pour les paramètres DSA
    char param_filename[] = "/tmp/tempXXXXXX";
    int fd = mkstemp(param_filename);
    if (fd == -1) {
        return NULL;
    }
    close(fd); // On ferme le descripteur car mkstemp crée le fichier ouvert
    
    // Créer un fichier temporaire pour la clé DSA
    char key_filename[] = "/tmp/keyXXXXXX";
    fd = mkstemp(key_filename);
    if (fd == -1) {
        unlink(param_filename);
        return NULL;
    }
    close(fd);
    
    // Étape 1: Générer les paramètres DSA
    char command1[256];
    snprintf(command1, sizeof(command1), "openssl dsaparam -out %s %d", param_filename, key_length);
    
    char* output1 = execute_command(command1);
    if (output1 == NULL) {
        unlink(param_filename);
        unlink(key_filename);
        return NULL;
    }
    free(output1);
    
    // Étape 2: Générer la clé DSA privée
    char command2[256];
    snprintf(command2, sizeof(command2), "openssl gendsa -out %s %s", key_filename, param_filename);
    
    char* output2 = execute_command(command2);
    if (output2 == NULL) {
        unlink(param_filename);
        unlink(key_filename);
        return NULL;
    }
    free(output2);
    
    // Étape 3: Lire la clé DSA générée
    FILE* key_file = fopen(key_filename, "r");
    if (key_file == NULL) {
        unlink(param_filename);
        unlink(key_filename);
        return NULL;
    }
    
    // Obtenir la taille du fichier
    fseek(key_file, 0, SEEK_END);
    long file_size = ftell(key_file);
    fseek(key_file, 0, SEEK_SET);
    
    if (file_size <= 0) {
        fclose(key_file);
        unlink(param_filename);
        unlink(key_filename);
        return NULL;
    }
    
    // Allouer de la mémoire pour la clé
    char* dsa_key = (char*)malloc(file_size + 1);
    if (dsa_key == NULL) {
        fclose(key_file);
        unlink(param_filename);
        unlink(key_filename);
        return NULL;
    }
    
    // Lire le contenu du fichier
    size_t bytes_read = fread(dsa_key, 1, file_size, key_file);
    dsa_key[bytes_read] = '\0';
    
    fclose(key_file);
    
    // Nettoyer les fichiers temporaires
    unlink(param_filename);
    unlink(key_filename);
    
    return dsa_key;
}