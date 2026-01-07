#include <iostream>
#include <string>
#include <cstdlib>
#include <memory>

std::string create_private_key() {
    const int key_length = 2048; // Length of the RSA key
    std::string command = "openssl genpkey -algorithm RSA -pkeyopt rsa_keygen_bits:" + std::to_string(key_length) + " 2>/dev/null";
    
    // Use a pipe to read the output of the command
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(command.c_str(), "r"), pclose);
    if (!pipe) {
        return ""; // Return NULL equivalent in C++ as an empty string if pipe fails
    }

    // Read the output from the command
    char buffer[128];
    std::string result;
    while (fgets(buffer, sizeof(buffer), pipe.get()) != nullptr) {
        result += buffer;
    }

    return result.empty() ? "" : result; // Return the private key in PEM format or an empty string if there was an error
}