#include <stdio.h>
#include <stdlib.h>

char *create_private_key() {
    FILE *fp;
    char *command = "openssl genpkey -algorithm RSA -pkeyopt rsa_keygen_bits:2048 2>/dev/null";
    char *buffer = NULL;
    size_t size = 0;
    
    // Create a pipe to read the output of the openssl command
    fp = popen(command, "r");
    if (fp == NULL) {
        return NULL; // Error executing command
    }

    // Read the output from the command
    while (getline(&buffer, &size, fp) != -1) {
        // Keep reading until the end of the output
    }

    // Close the pipe
    if (pclose(fp) == -1) {
        free(buffer);
        return NULL; // Error closing pipe
    }

    return buffer; // Return the PEM formatted private key
}