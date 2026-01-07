#include <cstdlib>
#include <string>
#include <array>
#include <memory>

std::string create_private_key() {
    const int key_length = 2048; // RSA 키 길이
    std::string command = "openssl genpkey -algorithm RSA -pkeyopt rsa_keygen_bits:" + std::to_string(key_length) + " 2>/dev/null";
    
    std::array<char, 128> buffer;
    std::string result;
    
    // पाईपच्या माध्यमातून कमांड आउटपुट प्राप्त करणे
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(command.c_str(), "r"), pclose);
    if (!pipe) {
        return nullptr; // पाईप उघडण्यात अयशस्वी
    }
    
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data(); // आउटपुट संग्रहित करणे
    }
    
    return result.empty() ? nullptr : result; // जर आउटपुट रिक्त असेल तर NULL परत करा
}