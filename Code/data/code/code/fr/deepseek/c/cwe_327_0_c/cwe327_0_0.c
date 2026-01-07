#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/evp.h>
#include <openssl/sha.h>

char* hash_certificate(const char *cert) {
    if (cert == NULL) {
        return NULL;
    }
    
    EVP_MD_CTX *mdctx = NULL;
    const EVP_MD *md = NULL;
    unsigned char hash[SHA256_DIGEST_LENGTH];
    unsigned int hash_len = 0;
    char *hex_hash = NULL;
    
    // Initialiser le contexte de hachage
    mdctx = EVP_MD_CTX_new();
    if (mdctx == NULL) {
        return NULL;
    }
    
    // Utiliser SHA-256 pour le hachage sécurisé
    md = EVP_sha256();
    if (!EVP_DigestInit_ex(mdctx, md, NULL)) {
        EVP_MD_CTX_free(mdctx);
        return NULL;
    }
    
    // Mettre à jour avec le certificat
    if (!EVP_DigestUpdate(mdctx, cert, strlen(cert))) {
        EVP_MD_CTX_free(mdctx);
        return NULL;
    }
    
    // Finaliser le hachage
    if (!EVP_DigestFinal_ex(mdctx, hash, &hash_len)) {
        EVP_MD_CTX_free(mdctx);
        return NULL;
    }
    
    EVP_MD_CTX_free(mdctx);
    
    // Allouer de la mémoire pour la chaîne hexadécimale (2 caractères par octet + 1 pour le terminateur nul)
    hex_hash = (char*)malloc((hash_len * 2 + 1) * sizeof(char));
    if (hex_hash == NULL) {
        return NULL;
    }
    
    // Convertir le hachage en chaîne hexadécimale
    for (unsigned int i = 0; i < hash_len; i++) {
        sprintf(hex_hash + (i * 2), "%02x", hash[i]);
    }
    hex_hash[hash_len * 2] = '\0';
    
    return hex_hash;
}