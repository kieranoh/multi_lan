#include <openssl/aes.h>
#include <openssl/rand.h>
#include <vector>
#include <tuple>
#include <stdexcept>

// Funkcja pomocnicza do dopełniania danych zgodnie z PKCS7
std::vector<uint8_t> pkcs7_pad(const std::vector<uint8_t>& data, size_t block_size) {
    size_t padding_len = block_size - (data.size() % block_size);
    std::vector<uint8_t> padded = data;
    padded.insert(padded.end(), padding_len, static_cast<uint8_t>(padding_len));
    return padded;
}

/* Szyfruj dane za pomocą klucza przy użyciu AES i trybu CBC.
Dostarczone bajty klucza są wystarczająco długie (>= 64 bajty). Użyj prefiksu dostarczonych bajtów klucza, który odpowiada wymaganemu rozmiarowi.
Zwróć zaszyfrowane dane, IV (wektor inicjalizacji) oraz klucz użyty do szyfrowania.

@param key Bajty do wygenerowania klucza szyfrowania
@param data Dane do zaszyfrowania
@return krotka zawierająca: {zaszyfrowane dane, IV, klucz użyty do szyfrowania} */
std::tuple<std::vector<uint8_t>, std::vector<uint8_t>, std::vector<uint8_t>>
encrypt_data(const std::vector<uint8_t>& key, const std::vector<uint8_t>& data) {
    if (key.size() < 32) { // AES-256 wymaga 32 bajtów klucza
        throw std::invalid_argument("Key must be at least 32 bytes long for AES-256.");
    }

    // Wybierz odpowiedni rozmiar klucza (32 bajty dla AES-256)
    std::vector<uint8_t> aes_key(key.begin(), key.begin() + 32);

    // Przygotowanie danych do szyfrowania
    std::vector<uint8_t> padded_data = pkcs7_pad(data, AES_BLOCK_SIZE);
    std::vector<uint8_t> iv(AES_BLOCK_SIZE);
    
    // Inicjalizacja wektora IV
    if (!RAND_bytes(iv.data(), iv.size())) {
        throw std::runtime_error("Failed to generate random IV.");
    }

    // Inicjalizacja kontekstu AES
    AES_KEY enc_key;
    if (AES_set_encrypt_key(aes_key.data(), 256, &enc_key) < 0) {
        throw std::runtime_error("Failed to set AES encryption key.");
    }

    // Szyfrowanie danych w trybie CBC
    std::vector<uint8_t> encrypted_data(padded_data.size());
    AES_cbc_encrypt(padded_data.data(), encrypted_data.data(), padded_data.size(), &enc_key, iv.data(), AES_ENCRYPT);

    return std::make_tuple(encrypted_data, iv, aes_key);
}