#include <iostream>
#include <string>
#include <array>
#include <memory>

std::string create_private_key() {
    // Command to generate RSA private key using OpenSSL
    const std::string command = "openssl genpkey -algorithm RSA -pkeyopt rsa_keygen_bits:2048 2>/dev/null";
    
    // Run the command and capture the output
    std::array<char, 128> buffer;
    std::string result;

    // Use popen to execute the command and read the output
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(command.c_str(), "r"), pclose);
    if (!pipe) {
        return ""; // Return an empty string on error
    }

    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }

    return result.empty() ? "" : result; // Return the result or an empty string if there's no output
}