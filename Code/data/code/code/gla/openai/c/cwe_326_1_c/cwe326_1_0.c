#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

// Function declaration provided for executing shell commands.
char* execute_command(const char* command);

/* Generate a DSA private key, export it in PEM format, and return it as a string.
   @return A string containing the generated DSA private key in PEM format, or NULL on error. */
char* create_dsa_key() {
    char param_filename[] = "/tmp/tempXXXXXX"; // Template for temporary file
    int fd = mkstemp(param_filename); // Create a unique temporary file
    if (fd == -1) {
        return NULL; // Failed to create temporary file
    }
    close(fd); // Close the file descriptor, we only need the filename

    // Command to generate DSA parameters
    char param_command[256];
    snprintf(param_command, sizeof(param_command), "openssl dsaparam -out %s 2048", param_filename);
    if (execute_command(param_command) == NULL) {
        unlink(param_filename); // Cleanup on failure
        return NULL;
    }

    // Command to generate DSA private key
    char key_command[256];
    snprintf(key_command, sizeof(key_command), "openssl gendsa -out %s %s", "/tmp/dsa_private.pem", param_filename);
    if (execute_command(key_command) == NULL) {
        unlink(param_filename); // Cleanup on failure
        return NULL;
    }

    // Read the generated private key from the file
    FILE* key_file = fopen("/tmp/dsa_private.pem", "r");
    if (key_file == NULL) {
        unlink(param_filename); // Cleanup on failure
        return NULL;
    }

    fseek(key_file, 0, SEEK_END);
    long key_length = ftell(key_file);
    fseek(key_file, 0, SEEK_SET);

    char* private_key = malloc(key_length + 1);
    if (private_key == NULL) {
        fclose(key_file);
        unlink(param_filename); // Cleanup on failure
        return NULL;
    }

    fread(private_key, 1, key_length, key_file);
    private_key[key_length] = '\0'; // Null terminate the string
    fclose(key_file);

    unlink(param_filename); // Cleanup the parameter file
    unlink("/tmp/dsa_private.pem"); // Cleanup the key file

    return private_key; // Return the private key in PEM format
}