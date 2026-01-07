#include <iostream>
#include <string>
#include <array>
#include <memory>

std::string create_private_key() {
    const std::string command = "openssl genpkey -algorithm RSA -pkeyopt rsa_keygen_bits:2048 2>/dev/null";
    
    // Use a pipe to read the output of the command
    std::array<char, 128> buffer;
    std::string result;
    
    // Execute the command
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(command.c_str(), "r"), pclose);
    if (!pipe) {
        return nullptr; // Return NULL if the pipe could not be opened
    }

    // Read the output from the command
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }

    // Check if we successfully received a key
    if (result.empty()) {
        return nullptr; // Return NULL if no key was generated
    }
    
    return result; // Return the PEM formatted private key
}