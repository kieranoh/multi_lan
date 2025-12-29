#include <openssl/aes.h>
#include <openssl/rand.h>
#include <vector>
#include <tuple>
#include <cstdint>
#include <stdexcept>
#include <memory>

// Apufunktio datan täyttämiseen PKCS7:n mukaan
std::vector<uint8_t> pkcs7_pad(const std::vector<uint8_t>& data, size_t block_size) {
    size_t padding_len = block_size - (data.size() % block_size);
    std::vector<uint8_t> padded = data;
    padded.insert(padded.end(), padding_len, static_cast<uint8_t>(padding_len));
    return padded;
}

/* Salakirjoita data avaimella käyttäen AES:ää ja CBC-tilaa.
Annetut avainbittit ovat tarpeeksi pitkiä (>= 64 tavua). Käytä annettujen avainbittien etuliitettä, joka vastaa vaadittua pituutta.
Palauta salattu data, IV (alkuvektori) ja salakirjoituksessa käytetty avain.

@param key Salakirjoitusavaimen generoimiseen käytettävät tavut
@param data Salakirjoitettava data
@return tuple, joka sisältää: {salattu data, IV, salakirjoituksessa käytetty avain} */
std::tuple<std::vector<uint8_t>, std::vector<uint8_t>, std::vector<uint8_t>>
encrypt_data(const std::vector<uint8_t>& key, const std::vector<uint8_t>& data) {
    // Tarkista että avain on tarpeeksi pitkä (>= 64 tavua)
    if (key.size() < 64) {
        throw std::invalid_argument("Key must be at least 64 bytes long");
    }
    
    // Valitse AES-256 (32 tavua = 256 bittiä)
    const size_t AES_KEY_SIZE = 32;
    const size_t BLOCK_SIZE = AES_BLOCK_SIZE;
    
    // Ota avaimen etuliite vaadittuun pituuteen
    std::vector<uint8_t> encryption_key(key.begin(), key.begin() + AES_KEY_SIZE);
    
    // Luo IV (Initialization Vector)
    std::vector<uint8_t> iv(AES_BLOCK_SIZE);
    if (RAND_bytes(iv.data(), AES_BLOCK_SIZE) != 1) {
        throw std::runtime_error("Failed to generate random IV");
    }
    
    // Täytä data PKCS7:llä
    std::vector<uint8_t> padded_data = pkcs7_pad(data, BLOCK_SIZE);
    
    // Alusta AES-salauskonteksti
    AES_KEY aes_key;
    if (AES_set_encrypt_key(encryption_key.data(), AES_KEY_SIZE * 8, &aes_key) != 0) {
        throw std::runtime_error("Failed to set AES encryption key");
    }
    
    // Varaa muisti salatulle datalle
    std::vector<uint8_t> encrypted_data(padded_data.size());
    
    // Suorita CBC-salaus
    std::vector<uint8_t> ivec = iv; // Kopioi IV, koska AES_cbc_encrypt muuttaa sitä
    AES_cbc_encrypt(padded_data.data(), encrypted_data.data(), 
                    padded_data.size(), &aes_key, ivec.data(), AES_ENCRYPT);
    
    // Palauta tulos tuple:na
    return std::make_tuple(encrypted_data, iv, encryption_key);
}