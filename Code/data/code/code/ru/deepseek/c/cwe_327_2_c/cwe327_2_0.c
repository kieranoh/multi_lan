#include <openssl/aes.h>
#include <openssl/des.h>
#include <openssl/rand.h>
#include <string.h>
#include <stdlib.h>

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
    encryption_result result = {NULL, 0, NULL, NULL};
    
    // Выбираем AES-256-CBC (фиксированный выбор алгоритма)
    const int algorithm_key_len = 32; // 256 бит для AES-256
    const int iv_len = AES_BLOCK_SIZE; // 16 байт для AES
    
    // Проверяем, что ключ достаточно длинный
    if (key_len < algorithm_key_len) {
        return result; // Возвращаем пустой результат
    }
    
    // Выделяем память для ключа алгоритма
    unsigned char* algorithm_key = (unsigned char*)malloc(algorithm_key_len);
    if (!algorithm_key) {
        return result;
    }
    
    // Копируем первые algorithm_key_len байт из предоставленного ключа
    memcpy(algorithm_key, key, algorithm_key_len);
    
    // Выделяем память для IV
    unsigned char* iv = (unsigned char*)malloc(iv_len);
    if (!iv) {
        free(algorithm_key);
        return result;
    }
    
    // Генерируем случайный IV
    if (RAND_bytes(iv, iv_len) != 1) {
        free(algorithm_key);
        free(iv);
        return result;
    }
    
    // Вычисляем размер буфера для зашифрованных данных
    // AES требует выравнивание до размера блока
    size_t padded_len = ((data_len + AES_BLOCK_SIZE) / AES_BLOCK_SIZE) * AES_BLOCK_SIZE;
    unsigned char* encrypted = (unsigned char*)malloc(padded_len);
    if (!encrypted) {
        free(algorithm_key);
        free(iv);
        return result;
    }
    
    // Инициализируем контекст AES
    AES_KEY aes_key;
    if (AES_set_encrypt_key(algorithm_key, 256, &aes_key) != 0) {
        free(algorithm_key);
        free(iv);
        free(encrypted);
        return result;
    }
    
    // Шифруем данные в режиме CBC
    // Создаем копию данных для padding
    unsigned char* padded_data = (unsigned char*)malloc(padded_len);
    if (!padded_data) {
        free(algorithm_key);
        free(iv);
        free(encrypted);
        return result;
    }
    
    // Копируем исходные данные
    memcpy(padded_data, data, data_len);
    // Заполняем оставшуюся часть согласно PKCS#7 padding
    unsigned char pad_value = padded_len - data_len;
    memset(padded_data + data_len, pad_value, pad_value);
    
    // Выполняем шифрование
    AES_cbc_encrypt(padded_data, encrypted, padded_len, &aes_key, iv, AES_ENCRYPT);
    
    // Очищаем временный буфер
    free(padded_data);
    
    // Заполняем структуру результата
    result.encrypted_data = encrypted;
    result.encrypted_len = padded_len;
    result.iv = iv;
    result.key = algorithm_key;
    
    return result;
}