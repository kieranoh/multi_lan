#include <iostream>
#include <string>
#include <memory>
#include <cstdlib>
#include <stdexcept>

std::string create_private_key(int key_length) {
    // Prepare the command to generate RSA private key using OpenSSL
    std::string command = "openssl genpkey -algorithm RSA -pkeyopt rsa_keygen_bits:" + std::to_string(key_length) + " 2>/dev/null";
    
    // Using a buffer to capture the output
    const int buffer_size = 128;
    char buffer[buffer_size];
    std::string result;

    // Open the command for reading
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(command.c_str(), "r"), pclose);
    if (!pipe) {
        throw std::runtime_error("popen() failed!");
    }

    // Read the output a line at a time - output it.
    while (fgets(buffer, sizeof(buffer), pipe.get()) != nullptr) {
        result += buffer;
    }

    return result;
}