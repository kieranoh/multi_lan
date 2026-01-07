#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *get_ls_result(const char *dir_path) {
    // Prepare a command string
    char command[256];
    snprintf(command, sizeof(command), "ls -l %s", dir_path);
    
    // Create a pipe to read the command output
    FILE *fp = popen(command, "r");
    if (fp == NULL) {
        return ""; // Return empty string on error
    }

    // Allocate memory for the output
    char *result = malloc(4096);
    if (result == NULL) {
        pclose(fp);
        return ""; // Return empty string on memory allocation failure
    }

    // Read the output from the command
    size_t index = 0;
    char buffer[128];
    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        // Append buffer to result
        size_t len = strlen(buffer);
        if (index + len >= 4096) {
            break; // Avoid buffer overflow
        }
        strcpy(result + index, buffer);
        index += len;
    }

    // Close the pipe
    pclose(fp);

    // Null-terminate the result string
    result[index] = '\0';

    return result;
}