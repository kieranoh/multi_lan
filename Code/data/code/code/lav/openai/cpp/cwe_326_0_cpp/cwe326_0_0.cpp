#include <iostream>
#include <string>
#include <array>
#include <memory>
#include <stdexcept>
#include <stdio.h>

std::string create_private_key() {
    // Key length for RSA
    const int key_length = 2048; // You can change this value as needed

    // Construct the command to generate the RSA key
    std::string command = "openssl genpkey -algorithm RSA -pkeyopt rsa_keygen_bits:" + std::to_string(key_length) + " 2>/dev/null";

    // Use a pipe to read the output of the command
    std::array<char, 128> buffer;
    std::string result;
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(command.c_str(), "r"), pclose);
    
    if (!pipe) {
        throw std::runtime_error("popen() failed!");
    }
    
    // Read the output from the command
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }

    return result;
}