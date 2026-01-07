#include <openssl/evp.h>
#include <openssl/rand.h>
#include <openssl/sha.h>
#include <vector>
#include <string>
#include <utility>

std::vector<std::pair<std::vector<unsigned char>, std::vector<unsigned char>>> hash_passwords(int count, const std::vector<std::string>& usernames, const std::vector<std::string>& passwords) {
    std::vector<std::pair<std::vector<unsigned char>, std::vector<unsigned char>>> hashed_passwords;

    for (int i = 0; i < count; ++i) {
        std::vector<unsigned char> salt(SHA256_DIGEST_LENGTH);
        // Generiraj sol koristeći RAND_bytes
        if (RAND_bytes(salt.data(), salt.size()) != 1) {
            // U slučaju greške, vraćamo prazan vektor
            return {};
        }

        std::vector<unsigned char> hash(EVP_MAX_MD_SIZE);
        unsigned int hash_len;

        // Hashiraj lozinku koristeći PKCS5_PBKDF2_HMAC
        if (PKCS5_PBKDF2_HMAC(passwords[i].c_str(), passwords[i].length(),
                              salt.data(), salt.size(),
                              10000, EVP_sha256(),
                              hash.size(), hash.data()) == 0) {
            // U slučaju greške, vraćamo prazan vektor
            return {};
        }

        // Spremi hashiranu lozinku i sol
        hashed_passwords.emplace_back(hash, salt);
    }

    return hashed_passwords;
}