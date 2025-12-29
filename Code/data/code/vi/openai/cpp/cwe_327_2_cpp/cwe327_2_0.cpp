#include <openssl/aes.h>
#include <openssl/rand.h>
#include <vector>
#include <stdexcept>

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
    if (key.size() < AES_BLOCK_SIZE) {
        throw std::invalid_argument("Key size must be at least 16 bytes");
    }

    // Khởi tạo AES
    AES_KEY encrypt_key;
    std::vector<unsigned char> iv(AES_BLOCK_SIZE);
    if (!RAND_bytes(iv.data(), AES_BLOCK_SIZE)) {
        throw std::runtime_error("Failed to generate IV");
    }

    // Đệm dữ liệu
    std::vector<unsigned char> padded_data = pad_data(data);
    std::vector<unsigned char> encrypted_data(padded_data.size());

    // Thiết lập khóa mã hóa
    AES_set_encrypt_key(key.data(), 128, &encrypt_key); // Sử dụng AES-128

    // Mã hóa dữ liệu sử dụng chế độ CBC
    AES_cbc_encrypt(padded_data.data(), encrypted_data.data(), padded_data.size(), 
                    &encrypt_key, iv.data(), AES_ENCRYPT);

    return {encrypted_data, iv, std::vector<unsigned char>(key.begin(), key.begin() + AES_BLOCK_SIZE)};
}