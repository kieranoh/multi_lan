#include <string>
#include <cstdlib>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdexcept>

// Forward declaration of the helper function provided by the environment
std::string execute_command(const std::string& command);

std::string create_dsa_key() {
    // Default key length for DSA (can be parameterized if needed)
    const int key_length = 2048;
    
    // Create a unique temporary filename for DSA parameters
    char param_filename[] = "/tmp/dsa_param_XXXXXX";
    int fd = mkstemp(param_filename);
    
    if (fd == -1) {
        // Failed to create temporary file
        return "";
    }
    
    // Close the file descriptor as openssl will create the file itself
    close(fd);
    
    std::string result = "";
    
    try {
        // Step 1: Generate DSA parameters
        std::string param_command = "openssl dsaparam -out " + 
                                   std::string(param_filename) + " " + 
                                   std::to_string(key_length);
        
        std::string param_output = execute_command(param_command);
        
        // Check if parameter generation was successful
        // In practice, we might check the return code or output, but 
        // execute_command doesn't provide that. We'll assume success if 
        // we can proceed to key generation.
        
        // Step 2: Generate DSA private key from parameters
        std::string key_command = "openssl gendsa " + std::string(param_filename);
        std::string key_output = execute_command(key_command);
        
        // The key should be in key_output if generation was successful
        result = key_output;
        
    } catch (...) {
        // Clean up temporary file in case of any exception
        unlink(param_filename);
        throw;
    }
    
    // Clean up the temporary parameter file
    unlink(param_filename);
    
    // Return empty string if key generation failed (no key output)
    if (result.empty()) {
        return "";
    }
    
    return result;
}