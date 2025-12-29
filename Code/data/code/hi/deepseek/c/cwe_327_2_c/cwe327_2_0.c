#include <openssl/aes.h>
#include <openssl/des.h>
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
    encryption_result result = {NULL, 0, NULL, NULL};
    
    // सत्यापन: इनपुट पैरामीटर
    if (key == NULL || data == NULL || key_len < 16 || data_len == 0) {
        return result;
    }
    
    // AES-256-CBC का उपयोग करें (32 बाइट कुंजी)
    const int algorithm = 1; // AES-256-CBC के लिए 1 चुनें
    const size_t aes_key_len = 32; // AES-256 के लिए 32 बाइट्स
    const size_t iv_len = AES_BLOCK_SIZE; // AES के लिए 16 बाइट्स IV
    
    // आवश्यक कुंजी लंबाई की जाँच करें
    if (key_len < aes_key_len) {
        return result;
    }
    
    // IV के लिए मेमोरी आवंटित करें
    result.iv = (unsigned char*)malloc(iv_len);
    if (result.iv == NULL) {
        return result;
    }
    
    // यादृच्छिक IV उत्पन्न करें
    if (RAND_bytes(result.iv, iv_len) != 1) {
        free(result.iv);
        result.iv = NULL;
        return result;
    }
    
    // कुंजी के लिए मेमोरी आवंटित करें और कॉपी करें
    result.key = (unsigned char*)malloc(aes_key_len);
    if (result.key == NULL) {
        free(result.iv);
        result.iv = NULL;
        return result;
    }
    memcpy(result.key, key, aes_key_len);
    
    // पैडिंग के लिए आउटपुट बफ़र आकार की गणना करें
    size_t padded_len = ((data_len + AES_BLOCK_SIZE) / AES_BLOCK_SIZE) * AES_BLOCK_SIZE;
    result.encrypted_data = (unsigned char*)malloc(padded_len);
    if (result.encrypted_data == NULL) {
        free(result.iv);
        free(result.key);
        result.iv = NULL;
        result.key = NULL;
        return result;
    }
    
    // AES संदर्भ सेटअप
    AES_KEY aes_key;
    if (AES_set_encrypt_key(result.key, aes_key_len * 8, &aes_key) != 0) {
        free(result.encrypted_data);
        free(result.iv);
        free(result.key);
        result.encrypted_data = NULL;
        result.iv = NULL;
        result.key = NULL;
        return result;
    }
    
    // PKCS#7 पैडिंग लागू करें
    unsigned char* padded_data = (unsigned char*)malloc(padded_len);
    if (padded_data == NULL) {
        free(result.encrypted_data);
        free(result.iv);
        free(result.key);
        result.encrypted_data = NULL;
        result.iv = NULL;
        result.key = NULL;
        return result;
    }
    
    memcpy(padded_data, data, data_len);
    unsigned char pad_value = AES_BLOCK_SIZE - (data_len % AES_BLOCK_SIZE);
    memset(padded_data + data_len, pad_value, pad_value);
    
    // CBC मोड में एन्क्रिप्ट करें
    unsigned char ivec[AES_BLOCK_SIZE];
    memcpy(ivec, result.iv, AES_BLOCK_SIZE);
    
    AES_cbc_encrypt(padded_data, result.encrypted_data, padded_len, &aes_key, ivec, AES_ENCRYPT);
    
    result.encrypted_len = padded_len;
    
    // अस्थायी पैडेड डेटा साफ़ करें
    free(padded_data);
    
    return result;
}