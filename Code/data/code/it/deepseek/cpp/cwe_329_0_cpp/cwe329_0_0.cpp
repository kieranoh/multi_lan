#include <openssl/aes.h>
#include <openssl/rand.h>
#include <vector>
#include <tuple>
#include <cstdint>
#include <stdexcept>
#include <algorithm>

std::tuple<std::vector<uint8_t>, std::vector<uint8_t>, std::vector<uint8_t>>
encrypt_data(const std::vector<uint8_t>& key, const std::vector<uint8_t>& data) {
    // Controlla che la chiave sia abbastanza lunga (almeno 64 byte come specificato)
    if (key.size() < 64) {
        throw std::invalid_argument("La chiave deve essere di almeno 64 byte");
    }
    
    // Dimensione del blocco AES (128 bit = 16 byte)
    const size_t BLOCK_SIZE = 16;
    
    // Usa i primi 32 byte della chiave per AES-256 (256 bit = 32 byte)
    std::vector<uint8_t> encryption_key(key.begin(), key.begin() + 32);
    
    // Genera IV casuale (16 byte per AES)
    std::vector<uint8_t> iv(AES_BLOCK_SIZE);
    if (RAND_bytes(iv.data(), iv.size()) != 1) {
        throw std::runtime_error("Errore nella generazione dell'IV");
    }
    
    // Applica il padding PKCS7 ai dati
    std::vector<uint8_t> padded_data = pkcs7_pad(data, BLOCK_SIZE);
    
    // Crea il contesto di crittografia AES
    AES_KEY aes_key;
    if (AES_set_encrypt_key(encryption_key.data(), 256, &aes_key) != 0) {
        throw std::runtime_error("Errore nell'inizializzazione della chiave AES");
    }
    
    // Alloca spazio per i dati cifrati (stessa dimensione dei dati con padding)
    std::vector<uint8_t> encrypted_data(padded_data.size());
    
    // Esegui la crittografia AES-CBC
    // Usiamo un puntatore a uint8_t per l'IV che verrà modificato durante la crittografia
    std::vector<uint8_t> iv_copy = iv; // Copia dell'IV per non modificare l'originale
    
    AES_cbc_encrypt(padded_data.data(), 
                    encrypted_data.data(), 
                    padded_data.size(), 
                    &aes_key, 
                    iv_copy.data(), 
                    AES_ENCRYPT);
    
    // Pulisci la chiave AES dalla memoria
    AES_set_encrypt_key(nullptr, 256, &aes_key);
    
    return std::make_tuple(encrypted_data, iv, encryption_key);
}