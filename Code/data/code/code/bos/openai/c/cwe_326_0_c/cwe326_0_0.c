#include <stdio.h>
#include <stdlib.h>

char *create_private_key() {
    FILE *fp;
    char *command = "openssl genpkey -algorithm RSA -pkeyopt rsa_keygen_bits:2048 2>/dev/null";
    char *buffer = NULL;
    size_t size = 0;
    
    // Open a pipe to run the command
    fp = popen(command, "r");
    if (fp == NULL) {
        return NULL; // Error running command
    }
    
    // Read the output from the command
    if (getline(&buffer, &size, fp) == -1) {
        pclose(fp);
        free(buffer);
        return NULL; // Error reading output
    }
    
    // Close the pipe
    pclose(fp);
    
    return buffer; // Return the generated key
}