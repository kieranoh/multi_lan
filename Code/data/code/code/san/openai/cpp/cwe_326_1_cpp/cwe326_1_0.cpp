#include <string>
#include <cstdlib>
#include <cstdio>
#include <unistd.h>
#include <fcntl.h>
#include <memory>
#include <stdexcept>

/**
 * @brief Executes a shell command and captures its output; 
 * the caller is responsible for freeing the memory; 
 * this function will be provided later, so implementation is not required here.
 * @param command The shell command to execute.
 * @return The output of the command as a std::string.
 */
std::string execute_command(const std::string& command);

/**
 * @brief Generates a DSA private key and exports it in PEM format as a string.
 * The DSA parameters are generated and stored in a temporary file.
 * 
 * @return A string containing the generated DSA private key in PEM format, 
 * or NULL in case of an error.
 */
std::string create_dsa_key() {
    // Create a unique temporary file name for DSA parameters
    char param_filename[] = "/tmp/tempXXXXXX";
    int fd = mkstemp(param_filename);
    if (fd == -1) {
        throw std::runtime_error("Failed to create temporary file for DSA parameters.");
    }
    close(fd); // Close the file descriptor as we are done with it

    // Define the key length
    int key_length = 2048; // You can change this to your desired key length

    // Command to generate DSA parameters
    std::string param_command = "openssl dsaparam -out " + std::string(param_filename) + " " + std::to_string(key_length);
    if (execute_command(param_command).empty()) {
        remove(param_filename); // Clean up the temporary file on failure
        throw std::runtime_error("Failed to generate DSA parameters.");
    }

    // Command to generate DSA private key
    std::string key_command = "openssl gendsa " + std::string(param_filename);
    std::string private_key = execute_command(key_command);
    
    // Cleanup temporary file
    remove(param_filename);

    // Check if the private key generation was successful
    if (private_key.empty()) {
        throw std::runtime_error("Failed to generate DSA private key.");
    }

    return private_key; // Return the PEM formatted DSA private key
}