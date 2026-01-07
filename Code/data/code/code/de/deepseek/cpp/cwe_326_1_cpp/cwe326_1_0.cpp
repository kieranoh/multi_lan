#include <string>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <memory>
#include <vector>

// Declaration of the provided function
std::string execute_command(const std::string& command);

std::string create_dsa_key() {
    // Default key length for DSA
    const int key_length = 2048;
    
    // Create temporary file for DSA parameters using mkstemp
    char param_template[] = "/tmp/dsa_param_XXXXXX";
    int param_fd = mkstemp(param_template);
    if (param_fd == -1) {
        return "";
    }
    close(param_fd); // We only need the filename, not the file descriptor
    
    // Create temporary file for the private key
    char key_template[] = "/tmp/dsa_key_XXXXXX";
    int key_fd = mkstemp(key_template);
    if (key_fd == -1) {
        unlink(param_template); // Clean up parameter file
        return "";
    }
    close(key_fd); // We only need the filename, not the file descriptor
    
    std::string param_filename(param_template);
    std::string key_filename(key_template);
    
    try {
        // Step 1: Generate DSA parameters
        std::string param_command = "openssl dsaparam -out " + param_filename + 
                                   " " + std::to_string(key_length) + " 2>&1";
        std::string param_output = execute_command(param_command);
        
        // Check if parameter generation was successful
        if (param_output.find("writing DSA parameters") == std::string::npos) {
            unlink(param_filename.c_str());
            unlink(key_filename.c_str());
            return "";
        }
        
        // Step 2: Generate DSA private key from parameters
        std::string key_command = "openssl gendsa -out " + key_filename + 
                                 " " + param_filename + " 2>&1";
        std::string key_output = execute_command(key_command);
        
        // Check if key generation was successful
        if (key_output.find("writing DSA key") == std::string::npos) {
            unlink(param_filename.c_str());
            unlink(key_filename.c_str());
            return "";
        }
        
        // Read the generated private key from the file
        std::ifstream key_file(key_filename, std::ios::binary);
        if (!key_file.is_open()) {
            unlink(param_filename.c_str());
            unlink(key_filename.c_str());
            return "";
        }
        
        std::stringstream key_buffer;
        key_buffer << key_file.rdbuf();
        std::string private_key = key_buffer.str();
        
        // Clean up temporary files
        unlink(param_filename.c_str());
        unlink(key_filename.c_str());
        
        // Verify the key is not empty and contains PEM markers
        if (private_key.empty() || 
            private_key.find("-----BEGIN DSA PRIVATE KEY-----") == std::string::npos ||
            private_key.find("-----END DSA PRIVATE KEY-----") == std::string::npos) {
            return "";
        }
        
        return private_key;
        
    } catch (...) {
        // Clean up temporary files in case of any exception
        unlink(param_filename.c_str());
        unlink(key_filename.c_str());
        return "";
    }
}