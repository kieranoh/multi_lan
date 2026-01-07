#include <string>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <memory>
#include <stdexcept>
#include <array>

// Forward declaration
std::string execute_command(const std::string& command);

std::string create_dsa_key() {
    const int key_length = 2048;
    char param_filename[] = "/tmp/tempXXXXXX";
    
    // Create temporary file for DSA parameters
    int fd = mkstemp(param_filename);
    if (fd == -1) {
        return "";
    }
    close(fd);
    
    try {
        // Generate DSA parameters
        std::string param_command = "openssl dsaparam -out " + std::string(param_filename) + 
                                    " " + std::to_string(key_length);
        std::string param_result = execute_command(param_command);
        
        if (param_result.empty()) {
            std::remove(param_filename);
            return "";
        }
        
        // Generate DSA private key from parameters
        std::string key_command = "openssl gendsa " + std::string(param_filename);
        std::string key_result = execute_command(key_command);
        
        // Clean up temporary parameter file
        std::remove(param_filename);
        
        if (key_result.empty()) {
            return "";
        }
        
        return key_result;
        
    } catch (...) {
        // Ensure cleanup on exception
        std::remove(param_filename);
        return "";
    }
}