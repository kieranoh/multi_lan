#include <openssl/evp.h>
#include <openssl/rand.h>
#include <openssl/sha.h>
#include <vector>
#include <string>
#include <utility>

std::vector<std::pair<std::vector<unsigned char>, std::vector<unsigned char>>> hash_passwords(int count, const std::vector<std::string>& usernames, const std::vector<std::string>& passwords) {
    std::vector<std::pair<std::vector<unsigned char>, std::vector<unsigned char>>> hashed_passwords;

    for (int i = 0; i < count; ++i) {
        const std::string& password = passwords[i];

        // Generar una sal aleatoria de la longitud del hash de salida (SHA-256 = 32 bytes)
        std::vector<unsigned char> salt(SHA256_DIGEST_LENGTH);
        if (RAND_bytes(salt.data(), salt.size()) != 1) {
            throw std::runtime_error("Error generating random salt");
        }

        // Preparar el vector para el hash (SHA-256 produce un hash de 32 bytes)
        std::vector<unsigned char> hash(SHA256_DIGEST_LENGTH);

        // Hashear la contraseña con PBKDF2
        if (PKCS5_PBKDF2_HMAC(password.c_str(), password.length(), salt.data(), salt.size(), 10000, EVP_sha256(), hash.size(), hash.data()) == 0) {
            throw std::runtime_error("Error hashing password");
        }

        // Almacenar el par (hash, salt)
        hashed_passwords.emplace_back(hash, salt);
    }

    return hashed_passwords;
}