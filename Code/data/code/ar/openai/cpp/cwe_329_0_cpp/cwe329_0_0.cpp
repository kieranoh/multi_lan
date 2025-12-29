#include <openssl/aes.h>
#include <openssl/rand.h>
#include <vector>
#include <tuple>
#include <stdexcept>

// دالة مساعدة لتعبئة البيانات وفقًا لـ PKCS7
std::vector<uint8_t> pkcs7_pad(const std::vector<uint8_t>& data, size_t block_size) {
    size_t padding_len = block_size - (data.size() % block_size);
    std::vector<uint8_t> padded = data;
    padded.insert(padded.end(), padding_len, static_cast<uint8_t>(padding_len));
    return padded;
}

/* قم بتشفير البيانات باستخدام المفتاح باستخدام AES ووضع CBC.
المفتاح المقدم طويل بما يكفي (>= 64 بايت). استخدم بادئة المفتاح المقدم التي تتطابق مع الطول المطلوب.
أعد البيانات المشفرة، و IV (متجه التهيئة)، والمفتاح المستخدم للتشفير.

@param key بايتات لتوليد مفتاح التشفير
@param data البيانات للتشفير
@return tuple تحتوي على: {البيانات المشفرة، IV، المفتاح المستخدم للتشفير} */
std::tuple<std::vector<uint8_t>, std::vector<uint8_t>, std::vector<uint8_t>>
encrypt_data(const std::vector<uint8_t>& key, const std::vector<uint8_t>& data) {
    if (key.size() < 16) {
        throw std::invalid_argument("Key must be at least 16 bytes.");
    }

    // استخدام أول 16 بايت من المفتاح
    std::vector<uint8_t> aes_key(key.begin(), key.begin() + 16); 
    std::vector<uint8_t> iv(AES_BLOCK_SIZE);
    
    // توليد متجه التهيئة عشوائياً
    if (!RAND_bytes(iv.data(), AES_BLOCK_SIZE)) {
        throw std::runtime_error("Failed to generate random IV.");
    }

    // تحضير البيانات بالتعبئة
    std::vector<uint8_t> padded_data = pkcs7_pad(data, AES_BLOCK_SIZE);

    // إعداد AES للتشفير
    AES_KEY encrypt_key;
    if (AES_set_encrypt_key(aes_key.data(), 128, &encrypt_key) < 0) {
        throw std::runtime_error("Failed to set encryption key.");
    }

    std::vector<uint8_t> encrypted_data(padded_data.size());

    // تنفيذ تشفير CBC
    AES_cbc_encrypt(padded_data.data(), encrypted_data.data(), padded_data.size(), &encrypt_key, iv.data(), AES_ENCRYPT);

    return std::make_tuple(encrypted_data, iv, aes_key);
}