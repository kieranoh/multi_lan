#include <openssl/aes.h>
#include <openssl/rand.h>
#include <vector>
#include <cstdint>
#include <tuple>
#include <stdexcept>
#include <memory>
#include <cstring>

std::tuple<std::vector<uint8_t>, std::vector<uint8_t>, std::vector<uint8_t>>
encrypt_data(const std::vector<uint8_t>& key, const std::vector<uint8_t>& data) {
    // Проверка входных параметров
    if (key.size() < 64) {
        throw std::invalid_argument("Key must be at least 64 bytes long");
    }
    
    // Определяем размер ключа AES-256 (32 байта)
    const size_t AES_KEY_SIZE = 32;
    
    // Извлекаем первые AES_KEY_SIZE байт из предоставленного ключа
    std::vector<uint8_t> encryption_key(key.begin(), key.begin() + AES_KEY_SIZE);
    
    // Генерируем случайный IV (вектор инициализации) для режима CBC
    std::vector<uint8_t> iv(AES_BLOCK_SIZE);
    if (RAND_bytes(iv.data(), AES_BLOCK_SIZE) != 1) {
        throw std::runtime_error("Failed to generate random IV");
    }
    
    // Дополняем данные по стандарту PKCS7
    std::vector<uint8_t> padded_data = data;
    size_t padding_len = AES_BLOCK_SIZE - (data.size() % AES_BLOCK_SIZE);
    padded_data.insert(padded_data.end(), padding_len, static_cast<uint8_t>(padding_len));
    
    // Выделяем память для зашифрованных данных
    std::vector<uint8_t> encrypted_data(padded_data.size());
    
    // Создаем и настраиваем контекст шифрования
    std::unique_ptr<AES_KEY> aes_key = std::make_unique<AES_KEY>();
    if (AES_set_encrypt_key(encryption_key.data(), AES_KEY_SIZE * 8, aes_key.get()) != 0) {
        throw std::runtime_error("Failed to set AES encryption key");
    }
    
    // Выполняем шифрование в режиме CBC
    std::vector<uint8_t> iv_copy = iv; // Копия IV для использования в функции шифрования
    AES_cbc_encrypt(padded_data.data(), encrypted_data.data(), 
                    padded_data.size(), aes_key.get(), iv_copy.data(), AES_ENCRYPT);
    
    return std::make_tuple(encrypted_data, iv, encryption_key);
}