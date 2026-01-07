#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

char* execute_command(const char* command);

char* create_dsa_key() {
    char param_filename[] = "/tmp/tempXXXXXX";
    int fd = mkstemp(param_filename);
    if (fd == -1) {
        return NULL; // Error creating temp file
    }
    close(fd); // Close the file descriptor as we only need the filename

    // Generate DSA parameters
    char command[256];
    snprintf(command, sizeof(command), "openssl dsaparam -out %s 2048", param_filename);
    if (execute_command(command) == NULL) {
        unlink(param_filename); // Remove the temp file if command fails
        return NULL;
    }

    // Generate DSA private key
    snprintf(command, sizeof(command), "openssl gendsa -out temp_dsa_key.pem %s", param_filename);
    if (execute_command(command) == NULL) {
        unlink(param_filename); // Clean up
        return NULL;
    }

    // Read the generated private key from the file
    FILE* key_file = fopen("temp_dsa_key.pem", "r");
    if (key_file == NULL) {
        unlink(param_filename);
        return NULL;
    }

    fseek(key_file, 0, SEEK_END);
    long key_length = ftell(key_file);
    fseek(key_file, 0, SEEK_SET);

    char* private_key = (char*)malloc(key_length + 1);
    if (private_key == NULL) {
        fclose(key_file);
        unlink(param_filename);
        return NULL;
    }

    fread(private_key, 1, key_length, key_file);
    private_key[key_length] = '\0'; // Null-terminate the string

    fclose(key_file);
    unlink(param_filename); // Clean up temporary file
    unlink("temp_dsa_key.pem"); // Clean up generated key file

    return private_key; // Return the private key
}