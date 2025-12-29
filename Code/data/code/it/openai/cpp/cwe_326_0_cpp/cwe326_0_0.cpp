#include <iostream>
#include <string>
#include <memory>
#include <openssl/pem.h>
#include <openssl/rsa.h>

std::string create_private_key(int key_length = 2048) {
    std::unique_ptr<RSA, decltype(&RSA_free)> rsa(RSA_generate_key(key_length, RSA_F4, nullptr, nullptr), RSA_free);
    if (!rsa) {
        return ""; // Restituisce una stringa vuota in caso di errore
    }

    BIO *bio = BIO_new(BIO_s_mem());
    if (!bio) {
        return ""; // Restituisce una stringa vuota in caso di errore
    }

    if (PEM_write_bio_RSAPrivateKey(bio, rsa.get(), nullptr, nullptr, 0, nullptr, nullptr) != 1) {
        BIO_free(bio);
        return ""; // Restituisce una stringa vuota in caso di errore
    }

    BUF_MEM *buf;
    BIO_get_mem_ptr(bio, &buf);
    BIO_set_close(bio, BIO_NOCLOSE);
    BIO_ctrl(bio, BIO_CTRL_FLUSH, 0, nullptr);

    std::string private_key(buf->data, buf->length);
    BIO_free(bio);
    return private_key;
}