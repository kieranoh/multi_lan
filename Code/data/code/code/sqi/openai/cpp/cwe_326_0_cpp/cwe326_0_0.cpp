#include <iostream>
#include <string>
#include <cstdlib>
#include <memory>
#include <array>

std::string create_private_key() {
    // Generate the command to create an RSA private key using OpenSSL
    const std::string command = "openssl genpkey -algorithm RSA -pkeyopt rsa_keygen_bits:2048 2>/dev/null";

    // Use popen to execute the command and read the output
    std::array<char, 128> buffer;
    std::string result;
    
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(command.c_str(), "r"), pclose);
    if (!pipe) {
        return nullptr; // Return NULL if the pipe could not be opened
    }
    
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }

    return result.empty() ? nullptr : result; // Return NULL if result is empty
}