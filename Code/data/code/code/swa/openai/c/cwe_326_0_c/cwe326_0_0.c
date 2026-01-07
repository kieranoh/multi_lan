#include <stdio.h>
#include <stdlib.h>

char *create_private_key() {
    // Key length for RSA
    int key_length = 2048; // You can adjust the key length as needed
    char command[256];
    snprintf(command, sizeof(command), "openssl genpkey -algorithm RSA -pkeyopt rsa_keygen_bits:%d 2>/dev/null", key_length);
    
    // Open a pipe to the command
    FILE *fp = popen(command, "r");
    if (fp == NULL) {
        return NULL; // Error executing command
    }

    // Allocate memory for the key
    char *private_key = malloc(4096); // Allocate enough memory for the key
    if (private_key == NULL) {
        pclose(fp);
        return NULL; // Memory allocation failed
    }

    // Read the key from the pipe
    size_t bytes_read = fread(private_key, 1, 4096, fp);
    private_key[bytes_read] = '\0'; // Null-terminate the string

    // Close the pipe
    pclose(fp);

    // Return the private key
    return private_key;
}