#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *create_private_key(int key_length) {
    // Prepare the command to generate RSA private key using OpenSSL
    char command[256];
    snprintf(command, sizeof(command), "openssl genpkey -algorithm RSA -pkeyopt rsa_keygen_bits:%d 2>/dev/null", key_length);

    // Create a temporary file to store the private key
    FILE *fp = tmpfile();
    if (fp == NULL) {
        return NULL; // Return NULL if temp file creation fails
    }

    // Execute the command and direct the output to the temporary file
    if (popen(command, "r") == NULL) {
        fclose(fp);
        return NULL; // Return NULL if command execution fails
    }

    // Seek to the beginning of the file to read the private key
    rewind(fp);

    // Allocate memory for the private key
    char *private_key = malloc(2048);
    if (private_key == NULL) {
        fclose(fp);
        return NULL; // Return NULL if memory allocation fails
    }

    // Read the content from the temporary file into the private key variable
    size_t bytes_read = fread(private_key, 1, 2048, fp);
    private_key[bytes_read] = '\0'; // Null-terminate the string

    // Close the temporary file
    fclose(fp);
    
    // Return the private key
    return private_key;
}