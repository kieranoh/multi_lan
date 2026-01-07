#include <iostream>
#include <string>
#include <memory>
#include <openssl/pem.h>
#include <openssl/rsa.h>
#include <openssl/err.h>

std::string create_private_key() {
    // Alusta OpenSSL
    OpenSSL_add_all_algorithms();
    ERR_load_crypto_strings();
    
    // Luo RSA-avainpari (2048 bittiä)
    const int key_length = 2048;
    BIGNUM* bn = BN_new();
    if (bn == nullptr) {
        return nullptr;
    }
    
    // Aseta RSA-avaimen julkisen eksponentin arvoksi F4 (65537)
    if (BN_set_word(bn, RSA_F4) != 1) {
        BN_free(bn);
        return nullptr;
    }
    
    // Luo RSA-avain
    RSA* rsa = RSA_new();
    if (rsa == nullptr) {
        BN_free(bn);
        return nullptr;
    }
    
    // Generoi RSA-avainpari
    if (RSA_generate_key_ex(rsa, key_length, bn, nullptr) != 1) {
        RSA_free(rsa);
        BN_free(bn);
        return nullptr;
    }
    
    BN_free(bn);
    
    // Luo BIO-muistivuo PEM-muotoilua varten
    BIO* bio = BIO_new(BIO_s_mem());
    if (bio == nullptr) {
        RSA_free(rsa);
        return nullptr;
    }
    
    // Vie yksityinen avain PEM-muotoon
    if (PEM_write_bio_RSAPrivateKey(bio, rsa, nullptr, nullptr, 0, nullptr, nullptr) != 1) {
        BIO_free_all(bio);
        RSA_free(rsa);
        return nullptr;
    }
    
    // Hae PEM-data BIO:sta
    char* pem_data = nullptr;
    long pem_size = BIO_get_mem_data(bio, &pem_data);
    
    if (pem_size <= 0) {
        BIO_free_all(bio);
        RSA_free(rsa);
        return nullptr;
    }
    
    // Kopioi PEM-data std::string:iin
    std::string private_key(pem_data, pem_size);
    
    // Vapauta resurssit
    BIO_free_all(bio);
    RSA_free(rsa);
    
    // Puhdista OpenSSL
    EVP_cleanup();
    ERR_free_strings();
    
    return private_key;
}