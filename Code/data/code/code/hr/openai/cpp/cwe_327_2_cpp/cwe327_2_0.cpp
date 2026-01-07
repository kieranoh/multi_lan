#include <openssl/aes.h>
#include <openssl/des.h>
#include <openssl/rand.h>
#include <vector>

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
    encryption_result result;
    
    // Inicijaliziraj IV
    result.iv.resize(AES_BLOCK_SIZE);
    if (!RAND_bytes(result.iv.data(), AES_BLOCK_SIZE)) {
        throw std::runtime_error("Failed to generate IV");
    }

    // Uzimamo prvi 16 bajtova ključa za AES
    std::vector<unsigned char> aes_key(key.begin(), key.begin() + AES_BLOCK_SIZE);

    // Padding data
    std::vector<unsigned char> padded_data = pad_data(data);

    // Enkripcija
    AES_KEY encrypt_key;
    AES_set_encrypt_key(aes_key.data(), 128, &encrypt_key); // Koristimo 128-bitni ključ

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

    result.key = aes_key; // Spremi korišteni ključ

    return result;
}