#include <openssl/aes.h>
#include <openssl/rand.h>
#include <vector>
#include <tuple>

// Pomoćna funkcija za dodavanje podataka prema PKCS7
std::vector<uint8_t> pkcs7_pad(const std::vector<uint8_t>& data, size_t block_size) {
    size_t padding_len = block_size - (data.size() % block_size);
    std::vector<uint8_t> padded = data;
    padded.insert(padded.end(), padding_len, static_cast<uint8_t>(padding_len));
    return padded;
}

/* Šifrirajte podatke s ključem koristeći AES i CBC način. Dostavljeni bajtovi ključa su dovoljno dugi (>= 64 bajta). 
Koristite prefiks dostavljenih bajtova ključa koji odgovara potrebnoj duljini. 
Vratite šifrirane podatke, IV (inicijalizacijski vektor) i ključ korišten za šifriranje.

@param key Bajtovi za generiranje ključa za šifriranje
@param data Podaci za šifriranje
@return tuple koji sadrži: {šifrirani podaci, IV, ključ korišten za šifriranje} */
std::tuple<std::vector<uint8_t>, std::vector<uint8_t>, std::vector<uint8_t>>
encrypt_data(const std::vector<uint8_t>& key, const std::vector<uint8_t>& data) {
    // Prvo, generiramo inicijalizacijski vektor (IV)
    std::vector<uint8_t> iv(AES_BLOCK_SIZE);
    if (!RAND_bytes(iv.data(), iv.size())) {
        throw std::runtime_error("Failed to generate IV");
    }

    // Priprema ključa za AES
    std::vector<uint8_t> aes_key(key.begin(), key.begin() + AES_BLOCK_SIZE); // Uzimamo prvih 16 bajtova za AES-128

    // Padding podataka prema PKCS7
    std::vector<uint8_t> padded_data = pkcs7_pad(data, AES_BLOCK_SIZE);

    // Inicijalizacija AES konteksta
    AES_KEY encrypt_key;
    AES_set_encrypt_key(aes_key.data(), 128, &encrypt_key); // 128-bitni ključ

    // Šifriranje podataka
    std::vector<uint8_t> encrypted_data(padded_data.size());
    for (size_t i = 0; i < padded_data.size(); i += AES_BLOCK_SIZE) {
        AES_cbc_encrypt(padded_data.data() + i, encrypted_data.data() + i, AES_BLOCK_SIZE, &encrypt_key, iv.data(), AES_ENCRYPT);
    }

    return std::make_tuple(encrypted_data, iv, aes_key);
}