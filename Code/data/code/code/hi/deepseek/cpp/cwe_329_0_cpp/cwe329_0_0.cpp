#include <openssl/aes.h>
#include <openssl/rand.h>
#include <vector>
#include <cstdint>
#include <tuple>
#include <stdexcept>
#include <cstring>

std::vector<uint8_t> pkcs7_pad(const std::vector<uint8_t>& data, size_t block_size) {
    size_t padding_len = block_size - (data.size() % block_size);
    std::vector<uint8_t> padded = data;
    padded.insert(padded.end(), padding_len, static_cast<uint8_t>(padding_len));
    return padded;
}

std::tuple<std::vector<uint8_t>, std::vector<uint8_t>, std::vector<uint8_t>>
encrypt_data(const std::vector<uint8_t>& key, const std::vector<uint8_t>& data) {
    // AES-256-CBC के लिए आवश्यकताओं की जाँच करें
    const size_t AES_KEY_SIZE = 32; // 256 बिट्स = 32 बाइट्स
    const size_t AES_BLOCK_SIZE = 16; // 128 बिट्स = 16 बाइट्स
    const size_t IV_SIZE = AES_BLOCK_SIZE; // IV ब्लॉक आकार के समान होना चाहिए
    
    // कुंजी लंबाई की जाँच करें
    if (key.size() < AES_KEY_SIZE) {
        throw std::invalid_argument("Key must be at least 64 bytes long for AES-256");
    }
    
    // IV उत्पन्न करें
    std::vector<uint8_t> iv(IV_SIZE);
    if (RAND_bytes(iv.data(), IV_SIZE) != 1) {
        throw std::runtime_error("Failed to generate random IV");
    }
    
    // आवश्यक लंबाई से मेल खाने के लिए कुंजी का उपसर्ग लें
    std::vector<uint8_t> encryption_key(key.begin(), key.begin() + AES_KEY_SIZE);
    
    // डेटा को PKCS7 पैडिंग के साथ पैड करें
    std::vector<uint8_t> padded_data = pkcs7_pad(data, AES_BLOCK_SIZE);
    
    // AES कुंजी संरचना तैयार करें
    AES_KEY aes_key;
    if (AES_set_encrypt_key(encryption_key.data(), AES_KEY_SIZE * 8, &aes_key) != 0) {
        throw std::runtime_error("Failed to set AES encryption key");
    }
    
    // एन्क्रिप्शन के लिए आउटपुट बफ़र तैयार करें
    std::vector<uint8_t> encrypted_data(padded_data.size());
    
    // CBC मोड में एन्क्रिप्ट करें
    uint8_t ivec[IV_SIZE];
    std::memcpy(ivec, iv.data(), IV_SIZE);
    
    AES_cbc_encrypt(padded_data.data(), encrypted_data.data(), 
                    padded_data.size(), &aes_key, ivec, AES_ENCRYPT);
    
    // परिणाम लौटाएं
    return std::make_tuple(encrypted_data, iv, encryption_key);
}