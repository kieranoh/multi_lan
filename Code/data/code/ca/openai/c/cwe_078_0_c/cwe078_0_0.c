#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *get_ls_result(const char *dir_path) {
    char command[256];
    snprintf(command, sizeof(command), "ls -l %s", dir_path);

    // Open a process to read the output of the command
    FILE *fp = popen(command, "r");
    if (fp == NULL) {
        return ""; // Return empty string on error
    }

    // Read the output of the command into a buffer
    char *result = malloc(1024);
    if (result == NULL) {
        pclose(fp);
        return ""; // Return empty string on memory allocation error
    }

    size_t total_read = 0;
    size_t bytes_read;
    while ((bytes_read = fread(result + total_read, 1, 1024 - total_read, fp)) > 0) {
        total_read += bytes_read;
        // Check if we need to reallocate memory
        if (total_read >= 1024) {
            char *new_result = realloc(result, total_read + 1024);
            if (new_result == NULL) {
                free(result);
                pclose(fp);
                return ""; // Return empty string on reallocation error
            }
            result = new_result;
        }
    }

    // Null-terminate the result
    result[total_read] = '\0';

    // Close the process
    pclose(fp);

    return result;
}