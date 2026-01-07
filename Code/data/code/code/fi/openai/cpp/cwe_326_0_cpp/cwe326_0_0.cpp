#include <iostream>
#include <string>
#include <cstdlib>
#include <memory>

std::string create_private_key() {
    // Define the command to generate the RSA private key using OpenSSL
    const std::string command = "openssl genpkey -algorithm RSA -pkeyopt rsa_keygen_bits:2048 2>/dev/null";

    // Create a unique pointer to a file stream
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(command.c_str(), "r"), pclose);
    
    // Check if the pipe was successfully opened
    if (!pipe) {
        return nullptr; // Return NULL if there was an error
    }

    // Read the output from the command
    char buffer[128];
    std::string result;
    while (fgets(buffer, sizeof(buffer), pipe.get()) != nullptr) {
        result += buffer; // Append the output to the result string
    }

    return result; // Return the private key in PEM format
}