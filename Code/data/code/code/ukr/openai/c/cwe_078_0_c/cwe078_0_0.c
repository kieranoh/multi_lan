#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

char *get_ls_result(const char *dir_path) {
    // Create a command string
    char command[BUFFER_SIZE];
    snprintf(command, sizeof(command), "ls -l %s", dir_path);
    
    // Open the command for reading
    FILE *fp = popen(command, "r");
    if (fp == NULL) {
        return ""; // Return empty string on error
    }

    // Allocate buffer for the output
    char *output = malloc(BUFFER_SIZE);
    if (output == NULL) {
        pclose(fp);
        return ""; // Return empty string if memory allocation fails
    }

    // Clear the output buffer
    output[0] = '\0';

    // Read the output a line at a time - output it.
    while (fgets(output + strlen(output), BUFFER_SIZE - strlen(output), fp) != NULL) {
        // Check if the output buffer is full
        if (strlen(output) + BUFFER_SIZE < BUFFER_SIZE) {
            // Concatenate the new output
            strcat(output, output);
        } else {
            break; // Stop reading if buffer is full
        }
    }

    // Close the command stream
    pclose(fp);
    
    // Return the output
    return output;
}