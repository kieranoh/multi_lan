#include <openssl/aes.h>
#include <openssl/rand.h>
#include <openssl/evp.h>
#include <vector>
#include <tuple>
#include <stdexcept>
#include <cstring>
#include <memory>

std::tuple<std::vector<uint8_t>, std::vector<uint8_t>, std::vector<uint8_t>>
encrypt_data(const std::vector<uint8_t>& key, const std::vector<uint8_t>& data) {
    // Ellenőrizzük, hogy a kulcs elég hosszú-e (legalább 64 bájt)
    if (key.size() < 64) {
        throw std::invalid_argument("Key must be at least 64 bytes long");
    }

    // AES-256 CBC használata (256 bites kulcs = 32 bájt)
    const size_t KEY_SIZE = 32;
    const size_t BLOCK_SIZE = AES_BLOCK_SIZE;
    
    // IV generálása (16 bájt AES blokkmérethez)
    std::vector<uint8_t> iv(BLOCK_SIZE);
    if (RAND_bytes(iv.data(), BLOCK_SIZE) != 1) {
        throw std::runtime_error("Failed to generate IV");
    }

    // Kulcs kivonása a megadott kulcsból (az első 32 bájtot használjuk)
    std::vector<uint8_t> encryption_key(key.begin(), key.begin() + KEY_SIZE);

    // Adatok kitöltése PKCS7 szerint
    std::vector<uint8_t> padded_data = data;
    size_t padding_len = BLOCK_SIZE - (data.size() % BLOCK_SIZE);
    padded_data.insert(padded_data.end(), padding_len, static_cast<uint8_t>(padding_len));

    // Titkosított adatok tárolója
    std::vector<uint8_t> ciphertext(padded_data.size() + BLOCK_SIZE);

    // OpenSSL EVP kontextus inicializálása
    std::unique_ptr<EVP_CIPHER_CTX, decltype(&EVP_CIPHER_CTX_free)> ctx(
        EVP_CIPHER_CTX_new(), EVP_CIPHER_CTX_free);
    
    if (!ctx) {
        throw std::runtime_error("Failed to create EVP cipher context");
    }

    // Titkosítás inicializálása AES-256 CBC módban
    if (EVP_EncryptInit_ex(ctx.get(), EVP_aes_256_cbc(), nullptr, 
                          encryption_key.data(), iv.data()) != 1) {
        throw std::runtime_error("Failed to initialize encryption");
    }

    // Titkosítás végrehajtása
    int len = 0;
    if (EVP_EncryptUpdate(ctx.get(), ciphertext.data(), &len, 
                         padded_data.data(), static_cast<int>(padded_data.size())) != 1) {
        throw std::runtime_error("Encryption update failed");
    }
    int ciphertext_len = len;

    // Titkosítás befejezése
    if (EVP_EncryptFinal_ex(ctx.get(), ciphertext.data() + len, &len) != 1) {
        throw std::runtime_error("Encryption finalization failed");
    }
    ciphertext_len += len;

    // Ciphertext méretének beállítása
    ciphertext.resize(ciphertext_len);

    return std::make_tuple(ciphertext, iv, encryption_key);
}