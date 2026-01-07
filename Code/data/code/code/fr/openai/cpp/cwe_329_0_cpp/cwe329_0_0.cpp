#include <openssl/aes.h>
#include <openssl/rand.h>
#include <vector>
#include <tuple>
#include <stdexcept>

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
    // Vérification de la longueur de la clé pour AES-128 (16 octets), AES-192 (24 octets) et AES-256 (32 octets)
    if (key.size() < 16) {
        throw std::invalid_argument("Key size is too small");
    }

    // Choisir la longueur de la clé pour AES
    size_t key_length = 16; // AES-128
    std::vector<uint8_t> aes_key(key.begin(), key.begin() + key_length);

    // Créer un vecteur d'initialisation (IV)
    std::vector<uint8_t> iv(AES_BLOCK_SIZE);
    if (!RAND_bytes(iv.data(), iv.size())) {
        throw std::runtime_error("Failed to generate random IV");
    }

    // Remplissage des données
    std::vector<uint8_t> padded_data = pkcs7_pad(data, AES_BLOCK_SIZE);

    // Configuration de l'objet de chiffrement
    AES_KEY encrypt_key;
    if (AES_set_encrypt_key(aes_key.data(), 128, &encrypt_key) != 0) {
        throw std::runtime_error("Failed to set encryption key");
    }

    // Chiffrement des données
    std::vector<uint8_t> encrypted_data(padded_data.size());
    for (size_t i = 0; i < padded_data.size(); i += AES_BLOCK_SIZE) {
        AES_cbc_encrypt(padded_data.data() + i, encrypted_data.data() + i, AES_BLOCK_SIZE, &encrypt_key, iv.data(), AES_ENCRYPT);
    }

    return std::make_tuple(encrypted_data, iv, aes_key);
}