#include <iostream>
#include <string>
#include <memory>
#include <stdexcept>
#include <array>
#include <sstream>
#include <cstdio>

std::string create_private_key(int key_length = 2048) {
    // Create a command to generate RSA private key using OpenSSL
    std::string command = "openssl genpkey -algorithm RSA -pkeyopt rsa_keygen_bits:" + std::to_string(key_length) + " 2>/dev/null";

    // Use a pipe to read the output of the command
    std::array<char, 128> buffer;
    std::string result;
    
    // Run the command and read its output
    std::shared_ptr<FILE> pipe(popen(command.c_str(), "r"), pclose);
    if (!pipe) {
        throw std::runtime_error("popen() failed!");
    }

    // Read the output into the result string
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }

    // Check if the result is empty, indicating an error
    if (result.empty()) {
        return nullptr; // Return NULL in case of error
    }

    return result; // Return the generated PEM formatted private key
}