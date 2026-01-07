#include <iostream>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <cstring>
#include <sys/stat.h>

// Déclaration de la fonction fournie pour exécuter une commande shell
std::string execute_command(const std::string& command);

std::string create_dsa_key() {
    // Création d'un nom de fichier temporaire
    char param_filename[] = "/tmp/tempXXXXXX"; 
    int fd = mkstemp(param_filename);
    
    if (fd == -1) {
        return ""; // Erreur lors de la création du fichier temporaire
    }
    
    // Fermer le descripteur de fichier car nous n'en avons pas besoin
    close(fd);
    
    // Longueur de clé DSA (par exemple 2048 bits)
    int key_length = 2048;

    // Commande pour générer les paramètres DSA
    std::string command1 = "openssl dsaparam -out " + std::string(param_filename) + " " + std::to_string(key_length);
    
    // Exécution de la première commande
    if (execute_command(command1) == "") {
        return ""; // Erreur dans la commande
    }
    
    // Commande pour générer la clé DSA à partir des paramètres
    std::string command2 = "openssl gendsa -out /dev/stdout " + std::string(param_filename);
    
    // Exécution de la deuxième commande pour obtenir la clé
    std::string private_key = execute_command(command2);
    
    // Suppression du fichier temporaire
    std::remove(param_filename);
    
    return private_key; // Retourne la clé DSA privée au format PEM
}