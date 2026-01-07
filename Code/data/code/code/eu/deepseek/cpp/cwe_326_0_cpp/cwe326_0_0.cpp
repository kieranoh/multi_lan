#include <openssl/pem.h>
#include <openssl/rsa.h>
#include <openssl/evp.h>
#include <memory>
#include <string>
#include <cstdio>
#include <cstdlib>

std::string create_private_key() {
    // RSA gakoaren luzera zehaztu
    const int key_length = 2048;
    
    // RSA gakoaren parametroak konfiguratu
    EVP_PKEY_CTX* ctx = EVP_PKEY_CTX_new_id(EVP_PKEY_RSA, nullptr);
    if (!ctx) {
        return nullptr;
    }
    
    if (EVP_PKEY_keygen_init(ctx) <= 0) {
        EVP_PKEY_CTX_free(ctx);
        return nullptr;
    }
    
    if (EVP_PKEY_CTX_set_rsa_keygen_bits(ctx, key_length) <= 0) {
        EVP_PKEY_CTX_free(ctx);
        return nullptr;
    }
    
    // Gako pribatua sortu
    EVP_PKEY* pkey = nullptr;
    if (EVP_PKEY_keygen(ctx, &pkey) <= 0) {
        EVP_PKEY_CTX_free(ctx);
        return nullptr;
    }
    
    EVP_PKEY_CTX_free(ctx);
    
    // Gakoa PEM formatuan esportatzeko memoria-bufferra prestatu
    BIO* bio = BIO_new(BIO_s_mem());
    if (!bio) {
        EVP_PKEY_free(pkey);
        return nullptr;
    }
    
    // Gako pribatua PEM formatuan idatzi
    if (!PEM_write_bio_PrivateKey(bio, pkey, nullptr, nullptr, 0, nullptr, nullptr)) {
        BIO_free_all(bio);
        EVP_PKEY_free(pkey);
        return nullptr;
    }
    
    // Bufferreko datuak string-era eraman
    BUF_MEM* buffer_ptr;
    BIO_get_mem_ptr(bio, &buffer_ptr);
    
    std::string private_key(buffer_ptr->data, buffer_ptr->length);
    
    // Errekurtsoak askatu
    BIO_free_all(bio);
    EVP_PKEY_free(pkey);
    
    return private_key;
}