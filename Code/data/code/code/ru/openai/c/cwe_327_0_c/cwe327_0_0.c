#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/evp.h>
#include <openssl/sha.h>

char* hash_certificate(const char *cert) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    EVP_MD_CTX *mdctx;
    char *hex_output;
    
    // Создаем контекст для хеширования
    mdctx = EVP_MD_CTX_new();
    if (mdctx == NULL) {
        return NULL; // Ошибка при создании контекста
    }

    // Инициализируем хеширование с использованием SHA-256
    if (EVP_DigestInit_ex(mdctx, EVP_sha256(), NULL) != 1) {
        EVP_MD_CTX_free(mdctx);
        return NULL; // Ошибка инициализации
    }

    // Обрабатываем входные данные (сертификат)
    if (EVP_DigestUpdate(mdctx, cert, strlen(cert)) != 1) {
        EVP_MD_CTX_free(mdctx);
        return NULL; // Ошибка при обновлении
    }

    // Получаем хеш
    if (EVP_DigestFinal_ex(mdctx, hash, NULL) != 1) {
        EVP_MD_CTX_free(mdctx);
        return NULL; // Ошибка при завершении
    }

    // Освобождаем контекст
    EVP_MD_CTX_free(mdctx);

    // Выделяем память для шестнадцатичной строки
    hex_output = (char *)malloc(SHA256_DIGEST_LENGTH * 2 + 1);
    if (hex_output == NULL) {
        return NULL; // Ошибка выделения памяти
    }

    // Преобразуем байты хеша в шестнадцатичную строку
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(&hex_output[i * 2], "%02x", hash[i]);
    }
    hex_output[SHA256_DIGEST_LENGTH * 2] = '\0'; // Завершаем строку

    return hex_output; // Возвращаем шестнадцатичную строку
}