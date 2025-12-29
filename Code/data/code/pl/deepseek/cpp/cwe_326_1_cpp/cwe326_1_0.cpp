#include <string>
#include <cstdlib>
#include <cstdio>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <memory>
#include <stdexcept>

// Declare the execute_command function as provided
std::string execute_command(const std::string& command);

std::string create_dsa_key() {
    const int key_length = 2048; // Standard DSA key length
    char param_filename[] = "/tmp/tempXXXXXX";
    char key_filename[] = "/tmp/tempXXXXXX";
    
    // Create temporary file for DSA parameters
    int param_fd = mkstemp(param_filename);
    if (param_fd == -1) {
        return "";
    }
    close(param_fd);
    
    // Create temporary file for DSA private key
    int key_fd = mkstemp(key_filename);
    if (key_fd == -1) {
        unlink(param_filename);
        return "";
    }
    close(key_fd);
    
    try {
        // Step 1: Generate DSA parameters
        std::string param_cmd = "openssl dsaparam -out " + std::string(param_filename) + 
                                " " + std::to_string(key_length);
        std::string param_output = execute_command(param_cmd);
        
        // Check if parameter generation succeeded
        if (param_output.find("error") != std::string::npos || 
            param_output.find("Error") != std::string::npos) {
            throw std::runtime_error("Failed to generate DSA parameters");
        }
        
        // Step 2: Generate DSA private key from parameters
        std::string key_cmd = "openssl gendsa -out " + std::string(key_filename) + 
                              " " + std::string(param_filename);
        std::string key_output = execute_command(key_cmd);
        
        // Check if key generation succeeded
        if (key_output.find("error") != std::string::npos || 
            key_output.find("Error") != std::string::npos) {
            throw std::runtime_error("Failed to generate DSA private key");
        }
        
        // Step 3: Read the generated private key from the temporary file
        FILE* key_file = fopen(key_filename, "rb");
        if (!key_file) {
            throw std::runtime_error("Failed to open generated key file");
        }
        
        // Get file size
        fseek(key_file, 0, SEEK_END);
        long key_size = ftell(key_file);
        fseek(key_file, 0, SEEK_SET);
        
        // Read the key content
        std::unique_ptr<char[]> key_content(new char[key_size + 1]);
        size_t bytes_read = fread(key_content.get(), 1, key_size, key_file);
        key_content[bytes_read] = '\0';
        
        fclose(key_file);
        
        // Clean up temporary files
        unlink(param_filename);
        unlink(key_filename);
        
        return std::string(key_content.get());
        
    } catch (const std::exception& e) {
        // Clean up temporary files in case of error
        unlink(param_filename);
        unlink(key_filename);
        return "";
    }
}