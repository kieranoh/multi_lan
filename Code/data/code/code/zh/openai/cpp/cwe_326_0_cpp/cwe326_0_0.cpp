#include <iostream>
#include <string>
#include <sstream>
#include <stdexcept>
#include <array>
#include <memory>

std::string create_private_key() {
    const int key_length = 2048; // RSA 密钥长度
    std::array<char, 128> buffer;
    
    // 构建命令
    std::string command = "openssl genpkey -algorithm RSA -pkeyopt rsa_keygen_bits:" + std::to_string(key_length) + " 2>/dev/null";

    // 使用管道执行命令并读取输出
    std::shared_ptr<FILE> pipe(popen(command.c_str(), "r"), pclose);
    if (!pipe) {
        return nullptr; // 如果管道打开失败，返回 NULL
    }
    
    std::string result;
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }

    // 检查生成的密钥是否为空
    if (result.empty()) {
        return nullptr; // 如果没有生成密钥，返回 NULL
    }

    return result; // 返回 PEM 格式的 RSA 私有密钥
}