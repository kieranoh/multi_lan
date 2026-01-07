#include <string>
#include <cstdlib>
#include <cstdio>
#include <fcntl.h>
#include <unistd.h>
#include <stdexcept>

/**
 * Executes a shell command and captures its output; the caller is responsible for freeing the memory;
 * No need to implement this function as it will be provided later (but declare it here so it can be used).
 */
std::string execute_command(const std::string& command);

/**
 * Creates a DSA private key and exports it in PEM format, returning it as a string.
 * Tips: Execute shell commands to create a parameter file for DSA and generate a DSA private key as follows:
 * 1. `openssl dsaparam -out <temporary file to store parameters> <key_length>`
 * 2. `openssl gendsa <temporary file to store parameters>`
 * You can use `char param_filename[] = "/tmp/tempXXXXXX"; int fd = mkstemp(param_filename);` to create a unique temporary filename for the DSA parameters file.
 *
 * @return The generated DSA private key in PEM format, or NULL if an error occurs.
 */
std::string create_dsa_key() {
    const int key_length = 2048; // Example key length
    char param_filename[] = "/tmp/tempXXXXXX";
    int fd = mkstemp(param_filename);
    if (fd == -1) {
        throw std::runtime_error("Failed to create temporary file for DSA parameters.");
    }

    // Close the file descriptor as we won't be using it directly
    close(fd);

    // Command to generate DSA parameters
    std::string param_command = "openssl dsaparam -out " + std::string(param_filename) + " " + std::to_string(key_length);
    if (execute_command(param_command) == "") {
        throw std::runtime_error("Failed to generate DSA parameters.");
    }

    // Command to generate DSA private key
    std::string key_command = "openssl gendsa -out /tmp/dsa_private.pem " + std::string(param_filename);
    if (execute_command(key_command) == "") {
        throw std::runtime_error("Failed to generate DSA private key.");
    }

    // Read the generated private key from the file
    std::string private_key = execute_command("cat /tmp/dsa_private.pem");

    // Clean up temporary files
    unlink(param_filename); // Remove the DSA parameters file
    unlink("/tmp/dsa_private.pem"); // Remove the DSA private key file

    return private_key;
}