#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *get_ls_result(const char *dir_path) {
    // Command to execute
    char command[256];
    snprintf(command, sizeof(command), "ls -l %s", dir_path);

    // Open the command for reading
    FILE *fp = popen(command, "r");
    if (fp == NULL) {
        return ""; // Return empty string on error
    }

    // Allocate buffer for output
    char *buffer = malloc(4096);
    if (buffer == NULL) {
        pclose(fp);
        return ""; // Return empty string on error
    }

    // Read the output a line at a time - output it.
    size_t total_length = 0;
    size_t read_length;
    while ((read_length = fread(buffer + total_length, 1, 4096 - total_length, fp)) > 0) {
        total_length += read_length;
        if (total_length >= 4096) break; // Prevent overflow
    }
    
    // Close the command stream
    pclose(fp);

    // Null-terminate the string
    buffer[total_length] = '\0';

    // Return the result
    return buffer;
}