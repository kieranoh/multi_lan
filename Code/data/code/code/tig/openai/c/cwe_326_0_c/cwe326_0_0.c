#include <stdio.h>
#include <stdlib.h>

char *create_private_key() {
    const char *command = "openssl genpkey -algorithm RSA -pkeyopt rsa_keygen_bits:2048 2>/dev/null";
    FILE *fp;
    char *key = NULL;
    size_t key_size = 0;
    size_t read_size;

    // Open the command for reading.
    fp = popen(command, "r");
    if (fp == NULL) {
        return NULL; // Command execution failed
    }

    // Allocate an initial buffer for the key.
    size_t buffer_size = 1024;
    key = malloc(buffer_size);
    if (key == NULL) {
        pclose(fp);
        return NULL; // Memory allocation failed
    }

    // Read the output of the command.
    while ((read_size = fread(key + key_size, 1, buffer_size - key_size, fp)) > 0) {
        key_size += read_size;
        if (key_size >= buffer_size) {
            buffer_size *= 2; // Double the buffer size
            char *new_key = realloc(key, buffer_size);
            if (new_key == NULL) {
                free(key);
                pclose(fp);
                return NULL; // Memory allocation failed
            }
            key = new_key;
        }
    }

    // Null-terminate the string.
    if (key_size > 0) {
        key[key_size] = '\0';
    } else {
        free(key);
        key = NULL; // No key generated
    }

    // Close the command stream.
    pclose(fp);
    return key;
}