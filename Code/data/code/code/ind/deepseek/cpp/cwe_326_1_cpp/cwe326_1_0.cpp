#include <string>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <memory>
#include <stdexcept>
#include <array>

// Shell command execution function declaration
std::string execute_command(const std::string& command);

std::string create_dsa_key() {
    const int key_length = 2048;
    
    // Create unique temporary filename for DSA parameters
    char param_filename[] = "/tmp/tempXXXXXX";
    int fd = mkstemp(param_filename);
    if (fd == -1) {
        return "";
    }
    close(fd);
    
    // Create unique temporary filename for private key
    char key_filename[] = "/tmp/tempXXXXXX";
    fd = mkstemp(key_filename);
    if (fd == -1) {
        std::remove(param_filename);
        return "";
    }
    close(fd);
    
    std::string result;
    
    try {
        // Step 1: Generate DSA parameters
        std::string param_command = "openssl dsaparam -out " + std::string(param_filename) + 
                                   " " + std::to_string(key_length);
        std::string param_output = execute_command(param_command);
        
        // Check if parameter generation succeeded
        if (param_output.find("error") != std::string::npos || 
            param_output.find("Error") != std::string::npos) {
            throw std::runtime_error("Failed to generate DSA parameters");
        }
        
        // Step 2: Generate DSA private key from parameters
        std::string key_command = "openssl gendsa -out " + std::string(key_filename) + 
                                 " " + std::string(param_filename);
        std::string key_output = execute_command(key_command);
        
        // Check if key generation succeeded
        if (key_output.find("error") != std::string::npos || 
            key_output.find("Error") != std::string::npos) {
            throw std::runtime_error("Failed to generate DSA private key");
        }
        
        // Step 3: Read the generated private key file
        FILE* key_file = fopen(key_filename, "rb");
        if (!key_file) {
            throw std::runtime_error("Failed to open generated key file");
        }
        
        // Get file size
        fseek(key_file, 0, SEEK_END);
        long file_size = ftell(key_file);
        fseek(key_file, 0, SEEK_SET);
        
        // Read file content
        std::unique_ptr<char[]> buffer(new char[file_size + 1]);
        size_t bytes_read = fread(buffer.get(), 1, file_size, key_file);
        buffer[bytes_read] = '\0';
        
        fclose(key_file);
        
        result = std::string(buffer.get(), bytes_read);
        
    } catch (const std::exception& e) {
        // Clean up temporary files
        std::remove(param_filename);
        std::remove(key_filename);
        return "";
    }
    
    // Clean up temporary files
    std::remove(param_filename);
    std::remove(key_filename);
    
    // Return empty string if result is empty
    if (result.empty()) {
        return "";
    }
    
    return result;
}