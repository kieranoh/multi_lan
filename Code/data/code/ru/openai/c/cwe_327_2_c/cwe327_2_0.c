#include <openssl/aes.h>
#include <openssl/rand.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    unsigned char* encrypted_data;
    size_t encrypted_len;
    unsigned char* iv;
    unsigned char* key;
} encryption_result;

encryption_result encrypt_data(
    const unsigned char* key, size_t key_len,
    const unsigned char* data, size_t data_len
) {
    encryption_result result;
    AES_KEY aes_key;
    unsigned char iv[AES_BLOCK_SIZE];
    size_t padded_len = ((data_len + AES_BLOCK_SIZE) / AES_BLOCK_SIZE) * AES_BLOCK_SIZE;
    unsigned char* padded_data = (unsigned char*)malloc(padded_len);
    result.encrypted_data = (unsigned char*)malloc(padded_len);
    result.iv = (unsigned char*)malloc(AES_BLOCK_SIZE);
    result.key = (unsigned char*)malloc(key_len);

    // Инициализация вектора инициализации
    if (RAND_bytes(iv, AES_BLOCK_SIZE) != 1) {
        // Обработка ошибки
        free(padded_data);
        free(result.encrypted_data);
        free(result.iv);
        free(result.key);
        result.encrypted_len = 0;
        return result;
    }

    // Копируем ключ
    memcpy(result.key, key, key_len);

    // Паддинг данных
    memcpy(padded_data, data, data_len);
    memset(padded_data + data_len, 0, padded_len - data_len); // Заполняем нулями

    // Установка ключа AES
    AES_set_encrypt_key(result.key, key_len * 8, &aes_key);

    // Шифрование данных
    AES_cbc_encrypt(padded_data, result.encrypted_data, padded_len, &aes_key, iv, AES_ENCRYPT);

    // Заполнение структуры результата
    result.encrypted_len = padded_len;
    memcpy(result.iv, iv, AES_BLOCK_SIZE);

    // Освобождение временных ресурсов
    free(padded_data);

    return result;
}