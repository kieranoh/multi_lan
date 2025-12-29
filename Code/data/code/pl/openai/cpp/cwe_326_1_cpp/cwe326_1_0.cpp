#include <iostream>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <fcntl.h>

std::string execute_command(const std::string& command);

std::string create_dsa_key() {
    // Generate a unique temporary file name
    char param_filename[] = "/tmp/tempXXXXXX";
    int fd = mkstemp(param_filename);
    if (fd == -1) {
        return nullptr; // Error creating temporary file
    }
    close(fd); // Close the file descriptor, we only need the filename

    // Command to create DSA parameters
    std::string param_command = "openssl dsaparam -out " + std::string(param_filename) + " 2048";
    if (execute_command(param_command) != "success") {
        return nullptr; // Error generating DSA parameters
    }

    // Command to generate DSA private key
    std::string key_command = "openssl gendsa -out /tmp/dsa_private.pem " + std::string(param_filename);
    if (execute_command(key_command) != "success") {
        return nullptr; // Error generating DSA key
    }

    // Read the generated private key from the file
    std::string private_key = execute_command("cat /tmp/dsa_private.pem");
    
    // Clean up temporary files
    remove(param_filename);
    remove("/tmp/dsa_private.pem");

    return private_key.empty() ? nullptr : private_key; // Return the private key or NULL if empty
}