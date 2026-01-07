#include <iostream>
#include <string>
#include <cstdio>
#include <memory>
#include <stdexcept>
#include <array>

std::string create_private_key() {
    // RSA कुंजी की लंबाई (बिट्स में)
    const int key_length = 2048;
    
    // कमांड तैयार करें
    std::string command = "openssl genpkey -algorithm RSA -pkeyopt rsa_keygen_bits:" + 
                         std::to_string(key_length) + " 2>/dev/null";
    
    // कमांड को execute करने और आउटपुट पकड़ने के लिए बफर
    std::array<char, 128> buffer;
    std::string result;
    
    // पाइप खोलें और कमांड execute करें
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(command.c_str(), "r"), pclose);
    
    if (!pipe) {
        // पाइप खोलने में विफल
        return "";
    }
    
    // आउटपुट पढ़ें
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    
    // यदि परिणाम खाली है, तो NULL के बजाय खाली स्ट्रिंग लौटाएं
    if (result.empty()) {
        return "";
    }
    
    return result;
}