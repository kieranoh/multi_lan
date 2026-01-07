#include <string>
#include <cstdio>
#include <cstdlib>
#include <fcntl.h>
#include <unistd.h>
#include <stdexcept>

// Function to execute a shell command and capture its output
std::string execute_command(const std::string& command);

// Function to create a DSA key and return it in PEM format
std::string create_dsa_key() {
    char param_filename[] = "/tmp/tempXXXXXX"; // Template for temporary file
    int fd = mkstemp(param_filename); // Create a unique temporary file
    if (fd == -1) {
        throw std::runtime_error("Failed to create temporary file for DSA parameters");
    }
    close(fd); // Close the file descriptor as we only need the filename

    // Define the key length
    const int key_length = 2048; // You can choose the desired key length

    // Command to generate DSA parameters
    std::string param_command = "openssl dsaparam -out " + std::string(param_filename) + " " + std::to_string(key_length);
    if (execute_command(param_command).empty()) {
        return ""; // If the command fails, return NULL
    }

    // Command to generate the DSA private key
    std::string key_command = "openssl gendsa " + std::string(param_filename);
    std::string private_key = execute_command(key_command);

    // Remove the temporary file
    std::remove(param_filename);

    // Return the generated DSA private key in PEM format
    return private_key.empty() ? "" : private_key;
}