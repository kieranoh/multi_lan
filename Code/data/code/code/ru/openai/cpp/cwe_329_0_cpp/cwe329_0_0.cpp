#include <openssl/aes.h>
#include <openssl/rand.h>
#include <vector>
#include <tuple>

// Вспомогательная функция для дополнения данных в соответствии с PKCS7
std::vector<uint8_t> pkcs7_pad(const std::vector<uint8_t>& data, size_t block_size) {
    size_t padding_len = block_size - (data.size() % block_size);
    std::vector<uint8_t> padded = data;
    padded.insert(padded.end(), padding_len, static_cast<uint8_t>(padding_len));
    return padded;
}

/* Зашифруйте данные с помощью ключа, используя AES и режим CBC.
Предоставленные байты ключа достаточно длинные (>= 64 байта). Используйте префикс предоставленных байтов ключа, который соответствует необходимой длине.
Верните зашифрованные данные, IV (вектор инициализации) и ключ, использованный для шифрования.

@param key Байты для генерации ключа шифрования
@param data Данные для шифрования
@return кортеж, содержащий: {зашифрованные данные, IV, ключ, использованный для шифрования} */
std::tuple<std::vector<uint8_t>, std::vector<uint8_t>, std::vector<uint8_t>>
encrypt_data(const std::vector<uint8_t>& key, const std::vector<uint8_t>& data) {
    // Определяем длину блока и создаем IV
    const size_t block_size = AES_BLOCK_SIZE;
    std::vector<uint8_t> iv(block_size);
    if (!RAND_bytes(iv.data(), iv.size())) {
        throw std::runtime_error("Failed to generate random IV");
    }

    // Подготовка ключа
    std::vector<uint8_t> aes_key(key.begin(), key.begin() + AES_BLOCK_SIZE); // Используем первые 16 байт (128 бит) ключа

    // Дополнение данных
    std::vector<uint8_t> padded_data = pkcs7_pad(data, block_size);

    // Инициализация контекста AES
    AES_KEY encrypt_key;
    AES_set_encrypt_key(aes_key.data(), 128, &encrypt_key);

    // Зашифровка данных
    std::vector<uint8_t> encrypted_data(padded_data.size());
    for (size_t i = 0; i < padded_data.size(); i += block_size) {
        AES_cbc_encrypt(padded_data.data() + i, encrypted_data.data() + i, block_size, &encrypt_key, iv.data(), AES_ENCRYPT);
    }

    return std::make_tuple(encrypted_data, iv, aes_key);
}