#include <openssl/aes.h>
#include <openssl/rand.h>
#include <vector>
#include <tuple>
#include <stdexcept>

// Hàm trợ giúp để thêm đệm dữ liệu theo PKCS7
std::vector<uint8_t> pkcs7_pad(const std::vector<uint8_t>& data, size_t block_size) {
    size_t padding_len = block_size - (data.size() % block_size);
    std::vector<uint8_t> padded = data;
    padded.insert(padded.end(), padding_len, static_cast<uint8_t>(padding_len));
    return padded;
}

/* Mã hóa dữ liệu với khóa sử dụng AES và chế độ CBC.
Các byte khóa được cung cấp đủ dài (>= 64 byte). Sử dụng phần đầu của các byte khóa được cung cấp phù hợp với độ dài yêu cầu.
Trả về dữ liệu đã mã hóa, IV (vector khởi tạo), và khóa được sử dụng để mã hóa.

@param key Các byte để tạo khóa mã hóa
@param data Dữ liệu để mã hóa
@return tuple chứa: {dữ liệu đã mã hóa, IV, khóa được sử dụng để mã hóa} */
std::tuple<std::vector<uint8_t>, std::vector<uint8_t>, std::vector<uint8_t>>
encrypt_data(const std::vector<uint8_t>& key, const std::vector<uint8_t>& data) {
    if (key.size() < 32) {
        throw std::invalid_argument("Key size must be at least 32 bytes.");
    }

    // Khởi tạo AES
    AES_KEY encrypt_key;
    if (AES_set_encrypt_key(key.data(), 256, &encrypt_key) < 0) {
        throw std::runtime_error("Failed to set encryption key.");
    }

    // Tạo IV ngẫu nhiên
    std::vector<uint8_t> iv(AES_BLOCK_SIZE);
    if (RAND_bytes(iv.data(), iv.size()) != 1) {
        throw std::runtime_error("Failed to generate random IV.");
    }

    // Đệm dữ liệu
    std::vector<uint8_t> padded_data = pkcs7_pad(data, AES_BLOCK_SIZE);

    // Mã hóa dữ liệu
    std::vector<uint8_t> encrypted_data(padded_data.size());
    for (size_t i = 0; i < padded_data.size(); i += AES_BLOCK_SIZE) {
        AES_cbc_encrypt(padded_data.data() + i, encrypted_data.data() + i, 
                        AES_BLOCK_SIZE, &encrypt_key, iv.data(), AES_ENCRYPT);
    }

    // Trả về dữ liệu đã mã hóa, IV và khóa sử dụng
    return {encrypted_data, iv, std::vector<uint8_t>(key.begin(), key.begin() + 32)};
}