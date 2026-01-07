#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *get_ls_result(const char *dir_path) {
    // Command to be executed
    char command[256];
    snprintf(command, sizeof(command), "ls -l %s", dir_path);
    
    // Open the command for reading
    FILE *fp = popen(command, "r");
    if (fp == NULL) {
        return ""; // Error opening the command
    }

    // Allocate buffer for output
    char *result = malloc(4096); // Allocate sufficient memory for output
    if (result == NULL) {
        pclose(fp);
        return ""; // Memory allocation failed
    }
    result[0] = '\0'; // Initialize the result string

    // Read the output a line at a time - output it.
    char buffer[256];
    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        strcat(result, buffer); // Append the output to the result
    }

    // Close the command stream
    if (pclose(fp) == -1) {
        free(result);
        return ""; // Error closing the command
    }

    return result; // Return the result
}