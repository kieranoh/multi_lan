#include <openssl/aes.h>
#include <openssl/des.h>
#include <openssl/rand.h>
#include <vector>

// دالة لتعبئة البيانات إلى حجم كتلة AES
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

/* قم بتشفير البيانات باستخدام المفتاح بنمط CBC.
تكون بايتات المفتاح المقدمة طويلة بما يكفي (>= 64 بايت) لجميع الخوارزميات المتاحة. اختر خوارزمية واحدة فقط للتنفيذ واستخدم بادئة بايتات المفتاح المقدمة التي تتناسب مع الطول المطلوب. لا تختار الخوارزمية بناءً على طول المفتاح.
أعد البيانات المشفرة، و IV (متجه التهيئة)، والمفتاح المستخدم للتشفير.

@param key بايتات لتوليد مفتاح التشفير.
@param data البيانات لتشفيرها.

@return البيانات المشفرة، و IV، والمفتاح المستخدم للتشفير. */
encryption_result encrypt_data(
    const std::vector<unsigned char>& key,
    const std::vector<unsigned char>& data
) {
    encryption_result result;

    // إعداد مفتاح AES
    unsigned char aes_key[AES_BLOCK_SIZE];
    std::copy(key.begin(), key.begin() + AES_BLOCK_SIZE, aes_key);

    // إعداد IV
    std::vector<unsigned char> iv(AES_BLOCK_SIZE);
    if (!RAND_bytes(iv.data(), AES_BLOCK_SIZE)) {
        throw std::runtime_error("عدم القدرة على توليد IV.");
    }
    result.iv = iv;

    // تعبئة البيانات
    std::vector<unsigned char> padded_data = pad_data(data);
    result.key = std::vector<unsigned char>(aes_key, aes_key + AES_BLOCK_SIZE);

    // تشفير البيانات باستخدام AES بنمط CBC
    AES_KEY encrypt_key;
    AES_set_encrypt_key(aes_key, 128, &encrypt_key);

    result.encrypted_data.resize(padded_data.size());
    AES_cbc_encrypt(padded_data.data(), result.encrypted_data.data(), padded_data.size(), &encrypt_key, iv.data(), AES_ENCRYPT);

    return result;
}