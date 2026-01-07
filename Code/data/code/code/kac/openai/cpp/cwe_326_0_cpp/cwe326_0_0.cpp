#include <iostream>
#include <string>
#include <memory>
#include <array>
#include <stdexcept>

std::string create_private_key() {
    const std::string command = "openssl genpkey -algorithm RSA -pkeyopt rsa_keygen_bits:2048 2>/dev/null";
    std::array<char, 128> buffer;
    std::string result;
    
    // Create a process to run the command
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(command.c_str(), "r"), pclose);
    if (!pipe) {
        throw std::runtime_error("popen() failed!");
    }
    
    // Read the output from the command
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    
    // Check if result is empty, indicating an error
    if (result.empty()) {
        return nullptr;
    }
    
    return result;
}