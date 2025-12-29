#include <iostream>
#include <string>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <stdexcept>

// Function declaration for executing shell commands
std::string execute_command(const std::string& command);

std::string create_dsa_key() {
    // Default key size for DSA
    const int key_size = 2048;
    
    // Create temporary file for DSA parameters
    char param_filename[] = "/tmp/tempXXXXXX";
    int fd = mkstemp(param_filename);
    
    if (fd == -1) {
        throw std::runtime_error("Failed to create temporary file for DSA parameters");
    }
    close(fd); // We just need the filename, not the file descriptor
    
    try {
        // Step 1: Generate DSA parameters
        std::string param_cmd = "openssl dsaparam -out " + std::string(param_filename) + 
                                " " + std::to_string(key_size);
        std::string param_result = execute_command(param_cmd);
        
        // Check if parameter generation was successful
        if (!param_result.empty()) {
            // Clean up temporary file
            unlink(param_filename);
            throw std::runtime_error("Failed to generate DSA parameters: " + param_result);
        }
        
        // Step 2: Generate DSA private key from parameters
        std::string key_cmd = "openssl gendsa " + std::string(param_filename);
        std::string private_key = execute_command(key_cmd);
        
        // Clean up temporary file
        unlink(param_filename);
        
        // Check if key generation was successful
        if (private_key.empty()) {
            throw std::runtime_error("Failed to generate DSA private key");
        }
        
        // Verify the output looks like a PEM private key
        if (private_key.find("-----BEGIN DSA PRIVATE KEY-----") == std::string::npos) {
            throw std::runtime_error("Generated key doesn't appear to be in PEM format");
        }
        
        return private_key;
        
    } catch (...) {
        // Clean up temporary file in case of any exception
        unlink(param_filename);
        throw;
    }
}