#include <string>
#include <cstdlib>
#include <cstdio>
#include <unistd.h>
#include <fcntl.h>
#include <stdexcept>
#include <cstring>

std::string execute_command(const std::string& command);

std::string create_dsa_key() {
    // Generate a unique temporary filename
    char param_filename[] = "/tmp/tempXXXXXX";
    int fd = mkstemp(param_filename);
    if (fd == -1) {
        throw std::runtime_error("Failed to create temporary file for DSA parameters.");
    }
    close(fd); // Close the file descriptor since we only need the filename

    // Define the key length
    const int key_length = 2048; // You can adjust the key length as needed

    // Create the command to generate DSA parameters
    std::string param_command = "openssl dsaparam -out " + std::string(param_filename) + " " + std::to_string(key_length);
    if (execute_command(param_command) == nullptr) {
        std::remove(param_filename); // Clean up the temporary file
        throw std::runtime_error("Failed to generate DSA parameters.");
    }

    // Create the command to generate the DSA private key
    std::string key_command = "openssl gendsa " + std::string(param_filename);
    std::string private_key = execute_command(key_command);
    
    // Clean up the temporary parameter file
    std::remove(param_filename);

    // Return the private key or throw an error if it failed
    if (private_key.empty()) {
        throw std::runtime_error("Failed to generate DSA private key.");
    }

    return private_key;
}