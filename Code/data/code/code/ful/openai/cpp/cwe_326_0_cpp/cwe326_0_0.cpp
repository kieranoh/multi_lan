#include <cstdlib>
#include <string>
#include <memory>
#include <stdexcept>

std::string create_private_key() {
    const std::string command = "openssl genpkey -algorithm RSA -pkeyopt rsa_keygen_bits:2048 2>/dev/null";
    
    // Create a pipe to read the output of the command
    FILE* pipe = popen(command.c_str(), "r");
    if (!pipe) {
        throw std::runtime_error("Failed to open pipe for command execution.");
    }
    
    // Read the output from the command
    char buffer[128];
    std::string result;
    while (fgets(buffer, sizeof(buffer), pipe) != nullptr) {
        result += buffer;
    }
    
    // Close the pipe and check for errors
    if (pclose(pipe) == -1) {
        throw std::runtime_error("Failed to close the pipe.");
    }

    // If the result is empty, it indicates an error occurred
    return result.empty() ? "NULL" : result;
}