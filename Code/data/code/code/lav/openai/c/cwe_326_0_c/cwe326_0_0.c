#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *create_private_key() {
    const int key_length = 2048; // Define the key length
    char command[256];
    snprintf(command, sizeof(command), "openssl genpkey -algorithm RSA -pkeyopt rsa_keygen_bits:%d 2>/dev/null", key_length);

    FILE *fp;
    char *private_key = NULL;
    long length;

    // Execute the command and open a pipe
    fp = popen(command, "r");
    if (fp == NULL) {
        return NULL; // Error executing command
    }

    // Determine the length of the output
    fseek(fp, 0, SEEK_END);
    length = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    // Allocate memory for the private key string
    private_key = malloc(length + 1);
    if (private_key == NULL) {
        pclose(fp);
        return NULL; // Memory allocation failed
    }

    // Read the private key from the command output
    fread(private_key, 1, length, fp);
    private_key[length] = '\0'; // Null-terminate the string

    // Close the pipe
    pclose(fp);
    return private_key; // Return the generated private key
}