#include <openssl/aes.h>
#include <openssl/des.h>
#include <openssl/rand.h>
#include <vector>
#include <stdexcept>
#include <cstring>

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

encryption_result encrypt_data(
    const std::vector<unsigned char>& key,
    const std::vector<unsigned char>& data
) {
    encryption_result result;
    
    // Выбираем AES-256-CBC (фиксированный выбор алгоритма согласно требованию)
    const int ALGORITHM_KEY_SIZE = 32; // 256 бит для AES-256
    const int IV_SIZE = AES_BLOCK_SIZE; // 16 байт для AES
    
    // Проверяем, что ключ достаточно длинный
    if (key.size() < ALGORITHM_KEY_SIZE) {
        throw std::runtime_error("Key is too short for AES-256");
    }
    
    // Используем первые ALGORITHM_KEY_SIZE байт из предоставленного ключа
    result.key = std::vector<unsigned char>(key.begin(), key.begin() + ALGORITHM_KEY_SIZE);
    
    // Генерируем случайный IV
    result.iv.resize(IV_SIZE);
    if (RAND_bytes(result.iv.data(), IV_SIZE) != 1) {
        throw std::runtime_error("Failed to generate random IV");
    }
    
    // Дополняем данные до размера блока AES
    std::vector<unsigned char> padded_data = pad_data(data);
    
    // Инициализируем контекст AES
    AES_KEY aes_key;
    if (AES_set_encrypt_key(result.key.data(), ALGORITHM_KEY_SIZE * 8, &aes_key) != 0) {
        throw std::runtime_error("Failed to set AES encryption key");
    }
    
    // Выделяем память для зашифрованных данных
    result.encrypted_data.resize(padded_data.size());
    
    // Шифруем данные в режиме CBC
    unsigned char ivec[IV_SIZE];
    std::memcpy(ivec, result.iv.data(), IV_SIZE);
    
    AES_cbc_encrypt(padded_data.data(), 
                    result.encrypted_data.data(), 
                    padded_data.size(), 
                    &aes_key, 
                    ivec, 
                    AES_ENCRYPT);
    
    return result;
}