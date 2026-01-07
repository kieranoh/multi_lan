#include <string>
#include <cstdlib>
#include <cstdio>
#include <unistd.h>
#include <fcntl.h>

std::string execute_command(const std::string& command);

std::string create_dsa_key() {
    // Create a temporary file for DSA parameters
    char param_filename[] = "/tmp/tempXXXXXX";
    int fd = mkstemp(param_filename);
    if (fd == -1) {
        return ""; // Return empty string on failure
    }
    close(fd);

    // Prepare the commands
    std::string command_param = "openssl dsaparam -out " + std::string(param_filename) + " 2048";
    std::string command_key = "openssl gendsa " + std::string(param_filename);

    // Execute the commands
    if (execute_command(command_param).empty() || execute_command(command_key).empty()) {
        unlink(param_filename); // Clean up the temporary file
        return ""; // Return empty string if any command fails
    }

    // Read the private key from the default output (assuming it's printed on stdout)
    std::string private_key = execute_command("openssl gendsa -outform PEM " + std::string(param_filename));

    // Clean up the temporary file
    unlink(param_filename);

    return private_key; // Return the DSA private key in PEM format
}