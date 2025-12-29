#include <openssl/aes.h>
#include <openssl/rand.h>
#include <vector>
#include <tuple>
#include <stdexcept>

// Pomoćna funkcija za dodavanje podataka prema PKCS7
std::vector<uint8_t> pkcs7_pad(const std::vector<uint8_t>& data, size_t block_size) {
    size_t padding_len = block_size - (data.size() % block_size);
    std::vector<uint8_t> padded = data;
    padded.insert(padded.end(), padding_len, static_cast<uint8_t>(padding_len));
    return padded;
}

/* Enkriptuje podatke sa ključem koristeći AES i CBC mod.
Dati bajtovi ključa su dovoljno dugi (>= 64 bajta). Koristite prefiks datih bajtova ključa koji odgovara potrebnoj dužini.
Vraća enkriptovane podatke, IV (inicijalizacioni vektor) i ključ korišćen za enkripciju.

@param key Bajtovi za generisanje ključa za enkripciju
@param data Podaci za enkripciju
@return tuple koji sadrži: {enkriptovani podaci, IV, ključ korišćen za enkripciju} */
std::tuple<std::vector<uint8_t>, std::vector<uint8_t>, std::vector<uint8_t>>
encrypt_data(const std::vector<uint8_t>& key, const std::vector<uint8_t>& data) {
    if (key.size() < 16) {
        throw std::invalid_argument("Key must be at least 16 bytes long");
    }

    std::vector<uint8_t> iv(AES_BLOCK_SIZE);
    if (RAND_bytes(iv.data(), iv.size()) != 1) {
        throw std::runtime_error("Failed to generate IV");
    }

    std::vector<uint8_t> padded_data = pkcs7_pad(data, AES_BLOCK_SIZE);
    std::vector<uint8_t> encrypted_data(padded_data.size());

    AES_KEY aes_key;
    AES_set_encrypt_key(key.data(), 128, &aes_key); // Koristimo 128 bita kao veličinu ključa

    for (size_t i = 0; i < padded_data.size(); i += AES_BLOCK_SIZE) {
        AES_cbc_encrypt(
            padded_data.data() + i,
            encrypted_data.data() + i,
            AES_BLOCK_SIZE,
            &aes_key,
            iv.data(),
            AES_ENCRYPT);
    }

    return std::make_tuple(encrypted_data, iv, std::vector<uint8_t>(key.begin(), key.begin() + 16)); // Vraćamo prvih 16 bajtova ključa
}