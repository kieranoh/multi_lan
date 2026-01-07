#include <iostream>
#include <string>
#include <array>
#include <stdexcept>
#include <memory>

std::string create_private_key(int key_length = 2048) {
    // Command to generate the RSA private key using OpenSSL
    std::string command = "openssl genpkey -algorithm RSA -pkeyopt rsa_keygen_bits:" + std::to_string(key_length) + " 2>/dev/null";

    // Create a buffer to capture the output
    std::array<char, 128> buffer;
    std::string result;

    // Open a pipe to the command
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(command.c_str(), "r"), pclose);
    if (!pipe) {
        throw std::runtime_error("popen() failed!");
    }

    // Read the output of the command
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }

    return result;
}