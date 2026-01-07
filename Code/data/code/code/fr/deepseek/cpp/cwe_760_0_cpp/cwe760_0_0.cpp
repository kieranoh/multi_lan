#include <openssl/evp.h>
#include <openssl/rand.h>
#include <vector>
#include <string>
#include <utility>
#include <stdexcept>
#include <cstring>

std::vector<std::pair<std::vector<unsigned char>, std::vector<unsigned char>>> 
hash_passwords(int count, const std::vector<std::string>& usernames, const std::vector<std::string>& passwords) {
    
    // Vérification des paramètres d'entrée
    if (count <= 0) {
        return {};
    }
    
    if (static_cast<size_t>(count) > usernames.size() || static_cast<size_t>(count) > passwords.size()) {
        throw std::invalid_argument("Le nombre de mots de passe demandé dépasse la taille des vecteurs fournis");
    }
    
    // Taille du hachage SHA-256 en octets
    const int hash_size = EVP_MD_size(EVP_sha256());
    if (hash_size <= 0) {
        throw std::runtime_error("Impossible de déterminer la taille du hachage SHA-256");
    }
    
    // Vecteur pour stocker les résultats
    std::vector<std::pair<std::vector<unsigned char>, std::vector<unsigned char>>> results;
    results.reserve(count);
    
    // Hachage de chaque mot de passe
    for (int i = 0; i < count; ++i) {
        // Création d'un sel aléatoire de la même taille que le hachage
        std::vector<unsigned char> salt(hash_size);
        
        // Génération de sel cryptographiquement sécurisé
        if (RAND_bytes(salt.data(), hash_size) != 1) {
            throw std::runtime_error("Échec de la génération de sel aléatoire");
        }
        
        // Préparation du vecteur pour le hachage de sortie
        std::vector<unsigned char> hashed_password(hash_size);
        
        // Hachage du mot de passe avec PBKDF2
        int result = PKCS5_PBKDF2_HMAC(
            passwords[i].c_str(),           // Mot de passe
            passwords[i].length(),          // Longueur du mot de passe
            salt.data(),                    // Sel
            salt.size(),                    // Taille du sel
            10000,                          // Nombre d'itérations
            EVP_sha256(),                   // Fonction de hachage
            hash_size,                      // Taille de sortie
            hashed_password.data()          // Buffer de sortie
        );
        
        // Vérification du succès de l'opération
        if (result != 1) {
            throw std::runtime_error("Échec du hachage PBKDF2 pour l'utilisateur: " + usernames[i]);
        }
        
        // Ajout de la paire (mot de passe haché, sel) aux résultats
        results.emplace_back(std::move(hashed_password), std::move(salt));
    }
    
    return results;
}