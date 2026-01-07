#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

char* execute_command(const char* command);

char* create_dsa_key() {
    // Create a temporary file for DSA parameters
    char param_filename[] = "/tmp/tempXXXXXX";
    int fd = mkstemp(param_filename);
    if (fd == -1) {
        return NULL;
    }
    close(fd); // We can close the file descriptor now

    // Set the key length
    int key_length = 2048; // You can adjust the key length as needed
    char command[256];

    // Generate DSA parameters
    snprintf(command, sizeof(command), "openssl dsaparam -out %s %d", param_filename, key_length);
    if (execute_command(command) == NULL) {
        unlink(param_filename); // Remove the temp file if command failed
        return NULL;
    }

    // Generate DSA private key
    char* private_key_command = (char*)malloc(256);
    if (private_key_command == NULL) {
        unlink(param_filename);
        return NULL;
    }

    snprintf(private_key_command, 256, "openssl gendsa %s", param_filename);
    char* private_key = execute_command(private_key_command);
    free(private_key_command); // Free the command string

    // Clean up the temporary parameter file
    unlink(param_filename);

    return private_key; // Return the PEM formatted private key or NULL on error
}