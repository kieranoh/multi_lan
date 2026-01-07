#include <string>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <unistd.h>
#include <fcntl.h>

std::string execute_command(const std::string& command);

std::string create_dsa_key() {
    char param_filename[] = "/tmp/tempXXXXXX";
    int fd = mkstemp(param_filename);
    if (fd == -1) {
        return nullptr; // Failed to create a temporary file
    }
    close(fd); // Close the file descriptor as we only need the filename

    // Generate DSA parameters and save to the temporary file
    std::string param_command = "openssl dsaparam -out " + std::string(param_filename) + " 2048";
    if (execute_command(param_command) == "") {
        unlink(param_filename); // Cleanup the temporary file
        return nullptr; // Failed to generate DSA parameters
    }

    // Generate DSA private key using the parameters file
    std::string key_command = "openssl gendsa " + std::string(param_filename);
    std::string private_key = execute_command(key_command);

    unlink(param_filename); // Cleanup the temporary file
    return private_key.empty() ? nullptr : private_key; // Return the key or NULL on failure
}