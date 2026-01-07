#include <iostream>
#include <string>
#include <array>
#include <memory>
#include <stdexcept>

std::string create_private_key() {
    // Key length can be customized as needed.
    const int key_length = 2048; // or any other valid length
    // Command to generate RSA private key using OpenSSL
    std::string command = "openssl genpkey -algorithm RSA -pkeyopt rsa_keygen_bits:" + std::to_string(key_length) + " 2>/dev/null";

    // Using a pipe to read the output of the command
    std::array<char, 128> buffer;
    std::string result;
    
    // Execute the command
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(command.c_str(), "r"), pclose);
    if (!pipe) {
        return nullptr; // Return NULL in case of error
    }
    
    // Read the output of the command
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }

    // If result is empty, it indicates an error
    if (result.empty()) {
        return nullptr;
    }

    return result; // Return the PEM formatted RSA private key
}