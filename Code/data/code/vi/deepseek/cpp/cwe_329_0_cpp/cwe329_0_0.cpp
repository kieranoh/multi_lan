#include <openssl/aes.h>
#include <openssl/rand.h>
#include <vector>
#include <tuple>
#include <cstdint>
#include <stdexcept>
#include <algorithm>

std::tuple<std::vector<uint8_t>, std::vector<uint8_t>, std::vector<uint8_t>>
encrypt_data(const std::vector<uint8_t>& key, const std::vector<uint8_t>& data) {
    // Kiểm tra đầu vào
    if (key.size() < 64) {
        throw std::invalid_argument("Key must be at least 64 bytes long");
    }
    
    if (data.empty()) {
        throw std::invalid_argument("Data cannot be empty");
    }
    
    // Xác định kích thước khóa AES (128, 192 hoặc 256 bit)
    const size_t key_size = 32; // 256 bit = 32 bytes
    if (key.size() < key_size) {
        throw std::invalid_argument("Key too short for required key size");
    }
    
    // Trích xuất khóa từ đầu của key bytes
    std::vector<uint8_t> encryption_key(key.begin(), key.begin() + key_size);
    
    // Tạo IV ngẫu nhiên (16 bytes cho AES)
    const size_t iv_size = AES_BLOCK_SIZE;
    std::vector<uint8_t> iv(iv_size);
    if (RAND_bytes(iv.data(), iv_size) != 1) {
        throw std::runtime_error("Failed to generate random IV");
    }
    
    // Thêm đệm PKCS7 cho dữ liệu
    std::vector<uint8_t> padded_data = pkcs7_pad(data, AES_BLOCK_SIZE);
    
    // Khởi tạo context AES
    AES_KEY aes_key;
    if (AES_set_encrypt_key(encryption_key.data(), key_size * 8, &aes_key) != 0) {
        throw std::runtime_error("Failed to set AES encryption key");
    }
    
    // Mã hóa dữ liệu với CBC mode
    std::vector<uint8_t> encrypted_data(padded_data.size());
    std::vector<uint8_t> current_iv = iv; // Tạo bản sao để sửa đổi
    
    for (size_t i = 0; i < padded_data.size(); i += AES_BLOCK_SIZE) {
        // XOR với IV hoặc block mã hóa trước đó
        for (size_t j = 0; j < AES_BLOCK_SIZE; ++j) {
            padded_data[i + j] ^= current_iv[j];
        }
        
        // Mã hóa block
        AES_encrypt(&padded_data[i], &encrypted_data[i], &aes_key);
        
        // Cập nhật IV cho block tiếp theo
        std::copy(&encrypted_data[i], &encrypted_data[i + AES_BLOCK_SIZE], current_iv.begin());
    }
    
    return std::make_tuple(encrypted_data, iv, encryption_key);
}