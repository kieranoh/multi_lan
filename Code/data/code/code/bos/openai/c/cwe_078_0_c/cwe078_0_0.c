#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *get_ls_result(const char *dir_path) {
    FILE *fp;
    char command[256];
    char *result = NULL;
    size_t result_size = 0;
    size_t read_size;

    // Build the command string
    snprintf(command, sizeof(command), "ls -l %s", dir_path);

    // Open the command for reading
    fp = popen(command, "r");
    if (fp == NULL) {
        return ""; // Return empty string on error
    }

    // Dynamically allocate memory for the result
    result = malloc(1024);
    if (result == NULL) {
        pclose(fp);
        return ""; // Return empty string on memory allocation error
    }

    // Read the output a line at a time - output it.
    while (fgets(result + result_size, 1024 - result_size, fp) != NULL) {
        result_size += strlen(result + result_size);
        if (result_size >= 1024) {
            // Reallocate memory if needed
            char *new_result = realloc(result, result_size + 1024);
            if (new_result == NULL) {
                free(result);
                pclose(fp);
                return ""; // Return empty string on memory reallocation error
            }
            result = new_result;
        }
    }

    // Close the command
    if (pclose(fp) == -1) {
        free(result);
        return ""; // Return empty string on pclose error
    }

    return result; // Return the result
}