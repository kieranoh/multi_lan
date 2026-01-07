#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

// Function declaration for execute_command
char* execute_command(const char* command);

char* create_dsa_key() {
    // Create temporary file for DSA parameters
    char param_filename[] = "/tmp/tempXXXXXX";
    int fd = mkstemp(param_filename);
    
    if (fd == -1) {
        // Failed to create temporary file
        return NULL;
    }
    
    // Close the file descriptor since we only need the filename
    close(fd);
    
    // Key length (2048 bits is a reasonable default for DSA)
    int key_length = 2048;
    
    // Step 1: Generate DSA parameters
    char cmd1[256];
    snprintf(cmd1, sizeof(cmd1), "openssl dsaparam -out %s %d", param_filename, key_length);
    
    char* result1 = execute_command(cmd1);
    if (result1 == NULL) {
        // Clean up temporary file
        unlink(param_filename);
        return NULL;
    }
    
    // Check if parameter generation was successful
    if (strstr(result1, "writing new key") == NULL && strstr(result1, "Generating") == NULL) {
        // Parameter generation may have failed
        free(result1);
        unlink(param_filename);
        return NULL;
    }
    
    free(result1);
    
    // Step 2: Generate DSA private key from parameters
    char cmd2[256];
    snprintf(cmd2, sizeof(cmd2), "openssl gendsa %s 2>&1", param_filename);
    
    char* result2 = execute_command(cmd2);
    
    // Clean up temporary parameter file
    unlink(param_filename);
    
    if (result2 == NULL) {
        return NULL;
    }
    
    // Check if key generation was successful
    // Successful DSA key generation typically contains "writing new key" or similar
    if (strstr(result2, "writing new key") == NULL && strstr(result2, "-----BEGIN DSA PRIVATE KEY-----") == NULL) {
        // Key generation failed
        free(result2);
        return NULL;
    }
    
    // Return the generated key
    return result2;
}