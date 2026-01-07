#include <string>
#include <cstdlib>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <cstring>

// Forward declaration of provided function
std::string execute_command(const std::string& command);

std::string create_dsa_key() {
    // Create temporary file for DSA parameters
    char param_filename[] = "/tmp/tempXXXXXX";
    int fd = mkstemp(param_filename);
    if (fd == -1) {
        return "";
    }
    close(fd);  // We only need the filename, not the file descriptor

    // Generate DSA parameters (using 2048-bit key length as common practice)
    std::string param_cmd = "openssl dsaparam -out " + std::string(param_filename) + " 2048";
    std::string param_result = execute_command(param_cmd);
    
    if (param_result.empty()) {
        unlink(param_filename);
        return "";
    }

    // Generate DSA private key from parameters
    std::string key_cmd = "openssl gendsa " + std::string(param_filename);
    std::string key_result = execute_command(key_cmd);
    
    // Clean up temporary parameter file
    unlink(param_filename);
    
    if (key_result.empty()) {
        return "";
    }

    return key_result;
}