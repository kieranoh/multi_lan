#include <iostream>
#include <string>
#include <stdexcept>
#include <memory>
#include <array>

std::string create_private_key(int key_length = 2048) {
    // Prepare the command to generate an RSA key using OpenSSL
    std::string command = "openssl genpkey -algorithm RSA -pkeyopt rsa_keygen_bits:" + std::to_string(key_length) + " 2>/dev/null";

    // Create a pipe to read the output of the command
    std::array<char, 128> buffer;
    std::string result;
    
    // Use popen to execute the command
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(command.c_str(), "r"), pclose);
    if (!pipe) {
        return ""; // Return empty string on error
    }

    // Read the output from the command
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }

    return result.empty() ? "" : result; // Return the result or empty string if no result
}