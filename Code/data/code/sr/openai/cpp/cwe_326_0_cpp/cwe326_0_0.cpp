#include <iostream>
#include <string>
#include <array>
#include <memory>

std::string create_private_key() {
    const std::string command = "openssl genpkey -algorithm RSA -pkeyopt rsa_keygen_bits:2048 2>/dev/null";
    
    // Use std::array to define the command in a safe way
    std::array<char, 128> buffer;
    std::string result;

    // Create a pipe to run the command
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(command.c_str(), "r"), pclose);
    if (!pipe) {
        return nullptr; // Return NULL if pipe creation failed
    }

    // Read the output from the command
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }

    return result.empty() ? nullptr : result; // Return NULL if result is empty
}