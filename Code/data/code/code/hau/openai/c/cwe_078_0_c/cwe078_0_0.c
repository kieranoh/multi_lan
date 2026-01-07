#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *get_ls_result(const char *dir_path) {
    // Prepare a command string with the ls -l command for the specified directory
    char command[256];
    snprintf(command, sizeof(command), "ls -l %s", dir_path);

    // Open the command for reading
    FILE *fp = popen(command, "r");
    if (fp == NULL) {
        // If popen fails, return an empty string
        return "";
    }

    // Allocate memory for the output
    char *output = malloc(1024 * sizeof(char)); // Allocate enough for output
    if (output == NULL) {
        pclose(fp);
        return "";
    }

    // Read the output a line at a time - output it.
    size_t total_size = 0;
    size_t bytes_read;
    while ((bytes_read = fread(output + total_size, sizeof(char), 1024, fp)) > 0) {
        total_size += bytes_read;
        
        // Reallocate if the buffer is not enough
        if (total_size >= 1024) {
            char *temp = realloc(output, total_size + 1024);
            if (temp == NULL) {
                free(output);
                pclose(fp);
                return "";
            }
            output = temp;
        }
    }

    // Null-terminate the string
    output[total_size] = '\0';

    // Close the command stream
    pclose(fp);

    // Check if the output is empty (indicating an error occurred)
    if (total_size == 0) {
        free(output);
        return "";
    }

    return output;
}