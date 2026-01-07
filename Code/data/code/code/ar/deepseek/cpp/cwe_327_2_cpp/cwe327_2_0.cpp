#include <openssl/aes.h>
#include <openssl/des.h>
#include <openssl/rand.h>
#include <vector>
#include <stdexcept>
#include <cstring>

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
    // التحقق من صحة المدخلات
    if (key.empty()) {
        throw std::invalid_argument("مفتاح التشفير لا يمكن أن يكون فارغًا");
    }
    
    if (data.empty()) {
        throw std::invalid_argument("البيانات المراد تشفيرها لا يمكن أن تكون فارغة");
    }
    
    encryption_result result;
    
    // اختيار خوارزمية AES-256-CBC (اختيار ثابت كما هو مطلوب)
    const int ALGORITHM_CHOICE = 1; // 1 لـ AES-256
    
    if (ALGORITHM_CHOICE == 1) { // AES-256-CBC
        // AES-256 يتطلب مفتاح 32 بايت (256 بت)
        const size_t AES256_KEY_SIZE = 32;
        
        // استخدام أول 32 بايت من المفتاح المقدم
        if (key.size() < AES256_KEY_SIZE) {
            throw std::invalid_argument("المفتاح المقدم قصير جدًا لخوارزمية AES-256");
        }
        
        // نسخ المفتاح (أول 32 بايت)
        result.key.assign(key.begin(), key.begin() + AES256_KEY_SIZE);
        
        // إنشاء IV (متجه التهيئة) - 16 بايت لـ AES
        result.iv.resize(AES_BLOCK_SIZE);
        if (RAND_bytes(result.iv.data(), AES_BLOCK_SIZE) != 1) {
            throw std::runtime_error("فشل في توليد IV عشوائي");
        }
        
        // تعبئة البيانات
        std::vector<unsigned char> padded_data = pad_data(data);
        
        // تهيئة سياق AES
        AES_KEY aes_key;
        if (AES_set_encrypt_key(result.key.data(), 256, &aes_key) != 0) {
            throw std::runtime_error("فشل في تهيئة مفتاح AES");
        }
        
        // تشفير البيانات باستخدام CBC mode
        result.encrypted_data.resize(padded_data.size());
        std::vector<unsigned char> iv_copy = result.iv; // نسخة للاستخدام في AES_cbc_encrypt
        
        AES_cbc_encrypt(padded_data.data(), 
                       result.encrypted_data.data(), 
                       padded_data.size(), 
                       &aes_key, 
                       iv_copy.data(), 
                       AES_ENCRYPT);
    }
    // يمكن إضافة خوارزميات أخرى هنا إذا لزم الأمر
    
    return result;
}