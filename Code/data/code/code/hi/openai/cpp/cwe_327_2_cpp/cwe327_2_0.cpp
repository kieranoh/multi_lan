#include <openssl/aes.h>
#include <openssl/rand.h>
#include <vector>

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
    
    // AES के लिए कुंजी और IV सेट करें
    AES_KEY aes_key;
    std::vector<unsigned char> iv(AES_BLOCK_SIZE);
    RAND_bytes(iv.data(), AES_BLOCK_SIZE); // IV उत्पन्न करें

    // डेटा को पैड करें
    std::vector<unsigned char> padded_data = pad_data(data);
    result.key = std::vector<unsigned char>(key.begin(), key.begin() + 32); // केवल पहले 32 बाइट्स लीजिए

    // एन्क्रिप्ट करें
    result.encrypted_data.resize(padded_data.size());
    AES_set_encrypt_key(result.key.data(), 256, &aes_key); // 256-बिट AES कुंजी सेट करें
    for (size_t i = 0; i < padded_data.size(); i += AES_BLOCK_SIZE) {
        AES_cbc_encrypt(padded_data.data() + i, result.encrypted_data.data() + i, AES_BLOCK_SIZE, &aes_key, iv.data(), AES_ENCRYPT);
    }

    result.iv = iv; // IV सेट करें
    return result;
}