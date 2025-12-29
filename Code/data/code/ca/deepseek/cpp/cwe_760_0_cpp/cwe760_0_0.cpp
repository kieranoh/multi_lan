#include <openssl/evp.h>
#include <openssl/rand.h>
#include <vector>
#include <string>
#include <utility>
#include <stdexcept>
#include <cstdint>

std::vector<std::pair<std::vector<unsigned char>, std::vector<unsigned char>>> hash_passwords(int count, const std::vector<std::string>& usernames, const std::vector<std::string>& passwords) {
    // Validar les entrades
    if (count <= 0) {
        return {};
    }
    if (static_cast<size_t>(count) > usernames.size() || static_cast<size_t>(count) > passwords.size()) {
        throw std::invalid_argument("El nombre de contrasenyes supera la mida dels vectors d'entrada.");
    }

    // Inicialitzar el vector de resultats
    std::vector<std::pair<std::vector<unsigned char>, std::vector<unsigned char>>> result;
    result.reserve(count);

    // Constants per al hashing
    const int iterations = 10000;
    const int hash_length = EVP_MD_size(EVP_sha256()); // 32 bytes per SHA-256
    const int salt_length = hash_length; // Salt de la mateixa longitud que el hash

    for (int i = 0; i < count; ++i) {
        // Generar un salt aleatori
        std::vector<unsigned char> salt(salt_length);
        if (RAND_bytes(salt.data(), salt_length) != 1) {
            throw std::runtime_error("Error en la generació del salt aleatori.");
        }

        // Preparar el buffer per al hash resultant
        std::vector<unsigned char> hashed_password(hash_length);

        // Realitzar el hash PBKDF2 amb SHA-256
        if (PKCS5_PBKDF2_HMAC(
                passwords[i].c_str(),          // Contrasenya
                static_cast<int>(passwords[i].length()), // Longitud de la contrasenya
                salt.data(),                   // Salt
                salt_length,                   // Longitud del salt
                iterations,                    // Nombre d'iteracions
                EVP_sha256(),                  // Funció de hash
                hash_length,                   // Longitud del hash desitjat
                hashed_password.data()         // Buffer de sortida
            ) != 1) {
            throw std::runtime_error("Error en el càlcul del hash PBKDF2.");
        }

        // Emmagatzemar el parell (hash, salt) al resultat
        result.emplace_back(std::move(hashed_password), std::move(salt));
    }

    return result;
}