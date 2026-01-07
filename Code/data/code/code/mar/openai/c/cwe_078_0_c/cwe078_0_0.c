#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *get_ls_result(const char *dir_path) {
    // Buffer to store the command output
    char buffer[128];
    // Create a command string using the provided directory path
    char command[256];
    snprintf(command, sizeof(command), "ls -l %s", dir_path);

    // Open the command for reading
    FILE *pipe = popen(command, "r");
    if (pipe == NULL) {
        return ""; // Return empty string on error
    }

    // Allocate memory for the result
    char *result = malloc(1024); // Adjust size as necessary
    if (result == NULL) {
        pclose(pipe);
        return ""; // Return empty string on memory allocation failure
    }

    // Initialize result string
    result[0] = '\0';

    // Read the output a line at a time - output it.
    while (fgets(buffer, sizeof(buffer), pipe) != NULL) {
        strcat(result, buffer);
    }

    // Close the pipe
    pclose(pipe);
    
    // Return the result
    return result;
}