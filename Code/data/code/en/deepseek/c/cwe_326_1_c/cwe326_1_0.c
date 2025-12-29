#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

// Declare the provided function
char* execute_command(const char* command);

char* create_dsa_key() {
    // Default key length (can be modified if needed)
    const char* key_length = "2048";
    
    // Create temporary file for DSA parameters
    char param_filename[] = "/tmp/tempXXXXXX";
    int fd = mkstemp(param_filename);
    if (fd == -1) {
        return NULL;
    }
    close(fd);  // We just need the filename, not the file descriptor
    
    // Step 1: Generate DSA parameters
    char command1[256];
    snprintf(command1, sizeof(command1), "openssl dsaparam -out %s %s", param_filename, key_length);
    
    char* output1 = execute_command(command1);
    if (output1 == NULL) {
        unlink(param_filename);  // Clean up temp file
        return NULL;
    }
    free(output1);  // We don't need the output, just check if command succeeded
    
    // Step 2: Generate DSA private key from parameters
    char command2[256];
    snprintf(command2, sizeof(command2), "openssl gendsa %s", param_filename);
    
    char* key_output = execute_command(command2);
    
    // Clean up temporary parameter file
    unlink(param_filename);
    
    // Check if key generation was successful
    if (key_output == NULL || strlen(key_output) == 0) {
        if (key_output != NULL) {
            free(key_output);
        }
        return NULL;
    }
    
    return key_output;
}