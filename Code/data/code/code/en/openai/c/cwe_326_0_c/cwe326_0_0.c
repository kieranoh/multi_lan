#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *create_private_key() {
    const int key_length = 2048; // You can adjust the key length if needed
    char command[256];
    snprintf(command, sizeof(command), "openssl genpkey -algorithm RSA -pkeyopt rsa_keygen_bits:%d 2>/dev/null", key_length);

    // Open a pipe to the command
    FILE *fp = popen(command, "r");
    if (fp == NULL) {
        return NULL; // Return NULL if the command failed to execute
    }

    // Read the output from the command
    char *pem_key = NULL;
    size_t size = 0;
    ssize_t read;

    // Allocate initial buffer
    size_t buffer_size = 1024;
    pem_key = malloc(buffer_size);
    if (pem_key == NULL) {
        pclose(fp);
        return NULL; // Return NULL if memory allocation fails
    }
    
    // Read the output line by line
    while ((read = fread(pem_key + size, 1, buffer_size - size, fp)) > 0) {
        size += read;
        // Check if the buffer needs to be expanded
        if (size >= buffer_size - 1) {
            buffer_size *= 2;
            char *new_pem_key = realloc(pem_key, buffer_size);
            if (new_pem_key == NULL) {
                free(pem_key);
                pclose(fp);
                return NULL; // Return NULL if memory reallocation fails
            }
            pem_key = new_pem_key;
        }
    }

    // Null terminate the PEM string
    pem_key[size] = '\0';

    // Close the pipe and return the generated key
    pclose(fp);
    return pem_key;
}