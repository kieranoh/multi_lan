#include <iostream>
#include <string>
#include <memory>
#include <array>
#include <stdexcept>

std::string create_private_key() {
    const std::string command = "openssl genpkey -algorithm RSA -pkeyopt rsa_keygen_bits:2048 2>/dev/null";
    std::array<char, 128> buffer;
    std::string result;

    // Create a pipe to read the output of the command
    auto pipe = popen(command.c_str(), "r");
    if (!pipe) {
        throw std::runtime_error("popen() failed!");
    }

    // Read the output until EOF
    while (fgets(buffer.data(), buffer.size(), pipe) != nullptr) {
        result += buffer.data();
    }

    // Close the pipe
    if (pclose(pipe) == -1) {
        return nullptr; // Error occurred
    }

    return result.empty() ? nullptr : result; // Return NULL on error
}