#include <stdio.h>
#include <stdlib.h>

char *create_private_key(int key_length) {
    // Allocate a buffer for the command
    char command[256];
    
    // Prepare the command to generate the RSA private key
    snprintf(command, sizeof(command), "openssl genpkey -algorithm RSA -pkeyopt rsa_keygen_bits:%d 2>/dev/null", key_length);
    
    // Create a temporary file to store the output
    FILE *fp = popen(command, "r");
    if (fp == NULL) {
        return NULL; // Command execution failed
    }

    // Allocate memory for the key
    char *private_key = malloc(4096); // Adjust size as necessary
    if (private_key == NULL) {
        pclose(fp);
        return NULL; // Memory allocation failed
    }

    // Read the key from the command's output
    size_t len = fread(private_key, 1, 4096, fp);
    private_key[len] = '\0'; // Null-terminate the string

    // Close the file pointer
    pclose(fp);

    // Return the generated private key
    return private_key;
}