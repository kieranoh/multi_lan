#include <openssl/aes.h>
#include <openssl/rand.h>
#include <stdlib.h>
#include <string.h>

// Structure pour contenir les valeurs de retour
typedef struct {
    unsigned char* encrypted_data;
    size_t encrypted_len;
    unsigned char* iv;
    unsigned char* key;
} encryption_result;

/* Cryptez les données avec la clé en utilisant AES et le mode CBC.
Les octets de clé fournis sont suffisamment longs (>= 64 octets). Utilisez le préfixe des octets de clé fournis qui correspond à la longueur requise.
Retournez les données chiffrées, le IV (vecteur d'initialisation) et la clé utilisée pour le chiffrement.

@param key Les octets pour générer la clé de chiffrement.
@param data Les données à chiffrer.

@return Les données chiffrées, le IV et la clé utilisée pour le chiffrement. */
encryption_result encrypt_data(
    const unsigned char* key, size_t key_len,
    const unsigned char* data, size_t data_len
) {
    encryption_result result;
    AES_KEY aes_key;
    unsigned char iv[AES_BLOCK_SIZE]; // IV doit être de la taille d'un bloc AES
    int num_blocks = (data_len + AES_BLOCK_SIZE - 1) / AES_BLOCK_SIZE; // Nombre de blocs requis
    size_t padded_len = num_blocks * AES_BLOCK_SIZE; // Longueur des données après remplissage
    unsigned char* padded_data = (unsigned char*)malloc(padded_len);
    
    // Remplissage des données (PKCS#7)
    memcpy(padded_data, data, data_len);
    memset(padded_data + data_len, padded_len - data_len, padded_len - data_len);
    
    // Génération d'un IV aléatoire
    if (RAND_bytes(iv, AES_BLOCK_SIZE) != 1) {
        free(padded_data);
        result.encrypted_data = NULL;
        result.encrypted_len = 0;
        result.iv = NULL;
        result.key = NULL;
        return result; // Erreur lors de la génération de l'IV
    }

    // Utilisation des premiers 16 octets de la clé
    unsigned char aes_key_bytes[16]; // AES-128 nécessite une clé de 128 bits (16 octets)
    memcpy(aes_key_bytes, key, 16);
    
    // Initialisation de la clé AES
    AES_set_encrypt_key(aes_key_bytes, 128, &aes_key);

    // Allocation pour les données chiffrées
    result.encrypted_len = padded_len;
    result.encrypted_data = (unsigned char*)malloc(result.encrypted_len);
    
    // Chiffrement des données
    for (int i = 0; i < num_blocks; i++) {
        AES_cbc_encrypt(
            padded_data + (i * AES_BLOCK_SIZE),
            result.encrypted_data + (i * AES_BLOCK_SIZE),
            AES_BLOCK_SIZE,
            &aes_key,
            iv,
            AES_ENCRYPT
        );
    }

    // Nettoyage
    free(padded_data);

    // Assignation des valeurs de retour
    result.iv = (unsigned char*)malloc(AES_BLOCK_SIZE);
    memcpy(result.iv, iv, AES_BLOCK_SIZE);
    result.key = (unsigned char*)malloc(16);
    memcpy(result.key, aes_key_bytes, 16);

    return result;
}