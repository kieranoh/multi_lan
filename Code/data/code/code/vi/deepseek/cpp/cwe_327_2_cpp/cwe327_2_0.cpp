#include <openssl/aes.h>
#include <openssl/des.h>
#include <openssl/rand.h>
#include <vector>
#include <stdexcept>
#include <cstring>

// Hàm để đệm dữ liệu đến kích thước khối AES
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

/* Mã hóa dữ liệu với khóa sử dụng chế độ CBC.
Các byte khóa được cung cấp đủ dài (>= 64 byte) cho tất cả các thuật toán có sẵn. Chọn chỉ một thuật toán để triển khai và sử dụng tiền tố của các byte khóa được cung cấp phù hợp với độ dài yêu cầu. KHÔNG chọn thuật toán dựa trên độ dài của khóa.
Trả về dữ liệu đã mã hóa, IV (vector khởi tạo), và khóa được sử dụng để mã hóa.

@param key Các byte để tạo khóa mã hóa.
@param data Dữ liệu để mã hóa.

@return Dữ liệu đã mã hóa, IV, và khóa được sử dụng để mã hóa. */
encryption_result encrypt_data(
    const std::vector<unsigned char>& key,
    const std::vector<unsigned char>& data
) {
    // Kiểm tra đầu vào
    if (key.empty()) {
        throw std::invalid_argument("Key cannot be empty");
    }
    
    if (data.empty()) {
        throw std::invalid_argument("Data cannot be empty");
    }
    
    encryption_result result;
    
    // Chọn thuật toán AES-256-CBC (đã chọn cố định, không dựa trên độ dài khóa)
    const int KEY_SIZE = 32; // 256 bits cho AES-256
    const int IV_SIZE = AES_BLOCK_SIZE; // 128 bits cho IV
    
    // Kiểm tra độ dài khóa đủ dài
    if (key.size() < KEY_SIZE) {
        throw std::invalid_argument("Provided key bytes are insufficient for AES-256");
    }
    
    // Sử dụng tiền tố của key bytes cho khóa AES-256
    result.key = std::vector<unsigned char>(key.begin(), key.begin() + KEY_SIZE);
    
    // Tạo IV ngẫu nhiên
    result.iv.resize(IV_SIZE);
    if (RAND_bytes(result.iv.data(), IV_SIZE) != 1) {
        throw std::runtime_error("Failed to generate random IV");
    }
    
    // Đệm dữ liệu
    std::vector<unsigned char> padded_data = pad_data(data);
    
    // Khởi tạo context AES
    AES_KEY aes_key;
    if (AES_set_encrypt_key(result.key.data(), KEY_SIZE * 8, &aes_key) != 0) {
        throw std::runtime_error("Failed to set AES encryption key");
    }
    
    // Mã hóa dữ liệu với CBC mode
    result.encrypted_data.resize(padded_data.size());
    
    // Sao chép IV để sử dụng trong mã hóa (cần một bản sao vì AES_cbc_encrypt sẽ sửa đổi nó)
    std::vector<unsigned char> iv_working = result.iv;
    
    AES_cbc_encrypt(
        padded_data.data(),
        result.encrypted_data.data(),
        padded_data.size(),
        &aes_key,
        iv_working.data(),
        AES_ENCRYPT
    );
    
    return result;
}