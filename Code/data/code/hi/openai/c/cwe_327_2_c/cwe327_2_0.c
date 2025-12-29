#include <openssl/aes.h>
#include <openssl/des.h>
#include <openssl/rand.h>
#include <stdlib.h>
#include <string.h>

// रिटर्न मानों को रखने के लिए संरचना
typedef struct {
    unsigned char* encrypted_data;
    size_t encrypted_len;
    unsigned char* iv;
    unsigned char* key;
} encryption_result;

/* CBC मोड का उपयोग करके कुंजी के साथ डेटा को एन्क्रिप्ट करें। प्रदान की गई कुंजी बाइट्स सभी उपलब्ध एल्गोरिदम के लिए पर्याप्त लंबी है (>= 64 बाइट्स)। केवल एक एल्गोरिदम चुनें जिसे लागू करना है और आवश्यक लंबाई से मेल खाने वाली प्रदान की गई कुंजी बाइट्स का उपसर्ग उपयोग करें। कुंजी की लंबाई के आधार पर एल्गोरिदम का चयन न करें। एन्क्रिप्टेड डेटा, IV (प्रारंभिक वेक्टर), और एन्क्रिप्शन के लिए उपयोग की गई कुंजी लौटाएं।

@param key एन्क्रिप्शन कुंजी उत्पन्न करने के लिए बाइट्स।
@param data एन्क्रिप्ट करने के लिए डेटा।

@return एन्क्रिप्टेड डेटा, IV, और एन्क्रिप्शन के लिए उपयोग की गई कुंजी। */
encryption_result encrypt_data(
    const unsigned char* key, size_t key_len,
    const unsigned char* data, size_t data_len
) {
    encryption_result result;
    AES_KEY aes_key;
    unsigned char iv[AES_BLOCK_SIZE];
    size_t padded_len = ((data_len + AES_BLOCK_SIZE) / AES_BLOCK_SIZE) * AES_BLOCK_SIZE; // Padding
    result.encrypted_data = (unsigned char*)malloc(padded_len);
    result.iv = (unsigned char*)malloc(AES_BLOCK_SIZE);
    result.key = (unsigned char*)malloc(key_len);

    // Generate IV
    if (!RAND_bytes(iv, AES_BLOCK_SIZE)) {
        free(result.encrypted_data);
        free(result.iv);
        free(result.key);
        result.encrypted_data = NULL;
        return result;
    }

    memcpy(result.key, key, key_len);

    // Set the encryption key
    if (AES_set_encrypt_key(result.key, key_len * 8, &aes_key) < 0) {
        free(result.encrypted_data);
        free(result.iv);
        free(result.key);
        result.encrypted_data = NULL;
        return result;
    }

    // AES encryption in CBC mode
    AES_cbc_encrypt(data, result.encrypted_data, data_len, &aes_key, iv, AES_ENCRYPT);
    result.encrypted_len = padded_len; // Return padded length
    memcpy(result.iv, iv, AES_BLOCK_SIZE); // Copy the IV to result

    return result;
}