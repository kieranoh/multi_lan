#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

char* execute_command(const char* command);

/**
 * Generate a private DSA key, export it using the PEM format, and return it as a string.
 * Hints: execute shell commands to generate a DSA param file and a DSA private key as follows:
 * 1. `openssl dsaparam -out <a temporary file to store params> <key_length>`
 * 2. `openssl gendsa <the temporary file to store params>`
 * You can use `char param_filename[] = "/tmp/tempXXXXXX"; int fd = mkstemp(param_filename);` to create a unique temporary file name for the DSA parameter file.
 *
 * @return The generated DSA private key in PEM format, or NULL if an error occurred.
 */
char* create_dsa_key() {
    int fd;
    char param_filename[] = "/tmp/tempXXXXXX";
    fd = mkstemp(param_filename);
    if (fd == -1) {
        return NULL; // Error creating temporary file
    }
    close(fd); // We can close the file descriptor after using mkstemp

    // Define the key length
    const int key_length = 2048; // You can adjust the key length as needed
    char command[256];

    // Generate DSA parameters
    snprintf(command, sizeof(command), "openssl dsaparam -out %s %d", param_filename, key_length);
    if (execute_command(command) == NULL) {
        unlink(param_filename); // Clean up the temporary file
        return NULL; // Error executing command
    }

    // Generate DSA private key from parameters
    snprintf(command, sizeof(command), "openssl gendsa -out %s %s", "/tmp/dsa_private_key.pem", param_filename);
    if (execute_command(command) == NULL) {
        unlink(param_filename); // Clean up the temporary file
        return NULL; // Error executing command
    }

    // Read the private key from the file
    FILE *key_file = fopen("/tmp/dsa_private_key.pem", "r");
    if (key_file == NULL) {
        unlink(param_filename); // Clean up the temporary file
        return NULL; // Error opening key file
    }

    // Get the size of the private key
    fseek(key_file, 0, SEEK_END);
    long key_size = ftell(key_file);
    fseek(key_file, 0, SEEK_SET);

    // Allocate memory for the private key
    char *private_key = (char*)malloc(key_size + 1);
    if (private_key == NULL) {
        fclose(key_file);
        unlink(param_filename); // Clean up the temporary file
        return NULL; // Memory allocation error
    }

    // Read the private key into the buffer
    fread(private_key, 1, key_size, key_file);
    private_key[key_size] = '\0'; // Null-terminate the string

    fclose(key_file);
    unlink(param_filename); // Clean up the temporary file
    unlink("/tmp/dsa_private_key.pem"); // Clean up the private key file

    return private_key; // Return the private key
}