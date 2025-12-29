#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/evp.h>
#include <openssl/err.h>

char* hash_certificate(const char *cert) {
    EVP_MD_CTX *mdctx = NULL;
    const EVP_MD *md = NULL;
    unsigned char hash[EVP_MAX_MD_SIZE];
    unsigned int hash_len = 0;
    char *hex_hash = NULL;
    
    // Inizializza le librerie OpenSSL se necessario
    OpenSSL_add_all_digests();
    
    // Crea il contesto per l'hash
    mdctx = EVP_MD_CTX_create();
    if (mdctx == NULL) {
        return NULL;
    }
    
    // Seleziona l'algoritmo di hash (SHA-256 è una scelta sicura)
    md = EVP_sha256();
    if (md == NULL) {
        EVP_MD_CTX_destroy(mdctx);
        return NULL;
    }
    
    // Inizializza il contesto con l'algoritmo scelto
    if (EVP_DigestInit_ex(mdctx, md, NULL) != 1) {
        EVP_MD_CTX_destroy(mdctx);
        return NULL;
    }
    
    // Calcola l'hash del certificato
    if (EVP_DigestUpdate(mdctx, cert, strlen(cert)) != 1) {
        EVP_MD_CTX_destroy(mdctx);
        return NULL;
    }
    
    // Finalizza l'hash
    if (EVP_DigestFinal_ex(mdctx, hash, &hash_len) != 1) {
        EVP_MD_CTX_destroy(mdctx);
        return NULL;
    }
    
    // Alloca memoria per la stringa esadecimale (2 caratteri per byte + 1 per il terminatore)
    hex_hash = (char*)malloc((hash_len * 2) + 1);
    if (hex_hash == NULL) {
        EVP_MD_CTX_destroy(mdctx);
        return NULL;
    }
    
    // Converti l'hash in formato esadecimale
    for (unsigned int i = 0; i < hash_len; i++) {
        sprintf(hex_hash + (i * 2), "%02x", hash[i]);
    }
    hex_hash[hash_len * 2] = '\0';
    
    // Pulisci e libera le risorse
    EVP_MD_CTX_destroy(mdctx);
    
    return hex_hash;
}