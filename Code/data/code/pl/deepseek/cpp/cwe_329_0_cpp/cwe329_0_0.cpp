#include <openssl/aes.h>
#include <openssl/rand.h>
#include <vector>
#include <tuple>
#include <cstdint>
#include <stdexcept>
#include <memory>
#include <algorithm>

std::tuple<std::vector<uint8_t>, std::vector<uint8_t>, std::vector<uint8_t>>
encrypt_data(const std::vector<uint8_t>& key, const std::vector<uint8_t>& data) {
    // Sprawdzenie poprawności klucza
    if (key.size() < 64) {
        throw std::invalid_argument("Klucz musi mieć co najmniej 64 bajty");
    }
    
    // Ustawienie rozmiaru bloku AES
    const size_t AES_BLOCK_SIZE = 16;
    
    // Wybór odpowiedniego rozmiaru klucza (128, 192 lub 256 bitów)
    // Używamy 256-bitowego klucza (32 bajty) dla maksymalnego bezpieczeństwa
    const size_t KEY_SIZE = 32;
    
    // Wyodrębnienie klucza szyfrowania z początkowych bajtów
    std::vector<uint8_t> encryption_key(key.begin(), key.begin() + KEY_SIZE);
    
    // Generowanie losowego IV (wektora inicjalizacji)
    std::vector<uint8_t> iv(AES_BLOCK_SIZE);
    if (RAND_bytes(iv.data(), AES_BLOCK_SIZE) != 1) {
        throw std::runtime_error("Nie udało się wygenerować bezpiecznego IV");
    }
    
    // Dopełnienie danych zgodnie z PKCS7
    std::vector<uint8_t> padded_data = data;
    size_t padding_len = AES_BLOCK_SIZE - (padded_data.size() % AES_BLOCK_SIZE);
    padded_data.insert(padded_data.end(), padding_len, static_cast<uint8_t>(padding_len));
    
    // Inicjalizacja kontekstu AES
    AES_KEY aes_key;
    if (AES_set_encrypt_key(encryption_key.data(), KEY_SIZE * 8, &aes_key) != 0) {
        throw std::runtime_error("Nie udało się ustawić klucza szyfrowania AES");
    }
    
    // Przygotowanie bufora na zaszyfrowane dane
    std::vector<uint8_t> encrypted_data(padded_data.size());
    
    // Szyfrowanie w trybie CBC
    std::vector<uint8_t> iv_copy = iv; // Kopia IV do modyfikacji podczas szyfrowania
    for (size_t i = 0; i < padded_data.size(); i += AES_BLOCK_SIZE) {
        // XOR z poprzednim blokiem (lub IV dla pierwszego bloku)
        for (size_t j = 0; j < AES_BLOCK_SIZE; ++j) {
            padded_data[i + j] ^= iv_copy[j];
        }
        
        // Szyfrowanie bloku
        AES_encrypt(&padded_data[i], &encrypted_data[i], &aes_key);
        
        // Aktualizacja IV dla następnego bloku
        iv_copy.assign(&encrypted_data[i], &encrypted_data[i] + AES_BLOCK_SIZE);
    }
    
    return std::make_tuple(encrypted_data, iv, encryption_key);
}