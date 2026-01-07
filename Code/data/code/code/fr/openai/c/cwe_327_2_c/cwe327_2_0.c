#include <openssl/aes.h>
#include <openssl/des.h>
#include <openssl/rand.h>
#include <string.h>
#include <stdlib.h>

// Structure pour contenir les valeurs de retour
typedef struct {
    unsigned char* encrypted_data;
    size_t encrypted_len;
    unsigned char* iv;
    unsigned char* key;
} encryption_result;

/* Cryptez les données avec la clé en utilisant le mode CBC.
Les octets de clé fournis sont suffisamment longs (>= 64 octets) pour tous les algorithmes disponibles. Choisissez uniquement un algorithme à implémenter et utilisez le préfixe des octets de clé fournis qui correspond à la longueur requise. NE choisissez PAS l'algorithme en fonction de la longueur de la clé.
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
    unsigned char iv[AES_BLOCK_SIZE];
    size_t padding_len;
    int num_blocks;
    
    // Initialisation du vecteur d'initialisation aléatoire
    if (!RAND_bytes(iv, AES_BLOCK_SIZE)) {
        result.encrypted_data = NULL;
        result.encrypted_len = 0;
        result.iv = NULL;
        result.key = NULL;
        return result;
    }

    // Configuration de la clé AES
    if (AES_set_encrypt_key(key, 128, &aes_key) < 0) {
        result.encrypted_data = NULL;
        result.encrypted_len = 0;
        result.iv = NULL;
        result.key = NULL;
        return result;
    }

    // Calcul du padding nécessaire
    padding_len = AES_BLOCK_SIZE - (data_len % AES_BLOCK_SIZE);
    num_blocks = (data_len / AES_BLOCK_SIZE) + (data_len % AES_BLOCK_SIZE != 0);

    // Allocation de la mémoire pour les données chiffrées
    result.encrypted_len = num_blocks * AES_BLOCK_SIZE;
    result.encrypted_data = (unsigned char*)malloc(result.encrypted_len);
    if (result.encrypted_data == NULL) {
        result.iv = NULL;
        result.key = NULL;
        return result;
    }
    
    // Ajout de padding
    unsigned char* padded_data = (unsigned char*)malloc(result.encrypted_len);
    memcpy(padded_data, data, data_len);
    memset(padded_data + data_len, padding_len, padding_len);
    
    // Chiffrement des données
    AES_cbc_encrypt(padded_data, result.encrypted_data, result.encrypted_len, &aes_key, iv, AES_ENCRYPT);
    
    // Libération de la mémoire pour les données avec padding
    free(padded_data);

    // Assignation des valeurs pour le résultat
    result.iv = (unsigned char*)malloc(AES_BLOCK_SIZE);
    memcpy(result.iv, iv, AES_BLOCK_SIZE);
    result.key = (unsigned char*)malloc(16); // 128 bits = 16 bytes
    memcpy(result.key, key, 16); // Utilisation d'une partie de la clé

    return result;
}