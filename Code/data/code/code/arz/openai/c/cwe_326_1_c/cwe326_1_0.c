#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

char* execute_command(const char* command);

char* create_dsa_key() {
    char param_filename[] = "/tmp/tempXXXXXX";
    int fd = mkstemp(param_filename);
    if (fd == -1) {
        return NULL; // Error creating temporary file
    }
    close(fd); // Close the file descriptor, we only need the filename

    // Step 1: Generate DSA parameters
    char command_param[256];
    snprintf(command_param, sizeof(command_param), "openssl dsaparam -out %s 2048", param_filename);
    if (execute_command(command_param) == NULL) {
        unlink(param_filename); // Clean up
        return NULL; // Error executing command
    }

    // Step 2: Generate DSA private key
    char command_key[256];
    snprintf(command_key, sizeof(command_key), "openssl gendsa -out %s %s", param_filename, param_filename);
    char* dsa_key = execute_command(command_key);
    if (dsa_key == NULL) {
        unlink(param_filename); // Clean up
        return NULL; // Error executing command
    }

    // Clean up the temporary parameter file
    unlink(param_filename);

    return dsa_key; // Return the generated DSA private key
}