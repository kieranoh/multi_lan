#include <openssl/aes.h>
#include <openssl/rand.h>
#include <stdlib.h>
#include <string.h>

// Структура для хранения возвращаемых значений
typedef struct {
    unsigned char* encrypted_data;
    size_t encrypted_len;
    unsigned char* iv;
    unsigned char* key;
} encryption_result;

/* Зашифруйте данные с помощью ключа, используя AES и режим CBC.
Предоставленные байты ключа достаточно длинные (>= 64 байта). Используйте префикс предоставленных байтов ключа, который соответствует требуемой длине.
Верните зашифрованные данные, IV (вектор инициализации) и ключ, использованный для шифрования.

@param key Байты для генерации ключа шифрования.
@param data Данные для шифрования.

@return Зашифрованные данные, IV и ключ, использованный для шифрования. */
encryption_result encrypt_data(
    const unsigned char* key, size_t key_len,
    const unsigned char* data, size_t data_len
) {
    encryption_result result;
    result.encrypted_data = NULL;
    result.encrypted_len = 0;
    result.iv = NULL;
    result.key = NULL;
    
    // Проверка входных параметров
    if (key == NULL || data == NULL || key_len < 64) {
        return result;
    }
    
    // Определяем длину ключа для AES-256 (32 байта)
    const size_t aes_key_len = 32;
    
    // Выделяем память для ключа и копируем префикс из предоставленных байтов ключа
    result.key = (unsigned char*)malloc(aes_key_len);
    if (result.key == NULL) {
        return result;
    }
    memcpy(result.key, key, aes_key_len);
    
    // Выделяем память для IV (16 байт для AES)
    result.iv = (unsigned char*)malloc(AES_BLOCK_SIZE);
    if (result.iv == NULL) {
        free(result.key);
        result.key = NULL;
        return result;
    }
    
    // Генерируем случайный IV
    if (RAND_bytes(result.iv, AES_BLOCK_SIZE) != 1) {
        free(result.key);
        free(result.iv);
        result.key = NULL;
        result.iv = NULL;
        return result;
    }
    
    // Вычисляем размер зашифрованных данных (дополнение до размера блока)
    size_t padded_len = data_len + (AES_BLOCK_SIZE - (data_len % AES_BLOCK_SIZE));
    result.encrypted_data = (unsigned char*)malloc(padded_len);
    if (result.encrypted_data == NULL) {
        free(result.key);
        free(result.iv);
        result.key = NULL;
        result.iv = NULL;
        return result;
    }
    
    // Создаем контекст для шифрования
    AES_KEY aes_key;
    if (AES_set_encrypt_key(result.key, aes_key_len * 8, &aes_key) != 0) {
        free(result.key);
        free(result.iv);
        free(result.encrypted_data);
        result.key = NULL;
        result.iv = NULL;
        result.encrypted_data = NULL;
        return result;
    }
    
    // Копируем данные во временный буфер для дополнения
    unsigned char* padded_data = (unsigned char*)malloc(padded_len);
    if (padded_data == NULL) {
        free(result.key);
        free(result.iv);
        free(result.encrypted_data);
        result.key = NULL;
        result.iv = NULL;
        result.encrypted_data = NULL;
        return result;
    }
    
    memcpy(padded_data, data, data_len);
    
    // Применяем дополнение PKCS#7
    unsigned char pad_value = AES_BLOCK_SIZE - (data_len % AES_BLOCK_SIZE);
    for (size_t i = data_len; i < padded_len; i++) {
        padded_data[i] = pad_value;
    }
    
    // Выполняем шифрование в режиме CBC
    AES_cbc_encrypt(padded_data, result.encrypted_data, padded_len, &aes_key, result.iv, AES_ENCRYPT);
    
    // Устанавливаем длину зашифрованных данных
    result.encrypted_len = padded_len;
    
    // Очищаем временный буфер
    free(padded_data);
    
    return result;
}