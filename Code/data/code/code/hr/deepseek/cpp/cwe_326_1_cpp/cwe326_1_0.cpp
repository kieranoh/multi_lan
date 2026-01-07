#include <string>
#include <cstdlib>
#include <cstdio>
#include <unistd.h>
#include <cstring>

// Forward declaration of the provided function
std::string execute_command(const std::string& command);

std::string create_dsa_key() {
    // Default key length (can be adjusted if needed)
    const int key_length = 2048;
    
    // Create temporary file for DSA parameters
    char param_filename[] = "/tmp/tempXXXXXX";
    int fd = mkstemp(param_filename);
    if (fd == -1) {
        return "";
    }
    close(fd);
    
    // Create temporary file for the private key
    char key_filename[] = "/tmp/tempXXXXXX";
    fd = mkstemp(key_filename);
    if (fd == -1) {
        remove(param_filename);
        return "";
    }
    close(fd);
    
    std::string result = "";
    
    try {
        // Step 1: Generate DSA parameters
        std::string param_cmd = "openssl dsaparam -out " + std::string(param_filename) + 
                                " " + std::to_string(key_length);
        std::string param_output = execute_command(param_cmd);
        
        // Check if parameter generation succeeded
        if (param_output.find("error") != std::string::npos || 
            param_output.find("Error") != std::string::npos) {
            remove(param_filename);
            remove(key_filename);
            return "";
        }
        
        // Step 2: Generate DSA private key from parameters
        std::string key_cmd = "openssl gendsa " + std::string(param_filename) + 
                              " -out " + std::string(key_filename);
        std::string key_output = execute_command(key_cmd);
        
        // Check if key generation succeeded
        if (key_output.find("error") != std::string::npos || 
            key_output.find("Error") != std::string::npos) {
            remove(param_filename);
            remove(key_filename);
            return "";
        }
        
        // Step 3: Read the generated private key
        FILE* key_file = fopen(key_filename, "r");
        if (key_file) {
            fseek(key_file, 0, SEEK_END);
            long file_size = ftell(key_file);
            fseek(key_file, 0, SEEK_SET);
            
            char* buffer = new char[file_size + 1];
            size_t bytes_read = fread(buffer, 1, file_size, key_file);
            buffer[bytes_read] = '\0';
            result = std::string(buffer);
            
            delete[] buffer;
            fclose(key_file);
        }
        
        // Clean up temporary files
        remove(param_filename);
        remove(key_filename);
        
    } catch (...) {
        // Clean up in case of any exception
        remove(param_filename);
        remove(key_filename);
        return "";
    }
    
    return result;
}