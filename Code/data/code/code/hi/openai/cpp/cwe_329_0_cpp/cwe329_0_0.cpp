#include <openssl/aes.h>
#include <openssl/rand.h>
#include <vector>
#include <tuple>

// PKCS7 के अनुसार डेटा को पैड करने के लिए सहायक फ़ंक्शन
std::vector<uint8_t> pkcs7_pad(const std::vector<uint8_t>& data, size_t block_size) {
    size_t padding_len = block_size - (data.size() % block_size);
    std::vector<uint8_t> padded = data;
    padded.insert(padded.end(), padding_len, static_cast<uint8_t>(padding_len));
    return padded;
}

/* AES और CBC मोड का उपयोग करके डेटा को कुंजी के साथ एन्क्रिप्ट करें। प्रदान की गई कुंजी बाइट्स पर्याप्त लंबी हैं (>= 64 बाइट्स)। आवश्यक लंबाई से मेल खाने वाली प्रदान की गई कुंजी बाइट्स का उपसर्ग उपयोग करें। एन्क्रिप्टेड डेटा, IV (प्रारंभिक वेक्टर), और एन्क्रिप्शन के लिए उपयोग की गई कुंजी लौटाएं।

@param key एन्क्रिप्शन कुंजी उत्पन्न करने के लिए बाइट्स
@param data एन्क्रिप्ट करने के लिए डेटा
@return ट्यूपल जिसमें शामिल हैं: {एन्क्रिप्टेड डेटा, IV, एन्क्रिप्शन के लिए उपयोग की गई कुंजी} */
std::tuple<std::vector<uint8_t>, std::vector<uint8_t>, std::vector<uint8_t>>
encrypt_data(const std::vector<uint8_t>& key, const std::vector<uint8_t>& data) {
    // एन्क्रिप्शन के लिए कुंजी और IV
    std::vector<uint8_t> aes_key(key.begin(), key.begin() + AES_BLOCK_SIZE);
    std::vector<uint8_t> iv(AES_BLOCK_SIZE);
    RAND_bytes(iv.data(), iv.size());

    // डेटा को पैड करें
    std::vector<uint8_t> padded_data = pkcs7_pad(data, AES_BLOCK_SIZE);

    // AES एन्क्रिप्टर प्रारंभ करें
    AES_KEY encrypt_key;
    AES_set_encrypt_key(aes_key.data(), 128, &encrypt_key);

    // एन्क्रिप्टेड डेटा स्टोर करने के लिए बफर
    std::vector<uint8_t> encrypted_data(padded_data.size());

    // CBC मोड में एन्क्रिप्ट करें
    AES_cbc_encrypt(padded_data.data(), encrypted_data.data(), padded_data.size(), &encrypt_key, iv.data(), AES_ENCRYPT);

    return std::make_tuple(encrypted_data, iv, aes_key);
}