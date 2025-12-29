#include <openssl/aes.h>
#include <openssl/rand.h>
#include <vector>
#include <tuple>
#include <stdexcept>

// Funció d'ajuda per omplir dades segons PKCS7
std::vector<uint8_t> pkcs7_pad(const std::vector<uint8_t>& data, size_t block_size) {
    size_t padding_len = block_size - (data.size() % block_size);
    std::vector<uint8_t> padded = data;
    padded.insert(padded.end(), padding_len, static_cast<uint8_t>(padding_len));
    return padded;
}

/* Xifrar les dades amb la clau utilitzant AES i mode CBC.
Els bytes de clau proporcionats són prou llargs (>= 64 bytes). Utilitzeu el prefix dels bytes de clau proporcionats que coincideix amb la longitud requerida.
Retorna les dades xifrades, l'IV (vector d'inicialització) i la clau utilitzada per a la xifrat. */
std::tuple<std::vector<uint8_t>, std::vector<uint8_t>, std::vector<uint8_t>>
encrypt_data(const std::vector<uint8_t>& key, const std::vector<uint8_t>& data) {
    if (key.size() < 32) {
        throw std::invalid_argument("La clau ha de tenir almenys 32 bytes per AES-256.");
    }
    
    // Utilitzem només els primers 32 bytes de la clau
    std::vector<uint8_t> aes_key(key.begin(), key.begin() + 32);
    
    // Generar un IV aleatori
    std::vector<uint8_t> iv(AES_BLOCK_SIZE);
    if (RAND_bytes(iv.data(), AES_BLOCK_SIZE) != 1) {
        throw std::runtime_error("Error generant IV aleatori.");
    }

    // Omplir les dades amb PKCS7
    std::vector<uint8_t> padded_data = pkcs7_pad(data, AES_BLOCK_SIZE);
    std::vector<uint8_t> encrypted_data(padded_data.size());

    AES_KEY enc_key;
    AES_set_encrypt_key(aes_key.data(), 256, &enc_key);

    // Xifrat de les dades en blocs
    for (size_t i = 0; i < padded_data.size(); i += AES_BLOCK_SIZE) {
        AES_cbc_encrypt(padded_data.data() + i, encrypted_data.data() + i, 
                        AES_BLOCK_SIZE, &enc_key, iv.data(), AES_ENCRYPT);
    }

    return std::make_tuple(encrypted_data, iv, aes_key);
}