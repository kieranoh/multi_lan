#include <openssl/aes.h>
#include <openssl/des.h>
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
    encryption_result result = {NULL, 0, NULL, NULL};
    
    // Vérification des paramètres d'entrée
    if (key == NULL || data == NULL || key_len < 16) {
        return result;
    }
    
    // Choix de l'algorithme (AES-256-CBC dans ce cas)
    // On utilise toujours AES-256-CBC indépendamment de la longueur de la clé
    const int algorithm = 1; // 1 pour AES-256-CBC
    
    if (algorithm == 1) { // AES-256-CBC
        // Taille de la clé pour AES-256
        const size_t aes_key_len = 32; // 256 bits = 32 octets
        const size_t iv_len = AES_BLOCK_SIZE; // 16 octets pour AES
        
        // Vérifier que la clé fournie est suffisamment longue
        if (key_len < aes_key_len) {
            return result;
        }
        
        // Allouer et copier la clé
        result.key = (unsigned char*)malloc(aes_key_len);
        if (result.key == NULL) {
            return result;
        }
        memcpy(result.key, key, aes_key_len);
        
        // Allouer et générer le IV
        result.iv = (unsigned char*)malloc(iv_len);
        if (result.iv == NULL) {
            free(result.key);
            result.key = NULL;
            return result;
        }
        
        // Générer un IV aléatoire
        if (RAND_bytes(result.iv, iv_len) != 1) {
            free(result.key);
            free(result.iv);
            result.key = NULL;
            result.iv = NULL;
            return result;
        }
        
        // Calculer la taille des données chiffrées (alignées sur la taille du bloc)
        size_t padded_len = data_len + (AES_BLOCK_SIZE - (data_len % AES_BLOCK_SIZE));
        if (data_len % AES_BLOCK_SIZE == 0) {
            padded_len = data_len + AES_BLOCK_SIZE; // Ajouter un bloc complet de bourrage
        }
        
        // Allouer mémoire pour les données chiffrées
        result.encrypted_data = (unsigned char*)malloc(padded_len);
        if (result.encrypted_data == NULL) {
            free(result.key);
            free(result.iv);
            result.key = NULL;
            result.iv = NULL;
            return result;
        }
        
        // Préparer les structures AES
        AES_KEY aes_key;
        if (AES_set_encrypt_key(result.key, 256, &aes_key) != 0) {
            free(result.key);
            free(result.iv);
            free(result.encrypted_data);
            result.key = NULL;
            result.iv = NULL;
            result.encrypted_data = NULL;
            return result;
        }
        
        // Copier les données d'entrée dans un buffer temporaire avec bourrage PKCS#7
        unsigned char* padded_data = (unsigned char*)malloc(padded_len);
        if (padded_data == NULL) {
            free(result.key);
            free(result.iv);
            free(result.encrypted_data);
            result.key = NULL;
            result.iv = NULL;
            result.encrypted_data = NULL;
            return result;
        }
        
        memcpy(padded_data, data, data_len);
        
        // Appliquer le bourrage PKCS#7
        unsigned char pad_value = padded_len - data_len;
        for (size_t i = data_len; i < padded_len; i++) {
            padded_data[i] = pad_value;
        }
        
        // Chiffrer les données avec AES-CBC
        AES_cbc_encrypt(padded_data, result.encrypted_data, padded_len, 
                       &aes_key, result.iv, AES_ENCRYPT);
        
        result.encrypted_len = padded_len;
        
        // Nettoyer le buffer temporaire
        free(padded_data);
        
    } else {
        // Autres algorithmes non implémentés dans cet exemple
        return result;
    }
    
    return result;
}