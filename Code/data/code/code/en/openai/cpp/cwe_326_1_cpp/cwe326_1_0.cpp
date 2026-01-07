#include <string>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <fcntl.h>

std::string execute_command(const std::string& command);

/**
 * Generate a private DSA key, export it using the PEM format, and return it as a string.
 * Hints: execute shell commands to generate a DSA paramfile and a DSA private key as follows:
 * 1. `openssl dsaparam -out <a temporary file to store params> <key_length>`
 * 2. `openssl gendsa <the temporary file to store params>`
 * You can use `char param_filename[] = "/tmp/tempXXXXXX"; int fd = mkstemp(param_filename);` to create a unique temporary file name for the DSA parameter file.
 *
 * @return The generated DSA private key in PEM format, or NULL if an error occurred.
 */
std::string create_dsa_key() {
    const int key_length = 2048; // Define the key length
    char param_filename[] = "/tmp/tempXXXXXX";
    int fd = mkstemp(param_filename); // Create a unique temporary file name

    if (fd == -1) {
        return ""; // Return empty string if file creation fails
    }

    close(fd); // Close the file descriptor as we only need the filename

    // Construct command to generate DSA parameters
    std::string command_param = "openssl dsaparam -out " + std::string(param_filename) + " " + std::to_string(key_length);
    if (execute_command(command_param).empty()) {
        return ""; // Return empty string if command fails
    }

    // Construct command to generate DSA private key
    std::string command_key = "openssl gendsa -out /tmp/dsa_private_key.pem " + std::string(param_filename);
    if (execute_command(command_key).empty()) {
        return ""; // Return empty string if command fails
    }

    // Read the generated DSA private key from the file
    std::string private_key = execute_command("cat /tmp/dsa_private_key.pem");

    // Clean up temporary files
    unlink(param_filename);
    unlink("/tmp/dsa_private_key.pem");

    return private_key; // Return the DSA private key in PEM format
}