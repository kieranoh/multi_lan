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
        std::vector<unsigned char> salt(SHA256_DIGEST_LENGTH);
        std::vector<unsigned char> hashed_password(EVP_MAX_MD_SIZE);
        unsigned int hashed_length = 0;

        // Generiere ein zufälliges Salz
        if (RAND_bytes(salt.data(), salt.size()) != 1) {
            throw std::runtime_error("Fehler beim Generieren des Salzes");
        }

        // Hash das Passwort mit PBKDF2
        PKCS5_PBKDF2_HMAC(password.c_str(), password.length(), salt.data(), salt.size(), 10000, EVP_sha256(), hashed_password.size(), hashed_password.data());

        // Speichere das gepaarte Ergebnis
        hashed_passwords.emplace_back(std::make_pair(std::move(hashed_password), std::move(salt)));
    }

    return hashed_passwords;
}