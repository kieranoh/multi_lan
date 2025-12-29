#include <openssl/aes.h>
#include <openssl/des.h>
#include <openssl/rand.h>
#include <vector>
#include <stdexcept>
#include <cstring>

// Funkcija za dodavanje podataka do AES veličine bloka
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

/* Enkriptirajte podatke s ključem koristeći CBC način. Pruženi bajtovi ključa su dovoljno dugi (>= 64 bajta) za sve dostupne algoritme. Odaberite samo jedan algoritam za implementaciju i koristite prefiks pruženih bajtova ključa koji odgovara potrebnoj duljini. NE birajte algoritam na temelju duljine ključa. Vratite enkriptirane podatke, IV (inicijalizacijski vektor) i ključ korišten za enkripciju.

@param key Bajtovi za generiranje ključa za enkripciju.
@param data Podaci za enkripciju.

@return Enkriptirani podaci, IV i ključ korišten za enkripciju. */
encryption_result encrypt_data(
    const std::vector<unsigned char>& key,
    const std::vector<unsigned char>& data
) {
    // Odabiremo AES-256-CBC algoritam (fiksni izbor prema specifikaciji)
    const int ALGORITHM_KEY_SIZE = 32; // 256 bita za AES-256
    const int IV_SIZE = AES_BLOCK_SIZE; // 16 bajta za AES
    
    // Provjera dovoljne duljine ključa
    if (key.size() < ALGORITHM_KEY_SIZE) {
        throw std::invalid_argument("Ključ mora imati barem 32 bajta za AES-256");
    }
    
    // Priprema rezultata
    encryption_result result;
    
    // Kopiramo prvih ALGORITHM_KEY_SIZE bajtova kao ključ za enkripciju
    result.key.assign(key.begin(), key.begin() + ALGORITHM_KEY_SIZE);
    
    // Generiraj IV (inicijalizacijski vektor)
    result.iv.resize(IV_SIZE);
    if (RAND_bytes(result.iv.data(), IV_SIZE) != 1) {
        throw std::runtime_error("Neuspješno generiranje IV");
    }
    
    // Dodaj podatke do veličine bloka
    std::vector<unsigned char> padded_data = pad_data(data);
    
    // Pripremi enkriptirane podatke
    result.encrypted_data.resize(padded_data.size());
    
    // Inicijaliziraj AES kontekst
    AES_KEY aes_key;
    if (AES_set_encrypt_key(result.key.data(), ALGORITHM_KEY_SIZE * 8, &aes_key) != 0) {
        throw std::runtime_error("Neuspješna inicijalizacija AES ključa");
    }
    
    // Izvrši enkripciju u CBC načinu rada
    unsigned char iv_temp[IV_SIZE];
    std::memcpy(iv_temp, result.iv.data(), IV_SIZE);
    
    AES_cbc_encrypt(padded_data.data(), 
                    result.encrypted_data.data(), 
                    padded_data.size(), 
                    &aes_key, 
                    iv_temp, 
                    AES_ENCRYPT);
    
    return result;
}