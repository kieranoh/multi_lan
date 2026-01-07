#include <string>
#include <memory>
#include <cstdio>
#include <stdexcept>
#include <array>

std::string create_private_key() {
    const int key_length = 2048;
    std::array<char, 128> buffer;
    std::string result;
    
    std::string command = "openssl genpkey -algorithm RSA -pkeyopt rsa_keygen_bits:" + 
                          std::to_string(key_length) + " 2>/dev/null";
    
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(command.c_str(), "r"), pclose);
    if (!pipe) {
        return nullptr;
    }
    
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    
    if (result.empty()) {
        return nullptr;
    }
    
    return result;
}