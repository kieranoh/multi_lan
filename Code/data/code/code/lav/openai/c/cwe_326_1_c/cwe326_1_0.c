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
        return NULL; // Failed to create a temporary file
    }
    close(fd); // Close the file descriptor, we just need the filename

    // Define the key length
    const int key_length = 2048; // You can adjust this as needed
    char command[256];

    // Generate DSA parameters
    snprintf(command, sizeof(command), "openssl dsaparam -out %s %d", param_filename, key_length);
    if (execute_command(command) == NULL) {
        unlink(param_filename); // Clean up the temporary file
        return NULL; // Failed to generate DSA parameters
    }

    // Generate DSA private key
    snprintf(command, sizeof(command), "openssl gendsa %s", param_filename);
    char* private_key = execute_command(command);
    
    // Clean up the temporary file
    unlink(param_filename); 

    return private_key; // Returns the private key or NULL on failure
}