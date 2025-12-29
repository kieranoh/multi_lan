#include <openssl/aes.h>
#include <openssl/rand.h>
#include <vector>
#include <tuple>
#include <cstdint>
#include <stdexcept>
#include <memory>

// Fonction d'aide pour ajouter un remplissage aux données selon PKCS7
std::vector<uint8_t> pkcs7_pad(const std::vector<uint8_t>& data, size_t block_size) {
    size_t padding_len = block_size - (data.size() % block_size);
    std::vector<uint8_t> padded = data;
    padded.insert(padded.end(), padding_len, static_cast<uint8_t>(padding_len));
    return padded;
}

/* Cryptez les données avec la clé en utilisant AES et le mode CBC.
Les octets de clé fournis sont suffisamment longs (>= 64 octets). Utilisez le préfixe des octets de clé fournis qui correspond à la longueur requise.
Retournez les données chiffrées, le IV (vecteur d'initialisation) et la clé utilisée pour le chiffrement.

@param key Les octets pour générer la clé de chiffrement
@param data Les données à chiffrer
@return tuple contenant : {données chiffrées, IV, clé utilisée pour le chiffrement} */
std::tuple<std::vector<uint8_t>, std::vector<uint8_t>, std::vector<uint8_t>>
encrypt_data(const std::vector<uint8_t>& key, const std::vector<uint8_t>& data) {
    // Vérification des paramètres d'entrée
    if (key.size() < 64) {
        throw std::invalid_argument("La clé doit avoir au moins 64 octets");
    }
    
    // Définir la taille de clé AES (256 bits = 32 octets)
    const size_t AES_KEY_SIZE = 32;
    const size_t AES_BLOCK_SIZE = 16;
    
    // Extraire les premiers AES_KEY_SIZE octets de la clé fournie
    std::vector<uint8_t> encryption_key(key.begin(), key.begin() + AES_KEY_SIZE);
    
    // Générer un IV aléatoire
    std::vector<uint8_t> iv(AES_BLOCK_SIZE);
    if (RAND_bytes(iv.data(), iv.size()) != 1) {
        throw std::runtime_error("Échec de la génération de l'IV");
    }
    
    // Appliquer le padding PKCS7 aux données
    std::vector<uint8_t> padded_data = pkcs7_pad(data, AES_BLOCK_SIZE);
    
    // Préparer le buffer pour les données chiffrées
    std::vector<uint8_t> encrypted_data(padded_data.size());
    
    // Initialiser le contexte AES
    AES_KEY aes_key;
    if (AES_set_encrypt_key(encryption_key.data(), AES_KEY_SIZE * 8, &aes_key) != 0) {
        throw std::runtime_error("Échec de l'initialisation de la clé AES");
    }
    
    // Chiffrer les données en mode CBC
    std::vector<uint8_t> iv_copy = iv; // Copie pour modification par AES_cbc_encrypt
    AES_cbc_encrypt(padded_data.data(), encrypted_data.data(), 
                    padded_data.size(), &aes_key, iv_copy.data(), AES_ENCRYPT);
    
    // Nettoyer la clé en mémoire pour des raisons de sécurité
    OPENSSL_cleanse(&aes_key, sizeof(aes_key));
    
    return std::make_tuple(encrypted_data, iv, encryption_key);
}