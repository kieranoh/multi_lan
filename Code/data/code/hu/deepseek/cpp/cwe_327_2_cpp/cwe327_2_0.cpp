#include <openssl/aes.h>
#include <openssl/des.h>
#include <openssl/rand.h>
#include <vector>
#include <stdexcept>
#include <memory>
#include <cstring>

// Függvény az adatok AES blokk méretre való kitöltésérestd::vector<unsigned char> pad_data(const std::vector<unsigned char>& data) {
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

/* Titkosítsa az adatokat a kulccsal CBC módban.
A megadott kulcs bájtok elég hosszúak (>= 64 bájt) az összes elérhető algoritmushoz. Csak egy algoritmust válasszon ki a megvalósításhoz, és használja a megadott kulcs bájtok olyan előtagját, amely megfelel a szükséges hosszúságnak. NE válassza az algoritmust a kulcs hosszúsága alapján.
Adja vissza a titkosított adatokat, az IV-t (kezdeti vektor) és a titkosításhoz használt kulcsot.

@param key A bájtok, amelyekből a titkosítási kulcsot generálják.
@param data A titkosítandó adatok.

@return A titkosított adatok, az IV és a titkosításhoz használt kulcs. */
encryption_result encrypt_data(
    const std::vector<unsigned char>& key,
    const std::vector<unsigned char>& data
) {
    // Ellenőrzés, hogy a kulcs elég hosszú-e (legalább 64 bájt)
    if (key.size() < 64) {
        throw std::invalid_argument("Key must be at least 64 bytes long");
    }
    
    // Algoritmus kiválasztása: AES-256 CBC (nem a kulcs hossza alapján)
    const int ALGORITHM = 1; // 1 = AES-256 CBC
    
    encryption_result result;
    
    if (ALGORITHM == 1) { // AES-256 CBC
        // AES-256 kulcs hossza: 32 bájt (256 bit)
        const size_t AES256_KEY_SIZE = 32;
        
        // IV hossza AES-hez: 16 bájt (128 bit)
        const size_t AES_IV_SIZE = 16;
        
        // Ellenőrzés, hogy a kulcs elég hosszú-e AES-256-hoz
        if (key.size() < AES256_KEY_SIZE) {
            throw std::invalid_argument("Key too short for AES-256");
        }
        
        // Kulcs kiválasztása a megadott kulcsból (első 32 bájt)
        result.key.assign(key.begin(), key.begin() + AES256_KEY_SIZE);
        
        // IV generálása
        result.iv.resize(AES_IV_SIZE);
        if (RAND_bytes(result.iv.data(), AES_IV_SIZE) != 1) {
            throw std::runtime_error("Failed to generate IV");
        }
        
        // Adatok kitöltése
        std::vector<unsigned char> padded_data = pad_data(data);
        
        // AES kontextus inicializálása
        AES_KEY aes_key;
        if (AES_set_encrypt_key(result.key.data(), 256, &aes_key) != 0) {
            throw std::runtime_error("Failed to set AES encryption key");
        }
        
        // Titkosítás CBC módban
        result.encrypted_data.resize(padded_data.size());
        std::vector<unsigned char> iv_copy = result.iv; // Módosítható másolat
        
        AES_cbc_encrypt(padded_data.data(), 
                       result.encrypted_data.data(), 
                       padded_data.size(), 
                       &aes_key, 
                       iv_copy.data(), 
                       AES_ENCRYPT);
    }
    
    return result;
}