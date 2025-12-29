#include <iostream>
#include <string>
#include <memory>
#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <openssl/err.h>
#include <openssl/evp.h>
#include <cstdio>

std::string create_private_key() {
    // Alapértelmezett kulcshossz
    const int key_length = 2048;
    
    // Inicializáljuk az OpenSSL-t
    OpenSSL_add_all_algorithms();
    ERR_load_crypto_strings();
    
    // RSA kontextus létrehozása
    EVP_PKEY_CTX* ctx = EVP_PKEY_CTX_new_id(EVP_PKEY_RSA, nullptr);
    if (!ctx) {
        ERR_print_errors_fp(stderr);
        return "";
    }
    
    // Kontextus inicializálása kulcsgeneráláshoz
    if (EVP_PKEY_keygen_init(ctx) <= 0) {
        ERR_print_errors_fp(stderr);
        EVP_PKEY_CTX_free(ctx);
        return "";
    }
    
    // RSA kulcshossz beállítása
    if (EVP_PKEY_CTX_set_rsa_keygen_bits(ctx, key_length) <= 0) {
        ERR_print_errors_fp(stderr);
        EVP_PKEY_CTX_free(ctx);
        return "";
    }
    
    // Kulcsgenerálás
    EVP_PKEY* pkey = nullptr;
    if (EVP_PKEY_keygen(ctx, &pkey) <= 0) {
        ERR_print_errors_fp(stderr);
        EVP_PKEY_CTX_free(ctx);
        return "";
    }
    
    // Kontextus felszabadítása
    EVP_PKEY_CTX_free(ctx);
    
    // PEM formátumú stringbe írás
    BIO* bio = BIO_new(BIO_s_mem());
    if (!bio) {
        ERR_print_errors_fp(stderr);
        EVP_PKEY_free(pkey);
        return "";
    }
    
    // Privát kulcs írása PEM formátumban
    if (!PEM_write_bio_PrivateKey(bio, pkey, nullptr, nullptr, 0, nullptr, nullptr)) {
        ERR_print_errors_fp(stderr);
        BIO_free(bio);
        EVP_PKEY_free(pkey);
        return "";
    }
    
    // Adatok kiolvasása a BIO-ból
    char* pem_data = nullptr;
    long pem_size = BIO_get_mem_data(bio, &pem_data);
    
    std::string result(pem_data, pem_size);
    
    // Erőforrások felszabadítása
    BIO_free(bio);
    EVP_PKEY_free(pkey);
    
    // OpenSSL takarítás
    EVP_cleanup();
    CRYPTO_cleanup_all_ex_data();
    ERR_free_strings();
    
    return result;
}