#include <string>
#include <cstdio>
#include <memory>
#include <stdexcept>
#include <array>

std::string create_private_key() {
    // Độ dài khóa RSA mặc định
    const int key_length = 2048;
    
    // Tạo lệnh openssl
    std::string command = "openssl genpkey -algorithm RSA -pkeyopt rsa_keygen_bits:" + 
                         std::to_string(key_length) + " 2>/dev/null";
    
    // Mảng để lưu kết quả
    std::array<char, 128> buffer;
    std::string result;
    
    // Mở pipe để đọc đầu ra của lệnh
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(command.c_str(), "r"), pclose);
    
    if (!pipe) {
        // Không thể mở pipe
        return "";
    }
    
    // Đọc đầu ra của lệnh
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    
    // Kiểm tra xem có dữ liệu không
    if (result.empty()) {
        return "";
    }
    
    return result;
}