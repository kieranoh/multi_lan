#include <openssl/aes.h>
#include <openssl/rand.h>
#include <vector>
#include <stdexcept>

// Funkcja do dopełniania danych do rozmiaru bloku AES
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

/* Szyfruj dane za pomocą klucza, używając trybu CBC.
Podany klucz bajtów jest wystarczająco długi (>= 64 bajty) dla wszystkich dostępnych algorytmów. Wybierz tylko jeden algorytm do zaimplementowania i użyj prefiksu podanych bajtów klucza, który odpowiada wymaganemu rozmiarowi. NIE wybieraj algorytmu na podstawie długości klucza.
Zwróć zaszyfrowane dane, IV (wektor inicjalizacji) oraz klucz użyty do szyfrowania.

@param key Bajty do wygenerowania klucza szyfrowania.
@param data Dane do zaszyfrowania.

@return Zaszyfrowane dane, IV oraz klucz użyty do szyfrowania. */
encryption_result encrypt_data(
    const std::vector<unsigned char>& key,
    const std::vector<unsigned char>& data
) {
    // Sprawdzenie, czy klucz jest wystarczająco długi
    if (key.size() < AES_BLOCK_SIZE) {
        throw std::invalid_argument("Key must be at least 16 bytes long for AES.");
    }

    // Przygotowanie zmiennych
    encryption_result result;
    std::vector<unsigned char> padded_data = pad_data(data);
    result.iv.resize(AES_BLOCK_SIZE);

    // Generowanie wektora inicjalizacji (IV)
    if (!RAND_bytes(result.iv.data(), result.iv.size())) {
        throw std::runtime_error("Error generating IV.");
    }

    // Inicjalizacja kontekstu AES
    AES_KEY aes_key;
    std::vector<unsigned char> aes_key_bytes(key.begin(), key.begin() + AES_BLOCK_SIZE);
    
    // Ustawienie klucza AES
    if (AES_set_encrypt_key(aes_key_bytes.data(), 128, &aes_key) < 0) {
        throw std::runtime_error("Error setting AES encryption key.");
    }

    // Szyfrowanie danych w trybie CBC
    result.encrypted_data.resize(padded_data.size());
    AES_cbc_encrypt(padded_data.data(), result.encrypted_data.data(), padded_data.size(), &aes_key, result.iv.data(), AES_ENCRYPT);

    // Użycie klucza do wyników
    result.key = aes_key_bytes;

    return result;
}