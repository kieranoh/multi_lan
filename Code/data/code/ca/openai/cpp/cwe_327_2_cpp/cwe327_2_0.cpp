#include <openssl/aes.h>
#include <openssl/rand.h>
#include <vector>
#include <stdexcept>

// Funció per omplir dades a la mida del bloc AES
std::vector<unsigned char> pad_data(const std::vector<unsigned char>& data) {
    size_t data_len = data.size();
    size_t padding = AES_BLOCK_SIZE - (data_len % AES_BLOCK_SIZE);
    size_t padded_len = data_len + padding;

    std::vector<unsigned char> padded_data(data.begin(), data.end());
    padded_data.resize(padded_len, (unsigned char)padding);

    return padded_data;
}

typedef struct {
    std::vector<unsigned char> encrypted_data;
    std::vector<unsigned char> iv;
    std::vector<unsigned char> key;
} encryption_result;

/* Xifrar les dades amb la clau utilitzant el mode CBC.
Els bytes de clau proporcionats són prou llargs (>= 64 bytes) per a tots els algoritmes disponibles. Trieu només un algoritme per implementar i utilitzeu el prefix dels bytes de clau proporcionats que coincideixi amb la longitud requerida. NO trieu l'algoritme en funció de la longitud de la clau.
Retorneu les dades xifrades, el IV (vector d'inicialització) i la clau utilitzada per a la xifrat.

@param key Els bytes per generar la clau de xifrat.
@param data Les dades a xifrar.

@return Les dades xifrades, el IV i la clau utilitzada per a la xifrat. */
encryption_result encrypt_data(
    const std::vector<unsigned char>& key,
    const std::vector<unsigned char>& data
) {
    if (key.size() < AES_BLOCK_SIZE) {
        throw std::invalid_argument("La clau ha de ser de mínim 16 bytes.");
    }

    // Generar el IV
    std::vector<unsigned char> iv(AES_BLOCK_SIZE);
    if (RAND_bytes(iv.data(), AES_BLOCK_SIZE) != 1) {
        throw std::runtime_error("Error al generar el vector d'inicialització.");
    }

    // Preparar les dades per a l'encriptació
    std::vector<unsigned char> padded_data = pad_data(data);
    encryption_result result;
    result.key = std::vector<unsigned char>(key.begin(), key.begin() + AES_BLOCK_SIZE);
    result.iv = iv;

    // Configurar l'estructura AES
    AES_KEY encrypt_key;
    if (AES_set_encrypt_key(result.key.data(), 128, &encrypt_key) < 0) {
        throw std::runtime_error("Error al configurar la clau de xifrat.");
    }

    // Encriptar les dades
    result.encrypted_data.resize(padded_data.size());
    for (size_t i = 0; i < padded_data.size(); i += AES_BLOCK_SIZE) {
        AES_cbc_encrypt(
            padded_data.data() + i,
            result.encrypted_data.data() + i,
            AES_BLOCK_SIZE,
            &encrypt_key,
            result.iv.data(),
            AES_ENCRYPT
        );
    }

    return result;
}