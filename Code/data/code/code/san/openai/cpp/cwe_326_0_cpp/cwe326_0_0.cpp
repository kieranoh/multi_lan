#include <iostream>
#include <string>
#include <stdexcept>
#include <array>
#include <memory>

std::string create_private_key(int key_length) {
    // Create a command to generate RSA private key using OpenSSL
    std::string command = "openssl genpkey -algorithm RSA -pkeyopt rsa_keygen_bits:" + std::to_string(key_length) + " 2>/dev/null";

    // Use a pipe to read the output of the command
    std::array<char, 128> buffer;
    std::string result;
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(command.c_str(), "r"), pclose);
    
    if (!pipe) {
        throw std::runtime_error("popen() failed!");
    }
    
    // Read the output of the command
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }

    // If the result is empty, it indicates an error occurred
    if (result.empty()) {
        return nullptr; // or handle error appropriately
    }

    return result; // Return the PEM formatted RSA private key
}