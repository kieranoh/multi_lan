#include <iostream>
#include <sstream>
#include <cstdlib>
#include <cstdio>
#include <memory>
#include <stdexcept>

std::string create_private_key() {
    const std::string command = "openssl genpkey -algorithm RSA -pkeyopt rsa_keygen_bits:2048 2>/dev/null";
    std::array<char, 128> buffer;
    std::string result;

    // Open the command for reading
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(command.c_str(), "r"), pclose);
    if (!pipe) {
        return nullptr; // Return nullptr if the pipe could not be opened
    }

    // Read the output a line at a time - output it.
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }

    if (result.empty()) {
        return nullptr; // Return nullptr if the result is empty (indicating an error)
    }

    return result; // Return the generated private key in PEM format
}