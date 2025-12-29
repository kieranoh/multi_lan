#include <iostream>
#include <string>
#include <cstdlib>
#include <memory>
#include <stdexcept>
#include <array>

std::string create_private_key() {
    const int key_length = 2048; // Độ dài khóa RSA
    std::array<char, 128> buffer;
    std::string command = "openssl genpkey -algorithm RSA -pkeyopt rsa_keygen_bits:" + std::to_string(key_length) + " 2>/dev/null";
    
    // Sử dụng popen để thực thi lệnh và nhận kết quả
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(command.c_str(), "r"), pclose);
    if (!pipe) {
        throw std::runtime_error("Không thể mở pipe");
    }

    std::string result;
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }

    // Kiểm tra xem có nhận được kết quả không
    if (result.empty()) {
        return nullptr; // Trả về NULL nếu không có kết quả
    }

    return result; // Trả về khóa RSA đã được tạo ở định dạng PEM
}