#include <stdio.h>
#include <stdlib.h>

char *create_private_key() {
    const char *command = "openssl genpkey -algorithm RSA -pkeyopt rsa_keygen_bits:2048 2>/dev/null";
    FILE *fp;
    char *private_key = NULL;
    size_t length = 0;

    // Open the command for reading.
    fp = popen(command, "r");
    if (fp == NULL) {
        return NULL; // Command execution failed
    }

    // Read the output a line at a time - output it.
    // Allocate initial buffer size
    size_t buffer_size = 1024;
    private_key = malloc(buffer_size);
    if (private_key == NULL) {
        pclose(fp);
        return NULL; // Memory allocation failed
    }

    // Read the output from the command
    while (fgets(private_key + length, buffer_size - length, fp) != NULL) {
        length += strlen(private_key + length);
        if (length + 1 >= buffer_size) {
            buffer_size *= 2; // Double the buffer size
            private_key = realloc(private_key, buffer_size);
            if (private_key == NULL) {
                pclose(fp);
                return NULL; // Memory allocation failed
            }
        }
    }

    // Close the command stream
    pclose(fp);

    return private_key; // Return the generated key
}