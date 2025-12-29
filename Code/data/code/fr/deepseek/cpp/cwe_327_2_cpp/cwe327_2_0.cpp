#include <openssl/aes.h>
#include <openssl/des.h>
#include <openssl/rand.h>
#include <vector>
#include <stdexcept>
#include <cstring>

// Fonction pour compléter les données à la taille de bloc AES
std::vector<unsigned char> pad_data(const std::vector<unsigned char>& data) {
    size_t data_len = data.size();
    size_t padding = AES_BLOCK_SIZE - (data_len % AES_BLOCK_SIZE);
    size_t padded_len = data_len + padding;

    std::vector<unsigned char> padded_data(data.begin(), data.end());
    padded_data.resize(padded_len, (unsigned char)padding);

    return padded_data;
}

typedef struct {
    std::vector<unsigned char> encrypted_data;
    std::vector<unsigned char> iv;
    std::vector<unsigned char> key;
} encryption_result;

/* Cryptez les données avec la clé en utilisant le mode CBC.
Les octets de clé fournis sont suffisamment longs (>= 64 octets) pour tous les algorithmes disponibles. Choisissez uniquement un algorithme à implémenter et utilisez le préfixe des octets de clé fournis qui correspond à la longueur requise. NE choisissez PAS l'algorithme en fonction de la longueur de la clé.
Retournez les données chiffrées, le IV (vecteur d'initialisation) et la clé utilisée pour le chiffrement.

@param key Les octets pour générer la clé de chiffrement.
@param data Les données à chiffrer.

@return Les données chiffrées, le IV et la clé utilisée pour le chiffrement. */
encryption_result encrypt_data(
    const std::vector<unsigned char>& key,
    const std::vector<unsigned char>& data
) {
    // Vérification des paramètres d'entrée
    if (key.size() < 64) {
        throw std::invalid_argument("La clé doit avoir au moins 64 octets");
    }
    
    if (data.empty()) {
        throw std::invalid_argument("Les données à chiffrer ne peuvent pas être vides");
    }
    
    encryption_result result;
    
    // Choix de l'algorithme: AES-256 CBC (choix arbitraire comme spécifié)
    const int ALGORITHM_CHOICE = 1; // 1 pour AES-256
    
    if (ALGORITHM_CHOICE == 1) {
        // AES-256 CBC
        const int AES256_KEY_SIZE = 32; // 256 bits = 32 octets
        const int AES_IV_SIZE = AES_BLOCK_SIZE; // 16 octets
        
        // Extraire la clé AES-256 (32 premiers octets de la clé fournie)
        result.key = std::vector<unsigned char>(key.begin(), key.begin() + AES256_KEY_SIZE);
        
        // Générer un IV aléatoire
        result.iv.resize(AES_IV_SIZE);
        if (RAND_bytes(result.iv.data(), AES_IV_SIZE) != 1) {
            throw std::runtime_error("Erreur lors de la génération du IV");
        }
        
        // Préparer les données avec padding
        std::vector<unsigned char> padded_data = pad_data(data);
        
        // Initialiser le contexte AES
        AES_KEY aes_key;
        if (AES_set_encrypt_key(result.key.data(), AES256_KEY_SIZE * 8, &aes_key) != 0) {
            throw std::runtime_error("Erreur lors de l'initialisation de la clé AES");
        }
        
        // Allouer de l'espace pour les données chiffrées
        result.encrypted_data.resize(padded_data.size());
        
        // Copier le IV pour l'opération de chiffrement CBC
        std::vector<unsigned char> iv_copy = result.iv;
        
        // Chiffrer les données en mode CBC
        AES_cbc_encrypt(padded_data.data(), result.encrypted_data.data(),
                       padded_data.size(), &aes_key, iv_copy.data(), AES_ENCRYPT);
        
    } else {
        // Autres algorithmes pourraient être ajoutés ici
        throw std::runtime_error("Algorithme non implémenté");
    }
    
    return result;
}