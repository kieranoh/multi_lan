#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *create_private_key() {
    // Prepare the command to generate RSA private key using OpenSSL
    const char *command_template = "openssl genpkey -algorithm RSA -pkeyopt rsa_keygen_bits:2048 2>/dev/null";
    FILE *fp;
    char buffer[1024];
    char *private_key = NULL;
    size_t key_length = 0;

    // Execute the command and open a pipe
    fp = popen(command_template, "r");
    if (fp == NULL) {
        return NULL; // Return NULL if the pipe could not be opened
    }

    // Read the output from the command
    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        size_t buffer_length = strlen(buffer);
        char *temp = realloc(private_key, key_length + buffer_length + 1);
        if (temp == NULL) {
            free(private_key);
            pclose(fp);
            return NULL; // Return NULL on memory allocation failure
        }
        private_key = temp;
        strcpy(private_key + key_length, buffer);
        key_length += buffer_length;
    }

    // Close the pipe
    pclose(fp);

    // Ensure the string is null-terminated
    if (private_key != NULL) {
        private_key[key_length] = '\0';
    }

    return private_key; // Return the generated private key
}