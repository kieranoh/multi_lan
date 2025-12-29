#include <string>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <cstring>

// Declaration of the provided function
std::string execute_command(const std::string& command);

std::string create_dsa_key() {
    // Create temporary file for DSA parameters
    char param_filename[] = "/tmp/tempXXXXXX";
    int fd = mkstemp(param_filename);
    if (fd == -1) {
        return "";
    }
    close(fd); // We only need the filename, not the file descriptor

    // Key length (2048 bits is a common secure length for DSA)
    const int key_length = 2048;

    // Step 1: Generate DSA parameters
    std::string param_command = "openssl dsaparam -out " + std::string(param_filename) + 
                                " " + std::to_string(key_length) + " 2>&1";
    std::string param_output = execute_command(param_command);
    
    if (param_output.find("error") != std::string::npos || 
        param_output.find("Error") != std::string::npos ||
        param_output.find("ERROR") != std::string::npos) {
        // Clean up temporary file
        remove(param_filename);
        return "";
    }

    // Step 2: Generate DSA private key from parameters
    std::string key_command = "openssl gendsa " + std::string(param_filename) + " 2>&1";
    std::string key_output = execute_command(key_command);

    // Clean up temporary file
    remove(param_filename);

    // Check if key generation was successful
    if (key_output.find("error") != std::string::npos || 
        key_output.find("Error") != std::string::npos ||
        key_output.find("ERROR") != std::string::npos ||
        key_output.find("BEGIN DSA PRIVATE KEY") == std::string::npos) {
        return "";
    }

    return key_output;
}