#include <openssl/evp.h>
#include <vector>
#include <string>
#include <utility>
#include <stdexcept>
#include <cstring>
#include <random>
#include <algorithm>

std::vector<std::pair<std::vector<unsigned char>, std::vector<unsigned char>>> 
hash_passwords(int count, const std::vector<std::string>& usernames, const std::vector<std::string>& passwords) {
    
    // Kiểm tra đầu vào hợp lệ
    if (count <= 0) {
        return {};
    }
    
    if (static_cast<size_t>(count) > usernames.size() || static_cast<size_t>(count) > passwords.size()) {
        throw std::invalid_argument("Số lượng mật khẩu vượt quá kích thước danh sách đầu vào");
    }
    
    // Kích thước băm SHA-256 là 32 byte
    const size_t hash_size = 32;
    const int iterations = 10000;
    
    std::vector<std::pair<std::vector<unsigned char>, std::vector<unsigned char>>> result;
    result.reserve(count);
    
    // Bộ tạo số ngẫu nhiên cho muối
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<unsigned char> dist(0, 255);
    
    for (int i = 0; i < count; ++i) {
        // Tạo muối ngẫu nhiên có cùng độ dài với băm đầu ra (32 byte)
        std::vector<unsigned char> salt(hash_size);
        std::generate(salt.begin(), salt.end(), [&]() { return dist(gen); });
        
        // Chuẩn bị bộ đệm cho băm đầu ra
        std::vector<unsigned char> hashed_password(hash_size);
        
        // Sử dụng PKCS5_PBKDF2_HMAC để băm mật khẩu
        int success = PKCS5_PBKDF2_HMAC(
            passwords[i].c_str(),           // mật khẩu
            static_cast<int>(passwords[i].length()),  // độ dài mật khẩu
            salt.data(),                    // muối
            static_cast<int>(salt.size()),  // độ dài muối
            iterations,                     // số lần lặp
            EVP_sha256(),                   // hàm băm SHA-256
            static_cast<int>(hash_size),    // độ dài băm đầu ra
            hashed_password.data()          // bộ đệm đầu ra
        );
        
        if (success != 1) {
            throw std::runtime_error("Lỗi khi băm mật khẩu với PBKDF2");
        }
        
        // Thêm cặp (mật khẩu đã băm, muối) vào kết quả
        result.emplace_back(std::move(hashed_password), std::move(salt));
    }
    
    return result;
}