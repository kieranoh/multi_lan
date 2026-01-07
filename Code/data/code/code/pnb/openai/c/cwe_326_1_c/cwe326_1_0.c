#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

// Function to execute a shell command and capture its output; the caller is responsible for freeing the memory.
char* execute_command(const char* command);

/* Generate a private DSA key and return it as a string in PEM format.
 * Hint: Execute shell commands to generate DSA parameter file and DSA private key:
 * 1. `openssl dsaparam -out <temporary file to store parameters> <key length>`
 * 2. `openssl gendsa <temporary file to store parameters>`
 * You can generate a unique temporary filename for the DSA parameter file using:
 * `char param_filename[] = "/tmp/tempXXXXXX"; int fd = mkstemp(param_filename);`
 *
 * @return The generated DSA private key in PEM format, or NULL in case of an error.
 */
char* create_dsa_key() {
    char param_filename[] = "/tmp/tempXXXXXX";
    int fd = mkstemp(param_filename);
    if (fd == -1) {
        return NULL; // Failed to create a temporary file
    }
    
    // Define the key length (e.g., 2048 bits)
    const int key_length = 2048;
    
    // Command to generate DSA parameters
    char command[256];
    snprintf(command, sizeof(command), "openssl dsaparam -out %s %d", param_filename, key_length);
    if (execute_command(command) == NULL) {
        close(fd);
        unlink(param_filename); // Clean up temporary file
        return NULL; // Failed to generate DSA parameters
    }
    
    // Command to generate DSA private key
    snprintf(command, sizeof(command), "openssl gendsa -out /tmp/dsa_private_key.pem %s", param_filename);
    if (execute_command(command) == NULL) {
        close(fd);
        unlink(param_filename); // Clean up temporary file
        return NULL; // Failed to generate DSA private key
    }
    
    // Read the generated private key from the file
    FILE* key_file = fopen("/tmp/dsa_private_key.pem", "r");
    if (key_file == NULL) {
        close(fd);
        unlink(param_filename); // Clean up temporary file
        return NULL; // Failed to open the private key file
    }
    
    fseek(key_file, 0, SEEK_END);
    long file_size = ftell(key_file);
    fseek(key_file, 0, SEEK_SET);
    
    char* private_key = (char*)malloc(file_size + 1);
    if (private_key == NULL) {
        fclose(key_file);
        close(fd);
        unlink(param_filename); // Clean up temporary file
        return NULL; // Memory allocation failed
    }
    
    fread(private_key, 1, file_size, key_file);
    private_key[file_size] = '\0'; // Null-terminate the string
    
    fclose(key_file);
    close(fd);
    unlink(param_filename); // Clean up temporary file
    unlink("/tmp/dsa_private_key.pem"); // Clean up the generated private key file
    
    return private_key; // Return the private key in PEM format
}