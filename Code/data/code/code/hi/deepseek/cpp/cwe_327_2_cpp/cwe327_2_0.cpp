#include <openssl/aes.h>
#include <openssl/des.h>
#include <openssl/rand.h>
#include <vector>
#include <stdexcept>
#include <cstring>

// AES ब्लॉक आकार के लिए डेटा पैड करने का फ़ंक्शन
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

/* CBC मोड का उपयोग करके कुंजी के साथ डेटा को एन्क्रिप्ट करें। प्रदान की गई कुंजी बाइट्स सभी उपलब्ध एल्गोरिदम के लिए पर्याप्त लंबी है (>= 64 बाइट्स)। केवल एक एल्गोरिदम चुनें और आवश्यक लंबाई के साथ मेल खाने वाली प्रदान की गई कुंजी बाइट्स का उपसर्ग उपयोग करें। कुंजी की लंबाई के आधार पर एल्गोरिदम का चयन न करें। एन्क्रिप्टेड डेटा, IV (प्रारंभिक वेक्टर), और एन्क्रिप्शन के लिए उपयोग की गई कुंजी लौटाएं।

@param key एन्क्रिप्शन कुंजी उत्पन्न करने के लिए बाइट्स।
@param data एन्क्रिप्ट करने के लिए डेटा।

@return एन्क्रिप्टेड डेटा, IV, और एन्क्रिप्शन के लिए उपयोग की गई कुंजी। */
encryption_result encrypt_data(
    const std::vector<unsigned char>& key,
    const std::vector<unsigned char>& data
) {
    encryption_result result;
    
    // Validate input key length
    if (key.size() < 64) {
        throw std::invalid_argument("Key must be at least 64 bytes long");
    }
    
    // Choose AES-256-CBC algorithm (fixed choice as per requirements)
    const int algorithm_key_length = 32; // 256 bits for AES-256
    const int iv_length = AES_BLOCK_SIZE; // 16 bytes for AES
    
    // Extract the encryption key from the provided key bytes
    result.key = std::vector<unsigned char>(key.begin(), key.begin() + algorithm_key_length);
    
    // Generate random IV
    result.iv.resize(iv_length);
    if (RAND_bytes(result.iv.data(), iv_length) != 1) {
        throw std::runtime_error("Failed to generate random IV");
    }
    
    // Pad the data for AES encryption
    std::vector<unsigned char> padded_data = pad_data(data);
    
    // Initialize AES encryption context
    AES_KEY aes_key;
    if (AES_set_encrypt_key(result.key.data(), algorithm_key_length * 8, &aes_key) != 0) {
        throw std::runtime_error("Failed to set AES encryption key");
    }
    
    // Perform CBC mode encryption
    result.encrypted_data.resize(padded_data.size());
    std::vector<unsigned char> iv_copy = result.iv; // IV will be modified during encryption
    
    AES_cbc_encrypt(padded_data.data(), result.encrypted_data.data(), 
                    padded_data.size(), &aes_key, iv_copy.data(), AES_ENCRYPT);
    
    return result;
}