#include <string>
#include <cstdlib>
#include <memory>
#include <stdexcept>
#include <array>

std::string create_private_key() {
    const std::string command = "openssl genpkey -algorithm RSA -pkeyopt rsa_keygen_bits:2048 2>/dev/null";
    
    std::array<char, 128> buffer;
    std::string result;
    
    // Use popen to execute the command and read the output
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(command.c_str(), "r"), pclose);
    if (!pipe) {
        throw std::runtime_error("popen() failed!");
    }

    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }

    // Check if the result is empty, which may indicate an error
    if (result.empty()) {
        return nullptr; // or you may choose to throw an exception
    }

    return result;
}