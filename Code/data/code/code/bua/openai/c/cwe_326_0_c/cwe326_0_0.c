#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *create_private_key() {
    FILE *fp;
    char *buffer = NULL;
    long length;

    // Open a pipe to the openssl command
    fp = popen("openssl genpkey -algorithm RSA -pkeyopt rsa_keygen_bits:2048 2>/dev/null", "r");
    if (fp == NULL) {
        return NULL; // Error executing command
    }

    // Read the output from the command
    fseek(fp, 0, SEEK_END);
    length = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    buffer = (char *)malloc(length + 1);
    if (buffer == NULL) {
        pclose(fp);
        return NULL; // Memory allocation error
    }

    fread(buffer, 1, length, fp);
    buffer[length] = '\0'; // Null-terminate the string

    // Close the pipe
    pclose(fp);
    return buffer; // Return the PEM formatted private key
}