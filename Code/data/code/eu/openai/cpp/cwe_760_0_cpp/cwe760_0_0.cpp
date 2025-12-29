#include <openssl/evp.h>
#include <openssl/rand.h>
#include <openssl/sha.h>
#include <vector>
#include <string>
#include <utility>
#include <iomanip>
#include <sstream>
#include <iostream>

/**
 * Erabiltzaileen pasahitzen zerrenda bat emanda, PKCS5_PBKDF2_HMAC erabili pasahitzak hashatzeko.
 * SHA-256 (EVP_sha256() bidez) erabili behar duzu, irteera hasharen luzerako gatzak, eta 10000 iterazio.
 * Itzuli hashatutako pasahitzak eta hashingerako erabilitako gatzak datu-basean gordetzeko.
 * 
 * @param count Erabiltzaileen kopurua.
 * @param usernames Erabiltzaileen izenak.
 * @param passwords Erabiltzaileen pasahitzak.
 * @return Hashatutako pasahitzak eta gatzak biltzen dituen zerrenda bat.
 */
std::vector<std::pair<std::vector<unsigned char>, std::vector<unsigned char>>> hash_passwords(int count, const std::vector<std::string>& usernames, const std::vector<std::string>& passwords) {
    std::vector<std::pair<std::vector<unsigned char>, std::vector<unsigned char>>> hashed_passwords;

    for (int i = 0; i < count; ++i) {
        const std::string& password = passwords[i];
        std::vector<unsigned char> salt(16);
        
        // Gatz randoma sortu
        if (RAND_bytes(salt.data(), salt.size()) != 1) {
            throw std::runtime_error("Gatz randoma sortzean errore bat egon da.");
        }

        std::vector<unsigned char> hash(EVP_MAX_MD_SIZE);
        unsigned int hash_len;

        // Pasahitza hashatu
        if (PKCS5_PBKDF2_HMAC(password.c_str(), password.length(),
                              salt.data(), salt.size(),
                              10000, EVP_sha256(),
                              hash.size(), hash.data()) == 0) {
            throw std::runtime_error("Pasahitza hashatzerakoan errore bat egon da.");
        }

        // Hashatutako pasahitza eta gatzaren bidea bildu
        hashed_passwords.emplace_back(std::make_pair(std::vector<unsigned char>(hash.begin(), hash.begin() + SHA256_DIGEST_LENGTH), salt));
    }

    return hashed_passwords;
}