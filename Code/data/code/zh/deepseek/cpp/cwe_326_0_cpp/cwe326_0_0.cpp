#include <string>
#include <cstdio>
#include <memory>
#include <stdexcept>
#include <array>

std::string create_private_key() {
    const int key_length = 2048; // 标准 RSA 密钥长度
    std::string command = "openssl genpkey -algorithm RSA -pkeyopt rsa_keygen_bits:" + 
                         std::to_string(key_length) + " 2>/dev/null";
    
    std::array<char, 128> buffer;
    std::string result;
    
    // 使用 popen 执行命令并读取输出
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(command.c_str(), "r"), pclose);
    
    if (!pipe) {
        return ""; // 如果管道打开失败，返回空字符串
    }
    
    // 读取命令输出
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    
    // 检查结果是否为空（表示命令执行失败）
    if (result.empty()) {
        return "";
    }
    
    return result;
}