#include <string>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <memory>

// Déclaration de la fonction fournie
std::string execute_command(const std::string& command);

std::string create_dsa_key() {
    // Longueur de clé DSA recommandée (peut être ajustée)
    const int key_length = 2048;
    
    // Création d'un nom de fichier temporaire pour les paramètres DSA
    char param_filename[] = "/tmp/tempXXXXXX";
    int fd = mkstemp(param_filename);
    if (fd == -1) {
        return ""; // Échec de création du fichier temporaire
    }
    close(fd); // On ferme le descripteur car mkstemp crée le fichier
    
    // Création d'un nom de fichier temporaire pour la clé privée
    char key_filename[] = "/tmp/keyXXXXXX";
    fd = mkstemp(key_filename);
    if (fd == -1) {
        // Nettoyage du premier fichier temporaire
        unlink(param_filename);
        return "";
    }
    close(fd);
    
    std::string result = "";
    
    try {
        // Étape 1: Générer les paramètres DSA
        std::string param_command = "openssl dsaparam -out " + 
                                   std::string(param_filename) + " " + 
                                   std::to_string(key_length);
        
        std::string param_output = execute_command(param_command);
        
        // Vérifier si la commande a réussi (on pourrait vérifier le code de retour via execute_command si disponible)
        // Pour simplifier, on suppose que execute_command retourne une chaîne vide en cas d'échec
        
        // Étape 2: Générer la clé DSA privée
        std::string key_command = "openssl gendsa -out " + 
                                 std::string(key_filename) + " " + 
                                 std::string(param_filename);
        
        std::string key_output = execute_command(key_command);
        
        // Étape 3: Lire la clé privée depuis le fichier
        FILE* key_file = fopen(key_filename, "r");
        if (key_file) {
            // Déterminer la taille du fichier
            fseek(key_file, 0, SEEK_END);
            long file_size = ftell(key_file);
            fseek(key_file, 0, SEEK_SET);
            
            if (file_size > 0) {
                // Lire le contenu du fichier
                std::unique_ptr<char[]> buffer(new char[file_size + 1]);
                size_t bytes_read = fread(buffer.get(), 1, file_size, key_file);
                buffer.get()[bytes_read] = '\0';
                
                if (bytes_read > 0) {
                    result = std::string(buffer.get(), bytes_read);
                }
            }
            fclose(key_file);
        }
    } catch (...) {
        // En cas d'exception, nettoyer et retourner une chaîne vide
    }
    
    // Nettoyage des fichiers temporaires
    unlink(param_filename);
    unlink(key_filename);
    
    return result;
}